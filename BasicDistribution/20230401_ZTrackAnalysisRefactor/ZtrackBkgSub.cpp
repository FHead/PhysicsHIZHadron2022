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

using namespace std;

double TptL_min = 0.5;

int main(int argc, char *argv[]);
void ZtrackBkg_single(int binnum,float ptL,float ptH,float centL,float centH,float TptL,float TptH);

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
  gStyle->SetTitleSize(36, "xyz");
  gStyle->SetTitleOffset(1, "yz");
  gStyle->SetTitleOffset(-0.5, "x");
  gStyle->SetLabelSize(24, "xyz");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);

  //gStyle->SetPadTopMargin(0.05);
  //gStyle->SetPadBottomMargin(0.15);
  //gStyle->SetPadLeftMargin(0.15);
  //gStyle->SetPadRightMargin(0.05);

  gStyle->SetLineScalePS(1.5);

  gROOT->ForceStyle();
}

void SetPad(TPad *P)
{
   if(P == nullptr)
      return;
   //P->SetLeftMargin(500);
   //P->SetTopMargin(0);
   P->SetRightMargin(0);
   //P->SetBottomMargin(0);
   //P->SetTickx(false);
   //P->SetTicky(false);
   P->Draw();
}

TFile *file_sigMC;
TFile *file_bkgMC;
//TFile *file_sigDA;
//TFile *file_bkgDA;
TFile *file_ppMC;
TFile *file_ppbkgMC;

TFile *file_sigMCgen;
TFile *file_bkgMCgen;

const char *typeofdata = "v17d_PFMuon/20240101/SigBkg";
const char *typeofdata1 = "360_ov1";

bool selfmix = true;

