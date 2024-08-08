#include <TFile.h>
#include <TTree.h>
#include <TChain.h>
#include <TROOT.h>
#include <TCut.h>
#include <TH1D.h>
#include <TSystem.h>

#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

#include <iostream>
#include <fstream>
#include <iomanip>

#include "CommonFunctions.h"
#include "CommandLine.h"
#include "ProgressBar.h"

#include "DataHelper.h"

struct Configuration;
int main(int argc, char *argv[]);


struct Configuration
{
public:
   double ZPTMin;
   double ZPTMax;
   double CentMin;
   double CentMax;
   double TrackPTMin;
   double TrackPTMax;
public:
   Configuration() {}
   Configuration(double zptl, double zpth, double centl, double centh, double trackptl, double trackpth)
   {
      ZPTMin = zptl;
      ZPTMax = zpth;
      CentMin = centl;
      CentMax = centh;
      TrackPTMin = trackptl;
      TrackPTMax = trackpth;
   }
};

static double BinEdge[201] = {0, 10.5072, 11.2099, 11.8364, 12.478, 13.1194, 13.7623, 14.4081, 15.0709, 15.7532, 16.4673, 17.1881, 17.923, 18.673, 19.4865, 20.3033, 21.1536, 22.0086, 22.9046, 23.8196, 24.7924, 25.8082, 26.8714, 27.9481, 29.0828, 30.2757, 31.5043, 32.8044, 34.1572, 35.6142, 37.1211, 38.6798, 40.3116, 42.0398, 43.8572, 45.6977, 47.6312, 49.6899, 51.815, 54.028, 56.3037, 58.7091, 61.2024, 63.8353, 66.5926, 69.3617, 72.2068, 75.2459, 78.3873, 81.5916, 84.9419, 88.498, 92.1789, 95.9582, 99.8431, 103.739, 107.78, 111.97, 116.312, 120.806, 125.46, 130.269, 135.247, 140.389, 145.713, 151.212, 156.871, 162.729, 168.762, 174.998, 181.424, 188.063, 194.907, 201.942, 209.19, 216.683, 224.37, 232.291, 240.43, 248.807, 257.416, 266.256, 275.348, 284.668, 294.216, 304.053, 314.142, 324.488, 335.101, 345.974, 357.116, 368.547, 380.283, 392.29, 404.564, 417.122, 429.968, 443.116, 456.577, 470.357, 484.422, 498.78, 513.473, 528.479, 543.813, 559.445, 575.411, 591.724, 608.352, 625.344, 642.686, 660.361, 678.371, 696.749, 715.485, 734.608, 754.068, 773.846, 794.046, 814.649, 835.608, 856.972, 878.719, 900.887, 923.409, 946.374, 969.674, 993.435, 1017.62, 1042.21, 1067.28, 1092.72, 1118.64, 1144.96, 1171.71, 1198.98, 1226.67, 1254.82, 1283.46, 1312.65, 1342.21, 1372.27, 1402.85, 1433.93, 1465.49, 1497.62, 1530.29, 1563.49, 1597.22, 1631.49, 1666.37, 1701.8, 1737.75, 1774.35, 1811.51, 1849.29, 1887.75, 1926.79, 1966.6, 2006.97, 2047.99, 2089.71, 2132.1, 2175.23, 2219.17, 2263.72, 2309.2, 2355.43, 2402.47, 2450.33, 2499.05, 2548.66, 2599.16, 2650.59, 2703.03, 2756.32, 2810.75, 2866.27, 2922.91, 2980.54, 3039.47, 3099.53, 3160.98, 3223.66, 3287.71, 3353.18, 3420.34, 3489.13, 3559.72, 3632.06, 3706.18, 3782.42, 3860.78, 3941.42, 4024.52, 4110.27, 4199.4, 4292.8, 4394.49, 4519.52, 5199.95};
static double BinEdgeDown[201] = {0, 10.5071, 11.2094, 11.8357, 12.4763, 13.117, 13.7597, 14.4049, 15.0671, 15.7491, 16.4622, 17.1812, 17.9144, 18.6674, 19.4797, 20.2963, 21.1435, 21.9974, 22.8928, 23.8068, 24.7805, 25.7931, 26.8556, 27.9308, 29.0638, 30.2582, 31.4795, 32.7816, 34.1349, 35.5834, 37.0941, 38.6474, 40.2782, 42.0035, 43.8112, 45.6576, 47.5758, 49.6381, 51.6667, 53.7353, 55.8903, 58.1259, 60.4528, 62.8712, 65.3859, 67.9968, 70.7065, 73.5231, 76.4519, 79.4922, 82.6461, 85.9264, 89.3269, 92.8562, 96.5212, 100.322, 104.262, 108.344, 112.585, 116.971, 121.521, 126.225, 131.09, 136.127, 141.328, 146.721, 152.284, 158.014, 163.935, 170.054, 176.372, 182.878, 189.602, 196.532, 203.653, 211.017, 218.599, 226.387, 234.418, 242.667, 251.16, 259.886, 268.852, 278.071, 287.498, 297.2, 307.184, 317.409, 327.894, 338.66, 349.686, 360.996, 372.607, 384.508, 396.669, 409.133, 421.86, 434.906, 448.258, 461.916, 475.906, 490.16, 504.74, 519.663, 534.911, 550.453, 566.322, 582.525, 599.08, 615.968, 633.211, 650.805, 668.76, 687.048, 705.707, 724.774, 744.163, 763.9, 783.999, 804.528, 825.432, 846.746, 868.429, 890.523, 913.007, 935.952, 959.211, 982.919, 1007.08, 1031.63, 1056.62, 1082.08, 1107.96, 1134.24, 1160.99, 1188.22, 1215.91, 1244.06, 1272.69, 1301.85, 1331.45, 1361.51, 1392.07, 1423.18, 1454.77, 1486.93, 1519.57, 1552.81, 1586.55, 1620.87, 1655.79, 1691.26, 1727.27, 1763.93, 1801.12, 1838.97, 1877.47, 1916.61, 1956.45, 1996.89, 2038.04, 2079.84, 2122.35, 2165.52, 2209.53, 2254.24, 2299.83, 2346.19, 2393.31, 2441.28, 2490.16, 2539.86, 2590.57, 2642.16, 2694.74, 2748.23, 2802.81, 2858.47, 2915.33, 2973.2, 3032.28, 3092.56, 3154.24, 3217.19, 3281.45, 3347.18, 3414.6, 3483.65, 3554.56, 3627.2, 3701.66, 3778.25, 3856.97, 3937.98, 4021.48, 4107.62, 4197.21, 4291.05, 4393.19, 4518.6, 5199.95};
static double BinEdgeUp[201] = {0, 10.5075, 11.2107, 11.838, 12.4797, 13.1213, 13.7641, 14.4124, 15.0745, 15.7577, 16.473, 17.1939, 17.9297, 18.6812, 19.4958, 20.3143, 21.1648, 22.0218, 22.9159, 23.8328, 24.8059, 25.8204, 26.89, 27.9702, 29.1042, 30.3022, 31.528, 32.8347, 34.1896, 35.6439, 37.1542, 38.7172, 40.3518, 42.091, 43.9053, 45.7415, 47.6853, 49.7457, 51.8755, 54.0983, 56.3594, 58.7848, 61.2861, 63.9228, 66.6825, 69.4421, 72.297, 75.3547, 78.4967, 81.6977, 85.0755, 88.6211, 92.3058, 96.1071, 99.9975, 104.065, 108.272, 112.512, 116.906, 121.601, 126.465, 131.482, 136.866, 142.229, 147.786, 153.546, 159.571, 165.586, 171.902, 178.419, 185.063, 191.856, 199.055, 206.261, 213.999, 221.719, 229.671, 237.84, 246.088, 254.828, 263.883, 272.907, 282.236, 291.925, 301.519, 311.477, 321.691, 332.153, 342.892, 353.878, 365.161, 376.742, 388.577, 400.684, 413.075, 425.746, 438.711, 451.989, 465.556, 479.45, 493.608, 508.077, 522.891, 538.003, 553.415, 569.151, 585.216, 601.601, 618.354, 635.422, 652.84, 670.599, 688.699, 707.161, 726.014, 745.185, 764.687, 784.557, 804.838, 825.489, 846.537, 867.951, 889.752, 911.955, 934.588, 957.52, 980.912, 1004.73, 1028.94, 1053.57, 1078.67, 1104.17, 1130.07, 1156.39, 1183.2, 1210.47, 1238.17, 1266.38, 1295.02, 1324.16, 1353.71, 1383.77, 1414.35, 1445.41, 1477, 1509.09, 1541.74, 1574.88, 1608.59, 1642.83, 1677.66, 1713.07, 1748.98, 1785.47, 1822.63, 1860.33, 1898.72, 1937.73, 1977.42, 2017.71, 2058.62, 2100.25, 2142.57, 2185.56, 2229.38, 2273.91, 2319.2, 2365.33, 2412.22, 2459.94, 2508.52, 2557.98, 2608.35, 2659.61, 2711.86, 2765, 2819.23, 2874.58, 2930.97, 2988.46, 3047.12, 3106.95, 3168.15, 3230.6, 3294.37, 3359.58, 3426.47, 3494.95, 3565.21, 3637.21, 3711.03, 3786.91, 3864.85, 3945.11, 4027.8, 4113.06, 4201.73, 4294.72, 4395.9, 4520.5, 5199.95};


