#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH2D.h"
#include "TMath.h"
#include "TSystem.h"
#include "TSystemFile.h"
#include "TSystemDirectory.h"
#include "TLorentzVector.h"

#include "Messenger.h"
#include "CommandLine.h"
// #include "UseFJ.h"
#include "CommonFunctions.h"
#include "ProgressBar.h"
#include "CustomAssert.h"
#include "JetCorrector.h"

#include "tnp_weight.h"
#include "trackingEfficiency2017pp.h"
#include "trackingEfficiency2018PbPb.h"
#include "TrackResidualCorrector.h"

struct EventIndex;
struct JetRecord;
int main(int argc, char *argv[]);
int FindFirstAbove(vector<EventIndex> &Indices, double X);
double GetHFSum(PFTreeMessenger *M, double MinPFPT);
double GetGenHFSum(GenParticleTreeMessenger *M, double MinGenTrackPT);

struct EventIndex
{
public:
   double HF;
   double VZ;
   int File;
   int Event;
public:
   bool operator <(const EventIndex &other) const
   {
      if(HF < other.HF)         return true;
      if(HF > other.HF)         return false;
      if(VZ < other.VZ)         return true;
      if(VZ > other.VZ)         return false;
      if(File < other.File)     return true;
      if(File > other.File)     return false;
      if(Event < other.Event)   return true;
      if(Event > other.Event)   return false;
      return false;
   }
};

struct JetRecord
{
public:
   double JetPT;
   double JetRawPT;
   double JetDEta;
   double JetDPhi;
   bool JetMuTagged;
   double RefPT;
   double RefDEta;
   double RefDPhi;
public:
   JetRecord(double pt = -1, double rawpt = -1, double deta = -1, double dphi = -1, bool mutagged = false, double refpt = -1, double refdeta = -1, double refdphi = -1)
      : JetPT(pt), JetRawPT(rawpt), JetDEta(deta), JetDPhi(dphi), JetMuTagged(mutagged),
      RefPT(refpt), RefDEta(refdeta), RefDPhi(refdphi)
   {
   }
   bool operator <(const JetRecord &other) const
   {
      if(JetPT < other.JetPT)   return true;
      if(JetPT > other.JetPT)   return false;
      if(JetRawPT < other.JetRawPT)   return true;
      if(JetRawPT > other.JetRawPT)   return false;
      if(JetDEta < other.JetDEta)   return true;
      if(JetDEta > other.JetDEta)   return false;
      if(JetDPhi < other.JetDPhi)   return true;
      if(JetDPhi > other.JetDPhi)   return false;
      if(JetMuTagged < other.JetMuTagged)   return true;
      if(JetMuTagged > other.JetMuTagged)   return false;
      if(RefPT < other.RefPT)   return true;
      if(RefPT > other.RefPT)   return false;
      if(RefDEta < other.RefDEta)   return true;
      if(RefDEta > other.RefDEta)   return false;
      if(RefDPhi < other.RefDPhi)   return true;
      if(RefDPhi > other.RefDPhi)   return false;
      return false;
   }
   bool operator >(const JetRecord &other) const
   {
      return (other < *this);
   }
};

