#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TMath.h>
#include <TROOT.h>
#include <cmath>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TSystem.h>
#include <TLatex.h>
#include <TLine.h>
#include <iostream>

double TptL_min = 0.5;

int main(int argc, char *argv[]);
void ZtrackDraw_single(int binnum,float ptL,float ptH,float centL,float centH,float TptL,float TptH);

void style(){

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLabelFont(43,"xyz");
  gStyle->SetTitleFont(43);
  gStyle->SetTitleFont(43,"xyz");
  gStyle->SetStatFont(43);

  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetOptStat(0); /*don't show statistics box*/
  gStyle->SetOptTitle(0); /*don't show histogram titles*/
  gStyle->SetTitleSize(48, "xyz");
  gStyle->SetTitleOffset(1, "xyz");
  gStyle->SetLabelSize(36, "xy");
  gStyle->SetLabelSize(20, "z");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);

  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.15);

  gStyle->SetLineScalePS(1.5);

  gROOT->ForceStyle();
}

TFile *file_sigMC;
TFile *file_bkgMC;
TFile *file_sigDA;
TFile *file_bkgDA;
TFile *file_ppMC;

TFile *file_sigMCgen;
TFile *file_bkgMCgen;

const char *typeofdata = "v17d/20240205";
const char *typeofdata1 = "v17d_PFmuon_SigBkg";
const char *typeofdatatext = "single muon";

