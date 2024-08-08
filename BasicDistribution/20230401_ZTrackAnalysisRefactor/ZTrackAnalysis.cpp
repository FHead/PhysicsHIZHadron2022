#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TNamed.h"
#include "TTree.h"
#include "TH1D.h"
#include "TDirectory.h"
#include "TH2D.h"
#include "TChain.h"

#include "CommonFunctions.h"
#include "CommandLine.h"
#include "ProgressBar.h"

struct Configuration;
int main(int argc, char *argv[]);

struct Configuration
{
public:
   int BinCount;
   double ZPTMin;
   double ZPTMax;
   double CentMin;
   double CentMax;
   double TrackPTMin;
   double TrackPTMax;
public:
   Configuration() {}
   Configuration(int bincount, double zptl, double zpth, double centl, double centh, double trackptl, double trackpth)
   {
      BinCount = bincount;
      ZPTMin = zptl;
      ZPTMax = zpth;
      CentMin = centl;
      CentMax = centh;
      TrackPTMin = trackptl;
      TrackPTMax = trackpth;
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputBase      = CL.Get("InputBase", "/eos/cms/store/group/phys_heavyions/pchou/OutputMC_v16/");
   string OutputFileName = CL.Get("Output", "Plots.root");
   double Fraction       = CL.GetDouble("Fraction", 1.00);
   bool IgnoreCentrality = CL.GetBool("IgnoreCentrality", false);
   bool OnlyZeroSub      = CL.GetBool("OnlyZeroSub", false);
   bool OnlyZeroNPU      = CL.GetBool("OnlyZeroNPU", false);
   bool OnlyOneSub       = CL.GetBool("OnlyOneSub", false);
   bool NoZeroSub        = CL.GetBool("NoZeroSub", false);
   bool NoOneSub         = CL.GetBool("NoOneSub", false);
   bool DoGenCorrelation = CL.GetBool("DoGenCorrelation", false);
   bool DoSingleFile     = CL.GetBool("DoSingleFile", false);
   
   // Note: fields are bin count, Z min, Z max, Cent. min, Cent. max, Track min, Track max
   vector<Configuration> C;


   //C.push_back(Configuration(40, 40,  200,  0, 10, 1, 2));

   
   C.push_back(Configuration(40, 40,  200,  0, 30, 1, 1000));
   C.push_back(Configuration(40, 40,  200,  0, 10, 1, 1000));
   C.push_back(Configuration(40, 40,  200, 10, 30, 1, 1000));
   C.push_back(Configuration(40, 40,  200, 30, 50, 1, 1000));
   C.push_back(Configuration(40, 40,  200, 50, 90, 1, 1000));
   C.push_back(Configuration(40, 40,  200, 30, 90, 1, 1000));
   C.push_back(Configuration(40, 40,  200,  0, 90, 1, 1000));


   C.push_back(Configuration(40, 40,  200,  0, 10, 1, 2));
   C.push_back(Configuration(40, 40,  200, 10, 30, 1, 2));
   C.push_back(Configuration(40, 40,  200, 30, 50, 1, 2));
   C.push_back(Configuration(40, 40,  200, 50, 90, 1, 2));
   C.push_back(Configuration(40, 40,  200,  0, 90, 1, 2));

   C.push_back(Configuration(40, 40,  200,  0, 100, 1, 2));
   C.push_back(Configuration(40, 40,  200,  0, 100, 2, 4));
   C.push_back(Configuration(40, 40,  200,  0, 100, 4, 10));

   //C.push_back(Configuration(40, 40,  200,  0, 30, 1, 2));
   //C.push_back(Configuration(40, 40,  200, 30, 90, 1, 2));

   C.push_back(Configuration(40, 40,  200,  0, 10, 2, 4));
   C.push_back(Configuration(40, 40,  200, 10, 30, 2, 4));
   C.push_back(Configuration(40, 40,  200, 30, 50, 2, 4));
   C.push_back(Configuration(40, 40,  200, 50, 90, 2, 4));
   C.push_back(Configuration(40, 40,  200,  0, 90, 2, 4));
   //C.push_back(Configuration(40, 40,  200,  0, 30, 2, 4));
   //C.push_back(Configuration(40, 40,  200, 30, 90, 2, 4));

   C.push_back(Configuration(40, 40,  200,  0, 10, 4, 10));
   C.push_back(Configuration(40, 40,  200, 10, 30, 4, 10));
   C.push_back(Configuration(40, 40,  200, 30, 50, 4, 10));
   C.push_back(Configuration(40, 40,  200, 50, 90, 4, 10));
   C.push_back(Configuration(40, 40,  200,  0, 90, 4, 10));

   
   vector<TDirectory *>     Folder;
   vector<double>           TotalEventCount;
   vector<TH1D *>           HTotalEventCount;
   vector<double>           TotalZEventCount;
   vector<TH1D *>           HTotalZEventCount;
   vector<double>           EventCount;
   vector<TH1D *>           HEventCount;
   vector<double>           GenEventCount;
   vector<TH1D *>           HGenEventCount;
   vector<TH1D *>           HZPT;
   vector<TH1D *>           HZEta;
   vector<TH1D *>           HZY;
   vector<TH1D *>           HZPhi;
   vector<TH2D *>           HZEtaPhi;
   vector<TH1D *>           HGenZEta;
   vector<TH1D *>           HGenZPhi;
   vector<TH2D *>           HGenZEtaPhi;
   vector<TH1D *>           HZMass;
   vector<TH1D *>           HTrackPT;
   vector<TH1D *>           HTrackEta;
   vector<TH1D *>           HTrackPhi;
   vector<TH2D *>           HTrackEtaPhi;
   vector<TH1D *>           HGenTrackEta;
   vector<TH1D *>           HGenTrackPhi;
   vector<TH2D *>           HGenTrackEtaPhi;
   vector<TH1D *>           HTrackMuonDEta;
   vector<TH1D *>           HTrackMuonDPhi;
   vector<TH2D *>           HTrackMuonDEtaDPhi;
   vector<TH2D *>           HTrackMuonDEtaDPhiZoom;
   vector<TH1D *>           HTrackMuonDR;
   vector<TH1D *>           HTrackMuonDRZoom;
   vector<TH1D *>           HEta;
   vector<TH1D *>           HPhi;
   vector<TH2D *>           HEtaPhi;
   vector<TH1D *>           HMaxHadronEta;
   vector<TH1D *>           HMaxHadronPhi;
   vector<TH2D *>           HMaxHadronEtaPhi;
   vector<TH2D *>           HZMaxHadronEtaPhi;
   vector<TH1D *>           HMaxOppositeHadronEta;
   vector<TH1D *>           HMaxOppositeHadronPhi;
   vector<TH2D *>           HMaxOppositeHadronEtaPhi;
   vector<TH2D *>           HZMaxOppositeHadronEtaPhi;
   vector<TH1D *>           HWTAEta;
   vector<TH1D *>           HWTAPhi;
   vector<TH2D *>           HWTAEtaPhi;
   vector<TH2D *>           HZWTAEtaPhi;
   vector<TH1D *>           HWTAMoreEta;
   vector<TH1D *>           HWTAMorePhi;
   vector<TH2D *>           HWTAMoreEtaPhi;
   vector<TH2D *>           HZWTAMoreEtaPhi;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   for(int iC = 0; iC < C.size(); iC++)
   {
      string FolderName =
         Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",
            C[iC].ZPTMin, C[iC].ZPTMax,
            C[iC].CentMin, C[iC].CentMax,
            C[iC].TrackPTMin, C[iC].TrackPTMax);
      replace(FolderName.begin(), FolderName.end(), '.', 'p');

      Folder.push_back(OutputFile.mkdir(FolderName.c_str()));
      
      Folder[iC]->cd();
      TotalEventCount.push_back(0);
      HTotalEventCount.push_back(new TH1D("HTotalEventCount", "", 1, 0, 1));
      TotalZEventCount.push_back(0);
      HTotalZEventCount.push_back(new TH1D("HTotalZEventCount", "", 1, 0, 1));
      EventCount.push_back(0);
      HEventCount.push_back(new TH1D("HEventCount", "", 1, 0, 1));
      GenEventCount.push_back(0);
      HGenEventCount.push_back(new TH1D("HGenEventCount", "", 1, 0, 1));
      
      HZPT.push_back(new TH1D("HZPT", "Z candidate PT", 100, 0, 200));
      HZY.push_back(new TH1D("HZY", "Z candidate y", 100, -3.2, 3.2));
      HZEta.push_back(new TH1D("HZEta", "Z candidate eta", 100, -3.2, 3.2));
      HZPhi.push_back(new TH1D("HZPhi", "Z candidate phi", 100, -M_PI, M_PI));
      HZEtaPhi.push_back(new TH2D("HZEtaPhi", "Z candidate eta phi", 100, -3.2, 3.2, 100, -M_PI, M_PI));
      HGenZEta.push_back(new TH1D("HGenZEta", "GEN Z eta", 100, -3.2, 3.2));
      HGenZPhi.push_back(new TH1D("HGenZPhi", "GEN Z phi", 100, -M_PI, M_PI));
      HGenZEtaPhi.push_back(new TH2D("HGenZEtaPhi", "GEN Z eta phi", 100, -3.2, 3.2, 100, -M_PI, M_PI));
      HZMass.push_back(new TH1D("HZMass", "Z candidate mass", 100, 0, 150));
      HTrackPT.push_back(new TH1D("HTrackPT", "Track PT", 100, 0, 200));
      HTrackEta.push_back(new TH1D("HTrackEta", "Track eta", 100, -3.2, 3.2));
      HTrackPhi.push_back(new TH1D("HTrackPhi", "Track phi", 100, -M_PI, M_PI));
      HTrackEtaPhi.push_back(new TH2D("HTrackEtaPhi", "Track eta phi", 100, -3.2, 3.2, 100, -M_PI, M_PI));
      HGenTrackEta.push_back(new TH1D("HGenTrackEta", "GEN Track eta", 100, -3.2, 3.2));
      HGenTrackPhi.push_back(new TH1D("HGenTrackPhi", "GEN Track phi", 100, -M_PI, M_PI));
      HGenTrackEtaPhi.push_back(new TH2D("HGenTrackEtaPhi", "GEN Track eta phi", 100, -3.2, 3.2, 100, -M_PI, M_PI));
      
      HTrackMuonDEta.push_back(new TH1D("HTrackMuonDEta", "track-muon delta eta", 100, -3.2, 3.2));
      HTrackMuonDPhi.push_back(new TH1D("HTrackMuonDPhi", "track-muon delta phi", 100, -M_PI, M_PI));
      HTrackMuonDEtaDPhi.push_back(new TH2D("HTrackMuonDEtaDPhi", "track-muon", 100, -3.2, 3.2, 100, -M_PI, M_PI));
      HTrackMuonDEtaDPhiZoom.push_back(new TH2D("HTrackMuonDEtaDPhiZoom", "track-muon", 100, -0.01, 0.01, 100, -0.01, 0.01));
      HTrackMuonDR.push_back(new TH1D("HTrackMuonDR", "track-muon delta R", 100, 0, 3.2));
      HTrackMuonDRZoom.push_back(new TH1D("HTrackMuonDRZoom", "track-muon delta R", 100, 0, 0.1));

      HEta.push_back(new TH1D("HEta", "", C[iC].BinCount, 0, 3.2));
      HPhi.push_back(new TH1D("HPhi", "", C[iC].BinCount, -M_PI * 0.5, M_PI * 1.5));
      HEtaPhi.push_back(new TH2D("HEtaPhi", "", 150, -3.2, 3.2, 150, -M_PI * 0.5, M_PI * 1.5));
      
      HMaxHadronEta.push_back(new TH1D("HMaxHadronEta", "", C[iC].BinCount, 0, 3.2));
      HMaxHadronPhi.push_back(new TH1D("HMaxHadronPhi", "", C[iC].BinCount, -M_PI * 0.5, M_PI * 1.5));
      HMaxHadronEtaPhi.push_back(new TH2D("HMaxHadronEtaPhi", "", 150, -3.2, 3.2, 150, -M_PI * 0.5, M_PI * 1.5));
      HZMaxHadronEtaPhi.push_back(new TH2D("HZMaxHadronEtaPhi", "Z-axis correlation", 150, -3.2, 3.2, 150, -M_PI * 0.5, M_PI * 1.5));
      
      HMaxOppositeHadronEta.push_back(new TH1D("HMaxOppositeHadronEta", "", C[iC].BinCount, 0, 3.2));
      HMaxOppositeHadronPhi.push_back(new TH1D("HMaxOppositeHadronPhi", "", C[iC].BinCount, -M_PI * 0.5, M_PI * 1.5));
      HMaxOppositeHadronEtaPhi.push_back(new TH2D("HMaxOppositeHadronEtaPhi", "", 150, -3.2, 3.2, 150, -M_PI * 0.5, M_PI * 1.5));
      HZMaxOppositeHadronEtaPhi.push_back(new TH2D("HZMaxOppositeHadronEtaPhi", "Z-axis correlation", 150, -3.2, 3.2, 150, -M_PI * 0.5, M_PI * 1.5));
      
      HWTAEta.push_back(new TH1D("HWTAEta", "", C[iC].BinCount, 0, 3.2));
      HWTAPhi.push_back(new TH1D("HWTAPhi", "", C[iC].BinCount, -M_PI * 0.5, M_PI * 1.5));
      HWTAEtaPhi.push_back(new TH2D("HWTAEtaPhi", "", 150, -3.2, 3.2, 150, -M_PI * 0.5, M_PI * 1.5));
      HZWTAEtaPhi.push_back(new TH2D("HZWTAEtaPhi", "Z-axis correlation", 150, -3.2, 3.2, 150, -M_PI * 0.5, M_PI * 1.5));
      
      HWTAMoreEta.push_back(new TH1D("HWTAMoreEta", "", C[iC].BinCount, 0, 3.2));
      HWTAMorePhi.push_back(new TH1D("HWTAMorePhi", "", C[iC].BinCount, -M_PI * 0.5, M_PI * 1.5));
      HWTAMoreEtaPhi.push_back(new TH2D("HWTAMoreEtaPhi", "", 150, -3.2, 3.2, 150, -M_PI * 0.5, M_PI * 1.5));
      HZWTAMoreEtaPhi.push_back(new TH2D("HZWTAMoreEtaPhi", "Z-axis correlation", 150, -3.2, 3.2, 150, -M_PI * 0.5, M_PI * 1.5));
   }
  
