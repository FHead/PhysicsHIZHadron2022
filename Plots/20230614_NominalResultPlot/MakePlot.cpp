#include <iostream>
#include <vector>
using namespace std;

#include "TCanvas.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TPad.h"
#include "TGaxis.h"
#include "TFile.h"
#include "TLatex.h"
#include "TGraph.h"
#include "TLegend.h"

#include "DataHelper.h"

#include "CommandLine.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void SetPad(TPad *P);
void SetWorld(TH2D *H);
void SetAxis(TGaxis *A);
TH1D *GetHistogram(TFile *F, string ToPlot, string Tag, int Color);
TH1D *BuildSystematics(TFile *F, TH1D *H, string ToPlot, string Tag, int Color);
void HistogramSelfSubtract(TH1D *H);
TH1D *SubtractHistogram(TH1D *H, TH1D *HRef);
TH1D *DivideHistogram(TH1D *H, TH1D *HRef);
void PrintHistogram(TFile *F, string Name);
void PrintHistogram(TH1D *H);
void HistogramShifting(TH1D *H, string TagShift, DataHelper ShiftFile, int iF);

int main(int argc, char *argv[])
{
   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);

   string OutputBase = CL.Get("OutputBase", "Plot");
   string ShiftFileName = CL.Get("ShiftFileName", "/afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/BasicDistribution/20230629_CountSkim/SkimCount/20240121/SkimCount_nominal_centN-v17d.dh");

   //bool LogScale                  = CL.GetBool("LogScale", false);

   vector<string> DataFiles       = CL.GetStringVector("DataFiles",
      vector<string>{"Root/PPData.root", "Root/Data.root"});
   bool SkipSubtract              = CL.GetBool("SkipSubtract", true);
   vector<string> SubtractFiles   = CL.GetStringVector("SubtractFiles",
      vector<string>{"None", "Root/DataMix.root"});
   double SubtractFudgeFactor     = CL.GetDouble("SubtractFudgeFactor", 1.00);
   bool SkipSelfSubtract          = CL.GetBool("SkipSelfSubtract", false);
   bool SkipSystematics           = CL.GetBool("SkipSystematics", false);
   bool SkipShifting              = CL.GetBool("SkipShifting", true);
   bool CompareDivide             = CL.GetBool("CompareDivide", false);
   vector<string> SystematicFiles = (SkipSystematics == false) ? CL.GetStringVector("SystematicFiles") : vector<string>();
   vector<string> CurveLabels     = CL.GetStringVector("CurveLabels",
      vector<string>{"pp", "PbPb 0-30%"});
   string ToPlot                  = CL.Get("ToPlot", "DeltaPhi");
   vector<string> Tags            = CL.GetStringVector("Tags",
   vector<string>
   {
      "Centrality_0_30_ZPT_40_200_TrackPT_10_20_PV_0_10",
      "Centrality_0_30_ZPT_40_200_TrackPT_20_50_PV_0_10",
      "Centrality_0_30_ZPT_40_200_TrackPT_50_100_PV_0_10",
      // "Centrality_30_90_ZPT_40_200_TrackPT_10_20_PV_0_10",
      // "Centrality_30_90_ZPT_40_200_TrackPT_20_50_PV_0_10",
      // "Centrality_30_90_ZPT_40_200_TrackPT_50_100_PV_0_10"
   });

   vector<string> TagShifts = CL.GetStringVector("TagShifts",
   vector<string>
   {
      "Count_ZPT_40_200_Cent_0_10_TrackPT_1p00_2p00",
      "Count_ZPT_40_200_Cent_0_10_TrackPT_2p00_4p00",
      "Count_ZPT_40_200_Cent_0_10_TrackPT_4p00_10p00",

   });
   vector<string> SecondTags      = CL.GetStringVector("SecondTags", vector<string>());
   vector<string> Labels          = CL.GetStringVector("Labels",
   vector<string>
   {
      "1 < p_{T}^{trk} < 2 GeV",
      "2 < p_{T}^{trk} < 5 GeV",
      "5 < p_{T}^{trk} < 10 GeV",
      // "30-90%, 1 < p_{T}^{trk} < 2 GeV",
      // "30-90%, 2 < p_{T}^{trk} < 5 GeV",
      // "30-90%, 5 < p_{T}^{trk} < 10 GeV"
   });

   vector<string> ExtraInfo       = CL.GetStringVector("ExtraInfo",
   vector<string>
   {
      "40 < p_{T}^{Z} < 200 GeV",
      ""
   });

   if(SystematicFiles.size() == 0)
      SkipSystematics = true;

   string PbPbLumi = "1.67 nb^{-1}";
   string PPLumi = "301 pb^{-1}";

   int NFile = DataFiles.size();
   int NColumn = Tags.size();

   double XMin = CL.GetDouble("XMin", 0);
   double XMax = CL.GetDouble("XMax", M_PI);
   double YMin = CL.GetDouble("YMin", -5);
   double YMax = CL.GetDouble("YMax", 10);
   double RMin = CL.GetDouble("RMin", -5);
   double RMax = CL.GetDouble("RMax", 5);

   int XAxisSpacing = 510;
   int YAxisSpacing = 510;
   int RAxisSpacing = 505;

   string XAxisLabel = CL.Get("XAxisLabel", "|#Delta#phi_{trk,Z}|");
   string YAxisLabel = CL.Get("YAxisLabel", "<#DeltaN_{ch}>/event");
   string RAxisLabel = CL.Get("RAxisLabel", "Difference to pp");

   double MarginLeft    = 100;
   double MarginRight   = 50;
   double MarginTop     = 50;
   double MarginBottom  = 100;
   double PadWidth      = 500;
   double PadHeight     = 500;
   double RPadHeight    = 200;

   double CanvasWidth   = MarginLeft + PadWidth * NColumn + MarginRight;
   double CanvasHeight  = MarginTop + PadHeight + RPadHeight + MarginBottom;

   double XMarginLeft   = MarginLeft / CanvasWidth;
   double XMarginRight  = MarginRight / CanvasWidth;
   double XMarginTop    = MarginTop / CanvasHeight;
   double XMarginBottom = MarginBottom / CanvasHeight;
   double XPadWidth     = PadWidth / CanvasWidth;
   double XPadHeight    = PadHeight / CanvasHeight;
   double XRPadHeight   = RPadHeight/ CanvasHeight;

   double LegendLeft    = CL.GetDouble("LegendLeft", 0.08);
   double LegendBottom  = CL.GetDouble("LegendBottom", 0.40);

   // Open input files
   vector<TFile *> File(NFile);
   for(int iF = 0; iF < NFile; iF++)
      File[iF] = new TFile(DataFiles[iF].c_str());
   
   vector<TFile *> SubtractFile(NFile);
   if(SkipSubtract == false)
   {
      for(int iF = 0; iF < NFile; iF++)
         SubtractFile[iF] = new TFile(SubtractFiles[iF].c_str());
   }
   
   vector<TFile *> SysFile(NFile);
   if(SkipSystematics == false)
   {
      for(int iF = 0; iF < NFile; iF++)
         SysFile[iF] = new TFile(SystematicFiles[iF].c_str());

      // for(int iF = 0; iF < NFile; iF++)
      // {
      //    for(int iC = 0; iC < NColumn; iC++)
      //       PrintHistogram(SysFile[iF], Form("H%s_%s", ToPlot.c_str(), Tags[iC].c_str()));
      // }
   }

   // Setup canvas and pads
   TCanvas Canvas("Canvas", "", CanvasWidth, CanvasHeight);

   vector<TPad *> Pad(NColumn);
   vector<TPad *> RPad(NColumn);
   for(int iC = 0; iC < NColumn; iC++)
   {
      Pad[iC] = new TPad(Form("P%d", iC), "",
         XMarginLeft + XPadWidth * iC, XMarginBottom + XRPadHeight,
         XMarginLeft + XPadWidth * (iC + 1), XMarginBottom + XRPadHeight + XPadHeight);
      RPad[iC] = new TPad(Form("RP%d", iC), "",
         XMarginLeft + XPadWidth * iC, XMarginBottom,
         XMarginLeft + XPadWidth * (iC + 1), XMarginBottom + XRPadHeight);

      //if(LogScale == true)
      //   Pad[iC]->SetLogy();

      SetPad(Pad[iC]);
      SetPad(RPad[iC]);
   }

   // Setup world histograms
   vector<TH2D *> HWorld(NColumn);
   vector<TH2D *> HRWorld(NColumn);
   for(int iC = 0; iC < NColumn; iC++)
   {
      HWorld[iC] = new TH2D(Form("HWorld%d", iC), "", 100, XMin, XMax, 100, YMin, YMax);
      HRWorld[iC] = new TH2D(Form("HRWorld%d", iC), "", 100, XMin, XMax, 100, RMin, RMax);
      
      SetWorld(HWorld[iC]);
      SetWorld(HRWorld[iC]);
   }

   // Setup axes
   Canvas.cd();
   vector<TGaxis *> XAxis(NColumn), YAxis(1), RAxis(1);
   for(int iC = 0; iC < NColumn; iC++)
   {
      XAxis[iC] = new TGaxis(XMarginLeft + XPadWidth * iC, XMarginBottom,
                             XMarginLeft + XPadWidth * (iC + 1), XMarginBottom,
                             XMin, XMax, XAxisSpacing, "S");
      XAxis[iC]->SetTickSize(0.03 / XPadWidth /*CanvasWidth / CanvasHeight*/);
      SetAxis(XAxis[iC]);
   }
   YAxis[0] = new TGaxis(XMarginLeft, XMarginBottom + XRPadHeight,
                         XMarginLeft, XMarginBottom + XRPadHeight + XPadHeight,
                         YMin, YMax, YAxisSpacing, "S");
   YAxis[0]->SetTickSize(0.03 / XPadHeight * CanvasHeight / CanvasWidth);
   SetAxis(YAxis[0]);
   RAxis[0] = new TGaxis(XMarginLeft, XMarginBottom,
                         XMarginLeft, XMarginBottom + XRPadHeight,
                         RMin, RMax, RAxisSpacing, "S");
   RAxis[0]->SetTickSize(0.03 / XRPadHeight * CanvasHeight / CanvasWidth);
   SetAxis(RAxis[0]);

   // Setup axis labels
   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();

   for(int iC = 0; iC < NColumn; iC++)
   {
      Latex.SetTextAngle(0);
      Latex.SetTextAlign(22);
      Latex.DrawLatex(XMarginLeft + XPadWidth * (iC + 0.5), XMarginBottom * 0.4, XAxisLabel.c_str());
   }
   Latex.SetTextAngle(90);
   Latex.DrawLatex(XMarginLeft * 0.35, XMarginBottom + XRPadHeight + XPadHeight * 0.5, YAxisLabel.c_str());
   Latex.DrawLatex(XMarginLeft * 0.35, XMarginBottom + XRPadHeight * 0.5, RAxisLabel.c_str());

   // Add decorations
   Latex.SetTextAngle(0);
   Latex.SetTextAlign(11);
   Latex.DrawLatex(XMarginLeft, XMarginBottom + XRPadHeight + XPadHeight + 0.01,
      "#font[62]{CMS} #font[52]{Preliminary}");
   Latex.SetTextAlign(31);
   Latex.DrawLatex(XMarginLeft + XPadWidth * NColumn, XMarginBottom + XRPadHeight + XPadHeight + 0.01,
      Form("PbPb (pp) 5.02 TeV %s (%s)", PbPbLumi.c_str(), PPLumi.c_str()));

   // Retrieve histograms
   vector<vector<TH1D *>> HData(NColumn);

   DataHelper ShiftFile(ShiftFileName);

   for(int iC = 0; iC < NColumn; iC++)
   {
      HData[iC].resize(NFile);

      for(int iF = 0; iF < NFile; iF++)
      {
         string Tag = Tags[iC];
         string TagShift = TagShifts[iC];
         if(SecondTags.size() == NColumn && iF == 1)
            Tag = SecondTags[iC];
            
         // cout << "???" << endl;
         // PrintHistogram(SysFile[iF], Form("H%s_%s", ToPlot.c_str(), Tag.c_str()));
         // PrintHistogram(File[iF], Form("H%s_%s", ToPlot.c_str(), Tag.c_str()));
         
         HData[iC][iF] = GetHistogram(File[iF], ToPlot, Tag, Colors[iF]);
         
         if(SkipSubtract == false)
         {
            TH1D *HSubtract = GetHistogram(SubtractFile[iF], ToPlot, Tag, Colors[iF]);
            if(HSubtract != nullptr)
               HData[iC][iF]->Add(HSubtract, -1 * SubtractFudgeFactor);
         }
         
         if(SkipSelfSubtract == false)
            HistogramSelfSubtract(HData[iC][iF]);

         if(SkipShifting == false)
            HistogramShifting(HData[iC][iF],TagShift,ShiftFile,iF);
         
         // PrintHistogram(File[iF], Form("H%s_%s", ToPlot.c_str(), Tag.c_str()));
         // PrintHistogram(HData[iC][iF]);
         
         // PrintHistogram(SysFile[iF], Form("H%s_%s", ToPlot.c_str(), Tag.c_str()));
      }
   }
   
   vector<vector<TH1D *>> HDataSys(NColumn);
   if(SkipSystematics == false)
   {
      for(int iC = 0; iC < NColumn; iC++)
      {
         HDataSys[iC].resize(NFile);
         
         for(int iF = 0; iF < NFile; iF++)
         {
            string Tag = Tags[iC];
            if(SecondTags.size() == NColumn && iF == 1)
               Tag = SecondTags[iC];
            
            // cout << "!!!" << endl;
            // PrintHistogram(SysFile[iF], Form("H%s_%s", ToPlot.c_str(), Tag.c_str()));
            
            HDataSys[iC][iF] = BuildSystematics(SysFile[iF], HData[iC][iF], ToPlot, Tag, Colors[iF]);
   
            // PrintHistogram(SysFile[iF], Form("H%s_%s", ToPlot.c_str(), Tag.c_str()));
         }   
      }

   }
   
   vector<vector<TH1D *>> HDataDiff(NColumn);
   vector<vector<TH1D *>> HDataSysDiff(NColumn);
   for(int iC = 0; iC < NColumn; iC++)
   {
      HDataDiff[iC].resize(NFile);
      HDataSysDiff[iC].resize(NFile);
      for(int iF = 0; iF < NFile; iF++)
      {
         if(CompareDivide == false){
            HDataDiff[iC][iF] = SubtractHistogram(HData[iC][iF], HData[iC][0]);
            if(SkipSystematics == false && HDataSys[iC][iF] != nullptr)
               HDataSysDiff[iC][iF] = SubtractHistogram(HDataSys[iC][iF], HData[iC][0]);
         }else{
            HDataDiff[iC][iF] = DivideHistogram(HData[iC][iF], HData[iC][0]);
            if(SkipSystematics == false && HDataSys[iC][iF] != nullptr)
               HDataSysDiff[iC][iF] = DivideHistogram(HDataSys[iC][iF], HData[iC][0]);
         }         
      }
   }

   // Setup legend
   TLegend Legend(LegendLeft, LegendBottom, LegendLeft + 0.40, LegendBottom + NFile * 0.1);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035 * CanvasHeight / PadHeight);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);

   double x[9]   = {2.349999999999999867e-01, 7.049999999999999600e-01, 1.175000000000000044e+00, 1.645000000000000018e+00, 2.040000000000000036e+00, 2.354999999999999982e+00, 2.669999999999999929e+00, 2.904999999999999805e+00, 3.060000000000000053e+00};
   double y24[9] = {7.836891324048251839e-01, 8.314701080954287615e-01, 9.302873851791002568e-01, 1.118398389215367272e+00, 1.431325590865351272e+00, 1.929228093985401848e+00, 2.826899540479912432e+00, 4.130493143300970615e+00, 5.211521328579531875e+00};
   double y12[9] = {3.209130112267858159e+00, 3.413356794170638864e+00, 3.738047789508202712e+00, 4.408176202331031135e+00, 5.299470850309038639e+00, 6.318805394385380581e+00, 7.963200037766525519e+00, 9.373303726595484164e+00, 1.009497352789722946e+01};

   double xeta0[41]  = {-8.000000000000000000e+00,-7.599999999999999645e+00,-7.200000000000000178e+00,-6.799999999999999822e+00,-6.400000000000000355e+00,-6.000000000000000000e+00,-5.599999999999999645e+00,-5.199999999999999289e+00,-4.799999999999999822e+00,-4.400000000000000355e+00,-4.000000000000000000e+00,-3.599999999999999645e+00,-3.199999999999999289e+00,-2.799999999999999822e+00,-2.399999999999999467e+00,-2.000000000000000000e+00,-1.599999999999999645e+00,-1.199999999999999289e+00,-7.999999999999998224e-01,-3.999999999999994671e-01, 0.000000000000000000e+00, 4.000000000000003553e-01, 8.000000000000007105e-01, 1.200000000000001066e+00, 1.600000000000001421e+00, 2.000000000000000000e+00, 2.400000000000000355e+00, 2.800000000000000711e+00, 3.200000000000001066e+00, 3.600000000000001421e+00, 4.000000000000000000e+00, 4.400000000000000355e+00, 4.800000000000000711e+00, 5.200000000000001066e+00, 5.600000000000001421e+00, 6.000000000000000000e+00, 6.400000000000000355e+00, 6.800000000000000711e+00, 7.200000000000001066e+00, 7.600000000000001421e+00, 8.000000000000000000e+00} ;
   double yeta024[41] = {4.806987943818639974e-03, 9.880710439151382807e-03, 1.709027133316882302e-02, 2.910827710362672363e-02, 3.901352263380930552e-02, 4.606934945291529110e-02, 6.142613747261948393e-02, 7.413215475688138267e-02, 9.211688117739419424e-02, 1.144785589470640602e-01, 1.527811620627367861e-01, 1.609737682846303364e-01, 1.984340162185953271e-01, 2.087236068614375106e-01, 2.238325289643768867e-01, 2.199548001334495073e-01, 2.332529750233778842e-01, 2.304643231123191804e-01, 2.769080358826803145e-01, 2.739126987030277016e-01, 2.835851727719385096e-01, 2.805476983599335394e-01, 2.705504864264959286e-01, 2.328074957549170765e-01, 2.382936329613525861e-01, 2.343486934906347519e-01, 2.113760145246216249e-01, 2.228634073023859630e-01, 1.935341796946895288e-01, 1.688880391660423363e-01, 1.384518527364451967e-01, 1.180145930897618101e-01, 8.987656151915404679e-02, 7.448932447307568538e-02, 5.213479585592990795e-02, 4.528412114988236703e-02, 4.542458511066461285e-02, 2.964337442792751645e-02, 1.388574967557457303e-02, 8.812116241455383511e-03, 4.539592432825410341e-03} ;
   double yeta012[41] = {2.296775566860532330e-02, 4.780164620086321120e-02, 6.544062158660465811e-02, 1.006195968931892781e-01, 1.455862898884915380e-01, 2.105307729079504975e-01, 2.538267681531374831e-01, 3.400316634321805531e-01, 4.437173885201119994e-01, 5.409442640122228418e-01, 6.591429068579626183e-01, 7.844985628314998793e-01, 8.423164102427826982e-01, 9.057385217911761988e-01, 9.336744869821629322e-01, 9.368175305170352019e-01, 9.745358939137289678e-01, 1.032007406425741847e+00, 1.061990821655705686e+00, 1.120393876407260958e+00, 1.144977302628758631e+00, 1.116480331527875069e+00, 1.092157705058768524e+00, 1.064265816486781091e+00, 1.001251333088074569e+00, 9.650458123090117635e-01, 9.306469789422366912e-01, 9.071688971752214226e-01, 8.437260942758471050e-01, 7.818281907858524171e-01, 6.752825206752051113e-01, 5.448362147540268818e-01, 4.283462490730268746e-01, 3.388750846897823910e-01, 2.597846842546887025e-01, 1.939288885484826142e-01, 1.629482402808811459e-01, 1.035673709834486755e-01, 6.464442291174231359e-02, 4.112434382586951237e-02, 2.483356926174676294e-02} ;
   
   double xeta[21], yeta12[21], yeta24[21];

   double SumXY_0 = 1; //std::stod(ShiftFile[TagShifts[0]]["PbPb Data Sig-Bkg NZ"].GetRepresentation()) / 41;
   double SumXY_1 = 1; //std::stod(ShiftFile[TagShifts[1]]["PbPb Data Sig-Bkg NZ"].GetRepresentation()) / 41;

   std::cout<< "SumXY_0 = "<<SumXY_0<<std::endl;

   double sum12=0, sum24=0, sumeta12=0, sumeta24=0, sumeta12_phi=0, sumeta24_phi=0;

   for(int iE=0;iE<9;iE++){
      sum12+=y12[iE];
      sum24+=y24[iE];
   }
   sum12*=(x[1]-x[0]);
   sum24*=(x[1]-x[0]);

   for(int iE=0;iE<41;iE++){
      sumeta12+=yeta012[iE];
      sumeta24+=yeta024[iE];
      if(fabs(xeta0[iE]) < 2.4){
         sumeta12_phi+=yeta012[iE];
         sumeta24_phi+=yeta024[iE];
      }
   }
   sumeta12+=(xeta[1]-xeta[0]);
   sumeta24+=(xeta[1]-xeta[0]);
   sumeta12_phi+=(xeta[1]-xeta[0]);
   sumeta24_phi+=(xeta[1]-xeta[0]);

   std::cout<<"sum12 = "<<sum12<<", sum24 = "<<sum24<<std::endl;
   std::cout<<"sumeta12 = "<<sumeta12<<", sumeta24 = "<<sumeta24<<std::endl;
   std::cout<<"sumeta12_phi = "<<sumeta12_phi<<", sumeta24_phi = "<<sumeta24_phi<<std::endl;



   for(int iE=0;iE<20;iE++){
      xeta[iE] = (fabs(xeta0[iE])+fabs(xeta0[40-iE]))/2;
      yeta12[iE] = (yeta012[iE]+yeta012[40-iE])*SumXY_0;
      yeta24[iE] = (yeta024[iE]+yeta024[40-iE])*SumXY_1;
   }

   xeta[20] = fabs(xeta0[20]); yeta12[20] = yeta012[20]*2*SumXY_0; yeta24[20] = yeta024[20]*2*SumXY_1;

   auto g12 = new TGraph(9,x,y12);
   auto g24 = new TGraph(9,x,y24);

   auto geta12 = new TGraph(21,xeta,yeta12);
   auto geta24 = new TGraph(21,xeta,yeta24);

   g12->SetLineWidth(2);
   g24->SetLineWidth(2);

   geta12->SetLineWidth(2);
   geta24->SetLineWidth(2);

   g12->SetLineColor(Colors[NFile]);
   g24->SetLineColor(Colors[NFile]);
   geta12->SetLineColor(Colors[NFile]);
   geta24->SetLineColor(Colors[NFile]);

   g12->SetTitle("");
   g24->SetTitle("");
   geta12->SetTitle("");
   geta24->SetTitle("");

   // Merge bins for the lowest pT region
   for(int iF = 0; iF < NFile; iF++){
      HData[0][iF]->Rebin(2);
      HDataSys[0][iF]->Rebin(2);

      HData[0][iF]->Scale(1./2);
      HDataSys[0][iF]->Scale(1./2);

      HDataSysDiff[0][iF]->Rebin(2);
      HDataDiff[0][iF]->Rebin(2);

      HDataSysDiff[0][iF]->Scale(1./2);
      HDataDiff[0][iF]->Scale(1./2);
   }

   // Draw things
   for(int iC = 0; iC < NColumn; iC++)
   {
      Pad[iC]->cd();
      HWorld[iC]->Draw("axis");

      TLine *l1 = new TLine(XMin,0,XMax,0);
      l1->SetLineWidth(2);
      l1->Draw();

      for(int iF = 0; iF < NFile; iF++)
      {
         if(SkipSystematics == false && HDataSys[iC][iF] != nullptr)
            HDataSys[iC][iF]->Draw("same e2");
         HData[iC][iF]->Draw("same");
      }

      Latex.SetTextAngle(0);
      Latex.SetTextAlign(33);
      Latex.SetTextSize(0.035 * CanvasHeight / PadHeight);
      Latex.DrawLatex(0.97, 0.97, Labels[iC].c_str());

      if(iC == 0)   // adding extra info!
      {
         for(int i = 0; i < (int)ExtraInfo.size(); i++)
         {
            Latex.SetTextAngle(0);
            Latex.SetTextAlign(11);
            Latex.SetTextSize(0.035 * CanvasHeight / PadHeight);
            Latex.DrawLatex(0.08, 0.85 - i * 0.075, ExtraInfo[i].c_str());
         }
      }
      if(iC == NColumn - 1)   // adding legend!
      {
         for(int iF = 0; iF < NFile; iF++)
            Legend.AddEntry(HData[iC][iF], CurveLabels[iF].c_str(), "pl");
         
         if((ToPlot.compare("DeltaPhi")==0||ToPlot.compare("DeltaEta")==0)&&ExtraInfo[1].compare("0-10%")==0)
            Legend.AddEntry(g12, "Theory prediction", "l");
         
         Legend.Draw();
      }

      if(iC==0 &&ToPlot.compare("DeltaPhi")==0&&ExtraInfo[1].compare("0-10%")==0){
         g12->Draw("L");
      }else if(iC==1 &&ToPlot.compare("DeltaPhi")==0&&ExtraInfo[1].compare("0-10%")==0){
         g24->Draw("L");
      }else if(iC==0 &&ToPlot.compare("DeltaEta")==0&&ExtraInfo[1].compare("0-10%")==0){
         geta12->Draw("L");
      }else if(iC==1 &&ToPlot.compare("DeltaEta")==0&&ExtraInfo[1].compare("0-10%")==0){
         geta24->Draw("L");
      }

      RPad[iC]->cd();
      HRWorld[iC]->Draw("axis");
      
      for(int iF = 0; iF < NFile; iF++)
      {
         if(SkipSystematics == false && HDataSysDiff[iC][iF] != nullptr)
            HDataSysDiff[iC][iF]->Draw("same e2");
         HDataDiff[iC][iF]->Draw("same");
      }

      
   }

   // Finally we have the plots
   Canvas.SaveAs((OutputBase + ".pdf").c_str());
   // Canvas.SaveAs((OutputBase + ".png").c_str());
   // Canvas.SaveAs((OutputBase + ".C").c_str());

   // Close input files
   for(int iF = 0; iF < NFile; iF++)
   {
      if(SkipSystematics == false && SysFile[iF] != nullptr)
      {
         SysFile[iF]->Close();
         delete SysFile[iF];
      }
   }
   for(int iF = 0; iF < NFile; iF++)
   {
      if(File[iF] != nullptr)
      {
         File[iF]->Close();
         delete File[iF];
      }
   }

   return 0;
}