void ZtrackDraw_single(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000)
{

   std::cout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;
   TCanvas *c = new TCanvas("c","",800,800);

   std::cout<<"Getting histograms..."<<std::endl;

   std::string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",ptL,ptH,centL,centH,TptL,TptH);
   std::replace(FolderName.begin(), FolderName.end(), '.', 'p');

   TH1D* hData_eta = (TH1D*) file_sigDA->Get(Form("%s/HEta", FolderName.c_str()));
   TH1D* hMC_eta = (TH1D*) file_sigMC->Get(Form("%s/HEta", FolderName.c_str()));
   TH1D* hpp_eta = (TH1D*) file_ppMC->Get(Form("%s/HEta", FolderName.c_str()));

   hData_eta->SetName("hData_eta");
   hMC_eta->SetName("hMC_eta");
   hpp_eta->SetName("hpp_eta");

   TH1D* hData_phi = (TH1D*) file_sigDA->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hMC_phi = (TH1D*) file_sigMC->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hpp_phi = (TH1D*) file_ppMC->Get(Form("%s/HPhi", FolderName.c_str()));

   hData_phi->SetName("hData_phi");
   hMC_phi->SetName("hMC_phi");
   hpp_phi->SetName("hpp_phi");

   TH2D* hData_etaphi_1 = (TH2D*) file_sigDA->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   TH2D* hMC_etaphi_1 = (TH2D*) file_sigMC->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   TH2D* hpp_etaphi_1 = (TH2D*) file_ppMC->Get(Form("%s/HEtaPhi", FolderName.c_str()));

   hData_etaphi_1->SetName("hData_etaphi_1");
   hMC_etaphi_1->SetName("hMC_etaphi_1");
   hpp_etaphi_1->SetName("hpp_etaphi_1");

   TH2D* hMC_etaphi_gen = (TH2D*) file_sigMCgen->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_etaphi_gen = (TH2D*) file_bkgMCgen->Get(Form("%s/HEtaPhi", FolderName.c_str()));

   hMC_etaphi_gen->SetName("hMC_etaphi_gen");
   hMC_bkg_etaphi_gen->SetName("hMC_etaphi_gen");

   TH1D* hData_MuDeta = (TH1D*) file_sigDA->Get(Form("%s/HTrackMuonDEta", FolderName.c_str()));
   TH1D* hMC_MuDeta = (TH1D*) file_sigMC->Get(Form("%s/HTrackMuonDEta", FolderName.c_str()));

   hData_MuDeta->SetName("hData_MuDeta");
   hMC_MuDeta->SetName("hMC_MuDeta");

   TH1D* hData_MuDphi = (TH1D*) file_sigDA->Get(Form("%s/HTrackMuonDPhi", FolderName.c_str()));
   TH1D* hMC_MuDphi = (TH1D*) file_sigMC->Get(Form("%s/HTrackMuonDPhi", FolderName.c_str()));

   hData_MuDphi->SetName("hData_MuDphi");
   hMC_MuDphi->SetName("hMC_MuDphi");

   TH2D* hData_MuDetaphi = (TH2D*) file_sigDA->Get(Form("%s/HTrackMuonDEtaDPhi", FolderName.c_str()));
   TH2D* hMC_MuDetaphi = (TH2D*) file_sigMC->Get(Form("%s/HTrackMuonDEtaDPhi", FolderName.c_str()));

   hData_MuDetaphi->SetName("hData_MuDetaphi");
   hMC_MuDetaphi->SetName("hMC_MuDetaphi");

   TH1D* hData_bkg_eta = (TH1D*) file_bkgDA->Get(Form("%s/HEta", FolderName.c_str()));
   TH1D* hMC_bkg_eta = (TH1D*) file_bkgMC->Get(Form("%s/HEta", FolderName.c_str()));

   hData_bkg_eta->SetName("hData_bkg_eta");
   hMC_bkg_eta->SetName("hMC_bkg_eta");

   TH1D* hData_bkg_phi = (TH1D*) file_bkgDA->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hMC_bkg_phi = (TH1D*) file_bkgMC->Get(Form("%s/HPhi", FolderName.c_str()));

   hData_bkg_phi->SetName("hData_bkg_phi");
   hMC_bkg_phi->SetName("hMC_bkg_phi");

   TH2D* hData_bkg_etaphi_1 = (TH2D*) file_bkgDA->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_etaphi_1 = (TH2D*) file_bkgMC->Get(Form("%s/HEtaPhi", FolderName.c_str()));

   hData_bkg_etaphi_1->SetName("hData_bkg_etaphi_1");
   hMC_bkg_etaphi_1->SetName("hMC_bkg_etaphi_1");

   TH1D* hData_bkg_MuDeta = (TH1D*) file_bkgDA->Get(Form("%s/HTrackMuonDEta", FolderName.c_str()));
   TH1D* hMC_bkg_MuDeta = (TH1D*) file_bkgMC->Get(Form("%s/HTrackMuonDEta", FolderName.c_str()));

   hData_bkg_MuDeta->SetName("hData_bkg_MuDeta");
   hMC_bkg_MuDeta->SetName("hMC_bkg_MuDeta");

   TH1D* hData_bkg_MuDphi = (TH1D*) file_bkgDA->Get(Form("%s/HTrackMuonDPhi", FolderName.c_str()));
   TH1D* hMC_bkg_MuDphi = (TH1D*) file_bkgMC->Get(Form("%s/HTrackMuonDPhi", FolderName.c_str()));

   hData_bkg_MuDphi->SetName("hData_bkg_MuDphi");
   hMC_bkg_MuDphi->SetName("hMC_bkg_MuDphi");

   TH2D* hData_bkg_MuDetaphi = (TH2D*) file_bkgDA->Get(Form("%s/HTrackMuonDEtaDPhi", FolderName.c_str()));
   TH2D* hMC_bkg_MuDetaphi = (TH2D*) file_bkgMC->Get(Form("%s/HTrackMuonDEtaDPhi", FolderName.c_str()));

   hData_bkg_MuDetaphi->SetName("hData_bkg_MuDetaphi");
   hMC_bkg_MuDetaphi->SetName("hMC_bkg_MuDetaphi");

   TH2D* hData_maxetaphi = (TH2D*) file_sigDA->Get(Form("%s/HMaxHadronEtaPhi", FolderName.c_str()));
   TH2D* hMC_maxetaphi = (TH2D*) file_sigMC->Get(Form("%s/HMaxHadronEtaPhi", FolderName.c_str()));
   TH2D* hData_bkg_maxetaphi = (TH2D*) file_bkgDA->Get(Form("%s/HMaxHadronEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_maxetaphi = (TH2D*) file_bkgMC->Get(Form("%s/HMaxHadronEtaPhi", FolderName.c_str()));

   hData_maxetaphi->SetName("hData_maxetaphi");
   hMC_maxetaphi->SetName("hMC_maxetaphi");
   hData_bkg_maxetaphi->SetName("hData_bkg_maxetaphi");
   hMC_bkg_maxetaphi->SetName("hMC_bkg_maxetaphi");

   TH2D* hData_maxOetaphi = (TH2D*) file_sigDA->Get(Form("%s/HMaxOppositeHadronEtaPhi", FolderName.c_str()));
   TH2D* hMC_maxOetaphi = (TH2D*) file_sigMC->Get(Form("%s/HMaxOppositeHadronEtaPhi", FolderName.c_str()));
   TH2D* hData_bkg_maxOetaphi = (TH2D*) file_bkgDA->Get(Form("%s/HMaxOppositeHadronEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_maxOetaphi = (TH2D*) file_bkgMC->Get(Form("%s/HMaxOppositeHadronEtaPhi", FolderName.c_str()));

   hData_maxOetaphi->SetName("hData_maxOetaphi");
   hMC_maxOetaphi->SetName("hMC_maxOetaphi");
   hData_bkg_maxOetaphi->SetName("hData_bkg_maxOetaphi");
   hMC_bkg_maxOetaphi->SetName("hMC_bkg_maxOetaphi");

   TH2D* hData_WTAetaphi = (TH2D*) file_sigDA->Get(Form("%s/HWTAEtaPhi", FolderName.c_str()));
   TH2D* hMC_WTAetaphi = (TH2D*) file_sigMC->Get(Form("%s/HWTAEtaPhi", FolderName.c_str()));
   TH2D* hData_bkg_WTAetaphi = (TH2D*) file_bkgDA->Get(Form("%s/HWTAEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_WTAetaphi = (TH2D*) file_bkgMC->Get(Form("%s/HWTAEtaPhi", FolderName.c_str()));

   hData_WTAetaphi->SetName("hData_WTAetaphi");
   hMC_WTAetaphi->SetName("hMC_WTAetaphi");
   hData_bkg_WTAetaphi->SetName("hData_bkg_WTAetaphi");
   hMC_bkg_WTAetaphi->SetName("hMC_bkg_WTAetaphi");

   TH2D* hData_WTAMoreetaphi = (TH2D*) file_sigDA->Get(Form("%s/HWTAMoreEtaPhi", FolderName.c_str()));
   TH2D* hMC_WTAMoreetaphi = (TH2D*) file_sigMC->Get(Form("%s/HWTAMoreEtaPhi", FolderName.c_str()));
   TH2D* hData_bkg_WTAMoreetaphi = (TH2D*) file_bkgDA->Get(Form("%s/HWTAMoreEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_WTAMoreetaphi = (TH2D*) file_bkgMC->Get(Form("%s/HWTAMoreEtaPhi", FolderName.c_str()));

   hData_WTAMoreetaphi->SetName("hData_WTAMoreetaphi");
   hMC_WTAMoreetaphi->SetName("hMC_WTAMoreetaphi");
   hData_bkg_WTAMoreetaphi->SetName("hData_bkg_WTAMoreetaphi");
   hMC_bkg_WTAMoreetaphi->SetName("hMC_bkg_WTAMoreetaphi");

   TH2D* hData_Zmaxetaphi = (TH2D*) file_sigDA->Get(Form("%s/HZMaxHadronEtaPhi", FolderName.c_str()));
   TH2D* hMC_Zmaxetaphi = (TH2D*) file_sigMC->Get(Form("%s/HZMaxHadronEtaPhi", FolderName.c_str()));
   TH2D* hData_Zbkg_maxetaphi = (TH2D*) file_bkgDA->Get(Form("%s/HZMaxHadronEtaPhi", FolderName.c_str()));
   TH2D* hMC_Zbkg_maxetaphi = (TH2D*) file_bkgMC->Get(Form("%s/HZMaxHadronEtaPhi", FolderName.c_str()));

   hData_Zmaxetaphi->SetName("hData_Zmaxetaphi");
   hMC_Zmaxetaphi->SetName("hMC_Zmaxetaphi");
   hData_Zbkg_maxetaphi->SetName("hData_Zbkg_maxetaphi");
   hMC_Zbkg_maxetaphi->SetName("hMC_Zbkg_maxetaphi");

   TH2D* hData_ZmaxOetaphi = (TH2D*) file_sigDA->Get(Form("%s/HZMaxOppositeHadronEtaPhi", FolderName.c_str()));
   TH2D* hMC_ZmaxOetaphi = (TH2D*) file_sigMC->Get(Form("%s/HZMaxOppositeHadronEtaPhi", FolderName.c_str()));
   TH2D* hData_Zbkg_maxOetaphi = (TH2D*) file_bkgDA->Get(Form("%s/HZMaxOppositeHadronEtaPhi", FolderName.c_str()));
   TH2D* hMC_Zbkg_maxOetaphi = (TH2D*) file_bkgMC->Get(Form("%s/HZMaxOppositeHadronEtaPhi", FolderName.c_str()));

   hData_ZmaxOetaphi->SetName("hData_ZmaxOetaphi");
   hMC_ZmaxOetaphi->SetName("hMC_ZmaxOetaphi");
   hData_Zbkg_maxOetaphi->SetName("hData_Zbkg_maxOetaphi");
   hMC_Zbkg_maxOetaphi->SetName("hMC_Zbkg_maxOetaphi");

   TH2D* hData_ZWTAetaphi = (TH2D*) file_sigDA->Get(Form("%s/HZWTAEtaPhi", FolderName.c_str()));
   TH2D* hMC_ZWTAetaphi = (TH2D*) file_sigMC->Get(Form("%s/HZWTAEtaPhi", FolderName.c_str()));
   TH2D* hData_Zbkg_WTAetaphi = (TH2D*) file_bkgDA->Get(Form("%s/HZWTAEtaPhi", FolderName.c_str()));
   TH2D* hMC_Zbkg_WTAetaphi = (TH2D*) file_bkgMC->Get(Form("%s/HZWTAEtaPhi", FolderName.c_str()));

   hData_ZWTAetaphi->SetName("hData_ZWTAetaphi");
   hMC_ZWTAetaphi->SetName("hMC_ZWTAetaphi");
   hData_Zbkg_WTAetaphi->SetName("hData_Zbkg_WTAetaphi");
   hMC_Zbkg_WTAetaphi->SetName("hMC_Zbkg_WTAetaphi");

   TH2D* hData_ZWTAMoreetaphi = (TH2D*) file_sigDA->Get(Form("%s/HZWTAMoreEtaPhi", FolderName.c_str()));
   TH2D* hMC_ZWTAMoreetaphi = (TH2D*) file_sigMC->Get(Form("%s/HZWTAMoreEtaPhi", FolderName.c_str()));
   TH2D* hData_Zbkg_WTAMoreetaphi = (TH2D*) file_bkgDA->Get(Form("%s/HZWTAMoreEtaPhi", FolderName.c_str()));
   TH2D* hMC_Zbkg_WTAMoreetaphi = (TH2D*) file_bkgMC->Get(Form("%s/HZWTAMoreEtaPhi", FolderName.c_str()));

   hData_ZWTAMoreetaphi->SetName("hData_ZWTAMoreetaphi");
   hMC_ZWTAMoreetaphi->SetName("hMC_ZWTAMoreetaphi");
   hData_Zbkg_WTAMoreetaphi->SetName("hData_Zbkg_WTAMoreetaphi");
   hMC_Zbkg_WTAMoreetaphi->SetName("hMC_Zbkg_WTAMoreetaphi");


   std::cout<<"Setting histograms..."<<std::endl;

   float hfL=0, hfH=0;

   if(centL==0) hfL=999999;
   else if (centL==10) hfL=3039.47;
   else if (centL==30) hfL=1342.21;
   else if (centL==50) hfL=484.422;
   else if (centL==90) hfL=24.7924;

   if(centH==0) hfH=999999;
   else if (centH==10) hfH=3039.47;
   else if (centH==30) hfH=1342.21;
   else if (centH==50) hfH=484.422;
   else if (centH==90) hfH=24.7924;

   std::cout<<"Getting Entries..."<<std::endl;

   TNamed *nD_tN  = (TNamed *) file_sigDA->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nM_tN  = (TNamed *) file_sigMC->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nDb_tN = (TNamed *) file_bkgDA->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nMb_tN = (TNamed *) file_bkgMC->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *npM_tN = (TNamed *) file_ppMC->Get(Form("%s/EntryCount",FolderName.c_str()));

   TNamed *nM_tNgen  = (TNamed *) file_sigMCgen->Get(Form("%s/GenEntryCount",FolderName.c_str()));
   TNamed *nMb_tNgen = (TNamed *) file_bkgMCgen->Get(Form("%s/GenEntryCount",FolderName.c_str()));

   std::string sD_tN  = (std::string) nD_tN->GetTitle();
   std::string sM_tN  = (std::string) nM_tN->GetTitle();
   std::string sDb_tN = (std::string) nDb_tN->GetTitle();
   std::string sMb_tN = (std::string) nMb_tN->GetTitle();
   std::string spM_tN = (std::string) npM_tN->GetTitle();

   std::string sM_tNgen  = (std::string) nM_tNgen->GetTitle();
   std::string sMb_tNgen = (std::string) nMb_tNgen->GetTitle();

   float tD_tN  = std::stof(sD_tN);
   float tM_tN  = std::stof(sM_tN);
   float tDb_tN = std::stof(sDb_tN);
   float tMb_tN = std::stof(sMb_tN);
   float tpM_tN = std::stof(spM_tN);

   float tM_tNgen  = std::stof(sM_tNgen);
   float tMb_tNgen = std::stof(sMb_tNgen);

   std::cout<<"tD_tN = "<<tD_tN<<std::endl;
   std::cout<<"tM_tN = "<<tM_tN<<std::endl;
   std::cout<<"tDb_tN = "<<tDb_tN<<std::endl;
   std::cout<<"tMb_tN = "<<tMb_tN<<std::endl;
   std::cout<<"tpM_tN = "<<tpM_tN<<std::endl;

   std::cout<<"tM_tNgen = "<<tM_tNgen<<std::endl;
   std::cout<<"tMb_tNgen = "<<tMb_tNgen<<std::endl;

   double bineta = 0.032, binphi = M_PI/50;
   double bineta2d = 6.4/150, binphi2d = M_PI/75;

   hData_eta->Scale(1./tD_tN/bineta);
   hMC_eta->Scale(1./tM_tN/bineta);

   hData_phi->Scale(1./tD_tN/binphi);
   hMC_phi->Scale(1./tM_tN/binphi);

   hData_bkg_eta->Scale(1./tDb_tN/bineta);
   hMC_bkg_eta->Scale(1./tMb_tN/bineta);

   hData_bkg_phi->Scale(1./tDb_tN/binphi);
   hMC_bkg_phi->Scale(1./tMb_tN/binphi);

   hData_etaphi_1->Scale(1./tD_tN/bineta2d/binphi2d);
   hMC_etaphi_1->Scale(1./tM_tN/bineta2d/binphi2d);
   hpp_etaphi_1->Scale(1./tpM_tN/bineta2d/binphi2d);

   hpp_phi->Scale(1./tpM_tN/binphi);
   hpp_eta->Scale(1./tpM_tN/bineta);

   hMC_etaphi_gen->Scale(1./tM_tNgen/bineta2d/binphi2d);
   hMC_bkg_etaphi_gen->Scale(1./tMb_tNgen/bineta2d/binphi2d);

   hData_bkg_etaphi_1->Scale(1./tDb_tN/bineta2d/binphi2d);
   hMC_bkg_etaphi_1->Scale(1./tMb_tN/bineta2d/binphi2d);

   hData_maxetaphi->Scale(1./tD_tN);
   hMC_maxetaphi->Scale(1./tM_tN);
   hData_bkg_maxetaphi->Scale(1./tDb_tN);
   hMC_bkg_maxetaphi->Scale(1./tMb_tN);

   hData_maxOetaphi->Scale(1./tD_tN);
   hMC_maxOetaphi->Scale(1./tM_tN);
   hData_bkg_maxOetaphi->Scale(1./tDb_tN);
   hMC_bkg_maxOetaphi->Scale(1./tMb_tN);

   hData_WTAetaphi->Scale(1./tD_tN);
   hMC_WTAetaphi->Scale(1./tM_tN);
   hData_bkg_WTAetaphi->Scale(1./tDb_tN);
   hMC_bkg_WTAetaphi->Scale(1./tMb_tN);

   hData_WTAMoreetaphi->Scale(1./tD_tN);
   hMC_WTAMoreetaphi->Scale(1./tM_tN);
   hData_bkg_WTAMoreetaphi->Scale(1./tDb_tN);
   hMC_bkg_WTAMoreetaphi->Scale(1./tMb_tN);

   hData_Zmaxetaphi->Scale(1./tD_tN);
   hMC_Zmaxetaphi->Scale(1./tM_tN);
   hData_Zbkg_maxetaphi->Scale(1./tDb_tN);
   hMC_Zbkg_maxetaphi->Scale(1./tMb_tN);

   hData_ZmaxOetaphi->Scale(1./tD_tN);
   hMC_ZmaxOetaphi->Scale(1./tM_tN);
   hData_Zbkg_maxOetaphi->Scale(1./tDb_tN);
   hMC_Zbkg_maxOetaphi->Scale(1./tMb_tN);

   hData_ZWTAetaphi->Scale(1./tD_tN);
   hMC_ZWTAetaphi->Scale(1./tM_tN);
   hData_Zbkg_WTAetaphi->Scale(1./tDb_tN);
   hMC_Zbkg_WTAetaphi->Scale(1./tMb_tN);

   hData_ZWTAMoreetaphi->Scale(1./tD_tN);
   hMC_ZWTAMoreetaphi->Scale(1./tM_tN);
   hData_Zbkg_WTAMoreetaphi->Scale(1./tDb_tN);
   hMC_Zbkg_WTAMoreetaphi->Scale(1./tMb_tN);

   std::cout<<"Rebinning..."<<std::endl;

   hData_etaphi_1->Rebin2D(10,10);
   hData_bkg_etaphi_1->Rebin2D(10,10);

   hData_etaphi_1->Scale(1./100);
   hData_bkg_etaphi_1->Scale(1./100);

   hData_MuDetaphi->Rebin2D(5,5);
   hData_bkg_MuDetaphi->Rebin2D(5,5);

   hData_MuDetaphi->Scale(1./25);
   hData_bkg_MuDetaphi->Scale(1./25);

   hData_maxetaphi->Rebin2D(5,5);
   hData_bkg_maxetaphi->Rebin2D(5,5);
   hData_maxOetaphi->Rebin2D(5,5);
   hData_bkg_maxOetaphi->Rebin2D(5,5);
   hData_WTAetaphi->Rebin2D(5,5);
   hData_bkg_WTAetaphi->Rebin2D(5,5);
   hData_WTAMoreetaphi->Rebin2D(5,5);
   hData_bkg_WTAMoreetaphi->Rebin2D(5,5);

   hData_maxetaphi->Scale(1./25);
   hData_bkg_maxetaphi->Scale(1./25);
   hData_maxOetaphi->Scale(1./25);
   hData_bkg_maxOetaphi->Scale(1./25);
   hData_WTAetaphi->Scale(1./25);
   hData_bkg_WTAetaphi->Scale(1./25);
   hData_WTAMoreetaphi->Scale(1./25);
   hData_bkg_WTAMoreetaphi->Scale(1./25);

   hData_Zmaxetaphi->Rebin2D(5,5);
   hData_Zbkg_maxetaphi->Rebin2D(5,5);
   hData_ZmaxOetaphi->Rebin2D(5,5);
   hData_Zbkg_maxOetaphi->Rebin2D(5,5);
   hData_ZWTAetaphi->Rebin2D(5,5);
   hData_Zbkg_WTAetaphi->Rebin2D(5,5);
   hData_ZWTAMoreetaphi->Rebin2D(5,5);
   hData_Zbkg_WTAMoreetaphi->Rebin2D(5,5);

   hData_Zmaxetaphi->Scale(1./25);
   hData_Zbkg_maxetaphi->Scale(1./25);
   hData_ZmaxOetaphi->Scale(1./25);
   hData_Zbkg_maxOetaphi->Scale(1./25);
   hData_ZWTAetaphi->Scale(1./25);
   hData_Zbkg_WTAetaphi->Scale(1./25);
   hData_ZWTAMoreetaphi->Scale(1./25);
   hData_Zbkg_WTAMoreetaphi->Scale(1./25);

   TH2D *hpp_etaphi_2 = (TH2D*) hpp_etaphi_1->Clone("hpp_etaphi_2");

   hpp_etaphi_1->Rebin2D(4,4);

   hMC_MuDetaphi->Rebin2D(4,4);
   hMC_bkg_MuDetaphi->Rebin2D(4,4);

   hMC_etaphi_gen->Rebin2D(4,4);
   hMC_bkg_etaphi_gen->Rebin2D(4,4);

   hpp_etaphi_1->Scale(1./16);
   hMC_MuDetaphi->Scale(1./16);
   hMC_bkg_MuDetaphi->Scale(1./16);
   
   hMC_etaphi_gen->Scale(1./16);
   hMC_bkg_etaphi_gen->Scale(1./16);

   hpp_etaphi_2->Rebin2D(10,10);
   hpp_etaphi_2->Scale(1./100);

   hMC_etaphi_1->Rebin2D(10,10);
   hMC_bkg_etaphi_1->Rebin2D(10,10);

   hMC_etaphi_1->Scale(1./100);
   hMC_bkg_etaphi_1->Scale(1./100);
   
   hMC_maxetaphi->Rebin2D(4,4);
   hMC_bkg_maxetaphi->Rebin2D(4,4);
   hMC_maxOetaphi->Rebin2D(4,4);
   hMC_bkg_maxOetaphi->Rebin2D(4,4);
   hMC_WTAetaphi->Rebin2D(4,4);
   hMC_bkg_WTAetaphi->Rebin2D(4,4);
   hMC_WTAMoreetaphi->Rebin2D(4,4);
   hMC_bkg_WTAMoreetaphi->Rebin2D(4,4);
   hMC_Zmaxetaphi->Rebin2D(4,4);
   hMC_Zbkg_maxetaphi->Rebin2D(4,4);
   hMC_ZmaxOetaphi->Rebin2D(4,4);
   hMC_Zbkg_maxOetaphi->Rebin2D(4,4);
   hMC_ZWTAetaphi->Rebin2D(4,4);
   hMC_Zbkg_WTAetaphi->Rebin2D(4,4);
   hMC_ZWTAMoreetaphi->Rebin2D(4,4);
   hMC_Zbkg_WTAMoreetaphi->Rebin2D(4,4);

   hMC_maxetaphi->Scale(1./16);
   hMC_bkg_maxetaphi->Scale(1./16);
   hMC_maxOetaphi->Scale(1./16);
   hMC_bkg_maxOetaphi->Scale(1./16);
   hMC_WTAetaphi->Scale(1./16);
   hMC_bkg_WTAetaphi->Scale(1./16);
   hMC_WTAMoreetaphi->Scale(1./16);
   hMC_bkg_WTAMoreetaphi->Scale(1./16);
   hMC_Zmaxetaphi->Scale(1./16);
   hMC_Zbkg_maxetaphi->Scale(1./16);
   hMC_ZmaxOetaphi->Scale(1./16);
   hMC_Zbkg_maxOetaphi->Scale(1./16);
   hMC_ZWTAetaphi->Scale(1./16);
   hMC_Zbkg_WTAetaphi->Scale(1./16);
   hMC_ZWTAMoreetaphi->Scale(1./16);
   hMC_Zbkg_WTAMoreetaphi->Scale(1./16);

   TH1D *hData_sb_eta = (TH1D*) hData_eta->Clone("hData_sb_eta");
   TH1D *hMC_sb_eta = (TH1D*) hMC_eta->Clone("hMC_sb_eta");
   TH1D *hData_sb_phi = (TH1D*) hData_phi->Clone("hData_sb_phi");
   TH1D *hMC_sb_phi = (TH1D*) hMC_phi->Clone("hMC_sb_phi");
   TH2D *hMC_sb_etaphi_1 = (TH2D*) hMC_etaphi_1->Clone("hMC_sb_etaphi_1");
   TH2D *hData_sb_etaphi_1 = (TH2D*) hData_etaphi_1->Clone("hData_sb_etaphi_1");

   TH2D *hMC_sb_etaphi_gen = (TH2D*) hMC_etaphi_gen->Clone("hMC_sb_etaphi_gen");
   TH2D *hMC_sbr_etaphi_gen = (TH2D*) hMC_etaphi_gen->Clone("hMC_sbr_etaphi_gen");
  
   TH1D *hData_sbr_eta = (TH1D*) hData_eta->Clone("hData_sbr_eta");
   TH1D *hMC_sbr_eta = (TH1D*) hMC_eta->Clone("hMC_sbr_eta");
   TH1D *hData_sbr_phi = (TH1D*) hData_phi->Clone("hData_sbr_phi");
   TH1D *hMC_sbr_phi = (TH1D*) hMC_phi->Clone("hMC_sbr_phi");
   TH2D *hMC_sbr_etaphi_1 = (TH2D*) hMC_etaphi_1->Clone("hMC_sbr_etaphi_1");
   TH2D *hData_sbr_etaphi_1 = (TH2D*) hData_etaphi_1->Clone("hData_sbr_etaphi_1");

   TH2D *hData_sb_maxetaphi = (TH2D*) hData_maxetaphi->Clone("hData_sb_maxetaphi");
   TH2D *hMC_sb_maxetaphi = (TH2D*) hMC_maxetaphi->Clone("hMC_sb_maxetaphi");
   TH2D *hData_sb_maxOetaphi = (TH2D*) hData_maxOetaphi->Clone("hData_sb_maxOetaphi");
   TH2D *hMC_sb_maxOetaphi = (TH2D*) hMC_maxOetaphi->Clone("hMC_sb_maxOetaphi");
   TH2D *hData_sb_WTAetaphi = (TH2D*) hData_WTAetaphi->Clone("hData_sb_WTAetaphi");
   TH2D *hMC_sb_WTAetaphi = (TH2D*) hMC_WTAetaphi->Clone("hMC_sb_WTAetaphi");
   TH2D *hData_sb_WTAMoreetaphi = (TH2D*) hData_WTAMoreetaphi->Clone("hData_sb_WTAMoreetaphi");
   TH2D *hMC_sb_WTAMoreetaphi = (TH2D*) hMC_WTAMoreetaphi->Clone("hMC_sb_WTAMoreetaphi");

   TH2D *hData_sbr_maxetaphi = (TH2D*) hData_maxetaphi->Clone("hData_sbr_maxetaphi");
   TH2D *hMC_sbr_maxetaphi = (TH2D*) hMC_maxetaphi->Clone("hMC_sbr_maxetaphi");
   TH2D *hData_sbr_maxOetaphi = (TH2D*) hData_maxOetaphi->Clone("hData_sbr_maxOetaphi");
   TH2D *hMC_sbr_maxOetaphi = (TH2D*) hMC_maxOetaphi->Clone("hMC_sbr_maxOetaphi");
   TH2D *hData_sbr_WTAetaphi = (TH2D*) hData_WTAetaphi->Clone("hData_sbr_WTAetaphi");
   TH2D *hMC_sbr_WTAetaphi = (TH2D*) hMC_WTAetaphi->Clone("hMC_sbr_WTAetaphi");
   TH2D *hData_sbr_WTAMoreetaphi = (TH2D*) hData_WTAMoreetaphi->Clone("hData_sbr_WTAMoreetaphi");
   TH2D *hMC_sbr_WTAMoreetaphi = (TH2D*) hMC_WTAMoreetaphi->Clone("hMC_sbr_WTAMoreetaphi");

   TH2D *hData_Zsb_maxetaphi = (TH2D*) hData_Zmaxetaphi->Clone("hData_Zsb_maxetaphi");
   TH2D *hMC_Zsb_maxetaphi = (TH2D*) hMC_Zmaxetaphi->Clone("hMC_Zsb_maxetaphi");
   TH2D *hData_Zsb_maxOetaphi = (TH2D*) hData_ZmaxOetaphi->Clone("hData_Zsb_maxOetaphi");
   TH2D *hMC_Zsb_maxOetaphi = (TH2D*) hMC_ZmaxOetaphi->Clone("hMC_Zsb_maxOetaphi");
   TH2D *hData_Zsb_WTAetaphi = (TH2D*) hData_ZWTAetaphi->Clone("hData_Zsb_WTAetaphi");
   TH2D *hMC_Zsb_WTAetaphi = (TH2D*) hMC_ZWTAetaphi->Clone("hMC_Zsb_WTAetaphi");
   TH2D *hData_Zsb_WTAMoreetaphi = (TH2D*) hData_ZWTAMoreetaphi->Clone("hData_Zsb_WTAMoreetaphi");
   TH2D *hMC_Zsb_WTAMoreetaphi = (TH2D*) hMC_ZWTAMoreetaphi->Clone("hMC_Zsb_WTAMoreetaphi");

   TH2D *hData_Zsbr_maxetaphi = (TH2D*) hData_Zmaxetaphi->Clone("hData_Zsbr_maxetaphi");
   TH2D *hMC_Zsbr_maxetaphi = (TH2D*) hMC_Zmaxetaphi->Clone("hMC_Zsbr_maxetaphi");
   TH2D *hData_Zsbr_maxOetaphi = (TH2D*) hData_ZmaxOetaphi->Clone("hData_Zsbr_maxOetaphi");
   TH2D *hMC_Zsbr_maxOetaphi = (TH2D*) hMC_ZmaxOetaphi->Clone("hMC_Zsbr_maxOetaphi");
   TH2D *hData_Zsbr_WTAetaphi = (TH2D*) hData_ZWTAetaphi->Clone("hData_Zsbr_WTAetaphi");
   TH2D *hMC_Zsbr_WTAetaphi = (TH2D*) hMC_ZWTAetaphi->Clone("hMC_Zsbr_WTAetaphi");
   TH2D *hData_Zsbr_WTAMoreetaphi = (TH2D*) hData_ZWTAMoreetaphi->Clone("hData_Zsbr_WTAMoreetaphi");
   TH2D *hMC_Zsbr_WTAMoreetaphi = (TH2D*) hMC_ZWTAMoreetaphi->Clone("hMC_Zsbr_WTAMoreetaphi");

   hData_sb_eta->Add(hData_bkg_eta,-1);
   hMC_sb_eta->Add(hMC_bkg_eta,-1);
   hData_sb_phi->Add(hData_bkg_phi,-1);
   hMC_sb_phi->Add(hMC_bkg_phi,-1);
   hMC_sb_etaphi_1->Add(hMC_bkg_etaphi_1,-1);
   hData_sb_etaphi_1->Add(hData_bkg_etaphi_1,-1);

   hMC_sb_etaphi_gen->Add(hMC_bkg_etaphi_gen,-1);
   hMC_sbr_etaphi_gen->Divide(hMC_bkg_etaphi_gen);

   hData_sbr_eta->Divide(hData_bkg_eta);
   hMC_sbr_eta->Divide(hMC_bkg_eta);
   hData_sbr_phi->Divide(hData_bkg_phi);
   hMC_sbr_phi->Divide(hMC_bkg_phi);
   hMC_sbr_etaphi_1->Divide(hMC_bkg_etaphi_1);
   hData_sbr_etaphi_1->Divide(hData_bkg_etaphi_1);

   hData_sb_maxetaphi->Add(hData_bkg_maxetaphi,-1);
   hMC_sb_maxetaphi->Add(hMC_bkg_maxetaphi,-1);
   hData_sb_maxOetaphi->Add(hData_bkg_maxOetaphi,-1);
   hMC_sb_maxOetaphi->Add(hMC_bkg_maxOetaphi,-1);
   hData_sb_WTAetaphi->Add(hData_bkg_WTAetaphi,-1);
   hMC_sb_WTAetaphi->Add(hMC_bkg_WTAetaphi,-1);
   hData_sb_WTAMoreetaphi->Add(hData_bkg_WTAMoreetaphi,-1);
   hMC_sb_WTAMoreetaphi->Add(hMC_bkg_WTAMoreetaphi,-1);

   hData_sbr_maxetaphi->Divide(hData_bkg_maxetaphi);
   hMC_sbr_maxetaphi->Divide(hMC_bkg_maxetaphi);
   hData_sbr_maxOetaphi->Divide(hData_bkg_maxOetaphi);
   hMC_sbr_maxOetaphi->Divide(hMC_bkg_maxOetaphi);
   hData_sbr_WTAetaphi->Divide(hData_bkg_WTAetaphi);
   hMC_sbr_WTAetaphi->Divide(hMC_bkg_WTAetaphi);
   hData_sbr_WTAMoreetaphi->Divide(hData_bkg_WTAMoreetaphi);
   hMC_sbr_WTAMoreetaphi->Divide(hMC_bkg_WTAMoreetaphi);

   hData_Zsb_maxetaphi->Add(hData_Zbkg_maxetaphi,-1);
   hMC_Zsb_maxetaphi->Add(hMC_Zbkg_maxetaphi,-1);
   hData_Zsb_maxOetaphi->Add(hData_Zbkg_maxOetaphi,-1);
   hMC_Zsb_maxOetaphi->Add(hMC_Zbkg_maxOetaphi,-1);
   hData_Zsb_WTAetaphi->Add(hData_Zbkg_WTAetaphi,-1);
   hMC_Zsb_WTAetaphi->Add(hMC_Zbkg_WTAetaphi,-1);
   hData_Zsb_WTAMoreetaphi->Add(hData_Zbkg_WTAMoreetaphi,-1);
   hMC_Zsb_WTAMoreetaphi->Add(hMC_Zbkg_WTAMoreetaphi,-1);

   hData_Zsbr_maxetaphi->Divide(hData_Zbkg_maxetaphi);
   hMC_Zsbr_maxetaphi->Divide(hMC_Zbkg_maxetaphi);
   hData_Zsbr_maxOetaphi->Divide(hData_Zbkg_maxOetaphi);
   hMC_Zsbr_maxOetaphi->Divide(hMC_Zbkg_maxOetaphi);
   hData_Zsbr_WTAetaphi->Divide(hData_Zbkg_WTAetaphi);
   hMC_Zsbr_WTAetaphi->Divide(hMC_Zbkg_WTAetaphi);
   hData_Zsbr_WTAMoreetaphi->Divide(hData_Zbkg_WTAMoreetaphi);
   hMC_Zsbr_WTAMoreetaphi->Divide(hMC_Zbkg_WTAMoreetaphi);

   int countD0 = hData_eta->GetEntries();
   std::cout<<"Data 0 = "<<countD0<<std::endl;
   int countM0 = hMC_eta->GetEntries();
   std::cout<<"MC 0 = "<<countM0<<std::endl;

   int countDb = hData_bkg_eta->GetEntries();
   std::cout<<"Data Bkg = "<<countDb<<std::endl;
   int countMb = hMC_bkg_eta->GetEntries();
   std::cout<<"MC Bkg = "<<countMb<<std::endl;

   std::cout<<"Drawing..."<<std::endl;

   hMC_eta->SetMarkerStyle(24);
   hMC_phi->SetMarkerStyle(24);
   hMC_bkg_eta->SetMarkerStyle(24);
   hMC_bkg_phi->SetMarkerStyle(24);
   hMC_sb_eta->SetMarkerStyle(24);
   hMC_sb_phi->SetMarkerStyle(24);
   hMC_sbr_eta->SetMarkerStyle(24);
   hMC_sbr_phi->SetMarkerStyle(24);

   hData_eta->SetMarkerColor(kBlack);
   hMC_eta->SetMarkerColor(kRed);
   hData_phi->SetMarkerColor(kBlack);
   hMC_phi->SetMarkerColor(kRed);

   hData_eta->SetLineColor(kBlack);
   hMC_eta->SetLineColor(kRed);
   hData_phi->SetLineColor(kBlack);
   hMC_phi->SetLineColor(kRed);

   hData_bkg_eta->SetMarkerColor(kBlack);
   hMC_bkg_eta->SetMarkerColor(kRed);
   hData_bkg_phi->SetMarkerColor(kBlack);
   hMC_bkg_phi->SetMarkerColor(kRed);

   hData_bkg_eta->SetLineColor(kBlack);
   hMC_bkg_eta->SetLineColor(kRed);
   hData_bkg_phi->SetLineColor(kBlack);
   hMC_bkg_phi->SetLineColor(kRed);

   hData_sb_eta->SetMarkerColor(kBlack);
   hMC_sb_eta->SetMarkerColor(kRed);
   hData_sb_phi->SetMarkerColor(kBlack);
   hMC_sb_phi->SetMarkerColor(kRed);

   hData_sb_eta->SetLineColor(kBlack);
   hMC_sb_eta->SetLineColor(kRed);
   hData_sb_phi->SetLineColor(kBlack);
   hMC_sb_phi->SetLineColor(kRed);

   hData_sbr_eta->SetMarkerColor(kBlack);
   hMC_sbr_eta->SetMarkerColor(kRed);
   hData_sbr_phi->SetMarkerColor(kBlack);
   hMC_sbr_phi->SetMarkerColor(kRed);

   hData_sbr_eta->SetLineColor(kBlack);
   hMC_sbr_eta->SetLineColor(kRed);
   hData_sbr_phi->SetLineColor(kBlack);
   hMC_sbr_phi->SetLineColor(kRed);

   if(TptL==0) TptL=TptL_min;

   TLegend leg(0.58,0.78,0.98,0.9);
   leg.AddEntry(hMC_eta ,"Monte Carlo: DYLL","lep");
   leg.AddEntry(hData_eta ,Form("Data: %s",typeofdatatext),"lep");
   leg.SetFillColorAlpha(kWhite,0);
   leg.SetLineColor(kBlack);
   leg.SetLineWidth(1);

   TLatex *pt = new TLatex(0.18,0.88,Form("%.0f %%< Centrality < %.0f %%",centL,centH));
   pt->SetTextFont(42);
   pt->SetTextSize(0.03);
   pt->SetNDC(kTRUE);

   TLatex *pt2 = new TLatex(0.18,0.82,Form("%.1f < Z p_{T} < %.1f GeV",ptL,ptH));
   pt2->SetTextFont(42);
   pt2->SetTextSize(0.03);
   pt2->SetNDC(kTRUE);

   TLatex *pt3 = new TLatex(0.18,0.76,Form("%.1f < Track p_{T} < %.1f GeV",TptL,TptH));
   pt3->SetTextFont(42);
   pt3->SetTextSize(0.03);
   pt3->SetNDC(kTRUE);

   TLatex *pt3d = new TLatex(0.03,0.94,Form("%.0f %%< Centrality < %.0f %%",centL,centH));
   pt3d->SetTextFont(42);
   pt3d->SetTextSize(0.03);
   pt3d->SetNDC(kTRUE);

   TLatex *pt3d2 = new TLatex(0.03,0.88,Form("%.1f < Z p_{T} < %.1f GeV",ptL,ptH));
   pt3d2->SetTextFont(42);
   pt3d2->SetTextSize(0.03);
   pt3d2->SetNDC(kTRUE);

   TLatex *pt3d3 = new TLatex(0.03,0.82,Form("%.1f < Track p_{T} < %.1f GeV",TptL,TptH));
   pt3d3->SetTextFont(42);
   pt3d3->SetTextSize(0.03);
   pt3d3->SetNDC(kTRUE);


   TLatex *ptN0 = new TLatex(0.1,0.97,Form("Signal N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f",tM_tN,tD_tN));
   ptN0->SetTextFont(42);
   ptN0->SetTextSize(0.03);
   ptN0->SetNDC(kTRUE);

   TLatex *ptNb = new TLatex(0.1,0.97,Form("Background N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f",tMb_tN,tDb_tN));
   ptNb->SetTextFont(42);
   ptNb->SetTextSize(0.03);
   ptNb->SetNDC(kTRUE);

   // == Start drawing == //

   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s",typeofdata));
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Deta",typeofdata));
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Dphi",typeofdata));
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/3D",typeofdata));
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/pp",typeofdata));
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/muD",typeofdata));
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/gen",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Deta/pdf",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Dphi/pdf",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/3D/pdf",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Deta/C",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Dphi/C",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/3D/C",typeofdata));


   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/maxetaphi",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/maxetaphi/C",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/maxOetaphi",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/maxOetaphi/C",typeofdata));
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/WTAetaphi",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/WTAetaphi/C",typeofdata));
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/WTAMoreetaphi",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/C",typeofdata));

   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Zmaxetaphi",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Zmaxetaphi/C",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZmaxOetaphi",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/C",typeofdata));
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZWTAetaphi",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZWTAetaphi/C",typeofdata));
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi",typeofdata));
   //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/C",typeofdata));


   // Draw eta 

   double max1 = hMC_eta->GetMaximum();
   double max2 = hData_eta->GetMaximum();
   
   if(max1<max2) hData_eta->Draw();
   else hMC_eta->Draw();
   hMC_eta->Draw("same");
   hData_eta->Draw("same");

   if(max1<max2) max1=max2;

   hMC_eta->SetXTitle("Signal |#Delta#eta_{Z,track}|");
   hData_eta->SetXTitle("Signal |#Delta#eta_{Z,track}|");
   hMC_eta->SetYTitle("dN/d#Delta#eta");
   hData_eta->SetYTitle("dN/d#Delta#eta");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_eta->SetMinimum(0);
   hMC_eta->SetMaximum(1.6*max1); 
   hData_eta->SetMinimum(0);
   hData_eta->SetMaximum(1.6*max1); 

   ptN0->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_bkg_eta->GetMaximum();
   max2 = hData_bkg_eta->GetMaximum();
   
   if(max1<max2) hData_bkg_eta->Draw();
   else hMC_bkg_eta->Draw();
   hMC_bkg_eta->Draw("same");
   hData_bkg_eta->Draw("same");

   if(max1<max2) max1=max2;

   hMC_bkg_eta->SetXTitle("Background |#Delta#eta_{Z,track}|");
   hData_bkg_eta->SetXTitle("Background |#Delta#eta_{Z,track}|");
   hMC_bkg_eta->SetYTitle("dN/d#Delta#eta");
   hData_bkg_eta->SetYTitle("dN/d#Delta#eta");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_bkg_eta->SetMinimum(0);
   hMC_bkg_eta->SetMaximum(1.6*max1); 
   hData_bkg_eta->SetMinimum(0);
   hData_bkg_eta->SetMaximum(1.6*max1); 

   ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();


   max1 = hMC_sb_eta->GetMaximum();
   max2 = hData_sb_eta->GetMaximum();

   double min1 = hMC_sb_phi->GetMinimum();
   double min2 = hData_sb_phi->GetMinimum();
   if(min2<min1) min1=min2;
   
   if(max1<max2) hData_sb_eta->Draw();
   else hMC_sb_eta->Draw();
   hMC_sb_eta->Draw("same");
   hData_sb_eta->Draw("same");

   hMC_sb_eta->SetXTitle("Signal - Background |#Delta#eta_{Z,track}|");
   hData_sb_eta->SetXTitle("Signal - Background |#Delta#eta_{Z,track}|");
   hMC_sb_eta->SetYTitle("dN/d#Delta#eta");
   hData_sb_eta->SetYTitle("dN/d#Delta#eta");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_sb_eta->SetMinimum(min1);
   hMC_sb_eta->SetMaximum(1.6*max1); 
   hData_sb_eta->SetMinimum(min1);
   hData_sb_eta->SetMaximum(1.6*max1); 

   //ptN0->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_sbr_eta->GetMaximum();
   max2 = hData_sbr_eta->GetMaximum();

   min1 = hMC_sbr_phi->GetMinimum();
   min2 = hData_sbr_phi->GetMinimum();
   if(min2<min1) min1=min2;
   
   if(max1<max2) hData_sbr_eta->Draw();
   else hMC_sbr_eta->Draw();
   hMC_sbr_eta->Draw("same");
   hData_sbr_eta->Draw("same");

   hMC_sbr_eta->SetXTitle("Signal/Background |#Delta#eta_{Z,track}|");
   hData_sbr_eta->SetXTitle("Signal/Background |#Delta#eta_{Z,track}|");
   hMC_sbr_eta->SetYTitle("dN/d#Delta#eta");
   hData_sbr_eta->SetYTitle("dN/d#Delta#eta");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_sbr_eta->SetMinimum(min1);
   hMC_sbr_eta->SetMaximum(1.6*max1); 
   hData_sbr_eta->SetMinimum(min1);
   hData_sbr_eta->SetMaximum(1.6*max1); 

   //ptN0->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_MuDeta->GetMaximum();
   max2 = hData_MuDeta->GetMaximum();
   
   if(max1<max2) hData_MuDeta->Draw();
   else hMC_MuDeta->Draw();
   hMC_MuDeta->Draw("same");
   hData_MuDeta->Draw("same");

   hMC_MuDeta->SetXTitle("Signal |#Delta#eta_{#mu#mu}|");
   hData_MuDeta->SetXTitle("Signal |#Delta#eta_{#mu#mu}|");
   hMC_MuDeta->SetYTitle("dN/d#Delta#eta");
   hData_MuDeta->SetYTitle("dN/d#Delta#eta");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_MuDeta->SetMinimum(0);
   hMC_MuDeta->SetMaximum(3.0/binnum); 
   hData_MuDeta->SetMinimum(0);
   hData_MuDeta->SetMaximum(3.0/binnum); 

   //ptN0->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_bkg_MuDeta->GetMaximum();
   max2 = hData_bkg_MuDeta->GetMaximum();
   
   if(max1<max2) hData_bkg_MuDeta->Draw();
   else hMC_bkg_MuDeta->Draw();
   hMC_bkg_MuDeta->Draw("same");
   hData_bkg_MuDeta->Draw("same");

   hMC_bkg_eta->SetXTitle("Background |#Delta#eta_{#mu#mu}|");
   hData_bkg_eta->SetXTitle("Background |#Delta#eta_{#mu#mu}|");
   hMC_bkg_eta->SetYTitle("dN/d#Delta#eta");
   hData_bkg_eta->SetYTitle("dN/d#Delta#eta");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_bkg_MuDeta->SetMinimum(0);
   hMC_bkg_MuDeta->SetMaximum(3.0/binnum); 
   hData_bkg_MuDeta->SetMinimum(0);
   hData_bkg_MuDeta->SetMaximum(3.0/binnum); 

   //ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_phi->GetMaximum();
   max2 = hData_phi->GetMaximum();
   
   if(max1<max2) hData_phi->Draw();
   else hMC_phi->Draw();
   hMC_phi->Draw("same");
   hData_phi->Draw("same");

   if(max1<max2) max1=max2;

   hMC_phi->SetXTitle("Signal #Delta#phi_{Z,track}");
   hData_phi->SetXTitle("Signal #Delta#phi_{Z,track}");
   hMC_phi->SetYTitle("dN/d#Delta#phi");
   hData_phi->SetYTitle("dN/d#Delta#phi");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_phi->SetMinimum(0);
   hMC_phi->SetMaximum(1.6*max1);
   hData_phi->SetMinimum(0);
   hData_phi->SetMaximum(1.6*max1);

   ptN0->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_bkg_phi->GetMaximum();
   max2 = hData_bkg_phi->GetMaximum();
   
   if(max1<max2) hData_bkg_phi->Draw();
   else hMC_bkg_phi->Draw();
   hMC_bkg_phi->Draw("same");
   hData_bkg_phi->Draw("same");

   if(max1<max2) max1=max2;

   hMC_bkg_phi->SetXTitle("Background #Delta#phi_{Z,track}");
   hData_bkg_phi->SetXTitle("Background #Delta#phi_{Z,track}");
   hMC_bkg_phi->SetYTitle("dN/d#Delta#phi");
   hData_bkg_phi->SetYTitle("dN/d#Delta#phi");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_bkg_phi->SetMinimum(0);
   hMC_bkg_phi->SetMaximum(1.6*max1);
   hData_bkg_phi->SetMinimum(0);
   hData_bkg_phi->SetMaximum(1.6*max1);

   ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_sb_phi->GetMaximum();
   max2 = hData_sb_phi->GetMaximum();

   min1 = hMC_sb_phi->GetMinimum();
   min2 = hData_sb_phi->GetMinimum();
   if(min2<min1) min1=min2;
   
   if(max1<max2) hData_sb_phi->Draw();
   else hMC_sb_phi->Draw();
   hMC_sb_phi->Draw("same");
   hData_sb_phi->Draw("same");

   if(max1<max2) max1=max2;

   hMC_sb_phi->SetXTitle("Signal - Background #Delta#phi_{Z,track}");
   hData_sb_phi->SetXTitle("Signal - Background #Delta#phi_{Z,track}");
   hMC_sb_phi->SetYTitle("dN/d#Delta#phi");
   hData_sb_phi->SetYTitle("dN/d#Delta#phi");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_sb_phi->SetMinimum(min1);
   hMC_sb_phi->SetMaximum(1.6*max1);
   hData_sb_phi->SetMinimum(min1);
   hData_sb_phi->SetMaximum(1.6*max1);

   //ptN0->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   TH1D *hMC_phi_com = (TH1D*) hMC_phi->Clone("hMC_phi_com");
   TH1D *hMC_bkg_phi_com = (TH1D*) hMC_bkg_phi->Clone("hMC_bkg_phi_com");
   TH1D *hMC_sb_phi_com = (TH1D*) hMC_sb_phi->Clone("hMC_sb_phi_com");
   TH1D *hpp_phi_com = (TH1D*) hpp_phi->Clone("hpp_phi_com");
