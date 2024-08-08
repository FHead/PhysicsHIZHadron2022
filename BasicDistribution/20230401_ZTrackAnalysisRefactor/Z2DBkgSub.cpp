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
void Z2DBkgSub_single(int binnum,float ptL,float ptH,float centL,float centH,float TptL,float TptH,
   string HistName, string XTitleName, string YTitleName, int rebinnum);
void Z2DBkgSub_loop(int binnum,float ptL,float ptH,float centL,float centH,float TptL,float TptH);

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
  gStyle->SetTitleSize(24, "xyz");
  gStyle->SetTitleOffset(1, "xyz");
  gStyle->SetLabelSize(24, "xy");
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
TFile *file_ppMC;
TFile *file_ppbkgMC;


const char *typeofdata = "v17d_PFMuon/20240206/nominal_ov10_10HF_GEN";
const char *typeofdata1 = "37_ov10_GEN";

//const char *typeofdata = "v17d_PFMuon/20240206/SigBkg_ov20_10HF";
//const char *typeofdata1 = "350_ov20_pp10HF";

bool selfmix = false;

void Z2DBkgSub_single(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000, 
   string HistName="HPhi", string XTitleName = "#Delta#phi_{Z,track}", string YTitleName = "dN/d#Delta#phi", string ZTitleName = "dN/d#Delta#eta#Delta#phi", int rebinnum=1)
{
   style();
   std::cout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;
   
   TCanvas *c = new TCanvas("c","",1600, 1600);

   std::cout<<"Getting histograms..."<<std::endl;

   std::string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",ptL,ptH,centL,centH,TptL,TptH);
   std::replace(FolderName.begin(), FolderName.end(), '.', 'p');

   TH2D* hMC_phi = (TH2D*) file_sigMC->Get(Form("%s/%s", FolderName.c_str(), HistName.c_str()));
   TH2D* hpp_phi = (TH2D*) file_ppMC->Get(Form("%s/%s", FolderName.c_str(), HistName.c_str()));
   TH2D* hpp_bkg_phi = (TH2D*) file_ppbkgMC->Get(Form("%s/%s", FolderName.c_str(), HistName.c_str()));

   hMC_phi->SetName("hMC_phi");
   hpp_phi->SetName("hpp_phi");
   hpp_bkg_phi->SetName("hpp_bkg_phi");

   TH2D* hMC_bkg_phi = (TH2D*) file_bkgMC->Get(Form("%s/%s", FolderName.c_str(), HistName.c_str()));
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

   TH1D *nM_tN     = (TH1D *) file_sigMC->Get(Form("%s/HGenEventCount",FolderName.c_str()));
   TH1D *nMb_tN    = (TH1D *) file_bkgMC->Get(Form("%s/HGenEventCount",FolderName.c_str()));
   TH1D *npM_tN    = (TH1D *) file_ppMC ->Get(Form("%s/HGenEventCount",FolderName.c_str()));
   TH1D *npb_tN    = (TH1D *) file_ppbkgMC ->Get(Form("%s/HGenEventCount",FolderName.c_str()));
   
   float tM_tN     =     nM_tN->GetBinContent(1);
   float tMb_tN    =    nMb_tN->GetBinContent(1);
   float tpM_tN    =    npM_tN->GetBinContent(1);  
   float tpb_tN    =    npb_tN->GetBinContent(1);  
   
   std::cout<<"tM_tN = " <<tM_tN<<std::endl;
   std::cout<<"tMb_tN = "<<tMb_tN<<std::endl;
   std::cout<<"tpM_tN = "<<tpM_tN<<std::endl;
   std::cout<<"tpb_tN = "<<tpb_tN<<std::endl;

   double binx1 = hMC_phi->GetXaxis()->GetBinLowEdge(1);
   double binx2 = hMC_phi->GetXaxis()->GetBinLowEdge(2);
   double biny1 = hMC_phi->GetYaxis()->GetBinLowEdge(1);
   double biny2 = hMC_phi->GetYaxis()->GetBinLowEdge(2);

   double bin_width = (binx2-binx1)*(biny2-biny1);

   hMC_phi->Scale(1./tM_tN/bin_width);
   hMC_bkg_phi->Scale(1./tMb_tN/bin_width);
   hpp_phi->Scale(1./tpM_tN/bin_width);
   hpp_bkg_phi->Scale(1./tpb_tN/bin_width);

   hMC_phi->Rebin2D(rebinnum,rebinnum);
   hMC_bkg_phi->Rebin2D(rebinnum,rebinnum);
   hpp_phi->Rebin2D(rebinnum,rebinnum);
   hpp_bkg_phi->Rebin2D(rebinnum,rebinnum);

   hMC_phi->Scale(1./rebinnum/rebinnum);
   hMC_bkg_phi->Scale(1./rebinnum/rebinnum);
   hpp_phi->Scale(1./rebinnum/rebinnum);
   hpp_bkg_phi->Scale(1./rebinnum/rebinnum);

   TH2D *hMC_sb_phi = (TH2D*) hMC_phi->Clone("hMC_sb_phi");
   hMC_sb_phi->Add(hMC_bkg_phi,-1);

   if(selfmix)
      hpp_phi->Add(hpp_bkg_phi,-1); //SigBkg


   TH2D *hMC_sbp_phi = (TH2D*) hMC_sb_phi->Clone("hMC_sbp_phi");
   hMC_sbp_phi->Add(hpp_phi,-1);

   TH2D *hMC_sbpr_phi = (TH2D*) hMC_sb_phi->Clone("hMC_sbpr_phi");
   hMC_sbpr_phi->Divide(hpp_phi);


   int countM0 = hMC_phi->GetEntries();
   std::cout<<"MC 0 = "<<countM0<<std::endl;

   int countMb = hMC_bkg_phi->GetEntries();
   std::cout<<"MC Bkg = "<<countMb<<std::endl;

   std::cout<<"Drawing..."<<std::endl;

   hMC_phi->SetMarkerStyle(24);
   hMC_bkg_phi->SetMarkerStyle(24);
   hMC_sb_phi->SetMarkerStyle(24);

   hMC_phi->SetMarkerColor(kRed);
   hMC_phi->SetLineColor(kRed);
   hMC_bkg_phi->SetMarkerColor(kRed);
   hMC_bkg_phi->SetLineColor(kRed);
   hMC_sb_phi->SetMarkerColor(kRed);
   hMC_sb_phi->SetLineColor(kRed);

   if(TptL==0) TptL=TptL_min;

   string typeofsample;

   if(selfmix)
      typeofsample = "Z - Z #times Z (MC)";
   else
      typeofsample = "Nominal MC Gen";

   TLatex *pt0 = new TLatex(0.1,0.97,typeofsample.c_str());
   //TLatex *pt0 = new TLatex(0.15,0.82,"Nominal MC GEN (Pythia+Hydjet)");
   pt0->SetTextFont(42);
   pt0->SetTextSize(0.03);
   pt0->SetNDC(kTRUE);

   TLatex *pt = new TLatex(0.1,0.97,Form("%.0f %%< Cent. < %.0f %%, %.1f < p_{T,Z} < %.1f GeV, %.1f < p_{T,trk} < %.1f GeV",centL,centH,ptL,ptH,TptL,TptH));
   pt->SetTextFont(42);
   pt->SetTextSize(0.03);
   pt->SetNDC(kTRUE);

   // == Start drawing == //

   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/2DBkgSub/%s",typeofdata,HistName.c_str()));

   double max1 = hMC_phi->GetMaximum();
   double max2 = hMC_bkg_phi->GetMaximum();

   hMC_phi->SetMarkerColor(kBlack);
   hMC_bkg_phi->SetMarkerColor(kBlue);
   hMC_sb_phi->SetMarkerColor(kRed);

   std::cout<< "bin_width = " << bin_width;
   std::cout<< ", rebinnum = " << rebinnum << std::endl;
   std::cout<< "hMC_phi->Integral() = "<< hMC_phi->Integral();
   std::cout<< ", hMC_bkg_phi->Integral() = "<< hMC_bkg_phi->Integral();
   std::cout<< ", hMC_sb_phi->Integral() = "<< hMC_sb_phi->Integral();
   std::cout<< ", hpp_phi->Integral() = "<< hpp_phi->Integral()<<std::endl;

   hMC_phi->SetLineColor(kBlack);
   hMC_bkg_phi->SetLineColor(kBlue);
   hMC_sb_phi->SetLineColor(kRed);
   hpp_phi->SetLineColor(kBlack);

   hMC_phi->SetMarkerStyle(kFullCircle);
   hMC_bkg_phi->SetMarkerStyle(kFullCircle);
   hMC_sb_phi->SetMarkerStyle(kFullCircle);

   hpp_phi->SetLineWidth(2);

   double min1 = hMC_sb_phi->GetMinimum();
   double min2 = hpp_phi->GetMinimum();
   
   c->Divide(2,2);
   c->cd(1);

   hMC_sb_phi->Draw("lego20");
   hMC_sb_phi->GetYaxis()->SetTitle(("Signal - Background MC " + YTitleName).c_str());
   hMC_sb_phi->GetXaxis()->SetTitle(("Signal - Background MC " + XTitleName).c_str());
   hMC_sb_phi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_phi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_phi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_phi->GetZaxis()->SetTitle(ZTitleName.c_str());

   pt0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);

   hpp_phi->Draw("lego20");

   if(selfmix){
      hpp_phi->GetYaxis()->SetTitle(("pp Signal - Background MC " + YTitleName).c_str());
      hpp_phi->GetXaxis()->SetTitle(("pp Signal - Background MC " + XTitleName).c_str());
   }else{
      hpp_phi->GetYaxis()->SetTitle(("pp MC " + YTitleName).c_str());
      hpp_phi->GetXaxis()->SetTitle(("pp MC " + XTitleName).c_str());
   }

   hpp_phi->GetXaxis()->SetTitleOffset(3.0);
   hpp_phi->GetYaxis()->SetTitleOffset(2.5);
   hpp_phi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_phi->GetZaxis()->SetTitle(ZTitleName.c_str());

   pt->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);

   hMC_sbp_phi->Draw("lego20");

   if(selfmix){
      hMC_sbp_phi->GetYaxis()->SetTitle(("PbPb-pp MC " + YTitleName).c_str());
      hMC_sbp_phi->GetXaxis()->SetTitle(("PbPb-pp MC " + XTitleName).c_str());
   }else{
      hMC_sbp_phi->GetYaxis()->SetTitle(("PbPb-pp MC " + YTitleName).c_str());
      hMC_sbp_phi->GetXaxis()->SetTitle(("PbPb-pp MC " + XTitleName).c_str());
   }

   hMC_sbp_phi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sbp_phi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sbp_phi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbp_phi->GetZaxis()->SetTitle(ZTitleName.c_str());


   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(4);

   if(hMC_sbpr_phi->GetMaximum()>5)
      hMC_sbpr_phi->SetMaximum(5);

   if(hMC_sbpr_phi->GetMinimum()<-5)
      hMC_sbpr_phi->SetMinimum(-5);

   hMC_sbpr_phi->Draw("lego20");

   if(selfmix){
      hMC_sbpr_phi->GetYaxis()->SetTitle(("PbPb/pp MC " + YTitleName).c_str());
      hMC_sbpr_phi->GetXaxis()->SetTitle(("PbPb/pp MC " + XTitleName).c_str());
   }else{
      hMC_sbpr_phi->GetYaxis()->SetTitle(("PbPb/pp MC " + YTitleName).c_str());
      hMC_sbpr_phi->GetXaxis()->SetTitle(("PbPb/pp MC " + XTitleName).c_str());
   }

   hMC_sbpr_phi->GetXaxis()->SetTitleOffset(3.0);
   hMC_sbpr_phi->GetYaxis()->SetTitleOffset(2.5);
   hMC_sbpr_phi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbpr_phi->GetZaxis()->SetTitle(ZTitleName.c_str());


   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/2DBkgSub/%s/Ztrack_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f.png",typeofdata,HistName.c_str(),typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   
   c->Clear();

   c->Divide(2,2);
   c->cd(1);

   hMC_sb_phi->Draw("COLZ");
   hMC_sb_phi->GetYaxis()->SetTitle(("Signal - Background MC " + YTitleName).c_str());
   hMC_sb_phi->GetXaxis()->SetTitle(("Signal - Background MC " + XTitleName).c_str());

   hMC_sb_phi->GetXaxis()->SetTitleOffset(2.0);
   hMC_sb_phi->GetYaxis()->SetTitleOffset(2.0);
   hMC_sb_phi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_phi->GetZaxis()->SetTitle(ZTitleName.c_str());

   pt0->Draw();

   c->cd(2);

   hpp_phi->Draw("COLZ");

   if(selfmix){
      hpp_phi->GetYaxis()->SetTitle(("pp Signal - Background MC " + YTitleName).c_str());
      hpp_phi->GetXaxis()->SetTitle(("pp Signal - Background MC " + XTitleName).c_str());
   }else{
      hpp_phi->GetYaxis()->SetTitle(("pp MC " + YTitleName).c_str());
      hpp_phi->GetXaxis()->SetTitle(("pp MC " + XTitleName).c_str());
   }

   hpp_phi->GetXaxis()->SetTitleOffset(2.0);
   hpp_phi->GetYaxis()->SetTitleOffset(2.0);
   hpp_phi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_phi->GetZaxis()->SetTitle(ZTitleName.c_str());

   pt->Draw();

   c->cd(3);

   hMC_sbp_phi->Draw("COLZ");

   hMC_sbp_phi->GetYaxis()->SetTitle(("PbPb-pp MC " + YTitleName).c_str());
   hMC_sbp_phi->GetXaxis()->SetTitle(("PbPb-pp MC " + XTitleName).c_str());


   hMC_sbp_phi->GetXaxis()->SetTitleOffset(2.0);
   hMC_sbp_phi->GetYaxis()->SetTitleOffset(2.0);
   hMC_sbp_phi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbp_phi->GetZaxis()->SetTitle(ZTitleName.c_str());

   c->cd(4);

   hMC_sbpr_phi->Draw("COLZ");

   hMC_sbpr_phi->GetYaxis()->SetTitle(("PbPb/pp MC " + YTitleName).c_str());
   hMC_sbpr_phi->GetXaxis()->SetTitle(("PbPb/pp MC " + XTitleName).c_str());


   hMC_sbpr_phi->GetXaxis()->SetTitleOffset(2.0);
   hMC_sbpr_phi->GetYaxis()->SetTitleOffset(2.0);
   hMC_sbpr_phi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sbpr_phi->GetZaxis()->SetTitle(ZTitleName.c_str());


   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/2DBkgSub/%s/Ztrack_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_COLZ.png",typeofdata,HistName.c_str(),typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   
   c->Clear();

}