   TChain *Tree = new TChain("Tree");
   if(DoSingleFile==false)
      Tree->Add((InputBase + "/*.root?#Tree").c_str());
   else
      Tree->Add((InputBase + "?#Tree").c_str());
 
   int HiBin;
   int NPU;
   vector<double> *ZMass       = nullptr;
   vector<double> *ZPT         = nullptr;
   vector<double> *ZEta        = nullptr;
   vector<double> *ZPhi        = nullptr;
   vector<double> *Mu1PT       = nullptr;
   vector<double> *Mu1Eta      = nullptr;
   vector<double> *Mu1Phi      = nullptr;
   vector<double> *Mu2PT       = nullptr;
   vector<double> *Mu2Eta      = nullptr;
   vector<double> *Mu2Phi      = nullptr;
   vector<double> *TrackPT     = nullptr;
   vector<double> *TrackDPhi   = nullptr;
   vector<double> *TrackDEta   = nullptr;
   vector<bool> *TrackMuTagged = nullptr;
   vector<int> *subevent       = nullptr;

   vector<double> *genZMass    = nullptr;
   vector<double> *genZPt      = nullptr;
   vector<double> *genZEta     = nullptr;
   vector<double> *genZPhi     = nullptr;

   vector<double> *genMu1Eta   = nullptr;
   vector<double> *genMu2Eta   = nullptr;
   vector<double> *genMu1Phi   = nullptr;
   vector<double> *genMu2Phi   = nullptr;