void ZtrackBkg_single(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000)
{
   style();
   std::cout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;
   
   double MarginLeft    = 50;
   double MarginRight   = 5;
   double MarginTop     = 0;
   double MarginBottom  = 50;
   double PadWidth      = 800;
   double PadHeight     = 800;
   double RPadHeight    = 250;

   double CanvasWidth   = MarginLeft + PadWidth + MarginRight;
   double CanvasHeight  = MarginTop + PadHeight + RPadHeight + MarginBottom;

   double XMarginLeft   = MarginLeft / CanvasWidth;
   double XMarginRight  = MarginRight / CanvasWidth;
   double XMarginTop    = MarginTop / CanvasHeight;
   double XMarginBottom = MarginBottom / CanvasHeight;
   double XPadWidth     = PadWidth / CanvasWidth;
   double XPadHeight    = PadHeight / CanvasHeight;
   double XRPadHeight   = RPadHeight/ CanvasHeight;

   TCanvas *c = new TCanvas("c","",CanvasWidth, CanvasHeight);

   TPad* Pad = new TPad("Pad", "",
         XMarginLeft, XMarginBottom + XRPadHeight,
         XMarginLeft + XPadWidth , XMarginBottom + XRPadHeight + XPadHeight);
   TPad* RPad = new TPad("RPad", "",
         XMarginLeft, XMarginBottom,
         XMarginLeft + XPadWidth , XMarginBottom + XRPadHeight);

   std::cout<<"GetBorderMode c: "<<c->GetBorderMode()<<std::endl;
   std::cout<<"GetBorderSize c: "<<c->GetBorderSize()<<std::endl;

   //c->SetFrameBorderSize(0);
   c->SetRightMargin(0);

   SetPad(Pad);
   SetPad(RPad);

   std::cout<<"GetBorderMode Pad: "<<Pad->GetBorderMode()<<std::endl;
   std::cout<<"GetBorderSize Pad: "<<Pad->GetBorderSize()<<std::endl;

   //Pad->SetBorderSize(0);

   RPad->SetTopMargin(0);
   Pad->SetBottomMargin(0);
   //Pad->SetLeftMargin(10);

   //Pad->Draw();
   //RPad->Draw();


   std::cout<<"Getting histograms..."<<std::endl;

   std::string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",ptL,ptH,centL,centH,TptL,TptH);
   std::replace(FolderName.begin(), FolderName.end(), '.', 'p');

   //TH1D* hData_eta = (TH1D*) file_sigDA->Get(Form("%s/HEta", FolderName.c_str()));
   //TH1D* hMC_eta = (TH1D*) file_sigMC->Get(Form("%s/HEta", FolderName.c_str()));
   //TH1D* hpp_eta = (TH1D*) file_ppMC->Get(Form("%s/HEta", FolderName.c_str()));

   //hData_eta->SetName("hData_eta");
   //hMC_eta->SetName("hMC_eta");
   //hpp_eta->SetName("hpp_eta");

   //TH1D* hData_phi = (TH1D*) file_sigDA->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hMC_phi = (TH1D*) file_sigMC->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hpp_phi = (TH1D*) file_ppMC->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hpp_bkg_phi = (TH1D*) file_ppbkgMC->Get(Form("%s/HPhi", FolderName.c_str()));
   

   //hData_phi->SetName("hData_phi");
   hMC_phi->SetName("hMC_phi");
   hpp_phi->SetName("hpp_phi");
   hpp_bkg_phi->SetName("hpp_bkg_phi");

   TH1D* hMC_phi_gen = (TH1D*) file_sigMCgen->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hMC_bkg_phi_gen = (TH1D*) file_bkgMCgen->Get(Form("%s/HPhi", FolderName.c_str()));

   hMC_phi_gen->SetName("hMC_phi");
   hMC_bkg_phi_gen->SetName("hMC_phi");

   //TH1D* hData_bkg_eta = (TH1D*) file_bkgDA->Get(Form("%s/HEta", FolderName.c_str()));
   //TH1D* hMC_bkg_eta = (TH1D*) file_bkgMC->Get(Form("%s/HEta", FolderName.c_str()));

   //hData_bkg_eta->SetName("hData_bkg_eta");
   //hMC_bkg_eta->SetName("hMC_bkg_eta");

   //TH1D* hData_bkg_phi = (TH1D*) file_bkgDA->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hMC_bkg_phi = (TH1D*) file_bkgMC->Get(Form("%s/HPhi", FolderName.c_str()));

   //hData_bkg_phi->SetName("hData_bkg_phi");
   hMC_bkg_phi->SetName("hMC_bkg_phi");


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

   TH1D *nM_tN     = (TH1D *) file_sigMC->Get(Form("%s/HEventCount",FolderName.c_str()));
   TH1D *nMb_tN    = (TH1D *) file_bkgMC->Get(Form("%s/HEventCount",FolderName.c_str()));
   TH1D *npM_tN    = (TH1D *) file_ppMC ->Get(Form("%s/HEventCount",FolderName.c_str()));
   TH1D *npb_tN    = (TH1D *) file_ppbkgMC ->Get(Form("%s/HEventCount",FolderName.c_str()));
   
   TH1D *nM_tNgen  = (TH1D *) file_sigMCgen->Get(Form("%s/HGenEventCount",FolderName.c_str()));
   TH1D *nMb_tNgen = (TH1D *) file_bkgMCgen->Get(Form("%s/HGenEventCount",FolderName.c_str()));

   float tM_tN     =     nM_tN->GetBinContent(1);
   float tMb_tN    =    nMb_tN->GetBinContent(1);
   float tpM_tN    =    npM_tN->GetBinContent(1);  
   float tpb_tN    =    npb_tN->GetBinContent(1);  
   float tM_tNgen  =  nM_tNgen->GetBinContent(1);
   float tMb_tNgen = nMb_tNgen->GetBinContent(1); 
   
   std::cout<<"tM_tN = "<<tM_tN<<std::endl;
   std::cout<<"tMb_tN = "<<tMb_tN<<std::endl;
   std::cout<<"tpM_tN = "<<tpM_tN<<std::endl;
   std::cout<<"tpb_tN = "<<tpb_tN<<std::endl;
   std::cout<<"tM_tNgen = "<<tM_tNgen<<std::endl;
   std::cout<<"tMb_tNgen = "<<tMb_tNgen<<std::endl;

   double bineta = 0.032, binphi = M_PI/50;
   double bineta2d = 6.4/150, binphi2d = M_PI/75;

   //hData_eta->Scale(1./tD_tN/bineta);
   //hMC_eta->Scale(1./tM_tN/bineta);

   //hData_phi->Scale(1./tD_tN/binphi);
   hMC_phi->Scale(1./tM_tN/binphi);

   hMC_phi_gen->Scale(1./tM_tNgen/binphi);

   //hData_bkg_eta->Scale(1./tDb_tN/bineta);
   //hMC_bkg_eta->Scale(1./tMb_tN/bineta);

   //hData_bkg_phi->Scale(1./tDb_tN/binphi);
   hMC_bkg_phi->Scale(1./tMb_tN/binphi);

   hMC_bkg_phi_gen->Scale(1./tMb_tNgen/binphi);

   hpp_phi->Scale(1./tpM_tN/binphi);
   hpp_bkg_phi->Scale(1./tpb_tN/binphi);
   //hpp_eta->Scale(1./tpM_tN/bineta);

   //TH1D *hData_sb_eta = (TH1D*) hData_eta->Clone("hData_sb_eta");
   //TH1D *hMC_sb_eta = (TH1D*) hMC_eta->Clone("hMC_sb_eta");
   //TH1D *hData_sb_phi = (TH1D*) hData_phi->Clone("hData_sb_phi");
   TH1D *hMC_sb_phi = (TH1D*) hMC_phi->Clone("hMC_sb_phi");

   TH1D *hMC_sb_phi_gen = (TH1D*) hMC_phi_gen->Clone("hMC_sb_phi_gen");

   //TH1D *hpp_sb_phi = (TH1D*) hpp_phi->Clone("hpp_sb_phi");

   //TH1D *hData_sbr_eta = (TH1D*) hData_eta->Clone("hData_sbr_eta");
   //TH1D *hMC_sbr_eta = (TH1D*) hMC_eta->Clone("hMC_sbr_eta");
   //TH1D *hData_sbr_phi = (TH1D*) hData_phi->Clone("hData_sbr_phi");
   TH1D *hMC_sbr_phi = (TH1D*) hMC_phi->Clone("hMC_sbr_phi");

   //hData_sb_eta->Add(hData_bkg_eta,-1);
   //hMC_sb_eta->Add(hMC_bkg_eta,-1);
   //hData_sb_phi->Add(hData_bkg_phi,-1);
   hMC_sb_phi->Add(hMC_bkg_phi,-1);

   hMC_sb_phi_gen->Add(hMC_bkg_phi_gen,-1);

   if(selfmix)
      hpp_phi->Add(hpp_bkg_phi,-1); //SigBkg

   //hData_sbr_eta->Divide(hData_bkg_eta);
   //hMC_sbr_eta->Divide(hMC_bkg_eta);
   //hData_sbr_phi->Divide(hData_bkg_phi);
   hMC_sbr_phi->Divide(hMC_bkg_phi);

   //int countD0 = hData_phi->GetEntries();
   //std::cout<<"Data 0 = "<<countD0<<std::endl;
   int countM0 = hMC_phi->GetEntries();
   std::cout<<"MC 0 = "<<countM0<<std::endl;

   //int countDb = hData_bkg_phi->GetEntries();
   //std::cout<<"Data Bkg = "<<countDb<<std::endl;
   int countMb = hMC_bkg_phi->GetEntries();
   std::cout<<"MC Bkg = "<<countMb<<std::endl;

   std::cout<<"Drawing..."<<std::endl;

   //hMC_eta->SetMarkerStyle(24);
   hMC_phi->SetMarkerStyle(24);
   //hMC_bkg_eta->SetMarkerStyle(24);
   hMC_bkg_phi->SetMarkerStyle(24);
   //hMC_sb_eta->SetMarkerStyle(24);
   hMC_sb_phi->SetMarkerStyle(24);
   //hMC_sbr_eta->SetMarkerStyle(24);
   hMC_sbr_phi->SetMarkerStyle(24);

   hMC_sb_phi_gen->SetMarkerStyle(24);

   //hData_eta->SetMarkerColor(kBlack);
   //hMC_eta->SetMarkerColor(kRed);
   //hData_phi->SetMarkerColor(kBlack);
   hMC_phi->SetMarkerColor(kRed);



   //hData_eta->SetLineColor(kBlack);
   //hMC_eta->SetLineColor(kRed);
   //hData_phi->SetLineColor(kBlack);
   hMC_phi->SetLineColor(kRed);

   //hData_bkg_eta->SetMarkerColor(kBlack);
   //hMC_bkg_eta->SetMarkerColor(kRed);
   //hData_bkg_phi->SetMarkerColor(kBlack);
   hMC_bkg_phi->SetMarkerColor(kRed);

   //hData_bkg_eta->SetLineColor(kBlack);
   //hMC_bkg_eta->SetLineColor(kRed);
   //hData_bkg_phi->SetLineColor(kBlack);
   hMC_bkg_phi->SetLineColor(kRed);

   //hData_sb_eta->SetMarkerColor(kBlack);
   //hMC_sb_eta->SetMarkerColor(kRed);
   //hData_sb_phi->SetMarkerColor(kBlack);
   hMC_sb_phi->SetMarkerColor(kRed);

   //hData_sb_eta->SetLineColor(kBlack);
   //hMC_sb_eta->SetLineColor(kRed);
   //hData_sb_phi->SetLineColor(kBlack);
   hMC_sb_phi->SetLineColor(kRed);

   //hData_sbr_eta->SetMarkerColor(kBlack);
   //hMC_sbr_eta->SetMarkerColor(kRed);
   //hData_sbr_phi->SetMarkerColor(kBlack);
   hMC_sbr_phi->SetMarkerColor(kRed);

   //hData_sbr_eta->SetLineColor(kBlack);
   //hMC_sbr_eta->SetLineColor(kRed);
   //hData_sbr_phi->SetLineColor(kBlack);
   hMC_sbr_phi->SetLineColor(kRed);

   hMC_sb_phi_gen->SetLineColor(kGreen);

   if(TptL==0) TptL=TptL_min;

   string typeofsample;

   if(selfmix)
      typeofsample = "Z - Z #times Z (MC)";
   else
      typeofsample = "Nominal MC";

   TLatex *pt0 = new TLatex(0.15,0.82,typeofsample.c_str());
   //TLatex *pt0 = new TLatex(0.15,0.82,"Z - Z #times Z (MC)");
   //TLatex *pt0 = new TLatex(0.15,0.82,"Nominal MC GEN (Pythia+Hydjet)");
   pt0->SetTextFont(42);
   pt0->SetTextSize(0.03);
   pt0->SetNDC(kTRUE);

   TLatex *pt = new TLatex(0.15,0.76,Form("%.0f %%< Centrality < %.0f %%",centL,centH));
   pt->SetTextFont(42);
   pt->SetTextSize(0.03);
   pt->SetNDC(kTRUE);

   TLatex *pt2 = new TLatex(0.15,0.70,Form("%.1f < Z p_{T} < %.1f GeV",ptL,ptH));
   pt2->SetTextFont(42);
   pt2->SetTextSize(0.03);
   pt2->SetNDC(kTRUE);

   TLatex *pt3 = new TLatex(0.15,0.64,Form("%.1f < Track p_{T} < %.1f GeV",TptL,TptH));
   pt3->SetTextFont(42);
   pt3->SetTextSize(0.03);
   pt3->SetNDC(kTRUE);

   // == Start drawing == //

   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/BkgSub",typeofdata));

   //hMC_phi->GetXaxis()->SetRangeUser(0,M_PI);
   //hMC_bkg_phi->GetXaxis()->SetRangeUser(0,M_PI);
   //hMC_sb_phi->GetXaxis()->SetRangeUser(0,M_PI);
   //hpp_phi->GetXaxis()->SetRangeUser(0,M_PI);
   //hMC_sb_phi_gen->GetXaxis()->SetRangeUser(0,M_PI);
   //hMC_phi_gen->GetXaxis()->SetRangeUser(0,M_PI);

   double max1 = hMC_phi->GetMaximum();
   double max2 = hMC_bkg_phi->GetMaximum();

   hMC_phi->SetMarkerColor(kBlack);
   hMC_bkg_phi->SetMarkerColor(kBlue);
   hMC_sb_phi->SetMarkerColor(kRed);

   std::cout<< "hMC_phi->Integral() = "<< hMC_phi->Integral();
   std::cout<< ", hMC_bkg_phi->Integral() = "<< hMC_bkg_phi->Integral();
   std::cout<< ", hMC_sb_phi->Integral() = "<< hMC_sb_phi->Integral();
   std::cout<< ", hpp_phi->Integral() = "<< hpp_phi->Integral()<<std::endl;

   TLatex *ptInt1 = new TLatex(0.15,0.46,Form("#Sigma raw = %.1f,  #Sigma bkg = %.1f",hMC_phi->Integral(),hMC_bkg_phi->Integral()));
   ptInt1->SetTextFont(42);
   ptInt1->SetTextSize(0.03);
   ptInt1->SetNDC(kTRUE);

   string pptext;

   if(selfmix)
      pptext = "#Sigma pp (raw-bkg)";
   else
      pptext = "#Sigma pp";

   //TLatex *ptInt2 = new TLatex(0.15,0.40,Form("#Sigma (raw-bkg) = %.1f,  #Sigma pp = %.1f",hMC_sb_phi->Integral(),hpp_phi->Integral()));
   TLatex *ptInt2 = new TLatex(0.15,0.40,Form("#Sigma (raw-bkg) = %.1f,  %s = %.1f",hMC_sb_phi->Integral(),pptext.c_str(),hpp_phi->Integral()));
   ptInt2->SetTextFont(42);
   ptInt2->SetTextSize(0.03);
   ptInt2->SetNDC(kTRUE);



   hMC_phi->SetLineColor(kBlack);
   hMC_bkg_phi->SetLineColor(kBlue);
   hMC_sb_phi->SetLineColor(kRed);
   hpp_phi->SetLineColor(kBlack);
   hMC_phi_gen->SetLineColor(kGreen);

   hMC_phi->SetMarkerStyle(kFullCircle);
   hMC_bkg_phi->SetMarkerStyle(kFullCircle);
   hMC_sb_phi->SetMarkerStyle(kFullCircle);

   hpp_phi->SetLineWidth(2);
   hMC_sb_phi_gen->SetLineWidth(2);
   hMC_phi_gen->SetLineWidth(2);
   
   Pad->cd();

   if(max1<max2) hMC_bkg_phi->Draw("ep");
   else hMC_phi->Draw("ep");
   hMC_phi->Draw("ep same");
   hMC_bkg_phi->Draw("ep same");

   hMC_sb_phi->Draw("ep same");
   hpp_phi->Draw("hist same");
   //hMC_sb_phi_gen->Draw("hist same");
   //hMC_phi_gen->Draw("hist same");

   if(max1<max2) max1=max2;

   //hMC_phi->SetXTitle("#Delta#phi_{Z,track}");
   //hMC_bkg_phi->SetXTitle("#Delta#phi_{Z,track}");
   hMC_phi->SetYTitle("dN/d#Delta#phi");
   hMC_bkg_phi->SetYTitle("dN/d#Delta#phi");
   hMC_sb_phi_gen->SetYTitle("dN/d#Delta#phi");

   //hMC_phi->Draw("axis same");

   TLegend leg1(0.68,0.62,0.98,0.88);
   leg1.AddEntry(hMC_phi ,"raw","lep");
   leg1.AddEntry(hMC_bkg_phi ,"bkg","lep");
   leg1.AddEntry(hMC_sb_phi ,"raw-bkg","lep");
   if(selfmix)
      leg1.AddEntry(hpp_phi ,"pp raw-bkg","l");
   else
      leg1.AddEntry(hpp_phi ,"pp","l");
   //leg1.AddEntry(hMC_sb_phi_gen,"raw-bkg GEN","lep");
   //leg1.AddEntry(hMC_phi_gen,"sig GEN","lep");
   //leg1.AddEntry(hpp_phi ,"sig GEN","l");
   leg1.SetFillColorAlpha(kWhite,0);
   leg1.SetLineColor(kBlack);
   leg1.SetLineWidth(1);
   leg1.Draw();

   pt0->Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   ptInt1->Draw();
   ptInt2->Draw();

   //std::cout<<"max1 = "<<max1<<std::endl;
   //hMC_phi->SetMinimum(0);
   hMC_phi->SetMaximum(1.6*max1);
   //hMC_bkg_phi->SetMinimum(0);
   hMC_bkg_phi->SetMaximum(1.6*max1);
/*
   if(ptL==30&&centL==0&&centH==30){
    hMC_phi->SetMaximum(max1);
    hMC_bkg_phi->SetMaximum(max1);
   }else if(ptL==30&&centL==30&&centH==50){
    hMC_phi->SetMaximum(max1/1.6);
    hMC_bkg_phi->SetMaximum(max1/1.6);
   }
*/
   //hMC_phi->GetYaxis()->SetRangeUser(0,max1/1.6);
   //hMC_bkg_phi->GetYaxis()->SetRangeUser(0,max1/1.6);
   //hMC_sb_phi->GetYaxis()->SetRangeUser(0,max1/1.6);
   //hpp_phi->GetYaxis()->SetRangeUser(0,max1/1.6);

   //ptN0->Draw();

   hMC_phi->SetMinimum(-10);
   hMC_bkg_phi->SetMinimum(-10);
   hMC_sb_phi->SetMinimum(-10);
   hpp_phi->SetMinimum(-10);
   hMC_sb_phi_gen->SetMinimum(-10);
   hMC_phi_gen->SetMinimum(-10);


   //Pad->Update();
   //Pad->RedrawAxis();

   RPad->cd();

   TH1D *PbPb_to_pp = (TH1D*) hMC_sb_phi->Clone("PbPb_to_pp");
   //PbPb_to_pp->Divide(hpp_phi);
   PbPb_to_pp->Add(hpp_phi,-1);

   TH1D *horiz_line = (TH1D*) hMC_sb_phi->Clone("horiz_line");
   //horiz_line->Divide(hMC_sb_phi);
   horiz_line->Add(hMC_sb_phi,-1);

   horiz_line->SetLineColor(kBlack);
   PbPb_to_pp->SetLineColor(kRed);

   PbPb_to_pp->SetXTitle("#Delta#phi_{Z,track}");

   if(selfmix)
      PbPb_to_pp->SetYTitle("(PbPb r-b) - (pp r-b)");
   else
      PbPb_to_pp->SetYTitle("PbPb r-b / pp");
   

   PbPb_to_pp->Draw("ep");
   horiz_line->Draw("hist same");

   //TLatex *xlab = new TLatex(0.8,0.2,"#Delta#phi_{Z,track}");
   //xlab->SetTextFont(43);
   //xlab->SetTextSize(5);
   //xlab->SetNDC(kTRUE);
   //xlab->Draw();

   //PbPb_to_pp->Draw("axis same");

   //RPad->Update();
   //RPad->RedrawAxis();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/BkgSub/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   
   Pad->SetLogy();
   hMC_phi->SetMinimum(0.01);
   hMC_bkg_phi->SetMinimum(0.01);
   hMC_sb_phi->SetMinimum(0.01);
   hpp_phi->SetMinimum(0.01);
   hMC_sb_phi_gen->SetMinimum(0.01);
   hMC_phi_gen->SetMinimum(0.01);


   hMC_phi->SetMaximum(1000000);
   hMC_bkg_phi->SetMaximum(1000000);
   hMC_sb_phi->SetMaximum(1000000);
   hpp_phi->SetMaximum(1000000);
   hMC_sb_phi_gen->SetMaximum(1000000);
   hMC_phi_gen->SetMaximum(1000000);


   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/BkgSub/Ztrack_%s_comlog_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicomlog.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   Pad->SetLogy(0);
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/BkgSub/pdf/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/BkgSub/C/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();



}