/*
   TH1D *hMC_phi_com = new TH1D("hMC_phi_com","",20,0,M_PI);
   TH1D *hMC_bkg_phi_com = new TH1D("hMC_bkg_phi_com","",20,0,M_PI);
   TH1D *hMC_sb_phi_com = new TH1D("hMC_sb_phi_com","",20,0,M_PI);
   TH1D *hpp_phi_com = new TH1D("hpp_phi_com","",20,0,M_PI);

   for (int bin=1; bin<=hMC_phi->GetNbinsX(); bin++) {
     double x = hMC_phi->GetBinCenter(bin);
     double y = hMC_phi->GetBinContent(bin);
     //double err = hMC_phi->SetBinError(bin);
     double newX = (x < 0) ? fabs(x) : ((x > M_PI) ? 2*M_PI - x : x); // apply the modifications
     hMC_phi_com->Fill(newX, y);
   }

   for (int bin=1; bin<=hMC_bkg_phi->GetNbinsX(); bin++) {
     double x = hMC_bkg_phi->GetBinCenter(bin);
     double y = hMC_bkg_phi->GetBinContent(bin);
     double newX = (x < 0) ? fabs(x) : ((x > M_PI) ? 2*M_PI - x : x); // apply the modifications
     hMC_bkg_phi_com->Fill(newX, y);
   }

   for (int bin=1; bin<=hMC_sb_phi->GetNbinsX(); bin++) {
     double x = hMC_sb_phi->GetBinCenter(bin);
     double y = hMC_sb_phi->GetBinContent(bin);
     double newX = (x < 0) ? fabs(x) : ((x > M_PI) ? 2*M_PI - x : x); // apply the modifications
     hMC_sb_phi_com->Fill(newX, y);
   }

   for (int bin=1; bin<=hpp_phi->GetNbinsX(); bin++) {
     double x = hpp_phi->GetBinCenter(bin);
     double y = hpp_phi->GetBinContent(bin);
     double newX = (x < 0) ? fabs(x) : ((x > M_PI) ? 2*M_PI - x : x); // apply the modifications
     hpp_phi_com->Fill(newX, y);
   }
*/

   
   hMC_phi_com->GetXaxis()->SetRangeUser(0,M_PI);
   hMC_bkg_phi_com->GetXaxis()->SetRangeUser(0,M_PI);
   hMC_sb_phi_com->GetXaxis()->SetRangeUser(0,M_PI);
   hpp_phi_com->GetXaxis()->SetRangeUser(0,M_PI);


   max1 = hMC_phi_com->GetMaximum();
   max2 = hMC_bkg_phi_com->GetMaximum();

   hMC_phi_com->SetMarkerColor(kBlack);
   hMC_bkg_phi_com->SetMarkerColor(kBlue);
   hMC_sb_phi_com->SetMarkerColor(kRed);

   hMC_phi_com->SetLineColor(kBlack);
   hMC_bkg_phi_com->SetLineColor(kBlue);
   hMC_sb_phi_com->SetLineColor(kRed);
   hpp_phi_com->SetLineColor(kBlack);

   hMC_phi_com->SetMarkerStyle(kFullCircle);
   hMC_bkg_phi_com->SetMarkerStyle(kFullCircle);
   hMC_sb_phi_com->SetMarkerStyle(kFullCircle);

   hpp_phi_com->SetLineWidth(2);

   
   if(max1<max2) hMC_bkg_phi_com->Draw("ep");
   else hMC_phi_com->Draw("ep");
   hMC_phi_com->Draw("ep same");
   hMC_bkg_phi_com->Draw("ep same");

   hMC_sb_phi_com->Draw("ep same");
   hpp_phi_com->Draw("hist same");

   if(max1<max2) max1=max2;

   hMC_phi_com->SetXTitle("#Delta#phi_{Z,track}");
   hMC_bkg_phi_com->SetXTitle("#Delta#phi_{Z,track}");
   hMC_phi_com->SetYTitle("dN/d#Delta#phi");
   hMC_bkg_phi_com->SetYTitle("dN/d#Delta#phi");

   TLegend leg1(0.58,0.68,0.98,0.9);
   leg1.AddEntry(hMC_phi_com ,"raw","lep");
   leg1.AddEntry(hMC_bkg_phi_com ,"bkg","lep");
   leg1.AddEntry(hMC_sb_phi_com ,"raw-bkg","lep");
   leg1.AddEntry(hpp_phi_com ,"pp","l");
   leg1.SetFillColorAlpha(kWhite,0);
   leg1.SetLineColor(kBlack);
   leg1.SetLineWidth(1);
   leg1.Draw();

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   //std::cout<<"max1 = "<<max1<<std::endl;
   //hMC_phi_com->SetMinimum(0);
   hMC_phi_com->SetMaximum(max1);
   //hMC_bkg_phi_com->SetMinimum(0);
   hMC_bkg_phi_com->SetMaximum(max1);