void Z2DBkgSub_loop(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000)
{

   //double bineta = 0.032, binphi = M_PI/50;

   string HistName[] = {"HGenZEtaPhi", "HGenTrackEtaPhi", "HEtaPhi"};
   string XTitleName[] = {"#eta_{Z}", "#eta_{track}", "#Delta#eta_{Z,track}"};
   string YTitleName[] = {"#phi_{Z}", "#phi_{track}", "#Delta#phi_{Z,track}"};
   string ZTitleName[] = {"dN/d#etad#phi", "dN/d#etad#phi","dN/d#Delta#etad#Delta#phi"};
   int rebin_num[] = {5,5,5};

   int i_draw = sizeof(HistName)/sizeof(HistName[0]);

   for(int i=0; i<i_draw; i++)
      Z2DBkgSub_single(binnum, ptL, ptH, centL, centH, TptL, TptH, 
         HistName[i], XTitleName[i], YTitleName[i], ZTitleName[i], rebin_num[i]);

}

int main(int argc, char *argv[]){

   style();

/*
   file_sigMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSignal_v17_PFmuon.root","read");
   //file_sigMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen_v17_PFmuon.root","read");
   
   if(selfmix)
      file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSigBkg_v17d_PFmuon_350_10HF_ov20.root","read");
   else
      file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCBackground_v17d_10HF.root","read");
      //file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCBackgroundGen_v17_PFmuon.root","read");
      //file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCGenbkg_v17d_10HF.root","read");
   
   file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMC_v17_PFmuon.root","read");
   //file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMCGen_v17_PFmuon.root","read");
   //file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen0Sub_v17_PFmuon.root","read");
 */  

   file_ppbkgMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMCSigBkg_v17d_PFmuon_143_10HF.root","read");
   //file_ppbkgMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMCSigBkg_v17d_Cent10_143.root","read");


   file_sigMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen_v17_PFmuon.root","read");
   file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCGenbkg_v17d_10HF.root","read");
   file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMCGen_v17_PFmuon.root","read");

   Z2DBkgSub_loop(40, 40, 200,  0, 10,  1, 1000);
   Z2DBkgSub_loop(40, 40, 200,  0, 10,  1, 2);
   Z2DBkgSub_loop(40, 40, 200,  0, 10,  2, 4);
   Z2DBkgSub_loop(40, 40, 200,  0, 10,  4, 10);

   Z2DBkgSub_loop(40, 40, 200,  0, 90,  1, 2);

   file_sigMC->Close();
   file_bkgMC->Close();
   file_ppMC->Close();
   file_ppbkgMC->Close();

   //gSystem->Exec(Form("convert +append /eos/user/p/pchou/figs/track/%s/2DBkgSub/*Eta/*40_200_0_10_1_2.png /eos/user/p/pchou/figs/track/%s/BasicBkgSub/Eta_merge.png",typeofdata,typeofdata));
   //gSystem->Exec(Form("convert +append /eos/user/p/pchou/figs/track/%s/2DBkgSub/*Phi/*40_200_0_10_1_2.png /eos/user/p/pchou/figs/track/%s/BasicBkgSub/Phi_merge.png",typeofdata,typeofdata));
   //gSystem->Exec(Form("convert -append /eos/user/p/pchou/figs/track/%s/2DBkgSub/*_merge.png /eos/user/p/pchou/figs/track/%s/BasicBkgSub/merge.png",typeofdata,typeofdata));

   return 0;

}