int main(int argc, char *argv[]){

   style();

   file_sigMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSignal_v17_PFmuon.root","read");
   //file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCBackground_v17d_PFmuon.root","read");
   file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSigBkg_v17d_PFmuon_360_ov1.root","read");
   //file_sigDA = TFile::Open("~/eos_base/BasicPlots/GraphDataSignal_v17_PFmuon.root","read");
   //file_bkgDA = TFile::Open("~/eos_base/BasicPlots/GraphDataBackground_v17_PFmuon.root","read");
   file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMC0Sub_v17_PFmuon.root","read");
   //file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMC_v17_PFmuon.root","read");
   //file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPData_v17_PFmuon.root","read");

   file_ppbkgMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMCSigBkg_v17d_Cent10_143.root","read");

   file_sigMCgen = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen_v17_PFmuon.root","read");
   //file_sigMCgen = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen0Sub_v17_PFmuon.root","read");
   file_bkgMCgen = TFile::Open("~/eos_base/BasicPlots/GraphMCBackgroundGen_v17_PFmuon.root","read");

   //file_sigMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen_v17_PFmuon.root","read");
   //file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCBackgroundGen_v17_PFmuon.root","read");
   //file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen0Sub_v17_PFmuon.root","read");

/*
   ZtrackBkg_single(40, 20, 2000,  0, 10,  0, 1000);
   ZtrackBkg_single(40, 20, 2000, 10, 30,  0, 1000);
   ZtrackBkg_single(40, 20, 2000, 30, 50,  0, 1000);
   ZtrackBkg_single(40, 20, 2000, 50, 90,  0, 1000);
   ZtrackBkg_single(40, 20, 2000,  0, 90,  1,    2);
   ZtrackBkg_single(40, 20, 2000,  0, 90,  2,    5);
   ZtrackBkg_single(40, 20, 2000,  0, 90,  5,   10);
   ZtrackBkg_single(40, 20, 2000,  0, 90, 10,   20);
   ZtrackBkg_single(40, 20, 2000,  0, 90, 20,   50);
   ZtrackBkg_single(40, 20, 2000,  0, 90, 50,  100);
*/
   ZtrackBkg_single(40, 40, 200,  0, 10,  1, 1000);

   ZtrackBkg_single(40, 40, 200,  0, 10,  1, 2);
   ZtrackBkg_single(40, 40, 200,  0, 10,  2, 4);
   ZtrackBkg_single(40, 40, 200,  0, 10,  4, 10);
   //ZtrackBkg_single(40, 40, 200, 10, 30,  1, 1000);
   //ZtrackBkg_single(40, 40, 200, 30, 50,  1, 1000);
   //ZtrackBkg_single(40, 40, 200, 50, 90,  1, 1000);
/*
   ZtrackBkg_single(40, 20, 2000,  0, 10, 10,   20);
   ZtrackBkg_single(40, 20, 2000, 10, 30, 10,   20);
   ZtrackBkg_single(40, 20, 2000, 30, 50, 10,   20);
   ZtrackBkg_single(40, 20, 2000, 50, 90, 10,   20);
*/
   //ZtrackBkg_single(40, 40, 200,  0, 30, 1, 1000);
   //ZtrackBkg_single(40, 40, 200,  0, 10, 1, 1000);
   //ZtrackBkg_single(40, 40, 200, 10, 30, 1, 1000);
   //ZtrackBkg_single(40, 40, 200, 30, 50, 1, 1000);
   //ZtrackBkg_single(40, 40, 200, 50, 90, 1, 1000);

   file_sigMC->Close();
   file_bkgMC->Close();
   //file_sigDA->Close();
   //file_bkgDA->Close();
   file_ppMC->Close();
   file_ppbkgMC->Close();

   file_sigMCgen->Close();
   file_bkgMCgen->Close();

   return 0;

}