void SetPad(TPad *P)
{
   if(P == nullptr)
      return;
   P->SetLeftMargin(0);
   P->SetTopMargin(0);
   P->SetRightMargin(0);
   P->SetBottomMargin(0);
   P->SetTickx(false);
   P->SetTicky(false);
   P->Draw();
}

void SetWorld(TH2D *H)
{
   if(H == nullptr)
      return;
   H->SetStats(0);
   H->GetXaxis()->SetTickLength(0);
   H->GetYaxis()->SetTickLength(0);
}

void SetAxis(TGaxis *A)
{
   if(A == nullptr)
      return;
   A->SetLabelFont(42);
   A->SetLabelSize(0.035);
   A->SetMaxDigits(6);
   A->SetMoreLogLabels();
   A->Draw();
}

TH1D *GetHistogram(TFile *F, string ToPlot, string Tag, int Color)
{
   TH1D *H  = (TH1D *)F->Get(Form("H%s_%s", ToPlot.c_str(), Tag.c_str()));
   TH1D *HN = (TH1D *)F->Get(Form("HN_%s", Tag.c_str()));

   if(H == nullptr || HN == nullptr)
      return nullptr;

   static int ID = 0;
   ID = ID + 1;
   H = (TH1D *)H->Clone(Form("H%d", ID));

   double Integral = HN->GetBinContent(1);

   H->Scale(1 / Integral);
   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      double XMin = H->GetXaxis()->GetBinLowEdge(i);
      double XMax = H->GetXaxis()->GetBinUpEdge(i);

      H->SetBinContent(i, H->GetBinContent(i) / (XMax - XMin));
      H->SetBinError(i, H->GetBinError(i) / (XMax - XMin));
   }

   H->SetStats(0);
   H->SetMarkerStyle(20);
   H->SetLineWidth(2);
   H->SetMarkerSize(2);
   
   H->SetMarkerColor(Color);
   H->SetLineColor(Color);
   
   return H;
}