   double maxOppositeDEta;
   double maxOppositeDPhi;
   double maxDEta;
   double maxDPhi;
   double maxOppositeWTADEta;
   double maxOppositeWTADPhi;
   double maxMoreOppositeWTADEta;
   double maxMoreOppositeWTADPhi;

   float NCollWeight;
   float ZWeight, VZWeight;
   vector<double> *trackWeight = nullptr;
   vector<double> *trackResidualWeight = nullptr;

   Tree->SetBranchAddress("hiBin",                  &HiBin);
   Tree->SetBranchAddress("NPU",                    &NPU);
   Tree->SetBranchAddress("zMass",                  &ZMass);
   Tree->SetBranchAddress("zPt",                    &ZPT);
   Tree->SetBranchAddress("zEta",                   &ZEta);
   Tree->SetBranchAddress("zPhi",                   &ZPhi);
   Tree->SetBranchAddress("muPt1",                  &Mu1PT);
   Tree->SetBranchAddress("muEta1",                 &Mu1Eta);
   Tree->SetBranchAddress("muPhi1",                 &Mu1Phi);
   Tree->SetBranchAddress("muPt2",                  &Mu2PT);
   Tree->SetBranchAddress("muEta2",                 &Mu2Eta);
   Tree->SetBranchAddress("muPhi2",                 &Mu2Phi);
   Tree->SetBranchAddress("trackPt",                &TrackPT);
   Tree->SetBranchAddress("trackDeta",              &TrackDEta);
   Tree->SetBranchAddress("trackDphi",              &TrackDPhi);