int main(int argc, char *argv[])
{

	cout<<"hi"<<endl;

	double piMass = 0.13957039;

	TChain *TreeSig = new TChain("Tree"); 
	TChain *TreeBkg = new TChain("Tree"); 
	TChain *TreePP0 = new TChain("Tree"); 
	
	TChain *TreeSigData = new TChain("Tree"); 
	TChain *TreeBkgData = new TChain("Tree"); 
	TChain *TreePP0Data = new TChain("Tree"); 

	CommandLine CL(argc, argv);

	string InputBase      = CL.Get("InputBase", "/eos/cms/store/group/phys_heavyions/pchou/");
   string OutputFileName = CL.Get("Output", "SkimCount.tex");
   string BkgDataDir     = CL.Get("BkgDataDir", "OutputDataBackground_v17_PFmuon");
   string BkgMCDir		  = CL.Get("BkgMCDir", "OutputMCBackground_v17d_PFmuon");
   //string BkgMCGenDir	  = CL.Get("BkgMCGenDir", "OutputMCGenbkg_v15c");

   string SigMCDir		  = CL.Get("SigMCDir", "OutputMC_v17_PFmuon");
   string SigPPMCDir     = CL.Get("SigPPMCDir", "OutputPPMC_v17_PFmuon");
   string SigPPDataDir	  = CL.Get("SigPPDataDir", "OutputPPData_v17_PFmuon");
   string SigDataDir	  = CL.Get("SigDataDir", "OutputData_v17_PFmuon");

	int CentUD            = CL.GetInteger("CentUD", 0);

	double Fraction       = CL.GetDouble("Fraction", 1.00);

	double HFShift        = CL.GetDouble("HFShift",682);
	double HFShiftData    = CL.GetDouble("HFShiftData",660);
	double HFTolerance    = CL.GetDouble("Tolerance",187.5);
	double HFToleranceData= CL.GetDouble("ToleranceData",150);
  //HFToleranceFraction   = CL.GetDouble("ToleranceFraction");

	int ZWtID			  = CL.GetInteger("ZWtID",-1);
	double VZMin		  = CL.GetDouble("VZMin",-15);
	double VZMax		  = CL.GetDouble("VZMax",15);

	int ppNPU			  = CL.GetInteger("ppNPU",1);

	bool IsDeltaEta     = CL.GetBool("IsDeltaEta", false);
	bool IsDeltaY       = CL.GetBool("IsDeltaY", false);

	ofstream fout;
	fout.open(OutputFileName);

	cout<<"Start to add trees"<<endl;

	//string YiBase = "/eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230310_ZHadronSkims/";

	TreeSig->Add((InputBase + SigMCDir + "/Result*.root?#Tree").c_str());
	TreePP0->Add((InputBase + SigPPMCDir + "/Result*.root?#Tree").c_str());
	TreeBkg->Add((InputBase + BkgMCDir + "/Result*.root?#Tree").c_str());
	TreeSigData->Add((InputBase + SigDataDir + "/Result*.root?#Tree").c_str());
	//TreeSigData->Add((YiBase + SigDataDir + "/Result6*.root?#Tree").c_str());
	TreeBkgData->Add((InputBase + BkgDataDir + "/Result*.root?#Tree").c_str());
	//TreeBkgData->Add((InputBase + BkgDataDir + "/Result6*.root?#Tree").c_str());
	TreePP0Data->Add((InputBase + SigPPDataDir + "/Result*.root?#Tree").c_str());
	//TreePP0Data->Add((YiBase + SigPPDataDir + "/Result6*.root?#Tree").c_str());

	cout<<"Trees added"<<endl;

	double cent[201];

   for(int i=0;i<201;i++){
   	if(CentUD==0)
   		cent[i]=BinEdge[i];
   	else if(CentUD==1)
   		cent[i]=BinEdgeUp[i];
   	else if(CentUD==2)
   		cent[i]=BinEdgeDown[i];
   	else
   		cent[i]=0;
   }

	// Note: fields are bin count, Z min, Z max, Cent. min, Cent. max, Track min, Track max

   int tablesize = 6;
	vector<Configuration> C;

	C.push_back(Configuration(40,200,0,10,1,2));
	C.push_back(Configuration(40,200,0,10,2,4));
	C.push_back(Configuration(40,200,0,10,4,10));
	C.push_back(Configuration(40,200,10,30,1,2));
	C.push_back(Configuration(40,200,10,30,2,4));
	C.push_back(Configuration(40,200,10,30,4,10));
	//C.push_back(Configuration(40,200,0,30,10,20));
	//C.push_back(Configuration(40,200,0,30,20,50));
	C.push_back(Configuration(40,200,30,50,1,2));
	C.push_back(Configuration(40,200,30,50,2,4));
	C.push_back(Configuration(40,200,30,50,4,10));
	//C.push_back(Configuration(40,200,30,50,10,20));
	//C.push_back(Configuration(40,200,30,50,20,50));
	C.push_back(Configuration(40,200,50,90,1,2));
	C.push_back(Configuration(40,200,50,90,2,4));
	C.push_back(Configuration(40,200,50,90,4,10));
	//C.push_back(Configuration(40,200,50,90,10,20));
	//C.push_back(Configuration(40,200,50,90,20,50));
/*
	C.push_back(Configuration(20,2000,0,10,10,20));
	C.push_back(Configuration(20,2000,0,10,20,50));
	C.push_back(Configuration(20,2000,0,10,50,100));
	C.push_back(Configuration(20,2000,0,90,10,20));
	C.push_back(Configuration(20,2000,0,90,20,50));
	C.push_back(Configuration(20,2000,0,90,50,100));
*/
	//vector<TDirectory *>     Folder;

	vector<TH1D> VecHNSig;
	vector<TH1D> VecHNBkg;
	vector<TH1D> VecHNPP0;
	vector<TH1D> VecHNSigData;
	vector<TH1D> VecHNBkgData;
	vector<TH1D> VecHNPP0Data;

	vector<TH1D> VecHNSig1;
	vector<TH1D> VecHNBkg1;
	vector<TH1D> VecHNPP01;
	vector<TH1D> VecHNSigData1;
	vector<TH1D> VecHNBkgData1;
	vector<TH1D> VecHNPP0Data1;

	TH1D HNSig("HNSig","Normalization", 1, 0, 1);
	TH1D HNBkg("HNBkg","Normalization", 1, 0, 1);
	TH1D HNPP0("HNPP0","Normalization", 1, 0, 1);
	TH1D HNSigData("HNSigData","Normalization", 1, 0, 1);
	TH1D HNBkgData("HNBkgData","Normalization", 1, 0, 1);
	TH1D HNPP0Data("HNPP0Data","Normalization", 1, 0, 1);

	TH1D HNSig1("HNSig1","Normalization", 1, 0, 1);
	TH1D HNBkg1("HNBkg1","Normalization", 1, 0, 1);
	TH1D HNPP01("HNPP01","Normalization", 1, 0, 1);
	TH1D HNSigData1("HNSigData1","Normalization", 1, 0, 1);
	TH1D HNBkgData1("HNBkgData1","Normalization", 1, 0, 1);
	TH1D HNPP0Data1("HNPP0Data1","Normalization", 1, 0, 1);

	//TFile OutputFile(OutputFileName.c_str(), "RECREATE");

	cout<<"Create VecHNs"<<endl;

	for(int iC = 0; iC < C.size(); iC++){

		//string FolderName =
		//	Form("Count_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",
		//		C[iC].ZPTMin, C[iC].ZPTMax,
		//		C[iC].CentMin, C[iC].CentMax,
		//		C[iC].TrackPTMin, C[iC].TrackPTMax);
		//replace(FolderName.begin(), FolderName.end(), '.', 'p');
//
		//Folder.push_back(OutputFile.mkdir(FolderName.c_str()));

		VecHNSig.push_back(HNSig); HNSig.Reset();
		VecHNBkg.push_back(HNBkg); HNBkg.Reset();
		VecHNPP0.push_back(HNPP0); HNPP0.Reset();
		VecHNSigData.push_back(HNSigData); HNSigData.Reset();
		VecHNBkgData.push_back(HNBkgData); HNBkgData.Reset();
		VecHNPP0Data.push_back(HNPP0Data); HNPP0Data.Reset();

		VecHNSig1.push_back(HNSig1); HNSig1.Reset();
		VecHNBkg1.push_back(HNBkg1); HNBkg1.Reset();
		VecHNPP01.push_back(HNPP01); HNPP01.Reset();
		VecHNSigData1.push_back(HNSigData1); HNSigData1.Reset();
		VecHNBkgData1.push_back(HNBkgData1); HNBkgData1.Reset();
		VecHNPP0Data1.push_back(HNPP0Data1); HNPP0Data1.Reset();
	}

	double zP, zPz, zE, zY, trkP, trkPz, trkE, trkY, TrackEta;

	float hiHF, SignalVZ;
	int NPU;

   vector<double> *ZMass       = nullptr;
	vector<double> *ZPT         = nullptr;
   vector<bool> *TrackMuTagged = nullptr;
   vector<double> *TrackPT     = nullptr;

   float NCollWeight;
   float ZWeight, VZWeight;
   vector<double> *trackWeight = nullptr;
   vector<double> *trackResidualWeight = nullptr;

   float ExtraZWeight[12];
   
	TreeSig->SetBranchAddress("zPt",                 &ZPT);
	TreeSig->SetBranchAddress("zMass",               &ZMass);
	TreeSig->SetBranchAddress("hiHF",                &hiHF);
   TreeSig->SetBranchAddress("SignalVZ",            &SignalVZ);
	TreeSig->SetBranchAddress("trackPt",             &TrackPT);

	TreeSig->SetBranchAddress("NCollWeight",         &NCollWeight);
   TreeSig->SetBranchAddress("ZWeight",             &ZWeight);
   TreeSig->SetBranchAddress("VZWeight",            &VZWeight);
   TreeSig->SetBranchAddress("ExtraZWeight",        &ExtraZWeight);
   TreeSig->SetBranchAddress("trackWeight",         &trackWeight);
   TreeSig->SetBranchAddress("trackResidualWeight", &trackResidualWeight);

   vector<double> *ZEta       = nullptr;
   vector<double> *trackDeta  = nullptr;

   TreeSig->SetBranchAddress("zEta",      &ZEta);
   TreeSig->SetBranchAddress("trackDeta", &trackDeta);

   if(TreeSig->GetBranch("trackMuTagged")) TreeSig->SetBranchAddress("trackMuTagged", &TrackMuTagged);

	int EntryCount = TreeSig->GetEntries() * Fraction;
	ProgressBar Bar(cout, EntryCount);
	Bar.SetStyle(-1);

	cout<<"Start Sig!"<<endl;

	for(int iE = 0; iE < EntryCount; iE++){

		if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0){
        	Bar.Update(iE);
        	Bar.Print();
		}

		TreeSig->GetEntry(iE);

		for(int iC = 0; iC < (int)C.size(); iC++){

			bool ZMassRange = false;
         if(ZMass != nullptr && ZMass->size() > 0 && ZMass->at(0) > 60)
          ZMassRange = true;

         bool ZPTRange = false;
         if(ZPT != nullptr && ZPT->size() > 0 && ZPT->at(0) > C[iC].ZPTMin && ZPT->at(0) <= C[iC].ZPTMax)
            ZPTRange = true;

         bool CentRange = false;
			if(hiHF <= cent[200-(int) (2*C[iC].CentMin)] && hiHF > cent[200-(int) (2*C[iC].CentMax)])
         	CentRange = true;

         bool VZRange = false;
         if(SignalVZ > VZMin && SignalVZ < VZMax)
         	VZRange = true;

         if(!(ZMassRange && ZPTRange && CentRange && VZRange)) 
         	continue;

         bool SomethingPassed = false;

			int NTrack = 0;
         if(TrackPT != nullptr)
         	NTrack = TrackPT->size();

         for(int iT = 0; iT < NTrack; iT++)
         {
         	bool TrackPTRange = false;
         	if(TrackPT->at(iT) > C[iC].TrackPTMin && TrackPT->at(iT) < C[iC].TrackPTMax)
         		TrackPTRange = true;

         	bool TrackNotCloseToMuon = true;
         	if(TrackMuTagged != nullptr && TrackMuTagged->at(iT) == true)
            	TrackNotCloseToMuon = false;

            zP = ZPT->at(0)*cosh(ZEta->at(0));
   			zPz = ZPT->at(0)*sinh(ZEta->at(0));
   			zE = sqrt(zP*zP+ZMass->at(0) * ZMass->at(0));
   			zY = 0.5*log((zE+zPz)/(zE-zPz));
			
				TrackEta = trackDeta->at(iT) + ZEta->at(0);

   			trkP = TrackPT->at(iT) *cosh(TrackEta);
   			trkPz = TrackPT->at(iT) *sinh(TrackEta);
			
   			trkE = sqrt(trkP*trkP+piMass*piMass);
   			trkY = 0.5*log((trkE+trkPz)/(trkE-trkPz));

   			bool IsHistRange = true;

   			if(IsDeltaEta && fabs(ZEta->at(0)) > 3.5)
   				IsHistRange = false;

   			if(IsDeltaY && fabs(trkY - zY) > 3.5)
   				IsHistRange = false;

            bool PassEvent = ZMassRange && ZPTRange && CentRange && VZRange && IsHistRange;
            bool PassEverything = PassEvent && TrackPTRange && TrackNotCloseToMuon;

         	if(PassEvent)
               SomethingPassed = true;

            if(!PassEverything) 
            	continue;

         	if(ZWtID==-1) 
         		VecHNSig[iC].Fill(0.,NCollWeight*ZWeight*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));
            else
         		VecHNSig[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));

			}

			if(!SomethingPassed)
				continue;

			if(ZWtID==-1) 
         	VecHNSig1[iC].Fill(0.,NCollWeight*ZWeight*VZWeight);
         else
         	VecHNSig1[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight);
		}
	}

	TreeBkg->SetBranchAddress("zPt",                 &ZPT);
	TreeBkg->SetBranchAddress("zMass",               &ZMass);
	TreeBkg->SetBranchAddress("hiHF",                &hiHF);
   TreeBkg->SetBranchAddress("SignalVZ",            &SignalVZ);
	TreeBkg->SetBranchAddress("trackPt",             &TrackPT);

	TreeBkg->SetBranchAddress("NCollWeight",         &NCollWeight);
   TreeBkg->SetBranchAddress("ZWeight",             &ZWeight);
   TreeBkg->SetBranchAddress("VZWeight",            &VZWeight);
   TreeBkg->SetBranchAddress("ExtraZWeight",        &ExtraZWeight);
   TreeBkg->SetBranchAddress("trackWeight",         &trackWeight);
   TreeBkg->SetBranchAddress("trackResidualWeight", &trackResidualWeight);

   TreeBkg->SetBranchAddress("zEta",      &ZEta);
   TreeBkg->SetBranchAddress("trackDeta", &trackDeta);

   if(TreeBkg->GetBranch("trackMuTagged")) TreeBkg->SetBranchAddress("trackMuTagged", &TrackMuTagged);

	EntryCount = TreeBkg->GetEntries() * Fraction;
	ProgressBar Bar1(cout, EntryCount);
	Bar1.SetStyle(-1);

	cout<<"Start Bkg!"<<endl;

	for(int iE = 0; iE < EntryCount; iE++){

		if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0){
        	Bar1.Update(iE);
        	Bar1.Print();
		}

		TreeBkg->GetEntry(iE);

		for(int iC = 0; iC < (int)C.size(); iC++){

			bool ZMassRange = false;
         if(ZMass != nullptr && ZMass->size() > 0 && ZMass->at(0) > 60)
            ZMassRange = true;

         bool ZPTRange = false;
         if(ZPT != nullptr && ZPT->size() > 0 && ZPT->at(0) > C[iC].ZPTMin && ZPT->at(0) <= C[iC].ZPTMax)
            ZPTRange = true;

         bool CentRange = false;
			if(hiHF <= cent[200-(int) (2*C[iC].CentMin)] && hiHF > cent[200-(int) (2*C[iC].CentMax)])
         	CentRange = true;

         bool VZRange = false;
         if(SignalVZ > VZMin && SignalVZ < VZMax)
         	VZRange = true;

         if(!(ZMassRange && ZPTRange && CentRange && VZRange)) 
         	continue;

         bool SomethingPassed = false;

			int NTrack = 0;
         if(TrackPT != nullptr)
         	NTrack = TrackPT->size();

         for(int iT = 0; iT < NTrack; iT++)
         {
         	bool TrackPTRange = false;
         	if(TrackPT->at(iT) > C[iC].TrackPTMin && TrackPT->at(iT) < C[iC].TrackPTMax)
         		TrackPTRange = true;

         	bool TrackNotCloseToMuon = true;
         	if(TrackMuTagged != nullptr && TrackMuTagged->at(iT) == true)
            	TrackNotCloseToMuon = false;

            zP = ZPT->at(0)*cosh(ZEta->at(0));
   			zPz = ZPT->at(0)*sinh(ZEta->at(0));
   			zE = sqrt(zP*zP+ZMass->at(0) * ZMass->at(0));
   			zY = 0.5*log((zE+zPz)/(zE-zPz));
			
				TrackEta = trackDeta->at(iT) + ZEta->at(0);

   			trkP = TrackPT->at(iT) *cosh(TrackEta);
   			trkPz = TrackPT->at(iT) *sinh(TrackEta);
			
   			trkE = sqrt(trkP*trkP+piMass*piMass);
   			trkY = 0.5*log((trkE+trkPz)/(trkE-trkPz));

   			bool IsHistRange = true;

   			if(IsDeltaEta && fabs(ZEta->at(0)) > 3.5)
   				IsHistRange = false;

   			if(IsDeltaY && fabs(trkY - zY) > 3.5)
   				IsHistRange = false;

            bool PassEvent = ZMassRange && ZPTRange && CentRange && VZRange && IsHistRange;
            bool PassEverything = PassEvent && TrackPTRange && TrackNotCloseToMuon;

         	if(PassEvent)
               SomethingPassed = true;

            if(!PassEverything) 
            	continue;

         	if(ZWtID==-1) 
         		VecHNBkg[iC].Fill(0.,NCollWeight*ZWeight*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));
            else
         		VecHNBkg[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));

			}

			if(!SomethingPassed)
				continue;

			if(ZWtID==-1) 
         	VecHNBkg1[iC].Fill(0.,NCollWeight*ZWeight*VZWeight);
         else
         	VecHNBkg1[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight);

		}
	}

	TreePP0->SetBranchAddress("zPt",                 &ZPT);
	TreePP0->SetBranchAddress("zMass",               &ZMass);
	TreePP0->SetBranchAddress("hiHF",                &hiHF);
   TreePP0->SetBranchAddress("NPU",                 &NPU);
   TreePP0->SetBranchAddress("SignalVZ",            &SignalVZ);
	TreePP0->SetBranchAddress("trackPt",             &TrackPT);

	TreePP0->SetBranchAddress("NCollWeight",         &NCollWeight);
   TreePP0->SetBranchAddress("ZWeight",             &ZWeight);
   TreePP0->SetBranchAddress("VZWeight",            &VZWeight);
   TreePP0->SetBranchAddress("ExtraZWeight",        &ExtraZWeight);
   TreePP0->SetBranchAddress("trackWeight",         &trackWeight);
   TreePP0->SetBranchAddress("trackResidualWeight", &trackResidualWeight);

   TreePP0->SetBranchAddress("zEta",      &ZEta);
   TreePP0->SetBranchAddress("trackDeta", &trackDeta);

   if(TreePP0->GetBranch("trackMuTagged")) TreePP0->SetBranchAddress("trackMuTagged", &TrackMuTagged);

	EntryCount = TreePP0->GetEntries() * Fraction;
	ProgressBar Bar2(cout, EntryCount);
	Bar2.SetStyle(-1);

	cout<<"Start pp!"<<endl;

	for(int iE = 0; iE < EntryCount; iE++){

		if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0){
        	Bar2.Update(iE);
        	Bar2.Print();
		}

		TreePP0->GetEntry(iE);

		for(int iC = 0; iC < (int)C.size(); iC++){

			bool ZMassRange = false;
         if(ZMass != nullptr && ZMass->size() > 0 && ZMass->at(0) > 60)
          ZMassRange = true;

         bool ZPTRange = false;
         if(ZPT != nullptr && ZPT->size() > 0 && ZPT->at(0) > C[iC].ZPTMin && ZPT->at(0) <= C[iC].ZPTMax)
            ZPTRange = true;

         bool VZRange = false;
         if(SignalVZ > VZMin && SignalVZ < VZMax)
         	VZRange = true;

         bool ppNPUcut = false;
         if(ppNPU==0 && NPU == 0 || ppNPU!=0)
         	ppNPUcut = true;

         if(!(ZMassRange && ZPTRange && VZRange && ppNPUcut)) 
         	continue;

         bool SomethingPassed = false;

			int NTrack = 0;
         if(TrackPT != nullptr)
         	NTrack = TrackPT->size();

         for(int iT = 0; iT < NTrack; iT++)
         {
         	bool TrackPTRange = false;
         	if(TrackPT->at(iT) > C[iC].TrackPTMin && TrackPT->at(iT) < C[iC].TrackPTMax)
         		TrackPTRange = true;

         	bool TrackNotCloseToMuon = true;
         	if(TrackMuTagged != nullptr && TrackMuTagged->at(iT) == true)
            	TrackNotCloseToMuon = false;

            zP = ZPT->at(0)*cosh(ZEta->at(0));
   			zPz = ZPT->at(0)*sinh(ZEta->at(0));
   			zE = sqrt(zP*zP+ZMass->at(0) * ZMass->at(0));
   			zY = 0.5*log((zE+zPz)/(zE-zPz));
			
				TrackEta = trackDeta->at(iT) + ZEta->at(0);

   			trkP = TrackPT->at(iT) *cosh(TrackEta);
   			trkPz = TrackPT->at(iT) *sinh(TrackEta);
			
   			trkE = sqrt(trkP*trkP+piMass*piMass);
   			trkY = 0.5*log((trkE+trkPz)/(trkE-trkPz));

   			bool IsHistRange = true;

   			if(IsDeltaEta && fabs(ZEta->at(0)) > 3.5)
   				IsHistRange = false;

   			if(IsDeltaY && fabs(trkY - zY) > 3.5)
   				IsHistRange = false;

            bool PassEvent = ZMassRange && ZPTRange && VZRange && ppNPUcut && IsHistRange;
            bool PassEverything = PassEvent && TrackPTRange && TrackNotCloseToMuon;

         	if(PassEvent)
               SomethingPassed = true;

            if(!PassEverything) 
            	continue;

         	if(ZWtID==-1) 
         		VecHNPP0[iC].Fill(0.,NCollWeight*ZWeight*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));
            else
         		VecHNPP0[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));

			}

			if(!SomethingPassed)
				continue;

			if(ZWtID==-1) 
         	VecHNPP01[iC].Fill(0.,NCollWeight*ZWeight*VZWeight);
         else
         	VecHNPP01[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight);

		}
	}

	TreeSigData->SetBranchAddress("zPt",                 &ZPT);
	TreeSigData->SetBranchAddress("zMass",               &ZMass);
	TreeSigData->SetBranchAddress("hiHF",                &hiHF);
   TreeSigData->SetBranchAddress("SignalVZ",            &SignalVZ);
	TreeSigData->SetBranchAddress("trackPt",             &TrackPT);

	TreeSigData->SetBranchAddress("NCollWeight",         &NCollWeight);
   TreeSigData->SetBranchAddress("ZWeight",             &ZWeight);
   TreeSigData->SetBranchAddress("VZWeight",            &VZWeight);
   TreeSigData->SetBranchAddress("ExtraZWeight",        &ExtraZWeight);
   TreeSigData->SetBranchAddress("trackWeight",         &trackWeight);
   TreeSigData->SetBranchAddress("trackResidualWeight", &trackResidualWeight);

   TreeSigData->SetBranchAddress("zEta",      &ZEta);
   TreeSigData->SetBranchAddress("trackDeta", &trackDeta);

   if(TreeSigData->GetBranch("trackMuTagged")) TreeSigData->SetBranchAddress("trackMuTagged", &TrackMuTagged);

	EntryCount = TreeSigData->GetEntries() * Fraction;
	ProgressBar Bar3(cout, EntryCount);
	Bar3.SetStyle(-1);

	cout<<"Start SigData!"<<endl;

	for(int iE = 0; iE < EntryCount; iE++){

		if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0){
        	Bar3.Update(iE);
        	Bar3.Print();
		}

		TreeSigData->GetEntry(iE);

		for(int iC = 0; iC < (int)C.size(); iC++){

			bool ZMassRange = false;
         if(ZMass != nullptr && ZMass->size() > 0 && ZMass->at(0) > 60)
          ZMassRange = true;

         bool ZPTRange = false;
         if(ZPT != nullptr && ZPT->size() > 0 && ZPT->at(0) > C[iC].ZPTMin && ZPT->at(0) <= C[iC].ZPTMax)
            ZPTRange = true;

         bool CentRange = false;
			if(hiHF <= cent[200-(int) (2*C[iC].CentMin)] && hiHF > cent[200-(int) (2*C[iC].CentMax)])
         	CentRange = true;

         bool VZRange = false;
         if(SignalVZ > VZMin && SignalVZ < VZMax)
         	VZRange = true;

         if(!(ZMassRange && ZPTRange && CentRange && VZRange)) 
         	continue;

         bool SomethingPassed = false;
         
			int NTrack = 0;
         if(TrackPT != nullptr)
            NTrack = TrackPT->size();

         for(int iT = 0; iT < NTrack; iT++)
         {
         	bool TrackPTRange = false;
         	if(TrackPT->at(iT) > C[iC].TrackPTMin && TrackPT->at(iT) < C[iC].TrackPTMax)
         		TrackPTRange = true;

         	bool TrackNotCloseToMuon = true;
         	if(TrackMuTagged != nullptr && TrackMuTagged->at(iT) == true)
            	TrackNotCloseToMuon = false;

            zP = ZPT->at(0)*cosh(ZEta->at(0));
   			zPz = ZPT->at(0)*sinh(ZEta->at(0));
   			zE = sqrt(zP*zP+ZMass->at(0) * ZMass->at(0));
   			zY = 0.5*log((zE+zPz)/(zE-zPz));
			
				TrackEta = trackDeta->at(iT) + ZEta->at(0);

   			trkP = TrackPT->at(iT) *cosh(TrackEta);
   			trkPz = TrackPT->at(iT) *sinh(TrackEta);
			
   			trkE = sqrt(trkP*trkP+piMass*piMass);
   			trkY = 0.5*log((trkE+trkPz)/(trkE-trkPz));

   			bool IsHistRange = true;

   			if(IsDeltaEta && fabs(ZEta->at(0)) > 3.5)
   				IsHistRange = false;

   			if(IsDeltaY && fabs(trkY - zY) > 3.5)
   				IsHistRange = false;

            bool PassEvent = ZMassRange && ZPTRange && CentRange && VZRange && IsHistRange;
            bool PassEverything = PassEvent && TrackPTRange && TrackNotCloseToMuon;

         	if(PassEvent)
               SomethingPassed = true;

            if(!PassEverything) 
            	continue;

           	if(ZWtID==-1) 
           		VecHNSigData[iC].Fill(0.,NCollWeight*ZWeight*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));
           	else
           		VecHNSigData[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));

			}

			if(!SomethingPassed)
				continue;

			if(ZWtID==-1) 
         	VecHNSigData1[iC].Fill(0.,NCollWeight*ZWeight*VZWeight);
         else
         	VecHNSigData1[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight);

		}
	}

	TreeBkgData->SetBranchAddress("zPt",                 &ZPT);
	TreeBkgData->SetBranchAddress("zMass",               &ZMass);
	TreeBkgData->SetBranchAddress("hiHF",                &hiHF);
   TreeBkgData->SetBranchAddress("SignalVZ",            &SignalVZ);
	TreeBkgData->SetBranchAddress("trackPt",             &TrackPT);

	TreeBkgData->SetBranchAddress("NCollWeight",         &NCollWeight);
   TreeBkgData->SetBranchAddress("ZWeight",             &ZWeight);
   TreeBkgData->SetBranchAddress("VZWeight",            &VZWeight);
   TreeBkgData->SetBranchAddress("ExtraZWeight",        &ExtraZWeight);
   TreeBkgData->SetBranchAddress("trackWeight",         &trackWeight);
   TreeBkgData->SetBranchAddress("trackResidualWeight", &trackResidualWeight);

   TreeBkgData->SetBranchAddress("zEta",      &ZEta);
   TreeBkgData->SetBranchAddress("trackDeta", &trackDeta);

   if(TreeBkgData->GetBranch("trackMuTagged")) TreeBkgData->SetBranchAddress("trackMuTagged", &TrackMuTagged);

	EntryCount = TreeBkgData->GetEntries() * Fraction;
	ProgressBar Bar4(cout, EntryCount);
	Bar4.SetStyle(-1);

	cout<<"Start BkgData!"<<endl;

	for(int iE = 0; iE < EntryCount; iE++){

		if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0){
        	Bar4.Update(iE);
        	Bar4.Print();
		}

		TreeBkgData->GetEntry(iE);


		for(int iC = 0; iC < (int)C.size(); iC++){
			bool ZMassRange = false;
         if(ZMass != nullptr && ZMass->size() > 0 && ZMass->at(0) > 60)
          ZMassRange = true;

         bool ZPTRange = false;
         if(ZPT != nullptr && ZPT->size() > 0 && ZPT->at(0) > C[iC].ZPTMin && ZPT->at(0) <= C[iC].ZPTMax)
            ZPTRange = true;

         bool CentRange = false;
			if(hiHF <= cent[200-(int) (2*C[iC].CentMin)] && hiHF > cent[200-(int) (2*C[iC].CentMax)])
         	CentRange = true;

         bool VZRange = false;
         if(SignalVZ > VZMin && SignalVZ < VZMax)
         	VZRange = true;

         if(!(ZMassRange && ZPTRange && CentRange && VZRange)) 
         	continue;

         bool SomethingPassed = false;
         
			int NTrack = 0;
         if(TrackPT != nullptr)
         	NTrack = TrackPT->size();

         for(int iT = 0; iT < NTrack; iT++)
         {
         	bool TrackPTRange = false;
         	if(TrackPT->at(iT) > C[iC].TrackPTMin && TrackPT->at(iT) < C[iC].TrackPTMax)
         		TrackPTRange = true;

         	bool TrackNotCloseToMuon = true;
         	if(TrackMuTagged != nullptr && TrackMuTagged->at(iT) == true)
            	TrackNotCloseToMuon = false;

            zP = ZPT->at(0)*cosh(ZEta->at(0));
   			zPz = ZPT->at(0)*sinh(ZEta->at(0));
   			zE = sqrt(zP*zP+ZMass->at(0) * ZMass->at(0));
   			zY = 0.5*log((zE+zPz)/(zE-zPz));
			
				TrackEta = trackDeta->at(iT) + ZEta->at(0);

   			trkP = TrackPT->at(iT) *cosh(TrackEta);
   			trkPz = TrackPT->at(iT) *sinh(TrackEta);
			
   			trkE = sqrt(trkP*trkP+piMass*piMass);
   			trkY = 0.5*log((trkE+trkPz)/(trkE-trkPz));

   			bool IsHistRange = true;

   			if(IsDeltaEta && fabs(ZEta->at(0)) > 3.5)
   				IsHistRange = false;

   			if(IsDeltaY && fabs(trkY - zY) > 3.5)
   				IsHistRange = false;

            bool PassEvent = ZMassRange && ZPTRange && CentRange && VZRange && IsHistRange;
            bool PassEverything = PassEvent && TrackPTRange && TrackNotCloseToMuon;

         	if(PassEvent)
               SomethingPassed = true;

            if(!PassEverything) 
            	continue;

         	if(ZWtID==-1) 
         		VecHNBkgData[iC].Fill(0.,NCollWeight*ZWeight*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));
            else
         		VecHNBkgData[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));

			}

			if(!SomethingPassed)
				continue;

			if(ZWtID==-1) 
         	VecHNBkgData1[iC].Fill(0.,NCollWeight*ZWeight*VZWeight);
         else
         	VecHNBkgData1[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight);

		}
	}

	TreePP0Data->SetBranchAddress("zPt",                 &ZPT);
	TreePP0Data->SetBranchAddress("zMass",               &ZMass);
	TreePP0Data->SetBranchAddress("hiHF",                &hiHF);
   TreePP0Data->SetBranchAddress("SignalVZ",            &SignalVZ);
	TreePP0Data->SetBranchAddress("trackPt",             &TrackPT);

	TreePP0Data->SetBranchAddress("NCollWeight",         &NCollWeight);
   TreePP0Data->SetBranchAddress("ZWeight",             &ZWeight);
   TreePP0Data->SetBranchAddress("VZWeight",            &VZWeight);
   TreePP0Data->SetBranchAddress("ExtraZWeight",        &ExtraZWeight);
   TreePP0Data->SetBranchAddress("trackWeight",         &trackWeight);
   TreePP0Data->SetBranchAddress("trackResidualWeight", &trackResidualWeight);

   TreePP0Data->SetBranchAddress("zEta",      &ZEta);
   TreePP0Data->SetBranchAddress("trackDeta", &trackDeta);

   if(TreePP0Data->GetBranch("trackMuTagged")) TreePP0Data->SetBranchAddress("trackMuTagged", &TrackMuTagged);

	EntryCount = TreePP0Data->GetEntries() * Fraction;
	ProgressBar Bar5(cout, EntryCount);
	Bar5.SetStyle(-1);

	cout<<"Start ppData!"<<endl;

	for(int iE = 0; iE < EntryCount; iE++){

		if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0){
        	Bar5.Update(iE);
        	Bar5.Print();
		}

		TreePP0Data->GetEntry(iE);


		for(int iC = 0; iC < (int)C.size(); iC++){

			bool ZMassRange = false;

         if(ZMass != nullptr && ZMass->size() > 0 && ZMass->at(0) > 60)
          ZMassRange = true;

         bool ZPTRange = false;
         if(ZPT != nullptr && ZPT->size() > 0 && ZPT->at(0) > C[iC].ZPTMin && ZPT->at(0) <= C[iC].ZPTMax)
            ZPTRange = true;

         bool VZRange = false;
         if(SignalVZ > VZMin && SignalVZ < VZMax)
         	VZRange = true;

         if(!(ZMassRange && ZPTRange && VZRange)) 
         	continue;

         bool SomethingPassed = false;

			int NTrack = 0;
         if(TrackPT != nullptr)
         	NTrack = TrackPT->size();

         for(int iT = 0; iT < NTrack; iT++)
         {
         	bool TrackPTRange = false;
         	if(TrackPT->at(iT) > C[iC].TrackPTMin && TrackPT->at(iT) < C[iC].TrackPTMax)
         		TrackPTRange = true;

         	bool TrackNotCloseToMuon = true;
         	if(TrackMuTagged != nullptr && TrackMuTagged->at(iT) == true)
            		TrackNotCloseToMuon = false;

            zP = ZPT->at(0)*cosh(ZEta->at(0));
   			zPz = ZPT->at(0)*sinh(ZEta->at(0));
   			zE = sqrt(zP*zP+ZMass->at(0) * ZMass->at(0));
   			zY = 0.5*log((zE+zPz)/(zE-zPz));
			
				TrackEta = trackDeta->at(iT) + ZEta->at(0);

   			trkP = TrackPT->at(iT) *cosh(TrackEta);
   			trkPz = TrackPT->at(iT) *sinh(TrackEta);
			
   			trkE = sqrt(trkP*trkP+piMass*piMass);
   			trkY = 0.5*log((trkE+trkPz)/(trkE-trkPz));

   			bool IsHistRange = true;

   			if(IsDeltaEta && fabs(ZEta->at(0)) > 3.5)
   				IsHistRange = false;

   			if(IsDeltaY && fabs(trkY - zY) > 3.5)
   				IsHistRange = false;

         	bool PassEvent = ZMassRange && ZPTRange && VZRange && IsHistRange;
            bool PassEverything = PassEvent && TrackPTRange && TrackNotCloseToMuon;

         	if(PassEvent)
               SomethingPassed = true;

            if(!PassEverything) 
            	continue;

         	if(ZWtID==-1) 
         		VecHNPP0Data[iC].Fill(0.,NCollWeight*ZWeight*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));
            else
         		VecHNPP0Data[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight*(trackWeight->at(iT))*(trackResidualWeight->at(iT)));

			}

			if(!SomethingPassed)
				continue;

			if(ZWtID==-1) 
         	VecHNPP0Data1[iC].Fill(0.,NCollWeight*ZWeight*VZWeight);
         else
         	VecHNPP0Data1[iC].Fill(0.,NCollWeight*ZWeight*ExtraZWeight[ZWtID]*VZWeight);

		}
	}

	string OutputDHName = OutputFileName;
	OutputDHName.resize(OutputDHName.size()-4);
	DataHelper DHFile(OutputDHName + ".dh");

	for(int iC = 0; iC < (int)C.size(); iC++){

		if(iC%tablesize==0){
			fout<<"\\begin{table}[h!]"<<endl;
			fout<<"\\centering"<<endl;
			fout<<"\\begin{tabular}{|l|c|c|c|c|}"<<endl;
		}
    	fout<<"\\multicolumn{5}{l}{ HFShift = "<<HFShift<<", HFTolerance = "<<HFTolerance<<"}\\\\"<<std::endl;
    	fout<<"\\multicolumn{5}{l}{ $"<<C[iC].ZPTMin<<" < p_{T}^{Z} < "<<C[iC].ZPTMax<<", "<<C[iC].CentMin<<" <$ Centrality $< "<<C[iC].CentMax<<", "<<C[iC].TrackPTMin<<" < p_{T}^{trk} < "<<C[iC].TrackPTMax<<"$}\\\\"<<std::endl;

		double t1N = VecHNSig[iC].GetBinContent(1);
		double t2N = VecHNBkg[iC].GetBinContent(1);
		double t4N = VecHNPP0[iC].GetBinContent(1);
		double t6N = VecHNSigData[iC].GetBinContent(1);
		double t7N = VecHNBkgData[iC].GetBinContent(1);
		double t8N = VecHNPP0Data[iC].GetBinContent(1);
	
		double t1E = VecHNSig[iC].GetBinError(1);
		double t2E = VecHNBkg[iC].GetBinError(1);
		double t4E = VecHNPP0[iC].GetBinError(1);
		double t6E = VecHNSigData[iC].GetBinError(1);
		double t7E = VecHNBkgData[iC].GetBinError(1);
		double t8E = VecHNPP0Data[iC].GetBinError(1);

		double z1N = VecHNSig1[iC].GetBinContent(1);
		double z2N = VecHNBkg1[iC].GetBinContent(1);
		double z4N = VecHNPP01[iC].GetBinContent(1);
		double z6N = VecHNSigData1[iC].GetBinContent(1);
		double z7N = VecHNBkgData1[iC].GetBinContent(1);
		double z8N = VecHNPP0Data1[iC].GetBinContent(1);
	
		int z1N0 = VecHNSig1[iC].GetEntries();
		int z2N0 = VecHNBkg1[iC].GetEntries();
		int z4N0 = VecHNPP01[iC].GetEntries();
		int z6N0 = VecHNSigData1[iC].GetEntries();
		int z7N0 = VecHNBkgData1[iC].GetEntries();
		int z8N0 = VecHNPP0Data1[iC].GetEntries();
	
		double z1E = VecHNSig1[iC].GetBinError(1);
		double z2E = VecHNBkg1[iC].GetBinError(1);
		double z4E = VecHNPP01[iC].GetBinError(1);
		double z6E = VecHNSigData1[iC].GetBinError(1);
		double z7E = VecHNBkgData1[iC].GetBinError(1);
		double z8E = VecHNPP0Data1[iC].GetBinError(1);

		double et1 = t1E/t1N, et2 = t2E/t2N, et4 = t4E/t4N, et6 = t6E/t6N, et7 = t7E/t7N, et8 = t8E/t8N;
		double ez1 = z1E/z1N, ez2 = z2E/z2N, ez4 = z4E/z4N, ez6 = z6E/z6N, ez7 = z7E/z7N, ez8 = z8E/z8N;
	/*
		//fout<<"======================================"<<std::endl;
		fout<<"\\hline\\hline"<<std::endl;
	
		fout<<left<<setw(20)<< "Sample"              <<setw(2)<<"&"<<left<<setw(15)<< "PbPb Sig MC" <<setw(2)<<"&"<<left<<setw(15)<< "PbPb Bkg MC" <<setw(2)<<"&"<<left<<setw(20)<< "PbPb Sig-Bkg MC" <<setw(2)<<"&"<<left<<setw(15)<< "pp MC" <<"\\\\"<<endl;
		fout<<left<<setw(20)<< "$N_Z$ (unweighted)"  <<setw(2)<<"&"<<left<<setw(15)<< z1N0          <<setw(2)<<"&"<<left<<setw(15)<< "-"           <<setw(2)<<"&"<<left<<setw(20)<< "-"         <<setw(2)<<"&"<<left<<setw(15)<< z4N0         <<"\\\\"<<endl;
		fout<<left<<setw(20)<< "$N_{evt}$ (weighted)"<<setw(2)<<"&"<<left<<setw(15)<< z1N           <<setw(2)<<"&"<<left<<setw(15)<< "-"           <<setw(2)<<"&"<<left<<setw(20)<< "-"           <<setw(2)<<"&"<<left<<setw(15)<< z4N          <<"\\\\"<<endl;
		fout<<left<<setw(20)<< "$N_{trk}/N_{evt}$"   <<setw(2)<<"&"<<left<<setw(15)<< t1N/z1N       <<setw(2)<<"&"<<left<<setw(15)<< t2N/z2N       <<setw(2)<<"&"<<left<<setw(20)<< t1N/z1N-t2N/z2N   <<setw(2)<<"&"<<left<<setw(15)<< t4N/z4N      <<"\\\\"<<endl;
		fout<<left<<setw(20)<< "Error"     	         <<setw(2)<<"&"<<left<<setw(15)<< t1E/z1N       <<setw(2)<<"&"<<left<<setw(15)<< t2E/z2N       <<setw(2)<<"&"<<left<<setw(20)<< sqrt((t1E/z1N)*(t1E/z1N)+(t2E/z2N)*(t2E/z2N)) <<setw(2)<<"&"<<left<<setw(15)<< t4E/z4N <<"\\\\"<<endl;
	
		//fout<<"--------------------------------------"<<std::endl;
		fout<<"\\hline"<<std::endl;
	
		fout<<left<<setw(20)<< "Sample"              <<setw(2)<<"&"<<left<<setw(15)<< "PbPb Sig Data"<<setw(2)<<"&"<<left<<setw(15)<< "PbPb Bkg Data"<<setw(2)<<"&"<<left<<setw(20)<< "PbPb Sig-Bkg Data"<<setw(2)<<"&"<<left<<setw(15)<< "pp Data" <<"\\\\"<<endl;
		fout<<left<<setw(20)<< "$N_Z$ (unweighted)"  <<setw(2)<<"&"<<left<<setw(15)<< z6N0           <<setw(2)<<"&"<<left<<setw(15)<< "-"           <<setw(2)<<"&"<<left<<setw(20)<< "-"          <<setw(2)<<"&"<<left<<setw(15)<< z8N0            <<"\\\\"<<endl;
		fout<<left<<setw(20)<< "$N_{evt}$ (weighted)"<<setw(2)<<"&"<<left<<setw(15)<< z6N            <<setw(2)<<"&"<<left<<setw(15)<< "-"            <<setw(2)<<"&"<<left<<setw(20)<< "-"            <<setw(2)<<"&"<<left<<setw(15)<< z8N             <<"\\\\"<<endl;
		fout<<left<<setw(20)<< "$N_{trk}/N_{evt}$"   <<setw(2)<<"&"<<left<<setw(15)<< t6N/z6N        <<setw(2)<<"&"<<left<<setw(15)<< t7N/z7N        <<setw(2)<<"&"<<left<<setw(20)<< t6N/z6N-t7N/z7N    <<setw(2)<<"&"<<left<<setw(15)<< t8N/z8N         <<"\\\\"<<endl;
		fout<<left<<setw(20)<< "Error"     	         <<setw(2)<<"&"<<left<<setw(15)<< t6E/z6N        <<setw(2)<<"&"<<left<<setw(15)<< t7E/z7N        <<setw(2)<<"&"<<left<<setw(20)<< sqrt((t6E/z6N)*(t6E/z6N)+(t7E/z7N)*(t7E/z7N)) <<setw(2)<<"&"<<left<<setw(15)<< t8E/z8N <<"\\\\"<<endl;
	*/

	//fout<<"======================================"<<std::endl;
		fout<<"\\hline\\hline"<<std::endl;
	
		fout<<left<<setw(20)<< "Sample"              <<setw(2)<<"&"<<left<<setw(20)<< "PbPb Sig-Bkg MC" 									 <<setw(2)<<"&"<<left<<setw(15)<< "pp MC" <<setw(2)<<"&"<<left<<setw(20)<< "PbPb Sig-Bkg Data"									 <<setw(2)<<"&"<<left<<setw(15)<< "pp Data" <<"\\\\"<<endl;
		fout<<"\\hline"<<std::endl;
		fout<<left<<setw(20)<< "$N_{trk}/N_{evt}$"   <<setw(2)<<"&"<<left<<setw(20)<< t1N/z1N-t2N/z2N   									 <<setw(2)<<"&"<<left<<setw(15)<< t4N/z4N <<setw(2)<<"&"<<left<<setw(20)<< t6N/z6N-t7N/z7N    									 <<setw(2)<<"&"<<left<<setw(15)<< t8N/z8N   <<"\\\\"<<endl;
		fout<<left<<setw(20)<< "Error"     	         <<setw(2)<<"&"<<left<<setw(20)<< sqrt((t1E/z1N)*(t1E/z1N)+(t2E/z2N)*(t2E/z2N)) <<setw(2)<<"&"<<left<<setw(15)<< t4E/z4N <<setw(2)<<"&"<<left<<setw(20)<< sqrt((t6E/z6N)*(t6E/z6N)+(t7E/z7N)*(t7E/z7N)) <<setw(2)<<"&"<<left<<setw(15)<< t8E/z8N   <<"\\\\"<<endl;

		//fout<<"======================================"<<std::endl;
		fout<<"\\hline\\hline"<<std::endl;
		if(iC%tablesize==tablesize-1||iC==(int)C.size()-1){
			fout<<"\\end{tabular}"<<std::endl;
			fout<<"\\end{table}"<<std::endl;
			fout<<"\\clearpage"<<std::endl;
		}

		string FolderName =
		Form("Count_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",
			C[iC].ZPTMin, C[iC].ZPTMax,
			C[iC].CentMin, C[iC].CentMax,
			C[iC].TrackPTMin, C[iC].TrackPTMax);
		replace(FolderName.begin(), FolderName.end(), '.', 'p');

		DHFile[FolderName]["PbPb MC Sig NZ"] = z1N0;
		DHFile[FolderName]["PbPb MC Bkg NZ"] = z2N0;
		DHFile[FolderName]["PbPb MC Sig-Bkg NZ"] = z1N0-z2N0;
		DHFile[FolderName]["pp MC NZ"] = z4N0;

		DHFile[FolderName]["PbPb MC Sig Nevt"] = z1N;
		DHFile[FolderName]["PbPb MC Bkg Nevt"] = z2N;
		DHFile[FolderName]["PbPb MC Sig-Bkg Nevt"] = z1N-z2N;
		DHFile[FolderName]["pp MC Nevt"] = z4N;

		DHFile[FolderName]["PbPb MC Sig Ntrk/Nevt"] = t1N/z1N;
		DHFile[FolderName]["PbPb MC Bkg Ntrk/Nevt"] = t2N/z2N;
		DHFile[FolderName]["PbPb MC Sig-Bkg Ntrk/Nevt"] = t1N/z1N-t2N/z2N;
		DHFile[FolderName]["pp MC Ntrk/Nevt"] = t4N/z4N;

		DHFile[FolderName]["PbPb MC Sig Ntrk/Nevt Error"] = t1E/z1N;
		DHFile[FolderName]["PbPb MC Bkg Ntrk/Nevt Error"] = t2E/z2N;
		DHFile[FolderName]["PbPb MC Sig-Bkg Ntrk/Nevt Error"] = sqrt((t1E/z1N)*(t1E/z1N)+(t2E/z2N)*(t2E/z2N));
		DHFile[FolderName]["pp MC Ntrk/Nevt Error"] = t4E/z4N;

		DHFile[FolderName]["PbPb Data Sig NZ"] = z6N0;
		DHFile[FolderName]["PbPb Data Bkg NZ"] = z7N0;
		DHFile[FolderName]["PbPb Data Sig-Bkg NZ"] = z6N0-z7N0;
		DHFile[FolderName]["pp Data NZ"] = z8N0;

		DHFile[FolderName]["PbPb Data Sig Nevt"] = z6N;
		DHFile[FolderName]["PbPb Data Bkg Nevt"] = z7N;
		DHFile[FolderName]["PbPb Data Sig-Bkg Nevt"] = z6N-z7N;
		DHFile[FolderName]["pp Data Nevt"] = z8N;

		DHFile[FolderName]["PbPb Data Sig Ntrk/Nevt"] = t6N/z6N;
		DHFile[FolderName]["PbPb Data Bkg Ntrk/Nevt"] = t7N/z7N;
		DHFile[FolderName]["PbPb Data Sig-Bkg Ntrk/Nevt"] = t6N/z6N-t7N/z7N;
		DHFile[FolderName]["pp Data Ntrk/Nevt"] = t8N/z8N;

		DHFile[FolderName]["PbPb Data Sig Ntrk/Nevt Error"] = t6E/z6N;
		DHFile[FolderName]["PbPb Data Bkg Ntrk/Nevt Error"] = t7E/z7N;
		DHFile[FolderName]["PbPb Data Sig-Bkg Ntrk/Nevt Error"] = sqrt((t6E/z6N)*(t6E/z6N)+(t7E/z7N)*(t7E/z7N));
		DHFile[FolderName]["pp Data Ntrk/Nevt Error"] = t8E/z8N;

		//string OutputFileNameBkup = OutputFileName;
		//OutputFileNameBkup.replace(OutputFileNameBkup.end()-4,OutputFileNameBkup.end(),"_bkup.txt");
		//gSystem->Exec(("cp " + OutputFileName + " " + OutputFileNameBkup).c_str());
	}
	DHFile.SaveToFile(); 
}