TH1D *BuildSystematics(TFile *F, TH1D *H, string ToPlot, string Tag, int Color)
{
   TH1D *HSys = (TH1D *)F->Get(Form("H%s_%s", ToPlot.c_str(), Tag.c_str()));
   if(HSys == nullptr)
      return nullptr;
   // HSys = (TH1D *)HSys->Clone();

   // PrintHistogram(F, Form("H%s_%s", ToPlot.c_str(), Tag.c_str()));
   
   static int ID = 0;
   ID = ID + 1;
   TH1D *HResult = (TH1D *)H->Clone(Form("HSys%d", ID));
   for(int i = 1; i <= H->GetNbinsX(); i++)
      HResult->SetBinError(i, HSys->GetBinContent(i));
   HResult->SetFillColorAlpha(Color, 0.25);
         
   // PrintHistogram(F, Form("H%s_%s", ToPlot.c_str(), Tag.c_str()));

   // cout << F->GetName() << endl;
   // cout << H->GetName() << endl;
   // for(int i = 1; i <= H->GetNbinsX(); i++)
   //    cout << i << " " << HSys->GetBinContent(i) << endl;

   return HResult;
}

void HistogramShifting(TH1D *H, string TagShift, DataHelper ShiftFile, int iF)
{
   if(H == nullptr)
      return;

   double SumX = 0;
   double SumXY = 0;
   double ErrXY = 0;
   if(iF==1) {
      SumXY = std::stod(ShiftFile[TagShift]["PbPb Data Sig-Bkg Ntrk/Nevt"].GetRepresentation());
      ErrXY = std::stod(ShiftFile[TagShift]["PbPb Data Sig-Bkg Ntrk/Nevt Error"].GetRepresentation());
      ErrXY = sqrt(ErrXY*ErrXY+SumXY*SumXY*0.05*0.05);
   }else if(iF==0){
      SumXY = std::stod(ShiftFile[TagShift]["pp Data Ntrk/Nevt"].GetRepresentation());
      ErrXY = std::stod(ShiftFile[TagShift]["pp Data Ntrk/Nevt Error"].GetRepresentation());
      ErrXY = sqrt(ErrXY*ErrXY+SumXY*SumXY*0.024*0.024);
   }else{
      SumXY = 0;
   }

   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      double XMin = H->GetXaxis()->GetBinLowEdge(i);
      double XMax = H->GetXaxis()->GetBinUpEdge(i);
      SumX = SumX + (XMax - XMin);
   }

   double Mean = SumXY / SumX;
   double Err = ErrXY / SumX;
   for(int i = 1; i <= H->GetNbinsX(); i++){
      H->SetBinContent(i, H->GetBinContent(i) + Mean);
      H->SetBinError(i,sqrt(H->GetBinError(i)*H->GetBinError(i) + Err*Err));
   }

}
void HistogramSelfSubtract(TH1D *H)
{
   if(H == nullptr)
      return;

   double SumX = 0;
   double SumXY = 0;
   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      double XMin = H->GetXaxis()->GetBinLowEdge(i);
      double XMax = H->GetXaxis()->GetBinUpEdge(i);
      double Y = H->GetBinContent(i);

      SumX = SumX + (XMax - XMin);
      SumXY = SumXY + (XMax - XMin) * Y;
   }

   double Mean = SumXY / SumX;
   for(int i = 1; i <= H->GetNbinsX(); i++)
      H->SetBinContent(i, H->GetBinContent(i) - Mean);
}