/*
   if(ptL==30&&centL==0&&centH==30){
    hMC_phi_com->SetMaximum(max1);
    hMC_bkg_phi_com->SetMaximum(max1);
   }else if(ptL==30&&centL==30&&centH==50){
    hMC_phi_com->SetMaximum(max1/1.6);
    hMC_bkg_phi_com->SetMaximum(max1/1.6);
   }
*/
   //hMC_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);
   //hMC_bkg_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);
   //hMC_sb_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);
   //hpp_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);

   //ptN0->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogy();
   hMC_phi_com->SetMinimum(0.01);
   hMC_bkg_phi_com->SetMinimum(0.01);
   hMC_sb_phi_com->SetMinimum(0.01);
   hpp_phi_com->SetMinimum(0.01);
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_comlog_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicomlog.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogy(0);
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_sbr_phi->GetMaximum();
   max2 = hData_sbr_phi->GetMaximum();

   min1 = hMC_sbr_phi->GetMinimum();
   min2 = hData_sbr_phi->GetMinimum();
   if(min2<min1) min1=min2;
   
   if(max1<max2) hData_sbr_phi->Draw();
   else hMC_sbr_phi->Draw();
   hMC_sbr_phi->Draw("same");
   hData_sbr_phi->Draw("same");

   if(max1<max2) max1=max2;

   hMC_sbr_phi->SetXTitle("Signal/Background #Delta#phi_{Z,track}");
   hData_sbr_phi->SetXTitle("Signal/Background #Delta#phi_{Z,track}");
   hMC_sbr_phi->SetYTitle("dN/d#Delta#phi");
   hData_sbr_phi->SetYTitle("dN/d#Delta#phi");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_sbr_phi->SetMinimum(min1);
   hMC_sbr_phi->SetMaximum(1.6*max1);
   hData_sbr_phi->SetMinimum(min1);
   hData_sbr_phi->SetMaximum(1.6*max1);

   //ptN0->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_MuDphi->GetMaximum();
   max2 = hData_MuDphi->GetMaximum();
   
   if(max1<max2) hData_MuDphi->Draw();
   else hMC_MuDphi->Draw();
   hMC_MuDphi->Draw("same");
   hData_MuDphi->Draw("same");

   hMC_MuDphi->SetXTitle("Signal |#Delta#phi_{#mu#mu}|");
   hData_MuDphi->SetXTitle("Signal |#Delta#phi_{#mu#mu}|");
   hMC_MuDphi->SetYTitle("dN/d#Delta#phi");
   hData_MuDphi->SetYTitle("dN/d#Delta#phi");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_MuDphi->SetMinimum(0);
   hMC_MuDphi->SetMaximum(3.0/binnum); 
   hData_MuDphi->SetMinimum(0);
   hData_MuDphi->SetMaximum(3.0/binnum); 

   //ptN0->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_bkg_MuDphi->GetMaximum();
   max2 = hData_bkg_MuDphi->GetMaximum();
   
   if(max1<max2) hData_bkg_MuDphi->Draw();
   else hMC_bkg_MuDphi->Draw();
   hMC_bkg_MuDphi->Draw("same");
   hData_bkg_MuDphi->Draw("same");

   hMC_bkg_phi->SetXTitle("Background |#Delta#phi_{#mu#mu}|");
   hData_bkg_phi->SetXTitle("Background |#Delta#phi_{#mu#mu}|");
   hMC_bkg_phi->SetYTitle("dN/d#Delta#phi");
   hData_bkg_phi->SetYTitle("dN/d#Delta#phi");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_bkg_MuDphi->SetMinimum(0);
   hMC_bkg_MuDphi->SetMaximum(3.0/binnum); 
   hData_bkg_MuDphi->SetMinimum(0);
   hData_bkg_MuDphi->SetMaximum(3.0/binnum); 

   //ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->SetCanvasSize(1400,800);
   c->Divide(2);
   c->cd(1);

   hMC_etaphi_1->Draw("lego20");
   hMC_etaphi_1->GetYaxis()->SetTitle("Signal MC #Delta#phi_{Z,track}");
   hMC_etaphi_1->GetXaxis()->SetTitle("Signal MC #Delta#eta_{Z,track}");
   hMC_etaphi_1->GetXaxis()->SetTitleSize(30);
   hMC_etaphi_1->GetYaxis()->SetTitleSize(30);
   hMC_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_etaphi_1->Draw("lego20");
   hData_etaphi_1->GetYaxis()->SetTitle("Signal Data #Delta#phi_{Z,track}");
   hData_etaphi_1->GetXaxis()->SetTitle("Signal Data #Delta#eta_{Z,track}");
   hData_etaphi_1->GetXaxis()->SetTitleSize(30);
   hData_etaphi_1->GetYaxis()->SetTitleSize(30);
   hData_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hData_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hData_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_bkg_etaphi_1->Draw("lego20");
   hMC_bkg_etaphi_1->GetYaxis()->SetTitle("Background MC #Delta#phi_{Z,track}");
   hMC_bkg_etaphi_1->GetXaxis()->SetTitle("Background MC #Delta#eta_{Z,track}");
   hMC_bkg_etaphi_1->GetXaxis()->SetTitleSize(30);
   hMC_bkg_etaphi_1->GetYaxis()->SetTitleSize(30);
   hMC_bkg_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_bkg_etaphi_1->Draw("lego20");
   hData_bkg_etaphi_1->GetYaxis()->SetTitle("Background Data #Delta#phi_{Z,track}");
   hData_bkg_etaphi_1->GetXaxis()->SetTitle("Background Data #Delta#eta_{Z,track}");
   hData_bkg_etaphi_1->GetXaxis()->SetTitleSize(30);
   hData_bkg_etaphi_1->GetYaxis()->SetTitleSize(30);
   hData_bkg_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hData_bkg_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hData_bkg_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_bkg_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sb_etaphi_1->Draw("lego20");
   hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sb_etaphi_1->Draw("lego20");
   hData_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   hData_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   hData_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hData_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hData_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hData_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hData_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sbr_etaphi_1->Draw("lego20");
   hMC_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   hMC_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   hMC_sbr_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_sbr_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sbr_etaphi_1->Draw("lego20");
   hData_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   hData_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   hData_sbr_etaphi_1->GetXaxis()->SetTitleSize(24);
   hData_sbr_etaphi_1->GetYaxis()->SetTitleSize(24);
   hData_sbr_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hData_sbr_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hData_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sbr_etaphi_1->Draw("COLZ");
   hMC_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   hMC_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   hMC_sbr_etaphi_1->GetXaxis()->SetTitleSize(48);
   hMC_sbr_etaphi_1->GetYaxis()->SetTitleSize(48);
   hMC_sbr_etaphi_1->GetXaxis()->SetTitleOffset(1);
   hMC_sbr_etaphi_1->GetYaxis()->SetTitleOffset(1);
   hMC_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   //gPad->SetTheta(60.839);
   //gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sbr_etaphi_1->Draw("COLZ");
   hData_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   hData_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   hData_sbr_etaphi_1->GetXaxis()->SetTitleSize(48);
   hData_sbr_etaphi_1->GetYaxis()->SetTitleSize(48);
   hData_sbr_etaphi_1->GetXaxis()->SetTitleOffset(1);
   hData_sbr_etaphi_1->GetYaxis()->SetTitleOffset(1);
   hData_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   //gPad->SetTheta(60.839);
   //gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_COLZ.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_COLZ.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_COLZ.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_etaphi_gen->Draw("lego20");
   hMC_etaphi_gen->GetYaxis()->SetTitle("Signal MC gen #Delta#phi_{Z,track}");
   hMC_etaphi_gen->GetXaxis()->SetTitle("Signal MC gen #Delta#eta_{Z,track}");
   hMC_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_etaphi_gen->Draw("lego20");
   hMC_bkg_etaphi_gen->GetYaxis()->SetTitle("Backgrond MC gen #Delta#phi_{Z,track}");
   hMC_bkg_etaphi_gen->GetXaxis()->SetTitle("Backgrond MC gen #Delta#eta_{Z,track}");
   hMC_bkg_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_bkg_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_bkg_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sb_etaphi_gen->Draw("lego20");
   hMC_sb_etaphi_gen->GetYaxis()->SetTitle("Signal-Background MC gen #Delta#phi_{Z,track}");
   hMC_sb_etaphi_gen->GetXaxis()->SetTitle("Signal-Background MC gen #Delta#eta_{Z,track}");
   hMC_sb_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_sbr_etaphi_gen->Draw("lego20");
   hMC_sbr_etaphi_gen->GetYaxis()->SetTitle("Signal/Backgrond MC gen #Delta#phi_{Z,track}");
   hMC_sbr_etaphi_gen->GetXaxis()->SetTitle("Signal/Backgrond MC gen #Delta#eta_{Z,track}");
   hMC_sbr_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_sbr_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_sbr_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbr_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_etaphi_gen->Draw("COLZ");
   hMC_etaphi_gen->GetYaxis()->SetTitle("Signal MC gen #Delta#phi_{Z,track}");
   hMC_etaphi_gen->GetXaxis()->SetTitle("Signal MC gen #Delta#eta_{Z,track}");
   hMC_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_etaphi_gen->GetXaxis()->SetTitleOffset(2.0);
   hMC_etaphi_gen->GetYaxis()->SetTitleOffset(1.5);
   hMC_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_etaphi_gen->Draw("COLZ");
   hMC_bkg_etaphi_gen->GetYaxis()->SetTitle("Backgrond MC gen #Delta#phi_{Z,track}");
   hMC_bkg_etaphi_gen->GetXaxis()->SetTitle("Backgrond MC gen #Delta#eta_{Z,track}");
   hMC_bkg_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_bkg_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_bkg_etaphi_gen->GetXaxis()->SetTitleOffset(2.0);
   hMC_bkg_etaphi_gen->GetYaxis()->SetTitleOffset(1.5);
   hMC_bkg_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen_COLZ.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen_COLZ.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen_COLZ.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sb_etaphi_gen->Draw("COLZ");
   hMC_sb_etaphi_gen->GetYaxis()->SetTitle("Signal-Background MC gen #Delta#phi_{Z,track}");
   hMC_sb_etaphi_gen->GetXaxis()->SetTitle("Signal-Background MC gen #Delta#eta_{Z,track}");
   hMC_sb_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_gen->GetXaxis()->SetTitleOffset(2.0);
   hMC_sb_etaphi_gen->GetYaxis()->SetTitleOffset(1.5);
   hMC_sb_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_sbr_etaphi_gen->Draw("COLZ");
   hMC_sbr_etaphi_gen->GetYaxis()->SetTitle("Signal/Backgrond MC gen #Delta#phi_{Z,track}");
   hMC_sbr_etaphi_gen->GetXaxis()->SetTitle("Signal/Backgrond MC gen #Delta#eta_{Z,track}");
   hMC_sbr_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_gen->GetXaxis()->SetTitleOffset(2.0);
   hMC_sbr_etaphi_gen->GetYaxis()->SetTitleOffset(1.5);
   hMC_sbr_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbr_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub_COLZ.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub_COLZ.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub_COLZ.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->SetCanvasSize(2000,800);
   c->Divide(3);
   c->cd(1);

   hMC_sb_etaphi_1->Draw("lego20");
   hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sb_etaphi_1->Draw("lego20");
   hData_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   hData_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   hData_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hData_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hData_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hData_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hData_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);
   hpp_etaphi_1->Draw("lego20");
   hpp_etaphi_1->GetYaxis()->SetTitle("pp MC #Delta#phi_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitle("pp MC #Delta#eta_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetYaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hpp_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hpp_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(3);
   c->cd(1);

   hMC_sb_etaphi_1->Draw("COLZ");
   hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(2.0);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.0);
   hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sb_etaphi_1->Draw("COLZ");
   hData_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   hData_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   hData_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hData_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hData_sb_etaphi_1->GetXaxis()->SetTitleOffset(2.0);
   hData_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.0);
   hData_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);
   hpp_etaphi_1->Draw("COLZ");
   hpp_etaphi_1->GetYaxis()->SetTitle("pp MC #Delta#phi_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitle("pp MC #Delta#eta_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetYaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetXaxis()->SetTitleOffset(2.0);
   hpp_etaphi_1->GetYaxis()->SetTitleOffset(2.0);
   hpp_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(3);
   c->cd(1);

   hMC_sb_etaphi_1->Draw("lego20");
   hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_sbr_etaphi_1->Draw("lego20");
   hMC_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   hMC_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   hMC_sbr_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_sbr_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);
   hpp_etaphi_1->Draw("lego20");
   hpp_etaphi_1->GetYaxis()->SetTitle("pp MC #Delta#phi_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitle("pp MC #Delta#eta_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetYaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hpp_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hpp_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(3);
   c->cd(1);

   hMC_sb_etaphi_1->Draw("COLZ");
   hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(2.0);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.0);
   hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_sbr_etaphi_1->Draw("COLZ");
   hMC_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   hMC_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   hMC_sbr_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_1->GetXaxis()->SetTitleOffset(2.0);
   hMC_sbr_etaphi_1->GetYaxis()->SetTitleOffset(2.0);
   hMC_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);
   hpp_etaphi_1->Draw("COLZ");
   hpp_etaphi_1->GetYaxis()->SetTitle("pp MC #Delta#phi_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitle("pp MC #Delta#eta_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetYaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetXaxis()->SetTitleOffset(2.0);
   hpp_etaphi_1->GetYaxis()->SetTitleOffset(2.0);
   hpp_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(3);
   c->cd(1);

   hMC_sb_etaphi_1->Draw("lego20");
   hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hpp_etaphi_1->Draw("lego20");
   hpp_etaphi_1->GetYaxis()->SetTitle("pp MC #Delta#phi_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitle("pp MC #Delta#eta_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetYaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hpp_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hpp_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);

   TH2D *hMC_sb_etaphi_2 = (TH2D*) hMC_sb_etaphi_1->Clone("hMC_sb_etaphi_2");

   hMC_sb_etaphi_2->Add(hpp_etaphi_2,-1);

   hMC_sb_etaphi_2->Draw("lego20");
   hMC_sb_etaphi_2->GetYaxis()->SetTitle("PbPb S-B MC - pp MC #Delta#phi_{Z,track}");
   hMC_sb_etaphi_2->GetXaxis()->SetTitle("PbPb S-B MC - pp MC #Delta#eta_{Z,track}");
   hMC_sb_etaphi_2->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_2->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_2->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_etaphi_2->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_etaphi_2->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_2->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/Ztrack_%s_ppsb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/pdf/Ztrack_%s_ppsb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/C/Ztrack_%s_ppsb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(3);
   c->cd(1);

   hMC_sb_etaphi_1->Draw("COLZ");
   hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(2.0);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.0);
   hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hpp_etaphi_1->Draw("COLZ");
   hpp_etaphi_1->GetYaxis()->SetTitle("pp MC #Delta#phi_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitle("pp MC #Delta#eta_{Z,track} (NPU=0)");
   hpp_etaphi_1->GetXaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetYaxis()->SetTitleSize(24);
   hpp_etaphi_1->GetXaxis()->SetTitleOffset(2.0);
   hpp_etaphi_1->GetYaxis()->SetTitleOffset(2.0);
   hpp_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);

   hMC_sb_etaphi_2->Draw("COLZ");
   hMC_sb_etaphi_2->GetYaxis()->SetTitle("PbPb S-B MC - pp MC #Delta#phi_{Z,track}");
   hMC_sb_etaphi_2->GetXaxis()->SetTitle("PbPb S-B MC - pp MC #Delta#eta_{Z,track}");
   hMC_sb_etaphi_2->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_2->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_2->GetXaxis()->SetTitleOffset(2.0);
   hMC_sb_etaphi_2->GetYaxis()->SetTitleOffset(2.0);
   hMC_sb_etaphi_2->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_etaphi_2->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/Ztrack_%s_ppsb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_COLZ.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/pdf/Ztrack_%s_ppsb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_COLZ.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/C/Ztrack_%s_ppsb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_COLZ.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->SetCanvasSize(1400,800);

   c->Divide(2);
   c->cd(1);
   hMC_MuDetaphi->Draw("lego20");
   hMC_MuDetaphi->GetYaxis()->SetTitle("Signal MC #Delta#phi_{#mu,#mu}");
   hMC_MuDetaphi->GetXaxis()->SetTitle("Signal MC #Delta#eta_{#mu,#mu}");
   hMC_MuDetaphi->GetXaxis()->SetTitleSize(30);
   hMC_MuDetaphi->GetYaxis()->SetTitleSize(30);
   hMC_MuDetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_MuDetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_MuDetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_MuDetaphi->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_MuDetaphi->Draw("lego20");
   hData_MuDetaphi->GetYaxis()->SetTitle("Signal Data #Delta#phi_{#mu,#mu}");
   hData_MuDetaphi->GetXaxis()->SetTitle("Signal Data #Delta#eta_{#mu,#mu}");
   hData_MuDetaphi->GetXaxis()->SetTitleSize(30);
   hData_MuDetaphi->GetYaxis()->SetTitleSize(30);
   hData_MuDetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_MuDetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_MuDetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_MuDetaphi->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_bkg_MuDetaphi->Draw("lego20");
   hMC_bkg_MuDetaphi->GetYaxis()->SetTitle("Background MC #Delta#phi_{#mu,#mu}");
   hMC_bkg_MuDetaphi->GetXaxis()->SetTitle("Background MC #Delta#eta_{#mu,#mu}");
   hMC_bkg_MuDetaphi->GetXaxis()->SetTitleSize(30);
   hMC_bkg_MuDetaphi->GetYaxis()->SetTitleSize(30);
   hMC_bkg_MuDetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_MuDetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_MuDetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_MuDetaphi->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_bkg_MuDetaphi->Draw("lego20");
   hData_bkg_MuDetaphi->GetYaxis()->SetTitle("Background Data #Delta#phi_{#mu,#mu}");
   hData_bkg_MuDetaphi->GetXaxis()->SetTitle("Background Data #Delta#eta_{#mu,#mu}");
   hData_bkg_MuDetaphi->GetXaxis()->SetTitleSize(30);
   hData_bkg_MuDetaphi->GetYaxis()->SetTitleSize(30);
   hData_bkg_MuDetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_bkg_MuDetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_bkg_MuDetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_bkg_MuDetaphi->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   int MCNbinsX = hMC_sbr_etaphi_1->GetNbinsX();
   int DataNbinsX = hMC_sbr_etaphi_1->GetNbinsX();

   TH1D* hMC_sbr_etaphi_projphi = (TH1D*) hMC_sbr_etaphi_1->ProjectionY("hMC_sbr_etaphi_projphi",1,MCNbinsX);
   TH1D* hData_sbr_etaphi_projphi = (TH1D*) hData_sbr_etaphi_1->ProjectionY("hData_sbr_etaphi_projphi",1,DataNbinsX);

   hMC_sbr_etaphi_projphi->Scale(1./MCNbinsX);
   hData_sbr_etaphi_projphi->Scale(1./DataNbinsX);

   hMC_sbr_etaphi_projphi->Draw("COLZ");
   hMC_sbr_etaphi_projphi->GetXaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track} (projection)");
   hMC_sbr_etaphi_projphi->GetXaxis()->SetTitleSize(30);
   hMC_sbr_etaphi_projphi->GetXaxis()->SetLabelSize(24);
   hMC_sbr_etaphi_projphi->GetXaxis()->SetTitleOffset(1.5);
   hMC_sbr_etaphi_projphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbr_etaphi_projphi->GetYaxis()->SetTitle("dN/d#Delta#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   c->cd(2);
   hData_sbr_etaphi_projphi->Draw("COLZ");
   hData_sbr_etaphi_projphi->GetXaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track} (projection)");
   hData_sbr_etaphi_projphi->GetXaxis()->SetTitleSize(30);
   hData_sbr_etaphi_projphi->GetXaxis()->SetLabelSize(24);
   hData_sbr_etaphi_projphi->GetXaxis()->SetTitleOffset(1.5);
   hData_sbr_etaphi_projphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sbr_etaphi_projphi->GetYaxis()->SetTitle("dN/d#Delta#phi");

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   int MCNbinsY = hMC_sbr_etaphi_1->GetNbinsY();
   int DataNbinsY = hMC_sbr_etaphi_1->GetNbinsY();

   TH1D* hMC_sbr_etaphi_projeta = (TH1D*) hMC_sbr_etaphi_1->ProjectionX("hMC_sbr_etaphi_projeta",1,(int) MCNbinsY/2);
   TH1D* hData_sbr_etaphi_projeta = (TH1D*) hData_sbr_etaphi_1->ProjectionX("hData_sbr_etaphi_projeta",1,(int) DataNbinsY/2);

   hMC_sbr_etaphi_projeta->Scale(2./MCNbinsY);
   hData_sbr_etaphi_projeta->Scale(2./DataNbinsY);

   hMC_sbr_etaphi_projeta->Draw("COLZ");
   hMC_sbr_etaphi_projeta->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track} (projection)");
   hMC_sbr_etaphi_projeta->GetXaxis()->SetTitleSize(30);
   hMC_sbr_etaphi_projeta->GetXaxis()->SetLabelSize(24);
   hMC_sbr_etaphi_projeta->GetXaxis()->SetTitleOffset(1.5);
   hMC_sbr_etaphi_projeta->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbr_etaphi_projeta->GetYaxis()->SetTitle("dN/d#Delta#eta");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   c->cd(2);
   hData_sbr_etaphi_projeta->Draw("COLZ");
   hData_sbr_etaphi_projeta->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track} (projection)");
   hData_sbr_etaphi_projeta->GetXaxis()->SetTitleSize(30);
   hData_sbr_etaphi_projeta->GetXaxis()->SetLabelSize(24);
   hData_sbr_etaphi_projeta->GetXaxis()->SetTitleOffset(1.5);
   hData_sbr_etaphi_projeta->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sbr_etaphi_projeta->GetYaxis()->SetTitle("dN/d#Delta#eta");

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projeta.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projeta.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projeta.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   // Don't draw other axes yet 
/*
   c->Divide(2);
   c->cd(1);

   hMC_maxetaphi->Draw("lego20");
   hMC_maxetaphi->GetYaxis()->SetTitle("Signal MC #Delta#phi_{Z,track}");
   hMC_maxetaphi->GetXaxis()->SetTitle("Signal MC #Delta#eta_{Z,track}");
   hMC_maxetaphi->GetXaxis()->SetTitleSize(30);
   hMC_maxetaphi->GetYaxis()->SetTitleSize(30);
   hMC_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_maxetaphi->Draw("lego20");
   hData_maxetaphi->GetYaxis()->SetTitle("Signal Data #Delta#phi_{Z,track}");
   hData_maxetaphi->GetXaxis()->SetTitle("Signal Data #Delta#eta_{Z,track}");
   hData_maxetaphi->GetXaxis()->SetTitleSize(30);
   hData_maxetaphi->GetYaxis()->SetTitleSize(30);
   hData_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_bkg_maxetaphi->Draw("lego20");
   hMC_bkg_maxetaphi->GetYaxis()->SetTitle("Background MC #Delta#phi_{Z,track}");
   hMC_bkg_maxetaphi->GetXaxis()->SetTitle("Background MC #Delta#eta_{Z,track}");
   hMC_bkg_maxetaphi->GetXaxis()->SetTitleSize(30);
   hMC_bkg_maxetaphi->GetYaxis()->SetTitleSize(30);
   hMC_bkg_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_bkg_maxetaphi->Draw("lego20");
   hData_bkg_maxetaphi->GetYaxis()->SetTitle("Background Data #Delta#phi_{Z,track}");
   hData_bkg_maxetaphi->GetXaxis()->SetTitle("Background Data #Delta#eta_{Z,track}");
   hData_bkg_maxetaphi->GetXaxis()->SetTitleSize(30);
   hData_bkg_maxetaphi->GetYaxis()->SetTitleSize(30);
   hData_bkg_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_bkg_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_bkg_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sb_maxetaphi->Draw("lego20");
   hMC_sb_maxetaphi->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   hMC_sb_maxetaphi->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   hMC_sb_maxetaphi->GetXaxis()->SetTitleSize(24);
   hMC_sb_maxetaphi->GetYaxis()->SetTitleSize(24);
   hMC_sb_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sb_maxetaphi->Draw("lego20");
   hData_sb_maxetaphi->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   hData_sb_maxetaphi->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   hData_sb_maxetaphi->GetXaxis()->SetTitleSize(24);
   hData_sb_maxetaphi->GetYaxis()->SetTitleSize(24);
   hData_sb_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_sb_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_sb_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sbr_maxetaphi->Draw("lego20");
   hMC_sbr_maxetaphi->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   hMC_sbr_maxetaphi->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   hMC_sbr_maxetaphi->GetXaxis()->SetTitleSize(24);
   hMC_sbr_maxetaphi->GetYaxis()->SetTitleSize(24);
   hMC_sbr_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sbr_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sbr_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sbr_maxetaphi->Draw("lego20");
   hData_sbr_maxetaphi->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   hData_sbr_maxetaphi->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   hData_sbr_maxetaphi->GetXaxis()->SetTitleSize(24);
   hData_sbr_maxetaphi->GetYaxis()->SetTitleSize(24);
   hData_sbr_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_sbr_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_sbr_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_maxOetaphi->Draw("lego20");
   hMC_maxOetaphi->GetYaxis()->SetTitle("Signal MC #Delta#phi_{Z,track}");
   hMC_maxOetaphi->GetXaxis()->SetTitle("Signal MC #Delta#eta_{Z,track}");
   hMC_maxOetaphi->GetXaxis()->SetTitleSize(30);
   hMC_maxOetaphi->GetYaxis()->SetTitleSize(30);
   hMC_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_maxOetaphi->Draw("lego20");
   hData_maxOetaphi->GetYaxis()->SetTitle("Signal Data #Delta#phi_{Z,track}");
   hData_maxOetaphi->GetXaxis()->SetTitle("Signal Data #Delta#eta_{Z,track}");
   hData_maxOetaphi->GetXaxis()->SetTitleSize(30);
   hData_maxOetaphi->GetYaxis()->SetTitleSize(30);
   hData_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_bkg_maxOetaphi->Draw("lego20");
   hMC_bkg_maxOetaphi->GetYaxis()->SetTitle("Background MC #Delta#phi_{Z,track}");
   hMC_bkg_maxOetaphi->GetXaxis()->SetTitle("Background MC #Delta#eta_{Z,track}");
   hMC_bkg_maxOetaphi->GetXaxis()->SetTitleSize(30);
   hMC_bkg_maxOetaphi->GetYaxis()->SetTitleSize(30);
   hMC_bkg_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_bkg_maxOetaphi->Draw("lego20");
   hData_bkg_maxOetaphi->GetYaxis()->SetTitle("Background Data #Delta#phi_{Z,track}");
   hData_bkg_maxOetaphi->GetXaxis()->SetTitle("Background Data #Delta#eta_{Z,track}");
   hData_bkg_maxOetaphi->GetXaxis()->SetTitleSize(30);
   hData_bkg_maxOetaphi->GetYaxis()->SetTitleSize(30);
   hData_bkg_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_bkg_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_bkg_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sb_maxOetaphi->Draw("lego20");
   hMC_sb_maxOetaphi->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   hMC_sb_maxOetaphi->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   hMC_sb_maxOetaphi->GetXaxis()->SetTitleSize(24);
   hMC_sb_maxOetaphi->GetYaxis()->SetTitleSize(24);
   hMC_sb_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sb_maxOetaphi->Draw("lego20");
   hData_sb_maxOetaphi->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   hData_sb_maxOetaphi->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   hData_sb_maxOetaphi->GetXaxis()->SetTitleSize(24);
   hData_sb_maxOetaphi->GetYaxis()->SetTitleSize(24);
   hData_sb_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_sb_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_sb_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sbr_maxOetaphi->Draw("lego20");
   hMC_sbr_maxOetaphi->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   hMC_sbr_maxOetaphi->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   hMC_sbr_maxOetaphi->GetXaxis()->SetTitleSize(24);
   hMC_sbr_maxOetaphi->GetYaxis()->SetTitleSize(24);
   hMC_sbr_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sbr_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sbr_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sbr_maxOetaphi->Draw("lego20");
   hData_sbr_maxOetaphi->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   hData_sbr_maxOetaphi->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   hData_sbr_maxOetaphi->GetXaxis()->SetTitleSize(24);
   hData_sbr_maxOetaphi->GetYaxis()->SetTitleSize(24);
   hData_sbr_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_sbr_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_sbr_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();
*/
   c->Divide(2);
   c->cd(1);

   hMC_WTAetaphi->Draw("lego20");
   hMC_WTAetaphi->GetYaxis()->SetTitle("Signal MC #Delta#phi_{axis,track}");
   hMC_WTAetaphi->GetXaxis()->SetTitle("Signal MC #Delta#eta_{axis,track}");
   hMC_WTAetaphi->GetXaxis()->SetTitleSize(30);
   hMC_WTAetaphi->GetYaxis()->SetTitleSize(30);
   hMC_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_WTAetaphi->Draw("lego20");
   hData_WTAetaphi->GetYaxis()->SetTitle("Signal Data #Delta#phi_{axis,track}");
   hData_WTAetaphi->GetXaxis()->SetTitle("Signal Data #Delta#eta_{axis,track}");
   hData_WTAetaphi->GetXaxis()->SetTitleSize(30);
   hData_WTAetaphi->GetYaxis()->SetTitleSize(30);
   hData_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_bkg_WTAetaphi->Draw("lego20");
   hMC_bkg_WTAetaphi->GetYaxis()->SetTitle("Background MC #Delta#phi_{axis,track}");
   hMC_bkg_WTAetaphi->GetXaxis()->SetTitle("Background MC #Delta#eta_{axis,track}");
   hMC_bkg_WTAetaphi->GetXaxis()->SetTitleSize(30);
   hMC_bkg_WTAetaphi->GetYaxis()->SetTitleSize(30);
   hMC_bkg_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_bkg_WTAetaphi->Draw("lego20");
   hData_bkg_WTAetaphi->GetYaxis()->SetTitle("Background Data #Delta#phi_{axis,track}");
   hData_bkg_WTAetaphi->GetXaxis()->SetTitle("Background Data #Delta#eta_{axis,track}");
   hData_bkg_WTAetaphi->GetXaxis()->SetTitleSize(30);
   hData_bkg_WTAetaphi->GetYaxis()->SetTitleSize(30);
   hData_bkg_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_bkg_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_bkg_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sb_WTAetaphi->Draw("lego20");
   hMC_sb_WTAetaphi->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{axis,track}");
   hMC_sb_WTAetaphi->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{axis,track}");
   hMC_sb_WTAetaphi->GetXaxis()->SetTitleSize(24);
   hMC_sb_WTAetaphi->GetYaxis()->SetTitleSize(24);
   hMC_sb_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sb_WTAetaphi->Draw("lego20");
   hData_sb_WTAetaphi->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{axis,track}");
   hData_sb_WTAetaphi->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{axis,track}");
   hData_sb_WTAetaphi->GetXaxis()->SetTitleSize(24);
   hData_sb_WTAetaphi->GetYaxis()->SetTitleSize(24);
   hData_sb_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_sb_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_sb_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   Int_t max_x, max_y, max_z, max_bin;
   // max_bin = hMC_sb_WTAetaphi->GetMaximumBin(max_x,max_y,max_z);
   // max1 = hMC_sb_WTAetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1);
   // hMC_sb_WTAetaphi->SetMaximum(0.0005);
   // max_bin = hData_sb_WTAetaphi->GetMaximumBin(max_x,max_y,max_z);
   // max2 = hData_sb_WTAetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1);
   // hData_sb_WTAetaphi->SetMaximum(0.0005);
   gPad->SetLogz();c->cd(1);gPad->SetLogz();
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi_zoom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogz(0);c->cd(2);gPad->SetLogz(0);
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sbr_WTAetaphi->Draw("lego20");
   hMC_sbr_WTAetaphi->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{axis,track}");
   hMC_sbr_WTAetaphi->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{axis,track}");
   hMC_sbr_WTAetaphi->GetXaxis()->SetTitleSize(24);
   hMC_sbr_WTAetaphi->GetYaxis()->SetTitleSize(24);
   hMC_sbr_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sbr_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sbr_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sbr_WTAetaphi->Draw("lego20");
   hData_sbr_WTAetaphi->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{axis,track}");
   hData_sbr_WTAetaphi->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{axis,track}");
   hData_sbr_WTAetaphi->GetXaxis()->SetTitleSize(24);
   hData_sbr_WTAetaphi->GetYaxis()->SetTitleSize(24);
   hData_sbr_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_sbr_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_sbr_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //max_bin = hMC_sbr_WTAetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max1 = hMC_sbr_WTAetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hMC_sbr_WTAetaphi->SetMaximum(0.0005);
   //max_bin = hData_sbr_WTAetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max2 = hData_sbr_WTAetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hData_sbr_WTAetaphi->SetMaximum(0.0005);
   gPad->SetLogz();c->cd(1);gPad->SetLogz();
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi_zoom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogz(0);c->cd(2);gPad->SetLogz(0);
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_WTAMoreetaphi->Draw("lego20");
   hMC_WTAMoreetaphi->GetYaxis()->SetTitle("Signal MC #Delta#phi_{axis,track}");
   hMC_WTAMoreetaphi->GetXaxis()->SetTitle("Signal MC #Delta#eta_{axis,track}");
   hMC_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   hMC_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   hMC_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_WTAMoreetaphi->Draw("lego20");
   hData_WTAMoreetaphi->GetYaxis()->SetTitle("Signal Data #Delta#phi_{axis,track}");
   hData_WTAMoreetaphi->GetXaxis()->SetTitle("Signal Data #Delta#eta_{axis,track}");
   hData_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   hData_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   hData_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH));    
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_bkg_WTAMoreetaphi->Draw("lego20");
   hMC_bkg_WTAMoreetaphi->GetYaxis()->SetTitle("Background MC #Delta#phi_{axis,track}");
   hMC_bkg_WTAMoreetaphi->GetXaxis()->SetTitle("Background MC #Delta#eta_{axis,track}");
   hMC_bkg_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   hMC_bkg_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   hMC_bkg_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_bkg_WTAMoreetaphi->Draw("lego20");
   hData_bkg_WTAMoreetaphi->GetYaxis()->SetTitle("Background Data #Delta#phi_{axis,track}");
   hData_bkg_WTAMoreetaphi->GetXaxis()->SetTitle("Background Data #Delta#eta_{axis,track}");
   hData_bkg_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   hData_bkg_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   hData_bkg_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_bkg_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_bkg_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sb_WTAMoreetaphi->Draw("lego20");
   hMC_sb_WTAMoreetaphi->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{axis,track}");
   hMC_sb_WTAMoreetaphi->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{axis,track}");
   hMC_sb_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   hMC_sb_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   hMC_sb_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sb_WTAMoreetaphi->Draw("lego20");
   hData_sb_WTAMoreetaphi->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{axis,track}");
   hData_sb_WTAMoreetaphi->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{axis,track}");
   hData_sb_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   hData_sb_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   hData_sb_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_sb_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_sb_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 

   //max_bin = hMC_sb_WTAMoreetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max1 = hMC_sb_WTAMoreetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hMC_sb_WTAMoreetaphi->SetMaximum(0.0005);
   //max_bin = hData_sb_WTAMoreetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max2 = hData_sb_WTAMoreetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hData_sb_WTAMoreetaphi->SetMaximum(0.0005);
   gPad->SetLogz();c->cd(1);gPad->SetLogz();
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi_zoom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogz(0);c->cd(2);gPad->SetLogz(0);
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sbr_WTAMoreetaphi->Draw("lego20");
   hMC_sbr_WTAMoreetaphi->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{axis,track}");
   hMC_sbr_WTAMoreetaphi->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{axis,track}");
   hMC_sbr_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   hMC_sbr_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   hMC_sbr_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sbr_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sbr_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sbr_WTAMoreetaphi->Draw("lego20");
   hData_sbr_WTAMoreetaphi->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{axis,track}");
   hData_sbr_WTAMoreetaphi->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{axis,track}");
   hData_sbr_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   hData_sbr_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   hData_sbr_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_sbr_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_sbr_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 

   //max_bin = hMC_sbr_WTAMoreetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max1 = hMC_sbr_WTAMoreetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hMC_sbr_WTAMoreetaphi->SetMaximum(0.0005);
   //max_bin = hData_sbr_WTAMoreetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max2 = hData_sbr_WTAMoreetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hData_sbr_WTAMoreetaphi->SetMaximum(0.0005);
   gPad->SetLogz();c->cd(1);gPad->SetLogz();
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi_zoom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogz(0);c->cd(2);gPad->SetLogz(0);
   c->Clear();

   /*

   c->Divide(2);
   c->cd(1);

   hMC_Zmaxetaphi->Draw("lego20");
   hMC_Zmaxetaphi->GetYaxis()->SetTitle("Signal MC #phi_{axis}");
   hMC_Zmaxetaphi->GetXaxis()->SetTitle("Signal MC #eta_{axis}");
   hMC_Zmaxetaphi->GetXaxis()->SetTitleSize(30);
   hMC_Zmaxetaphi->GetYaxis()->SetTitleSize(30);
   hMC_Zmaxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zmaxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zmaxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zmaxetaphi->Draw("lego20");
   hData_Zmaxetaphi->GetYaxis()->SetTitle("Signal Data #phi_{axis}");
   hData_Zmaxetaphi->GetXaxis()->SetTitle("Signal Data #eta_{axis}");
   hData_Zmaxetaphi->GetXaxis()->SetTitleSize(30);
   hData_Zmaxetaphi->GetYaxis()->SetTitleSize(30);
   hData_Zmaxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zmaxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zmaxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zbkg_maxetaphi->Draw("lego20");
   hMC_Zbkg_maxetaphi->GetYaxis()->SetTitle("Background MC #phi_{axis}");
   hMC_Zbkg_maxetaphi->GetXaxis()->SetTitle("Background MC #eta_{axis}");
   hMC_Zbkg_maxetaphi->GetXaxis()->SetTitleSize(30);
   hMC_Zbkg_maxetaphi->GetYaxis()->SetTitleSize(30);
   hMC_Zbkg_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zbkg_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zbkg_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zbkg_maxetaphi->Draw("lego20");
   hData_Zbkg_maxetaphi->GetYaxis()->SetTitle("Background Data #phi_{axis}");
   hData_Zbkg_maxetaphi->GetXaxis()->SetTitle("Background Data #eta_{axis}");
   hData_Zbkg_maxetaphi->GetXaxis()->SetTitleSize(30);
   hData_Zbkg_maxetaphi->GetYaxis()->SetTitleSize(30);
   hData_Zbkg_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zbkg_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zbkg_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zsb_maxetaphi->Draw("lego20");
   hMC_Zsb_maxetaphi->GetYaxis()->SetTitle("Signal - Background MC #phi_{axis}");
   hMC_Zsb_maxetaphi->GetXaxis()->SetTitle("Signal - Background MC #eta_{axis}");
   hMC_Zsb_maxetaphi->GetXaxis()->SetTitleSize(24);
   hMC_Zsb_maxetaphi->GetYaxis()->SetTitleSize(24);
   hMC_Zsb_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zsb_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zsb_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zsb_maxetaphi->Draw("lego20");
   hData_Zsb_maxetaphi->GetYaxis()->SetTitle("Signal - Background Data #phi_{axis}");
   hData_Zsb_maxetaphi->GetXaxis()->SetTitle("Signal - Background Data #eta_{axis}");
   hData_Zsb_maxetaphi->GetXaxis()->SetTitleSize(24);
   hData_Zsb_maxetaphi->GetYaxis()->SetTitleSize(24);
   hData_Zsb_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zsb_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zsb_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zsbr_maxetaphi->Draw("lego20");
   hMC_Zsbr_maxetaphi->GetYaxis()->SetTitle("Signal/Background MC #phi_{axis}");
   hMC_Zsbr_maxetaphi->GetXaxis()->SetTitle("Signal/Background MC #eta_{axis}");
   hMC_Zsbr_maxetaphi->GetXaxis()->SetTitleSize(24);
   hMC_Zsbr_maxetaphi->GetYaxis()->SetTitleSize(24);
   hMC_Zsbr_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zsbr_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zsbr_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zsbr_maxetaphi->Draw("lego20");
   hData_Zsbr_maxetaphi->GetYaxis()->SetTitle("Signal/Background Data #phi_{axis}");
   hData_Zsbr_maxetaphi->GetXaxis()->SetTitle("Signal/Background Data #eta_{axis}");
   hData_Zsbr_maxetaphi->GetXaxis()->SetTitleSize(24);
   hData_Zsbr_maxetaphi->GetYaxis()->SetTitleSize(24);
   hData_Zsbr_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zsbr_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zsbr_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_ZmaxOetaphi->Draw("lego20");
   hMC_ZmaxOetaphi->GetYaxis()->SetTitle("Signal MC #phi_{axis}");
   hMC_ZmaxOetaphi->GetXaxis()->SetTitle("Signal MC #eta_{axis}");
   hMC_ZmaxOetaphi->GetXaxis()->SetTitleSize(30);
   hMC_ZmaxOetaphi->GetYaxis()->SetTitleSize(30);
   hMC_ZmaxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_ZmaxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_ZmaxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_ZmaxOetaphi->Draw("lego20");
   hData_ZmaxOetaphi->GetYaxis()->SetTitle("Signal Data #phi_{axis}");
   hData_ZmaxOetaphi->GetXaxis()->SetTitle("Signal Data #eta_{axis}");
   hData_ZmaxOetaphi->GetXaxis()->SetTitleSize(30);
   hData_ZmaxOetaphi->GetYaxis()->SetTitleSize(30);
   hData_ZmaxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_ZmaxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_ZmaxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zbkg_maxOetaphi->Draw("lego20");
   hMC_Zbkg_maxOetaphi->GetYaxis()->SetTitle("Background MC #phi_{axis}");
   hMC_Zbkg_maxOetaphi->GetXaxis()->SetTitle("Background MC #eta_{axis}");
   hMC_Zbkg_maxOetaphi->GetXaxis()->SetTitleSize(30);
   hMC_Zbkg_maxOetaphi->GetYaxis()->SetTitleSize(30);
   hMC_Zbkg_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zbkg_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zbkg_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zbkg_maxOetaphi->Draw("lego20");
   hData_Zbkg_maxOetaphi->GetYaxis()->SetTitle("Background Data #phi_{axis}");
   hData_Zbkg_maxOetaphi->GetXaxis()->SetTitle("Background Data #eta_{axis}");
   hData_Zbkg_maxOetaphi->GetXaxis()->SetTitleSize(30);
   hData_Zbkg_maxOetaphi->GetYaxis()->SetTitleSize(30);
   hData_Zbkg_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zbkg_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zbkg_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zsb_maxOetaphi->Draw("lego20");
   hMC_Zsb_maxOetaphi->GetYaxis()->SetTitle("Signal - Background MC #phi_{axis}");
   hMC_Zsb_maxOetaphi->GetXaxis()->SetTitle("Signal - Background MC #eta_{axis}");
   hMC_Zsb_maxOetaphi->GetXaxis()->SetTitleSize(24);
   hMC_Zsb_maxOetaphi->GetYaxis()->SetTitleSize(24);
   hMC_Zsb_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zsb_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zsb_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zsb_maxOetaphi->Draw("lego20");
   hData_Zsb_maxOetaphi->GetYaxis()->SetTitle("Signal - Background Data #phi_{axis}");
   hData_Zsb_maxOetaphi->GetXaxis()->SetTitle("Signal - Background Data #eta_{axis}");
   hData_Zsb_maxOetaphi->GetXaxis()->SetTitleSize(24);
   hData_Zsb_maxOetaphi->GetYaxis()->SetTitleSize(24);
   hData_Zsb_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zsb_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zsb_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zsbr_maxOetaphi->Draw("lego20");
   hMC_Zsbr_maxOetaphi->GetYaxis()->SetTitle("Signal/Background MC #phi_{axis}");
   hMC_Zsbr_maxOetaphi->GetXaxis()->SetTitle("Signal/Background MC #eta_{axis}");
   hMC_Zsbr_maxOetaphi->GetXaxis()->SetTitleSize(24);
   hMC_Zsbr_maxOetaphi->GetYaxis()->SetTitleSize(24);
   hMC_Zsbr_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zsbr_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zsbr_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zsbr_maxOetaphi->Draw("lego20");
   hData_Zsbr_maxOetaphi->GetYaxis()->SetTitle("Signal/Background Data #phi_{axis}");
   hData_Zsbr_maxOetaphi->GetXaxis()->SetTitle("Signal/Background Data #eta_{axis}");
   hData_Zsbr_maxOetaphi->GetXaxis()->SetTitleSize(24);
   hData_Zsbr_maxOetaphi->GetYaxis()->SetTitleSize(24);
   hData_Zsbr_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zsbr_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zsbr_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   */

   c->Divide(2);
   c->cd(1);

   hMC_ZWTAetaphi->Draw("lego20");
   hMC_ZWTAetaphi->GetYaxis()->SetTitle("Signal MC #phi_{axis}");
   hMC_ZWTAetaphi->GetXaxis()->SetTitle("Signal MC #eta_{axis}");
   hMC_ZWTAetaphi->GetXaxis()->SetTitleSize(30);
   hMC_ZWTAetaphi->GetYaxis()->SetTitleSize(30);
   hMC_ZWTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_ZWTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_ZWTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_ZWTAetaphi->Draw("lego20");
   hData_ZWTAetaphi->GetYaxis()->SetTitle("Signal Data #phi_{axis}");
   hData_ZWTAetaphi->GetXaxis()->SetTitle("Signal Data #eta_{axis}");
   hData_ZWTAetaphi->GetXaxis()->SetTitleSize(30);
   hData_ZWTAetaphi->GetYaxis()->SetTitleSize(30);
   hData_ZWTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_ZWTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_ZWTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zbkg_WTAetaphi->Draw("lego20");
   hMC_Zbkg_WTAetaphi->GetYaxis()->SetTitle("Background MC #phi_{axis}");
   hMC_Zbkg_WTAetaphi->GetXaxis()->SetTitle("Background MC #eta_{axis}");
   hMC_Zbkg_WTAetaphi->GetXaxis()->SetTitleSize(30);
   hMC_Zbkg_WTAetaphi->GetYaxis()->SetTitleSize(30);
   hMC_Zbkg_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zbkg_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zbkg_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zbkg_WTAetaphi->Draw("lego20");
   hData_Zbkg_WTAetaphi->GetYaxis()->SetTitle("Background Data #phi_{axis}");
   hData_Zbkg_WTAetaphi->GetXaxis()->SetTitle("Background Data #eta_{axis}");
   hData_Zbkg_WTAetaphi->GetXaxis()->SetTitleSize(30);
   hData_Zbkg_WTAetaphi->GetYaxis()->SetTitleSize(30);
   hData_Zbkg_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zbkg_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zbkg_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zsb_WTAetaphi->Draw("lego20");
   hMC_Zsb_WTAetaphi->GetYaxis()->SetTitle("Signal - Background MC #phi_{axis}");
   hMC_Zsb_WTAetaphi->GetXaxis()->SetTitle("Signal - Background MC #eta_{axis}");
   hMC_Zsb_WTAetaphi->GetXaxis()->SetTitleSize(24);
   hMC_Zsb_WTAetaphi->GetYaxis()->SetTitleSize(24);
   hMC_Zsb_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zsb_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zsb_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zsb_WTAetaphi->Draw("lego20");
   hData_Zsb_WTAetaphi->GetYaxis()->SetTitle("Signal - Background Data #phi_{axis}");
   hData_Zsb_WTAetaphi->GetXaxis()->SetTitle("Signal - Background Data #eta_{axis}");
   hData_Zsb_WTAetaphi->GetXaxis()->SetTitleSize(24);
   hData_Zsb_WTAetaphi->GetYaxis()->SetTitleSize(24);
   hData_Zsb_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zsb_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zsb_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 

   //max_bin = hMC_Zsb_WTAetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max1 = hMC_Zsb_WTAetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hMC_Zsb_WTAetaphi->SetMaximum(0.0005);
   //max_bin = hData_Zsb_WTAetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max2 = hData_Zsb_WTAetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hData_Zsb_WTAetaphi->SetMaximum(0.0005);
   gPad->SetLogz();c->cd(1);gPad->SetLogz();
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi_zoom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogz(0);c->cd(2);gPad->SetLogz(0);
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zsbr_WTAetaphi->Draw("lego20");
   hMC_Zsbr_WTAetaphi->GetYaxis()->SetTitle("Signal/Background MC #phi_{axis}");
   hMC_Zsbr_WTAetaphi->GetXaxis()->SetTitle("Signal/Background MC #eta_{axis}");
   hMC_Zsbr_WTAetaphi->GetXaxis()->SetTitleSize(24);
   hMC_Zsbr_WTAetaphi->GetYaxis()->SetTitleSize(24);
   hMC_Zsbr_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zsbr_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zsbr_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zsbr_WTAetaphi->Draw("lego20");
   hData_Zsbr_WTAetaphi->GetYaxis()->SetTitle("Signal/Background Data #phi_{axis}");
   hData_Zsbr_WTAetaphi->GetXaxis()->SetTitle("Signal/Background Data #eta_{axis}");
   hData_Zsbr_WTAetaphi->GetXaxis()->SetTitleSize(24);
   hData_Zsbr_WTAetaphi->GetYaxis()->SetTitleSize(24);
   hData_Zsbr_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zsbr_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zsbr_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 

   //max_bin = hMC_Zsbr_WTAetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max1 = hMC_Zsbr_WTAetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hMC_Zsbr_WTAetaphi->SetMaximum(0.0005);
   //max_bin = hData_Zsbr_WTAetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max2 = hData_Zsbr_WTAetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hData_Zsbr_WTAetaphi->SetMaximum(0.0005);
   gPad->SetLogz();c->cd(1);gPad->SetLogz();
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi_zoom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogz(0);c->cd(2);gPad->SetLogz(0);
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_ZWTAMoreetaphi->Draw("lego20");
   hMC_ZWTAMoreetaphi->GetYaxis()->SetTitle("Signal MC #phi_{axis}");
   hMC_ZWTAMoreetaphi->GetXaxis()->SetTitle("Signal MC #eta_{axis}");
   hMC_ZWTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   hMC_ZWTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   hMC_ZWTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_ZWTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_ZWTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_ZWTAMoreetaphi->Draw("lego20");
   hData_ZWTAMoreetaphi->GetYaxis()->SetTitle("Signal Data #phi_{axis}");
   hData_ZWTAMoreetaphi->GetXaxis()->SetTitle("Signal Data #eta_{axis}");
   hData_ZWTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   hData_ZWTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   hData_ZWTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_ZWTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_ZWTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zbkg_WTAMoreetaphi->Draw("lego20");
   hMC_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitle("Background MC #phi_{axis}");
   hMC_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitle("Background MC #eta_{axis}");
   hMC_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   hMC_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   hMC_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zbkg_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zbkg_WTAMoreetaphi->Draw("lego20");
   hData_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitle("Background Data #phi_{axis}");
   hData_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitle("Background Data #eta_{axis}");
   hData_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   hData_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   hData_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zbkg_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zsb_WTAMoreetaphi->Draw("lego20");
   hMC_Zsb_WTAMoreetaphi->GetYaxis()->SetTitle("Signal - Background MC #phi_{axis}");
   hMC_Zsb_WTAMoreetaphi->GetXaxis()->SetTitle("Signal - Background MC #eta_{axis}");
   hMC_Zsb_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   hMC_Zsb_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   hMC_Zsb_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zsb_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zsb_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zsb_WTAMoreetaphi->Draw("lego20");
   hData_Zsb_WTAMoreetaphi->GetYaxis()->SetTitle("Signal - Background Data #phi_{axis}");
   hData_Zsb_WTAMoreetaphi->GetXaxis()->SetTitle("Signal - Background Data #eta_{axis}");
   hData_Zsb_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   hData_Zsb_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   hData_Zsb_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zsb_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zsb_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 

   //max_bin = hMC_Zsb_WTAMoreetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max1 = hMC_Zsb_WTAMoreetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hMC_Zsb_WTAMoreetaphi->SetMaximum(0.0005);
   //max_bin = hData_Zsb_WTAMoreetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max2 = hData_Zsb_WTAMoreetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hData_Zsb_WTAMoreetaphi->SetMaximum(0.0005);
   gPad->SetLogz();c->cd(1);gPad->SetLogz();
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi_zoom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogz(0);c->cd(2);gPad->SetLogz(0);
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zsbr_WTAMoreetaphi->Draw("lego20");
   hMC_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitle("Signal/Background MC #phi_{axis}");
   hMC_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitle("Signal/Background MC #eta_{axis}");
   hMC_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   hMC_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   hMC_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zsbr_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_Zsbr_WTAMoreetaphi->Draw("lego20");
   hData_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitle("Signal/Background Data #phi_{axis}");
   hData_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitle("Signal/Background Data #eta_{axis}");
   hData_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   hData_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   hData_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   hData_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   hData_Zsbr_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 

   //max_bin = hMC_Zsbr_WTAMoreetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max1 = hMC_Zsbr_WTAMoreetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hMC_Zsbr_WTAMoreetaphi->SetMaximum(0.0005);
   //max_bin = hData_Zsbr_WTAMoreetaphi->GetMaximumBin(max_x,max_y,max_z);
   //max2 = hData_Zsbr_WTAMoreetaphi->Integral(max_x-5,max_x-3,max_y-1,max_y+1)/9.;
   //hData_Zsbr_WTAMoreetaphi->SetMaximum(0.0005);
   gPad->SetLogz();c->cd(1);gPad->SetLogz();
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi_zoom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogz(0);c->cd(2);gPad->SetLogz(0);
   c->Clear();

   delete hMC_eta; hMC_eta=NULL;
   delete hData_eta; hData_eta=NULL;
   delete gROOT->FindObject("hMC_eta");
   delete gROOT->FindObject("hData_eta");

   delete hMC_bkg_eta; hMC_bkg_eta=NULL;
   delete hData_bkg_eta; hData_bkg_eta=NULL;
   delete gROOT->FindObject("hMC_bkg_eta");
   delete gROOT->FindObject("hData_bkg_eta");

   delete hMC_sb_eta; hMC_sb_eta=NULL;
   delete hData_sb_eta; hData_sb_eta=NULL;
   delete gROOT->FindObject("hMC_sb_eta");
   delete gROOT->FindObject("hData_sb_eta");

}

