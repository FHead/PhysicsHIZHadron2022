#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh

CMSSWDir=/afs/cern.ch/user/p/pchou/CMSSW_13_2_3/src

cd $CMSSWDir

cmsenv

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/

source /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/SetupAnalysis.sh

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/BasicDistribution/20230401_ZTrackAnalysisRefactor

mkdir -p log

if [ $1 -eq 0 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataSignal_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackground_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackground_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 2 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignal_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 3 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackground_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackground_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 4 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPMC_v17_PFmuon.root --IgnoreCentrality true --Fraction 1
elif [ $1 -eq 5 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPMC0Sub_v17_PFmuon.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 1
elif [ $1 -eq 6 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignalGen_v17_PFmuon.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 7 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignalGen0Sub_v17_PFmuon.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 8 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenbkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundGen_v17_PFmuon.root --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 9 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenbkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundGen0Sub_v17_PFmuon.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 10 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPMCGen_v17_PFmuon.root --IgnoreCentrality true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 11 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPMCGen0Sub_v17_PFmuon.root --IgnoreCentrality true  --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true
elif [ $1 -eq 12 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignal0Sub_v17_PFmuon.root --OnlyZeroSub true --Fraction 1
elif [ $1 -eq 13 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPData_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPData_v17_PFmuon.root --IgnoreCentrality true --Fraction 1
elif [ $1 -eq 14 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackgroundUEUp25_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackgroundUEUp25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 15 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEUp25_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEUp25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 16 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackgroundUEDown25_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataBackgroundUEDown25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 17 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackgroundUEDown25_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCBackgroundUEDown25_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 18 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataLoose_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataSignalLoose_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 19 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataTight_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataSignalTight_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 20 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCLoose_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignalLoose_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 21 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCTight_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSignalTight_v17_PFmuon.root --Fraction 1
elif [ $1 -eq 22 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataSigBkg_v17_PFmuon/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/OutputDataSigBkg_v17_PFmuon.root --Fraction 1
else
	echo "Input number exceeded"
fi