TH1D *SubtractHistogram(TH1D *H, TH1D *HRef)
{
   int N = H->GetNbinsX();

   static int ID = 0;
   ID = ID + 1;
   TH1D *HDiff = (TH1D *)H->Clone(Form("HDiff%d", ID));

   for(int i = 1; i <= N; i++)
   {
      HDiff->SetBinContent(i, H->GetBinContent(i) - HRef->GetBinContent(i));
      HDiff->SetBinError(i, H->GetBinError(i));
   }

   return HDiff;
}

TH1D *DivideHistogram(TH1D *H, TH1D *HRef)
{
   int N = H->GetNbinsX();

   static int ID = 0;
   ID = ID + 1;
   TH1D *HDiff = (TH1D *)H->Clone(Form("HDiff%d", ID));

   for(int i = 1; i <= N; i++)
   {
      HDiff->SetBinContent(i, H->GetBinContent(i) / HRef->GetBinContent(i));
      HDiff->SetBinError(i, H->GetBinError(i)/ HRef->GetBinContent(i));
   }

   return HDiff;
}

void PrintHistogram(TFile *F, string Name)
{
   if(F == nullptr)
      return;
   TH1D *H = (TH1D *)F->Get(Name.c_str());
   if(H == nullptr)
      return;

   cout << F->GetName() << " " << Name << endl;
   PrintHistogram(H);
}

void PrintHistogram(TH1D *H)
{
   if(H == nullptr)
      return;
   for(int i = 1; i <= H->GetNbinsX(); i++)
      cout << i << " " << H->GetBinContent(i) << endl;
}

