#!/bin/sh
source /cvmfs/cms.cern.ch/cmsset_default.sh

CMSSWDir=/afs/cern.ch/user/p/pchou/CMSSW_13_3_1/src

cd $CMSSWDir

cmsenv

source /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/SetupAnalysis.sh

cd /afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/BasicDistribution/20230629_CountSkim

mkdir -p SkimCount/20240121
mkdir -p SkimCount/log/20240121


if [ $1 -eq 0 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_nominal_centN-v17d.tex -Fraction 1 -CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 1 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_nominal_centU-v17d.tex -Fraction 1 -CentUD 1 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 2 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_nominal_centD-v17d.tex -Fraction 1 -CentUD 2 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 3 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_UEUp25_centN-v17d.tex -Fraction 1 -CentUD 0 --HFShift 699 --HFShiftData 676.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEUp25_v17_PFmuon --BkgMCDir OutputMCBackgroundUEUp25_v17d_PFmuon
elif [ $1 -eq 4 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_UEUp25_centU-v17d.tex -Fraction 1 -CentUD 1 --HFShift 699 --HFShiftData 676.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEUp25_v17_PFmuon --BkgMCDir OutputMCBackgroundUEUp25_v17d_PFmuon
elif [ $1 -eq 5 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_UEUp25_centD-v17d.tex -Fraction 1 -CentUD 2 --HFShift 699 --HFShiftData 676.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEUp25_v17_PFmuon --BkgMCDir OutputMCBackgroundUEUp25_v17d_PFmuon
elif [ $1 -eq 6 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_UEDown25_centN-v17d.tex -Fraction 1 -CentUD 0 --HFShift 665 --HFShiftData 643.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEDown25_v17_PFmuon --BkgMCDir OutputMCBackgroundUEDown25_v17d_PFmuon
elif [ $1 -eq 7 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_UEDown25_centU-v17d.tex -Fraction 1 -CentUD 1 --HFShift 665 --HFShiftData 643.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEDown25_v17_PFmuon --BkgMCDir OutputMCBackgroundUEDown25_v17d_PFmuon
elif [ $1 -eq 8 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_UEDown25_centD-v17d.tex -Fraction 1 -CentUD 2 --HFShift 665 --HFShiftData 643.5 --Tolerance 187.5 --BkgDataDir OutputDataBackgroundUEDown25_v17_PFmuon --BkgMCDir OutputMCBackgroundUEDown25_v17d_PFmuon
elif [ $1 -eq 9 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt0-v17d.tex -Fraction 1 --ZWtID 0 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 10 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt1-v17d.tex -Fraction 1 --ZWtID 1 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 11 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt2-v17d.tex -Fraction 1 --ZWtID 2 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 12 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt3-v17d.tex -Fraction 1 --ZWtID 3 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 13 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt4-v17d.tex -Fraction 1 --ZWtID 4 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 14 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt5-v17d.tex -Fraction 1 --ZWtID 5 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 15 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt6-v17d.tex -Fraction 1 --ZWtID 6 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 16 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt7-v17d.tex -Fraction 1 --ZWtID 7 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 17 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt8-v17d.tex -Fraction 1 --ZWtID 8 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 18 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt9-v17d.tex -Fraction 1 --ZWtID 9 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 19 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt10-v17d.tex -Fraction 1 --ZWtID 10 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 20 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ZWt11-v17d.tex -Fraction 1 --ZWtID 11 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 21 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_ppNPU0-v17d.tex -Fraction 1 --ppNPU 0 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 22 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_VZ10-v17d.tex -Fraction 1 --VZMin -10 --VZMax 10 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 23 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_VZ20-v17d.tex -Fraction 1 --VZMin -20 --VZMax 20 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon
elif [ $1 -eq 24 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_loose-v17d.tex -Fraction 1 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon --SigMCDir OutputMCLoose_v17_PFmuon --SigDataDir OutputDataLoose_v17_PFmuon
elif [ $1 -eq 25 ]
then
	./ExecuteCount --Output SkimCount/20240121/SkimCount_tight-v17d.tex -Fraction 1 --CentUD 0 --HFShift 682 --HFShiftData 660 --Tolerance 187.5 --BkgDataDir OutputDataBackground_v17_PFmuon --BkgMCDir OutputMCBackground_v17d_PFmuon --SigMCDir OutputMCTight_v17_PFmuon --SigDataDir OutputDataTight_v17_PFmuon
else
	echo "Input number exceeded"
fi