int main(int argc, char *argv[])
{
   string Version = "V18";

   CommandLine CL(argc, argv);

   vector<string> InputFileNames      = CL.GetStringVector("Input");
   string OutputFileName              = CL.Get("Output");
   bool DoGenLevel                    = CL.GetBool("DoGenLevel", true);
   double Fraction                    = CL.GetDouble("Fraction", 1.00);
   double MinZPT                      = CL.GetDouble("MinZPT", 20.00);
   double MinTrackPT                  = CL.GetDouble("MinTrackPT", 1.00);
   double MinGenTrackPT               = CL.GetDouble("MinGenTrackPT", 0.40);
   double MinPFPT                     = CL.GetDouble("MinPFPT", 0);
   bool IsData                        = CL.GetBool("IsData", false);
   bool IsPP                          = CL.GetBool("IsPP", false);
   bool DoGenCorrelation              = CL.GetBool("DoGenCorrelation", false);
   bool GenCorrelationCharged         = CL.GetBool("GenCorrelationCharged", false);
   bool DoBackground                  = CL.GetBool("DoBackground", false);
   bool DoSumET                       = CL.GetBool("DoSumET", true);
   bool DoExtraAxes                   = CL.GetBool("DoExtraAxes", true);
   double MuonVeto                    = CL.GetDouble("MuonVeto", 0.01);
   bool DoJet                         = CL.GetBool("DoJet", false);
   vector<string> JECFiles            = DoJet ? CL.GetStringVector("JEC") : vector<string>{""};
   string JetTreeName                 = DoJet ? CL.Get("Jet") : "";
   double MinJetPT                    = CL.GetDouble("MinJetPT", 15);
   bool DoMCHiBinShift                = CL.GetBool("DoMCHiBinShift", true);
   double MCHiBinShift                = DoMCHiBinShift ? CL.GetDouble("MCHiBinShift", 3) : 0;

   bool DoAlternateTrackSelection     = CL.GetBool("DoAlternateTrackSelection", false);
   int AlternateTrackSelection        = DoAlternateTrackSelection ? CL.GetInt("AlternateTrackSelection") : 0;

   bool DoTrackEfficiency             = CL.GetBool("DoTrackEfficiency", true);
   string TrackEfficiencyPath         = (DoTrackEfficiency == true) ? CL.Get("TrackEfficiencyPath") : "";
   bool DoTrackResidual               = CL.GetBool("DoTrackResidual", false);
   vector<string> TrackResidualPath   = (DoTrackResidual == true) ? CL.GetStringVector("TrackResidualPath") : vector<string>{"", "", "", ""};

   string PFTreeName                  = IsPP ? "pfcandAnalyzer/pfTree" : "particleFlowAnalyser/pftree";
   PFTreeName                         = CL.Get("PFTree", PFTreeName);

   bool DoCS                          = CL.GetBool("DoCS", false);
   string RhoTreeName                 = CL.Get("RhoTree", "hiPuRhoAnalyzer/t");

   bool WithProgressBar               = CL.GetBool("WithProgressBar", false);

   // Assert(!(IsPP == true && IsData == true), "Data selections for pp not implemented yet");
   Assert(!(DoGenCorrelation == true && DoGenLevel == false), "You need to turn on gen level to do gen correlation!");
   if(DoTrackResidual == true)
      Assert(TrackResidualPath.size() == 1 || TrackResidualPath.size() == 4, "You need 1 file for residual correction or 4 files for centrality-dependence");

   if(DoBackground == true)
   {
      cerr << "=== WARNING ===" << endl;
      cerr << "Background mixing mode not supported anymore with this code.  Please use other specialized code for this.  I won't stop you though, proceed with your own risk" << endl;
      cerr << "=== WARNING ===" << endl;
   }

   JetCorrector JEC(JECFiles);

   vector<string> BackgroundFileNames;
   int NBackground = 0;
   double HFShift = 0;
   double HFTolerance = 0;
   double HFToleranceFraction = 0;
   double HFCeiling = -1;
   double VZTolerance = 0;
   int Oversample = 1;
   if(DoBackground == true)
   {
      BackgroundFileNames         = CL.GetStringVector("Background");
      VZTolerance                 = CL.GetDouble("VZTolerance", 2);
      HFShift                     = CL.GetDouble("HFShift");
      HFTolerance                 = CL.GetDouble("Tolerance");
      HFToleranceFraction         = CL.GetDouble("ToleranceFraction");
      HFCeiling                   = CL.GetDouble("HFCeiling", -1);
      NBackground                 = BackgroundFileNames.size();
      Oversample                  = CL.GetInteger("Oversample", 1);
   }

   TrkEff2017pp *TrackEfficiencyPP = nullptr;
   TrkEff2018PbPb *TrackEfficiencyPbPb = nullptr;
   if(DoTrackEfficiency == true)
   {
      if(IsPP == true)
         TrackEfficiencyPP = new TrkEff2017pp(false, TrackEfficiencyPath);
      else
      {
         if(DoAlternateTrackSelection == false)
            TrackEfficiencyPbPb = new TrkEff2018PbPb("general", "", false, TrackEfficiencyPath);
         if(DoAlternateTrackSelection == true && AlternateTrackSelection == 0)
            TrackEfficiencyPbPb = new TrkEff2018PbPb("general", "", false, TrackEfficiencyPath);
         if(DoAlternateTrackSelection == true && AlternateTrackSelection == 1)
            TrackEfficiencyPbPb = new TrkEff2018PbPb("general", "Loose", false, TrackEfficiencyPath);
         if(DoAlternateTrackSelection == true && AlternateTrackSelection == 2)
            TrackEfficiencyPbPb = new TrkEff2018PbPb("general", "Tight", false, TrackEfficiencyPath);
      }
   }

   //for(int iTRP=0;iTRP<TrackResidualPath.size();iTRP++)
   //   cout<<"TrackResidualPath = "<<TrackResidualPath[iTRP]<<endl;

   TrackResidualCentralityCorrector TrackResidual(TrackResidualPath);

   // Do some pre-caching if we read background files.
   // Later on if speed is an issue we can do some optimizations
   vector<TFile *>                    BackgroundFiles;
   vector<HiEventTreeMessenger *>     MBackgroundEvent;
   vector<GenParticleTreeMessenger *> MBackgroundGen;
   vector<TrackTreeMessenger *>       MBackgroundTrackPP;
   vector<PbPbTrackTreeMessenger *>   MBackgroundTrack;
   vector<PFTreeMessenger *>          MBackgroundPF;
   vector<RhoTreeMessenger *>         MBackgroundRho;
   vector<EventIndex>                 BackgroundIndices;
   if(DoBackground == true)
   {
      for(int iB = 0; iB < NBackground; iB++)
      {
         BackgroundFiles.push_back(new TFile(BackgroundFileNames[iB].c_str()));
         MBackgroundEvent.push_back(new HiEventTreeMessenger(BackgroundFiles[iB]));
         MBackgroundGen.push_back(new GenParticleTreeMessenger(BackgroundFiles[iB]));
         MBackgroundTrackPP.push_back(new TrackTreeMessenger(BackgroundFiles[iB]));
         MBackgroundTrack.push_back(new PbPbTrackTreeMessenger(BackgroundFiles[iB]));
         MBackgroundPF.push_back(new PFTreeMessenger(BackgroundFiles[iB], PFTreeName));
         MBackgroundRho.push_back(new RhoTreeMessenger(BackgroundFiles[iB], RhoTreeName));

         int EntryCount = MBackgroundEvent[iB]->GetEntries();
         for(int iE = 0; iE < EntryCount; iE++)
         {
            MBackgroundEvent[iB]->GetEntry(iE);
            MBackgroundGen[iB]->GetEntry(iE);
            MBackgroundPF[iB]->GetEntry(iE);
            EventIndex E;
            E.HF = DoGenCorrelation ? GetGenHFSum(MBackgroundGen[iB], MinGenTrackPT) : (DoSumET ? MBackgroundEvent[iB]->hiHF : GetHFSum(MBackgroundPF[iB], MinPFPT));
            E.VZ = MBackgroundEvent[iB]->vz;
            E.File = iB;
            E.Event = iE;
            BackgroundIndices.push_back(E);
         }
      }
   }
   sort(BackgroundIndices.begin(), BackgroundIndices.end());

   // Declare output files
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TNtuple NTuple("NTuple", "Z tree", "mass:pt:eta:phi");
   TTree Tree("Tree", Form("Tree for ZHadron analysis, %s", Version.c_str()));
   TTree InfoTree("InfoTree", "Information");

   string Key, Value;
   InfoTree.Branch("Key", &Key);
   InfoTree.Branch("Value", &Value);

   time_t CurrentTime = time(NULL);
   string StringTime = ctime(&CurrentTime);
   replace(StringTime.begin(), StringTime.end(), '\n', ' ');

   Key = "Version";                 Value = InfoString(Version);                 InfoTree.Fill();
   Key = "CurrentTime";             Value = InfoString(StringTime);              InfoTree.Fill();
   Key = "Input";                   Value = InfoString(InputFileNames);          InfoTree.Fill();
   Key = "Output";                  Value = InfoString(OutputFileName);          InfoTree.Fill();
   Key = "DoGenLevel";              Value = InfoString(DoGenLevel);              InfoTree.Fill();
   Key = "Fraction";                Value = InfoString(Fraction);                InfoTree.Fill();
   Key = "MinZPT";                  Value = InfoString(MinZPT);                  InfoTree.Fill();
   Key = "MinTrackPT";              Value = InfoString(MinTrackPT);              InfoTree.Fill();
   Key = "MinGenTrackPT";           Value = InfoString(MinGenTrackPT);           InfoTree.Fill();
   Key = "MinPFPT";                 Value = InfoString(MinPFPT);                 InfoTree.Fill();
   Key = "IsData";                  Value = InfoString(IsData);                  InfoTree.Fill();
   Key = "IsPP";                    Value = InfoString(IsPP);                    InfoTree.Fill();
   Key = "DoGenCorrelation";        Value = InfoString(DoGenCorrelation);        InfoTree.Fill();
   Key = "GenCorrelationCharged";   Value = InfoString(GenCorrelationCharged);   InfoTree.Fill();
   Key = "DoBackground";            Value = InfoString(DoBackground);            InfoTree.Fill();
   Key = "DoSumET";                 Value = InfoString(DoSumET);                 InfoTree.Fill();
   Key = "DoExtraAxes";             Value = InfoString(DoExtraAxes);             InfoTree.Fill();
   Key = "MuonVeto";                Value = InfoString(MuonVeto);                InfoTree.Fill();
   Key = "DoJet";                   Value = InfoString(DoJet);                   InfoTree.Fill();
   Key = "JECFiles";                Value = InfoString(JECFiles);                InfoTree.Fill();
   Key = "JetTreeName";             Value = InfoString(JetTreeName);             InfoTree.Fill();
   Key = "MinJetPT";                Value = InfoString(MinJetPT);                InfoTree.Fill();
   Key = "DoTrackEfficiency";       Value = InfoString(DoTrackEfficiency);       InfoTree.Fill();
   Key = "TrackEfficiencyPath";     Value = InfoString(TrackEfficiencyPath);     InfoTree.Fill();
   Key = "DoTrackResidual";         Value = InfoString(DoTrackResidual);         InfoTree.Fill();
   Key = "TrackResidualPath";       Value = InfoString(TrackResidualPath);       InfoTree.Fill();
   Key = "PFTreeName";              Value = InfoString(PFTreeName);              InfoTree.Fill();
   Key = "RhoTreeName";             Value = InfoString(RhoTreeName);             InfoTree.Fill();
   Key = "Background";              Value = InfoString(BackgroundFileNames);     InfoTree.Fill();
   Key = "VZTolerance";             Value = InfoString(VZTolerance);             InfoTree.Fill();
   Key = "HFShift";                 Value = InfoString(HFShift);                 InfoTree.Fill();
   Key = "Tolerance";               Value = InfoString(HFTolerance);             InfoTree.Fill();
   Key = "ToleranceFraction";       Value = InfoString(HFToleranceFraction);     InfoTree.Fill();
   Key = "HFCeiling";               Value = InfoString(HFCeiling);               InfoTree.Fill();
   Key = "Oversample";              Value = InfoString(Oversample);              InfoTree.Fill();

   TH2D H2D("H2D", "", 100, -6, 6, 100, -M_PI, M_PI);

   ZHadronMessenger MZHadron;
   MZHadron.SetBranch(&Tree);
   Tree.SetAlias("zP", "(zPt*cosh(zEta))");
   Tree.SetAlias("zPz", "(zPt*sinh(zEta))");
   Tree.SetAlias("zE", "sqrt(zP*zP+zMass*zMass)");
   Tree.SetAlias("zY", "(0.5*log((zE+zPz)/(zE-zPz)))");

   // Loop over signal files
   for(string InputFileName : InputFileNames)
   {
      MZHadron.Clear();

      // Get the input file
      TFile InputFile(InputFileName.c_str());

      // Setup all the messengers.  In the future we'll add more for triggers etc.
      HiEventTreeMessenger     MSignalEvent(InputFile);
      TrackTreeMessenger       MSignalTrackPP(InputFile);
      PbPbTrackTreeMessenger   MSignalTrack(InputFile);
      GenParticleTreeMessenger MSignalGen(InputFile);
      PFTreeMessenger          MSignalPF(InputFile, PFTreeName);
      MuTreeMessenger          MSignalMu(InputFile);
      SkimTreeMessenger        MSignalSkim(InputFile);
      TriggerTreeMessenger     MSignalTrigger(InputFile);
      JetTreeMessenger         MSignalJet(InputFile, JetTreeName);
      RhoTreeMessenger         MSignalRho(InputFile, RhoTreeName);

      // Start looping over events
      int EntryCount = MSignalEvent.GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);
      // Bar.SetStyle(6);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         // Progress bar stuff
         if(WithProgressBar && (EntryCount < 300 || (iE % (EntryCount / 250)) == 0))
         {
            Bar.Update(iE);
            Bar.Print();
         }

         TLorentzVector VGenZ, VGenMu1, VGenMu2;

         MSignalEvent.GetEntry(iE);
         MSignalGen.GetEntry(iE);
         if(IsPP == true)
            MSignalTrackPP.GetEntry(iE);
         else
            MSignalTrack.GetEntry(iE);
         MSignalMu.GetEntry(iE);
         MSignalSkim.GetEntry(iE);
         MSignalTrigger.GetEntry(iE);
         MSignalPF.GetEntry(iE);
         if(DoJet == true)
            MSignalJet.GetEntry(iE);
         MSignalRho.GetEntry(iE);

         if(IsPP == false && IsData == false && DoMCHiBinShift == true)   // PbPb MC, we shift 1.5% as per Kaya
         {
            MSignalEvent.hiBin = MSignalEvent.hiBin - MCHiBinShift;
            if(MSignalEvent.hiBin < 0)   // too central, skip
               continue;
         }

         MZHadron.Run   = MSignalEvent.Run;
         MZHadron.Lumi  = MSignalEvent.Lumi;
         MZHadron.Event = MSignalEvent.Event;
         MZHadron.hiBin = MSignalEvent.hiBin;
         if(IsPP == false && IsData == true)   // need hiBin shifts!
         {
            MZHadron.hiBinUp   = GetHiBin(MSignalEvent.hiHF, 1);
            MZHadron.hiBinDown = GetHiBin(MSignalEvent.hiHF, -1);
         }
         MZHadron.hiHF  = MSignalEvent.hiHF;
         MZHadron.NPU   = 0;
         if(MSignalEvent.npus->size() == 9)
            MZHadron.NPU = MSignalEvent.npus->at(5);
         else if(MSignalEvent.npus->size() > 1)
            MZHadron.NPU = MSignalEvent.npus->at(0);
         else
            MZHadron.NPU = 0;

         // Fill vertex information
         MZHadron.NVertex = 0;
         int BestVertex = -1;
         for(int i = 0; i < (IsPP ? MSignalTrackPP.nVtx : MSignalTrack.VX->size()); i++)
         {
            // TODO: Add vertex selections here

            if(IsPP == true && (BestVertex < 0 || MSignalTrackPP.sumPtVtx[i] > MSignalTrackPP.sumPtVtx[BestVertex]))
               BestVertex = i;
            if(IsPP == false && (BestVertex < 0 || MSignalTrack.VPTSum->at(i) > MSignalTrack.VPTSum->at(BestVertex)))
               BestVertex = i;

            MZHadron.NVertex = MZHadron.NVertex + 1;
         }
         
         if(BestVertex >= 0)
         {
            MZHadron.VX      = IsPP ? MSignalTrackPP.xVtx[BestVertex] : MSignalTrack.VX->at(BestVertex);
            MZHadron.VY      = IsPP ? MSignalTrackPP.yVtx[BestVertex] : MSignalTrack.VY->at(BestVertex);
            MZHadron.VZ      = IsPP ? MSignalTrackPP.zVtx[BestVertex] : MSignalTrack.VZ->at(BestVertex);
            MZHadron.VXError = IsPP ? MSignalTrackPP.xVtxErr[BestVertex] : MSignalTrack.VXError->at(BestVertex);
            MZHadron.VYError = IsPP ? MSignalTrackPP.yVtxErr[BestVertex] : MSignalTrack.VYError->at(BestVertex);
            MZHadron.VZError = IsPP ? MSignalTrackPP.zVtxErr[BestVertex] : MSignalTrack.VZError->at(BestVertex);

            if(IsData == false)
               MZHadron.VZWeight = IsPP ? GetVZWeightPP(MZHadron.VZ) : GetVZWeightPbPb(MZHadron.VZ);
            else
               MZHadron.VZWeight = 1;
         }

         // Do event selection and triggers
         if(IsPP == true)
         {
            if(IsData == true)
            {
               int pprimaryVertexFilter = MSignalSkim.PVFilter;
               int beamScrapingFilter = MSignalSkim.BeamScrapingFilter;
      
               // Event selection criteria
               //    see https://twiki.cern.ch/twiki/bin/viewauth/CMS/HIPhotonJe5TeVpp2017PbPb2018
               if(pprimaryVertexFilter == 0 || beamScrapingFilter == 0)
                  continue;
      
               //HLT trigger to select dimuon events, see Kaya's note: AN2019_143_v12, p.5
               int HLT_HIL2Mu12 = MSignalTrigger.CheckTriggerStartWith("HLT_HIL2Mu12");
               int HLT_HIL3Mu12 = MSignalTrigger.CheckTriggerStartWith("HLT_HIL3Mu12");
               if(HLT_HIL3Mu12 == 0 && HLT_HIL2Mu12 == 0)
                  continue;

               MZHadron.NCollWeight = 1;
            }
            else
               MZHadron.NCollWeight = 1;
         }
         else
         {
            if(IsData == true)
            {
               int pprimaryVertexFilter = MSignalSkim.PVFilter;
               int phfCoincFilter2Th4 = MSignalSkim.HFCoincidenceFilter2Th4;
               int pclusterCompatibilityFilter = MSignalSkim.ClusterCompatibilityFilter;
      
               // Event selection criteria
               //    see https://twiki.cern.ch/twiki/bin/viewauth/CMS/HIPhotonJe5TeVpp2017PbPb2018
               if(pprimaryVertexFilter == 0 || phfCoincFilter2Th4 == 0 || pclusterCompatibilityFilter == 0)
                  continue;
      
               //HLT trigger to select dimuon events, see Kaya's note: AN2019_143_v12, p.5
               int HLT_HIL3Mu12 = MSignalTrigger.CheckTriggerStartWith("HLT_HIL3Mu12");
               if(HLT_HIL3Mu12 == 0)
                  continue;

               MZHadron.NCollWeight = 1;
            }
            else
               MZHadron.NCollWeight = FindNColl(MSignalEvent.hiBin);
         }

         // Oversample if needed
         for(int iS = 0; iS < Oversample; iS++)
         {
            // Loop over gen muons
            if(DoGenLevel == true && MSignalMu.NGen > 1)
            {
               for(int igen1 = 0; igen1 < MSignalMu.NGen; igen1++)
               {
                  // We only want muon from Z's
                  if(MSignalMu.GenMom[igen1] != 23)
                     continue;
                  if(MSignalMu.GenPT[igen1] < 20)
                     continue;
                  if(fabs(MSignalMu.GenEta[igen1]) > 2.4)
                     continue;
   
                  VGenMu1.SetPtEtaPhiM(MSignalMu.GenPT[igen1],
                        MSignalMu.GenEta[igen1],
                        MSignalMu.GenPhi[igen1],
                        M_MU);
   
                  for(int igen2 = igen1 + 1; igen2 < MSignalMu.NGen; igen2++)
                  {
                     // We only want muon from Z's
                     if(MSignalMu.GenMom[igen2] != 23)
                        continue;
                     if(MSignalMu.GenPT[igen2] < 20)
                        continue;
                     if(fabs(MSignalMu.GenEta[igen2]) > 2.4)
                        continue;
   
                     VGenMu2.SetPtEtaPhiM(MSignalMu.GenPT[igen2],
                           MSignalMu.GenEta[igen2],
                           MSignalMu.GenPhi[igen2],
                           M_MU);
   
                     VGenZ = VGenMu1 + VGenMu2;

                     if(VGenZ.M() < 60 || VGenZ.M() > 120)
                        continue;
                     if(fabs(VGenZ.Rapidity()) > 2.4)
                        continue;

                     MZHadron.genZMass->push_back(VGenZ.M());
                     MZHadron.genZPt->push_back  (VGenZ.Pt());
                     MZHadron.genZPhi->push_back (VGenZ.Phi());
                     MZHadron.genZEta->push_back (VGenZ.Eta());
   
                     MZHadron.genMuPt1->push_back(MSignalMu.GenPT[igen1]);
                     MZHadron.genMuPt2->push_back(MSignalMu.GenPT[igen2]);
                     MZHadron.genMuEta1->push_back(MSignalMu.GenEta[igen1]);
                     MZHadron.genMuEta2->push_back(MSignalMu.GenEta[igen2]);
                     MZHadron.genMuPhi1->push_back(MSignalMu.GenPhi[igen1]);
                     MZHadron.genMuPhi2->push_back(MSignalMu.GenPhi[igen2]);
   
                     double genDeltaMuEta = MSignalMu.GenEta[igen1] - MSignalMu.GenEta[igen2];
                     double genDeltaMuPhi = PhiRangePositive(DeltaPhi(MSignalMu.GenPhi[igen1], MSignalMu.GenPhi[igen2]));
   
                     MZHadron.genMuDeta->push_back(genDeltaMuEta);
                     MZHadron.genMuDphi->push_back(genDeltaMuPhi);
                     MZHadron.genMuDR->push_back(sqrt(genDeltaMuEta * genDeltaMuEta + genDeltaMuPhi * genDeltaMuPhi));
   
                     double genDeltaPhiStar = tan((M_PI - genDeltaMuPhi) / 2)
                        * sqrt(1 - tanh(genDeltaMuEta / 2) * tanh(genDeltaMuEta / 2));
                     MZHadron.genMuDphiS->push_back(genDeltaPhiStar);
                  }
               }
            }
   
            // Loop over reco dimuon pairs
            //for(int ipair = 0; ipair < 1; ipair++)
            for(int ipair = 0; ipair < MSignalMu.NDi; ipair++)
            {
               //if(MSignalMu.NDi < 1) continue;
               // We want opposite-charge muons with some basic kinematic cuts
               if(MSignalMu.DiCharge1[ipair] == MSignalMu.DiCharge2[ipair])        continue;
               if(fabs(MSignalMu.DiEta1[ipair]) > 2.4)                             continue;
               if(fabs(MSignalMu.DiEta2[ipair]) > 2.4)                             continue;
               if(fabs(MSignalMu.DiPT1[ipair]) < 20)                               continue;
               if(fabs(MSignalMu.DiPT2[ipair]) < 20)                               continue;
               if(MSignalMu.DimuonPassTightCut(ipair) == false)                    continue;
               if(MSignalMu.DiMass[ipair] < 60 || MSignalMu.DiMass[ipair] > 120)   continue;
               
               TLorentzVector Mu1, Mu2;
               Mu1.SetPtEtaPhiM(MSignalMu.DiPT1[ipair], MSignalMu.DiEta1[ipair], MSignalMu.DiPhi1[ipair], M_MU);
               Mu2.SetPtEtaPhiM(MSignalMu.DiPT2[ipair], MSignalMu.DiEta2[ipair], MSignalMu.DiPhi2[ipair], M_MU);
               TLorentzVector Z = Mu1 + Mu2;
               if(fabs(Z.Rapidity()) > 2.4)
                  continue;

               MZHadron.zMass->push_back(MSignalMu.DiMass[ipair]);
               MZHadron.zEta->push_back(MSignalMu.DiEta[ipair]);
               MZHadron.zPhi->push_back(MSignalMu.DiPhi[ipair]);
               MZHadron.zPt->push_back(MSignalMu.DiPT[ipair]);
   
               MZHadron.muEta1->push_back(MSignalMu.DiEta1[ipair]);
               MZHadron.muEta2->push_back(MSignalMu.DiEta2[ipair]);
               MZHadron.muPhi1->push_back(MSignalMu.DiPhi1[ipair]);
               MZHadron.muPhi2->push_back(MSignalMu.DiPhi2[ipair]);
   
               MZHadron.muPt1->push_back(MSignalMu.DiPT1[ipair]);
               MZHadron.muPt2->push_back(MSignalMu.DiPT2[ipair]);
   
               double deltaMuEta = MSignalMu.DiEta1[ipair] - MSignalMu.DiEta2[ipair];
               double deltaMuPhi = PhiRangePositive(DeltaPhi(MSignalMu.DiPhi1[ipair], MSignalMu.DiPhi2[ipair]));
   
               MZHadron.muDeta->push_back(deltaMuEta);
               MZHadron.muDphi->push_back(deltaMuPhi);
               MZHadron.muDR->push_back(sqrt(deltaMuEta * deltaMuEta + deltaMuPhi * deltaMuPhi));
   
               double deltaPhiStar = tan((M_PI - deltaMuPhi) / 2) * sqrt(1 - tanh(deltaMuEta / 2) * tanh(deltaMuEta / 2));
   
               MZHadron.muDphiS->push_back(deltaPhiStar);
   
               NTuple.Fill(MSignalMu.DiMass[ipair], MSignalMu.DiPT[ipair], MSignalMu.DiEta[ipair], MSignalMu.DiPhi[ipair]);
            }

            MZHadron.SignalHF = DoGenCorrelation ? GetGenHFSum(&MSignalGen, MinGenTrackPT) : (DoSumET ? MSignalEvent.hiHF : GetHFSum(&MSignalPF, MinPFPT));
            MZHadron.SignalVZ = MSignalEvent.vz;

            // Z-track correlation
            bool GoodGenZ = MZHadron.genZPt->size() > 0 && (MZHadron.genZPt->at(0) > MinZPT);
            bool GoodRecoZ = MZHadron.zPt->size() > 0 && (MZHadron.zPt->at(0) > MinZPT);
            if((DoGenCorrelation == true && GoodGenZ == true) || (DoGenCorrelation == false && GoodRecoZ == true))
            {
               // Decide whether to use signal or background for tracks
               EventIndex Location;
               if(DoBackground == true)
               {
                  // find the background event location based on HF
                  double SignalHF = MZHadron.SignalHF;
                  double LowerHF = min(SignalHF - HFTolerance, SignalHF * (1 - HFToleranceFraction)) - HFShift;
                  double HigherHF = max(SignalHF + HFTolerance, SignalHF * (1 + HFToleranceFraction)) - HFShift;

                  if(SignalHF < HFShift)
                     continue;

                  if(HFCeiling >= 0 && LowerHF > HFCeiling)
                     LowerHF = HFCeiling;

                  // cout << endl;
                  // cout << SignalHF << " " << LowerHF << " " << HigherHF << " " << HFShift << endl;

                  // cout << MSignalEvent.hiHF << " " << SignalHF << endl;

                  int LowerIndex = FindFirstAbove(BackgroundIndices, LowerHF);
                  int HigherIndex = FindFirstAbove(BackgroundIndices, HigherHF);

                  vector<int> GoodIndices;
                  GoodIndices.reserve(HigherIndex - LowerIndex + 1);
                  for(int i = LowerIndex; i <= HigherIndex; i++)
                     if(fabs(BackgroundIndices[i].VZ - MZHadron.SignalVZ) < VZTolerance)
                        GoodIndices.push_back(i);

                  Assert(HigherIndex > LowerIndex,
                     Form("Warning!  Too few events matched.  Please enlarge tolerance or add more background files.  %f < %f - %f < %f",
                        LowerHF, SignalHF, HFShift, HigherHF));
                  Assert(GoodIndices.size() > 0,
                     Form("Warning!  Too few events matched.  Please enlarge tolerance or add more background files.  %f < %f - %f < %f, %f",
                        LowerHF, SignalHF, HFShift, HigherHF, MZHadron.SignalVZ));

                  // int Index = LowerIndex + rand() % (HigherIndex - LowerIndex);
                  int Index = rand() % GoodIndices.size();

                  Location = BackgroundIndices[GoodIndices[Index]];

                  // cout << "Index inside the array" << Index << endl;
                  // cout << "From index " << Location.File << " " << Location.Event << " " << Location.HF << endl;
                  // cout << "Track tree pointer " << MBackgroundTrack[Location.File]->Tree << endl;
                  // MBackgroundEvent[Location.File]->GetEntry(Location.Event);
                  // cout << "From background event HF = " << MBackgroundEvent[Location.File]->hiHF << endl;

                  MZHadron.BackgroundHF = Location.HF;

                  // cout << Location.HF << endl;

                  if(DoGenCorrelation == true)
                     MBackgroundGen[Location.File]->GetEntry(Location.Event);
                  else
                  {
                     if(IsPP == true)
                        MBackgroundTrackPP[Location.File]->GetEntry(Location.Event);
                     else
                        MBackgroundTrack[Location.File]->GetEntry(Location.Event);
                  }
                  
                  // MBackgroundPF[Location.File]->GetEntry(Location.Event);
               }
               PbPbTrackTreeMessenger *MTrack = DoBackground ? MBackgroundTrack[Location.File] : &MSignalTrack;
               TrackTreeMessenger *MTrackPP   = DoBackground ? MBackgroundTrackPP[Location.File] : &MSignalTrackPP;
               GenParticleTreeMessenger *MGen = DoBackground ? MBackgroundGen[Location.File] : &MSignalGen;
               PFTreeMessenger *MPF           = &MSignalPF;

               // Loop over tracks and build the correlation function
               int NTrack = DoGenCorrelation ? MGen->Mult : (IsPP ? MTrackPP->nTrk : MTrack->TrackPT->size());
               for(int itrack = 0; itrack < NTrack; itrack++)
               {
                  if(IsData == false && IsPP == false){
                     if(MGen->PT->at(itrack) < MinGenTrackPT )
                        continue;
                  }

                  if(DoGenCorrelation == false)   // track selection on reco
                  {
                     if(IsPP == true)
                     {
                        if(DoAlternateTrackSelection == false && MTrackPP->PassZHadron2022Cut(itrack) == false)
                           continue;
                        if(DoAlternateTrackSelection == true && AlternateTrackSelection == 0 && MTrackPP->PassZHadron2022Cut(itrack) == false)
                           continue;
                        if(DoAlternateTrackSelection == true && AlternateTrackSelection == 1 && MTrackPP->PassZHadron2022CutLoose(itrack) == false)
                           continue;
                        if(DoAlternateTrackSelection == true && AlternateTrackSelection == 2 && MTrackPP->PassZHadron2022CutTight(itrack) == false)
                           continue;
                     }
                     if(IsPP == false)
                     {
                        if(DoAlternateTrackSelection == false && MTrack->PassZHadron2022Cut(itrack) == false)
                           continue;
                        if(DoAlternateTrackSelection == true && AlternateTrackSelection == 0 && MTrack->PassZHadron2022Cut(itrack) == false)
                           continue;
                        if(DoAlternateTrackSelection == true && AlternateTrackSelection == 1 && MTrack->PassZHadron2022CutLoose(itrack) == false)
                           continue;
                        if(DoAlternateTrackSelection == true && AlternateTrackSelection == 2 && MTrack->PassZHadron2022CutTight(itrack) == false)
                           continue;
                     }
                     // if(IsPP == false)
                     // {
                     //    if(DoBackground == true && IsData == true)
                     //    {
                     //       if(MTrack->PassZHadron2022CutNoVZ(itrack) == false)
                     //          continue;
                     //    }
                     //    else
                     //    {
                     //       if(MTrack->PassZHadron2022Cut(itrack) == false)
                     //          continue;
                     //    }
                     // }
                     if((IsPP ? MTrackPP->trkPt[itrack] : MTrack->TrackPT->at(itrack)) < MinTrackPT)
                        continue;
                  }

                  if(DoGenCorrelation == true)
                  {
                     if(MGen->PT->at(itrack) < MinTrackPT)
                        continue;
                     if(MGen->Eta->at(itrack) < -2.4)
                        continue;
                     if(MGen->Eta->at(itrack) > +2.4)
                        continue;
                     if(MGen->DaughterCount->at(itrack) > 0)
                        continue;
                     if(GenCorrelationCharged == true && MGen->Charge->at(itrack) == 0)
                        continue;
                  }
              
                  double TrackEta = DoGenCorrelation ? MGen->Eta->at(itrack) : (IsPP ? MTrackPP->trkEta[itrack] : MTrack->TrackEta->at(itrack));
                  double TrackPhi = DoGenCorrelation ? MGen->Phi->at(itrack) : (IsPP ? MTrackPP->trkPhi[itrack] : MTrack->TrackPhi->at(itrack));
                  double TrackPT  = DoGenCorrelation ? MGen->PT->at(itrack) : (IsPP ? MTrackPP->trkPt[itrack] : MTrack->TrackPT->at(itrack));
                  int TrackCharge = DoGenCorrelation ? MGen->Charge->at(itrack) : (IsPP ? MTrackPP->trkCharge[itrack] : MTrack->TrackCharge->at(itrack));
                  int SubEvent    = DoGenCorrelation ? (MGen->SubEvent->at(itrack) + DoBackground) : (IsPP ? 0 : DoBackground);

                  double Mu1Eta = DoGenCorrelation ? MZHadron.genMuEta1->at(0) : MZHadron.muEta1->at(0);
                  double Mu1Phi = DoGenCorrelation ? MZHadron.genMuPhi1->at(0) : MZHadron.muPhi1->at(0);
                  double Mu2Eta = DoGenCorrelation ? MZHadron.genMuEta2->at(0) : MZHadron.muEta2->at(0);
                  double Mu2Phi = DoGenCorrelation ? MZHadron.genMuPhi2->at(0) : MZHadron.muPhi2->at(0);

                  double DeltaEtaMu1 = TrackEta - Mu1Eta;
                  double DeltaEtaMu2 = TrackEta - Mu2Eta;
                  double DeltaPhiMu1 = DeltaPhi(TrackPhi, Mu1Phi);
                  double DeltaPhiMu2 = DeltaPhi(TrackPhi, Mu2Phi);

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  bool MuTagged = false;
                  if(DeltaRMu1 < MuonVeto)   MuTagged = true;
                  if(DeltaRMu2 < MuonVeto)   MuTagged = true;

                  double ZEta = DoGenCorrelation ? MZHadron.genZEta->at(0) : MZHadron.zEta->at(0);
                  double ZPhi = DoGenCorrelation ? MZHadron.genZPhi->at(0) : MZHadron.zPhi->at(0);

                  double deltaEta = TrackEta - ZEta;
                  double deltaPhi = DeltaPhi(TrackPhi, ZPhi);

                  H2D.Fill(+deltaEta, +deltaPhi, 0.25);
                  H2D.Fill(-deltaEta, +deltaPhi, 0.25);
                  H2D.Fill(-deltaEta, -deltaPhi, 0.25);
                  H2D.Fill(+deltaEta, -deltaPhi, 0.25);

                  MZHadron.trackDphi->push_back(deltaPhi);
                  MZHadron.trackDeta->push_back(deltaEta);
                  MZHadron.trackPt->push_back(TrackPT);
                  MZHadron.trackMuTagged->push_back(MuTagged);
                  MZHadron.trackMuDR->push_back(min(DeltaRMu1, DeltaRMu2));
                  MZHadron.subevent->push_back(SubEvent);

                  double TrackCorrection = 1;
                  if(DoTrackEfficiency == true && DoGenCorrelation == false)
                  {
                     if(IsPP == true)
                        TrackCorrection = TrackEfficiencyPP->getCorrection(TrackPT, TrackEta);
                     else
                        TrackCorrection = TrackEfficiencyPbPb->getCorrection(TrackPT, TrackEta, MZHadron.hiBin);
                  }
                  double TrackResidualCorrection = 1;
                  if(DoTrackResidual == true && DoGenCorrelation == false)
                  {
                     TrackResidualCorrection = TrackResidual.GetCorrectionFactor(TrackPT, TrackEta, TrackPhi, MZHadron.hiBin);
                  }
                  MZHadron.trackWeight->push_back(TrackCorrection);
                  MZHadron.trackResidualWeight->push_back(TrackResidualCorrection);
               }
            }

            if(GoodRecoZ == true && DoJet == true)
            {
               JetRecord MaxJet12, MaxJet34, MaxJet56, MaxJet78;

               vector<JetRecord> Jets;
               for(int iJ = 0; iJ < MSignalJet.JetCount; iJ++)
               {
                  JEC.SetJetEta(MSignalJet.JetEta[iJ]);
                  JEC.SetJetPhi(MSignalJet.JetPhi[iJ]);
                  JEC.SetJetPT(MSignalJet.JetRawPT[iJ]);
                  JEC.SetJetArea(0.5);
                  JEC.SetRho(0);
                  
                  double JetEta = MSignalJet.JetEta[iJ];
                  double JetPhi = MSignalJet.JetPhi[iJ];
                  double JetPT  = JEC.GetCorrectedPT();
                  double RefEta = MSignalJet.RefEta[iJ];
                  double RefPhi = MSignalJet.RefPhi[iJ];
                  double RefPT  = MSignalJet.RefPT[iJ];

                  if(JetEta < -2 || JetEta > 2)
                     continue;
                  if(JetPT < MinJetPT)   // Skip small jets
                     continue;

                  double Mu1Eta = MZHadron.muEta1->at(0);
                  double Mu1Phi = MZHadron.muPhi1->at(0);
                  double Mu2Eta = MZHadron.muEta2->at(0);
                  double Mu2Phi = MZHadron.muPhi2->at(0);

                  double DeltaEtaMu1 = JetEta - Mu1Eta;
                  double DeltaEtaMu2 = JetEta - Mu2Eta;
                  double DeltaPhiMu1 = DeltaPhi(JetPhi, Mu1Phi);
                  double DeltaPhiMu2 = DeltaPhi(JetPhi, Mu2Phi);

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  bool MuTagged = false;
                  if(DeltaRMu1 < MuonVeto)   MuTagged = true;
                  if(DeltaRMu2 < MuonVeto)   MuTagged = true;

                  double ZEta = MZHadron.zEta->at(0);
                  double ZPhi = MZHadron.zPhi->at(0);

                  double deltaEta = JetEta - ZEta;
                  double deltaPhi = DeltaPhi(JetPhi, ZPhi);
                  double refDeltaEta = RefEta - ZEta;
                  double refDeltaPhi = DeltaPhi(RefPhi, ZPhi);

                  JetRecord ThisJet(JetPT, MSignalJet.JetRawPT[iJ], deltaEta, deltaPhi, MuTagged, RefPT, refDeltaEta, refDeltaPhi);

                  Jets.push_back(ThisJet);

                  if(fabs(deltaPhi) > M_PI * 1 / 2 && ThisJet > MaxJet12)   MaxJet12 = ThisJet;
                  if(fabs(deltaPhi) > M_PI * 3 / 4 && ThisJet > MaxJet34)   MaxJet34 = ThisJet;
                  if(fabs(deltaPhi) > M_PI * 5 / 6 && ThisJet > MaxJet56)   MaxJet56 = ThisJet;
                  if(fabs(deltaPhi) > M_PI * 7 / 8 && ThisJet > MaxJet78)   MaxJet78 = ThisJet;
               }
               sort(Jets.begin(), Jets.end(), greater<JetRecord>());

               for(int iJ = 0; iJ < (int)Jets.size(); iJ++)
               {
                  MZHadron.jetPt->push_back(Jets[iJ].JetPT);
                  MZHadron.jetDeta->push_back(Jets[iJ].JetDEta);
                  MZHadron.jetDphi->push_back(Jets[iJ].JetDPhi);
                  MZHadron.jetMuTagged->push_back(Jets[iJ].JetMuTagged);
                  MZHadron.jetRefPt->push_back(Jets[iJ].RefPT);
                  MZHadron.jetRefDeta->push_back(Jets[iJ].RefDEta);
                  MZHadron.jetRefDphi->push_back(Jets[iJ].RefDPhi);
               }

               MZHadron.maxOppositeJet12Pt   = MaxJet12.JetPT;
               MZHadron.maxOppositeJet12DEta = MaxJet12.JetDEta;
               MZHadron.maxOppositeJet12DPhi = MaxJet12.JetDPhi;
               MZHadron.maxOppositeJet34Pt   = MaxJet34.JetPT;
               MZHadron.maxOppositeJet34DEta = MaxJet34.JetDEta;
               MZHadron.maxOppositeJet34DPhi = MaxJet34.JetDPhi;
               MZHadron.maxOppositeJet56Pt   = MaxJet56.JetPT;
               MZHadron.maxOppositeJet56DEta = MaxJet56.JetDEta;
               MZHadron.maxOppositeJet56DPhi = MaxJet56.JetDPhi;
               MZHadron.maxOppositeJet78Pt   = MaxJet78.JetPT;
               MZHadron.maxOppositeJet78DEta = MaxJet78.JetDEta;
               MZHadron.maxOppositeJet78DPhi = MaxJet78.JetDPhi;

               // Now gen jets if there are any
               if(DoGenLevel == true)
               {
                  for(int iJ = 0; iJ < MSignalJet.GenCount; iJ++)
                  {
                     if(MSignalJet.GenEta[iJ] < -2 || MSignalJet.GenEta[iJ] > 2)
                        continue;
                     if(MSignalJet.GenPT[iJ] < MinJetPT - 5)   // reserve some margins for gen jets just in case
                        continue;

                     MZHadron.genJetPt->push_back(MSignalJet.GenPT[iJ]);
                     MZHadron.genJetEta->push_back(MSignalJet.GenEta[iJ]);
                     MZHadron.genJetPhi->push_back(MSignalJet.GenPhi[iJ]);
                  }
               }
            }

            if(GoodRecoZ == true && DoExtraAxes == true)
            {
               PFTreeMessenger *MPF = &MSignalPF;

               int MaxOppositeIndex = -1;
               double MaxOppositeDEta = 0;
               double MaxOppositeDPhi = 0;
               int MaxIndex = -1;
               double MaxDEta = 0;
               double MaxDPhi = 0;

               // Do CS PF
               vector<double> CSPFEta;
               vector<double> CSPFPhi;
               vector<double> CSPFPT;
               for(int iPF = 0; iPF < MPF->ID->size(); iPF++)
               {
                  CSPFEta.push_back(MPF->Eta->at(iPF));
                  CSPFPhi.push_back(MPF->Phi->at(iPF));
                  CSPFPT.push_back(MPF->PT->at(iPF));
               }
               if(DoCS == true)
                  ConstituentSubtraction(CSPFEta, CSPFPhi, CSPFPT, MSignalRho.EtaMin, MSignalRho.EtaMax, MSignalRho.Rho, 0.5);

               // Loop over PF candidates to find WTA
               vector<double> OppositePFEta;
               vector<double> OppositePFPhi;
               vector<double> OppositePFPT;
               vector<double> MoreOppositePFEta;
               vector<double> MoreOppositePFPhi;
               vector<double> MoreOppositePFPT;
               for(int iPF = 0; iPF < MPF->ID->size(); iPF++)
               {
                  if(MPF->Eta->at(iPF) < -2.4 || MPF->Eta->at(iPF) > +2.4)   // don't use forward region
                     continue;

                  // cout << iPF << " " << MPF->ID->size() << endl;

                  double DeltaEtaMu1 = MPF->Eta->at(iPF) - MZHadron.muEta1->at(0);
                  double DeltaEtaMu2 = MPF->Eta->at(iPF) - MZHadron.muEta2->at(0);
                  double DeltaPhiMu1 = DeltaPhi(MPF->Phi->at(iPF), MZHadron.muPhi1->at(0));
                  double DeltaPhiMu2 = DeltaPhi(MPF->Phi->at(iPF), MZHadron.muPhi2->at(0));

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  if(DeltaRMu1 < MuonVeto)   continue;
                  if(DeltaRMu2 < MuonVeto)   continue;

                  double deltaPhi = DeltaPhi(MPF->Phi->at(iPF), MZHadron.zPhi->at(0));
                  double deltaEta = MPF->Eta->at(iPF) - MZHadron.zEta->at(0);

                  if(fabs(deltaPhi) > M_PI / 2)
                  {
                     if(MaxOppositeIndex < 0 || MPF->PT->at(iPF) > MPF->PT->at(MaxOppositeIndex))
                     {
                        MaxOppositeIndex = iPF;
                        MaxOppositeDEta = deltaEta;
                        MaxOppositeDPhi = deltaPhi;
                     }
                  }

                  if(fabs(deltaPhi) > M_PI / 2)
                  {
                     OppositePFEta.push_back(deltaEta);
                     OppositePFPhi.push_back(deltaPhi);
                     OppositePFPT.push_back(MPF->PT->at(iPF));
                  }

                  if(fabs(deltaPhi) > 3 * M_PI / 4)
                  {
                     MoreOppositePFEta.push_back(deltaEta);
                     MoreOppositePFPhi.push_back(deltaPhi);
                     MoreOppositePFPT.push_back(MPF->PT->at(iPF));
                  }

                  if(MaxIndex < 0 || MPF->PT->at(iPF) > MPF->PT->at(MaxIndex))
                  {
                     MaxIndex = iPF;
                     MaxDEta = deltaEta;
                     MaxDPhi = deltaPhi;
                  }
               }

               // Loop over CS PF candidates to find WTA
               vector<double> OppositeCSPFEta;
               vector<double> OppositeCSPFPhi;
               vector<double> OppositeCSPFPT;
               for(int iPF = 0; iPF < CSPFEta.size(); iPF++)
               {
                  if(CSPFEta[iPF] < -2.4 || CSPFEta[iPF] > +2.4)   // don't use forward region
                     continue;

                  // cout << iPF << " " << MPF->ID->size() << endl;

                  double DeltaEtaMu1 = CSPFEta[iPF] - MZHadron.muEta1->at(0);
                  double DeltaEtaMu2 = CSPFEta[iPF] - MZHadron.muEta2->at(0);
                  double DeltaPhiMu1 = DeltaPhi(CSPFPhi[iPF], MZHadron.muPhi1->at(0));
                  double DeltaPhiMu2 = DeltaPhi(CSPFPhi[iPF], MZHadron.muPhi2->at(0));

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  if(DeltaRMu1 < MuonVeto)   continue;
                  if(DeltaRMu2 < MuonVeto)   continue;

                  double deltaPhi = DeltaPhi(CSPFPhi[iPF], MZHadron.zPhi->at(0));
                  double deltaEta = CSPFEta[iPF] - MZHadron.zEta->at(0);

                  if(fabs(deltaPhi) > M_PI / 2)
                  {
                     OppositeCSPFEta.push_back(deltaEta);
                     OppositeCSPFPhi.push_back(deltaPhi);
                     OppositeCSPFPT.push_back(CSPFPT[iPF]);
                  }
               }

               // Loop over tracks to find Charged WTA
               vector<double> OppositeTrackEta;
               vector<double> OppositeTrackPhi;
               vector<double> OppositeTrackPT;
               vector<double> MoreOppositeTrackEta;
               vector<double> MoreOppositeTrackPhi;
               vector<double> MoreOppositeTrackPT;
               vector<double> OppositeHardTrackEta;
               vector<double> OppositeHardTrackPhi;
               vector<double> OppositeHardTrackPT;
               
               int NTrack = IsPP ? MSignalTrackPP.nTrk : MSignalTrack.TrackPT->size();
               for(int iTrack = 0; iTrack < NTrack; iTrack++)
               {
                  //if(IsData == false && IsPP == false){
                  //   if(MGen->PT->at(itrack) < MinGenTrackPT )
                  //      continue;
                  //}

                  if(IsPP == true)
                  {
                     if(DoAlternateTrackSelection == false && MSignalTrackPP.PassZHadron2022Cut(iTrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 0 && MSignalTrackPP.PassZHadron2022Cut(iTrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 1 && MSignalTrackPP.PassZHadron2022CutLoose(iTrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 2 && MSignalTrackPP.PassZHadron2022CutTight(iTrack) == false)
                        continue;
                  }
                  if(IsPP == false)
                  {
                     if(DoAlternateTrackSelection == false && MSignalTrack.PassZHadron2022Cut(iTrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 0 && MSignalTrack.PassZHadron2022Cut(iTrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 1 && MSignalTrack.PassZHadron2022CutLoose(iTrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 2 && MSignalTrack.PassZHadron2022CutTight(iTrack) == false)
                        continue;
                  }

                  double TrackPT = IsPP ? MSignalTrackPP.trkPt[iTrack] : MSignalTrack.TrackPT->at(iTrack);
                  double TrackEta = IsPP ? MSignalTrackPP.trkEta[iTrack] : MSignalTrack.TrackEta->at(iTrack);
                  double TrackPhi = IsPP ? MSignalTrackPP.trkPhi[iTrack] : MSignalTrack.TrackPhi->at(iTrack);

                  double DeltaEtaMu1 = TrackEta - MZHadron.muEta1->at(0);
                  double DeltaEtaMu2 = TrackEta - MZHadron.muEta2->at(0);
                  double DeltaPhiMu1 = DeltaPhi(TrackPhi, MZHadron.muPhi1->at(0));
                  double DeltaPhiMu2 = DeltaPhi(TrackPhi, MZHadron.muPhi2->at(0));

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  if(DeltaRMu1 < MuonVeto)   continue;
                  if(DeltaRMu2 < MuonVeto)   continue;

                  double deltaPhi = DeltaPhi(TrackPhi, MZHadron.zPhi->at(0));
                  double deltaEta = TrackEta - MZHadron.zEta->at(0);

                  if(fabs(deltaPhi) > M_PI / 2)
                  {
                     OppositeTrackEta.push_back(deltaEta);
                     OppositeTrackPhi.push_back(deltaPhi);
                     OppositeTrackPT.push_back(TrackPT);
                  }
                  
                  if(fabs(deltaPhi) > M_PI / 2 && TrackPT > 5)
                  {
                     OppositeHardTrackEta.push_back(deltaEta);
                     OppositeHardTrackPhi.push_back(deltaPhi);
                     OppositeHardTrackPT.push_back(TrackPT);
                  }

                  if(fabs(deltaPhi) > 3 * M_PI / 4)
                  {
                     MoreOppositeTrackEta.push_back(deltaEta);
                     MoreOppositeTrackPhi.push_back(deltaPhi);
                     MoreOppositeTrackPT.push_back(TrackPT);
                  }
               }

               pair<double, double> WTA            = WTAAxis(OppositePFEta, OppositePFPhi, OppositePFPT);
               pair<double, double> WTAMore        = WTAAxis(MoreOppositePFEta, MoreOppositePFPhi, MoreOppositePFPT);
               pair<double, double> CSWTA          = WTAAxis(OppositeCSPFEta, OppositeCSPFPhi, OppositeCSPFPT);
               pair<double, double> ChargedWTA     = WTAAxis(OppositeTrackEta, OppositeTrackPhi, OppositeTrackPT);
               pair<double, double> ChargedWTAMore = WTAAxis(MoreOppositeTrackEta, MoreOppositeTrackPhi, MoreOppositeTrackPT);
               pair<double, double> HardChargedWTA = WTAAxis(OppositeHardTrackEta, OppositeHardTrackPhi, OppositeHardTrackPT);
               
               MZHadron.maxOppositeDEta               = MaxOppositeDEta;
               MZHadron.maxOppositeDPhi               = MaxOppositeDPhi;
               MZHadron.maxDEta                       = MaxDEta;
               MZHadron.maxDPhi                       = MaxDPhi;
               MZHadron.maxOppositeWTADEta            = WTA.first;
               MZHadron.maxOppositeWTADPhi            = WTA.second;
               MZHadron.maxMoreOppositeWTADEta        = WTAMore.first;
               MZHadron.maxMoreOppositeWTADPhi        = WTAMore.second;
               MZHadron.maxOppositeCSWTADEta          = CSWTA.first;
               MZHadron.maxOppositeCSWTADPhi          = CSWTA.second;
               MZHadron.maxOppositeChargedWTADEta     = ChargedWTA.first;
               MZHadron.maxOppositeChargedWTADPhi     = ChargedWTA.second;
               MZHadron.maxMoreOppositeChargedWTADEta = ChargedWTAMore.first;
               MZHadron.maxMoreOppositeChargedWTADPhi = ChargedWTAMore.second;
               MZHadron.maxOppositeHardChargedWTADEta = HardChargedWTA.first;
               MZHadron.maxOppositeHardChargedWTADPhi = HardChargedWTA.second;
            }

            MZHadron.ZWeight = 1;
            if(DoGenCorrelation == false && MZHadron.zPt->size() > 0)
            {
               TLorentzVector Z;
               Z.SetPtEtaPhiM(MZHadron.zPt->at(0), MZHadron.zEta->at(0), MZHadron.zPhi->at(0), MZHadron.zMass->at(0));
               if(IsPP == false)
               {
                  if(IsData == false)
                     MZHadron.ZWeight = GetZWeightPbPbMC(Z.Pt(), Z.Rapidity(), MZHadron.hiBin);
                  else
                  {
                     MZHadron.ZWeight = GetZWeightPbPbDataTrigger(Z.Pt(), Z.Rapidity(), MZHadron.hiBin);
                     
                     double Mu1Eta = MZHadron.muEta1->at(0);
                     double Mu1PT = MZHadron.muPt1->at(0);
                     double Mu2Eta = MZHadron.muEta1->at(0);
                     double Mu2PT = MZHadron.muPt1->at(0);
                     double Centrality = MZHadron.hiBin * 0.5;

                     MZHadron.ExtraZWeight[0] =
                        tnp_weight_glbPFtrk_pbpb(Mu1Eta, Centrality, -1)
                        / tnp_weight_glbPFtrk_pbpb(Mu1Eta, Centrality, 0)
                        * tnp_weight_glbPFtrk_pbpb(Mu2Eta, Centrality, -1)
                        / tnp_weight_glbPFtrk_pbpb(Mu2Eta, Centrality, 0);
                     MZHadron.ExtraZWeight[1] =
                        tnp_weight_glbPFtrk_pbpb(Mu1Eta, Centrality, -2)
                        / tnp_weight_glbPFtrk_pbpb(Mu1Eta, Centrality, 0)
                        * tnp_weight_glbPFtrk_pbpb(Mu2Eta, Centrality, -2)
                        / tnp_weight_glbPFtrk_pbpb(Mu2Eta, Centrality, 0);
                     MZHadron.ExtraZWeight[2] =
                        tnp_weight_muid_pbpb(Mu1Eta, -1)
                        / tnp_weight_muid_pbpb(Mu1Eta, 0)
                        * tnp_weight_muid_pbpb(Mu2Eta, -1)
                        / tnp_weight_muid_pbpb(Mu2Eta, 0);
                     MZHadron.ExtraZWeight[3] =
                        tnp_weight_muid_pbpb(Mu1Eta, -2)
                        / tnp_weight_muid_pbpb(Mu1Eta, 0)
                        * tnp_weight_muid_pbpb(Mu2Eta, -2)
                        / tnp_weight_muid_pbpb(Mu2Eta, 0);
                     // MZHadron.ExtraZWeight[4] =
                     //    tnp_weight_trig_pbpb(Mu1PT, Mu1Eta, Centrality, -1)
                     //    / tnp_weight_trig_pbpb(Mu1PT, Mu1Eta, Centrality, 0)
                     //    * tnp_weight_trig_pbpb(Mu2PT, Mu2Eta, Centrality, -1)
                     //    / tnp_weight_trig_pbpb(Mu2PT, Mu2Eta, Centrality, 0);
                     // MZHadron.ExtraZWeight[5] =
                     //    tnp_weight_trig_pbpb(Mu1PT, Mu1Eta, Centrality, -2)
                     //    / tnp_weight_trig_pbpb(Mu1PT, Mu1Eta, Centrality, 0)
                     //    * tnp_weight_trig_pbpb(Mu2PT, Mu2Eta, Centrality, -2)
                     //    / tnp_weight_trig_pbpb(Mu2PT, Mu2Eta, Centrality, 0);
                     MZHadron.ExtraZWeight[4] =
                        tnp_weight_trig_double_pbpb(Mu1PT, Mu1Eta, Centrality, Mu2PT, Mu2Eta, Centrality, -1)
                        / tnp_weight_trig_double_pbpb(Mu1PT, Mu1Eta, Centrality, Mu2PT, Mu2Eta, Centrality, 0);
                     MZHadron.ExtraZWeight[5] =
                        tnp_weight_trig_double_pbpb(Mu1PT, Mu1Eta, Centrality, Mu2PT, Mu2Eta, Centrality, -2)
                        / tnp_weight_trig_double_pbpb(Mu1PT, Mu1Eta, Centrality, Mu2PT, Mu2Eta, Centrality, 0);

                     MZHadron.ExtraZWeight[6] =
                        tnp_weight_glbPFtrk_pbpb(Mu1Eta, Centrality, 1)
                        / tnp_weight_glbPFtrk_pbpb(Mu1Eta, Centrality, 0)
                        * tnp_weight_glbPFtrk_pbpb(Mu2Eta, Centrality, 1)
                        / tnp_weight_glbPFtrk_pbpb(Mu2Eta, Centrality, 0);
                     MZHadron.ExtraZWeight[7] =
                        tnp_weight_glbPFtrk_pbpb(Mu1Eta, Centrality, 2)
                        / tnp_weight_glbPFtrk_pbpb(Mu1Eta, Centrality, 0)
                        * tnp_weight_glbPFtrk_pbpb(Mu2Eta, Centrality, 2)
                        / tnp_weight_glbPFtrk_pbpb(Mu2Eta, Centrality, 0);
                     MZHadron.ExtraZWeight[8] =
                        tnp_weight_muid_pbpb(Mu1Eta, 1)
                        / tnp_weight_muid_pbpb(Mu1Eta, 0)
                        * tnp_weight_muid_pbpb(Mu2Eta, 1)
                        / tnp_weight_muid_pbpb(Mu2Eta, 0);
                     MZHadron.ExtraZWeight[9] =
                        tnp_weight_muid_pbpb(Mu1Eta, 2)
                        / tnp_weight_muid_pbpb(Mu1Eta, 0)
                        * tnp_weight_muid_pbpb(Mu2Eta, 2)
                        / tnp_weight_muid_pbpb(Mu2Eta, 0);
                     // MZHadron.ExtraZWeight[10] =
                     //    tnp_weight_trig_pbpb(Mu1PT, Mu1Eta, Centrality, 1)
                     //    / tnp_weight_trig_pbpb(Mu1PT, Mu1Eta, Centrality, 0)
                     //    * tnp_weight_trig_pbpb(Mu2PT, Mu2Eta, Centrality, 1)
                     //    / tnp_weight_trig_pbpb(Mu2PT, Mu2Eta, Centrality, 0);
                     // MZHadron.ExtraZWeight[11] =
                     //    tnp_weight_trig_pbpb(Mu1PT, Mu1Eta, Centrality, 2)
                     //    / tnp_weight_trig_pbpb(Mu1PT, Mu1Eta, Centrality, 0)
                     //    * tnp_weight_trig_pbpb(Mu2PT, Mu2Eta, Centrality, 2)
                     //    / tnp_weight_trig_pbpb(Mu2PT, Mu2Eta, Centrality, 0);
                     MZHadron.ExtraZWeight[10] =
                        tnp_weight_trig_double_pbpb(Mu1PT, Mu1Eta, Centrality, Mu2PT, Mu2Eta, Centrality, 1)
                        / tnp_weight_trig_double_pbpb(Mu1PT, Mu1Eta, Centrality, Mu2PT, Mu2Eta, Centrality, 0);
                     MZHadron.ExtraZWeight[11] =
                        tnp_weight_trig_double_pbpb(Mu1PT, Mu1Eta, Centrality, Mu2PT, Mu2Eta, Centrality, 2)
                        / tnp_weight_trig_double_pbpb(Mu1PT, Mu1Eta, Centrality, Mu2PT, Mu2Eta, Centrality, 0);
                  }
               }
               else
               {
                  if(IsData == false)
                     MZHadron.ZWeight = GetZWeightPPMC(Z.Pt(), Z.Rapidity());
                  else
                  {
                     MZHadron.ZWeight = GetZWeightPPDataTrigger(Z.Pt(), Z.Rapidity());
                     // Extra Z weight for systematics

                     double Mu1Eta = MZHadron.muEta1->at(0);
                     double Mu1PT = MZHadron.muPt1->at(0);
                     double Mu2Eta = MZHadron.muEta1->at(0);
                     double Mu2PT = MZHadron.muPt1->at(0);

                     MZHadron.ExtraZWeight[0] =
                        tnp_weight_TightID_pp(Mu1Eta, 1)
                        / tnp_weight_TightID_pp(Mu1Eta, 0)
                        * tnp_weight_TightID_pp(Mu2Eta, 1)
                        / tnp_weight_TightID_pp(Mu2Eta, 0);
                     MZHadron.ExtraZWeight[1] =
                        tnp_weight_TightID_pp(Mu1Eta, -1)
                        / tnp_weight_TightID_pp(Mu1Eta, 0)
                        * tnp_weight_TightID_pp(Mu2Eta, -1)
                        / tnp_weight_TightID_pp(Mu2Eta, 0);
                     // MZHadron.ExtraZWeight[2] =
                     //    tnp_weight_L3Mu12_pp(Mu1Eta, 1)
                     //    / tnp_weight_L3Mu12_pp(Mu1Eta, 0)
                     //    * tnp_weight_L3Mu12_pp(Mu2Eta, 1)
                     //    / tnp_weight_L3Mu12_pp(Mu2Eta, 0);
                     // MZHadron.ExtraZWeight[3] =
                     //    tnp_weight_L3Mu12_pp(Mu1Eta, -1)
                     //    / tnp_weight_L3Mu12_pp(Mu1Eta, 0)
                     //    * tnp_weight_L3Mu12_pp(Mu2Eta, -1)
                     //    / tnp_weight_L3Mu12_pp(Mu2Eta, 0);
                     MZHadron.ExtraZWeight[2] =
                        tnp_weight_L3Mu12_double_pp(Mu1Eta, Mu2Eta, 1)
                        / tnp_weight_L3Mu12_double_pp(Mu1Eta, Mu2Eta, 0);
                     MZHadron.ExtraZWeight[3] =
                        tnp_weight_L3Mu12_double_pp(Mu1Eta, Mu2Eta, -1)
                        / tnp_weight_L3Mu12_double_pp(Mu1Eta, Mu2Eta, 0);

                     for(int i = 4; i < 12; i++)
                        MZHadron.ExtraZWeight[i] = 1;
                  }
               }
            }

            MZHadron.FillEntry();
         }
      }

      if(WithProgressBar){
         Bar.Update(EntryCount);
         Bar.Print();
         Bar.PrintLine();
      }

      InputFile.Close();
   }

   OutputFile.cd();
   H2D.Write();
   NTuple.Write();
   Tree.Write();
   InfoTree.Write();

   // gROOT->GetListOfFiles()->Remove(&OutputFile);
   OutputFile.Close();

   if(DoBackground == true)
   {
      for(TFile *F : BackgroundFiles)
      {
         if(F == nullptr)
            continue;
         F->Close();
         delete F;
      }

      for(HiEventTreeMessenger *M : MBackgroundEvent)
         if(M != nullptr)
            delete M;

      for(PbPbTrackTreeMessenger *M : MBackgroundTrack)
         if(M != nullptr)
            delete M;

      for(PFTreeMessenger *M : MBackgroundPF)
         if(M != nullptr)
            delete M;
      
      for(RhoTreeMessenger *M : MBackgroundRho)
         if(M != nullptr)
            delete M;
   }

   if(DoTrackEfficiency == true)
   {
      if(TrackEfficiencyPP != nullptr)
         delete TrackEfficiencyPP;
      if(TrackEfficiencyPbPb != nullptr)
         delete TrackEfficiencyPbPb;
   }

   return 0;
}

int FindFirstAbove(vector<EventIndex> &Indices, double X)
{
   if(X < Indices[0].HF)
      return 0;

   if(X >= Indices[Indices.size()-1].HF)
      return Indices.size();

   int Low = 0;
   int High = Indices.size();

   while(High - Low > 1)
   {
      int Middle = (High + Low) / 2;
      if(X < Indices[Middle].HF)
         High = Middle;
      else
         Low = Middle;
   }

   return Low;
}

double GetHFSum(PFTreeMessenger *M, double MinPFPT)
{
   if(M == nullptr)
      return -1;
   if(M->Tree == nullptr)
      return -1;

   double Sum = 0;
   for(int iPF = 0; iPF < M->ID->size(); iPF++)
      if(fabs(M->Eta->at(iPF)) > 3 && fabs(M->Eta->at(iPF)) < 5 && M->PT->at(iPF) > MinPFPT )
         Sum = Sum + M->E->at(iPF);

   // cout << Sum << endl;

   return Sum;
}

double GetGenHFSum(GenParticleTreeMessenger *M, double MinGenTrackPT)
{
   if(M == nullptr)
      return -1;
   if(M->Tree == nullptr)
      return -1;

   double Sum = 0;
   for(int iGen = 0; iGen < M->Mult; iGen++)
   {
      if(fabs(M->Eta->at(iGen)) < 3)
         continue;
      if(fabs(M->Eta->at(iGen)) > 5)
         continue;
      if(fabs(M->PT->at(iGen)) < MinGenTrackPT)
         continue;
      if(M->DaughterCount->at(iGen) > 0)
         continue;
      Sum = Sum + M->PT->at(iGen) * cosh(M->Eta->at(iGen));
   }

   return Sum;
}