   Tree->SetBranchAddress("NCollWeight",            &NCollWeight);
   Tree->SetBranchAddress("ZWeight",                &ZWeight);
   Tree->SetBranchAddress("VZWeight",               &VZWeight);
   

   Tree->SetBranchAddress("trackWeight",            &trackWeight);
   Tree->SetBranchAddress("trackResidualWeight",    &trackResidualWeight);

   Tree->SetBranchAddress("subevent",               &subevent);

   if(Tree->GetBranch("trackMuTagged"))          Tree->SetBranchAddress("trackMuTagged",          &TrackMuTagged);
   if(Tree->GetBranch("maxOppositeDEta"))        Tree->SetBranchAddress("maxOppositeDEta",        &maxOppositeDEta);
   if(Tree->GetBranch("maxOppositeDPhi"))        Tree->SetBranchAddress("maxOppositeDPhi",        &maxOppositeDPhi);
   if(Tree->GetBranch("maxDEta"))                Tree->SetBranchAddress("maxDEta",                &maxDEta);
   if(Tree->GetBranch("maxDPhi"))                Tree->SetBranchAddress("maxDPhi",                &maxDPhi);
   if(Tree->GetBranch("maxOppositeWTADEta"))     Tree->SetBranchAddress("maxOppositeWTADEta",     &maxOppositeWTADEta);
   if(Tree->GetBranch("maxOppositeWTADPhi"))     Tree->SetBranchAddress("maxOppositeWTADPhi",     &maxOppositeWTADPhi);
   if(Tree->GetBranch("maxMoreOppositeWTADEta")) Tree->SetBranchAddress("maxMoreOppositeWTADEta", &maxMoreOppositeWTADEta);
   if(Tree->GetBranch("maxMoreOppositeWTADPhi")) Tree->SetBranchAddress("maxMoreOppositeWTADPhi", &maxMoreOppositeWTADPhi);

   if(Tree->GetBranch("genZEta"))  Tree->SetBranchAddress("genZEta",  &genZEta);
   if(Tree->GetBranch("genZPhi"))  Tree->SetBranchAddress("genZPhi",  &genZPhi);
   if(Tree->GetBranch("genZMass")) Tree->SetBranchAddress("genZMass", &genZMass);
   if(Tree->GetBranch("genZPt"))   Tree->SetBranchAddress("genZPt",   &genZPt);
   if(Tree->GetBranch("genMuEta1"))   Tree->SetBranchAddress("genMuEta1",   &genMu1Eta);
   if(Tree->GetBranch("genMuEta2"))   Tree->SetBranchAddress("genMuEta2",   &genMu2Eta);
   if(Tree->GetBranch("genMuPhi1"))   Tree->SetBranchAddress("genMuPhi1",   &genMu1Phi);
   if(Tree->GetBranch("genMuPhi2"))   Tree->SetBranchAddress("genMuPhi2",   &genMu2Phi);