int main(int argc, char *argv[]){

   style();

   file_sigMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSignal_v17_PFmuon.root","read");
   //file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCBackground_v17d_10HF.root","read");
   file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSigBkg_v17d_PFmuon_350_10HF_ov20.root","read");
   file_sigDA = TFile::Open("~/eos_base/BasicPlots/GraphDataSignal_v17_PFmuon.root","read");
   //file_bkgDA = TFile::Open("~/eos_base/BasicPlots/GraphDataBackground_v17_PFmuon.root","read");
   file_bkgDA = TFile::Open("~/eos_base/BasicPlots/GraphDataSigBkg_v17d_PFmuon.root","read");
   file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMC_v17_PFmuon.root","read");

   file_sigMCgen = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen_v17_PFmuon.root","read");
   //file_bkgMCgen = TFile::Open("~/eos_base/BasicPlots/GraphMCBackgroundGen_v17_PFmuon.root","read");
   file_bkgMCgen = TFile::Open("~/eos_base/BasicPlots/GraphMCGenSigBkg_v17b_checkz.root","read");

/*
   ZtrackDraw_single(40, 20, 2000,  0, 10,  0, 1000);
   ZtrackDraw_single(40, 20, 2000, 10, 30,  0, 1000);
   ZtrackDraw_single(40, 20, 2000, 30, 50,  0, 1000);
   ZtrackDraw_single(40, 20, 2000, 50, 90,  0, 1000);
   ZtrackDraw_single(40, 20, 2000,  0, 90,  1,    2);
   ZtrackDraw_single(40, 20, 2000,  0, 90,  2,    5);
   ZtrackDraw_single(40, 20, 2000,  0, 90,  5,   10);
   ZtrackDraw_single(40, 20, 2000,  0, 90, 10,   20);
   ZtrackDraw_single(40, 20, 2000,  0, 90, 20,   50);
   ZtrackDraw_single(40, 20, 2000,  0, 90, 50,  100);
*/
   //ZtrackDraw_single(40, 40, 200,  0, 10,  1, 1000);
   //ZtrackDraw_single(40, 40, 200, 10, 30,  1, 1000);
   //ZtrackDraw_single(40, 40, 200, 30, 50,  1, 1000);
   //ZtrackDraw_single(40, 40, 200, 50, 90,  1, 1000);
//
   //ZtrackDraw_single(40, 40, 200,  0, 10,  1, 1000);
   ZtrackDraw_single(40, 40, 200,  0, 10,  1, 2);
   //ZtrackDraw_single(40, 40, 200,  0, 10,  2, 4);
   //ZtrackDraw_single(40, 40, 200,  0, 10,  4, 10);

   ZtrackDraw_single(40, 40, 200,  0, 90,  1, 2);
/*
   ZtrackDraw_single(40, 20, 2000,  0, 10, 10,   20);
   ZtrackDraw_single(40, 20, 2000, 10, 30, 10,   20);
   ZtrackDraw_single(40, 20, 2000, 30, 50, 10,   20);
   ZtrackDraw_single(40, 20, 2000, 50, 90, 10,   20);
*/
   //ZtrackDraw_single(40, 40, 200,  0, 30, 1, 1000);
   //ZtrackDraw_single(40, 40, 200,  0, 10, 1, 1000);
   //ZtrackDraw_single(40, 40, 200, 10, 30, 1, 1000);
   //ZtrackDraw_single(40, 40, 200, 30, 50, 1, 1000);
   //ZtrackDraw_single(40, 40, 200, 50, 90, 1, 1000);

   file_sigMC->Close();
   file_bkgMC->Close();
   file_sigDA->Close();
   file_bkgDA->Close();
   file_ppMC->Close();

   file_sigMCgen->Close();
   file_bkgMCgen->Close();

   return 0;

}
