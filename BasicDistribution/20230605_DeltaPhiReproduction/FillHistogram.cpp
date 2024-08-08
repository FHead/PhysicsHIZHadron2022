#include <iostream>
#include <map>
#include <cmath>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"

#include "CommonFunctions.h"
#include "CommandLine.h"
#include "Messenger.h"

struct Configuration;
int main(int argc, char *argv[]);

struct Configuration
{
   double CMin, CMax;
   double ZPTMin, ZPTMax;
   double PTMin, PTMax;
   int NPVMin, NPVMax;
   string Tag;
   Configuration(double cmin, double cmax, double zptmin, double zptmax, double ptmin, double ptmax, int npvmin, int npvmax)
      : CMin(cmin), CMax(cmax), ZPTMin(zptmin), ZPTMax(zptmax), PTMin(ptmin), PTMax(ptmax), NPVMin(npvmin), NPVMax(npvmax)
   {
      Tag = Form("Centrality_%.0f_%.0f_ZPT_%.0f_%.0f_TrackPT_%.0f_%.0f_PV_%d_%d",
         CMin, CMax, ZPTMin, ZPTMax, PTMin * 10, PTMax * 10, NPVMin, NPVMax);
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   bool DoGen                    = CL.GetBool("DoGen", false);
   bool DoSignalEvent            = CL.GetBool("DoSignalEvent", false);
   bool IsMC                     = CL.GetBool("IsMC", false);
   bool IsPP                     = CL.GetBool("IsPP", false);
   double Fraction               = CL.GetDouble("Fraction", 1.00);
   bool SkipResidual             = CL.GetBool("SkipResidual", false);
   bool RedoHiBin                = CL.GetBool("RedoHiBin", false);
   int HiBinVariation            = RedoHiBin ? CL.GetInt("HiBinVariation") : 0;
   bool AlternateMuTag           = CL.GetBool("AlternateMuTag", false);
   double MuTagRange             = AlternateMuTag ? CL.GetDouble("MuTagRange") : 1000;
   bool DoExtraZWeight           = CL.GetBool("DoExtraZWeight", false);
   int ExtraZWeightIndex         = DoExtraZWeight ? CL.GetInt("ExtraZWeightIndex") : 0;
   bool DoAdHocSignalHF          = CL.GetBool("DoAdHocSignalHF", false);
   bool DoReplaceZWeight         = CL.GetBool("DoReplaceZWeight", true);
   double VZMin                  = CL.GetDouble("VZMin",-15);
   double VZMax                  = CL.GetDouble("VZMax",15);

   vector<Configuration> Cs;

   Cs.push_back(Configuration(0,  30,  5,  20, 1, 4, 0, 10));
   Cs.push_back(Configuration(0,  30,  5,  20, 1, 2, 0, 10));

   // vector<pair<int, int>> NPV{pair<int, int>(0, 10), pair<int, int>(0, 1), pair<int, int>(2, 10)};
   // vector<pair<int, int>> Centrality{pair<int, int>(0, 10), pair<int, int>(10, 30), pair<int, int>(30, 50), pair<int, int>(50, 90), pair<int, int>(0, 30), pair<int, int>(30, 90), pair<int, int>(0, 90), pair<int, int>(0, 50), pair<int, int>(10, 90), pair<int, int>(50, 70), pair<int, int>(70, 90)};
   // vector<pair<double, double>> TrackPT{pair<double, double>(1, 4), pair<double, double>(1, 2), pair<double, double>(2, 5), pair<double, double>(5, 10), pair<double, double>(10, 100), pair<double, double>(1, 100), pair<double, double>(4, 10), pair<double, double>(2, 4), pair<double, double>(1, 10), pair<double, double>(5, 100), pair<double, double>(2, 100)};
   // vector<double> ZPTMin{30, 40, 50, 60};

   // Reduced set for faster running
   vector<pair<int, int>> NPV{pair<int, int>(0, 10), pair<int, int>(0, 1)};
   vector<pair<int, int>> Centrality{pair<int, int>(0, 10), pair<int, int>(10, 30), pair<int, int>(30, 50), pair<int, int>(50, 90), pair<int, int>(0, 30), pair<int, int>(30, 90), pair<int, int>(0, 90), pair<int, int>(0, 50), pair<int, int>(50, 70), pair<int, int>(70, 90)};
   vector<pair<double, double>> TrackPT{pair<double, double>(1, 2), pair<double, double>(10, 100), pair<double, double>(1, 100), pair<double, double>(4, 10), pair<double, double>(2, 4), pair<double, double>(1, 10)};
   vector<double> ZPTMin{30, 40, 60};
   
   for(double ZPT : ZPTMin)
      for(pair<int, int> PV : NPV)
         for(pair<double, double> Track : TrackPT)
            for(pair<int, int> C : Centrality)
               Cs.push_back(Configuration(C.first, C.second, ZPT, 200, Track.first, Track.second, PV.first, PV.second));

   double HiHFBins[401] = {0};
   for(int i = 0; i <= 400; i++)
      HiHFBins[i] = exp((log(6000) - log(1)) / 400 * i + log(1));
   
   double SignalHFBins[401] = {0};
   for(int i = 0; i <= 400; i++)
      SignalHFBins[i] = exp((log(135000) - log(500)) / 400 * i + log(500));

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   vector<TH1D *> HDeltaPhi;
   vector<TH1D *> HDeltaEta;
   vector<TH1D *> HDeltaEtaZSide;
   vector<TH1D *> HDeltaEtaJetSide;
   vector<TH1D *> HDeltaY;
   vector<TH1D *> HDeltaYZSide;
   vector<TH1D *> HDeltaYJetSide;
   vector<TH1D *> HHiBin;
   vector<TH1D *> HHiHF;
   vector<TH1D *> HSignalHF;
   vector<TH1D *> HN;
   
   for(Configuration &C : Cs)
   {
      HDeltaPhi.push_back(new TH1D(Form("HDeltaPhi_%s", C.Tag.c_str()), ";|#Delta#phi|;", 10, 0, M_PI));
      HDeltaEta.push_back(new TH1D(Form("HDeltaEta_%s", C.Tag.c_str()), ";|#Delta#eta|;", 10, 0, 3.5));
      HDeltaEtaZSide.push_back(new TH1D(Form("HDeltaEtaZSide_%s", C.Tag.c_str()), ";|#Delta#eta|;", 10, 0, 3.5));
      HDeltaEtaJetSide.push_back(new TH1D(Form("HDeltaEtaJetSide_%s", C.Tag.c_str()), ";|#Delta#eta|;", 10, 0, 3.5));
      HDeltaY.push_back(new TH1D(Form("HDeltaY_%s", C.Tag.c_str()), ";|#Deltay|;", 10, 0, 3.5));
      HDeltaYZSide.push_back(new TH1D(Form("HDeltaYZSide_%s", C.Tag.c_str()), ";|#Deltay|;", 10, 0, 3.5));
      HDeltaYJetSide.push_back(new TH1D(Form("HDeltaYJetSide_%s", C.Tag.c_str()), ";|#Deltay|;", 10, 0, 3.5));
      HHiBin.push_back(new TH1D(Form("HHiBin_%s", C.Tag.c_str()), ";hiBin;", 200, 0, 200));
      HHiHF.push_back(new TH1D(Form("HHiHF_%s", C.Tag.c_str()), ";hiHF;", 400, HiHFBins));
      HSignalHF.push_back(new TH1D(Form("HSignalHF_%s", C.Tag.c_str()), ";SumHF;", 400, SignalHFBins));
      HN.push_back(new TH1D(Form("HN_%s", C.Tag.c_str()), ";;", 1, 0, 1));
   }

   for(string InputFileName : InputFileNames)
   {
      cout << "Processing input file " << InputFileName << "..." << endl;

      TFile InputFile(InputFileName.c_str());

      TTree *Tree = (TTree *)InputFile.Get("Tree");
      ZHadronMessenger M(Tree);

      if(Tree == nullptr)
      {
         InputFile.Close();
         continue;
      }

      int EntryCount = M.Tree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         M.GetEntry(iE);

         // hibin recalculate if needed
         if(RedoHiBin == true)
            M.hiBin = GetHiBin(M.hiHF, HiBinVariation);

         // no identified Z in this event
         if(DoGen == true && M.genZPt->size() == 0)   continue;
         if(DoGen == false && M.zPt->size() == 0)     continue;

         double ZPT   = DoGen ? M.genZPt->at(0)   : M.zPt->at(0);
         double ZEta  = DoGen ? M.genZEta->at(0)  : M.zEta->at(0);
         double ZPhi  = DoGen ? M.genZPhi->at(0)  : M.zPhi->at(0);
         double ZMass = DoGen ? M.genZMass->at(0) : M.zMass->at(0);

         double ZPZ   = ZPT * sinh(ZEta);
         double ZP    = ZPT * cosh(ZEta);
         double ZE    = sqrt(ZP * ZP + ZMass * ZMass);
         double ZY    = 0.5 * log((ZE + ZPZ) / (ZE - ZPZ));

         // cout << ZPZ << " " << ZEta << " " << 0.5 * log((ZP + ZPZ) / (ZP - ZPZ)) << " " << ZY << endl;

         double Mu1Eta = DoGen ? M.genMuEta1->at(0) : M.muEta1->at(0);
         double Mu1Phi = DoGen ? M.genMuPhi1->at(0) : M.muPhi1->at(0);
         double Mu2Eta = DoGen ? M.genMuEta2->at(0) : M.muEta2->at(0);
         double Mu2Phi = DoGen ? M.genMuPhi2->at(0) : M.muPhi2->at(0);

         double Mu1DEta = Mu1Eta - ZEta;
         double Mu1DPhi = DeltaPhi(Mu1Phi, ZPhi);
         double Mu2DEta = Mu2Eta - ZEta;
         double Mu2DPhi = DeltaPhi(Mu2Phi, ZPhi);

         double EventWeight = M.NCollWeight * M.ZWeight * M.VZWeight;
         if(DoReplaceZWeight == true)
         {
            EventWeight = M.NCollWeight * M.VZWeight;
            if(IsPP == true)
               EventWeight = EventWeight * GetZWeightPPDataTrigger(ZPT, ZY);
            else
               EventWeight = EventWeight * GetZWeightPbPbDataTrigger(ZPT, ZY, M.hiBin);
         }
         if(DoExtraZWeight == true && ExtraZWeightIndex >= 0)
            EventWeight = EventWeight * M.ExtraZWeight[ExtraZWeightIndex];

         if(DoAdHocSignalHF == true)
         {
            double SignalHFWeight = 0.04585 + 187.7 / M.SignalHF + 0.0007564 * log(M.SignalHF);
            EventWeight = EventWeight / SignalHFWeight;
         }

         for(int iC = 0; iC < (int)Cs.size(); iC++)
         {
            if(IsPP == false && M.hiBin * 0.5 < Cs[iC].CMin)    continue;
            if(IsPP == false && M.hiBin * 0.5 >= Cs[iC].CMax)   continue;
            if(ZPT < Cs[iC].ZPTMin)                             continue;
            if(ZPT >= Cs[iC].ZPTMax)                            continue;
            if(M.NVertex < Cs[iC].NPVMin)                       continue;
            if(M.NVertex > Cs[iC].NPVMax)                       continue;
            if(M.SignalVZ < VZMin)                              continue;
            if(M.SignalVZ > VZMax)                              continue;
            
            HN[iC]->Fill(0.0, EventWeight);
            HHiBin[iC]->Fill(M.hiBin, EventWeight);
            HHiHF[iC]->Fill(M.hiHF, EventWeight);
            HSignalHF[iC]->Fill(M.SignalHF, EventWeight);
         }

         int TrackCount = M.trackPt->size();
         for(int iT = 0; iT < TrackCount; iT++)
         {
            double TrackMuDEta1 = M.trackDeta->at(iT) - Mu1DEta;
            double TrackMuDPhi1 = DeltaPhi(M.trackDphi->at(iT), Mu1DPhi);
            double TrackMuDR1 = sqrt(TrackMuDEta1 * TrackMuDEta1 + TrackMuDPhi1 * TrackMuDPhi1);
            double TrackMuDEta2 = M.trackDeta->at(iT) - Mu2DEta;
            double TrackMuDPhi2 = DeltaPhi(M.trackDphi->at(iT), Mu2DPhi);
            double TrackMuDR2 = sqrt(TrackMuDEta2 * TrackMuDEta2 + TrackMuDPhi2 * TrackMuDPhi2);

            if(AlternateMuTag == false && M.trackMuTagged->at(iT) == true)
               continue;
            if(AlternateMuTag == true && min(TrackMuDR1, TrackMuDR2) < MuTagRange)
               continue;
            if(DoSignalEvent == true && M.subevent->at(iT) != 0)
               continue;

            double TrackEta = M.trackDeta->at(iT) + ZEta;
            double TrackPhi = M.trackDphi->at(iT) + ZPhi;

            double TrackDEta = TrackEta - ZEta;
            double TrackDY   = TrackEta - ZY;
            double TrackDPhi = DeltaPhi(TrackPhi, ZPhi);

            double TrackWeight = M.trackWeight->at(iT) * M.trackResidualWeight->at(iT) * EventWeight;
            if(SkipResidual == true)
               TrackWeight = M.trackWeight->at(iT) * EventWeight;

            for(int iC = 0; iC < (int)Cs.size(); iC++)
            {
               if(IsPP == false && M.hiBin * 0.5 < Cs[iC].CMin)       continue;
               if(IsPP == false && M.hiBin * 0.5 >= Cs[iC].CMax)      continue;
               if(ZPT < Cs[iC].ZPTMin)                                continue;
               if(ZPT >= Cs[iC].ZPTMax)                               continue;
               if(M.trackPt->at(iT) < Cs[iC].PTMin)                   continue;
               if(M.trackPt->at(iT) >= Cs[iC].PTMax)                  continue;
               if(DoGen == false && M.NVertex < Cs[iC].NPVMin)        continue;
               if(DoGen == false && M.NVertex > Cs[iC].NPVMax)        continue;
               if(M.SignalVZ < VZMin)                                 continue;
               if(M.SignalVZ > VZMax)                                 continue;

               HDeltaPhi[iC]->Fill(fabs(TrackDPhi), TrackWeight);

               HDeltaEta[iC]->Fill(fabs(TrackDEta), TrackWeight);

               double zP = ZPT*cosh(ZEta);
               double zPz = ZPT*sinh(ZEta);
               double zE = sqrt(zP*zP+ZMass*ZMass);
               double zY = 0.5*log((zE+zPz)/(zE-zPz));

               double trkP = M.trackPt->at(iT) *cosh(TrackEta);
               double trkPz = M.trackPt->at(iT) *sinh(TrackEta);

               double piMass = 0.13957039;

               double trkE = sqrt(trkP*trkP+piMass*piMass);
               double trkY = 0.5*log((trkE+trkPz)/(trkE-trkPz));


               //double TrackDY = TrackEta - zY;
               double TrackDY = trkY - zY;

               HDeltaY[iC]->Fill(fabs(TrackDY), TrackWeight);

               if(fabs(TrackDPhi) < M_PI / 2){
                  HDeltaEtaZSide[iC]->Fill(fabs(TrackDEta), TrackWeight);
                  HDeltaYZSide[iC]->Fill(fabs(TrackDY), TrackWeight);
               }
               else{
                  HDeltaEtaJetSide[iC]->Fill(fabs(TrackDEta), TrackWeight);
               
               HDeltaY[iC]->Fill(fabs(TrackDY), TrackWeight);
               if(fabs(TrackDPhi) < M_PI / 2)
                  HDeltaYZSide[iC]->Fill(fabs(TrackDY), TrackWeight);
               else
                  HDeltaYJetSide[iC]->Fill(fabs(TrackDY), TrackWeight);
               }
            }   
         }
      }

      InputFile.Close();
   }

   OutputFile.cd();

   for(int i = 0; i < (int)Cs.size(); i++)
   {
      HDeltaPhi[i]->Write();
      HDeltaEta[i]->Write();
      HDeltaEtaZSide[i]->Write();
      HDeltaEtaJetSide[i]->Write();
      HDeltaY[i]->Write();
      HDeltaYZSide[i]->Write();
      HDeltaYJetSide[i]->Write();
      HHiBin[i]->Write();
      HHiHF[i]->Write();
      HSignalHF[i]->Write();
      HN[i]->Write();
   }

   OutputFile.Close();

   return 0;
}



