#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh

CMSSWDir=/afs/cern.ch/user/p/pchou/CMSSW_13_3_1/src

cd $CMSSWDir

cmsenv

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/

source /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/SetupAnalysis.sh

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/BasicDistribution/20230401_ZTrackAnalysisRefactor

mkdir -p log

if [ $1 -eq 0 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCSigBkg_v17b_tor50/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCSigBkg_v17b_tor50.root --Fraction 1
elif [ $1 -eq 1 ]
then
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCSigBkg_v17b_tor50/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPMCSigBkg_v17b_tor50.root --Fraction 1 --IgnoreCentrality true
#elif [ $1 -eq 4 ]
#then
#	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataSigBkg_v17b_checkz/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphDataSigBkg_v17b_checkz.root --Fraction 1
#elif [ $1 -eq 5 ]
#then
#	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPDataSigBkg_v17b_checkz/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphPPDataSigBkg_v17b_checkz.root --Fraction 1 --IgnoreCentrality true
#elif [ $1 -eq 6 ]
#then
#	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenSigBkg_v17b_checkz/ --Output /eos/cms/store/group/phys_heavyions/pchou/BasicPlots/GraphMCGenSigBkg_v17b_checkz.root --Fraction 1 --IgnoreCentrality true  --DoGenCorrelation true
else
	echo "Input number exceeded"
fi