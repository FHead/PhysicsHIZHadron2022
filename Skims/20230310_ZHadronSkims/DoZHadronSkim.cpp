#include <vector>
#include <iostream>
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
#include "CommonFunctions.h"
#include "ProgressBar.h"

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   bool DoGenLevel               = CL.GetBool("DoGenLevel", false);
   int PartNumber                = CL.GetInteger("ParNumber", 0);
   int NumberOfParts             = CL.GetInteger("NumberOfParts", 50);

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TNtuple NTuple("NTuple", "Z tree", "mass:pt:eta:phi");
   TTree Tree("Tree", "Tree for ZHadron analysis");

   TH2D H2D("H2D", "", 100, -6, 6, 100, -M_PI, M_PI);

   ZHadronMessenger MZHadron;
   MZHadron.SetBranch(&Tree);

   for(string InputFileName : InputFileNames)
   {
      MZHadron.Clear();

      TFile InputFile(InputFileName.c_str());

      HiEventTreeMessenger   MSignalEvent(InputFile);
      PbPbTrackTreeMessenger MSignalTrack(InputFile);
      MuTreeMessenger        MSignalMu(InputFile);

      int EntryCount = MSignalEvent.GetEntries();
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);

      for(int iE = 0; iE < MSignalEvent.GetEntries(); iE++)
      {
         if(EntryCount < 500 || (iE % (EntryCount / 500)) == 0)
         {
            Bar.Update(EntryCount);
            Bar.Print();
         }

         TLorentzVector VGenZ, VGenMu1, VGenMu2;

         MSignalEvent.GetEntry(iE);
         MSignalTrack.GetEntry(iE);
         MSignalMu.GetEntry(iE);

         MZHadron.Run   = MSignalEvent.Run;
         MZHadron.Lumi  = MSignalEvent.Lumi;
         MZHadron.Event = MSignalEvent.Event;
         MZHadron.hiBin = MSignalEvent.hiBin;
         MZHadron.hiHF  = MSignalEvent.hiHF;

         // Loop over gen muons
         if(MSignalMu.NGen > 1)
         {
            for(int igen1 = 0; igen1 < MSignalMu.NGen; igen1++)
            {
               if(MSignalMu.GenMom[igen1] != 23)
                  continue;

               VGenMu1.SetPtEtaPhiM(MSignalMu.GenPT[igen1],
                     MSignalMu.GenEta[igen1],
                     MSignalMu.GenPhi[igen1],
                     M_MU);

               for(int igen2 = igen1 + 1; igen2 < MSignalMu.NGen; igen2++)
               {
                  if(MSignalMu.GenMom[igen2] != 23)
                     continue;

                  VGenMu2.SetPtEtaPhiM(MSignalMu.GenPT[igen2],
                        MSignalMu.GenEta[igen2],
                        MSignalMu.GenPhi[igen2],
                        M_MU);

                  VGenZ = VGenMu1 + VGenMu2;
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
         for(int ipair = 0; ipair < MSignalMu.NDi; ipair++)
         {
            if(MSignalMu.DiCharge1[ipair] == MSignalMu.DiCharge2[ipair])   continue;
            if(fabs(MSignalMu.DiEta1[ipair]) > 2.4)                        continue;
            if(fabs(MSignalMu.DiEta2[ipair]) > 2.4)                        continue;
            if(fabs(MSignalMu.DiPT1[ipair]) < 20)                          continue;
            if(fabs(MSignalMu.DiPT2[ipair]) < 20)                          continue;

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

         // Z-track correlation
         if(MZHadron.zMass->size() > 0 && MZHadron.zPt->at(0) > 30)
         {
            for(int itrack = 0; itrack < MSignalTrack.TrackPT->size(); itrack++)
            {
               if(MSignalTrack.TrackHighPurity->at(itrack) == false)
                  continue;

               double deltaPhi = DeltaPhi(MZHadron.zPhi->at(0), MSignalTrack.TrackPhi->at(itrack) - M_PI);
               double deltaEta = fabs(MZHadron.zEta->at(0) - MSignalTrack.TrackEta->at(itrack));

               H2D.Fill(deltaEta, deltaPhi, 0.25);
               H2D.Fill(-deltaEta, deltaPhi, 0.25);
               H2D.Fill(-deltaEta, -deltaPhi, 0.25);
               H2D.Fill(deltaEta, -deltaPhi, 0.25);

               MZHadron.trackDphi->push_back(deltaPhi);
               MZHadron.trackDeta->push_back(deltaEta);
               MZHadron.trackPt->push_back(MSignalTrack.TrackPT->at(itrack));
            }
         }

         MZHadron.FillEntry();
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   OutputFile.cd();
   H2D.Write();
   NTuple.Write();
   Tree.Write();
   OutputFile.Close();

   return 0;
}

