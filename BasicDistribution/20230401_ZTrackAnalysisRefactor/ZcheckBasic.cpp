#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>
#include <TROOT.h>
#include <cmath>
#include <TH2D.h>
#include <TCut.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TSystem.h>
#include <TLatex.h>
#include <TChain.h>
#include <TLine.h>

double TptL_min = 0.5;

int main(int argc, char *argv[]);
void ZcheckBasic_single(int binnum,float ptL,float ptH,float centL,float centH,float TptL,float TptH);

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
  gStyle->SetLabelSize(36, "xyz");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);

  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);

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

TFile *file_sigMCgen0Sub;

const char *typeofdata = "v17d_PFMuon/20240101/SigBkg";
const char *typeofdata1 = "360_ov1";

const char *typeofdatatext = "single muon";

void ZcheckBasic_single(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000)
{

   std::cout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;
   TCanvas *c = new TCanvas("c","",1400,800);

   std::cout<<"Getting histograms..."<<std::endl;

   std::string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",ptL,ptH,centL,centH,TptL,TptH);
   std::replace(FolderName.begin(), FolderName.end(), '.', 'p');

   TH1D* hData_Zeta = (TH1D*) file_sigDA->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hMC_Zeta = (TH1D*) file_sigMC->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hpp_Zeta = (TH1D*) file_ppMC->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hData_bkg_Zeta = (TH1D*) file_bkgDA->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hMC_bkg_Zeta = (TH1D*) file_bkgMC->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hMC_Zeta_gen = (TH1D*) file_sigMCgen->Get(Form("%s/HGenZEta", FolderName.c_str()));
   TH1D* hMC_bkg_Zeta_gen = (TH1D*) file_bkgMCgen->Get(Form("%s/HGenZEta", FolderName.c_str()));
   TH1D* hMC_Zeta_gen0Sub = (TH1D*) file_sigMCgen0Sub->Get(Form("%s/HGenZEta", FolderName.c_str()));

   hData_Zeta->SetName("hData_Zeta");
   hMC_Zeta->SetName("hMC_Zeta");
   hpp_Zeta->SetName("hpp_Zeta");
   hData_bkg_Zeta->SetName("hData_bkg_Zeta");
   hMC_bkg_Zeta->SetName("hMC_bkg_Zeta");
   hMC_Zeta_gen->SetName("hMC_Zeta_gen");
   hMC_bkg_Zeta_gen->SetName("hMC_bkg_Zeta_gen");
   hMC_Zeta_gen0Sub->SetName("hMC_Zeta_gen0Sub");

   TH1D* hData_Zphi = (TH1D*) file_sigDA->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hMC_Zphi = (TH1D*) file_sigMC->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hpp_Zphi = (TH1D*) file_ppMC->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hData_bkg_Zphi = (TH1D*) file_bkgDA->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hMC_bkg_Zphi = (TH1D*) file_bkgMC->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hMC_Zphi_gen = (TH1D*) file_sigMCgen->Get(Form("%s/HGenZPhi", FolderName.c_str()));
   TH1D* hMC_bkg_Zphi_gen = (TH1D*) file_bkgMCgen->Get(Form("%s/HGenZPhi", FolderName.c_str()));
   TH1D* hMC_Zphi_gen0Sub = (TH1D*) file_sigMCgen0Sub->Get(Form("%s/HGenZPhi", FolderName.c_str()));

   hData_Zphi->SetName("hData_Zphi");
   hMC_Zphi->SetName("hMC_Zphi");
   hpp_Zphi->SetName("hpp_Zphi");
   hData_bkg_Zphi->SetName("hData_bkg_Zphi");
   hMC_bkg_Zphi->SetName("hMC_bkg_Zphi");
   hMC_Zphi_gen->SetName("hMC_Zphi_gen");
   hMC_bkg_Zphi_gen->SetName("hMC_bkg_Zphi_gen");
   hMC_Zphi_gen0Sub->SetName("hMC_Zphi_gen0Sub");

   TH2D* hData_Zetaphi = (TH2D*) file_sigDA->Get(Form("%s/HZEtaPhi", FolderName.c_str()));
   TH2D* hMC_Zetaphi = (TH2D*) file_sigMC->Get(Form("%s/HZEtaPhi", FolderName.c_str()));
   TH2D* hpp_Zetaphi = (TH2D*) file_ppMC->Get(Form("%s/HZEtaPhi", FolderName.c_str()));
   TH2D* hData_bkg_Zetaphi = (TH2D*) file_bkgDA->Get(Form("%s/HZEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_Zetaphi = (TH2D*) file_bkgMC->Get(Form("%s/HZEtaPhi", FolderName.c_str()));
   TH2D* hMC_Zetaphi_gen = (TH2D*) file_sigMCgen->Get(Form("%s/HGenZEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_Zetaphi_gen = (TH2D*) file_bkgMCgen->Get(Form("%s/HGenZEtaPhi", FolderName.c_str()));
   TH2D* hMC_Zetaphi_gen0Sub = (TH2D*) file_sigMCgen0Sub->Get(Form("%s/HGenZEtaPhi", FolderName.c_str()));

   hData_Zetaphi->SetName("hData_Zetaphi");
   hMC_Zetaphi->SetName("hMC_Zetaphi");
   hpp_Zetaphi->SetName("hpp_Zetaphi");
   hData_bkg_Zetaphi->SetName("hData_bkg_Zetaphi");
   hMC_bkg_Zetaphi->SetName("hMC_bkg_Zetaphi");
   hMC_Zetaphi_gen->SetName("hMC_Zetaphi_gen");
   hMC_bkg_Zetaphi_gen->SetName("hMC_bkg_Zetaphi_gen");
   hMC_Zetaphi_gen0Sub->SetName("hMC_Zetaphi_gen0Sub");


   TH1D* hData_Tracketa = (TH1D*) file_sigDA->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hMC_Tracketa = (TH1D*) file_sigMC->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hpp_Tracketa = (TH1D*) file_ppMC->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hData_bkg_Tracketa = (TH1D*) file_bkgDA->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hMC_bkg_Tracketa = (TH1D*) file_bkgMC->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hMC_Tracketa_gen = (TH1D*) file_sigMCgen->Get(Form("%s/HGenTrackEta", FolderName.c_str()));
   TH1D* hMC_bkg_Tracketa_gen = (TH1D*) file_bkgMCgen->Get(Form("%s/HGenTrackEta", FolderName.c_str()));
   TH1D* hMC_Tracketa_gen0Sub = (TH1D*) file_sigMCgen0Sub->Get(Form("%s/HGenTrackEta", FolderName.c_str()));

   hData_Tracketa->SetName("hData_Tracketa");
   hMC_Tracketa->SetName("hMC_Tracketa");
   hpp_Tracketa->SetName("hpp_Tracketa");
   hData_bkg_Tracketa->SetName("hData_bkg_Tracketa");
   hMC_bkg_Tracketa->SetName("hMC_bkg_Tracketa");
   hMC_Tracketa_gen->SetName("hMC_Tracketa_gen");
   hMC_bkg_Tracketa_gen->SetName("hMC_bkg_Tracketa_gen");
   hMC_Tracketa_gen0Sub->SetName("hMC_Tracketa_gen0Sub");

   TH1D* hData_Trackphi = (TH1D*) file_sigDA->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hMC_Trackphi = (TH1D*) file_sigMC->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hpp_Trackphi = (TH1D*) file_ppMC->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hData_bkg_Trackphi = (TH1D*) file_bkgDA->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hMC_bkg_Trackphi = (TH1D*) file_bkgMC->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hMC_Trackphi_gen = (TH1D*) file_sigMCgen->Get(Form("%s/HGenTrackPhi", FolderName.c_str()));
   TH1D* hMC_bkg_Trackphi_gen = (TH1D*) file_bkgMCgen->Get(Form("%s/HGenTrackPhi", FolderName.c_str()));
   TH1D* hMC_Trackphi_gen0Sub = (TH1D*) file_sigMCgen0Sub->Get(Form("%s/HGenTrackPhi", FolderName.c_str()));

   hData_Trackphi->SetName("hData_Trackphi");
   hMC_Trackphi->SetName("hMC_Trackphi");
   hpp_Trackphi->SetName("hpp_Trackphi");
   hData_bkg_Trackphi->SetName("hData_bkg_Trackphi");
   hMC_bkg_Trackphi->SetName("hMC_bkg_Trackphi");
   hMC_Trackphi_gen->SetName("hMC_Trackphi_gen");
   hMC_bkg_Trackphi_gen->SetName("hMC_bkg_Trackphi_gen");
   hMC_Trackphi_gen0Sub->SetName("hMC_Trackphi_gen0Sub");

   TH2D* hData_Tracketaphi = (TH2D*) file_sigDA->Get(Form("%s/HTrackEtaPhi", FolderName.c_str()));
   TH2D* hMC_Tracketaphi = (TH2D*) file_sigMC->Get(Form("%s/HTrackEtaPhi", FolderName.c_str()));
   TH2D* hpp_Tracketaphi = (TH2D*) file_ppMC->Get(Form("%s/HTrackEtaPhi", FolderName.c_str()));
   TH2D* hData_bkg_Tracketaphi = (TH2D*) file_bkgDA->Get(Form("%s/HTrackEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_Tracketaphi = (TH2D*) file_bkgMC->Get(Form("%s/HTrackEtaPhi", FolderName.c_str()));
   TH2D* hMC_Tracketaphi_gen = (TH2D*) file_sigMCgen->Get(Form("%s/HGenTrackEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_Tracketaphi_gen = (TH2D*) file_bkgMCgen->Get(Form("%s/HGenTrackEtaPhi", FolderName.c_str()));
   TH2D* hMC_Tracketaphi_gen0Sub = (TH2D*) file_sigMCgen0Sub->Get(Form("%s/HGenTrackEtaPhi", FolderName.c_str()));

   hData_Tracketaphi->SetName("hData_Tracketaphi");
   hMC_Tracketaphi->SetName("hMC_Tracketaphi");
   hpp_Tracketaphi->SetName("hpp_Tracketaphi");
   hData_bkg_Tracketaphi->SetName("hData_bkg_Tracketaphi");
   hMC_bkg_Tracketaphi->SetName("hMC_bkg_Tracketaphi");
   hMC_Tracketaphi_gen->SetName("hMC_Tracketaphi_gen");
   hMC_bkg_Tracketaphi_gen->SetName("hMC_bkg_Tracketaphi_gen");
   hMC_Tracketaphi_gen0Sub->SetName("hMC_Tracketaphi_gen0Sub");

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

   TNamed *nM_tNgen0Sub  = (TNamed *) file_sigMCgen0Sub->Get(Form("%s/GenEntryCount",FolderName.c_str()));

   std::string sD_tN  = (std::string) nD_tN->GetTitle();
   std::string sM_tN  = (std::string) nM_tN->GetTitle();
   std::string sDb_tN = (std::string) nDb_tN->GetTitle();
   std::string sMb_tN = (std::string) nMb_tN->GetTitle();
   std::string spM_tN = (std::string) npM_tN->GetTitle();

   std::string sM_tNgen  = (std::string) nM_tNgen->GetTitle();
   std::string sMb_tNgen = (std::string) nMb_tNgen->GetTitle();

   std::string sM_tNgen0Sub  = (std::string) nM_tNgen0Sub->GetTitle();

   float tD_tN  = std::stof(sD_tN);
   float tM_tN  = std::stof(sM_tN);
   float tDb_tN = std::stof(sDb_tN);
   float tMb_tN = std::stof(sMb_tN);
   float tpM_tN = std::stof(spM_tN);

   float tM_tNgen  = std::stof(sM_tNgen);
   float tMb_tNgen = std::stof(sMb_tNgen);

   float tM_tNgen0Sub  = std::stof(sM_tNgen0Sub);

   std::cout<<"tD_tN = "<<tD_tN<<std::endl;
   std::cout<<"tM_tN = "<<tM_tN<<std::endl;
   std::cout<<"tDb_tN = "<<tDb_tN<<std::endl;
   std::cout<<"tMb_tN = "<<tMb_tN<<std::endl;
   std::cout<<"tpM_tN = "<<tpM_tN<<std::endl;

   std::cout<<"tM_tNgen = "<<tM_tNgen<<std::endl;
   std::cout<<"tMb_tNgen = "<<tMb_tNgen<<std::endl;

   std::cout<<"tM_tNgen0Sub = "<<tM_tNgen0Sub<<std::endl;

   double bineta = 0.064, binphi = M_PI/50;
   double bineta2d = 6.4/150, binphi2d = M_PI/75;

   hData_Zeta->Scale(1./tD_tN/bineta);
   hMC_Zeta->Scale(1./tM_tN/bineta);
   hpp_Zeta->Scale(1./tpM_tN/bineta);
   hData_bkg_Zeta->Scale(1./tDb_tN/bineta);
   hMC_bkg_Zeta->Scale(1./tMb_tN/bineta);
   hMC_Zeta_gen->Scale(1./tM_tNgen/bineta);
   hMC_bkg_Zeta_gen->Scale(1./tMb_tNgen/bineta);
   hMC_Zeta_gen0Sub->Scale(1./tM_tNgen0Sub/bineta);


   hData_Zeta->Rebin(2);
   hMC_Zeta->Rebin(2);
   hpp_Zeta->Rebin(2);
   hData_bkg_Zeta->Rebin(5);
   hMC_bkg_Zeta->Rebin(5);
   hMC_Zeta_gen->Rebin(2);
   hMC_bkg_Zeta_gen->Rebin(5);
   hMC_Zeta_gen0Sub->Rebin(2);

   hData_Zeta->Scale(1./2);
   hMC_Zeta->Scale(1./2);
   hpp_Zeta->Scale(1./2);
   hData_bkg_Zeta->Scale(1./5);
   hMC_bkg_Zeta->Scale(1./5);
   hMC_Zeta_gen->Scale(1./2);
   hMC_bkg_Zeta_gen->Scale(1./5);
   hMC_Zeta_gen0Sub->Scale(1./2);


   hData_Zeta->SetMarkerStyle(24);
   hMC_Zeta->SetMarkerStyle(24);
   hpp_Zeta->SetMarkerStyle(24);
   hData_bkg_Zeta->SetMarkerStyle(24);
   hMC_bkg_Zeta->SetMarkerStyle(24);
   hMC_Zeta_gen->SetMarkerStyle(24);
   hMC_bkg_Zeta_gen->SetMarkerStyle(24);
   hMC_Zeta_gen0Sub->SetMarkerStyle(24);

   hData_Zeta->SetMarkerColor(kBlack);
   hData_bkg_Zeta->SetMarkerColor(kBlack);

   hData_Zeta->SetLineColor(kBlack);
   hMC_Zeta->SetLineColor(TColor::GetColor("#377eb8"));//blue
   hpp_Zeta->SetLineColor(TColor::GetColor("#984ea3"));//purple
   hData_bkg_Zeta->SetLineColor(kBlack);
   hMC_bkg_Zeta->SetLineColor(TColor::GetColor("#377eb8"));//blue
   hMC_Zeta_gen->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_bkg_Zeta_gen->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_Zeta_gen0Sub->SetLineColor(TColor::GetColor("#4daf4a"));//green

   hData_Zeta->SetLineWidth(2);
   hMC_Zeta->SetLineWidth(2);
   hpp_Zeta->SetLineWidth(2);
   hData_bkg_Zeta->SetLineWidth(2);
   hMC_bkg_Zeta->SetLineWidth(2);
   hMC_Zeta_gen->SetLineWidth(2);
   hMC_bkg_Zeta_gen->SetLineWidth(2);
   hMC_Zeta_gen0Sub->SetLineWidth(2);

   hData_Tracketa->Scale(1./tD_tN/bineta);
   hMC_Tracketa->Scale(1./tM_tN/bineta);
   hpp_Tracketa->Scale(1./tpM_tN/bineta);
   hData_bkg_Tracketa->Scale(1./tDb_tN/bineta);
   hMC_bkg_Tracketa->Scale(1./tMb_tN/bineta);
   hMC_Tracketa_gen->Scale(1./tM_tNgen/bineta);
   hMC_bkg_Tracketa_gen->Scale(1./tMb_tNgen/bineta);
   hMC_Tracketa_gen0Sub->Scale(1./tM_tNgen0Sub/bineta);

   hData_Tracketa->Rebin(5);
   hMC_Tracketa->Rebin(5);
   hpp_Tracketa->Rebin(5);
   hData_bkg_Tracketa->Rebin(5);
   hMC_bkg_Tracketa->Rebin(5);
   hMC_Tracketa_gen->Rebin(5);
   hMC_bkg_Tracketa_gen->Rebin(5);
   hMC_Tracketa_gen0Sub->Rebin(5);

   hData_Tracketa->Scale(1./5);
   hMC_Tracketa->Scale(1./5);
   hpp_Tracketa->Scale(1./5);
   hData_bkg_Tracketa->Scale(1./5);
   hMC_bkg_Tracketa->Scale(1./5);
   hMC_Tracketa_gen->Scale(1./5);
   hMC_bkg_Tracketa_gen->Scale(1./5);
   hMC_Tracketa_gen0Sub->Scale(1./5);


   hData_Tracketa->SetMarkerStyle(24);
   hMC_Tracketa->SetMarkerStyle(24);
   hpp_Tracketa->SetMarkerStyle(24);
   hData_bkg_Tracketa->SetMarkerStyle(24);
   hMC_bkg_Tracketa->SetMarkerStyle(24);
   hMC_Tracketa_gen->SetMarkerStyle(24);
   hMC_bkg_Tracketa_gen->SetMarkerStyle(24);
   hMC_Tracketa_gen0Sub->SetMarkerStyle(24);

   hData_Tracketa->SetMarkerColor(kBlack);
   hData_bkg_Tracketa->SetMarkerColor(kBlack);

   hData_Tracketa->SetLineColor(kBlack);
   hMC_Tracketa->SetLineColor(TColor::GetColor("#377eb8"));//blue
   hpp_Tracketa->SetLineColor(TColor::GetColor("#984ea3"));//purple
   hData_bkg_Tracketa->SetLineColor(kBlack);
   hMC_bkg_Tracketa->SetLineColor(TColor::GetColor("#377eb8"));//blue
   hMC_Tracketa_gen->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_bkg_Tracketa_gen->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_Tracketa_gen0Sub->SetLineColor(TColor::GetColor("#4daf4a"));//green

   hData_Tracketa->SetLineWidth(2);
   hMC_Tracketa->SetLineWidth(2);
   hpp_Tracketa->SetLineWidth(2);
   hData_bkg_Tracketa->SetLineWidth(2);
   hMC_bkg_Tracketa->SetLineWidth(2);
   hMC_Tracketa_gen->SetLineWidth(2);
   hMC_bkg_Tracketa_gen->SetLineWidth(2);
   hMC_Tracketa_gen0Sub->SetLineWidth(2);

   hData_Zphi->Scale(1./tD_tN/binphi);
   hMC_Zphi->Scale(1./tM_tN/binphi);
   hpp_Zphi->Scale(1./tpM_tN/binphi);
   hData_bkg_Zphi->Scale(1./tDb_tN/binphi);
   hMC_bkg_Zphi->Scale(1./tMb_tN/binphi);
   hMC_Zphi_gen->Scale(1./tM_tNgen/binphi);
   hMC_bkg_Zphi_gen->Scale(1./tMb_tNgen/binphi);
   hMC_Zphi_gen0Sub->Scale(1./tM_tNgen0Sub/binphi);

   hData_Zphi->Rebin(2);
   hMC_Zphi->Rebin(2);
   hpp_Zphi->Rebin(2);
   hData_bkg_Zphi->Rebin(5);
   hMC_bkg_Zphi->Rebin(5);
   hMC_Zphi_gen->Rebin(2);
   hMC_bkg_Zphi_gen->Rebin(5);
   hMC_Zphi_gen0Sub->Rebin(2);


   hData_Zphi->SetMarkerStyle(24);
   hMC_Zphi->SetMarkerStyle(24);
   hpp_Zphi->SetMarkerStyle(24);
   hData_bkg_Zphi->SetMarkerStyle(24);
   hMC_bkg_Zphi->SetMarkerStyle(24);
   hMC_Zphi_gen->SetMarkerStyle(24);
   hMC_bkg_Zphi_gen->SetMarkerStyle(24);
   hMC_Zphi_gen0Sub->SetMarkerStyle(24);

   hData_Zphi->SetMarkerColor(kBlack);
   hData_bkg_Zphi->SetMarkerColor(kBlack);

   hData_Zphi->SetLineColor(kBlack);
   hMC_Zphi->SetLineColor(TColor::GetColor("#377eb8"));//blue
   hpp_Zphi->SetLineColor(TColor::GetColor("#984ea3"));//purple
   hData_bkg_Zphi->SetLineColor(kBlack);
   hMC_bkg_Zphi->SetLineColor(TColor::GetColor("#377eb8"));//blue
   hMC_Zphi_gen->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_bkg_Zphi_gen->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_Zphi_gen0Sub->SetLineColor(TColor::GetColor("#4daf4a"));//green

   hData_Zphi->SetLineWidth(2);
   hMC_Zphi->SetLineWidth(2);
   hpp_Zphi->SetLineWidth(2);
   hData_bkg_Zphi->SetLineWidth(2);
   hMC_bkg_Zphi->SetLineWidth(2);
   hMC_Zphi_gen->SetLineWidth(2);
   hMC_bkg_Zphi_gen->SetLineWidth(2);
   hMC_Zphi_gen0Sub->SetLineWidth(2);

   hData_Trackphi->Scale(1./tD_tN/binphi);
   hMC_Trackphi->Scale(1./tM_tN/binphi);
   hpp_Trackphi->Scale(1./tpM_tN/binphi);
   hData_bkg_Trackphi->Scale(1./tDb_tN/binphi);
   hMC_bkg_Trackphi->Scale(1./tMb_tN/binphi);
   hMC_Trackphi_gen->Scale(1./tM_tNgen/binphi);
   hMC_bkg_Trackphi_gen->Scale(1./tMb_tNgen/binphi);
   hMC_Trackphi_gen0Sub->Scale(1./tM_tNgen0Sub/binphi);


   hData_Trackphi->SetMarkerStyle(24);
   hMC_Trackphi->SetMarkerStyle(24);
   hpp_Trackphi->SetMarkerStyle(24);
   hData_bkg_Trackphi->SetMarkerStyle(24);
   hMC_bkg_Trackphi->SetMarkerStyle(24);
   hMC_Trackphi_gen->SetMarkerStyle(24);
   hMC_bkg_Trackphi_gen->SetMarkerStyle(24);
   hMC_Trackphi_gen0Sub->SetMarkerStyle(24);

   hData_Trackphi->Rebin(5);
   hMC_Trackphi->Rebin(5);
   hpp_Trackphi->Rebin(5);
   hData_bkg_Trackphi->Rebin(5);
   hMC_bkg_Trackphi->Rebin(5);
   hMC_Trackphi_gen->Rebin(5);
   hMC_bkg_Trackphi_gen->Rebin(5);
   hMC_Trackphi_gen0Sub->Rebin(5);

   hData_Trackphi->Scale(1./5);
   hMC_Trackphi->Scale(1./5);
   hpp_Trackphi->Scale(1./5);
   hData_bkg_Trackphi->Scale(1./5);
   hMC_bkg_Trackphi->Scale(1./5);
   hMC_Trackphi_gen->Scale(1./5);
   hMC_bkg_Trackphi_gen->Scale(1./5);
   hMC_Trackphi_gen0Sub->Scale(1./5);

   hData_Trackphi->SetMarkerColor(kBlack);
   hData_bkg_Trackphi->SetMarkerColor(kBlack);

   hData_Trackphi->SetLineColor(kBlack);
   hMC_Trackphi->SetLineColor(TColor::GetColor("#377eb8"));//blue
   hpp_Trackphi->SetLineColor(TColor::GetColor("#984ea3"));//purple
   hData_bkg_Trackphi->SetLineColor(kBlack);
   hMC_bkg_Trackphi->SetLineColor(TColor::GetColor("#377eb8"));//blue
   hMC_Trackphi_gen->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_bkg_Trackphi_gen->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_Trackphi_gen0Sub->SetLineColor(TColor::GetColor("#4daf4a"));//green

   hData_Trackphi->SetLineWidth(2);
   hMC_Trackphi->SetLineWidth(2);
   hpp_Trackphi->SetLineWidth(2);
   hData_bkg_Trackphi->SetLineWidth(2);
   hMC_bkg_Trackphi->SetLineWidth(2);
   hMC_Trackphi_gen->SetLineWidth(2);
   hMC_bkg_Trackphi_gen->SetLineWidth(2);
   hMC_Trackphi_gen0Sub->SetLineWidth(2);

   hData_Zetaphi->Scale(1./tD_tN/binphi2d/bineta2d);
   hMC_Zetaphi->Scale(1./tM_tN/binphi2d/bineta2d);
   hpp_Zetaphi->Scale(1./tpM_tN/binphi2d/bineta2d);
   hData_bkg_Zetaphi->Scale(1./tDb_tN/binphi2d/bineta2d);
   hMC_bkg_Zetaphi->Scale(1./tMb_tN/binphi2d/bineta2d);
   hMC_Zetaphi_gen->Scale(1./tM_tNgen/binphi2d/bineta2d);
   hMC_bkg_Zetaphi_gen->Scale(1./tMb_tNgen/binphi2d/bineta2d);
   hMC_Zetaphi_gen0Sub->Scale(1./tM_tNgen0Sub/binphi2d/bineta2d);

   hData_Zetaphi->Rebin2D(5,5);
   hMC_Zetaphi->Rebin2D(5,5);
   hpp_Zetaphi->Rebin2D(5,5);
   hData_bkg_Zetaphi->Rebin2D(5,5);
   hMC_bkg_Zetaphi->Rebin2D(5,5);
   hMC_Zetaphi_gen->Rebin2D(5,5);
   hMC_bkg_Zetaphi_gen->Rebin2D(5,5);
   hMC_Zetaphi_gen0Sub->Rebin2D(5,5);

   hData_Zetaphi->Scale(1./25);
   hMC_Zetaphi->Scale(1./25);
   hpp_Zetaphi->Scale(1./25);
   hData_bkg_Zetaphi->Scale(1./25);
   hMC_bkg_Zetaphi->Scale(1./25);
   hMC_Zetaphi_gen->Scale(1./25);
   hMC_bkg_Zetaphi_gen->Scale(1./25);
   hMC_Zetaphi_gen0Sub->Scale(1./25);

   hData_Tracketaphi->Scale(1./tD_tN/binphi2d/bineta2d);
   hMC_Tracketaphi->Scale(1./tM_tN/binphi2d/bineta2d);
   hpp_Tracketaphi->Scale(1./tpM_tN/binphi2d/bineta2d);
   hData_bkg_Tracketaphi->Scale(1./tDb_tN/binphi2d/bineta2d);
   hMC_bkg_Tracketaphi->Scale(1./tMb_tN/binphi2d/bineta2d);
   hMC_Tracketaphi_gen->Scale(1./tM_tNgen/binphi2d/bineta2d);
   hMC_bkg_Tracketaphi_gen->Scale(1./tMb_tNgen/binphi2d/bineta2d);
   hMC_Tracketaphi_gen0Sub->Scale(1./tM_tNgen0Sub/binphi2d/bineta2d);

   hData_Tracketaphi->Rebin2D(5,5);
   hMC_Tracketaphi->Rebin2D(5,5);
   hpp_Tracketaphi->Rebin2D(5,5);
   hData_bkg_Tracketaphi->Rebin2D(5,5);
   hMC_bkg_Tracketaphi->Rebin2D(5,5);
   hMC_Tracketaphi_gen->Rebin2D(5,5);
   hMC_bkg_Tracketaphi_gen->Rebin2D(5,5);
   hMC_Tracketaphi_gen0Sub->Rebin2D(5,5);

   hData_Tracketaphi->Scale(1./25);
   hMC_Tracketaphi->Scale(1./25);
   hpp_Tracketaphi->Scale(1./25);
   hData_bkg_Tracketaphi->Scale(1./25);
   hMC_bkg_Tracketaphi->Scale(1./25);
   hMC_Tracketaphi_gen->Scale(1./25);
   hMC_bkg_Tracketaphi_gen->Scale(1./25);
   hMC_Tracketaphi_gen0Sub->Scale(1./25);

   if(TptL==0) TptL=TptL_min;

   TLegend leg(0.58,0.72,0.98,0.9);
   leg.AddEntry(hMC_Zeta_gen ,"Monte Carlo: GEN level","l");
   leg.AddEntry(hMC_Zeta ,"Monte Carlo: RECO level","l");
   leg.AddEntry(hData_Zeta ,Form("Data: %s",typeofdatatext),"p");
   leg.AddEntry(hpp_Zeta ,"pp MC (NPU=0)","l");
   leg.SetFillColorAlpha(kWhite,0);
   leg.SetLineColor(kBlack);
   leg.SetLineWidth(1);

   TLatex *pt = new TLatex(0.18,0.88,Form("%.0f %%< Centrality < %.0f %%",centL,centH));
   pt->SetTextFont(42);
   pt->SetTextSize(0.03);
   pt->SetNDC(kTRUE);

   TLatex *pt2 = new TLatex(0.18,0.82,Form("%.1f < Z p_{T} < %.1f",ptL,ptH));
   pt2->SetTextFont(42);
   pt2->SetTextSize(0.03);
   pt2->SetNDC(kTRUE);

   TLatex *pt3 = new TLatex(0.18,0.76,Form("%.1f < Track p_{T} < %.1f",TptL,TptH));
   pt3->SetTextFont(42);
   pt3->SetTextSize(0.03);
   pt3->SetNDC(kTRUE);

   TLatex *pt3d = new TLatex(0.03,0.94,Form("%.0f %%< Centrality < %.0f %%",centL,centH));
   pt3d->SetTextFont(42);
   pt3d->SetTextSize(0.03);
   pt3d->SetNDC(kTRUE);

   TLatex *pt3d2 = new TLatex(0.03,0.88,Form("%.1f < Z p_{T} < %.1f",ptL,ptH));
   pt3d2->SetTextFont(42);
   pt3d2->SetTextSize(0.03);
   pt3d2->SetNDC(kTRUE);

   TLatex *pt3d3 = new TLatex(0.03,0.82,Form("%.1f < Track p_{T} < %.1f",TptL,TptH));
   pt3d3->SetTextFont(42);
   pt3d3->SetTextSize(0.03);
   pt3d3->SetNDC(kTRUE);

   TLatex *ptN0 = new TLatex(0.3,0.97,Form("Signal N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f",tM_tN,tD_tN));
   ptN0->SetTextFont(42);
   ptN0->SetTextSize(0.03);
   ptN0->SetNDC(kTRUE);

   TLatex *ptNb = new TLatex(0.3,0.97,Form("Background N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f",tMb_tN,tDb_tN));
   ptNb->SetTextFont(42);
   ptNb->SetTextSize(0.03);
   ptNb->SetNDC(kTRUE);

   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Basic",typeofdata));

   c->Divide(2);
   c->cd(1);

   double max1 = hMC_Zeta_gen->GetMaximum();
   double max2 = hMC_Zeta->GetMaximum();
   double max3 = hData_Zeta->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_Zeta->Draw("hist");
   else if(max1<max3 && max2<max3) hData_Zeta->Draw();
   else hMC_Zeta_gen->Draw("hist");
   hMC_Zeta_gen->Draw("hist same");
   hMC_Zeta->Draw("hist same");
   hData_Zeta->Draw("same");
   hpp_Zeta->Draw("hist same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_Zeta_gen->SetXTitle("Signal #eta_{Z}");
   hMC_Zeta->SetXTitle("Signal #eta_{Z}");
   hData_Zeta->SetXTitle("Signal #eta_{Z}");
   hMC_Zeta_gen->SetYTitle("dN/d#eta");
   hMC_Zeta->SetYTitle("dN/d#eta");
   hData_Zeta->SetYTitle("dN/d#eta");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_Zeta_gen->SetMinimum(0);
   hMC_Zeta_gen->SetMaximum(1.6*max1); 
   hMC_Zeta->SetMinimum(0);
   hMC_Zeta->SetMaximum(1.6*max1); 
   hData_Zeta->SetMinimum(0);
   hData_Zeta->SetMaximum(1.6*max1); 

   ptN0->Draw();

   c->cd(2);

   max1 = hMC_bkg_Zeta_gen->GetMaximum();
   max2 = hMC_bkg_Zeta->GetMaximum();
   max3 = hData_bkg_Zeta->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_bkg_Zeta->Draw("hist");
   else if(max1<max3 && max2<max3) hData_bkg_Zeta->Draw();
   else hMC_bkg_Zeta_gen->Draw("hist");
   hMC_bkg_Zeta_gen->Draw("hist same");
   hMC_bkg_Zeta->Draw("hist same");
   hData_bkg_Zeta->Draw("same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_bkg_Zeta_gen->SetXTitle("Background #eta_{Z}");
   hMC_bkg_Zeta->SetXTitle("Background #eta_{Z}");
   hData_bkg_Zeta->SetXTitle("Background #eta_{Z}");
   hMC_bkg_Zeta_gen->SetYTitle("dN/d#eta");
   hMC_bkg_Zeta->SetYTitle("dN/d#eta");
   hData_bkg_Zeta->SetYTitle("dN/d#eta");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_bkg_Zeta_gen->SetMinimum(0);
   hMC_bkg_Zeta_gen->SetMaximum(1.6*max1); 
   hMC_bkg_Zeta->SetMinimum(0);
   hMC_bkg_Zeta->SetMaximum(1.6*max1); 
   hData_bkg_Zeta->SetMinimum(0);
   hData_bkg_Zeta->SetMaximum(1.6*max1); 

   ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_Z_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Zeta.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   max1 = hMC_Zphi_gen->GetMaximum();
   max2 = hMC_Zphi->GetMaximum();
   max3 = hData_Zphi->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_Zphi->Draw("hist");
   else if(max1<max3 && max2<max3) hData_Zphi->Draw();
   else hMC_Zphi_gen->Draw("hist");
   hMC_Zphi_gen->Draw("hist same");
   hMC_Zphi->Draw("hist same");
   hData_Zphi->Draw("same");
   hpp_Zphi->Draw("hist same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_Zphi_gen->SetXTitle("Signal #phi_{Z}");
   hMC_Zphi->SetXTitle("Signal #phi_{Z}");
   hData_Zphi->SetXTitle("Signal #phi_{Z}");
   hMC_Zphi_gen->SetYTitle("dN/d#phi");
   hMC_Zphi->SetYTitle("dN/d#phi");
   hData_Zphi->SetYTitle("dN/d#phi");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_Zphi_gen->SetMinimum(0);
   hMC_Zphi_gen->SetMaximum(1.6*max1); 
   hMC_Zphi->SetMinimum(0);
   hMC_Zphi->SetMaximum(1.6*max1); 
   hData_Zphi->SetMinimum(0);
   hData_Zphi->SetMaximum(1.6*max1); 

   ptN0->Draw();

   c->cd(2);

   max1 = hMC_bkg_Zphi_gen->GetMaximum();
   max2 = hMC_bkg_Zphi->GetMaximum();
   max3 = hData_bkg_Zphi->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_bkg_Zphi->Draw("hist");
   else if(max1<max3 && max2<max3) hData_bkg_Zphi->Draw();
   else hMC_bkg_Zphi_gen->Draw("hist");
   hMC_bkg_Zphi_gen->Draw("hist same");
   hMC_bkg_Zphi->Draw("hist same");
   hData_bkg_Zphi->Draw("same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_bkg_Zphi_gen->SetXTitle("Background #phi_{Z}");
   hMC_bkg_Zphi->SetXTitle("Background #phi_{Z}");
   hData_bkg_Zphi->SetXTitle("Background #phi_{Z}");
   hMC_bkg_Zphi_gen->SetYTitle("dN/d#phi");
   hMC_bkg_Zphi->SetYTitle("dN/d#phi");
   hData_bkg_Zphi->SetYTitle("dN/d#phi");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_bkg_Zphi_gen->SetMinimum(0);
   hMC_bkg_Zphi_gen->SetMaximum(1.6*max1); 
   hMC_bkg_Zphi->SetMinimum(0);
   hMC_bkg_Zphi->SetMaximum(1.6*max1); 
   hData_bkg_Zphi->SetMinimum(0);
   hData_bkg_Zphi->SetMaximum(1.6*max1); 

   ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_Z_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Zphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();



   c->Divide(2);
   c->cd(1);

   max1 = hMC_Tracketa_gen->GetMaximum();
   max2 = hMC_Tracketa->GetMaximum();
   max3 = hData_Tracketa->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_Tracketa->Draw("hist");
   else if(max1<max3 && max2<max3) hData_Tracketa->Draw();
   else hMC_Tracketa_gen->Draw("hist");
   hMC_Tracketa_gen->Draw("hist same");
   hMC_Tracketa->Draw("hist same");
   hData_Tracketa->Draw("same");
   hpp_Tracketa->Draw("hist same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_Tracketa_gen->SetXTitle("Signal #eta_{Track}");
   hMC_Tracketa->SetXTitle("Signal #eta_{Track}");
   hData_Tracketa->SetXTitle("Signal #eta_{Track}");
   hMC_Tracketa_gen->SetYTitle("dN/d#eta");
   hMC_Tracketa->SetYTitle("dN/d#eta");
   hData_Tracketa->SetYTitle("dN/d#eta");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_Tracketa_gen->SetMinimum(0);
   hMC_Tracketa_gen->SetMaximum(1.6*max1); 
   hMC_Tracketa->SetMinimum(0);
   hMC_Tracketa->SetMaximum(1.6*max1); 
   hData_Tracketa->SetMinimum(0);
   hData_Tracketa->SetMaximum(1.6*max1); 

   ptN0->Draw();

   c->cd(2);

   max1 = hMC_bkg_Tracketa_gen->GetMaximum();
   max2 = hMC_bkg_Tracketa->GetMaximum();
   max3 = hData_bkg_Tracketa->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_bkg_Tracketa->Draw("hist");
   else if(max1<max3 && max2<max3) hData_bkg_Tracketa->Draw();
   else hMC_bkg_Tracketa_gen->Draw("hist");
   hMC_bkg_Tracketa_gen->Draw("hist same");
   hMC_bkg_Tracketa->Draw("hist same");
   hData_bkg_Tracketa->Draw("same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_bkg_Tracketa_gen->SetXTitle("Background #eta_{Track}");
   hMC_bkg_Tracketa->SetXTitle("Background #eta_{Track}");
   hData_bkg_Tracketa->SetXTitle("Background #eta_{Track}");
   hMC_bkg_Tracketa_gen->SetYTitle("dN/d#eta");
   hMC_bkg_Tracketa->SetYTitle("dN/d#eta");
   hData_bkg_Tracketa->SetYTitle("dN/d#eta");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_bkg_Tracketa_gen->SetMinimum(0);
   hMC_bkg_Tracketa_gen->SetMaximum(1.6*max1); 
   hMC_bkg_Tracketa->SetMinimum(0);
   hMC_bkg_Tracketa->SetMaximum(1.6*max1); 
   hData_bkg_Tracketa->SetMinimum(0);
   hData_bkg_Tracketa->SetMaximum(1.6*max1); 

   ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_track_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Tracketa.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   max1 = hMC_Trackphi_gen->GetMaximum();
   max2 = hMC_Trackphi->GetMaximum();
   max3 = hData_Trackphi->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_Trackphi->Draw("hist");
   else if(max1<max3 && max2<max3) hData_Trackphi->Draw();
   else hMC_Trackphi_gen->Draw("hist");
   hMC_Trackphi_gen->Draw("hist same");
   hMC_Trackphi->Draw("hist same");
   hData_Trackphi->Draw("same");
   hpp_Trackphi->Draw("hist same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_Trackphi_gen->SetXTitle("Signal #phi_{Track}");
   hMC_Trackphi->SetXTitle("Signal #phi_{Track}");
   hData_Trackphi->SetXTitle("Signal #phi_{Track}");
   hMC_Trackphi_gen->SetYTitle("dN/d#phi");
   hMC_Trackphi->SetYTitle("dN/d#phi");
   hData_Trackphi->SetYTitle("dN/d#phi");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_Trackphi_gen->SetMinimum(0);
   hMC_Trackphi_gen->SetMaximum(1.6*max1); 
   hMC_Trackphi->SetMinimum(0);
   hMC_Trackphi->SetMaximum(1.6*max1); 
   hData_Trackphi->SetMinimum(0);
   hData_Trackphi->SetMaximum(1.6*max1); 

   ptN0->Draw();

   c->cd(2);

   max1 = hMC_bkg_Trackphi_gen->GetMaximum();
   max2 = hMC_bkg_Trackphi->GetMaximum();
   max3 = hData_bkg_Trackphi->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_bkg_Trackphi->Draw("hist");
   else if(max1<max3 && max2<max3) hData_bkg_Trackphi->Draw();
   else hMC_bkg_Trackphi_gen->Draw("hist");
   hMC_bkg_Trackphi_gen->Draw("hist same");
   hMC_bkg_Trackphi->Draw("hist same");
   hData_bkg_Trackphi->Draw("same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_bkg_Trackphi_gen->SetXTitle("Background #phi_{Track}");
   hMC_bkg_Trackphi->SetXTitle("Background #phi_{Track}");
   hData_bkg_Trackphi->SetXTitle("Background #phi_{Track}");
   hMC_bkg_Trackphi_gen->SetYTitle("dN/d#phi");
   hMC_bkg_Trackphi->SetYTitle("dN/d#phi");
   hData_bkg_Trackphi->SetYTitle("dN/d#phi");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_bkg_Trackphi_gen->SetMinimum(0);
   hMC_bkg_Trackphi_gen->SetMaximum(1.6*max1); 
   hMC_bkg_Trackphi->SetMinimum(0);
   hMC_bkg_Trackphi->SetMaximum(1.6*max1); 
   hData_bkg_Trackphi->SetMinimum(0);
   hData_bkg_Trackphi->SetMaximum(1.6*max1); 

   ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_track_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Trackphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zetaphi_gen->Draw("lego20");
   hMC_Zetaphi_gen->GetYaxis()->SetTitle("Signal MC GEN #phi_{Z,track}");
   hMC_Zetaphi_gen->GetXaxis()->SetTitle("Signal MC GEN #eta_{Z,track}");
   hMC_Zetaphi_gen->GetXaxis()->SetTitleSize(30);
   hMC_Zetaphi_gen->GetYaxis()->SetTitleSize(30);
   hMC_Zetaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zetaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zetaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_Zetaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_Zetaphi_gen->Draw("lego20");
   hMC_bkg_Zetaphi_gen->GetYaxis()->SetTitle("Background MC GEN #phi_{Z,track}");
   hMC_bkg_Zetaphi_gen->GetXaxis()->SetTitle("Background MC GEN #eta_{Z,track}");
   hMC_bkg_Zetaphi_gen->GetXaxis()->SetTitleSize(30);
   hMC_bkg_Zetaphi_gen->GetYaxis()->SetTitleSize(30);
   hMC_bkg_Zetaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_Zetaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_Zetaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_Zetaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_Z_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Zetaphi_GEN.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zetaphi->Draw("lego20");
   hMC_Zetaphi->GetYaxis()->SetTitle("Signal MC RECO #phi_{Z,track}");
   hMC_Zetaphi->GetXaxis()->SetTitle("Signal MC RECO #eta_{Z,track}");
   hMC_Zetaphi->GetXaxis()->SetTitleSize(30);
   hMC_Zetaphi->GetYaxis()->SetTitleSize(30);
   hMC_Zetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Zetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Zetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_Zetaphi->GetZaxis()->SetTitle("dN/d#etad#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_Zetaphi->Draw("lego20");
   hMC_bkg_Zetaphi->GetYaxis()->SetTitle("Background MC RECO #phi_{Z,track}");
   hMC_bkg_Zetaphi->GetXaxis()->SetTitle("Background MC RECO #eta_{Z,track}");
   hMC_bkg_Zetaphi->GetXaxis()->SetTitleSize(30);
   hMC_bkg_Zetaphi->GetYaxis()->SetTitleSize(30);
   hMC_bkg_Zetaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_Zetaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_Zetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_Zetaphi->GetZaxis()->SetTitle("dN/d#etad#phi");

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_Z_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Zetaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

    c->Divide(2);
   c->cd(1);

   hMC_Tracketaphi_gen->Draw("lego20");
   hMC_Tracketaphi_gen->GetYaxis()->SetTitle("Signal MC GEN #phi_{Track,track}");
   hMC_Tracketaphi_gen->GetXaxis()->SetTitle("Signal MC GEN #eta_{Track,track}");
   hMC_Tracketaphi_gen->GetXaxis()->SetTitleSize(30);
   hMC_Tracketaphi_gen->GetYaxis()->SetTitleSize(30);
   hMC_Tracketaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_Tracketaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_Tracketaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_Tracketaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_Tracketaphi_gen->Draw("lego20");
   hMC_bkg_Tracketaphi_gen->GetYaxis()->SetTitle("Background MC GEN #phi_{Track,track}");
   hMC_bkg_Tracketaphi_gen->GetXaxis()->SetTitle("Background MC GEN #eta_{Track,track}");
   hMC_bkg_Tracketaphi_gen->GetXaxis()->SetTitleSize(30);
   hMC_bkg_Tracketaphi_gen->GetYaxis()->SetTitleSize(30);
   hMC_bkg_Tracketaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_Tracketaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_Tracketaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_Tracketaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_track_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Tracketaphi_GEN.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Tracketaphi->Draw("lego20");
   hMC_Tracketaphi->GetYaxis()->SetTitle("Signal MC RECO #phi_{Track,track}");
   hMC_Tracketaphi->GetXaxis()->SetTitle("Signal MC RECO #eta_{Track,track}");
   hMC_Tracketaphi->GetXaxis()->SetTitleSize(30);
   hMC_Tracketaphi->GetYaxis()->SetTitleSize(30);
   hMC_Tracketaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_Tracketaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_Tracketaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_Tracketaphi->GetZaxis()->SetTitle("dN/d#etad#phi");

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_Tracketaphi->Draw("lego20");
   hMC_bkg_Tracketaphi->GetYaxis()->SetTitle("Background MC RECO #phi_{Track,track}");
   hMC_bkg_Tracketaphi->GetXaxis()->SetTitle("Background MC RECO #eta_{Track,track}");
   hMC_bkg_Tracketaphi->GetXaxis()->SetTitleSize(30);
   hMC_bkg_Tracketaphi->GetYaxis()->SetTitleSize(30);
   hMC_bkg_Tracketaphi->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_Tracketaphi->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_Tracketaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_Tracketaphi->GetZaxis()->SetTitle("dN/d#etad#phi");

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_track_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Tracketaphi.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zetaphi_gen->Draw("COLZ");
   hMC_Zetaphi_gen->GetYaxis()->SetTitle("Signal MC GEN #phi_{Z,track}");
   hMC_Zetaphi_gen->GetXaxis()->SetTitle("Signal MC GEN #eta_{Z,track}");
   hMC_Zetaphi_gen->GetXaxis()->SetTitleSize(48);
   hMC_Zetaphi_gen->GetYaxis()->SetTitleSize(48);
   hMC_Zetaphi_gen->GetXaxis()->SetTitleOffset(1);
   hMC_Zetaphi_gen->GetYaxis()->SetTitleOffset(1);
   hMC_Zetaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_Zetaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_Zetaphi_gen->Draw("COLZ");
   hMC_bkg_Zetaphi_gen->GetYaxis()->SetTitle("Background MC GEN #phi_{Z,track}");
   hMC_bkg_Zetaphi_gen->GetXaxis()->SetTitle("Background MC GEN #eta_{Z,track}");
   hMC_bkg_Zetaphi_gen->GetXaxis()->SetTitleSize(48);
   hMC_bkg_Zetaphi_gen->GetYaxis()->SetTitleSize(48);
   hMC_bkg_Zetaphi_gen->GetXaxis()->SetTitleOffset(1);
   hMC_bkg_Zetaphi_gen->GetYaxis()->SetTitleOffset(1);
   hMC_bkg_Zetaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_Zetaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_Z_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Zetaphi_GEN_COLZ.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Zetaphi->Draw("COLZ");
   hMC_Zetaphi->GetYaxis()->SetTitle("Signal MC RECO #phi_{Z,track}");
   hMC_Zetaphi->GetXaxis()->SetTitle("Signal MC RECO #eta_{Z,track}");
   hMC_Zetaphi->GetXaxis()->SetTitleSize(48);
   hMC_Zetaphi->GetYaxis()->SetTitleSize(48);
   hMC_Zetaphi->GetXaxis()->SetTitleOffset(1);
   hMC_Zetaphi->GetYaxis()->SetTitleOffset(1);
   hMC_Zetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_Zetaphi->GetZaxis()->SetTitle("dN/d#etad#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_Zetaphi->Draw("COLZ");
   hMC_bkg_Zetaphi->GetYaxis()->SetTitle("Background MC RECO #phi_{Z,track}");
   hMC_bkg_Zetaphi->GetXaxis()->SetTitle("Background MC RECO #eta_{Z,track}");
   hMC_bkg_Zetaphi->GetXaxis()->SetTitleSize(48);
   hMC_bkg_Zetaphi->GetYaxis()->SetTitleSize(48);
   hMC_bkg_Zetaphi->GetXaxis()->SetTitleOffset(1);
   hMC_bkg_Zetaphi->GetYaxis()->SetTitleOffset(1);
   hMC_bkg_Zetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_Zetaphi->GetZaxis()->SetTitle("dN/d#etad#phi");

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_Z_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Zetaphi_COLZ.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Tracketaphi_gen->Draw("COLZ");
   hMC_Tracketaphi_gen->GetYaxis()->SetTitle("Signal MC GEN #phi_{Track,track}");
   hMC_Tracketaphi_gen->GetXaxis()->SetTitle("Signal MC GEN #eta_{Track,track}");
   hMC_Tracketaphi_gen->GetXaxis()->SetTitleSize(48);
   hMC_Tracketaphi_gen->GetYaxis()->SetTitleSize(48);
   hMC_Tracketaphi_gen->GetXaxis()->SetTitleOffset(1);
   hMC_Tracketaphi_gen->GetYaxis()->SetTitleOffset(1);
   hMC_Tracketaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_Tracketaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_Tracketaphi_gen->Draw("COLZ");
   hMC_bkg_Tracketaphi_gen->GetYaxis()->SetTitle("Background MC GEN #phi_{Track,track}");
   hMC_bkg_Tracketaphi_gen->GetXaxis()->SetTitle("Background MC GEN #eta_{Track,track}");
   hMC_bkg_Tracketaphi_gen->GetXaxis()->SetTitleSize(48);
   hMC_bkg_Tracketaphi_gen->GetYaxis()->SetTitleSize(48);
   hMC_bkg_Tracketaphi_gen->GetXaxis()->SetTitleOffset(1);
   hMC_bkg_Tracketaphi_gen->GetYaxis()->SetTitleOffset(1);
   hMC_bkg_Tracketaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_Tracketaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_track_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Tracketaphi_GEN_COLZ.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_Tracketaphi->Draw("COLZ");
   hMC_Tracketaphi->GetYaxis()->SetTitle("Signal MC RECO #phi_{Track,track}");
   hMC_Tracketaphi->GetXaxis()->SetTitle("Signal MC RECO #eta_{Track,track}");
   hMC_Tracketaphi->GetXaxis()->SetTitleSize(48);
   hMC_Tracketaphi->GetYaxis()->SetTitleSize(48);
   hMC_Tracketaphi->GetXaxis()->SetTitleOffset(1);
   hMC_Tracketaphi->GetYaxis()->SetTitleOffset(1);
   hMC_Tracketaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_Tracketaphi->GetZaxis()->SetTitle("dN/d#etad#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_Tracketaphi->Draw("COLZ");
   hMC_bkg_Tracketaphi->GetYaxis()->SetTitle("Background MC RECO #phi_{Track,track}");
   hMC_bkg_Tracketaphi->GetXaxis()->SetTitle("Background MC RECO #eta_{Track,track}");
   hMC_bkg_Tracketaphi->GetXaxis()->SetTitleSize(48);
   hMC_bkg_Tracketaphi->GetYaxis()->SetTitleSize(48);
   hMC_bkg_Tracketaphi->GetXaxis()->SetTitleOffset(1);
   hMC_bkg_Tracketaphi->GetYaxis()->SetTitleOffset(1);
   hMC_bkg_Tracketaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_bkg_Tracketaphi->GetZaxis()->SetTitle("dN/d#etad#phi");

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/ZH_track_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Tracketaphi_COLZ.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();


}
int main(int argc, char *argv[]){

  style();

   file_sigMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSignal_v17_PFmuon.root","read");
   file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSigBkg_v17d_PFmuon_350_ov5.root","read");
   file_sigDA = TFile::Open("~/eos_base/BasicPlots/GraphDataSignal_v17_PFmuon.root","read");
   file_bkgDA = TFile::Open("~/eos_base/BasicPlots/GraphDataSigBkg_v17d_PFmuon.root","read");
   file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMC0Sub_v17_PFmuon.root","read");

   file_sigMCgen = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen_v17_PFmuon.root","read");
   file_bkgMCgen = TFile::Open("~/eos_base/BasicPlots/GraphMCGenSigBkg_v17b_checkz.root","read");
   file_sigMCgen0Sub = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen0Sub_v17_PFmuon.root","read");

  /* 
  ZcheckBasic_single(40, 20, 2000,  0, 90,  0, 1000);
  ZcheckBasic_single(40,  5, 2000,  0, 90,  0, 1000);

  ZcheckBasic_single(40, 20, 2000,  0, 90,  4,    5);
  ZcheckBasic_single(40, 20, 2000,  0, 90,  5,    7);
  ZcheckBasic_single(40, 20, 2000,  0, 90,  7,   10);
  ZcheckBasic_single(40, 20, 2000,  0, 90, 10,   20);
  ZcheckBasic_single(40, 20, 2000,  0, 90, 20,   50);
  ZcheckBasic_single(40, 20, 2000,  0, 90, 50,  100);
*/
  //ZcheckBasic_single(40, 10, 2000,  0, 90,  2, 1000);

  ZcheckBasic_single(40, 40, 200,  0, 10,  1, 1000);
  ZcheckBasic_single(40, 40, 200,  0, 10,  1, 2);
  ZcheckBasic_single(40, 40, 200,  0, 10,  2, 4);
  ZcheckBasic_single(40, 40, 200,  0, 10,  4, 10);

  //ZcheckBasic_single(40, 40, 200,  0, 10,  1, 1000);
  //ZcheckBasic_single(40, 40, 200, 10, 30,  1, 1000);
  //ZcheckBasic_single(40, 40, 200, 30, 50,  1, 1000);
  //ZcheckBasic_single(40, 40, 200, 50, 90,  1, 1000);

  return 0;
}