   int EntryCount = Tree->GetEntries() * Fraction;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);

   //std::cout<<"TrackPT, TrackEta, TrackPhi, NCollWeight, trackWeight, trackResidualWeight, ZWeight, zPt, ZEta, ZMass"<<std::endl;
            
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      Tree->GetEntry(iE);

      //if(OnlyZeroSub == true && DoGenCorrelation == false && NPU != 0) continue;
      if(OnlyZeroNPU == true && NPU != 0) continue;

      for(int iC = 0; iC < (int)C.size(); iC++)
      {
         bool ZMassRange = false;
         if(DoGenCorrelation == false && ZMass != nullptr && ZMass->size() > 0 && ZMass->at(0) > 60)
            ZMassRange = true;

         if(DoGenCorrelation == true && genZMass != nullptr && genZMass->size() > 0){
            if(genZMass->at(0) > 60) ZMassRange = true;
         }

         bool ZPTRange = false;
         if(DoGenCorrelation == false && ZPT != nullptr && ZPT->size() > 0 && ZPT->at(0) > C[iC].ZPTMin && ZPT->at(0) <= C[iC].ZPTMax)
            ZPTRange = true;

         if(DoGenCorrelation == true && genZPt != nullptr && genZPt->size() > 0){
            if (genZPt->at(0) > C[iC].ZPTMin && genZPt->at(0) <= C[iC].ZPTMax) ZPTRange = true;
         }

         bool CentRange = false;
         if(HiBin >= C[iC].CentMin * 2 && HiBin < C[iC].CentMax * 2)
            CentRange = true;
         if(IgnoreCentrality == true)
            CentRange = true;

         TotalEventCount[iC] = TotalEventCount[iC] + NCollWeight*ZWeight*VZWeight;
         HTotalEventCount[iC]->Fill(0., NCollWeight*ZWeight*VZWeight);

         // If we know that the Z candidate is not in range, no need to loop over tracks!
         // Saves a tiny bit of time
         if(!(ZMassRange && ZPTRange && CentRange))
            continue;

         bool SomethingPassed = false;

         double ZEta_0, ZPhi_0, ZMass_0, ZPT_0;
         double Mu1Eta_0, Mu2Eta_0, Mu1Phi_0, Mu2Phi_0;

         if(DoGenCorrelation == true){
            ZEta_0 = genZEta->at(0); ZPhi_0 = genZPhi->at(0); ZMass_0 = genZMass->at(0); ZPT_0 = genZPt->at(0);
            Mu1Eta_0 = genMu1Eta->at(0); Mu2Eta_0 = genMu2Eta->at(0); 
            Mu1Phi_0 = genMu1Phi->at(0); Mu2Phi_0 = genMu2Phi->at(0); 
         }else{
            ZEta_0 = ZEta->at(0); ZPhi_0 = ZPhi->at(0); ZMass_0 = ZMass->at(0); ZPT_0 = ZPT->at(0);
            Mu1Eta_0 = Mu1Eta->at(0); Mu2Eta_0 = Mu2Eta->at(0); 
            Mu1Phi_0 = Mu1Phi->at(0); Mu2Phi_0 = Mu2Phi->at(0); 
         }

         int NTrack = 0;
         if(TrackPT != nullptr)
            NTrack = TrackPT->size();
         for(int iT = 0; iT < NTrack; iT++)
         {
            if(OnlyZeroSub == true && DoGenCorrelation == true && subevent->at(iT) != 0) continue;
            if(OnlyOneSub == true && DoGenCorrelation == true && subevent->at(iT) != 1) continue;
            if(NoZeroSub == true && DoGenCorrelation == true && subevent->at(iT) == 0) continue;
            if(NoOneSub == true && DoGenCorrelation == true && subevent->at(iT) == 1) continue;

            bool TrackPTRange = false;
            if(TrackPT->at(iT) > C[iC].TrackPTMin && TrackPT->at(iT) < C[iC].TrackPTMax)
               TrackPTRange = true;

            bool TrackNotCloseToMuon = true;
            if(TrackMuTagged != nullptr && TrackMuTagged->at(iT) == true)
               TrackNotCloseToMuon = false;

            bool PassEvent = ZMassRange && ZPTRange && CentRange;
            bool PassEverything = PassEvent && TrackPTRange && TrackNotCloseToMuon;

            double weight = (trackWeight->at(iT))*(trackResidualWeight->at(iT))*NCollWeight*ZWeight*VZWeight;
            //double weight = NCollWeight;
            //double weight = trackWeight->at(iT);

            double DEtaToMax             = TrackDEta->at(iT) - maxDEta;
            double DPhiToMax             = DeltaPhi(TrackDPhi->at(iT), maxDPhi);
            double DEtaToMaxOpposite     = TrackDEta->at(iT) - maxOppositeDEta;
            double DPhiToMaxOpposite     = DeltaPhi(TrackDPhi->at(iT), maxOppositeDPhi);
            double DEtaToOppositeWTA     = TrackDEta->at(iT) - maxOppositeWTADEta;
            double DPhiToOppositeWTA     = DeltaPhi(TrackDPhi->at(iT), maxOppositeWTADPhi);
            double DEtaToMoreOppositeWTA = TrackDEta->at(iT) - maxMoreOppositeWTADEta;
            double DPhiToMoreOppositeWTA = DeltaPhi(TrackDPhi->at(iT), maxMoreOppositeWTADPhi);

            // cout << TrackDEta->at(iT) << " " << Mu1Eta->at(0) << " " << ZEta->at(0) << endl;

            double DEtaToMu1             = TrackDEta->at(iT) + ZEta_0 - Mu1Eta_0;
            double DPhiToMu1             = PhiRangeSymmetric(TrackDPhi->at(iT) + ZPhi_0 - Mu1Phi_0);
            double DEtaToMu2             = TrackDEta->at(iT) + ZEta_0 - Mu2Eta_0;
            double DPhiToMu2             = PhiRangeSymmetric(TrackDPhi->at(iT) + ZPhi_0 - Mu2Phi_0);

            double DRToMu1               = sqrt(DEtaToMu1 * DEtaToMu1 + DPhiToMu1 * DPhiToMu1);
            double DRToMu2               = sqrt(DEtaToMu2 * DEtaToMu2 + DPhiToMu2 * DPhiToMu2);

            if(PassEvent)
               SomethingPassed = true;
            if(PassEvent && TrackPTRange)
            {
               HTrackMuonDEta[iC]->Fill(DEtaToMu1, weight);
               HTrackMuonDEta[iC]->Fill(DEtaToMu2, weight);
               HTrackMuonDPhi[iC]->Fill(DPhiToMu1, weight);
               HTrackMuonDPhi[iC]->Fill(DPhiToMu2, weight);
               HTrackMuonDEtaDPhi[iC]->Fill(DEtaToMu1, DPhiToMu1, weight);
               HTrackMuonDEtaDPhi[iC]->Fill(DEtaToMu2, DPhiToMu2, weight);
               HTrackMuonDEtaDPhiZoom[iC]->Fill(DEtaToMu1, DPhiToMu1, weight);
               HTrackMuonDEtaDPhiZoom[iC]->Fill(DEtaToMu2, DPhiToMu2, weight);
               HTrackMuonDR[iC]->Fill(DRToMu1, weight);
               HTrackMuonDR[iC]->Fill(DRToMu2, weight);
               HTrackMuonDRZoom[iC]->Fill(DRToMu1, weight);
               HTrackMuonDRZoom[iC]->Fill(DRToMu2, weight);
            }
            if(PassEverything)
            {
               HTrackPT[iC]->Fill(TrackPT->at(iT), weight);
               HTrackEta[iC]->Fill(TrackDEta->at(iT) + ZEta_0, weight);
               HTrackPhi[iC]->Fill(PhiRangeSymmetric(TrackDPhi->at(iT) + ZPhi_0), weight);
               HTrackEtaPhi[iC]->Fill(TrackDEta->at(iT) + ZEta_0, PhiRangeSymmetric(TrackDPhi->at(iT) + ZPhi_0), weight);
               
               //std::cout<<TrackPT->at(iT)<<", "<<TrackDEta->at(iT) + ZEta_0<<", "<<PhiRangeSymmetric(TrackDPhi->at(iT) + ZPhi_0);
               //std::cout<<", "<<NCollWeight<<", "<<trackWeight->at(iT)<<", "<<trackResidualWeight->at(iT)<<", "<<ZWeight<<", "<<ZPT_0<<", "<<ZEta_0<<", "<<ZMass_0<<std::endl;
            
               if(genZEta->size() > 0){
                  HGenTrackEta[iC]->Fill(TrackDEta->at(iT) + genZEta->at(0), weight);
                  HGenTrackPhi[iC]->Fill(PhiRangeSymmetric(TrackDPhi->at(iT) + genZPhi->at(0)), weight);
                  HGenTrackEtaPhi[iC]->Fill(TrackDEta->at(iT) + genZEta->at(0), PhiRangeSymmetric(TrackDPhi->at(iT) + genZPhi->at(0)), weight);
               }

               HEta[iC]->Fill(TrackDEta->at(iT), weight);
               HPhi[iC]->Fill(PhiRangeCorrelation(+TrackDPhi->at(iT)), 0.5*weight);
               HPhi[iC]->Fill(PhiRangeCorrelation(-TrackDPhi->at(iT)), 0.5*weight);

               HEtaPhi[iC]->Fill(+TrackDEta->at(iT), PhiRangeCorrelation(+TrackDPhi->at(iT)), 0.25*weight);
               HEtaPhi[iC]->Fill(+TrackDEta->at(iT), PhiRangeCorrelation(-TrackDPhi->at(iT)), 0.25*weight);
               HEtaPhi[iC]->Fill(-TrackDEta->at(iT), PhiRangeCorrelation(+TrackDPhi->at(iT)), 0.25*weight);
               HEtaPhi[iC]->Fill(-TrackDEta->at(iT), PhiRangeCorrelation(-TrackDPhi->at(iT)), 0.25*weight);
               
               if(fabs(maxDEta + ZEta_0)<M_PI/2){
                  HMaxHadronEta[iC]->Fill(DEtaToMax, weight);
                  HMaxHadronPhi[iC]->Fill(PhiRangeCorrelation(+DPhiToMax), 0.5*weight);
                  HMaxHadronPhi[iC]->Fill(PhiRangeCorrelation(-DPhiToMax), 0.5*weight);
               
                  HMaxHadronEtaPhi[iC]->Fill(+DEtaToMax, PhiRangeCorrelation(+DPhiToMax), 0.25*weight);
                  HMaxHadronEtaPhi[iC]->Fill(+DEtaToMax, PhiRangeCorrelation(-DPhiToMax), 0.25*weight);
                  HMaxHadronEtaPhi[iC]->Fill(-DEtaToMax, PhiRangeCorrelation(+DPhiToMax), 0.25*weight);
                  HMaxHadronEtaPhi[iC]->Fill(-DEtaToMax, PhiRangeCorrelation(-DPhiToMax), 0.25*weight);
               }
               if(fabs(maxOppositeDEta + ZEta_0)<M_PI/2){
                  HMaxOppositeHadronEta[iC]->Fill(DEtaToMaxOpposite, weight);
                  HMaxOppositeHadronPhi[iC]->Fill(PhiRangeCorrelation(+DPhiToMaxOpposite), 0.5*weight);
                  HMaxOppositeHadronPhi[iC]->Fill(PhiRangeCorrelation(-DPhiToMaxOpposite), 0.5*weight);
               
                  HMaxOppositeHadronEtaPhi[iC]->Fill(+DEtaToMaxOpposite, PhiRangeCorrelation(+DPhiToMaxOpposite), 0.25*weight);
                  HMaxOppositeHadronEtaPhi[iC]->Fill(+DEtaToMaxOpposite, PhiRangeCorrelation(-DPhiToMaxOpposite), 0.25*weight);
                  HMaxOppositeHadronEtaPhi[iC]->Fill(-DEtaToMaxOpposite, PhiRangeCorrelation(+DPhiToMaxOpposite), 0.25*weight);
                  HMaxOppositeHadronEtaPhi[iC]->Fill(-DEtaToMaxOpposite, PhiRangeCorrelation(-DPhiToMaxOpposite), 0.25*weight);
               }
               if(fabs(maxOppositeWTADEta + ZEta_0)<M_PI/2){
                  HWTAEta[iC]->Fill(DEtaToOppositeWTA, weight);
                  HWTAPhi[iC]->Fill(PhiRangeCorrelation(+DPhiToOppositeWTA), 0.5*weight);
                  HWTAPhi[iC]->Fill(PhiRangeCorrelation(-DPhiToOppositeWTA), 0.5*weight);
               
                  HWTAEtaPhi[iC]->Fill(+DEtaToOppositeWTA, PhiRangeCorrelation(+DPhiToOppositeWTA), 0.25*weight);
                  HWTAEtaPhi[iC]->Fill(+DEtaToOppositeWTA, PhiRangeCorrelation(-DPhiToOppositeWTA), 0.25*weight);
                  HWTAEtaPhi[iC]->Fill(-DEtaToOppositeWTA, PhiRangeCorrelation(+DPhiToOppositeWTA), 0.25*weight);
                  HWTAEtaPhi[iC]->Fill(-DEtaToOppositeWTA, PhiRangeCorrelation(-DPhiToOppositeWTA), 0.25*weight);
               }
               if(fabs(maxMoreOppositeWTADEta + ZEta_0)<M_PI/2){
                  HWTAMoreEta[iC]->Fill(DEtaToMoreOppositeWTA, weight);
                  HWTAMorePhi[iC]->Fill(PhiRangeCorrelation(+DPhiToMoreOppositeWTA), 0.5*weight);
                  HWTAMorePhi[iC]->Fill(PhiRangeCorrelation(-DPhiToMoreOppositeWTA), 0.5*weight);
               
                  HWTAMoreEtaPhi[iC]->Fill(+DEtaToMoreOppositeWTA, PhiRangeCorrelation(+DPhiToMoreOppositeWTA), 0.25*weight);
                  HWTAMoreEtaPhi[iC]->Fill(+DEtaToMoreOppositeWTA, PhiRangeCorrelation(-DPhiToMoreOppositeWTA), 0.25*weight);
                  HWTAMoreEtaPhi[iC]->Fill(-DEtaToMoreOppositeWTA, PhiRangeCorrelation(+DPhiToMoreOppositeWTA), 0.25*weight);
                  HWTAMoreEtaPhi[iC]->Fill(-DEtaToMoreOppositeWTA, PhiRangeCorrelation(-DPhiToMoreOppositeWTA), 0.25*weight);
               }
            }
         }

         double zP = ZPT_0*cosh(ZEta_0);
         double zPz = ZPT_0*sinh(ZEta_0);
         double zE = sqrt(zP*zP+ZMass_0*ZMass_0);
         double zY = 0.5*log((zE+zPz)/(zE-zPz));
         //double TrackDY = TrackEta - zY;

        TotalZEventCount[iC] = TotalZEventCount[iC] + NCollWeight*ZWeight*VZWeight;
        HTotalZEventCount[iC]->Fill(0., NCollWeight*ZWeight*VZWeight);

         if(SomethingPassed == true)
         {
            EventCount[iC] = EventCount[iC] + NCollWeight*ZWeight*VZWeight;
            HEventCount[iC]->Fill(0., NCollWeight*ZWeight*VZWeight);
            
            HZPT[iC]->Fill(ZPT_0, NCollWeight*ZWeight*VZWeight);
            HZEta[iC]->Fill(ZEta_0, NCollWeight*ZWeight*VZWeight);
            HZPhi[iC]->Fill(ZPhi_0, NCollWeight*ZWeight*VZWeight);
            HZY[iC]->Fill(zY, NCollWeight*ZWeight*VZWeight);
            HZMass[iC]->Fill(ZMass_0, NCollWeight*ZWeight*VZWeight);
            HZEtaPhi[iC]->Fill(ZEta_0, ZPhi_0, NCollWeight*ZWeight*VZWeight);

            if(genZEta->size() > 0){
               GenEventCount[iC] = GenEventCount[iC] + NCollWeight*ZWeight*VZWeight;
               HGenEventCount[iC]->Fill(0., NCollWeight*ZWeight*VZWeight);
               HGenZEta[iC]->Fill(genZEta->at(0), NCollWeight*ZWeight*VZWeight);
               HGenZPhi[iC]->Fill(genZPhi->at(0), NCollWeight*ZWeight*VZWeight);
               HGenZEtaPhi[iC]->Fill(genZEta->at(0), genZPhi->at(0), NCollWeight*ZWeight*VZWeight);
            }
            
            if(fabs(maxDEta + ZEta_0)<M_PI/2)
               HZMaxHadronEtaPhi[iC]->Fill(maxDEta + ZEta_0, PhiRangeCorrelation(maxDPhi + ZPhi_0), NCollWeight*ZWeight*VZWeight);
            
            if(fabs(maxOppositeDEta + ZEta_0)<M_PI/2)
               HZMaxOppositeHadronEtaPhi[iC]->Fill(maxOppositeDEta + ZEta_0, PhiRangeCorrelation(maxOppositeDPhi + ZPhi_0), NCollWeight*ZWeight*VZWeight);
            
            if(fabs(maxOppositeWTADEta + ZEta_0)<M_PI/2)
               HZWTAEtaPhi[iC]->Fill(maxOppositeWTADEta + ZEta_0, PhiRangeCorrelation(maxOppositeWTADPhi + ZPhi_0), NCollWeight*ZWeight*VZWeight);
            
            if(fabs(maxMoreOppositeWTADEta + ZEta_0)<M_PI/2)
               HZWTAMoreEtaPhi[iC]->Fill(maxMoreOppositeWTADEta + ZEta_0, PhiRangeCorrelation(maxMoreOppositeWTADPhi + ZPhi_0), NCollWeight*ZWeight*VZWeight);
         }
      }
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   for(int iC = 0; iC < (int)C.size(); iC++)
   {
      Folder[iC]->cd();
      TNamed NTot("TotalEntryCount", Form("%f", TotalEventCount[iC]));
      NTot.Write();
      TNamed NTotZ("TotalZEntryCount", Form("%f", TotalZEventCount[iC]));
      NTotZ.Write();
      TNamed N("EntryCount", Form("%f", EventCount[iC]));
      N.Write();
      TNamed NGen("GenEntryCount", Form("%f", GenEventCount[iC]));
      NGen.Write();
      HEventCount[iC]->Write();
      HGenEventCount[iC]->Write();
      HTotalZEventCount[iC]->Write();
      HTotalEventCount[iC]->Write();
      HZPT[iC]->Write();
      HZY[iC]->Write();
      HZEta[iC]->Write();
      HZPhi[iC]->Write();
      HZEtaPhi[iC]->Write();
      HGenZEta[iC]->Write();
      HGenZPhi[iC]->Write();
      HGenZEtaPhi[iC]->Write();
      HZMass[iC]->Write();
      HTrackPT[iC]->Write();
      HTrackEta[iC]->Write();
      HTrackPhi[iC]->Write();
      HTrackEtaPhi[iC]->Write();
      HGenTrackEta[iC]->Write();
      HGenTrackPhi[iC]->Write();
      HGenTrackEtaPhi[iC]->Write();
      HTrackMuonDEta[iC]->Write();
      HTrackMuonDPhi[iC]->Write();
      HTrackMuonDEtaDPhi[iC]->Write();
      HTrackMuonDEtaDPhiZoom[iC]->Write();
      HTrackMuonDR[iC]->Write();
      HTrackMuonDRZoom[iC]->Write();
      HEta[iC]->Write();
      HPhi[iC]->Write();
      HEtaPhi[iC]->Write();
      HMaxHadronEta[iC]->Write();
      HMaxHadronPhi[iC]->Write();
      HMaxHadronEtaPhi[iC]->Write();
      HZMaxHadronEtaPhi[iC]->Write();
      HMaxOppositeHadronEta[iC]->Write();
      HMaxOppositeHadronPhi[iC]->Write();
      HMaxOppositeHadronEtaPhi[iC]->Write();
      HZMaxOppositeHadronEtaPhi[iC]->Write();
      HWTAEta[iC]->Write();
      HWTAPhi[iC]->Write();
      HWTAEtaPhi[iC]->Write();
      HZWTAEtaPhi[iC]->Write();
      HWTAMoreEta[iC]->Write();
      HWTAMorePhi[iC]->Write();
      HWTAMoreEtaPhi[iC]->Write();
      HZWTAMoreEtaPhi[iC]->Write();
   }

   OutputFile.Close();

   return 0;
}