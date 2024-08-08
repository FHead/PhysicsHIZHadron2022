#!/bin/bash

mkdir -p Sys/v17/

# Muon matching
./Execute --Variation Root/DataMuMatch.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbMuMatch.root \
   --Scheme Maximum
./Execute --Variation Root/PPDataMuMatch.root --Reference Root/PPData.root \
   --Output Sys/v17/PPMuMatch.root \
   --Scheme Maximum

# Background subtraction
./Execute --Variation Root/DataMixUEUp25.root --Reference Root/DataMix.root \
   --Output Sys/v17/PbPbUEUp25.root \
   --Scheme RMS
./Execute --Variation Root/DataMixUEDown25.root --Reference Root/DataMix.root \
   --Output Sys/v17/PbPbUEDown25.root \
   --Scheme RMS
./Execute --Variation Sys/v17/PbPbUEUp25.root --Reference Sys/v17/PbPbUEDown25.root \
   --Output Sys/v17/PbPbUE25.root \
   --DirectMode true --Scheme DirectMaximum

# Non-closure

# pp PU
./Execute --Variation Root/PPData.root --Reference Root/PPData.root \
   --Output Sys/v17/PPPU.root \
   --Scheme Maximum --DoSubstitute true --SubstituteFrom PV_0_10 --SubstituteTo PV_0_1

# Lepton SF variation
./Execute --Variation Root/DataExtraZWeight0.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF0.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight1.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF1.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight2.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF2.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight3.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF3.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight4.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF4.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight5.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF5.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight6.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF6.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight7.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF7.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight8.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF8.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight9.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF9.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight10.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF10.root \
   --Scheme Maximum
./Execute --Variation Root/DataExtraZWeight11.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbSF11.root \
   --Scheme Maximum
./Execute --Variation Sys/v17/PbPbSF0.root --Reference Sys/v17/PbPbSF1.root \
   --Output Sys/v17/PbPbSFSys1.root \
   --DirectMode true --Scheme DirectMaximum
./Execute --Variation Sys/v17/PbPbSF2.root --Reference Sys/v17/PbPbSF3.root \
   --Output Sys/v17/PbPbSFSys2.root \
   --DirectMode true --Scheme DirectMaximum
./Execute --Variation Sys/v17/PbPbSF4.root --Reference Sys/v17/PbPbSF5.root \
   --Output Sys/v17/PbPbSFSys3.root \
   --DirectMode true --Scheme DirectMaximum
./Execute --Variation Sys/v17/PbPbSF6.root --Reference Sys/v17/PbPbSF7.root \
   --Output Sys/v17/PbPbSFStat1.root \
   --DirectMode true --Scheme DirectMaximum
./Execute --Variation Sys/v17/PbPbSF8.root --Reference Sys/v17/PbPbSF9.root \
   --Output Sys/v17/PbPbSFStat2.root \
   --DirectMode true --Scheme DirectMaximum
./Execute --Variation Sys/v17/PbPbSF10.root --Reference Sys/v17/PbPbSF11.root \
   --Output Sys/v17/PbPbSFStat3.root \
   --DirectMode true --Scheme DirectMaximum
./Execute --Variation Sys/v17/PbPbSFSys1.root --Reference Sys/v17/PbPbSFStat1.root \
   --Output Sys/v17/PbPbSFCombined1.root \
   --DirectMode true --Scheme DirectQuadraticSum
./Execute --Variation Sys/v17/PbPbSFSys2.root --Reference Sys/v17/PbPbSFStat2.root \
   --Output Sys/v17/PbPbSFCombined2.root \
   --DirectMode true --Scheme DirectQuadraticSum
./Execute --Variation Sys/v17/PbPbSFSys3.root --Reference Sys/v17/PbPbSFStat3.root \
   --Output Sys/v17/PbPbSFCombined3.root \
   --DirectMode true --Scheme DirectQuadraticSum

#ppSF
./Execute --Variation Root/PPDataExtraZWeight0.root --Reference Root/PPData.root \
   --Output Sys/v17/PPSF0.root \
   --Scheme Maximum
./Execute --Variation Root/PPDataExtraZWeight1.root --Reference Root/PPData.root \
   --Output Sys/v17/PPSF1.root \
   --Scheme Maximum
./Execute --Variation Root/PPDataExtraZWeight2.root --Reference Root/PPData.root \
   --Output Sys/v17/PPSF2.root \
   --Scheme Maximum
./Execute --Variation Root/PPDataExtraZWeight3.root --Reference Root/PPData.root \
   --Output Sys/v17/PPSF3.root \
   --Scheme Maximum
./Execute --Variation Sys/v17/PPSF0.root --Reference Sys/v17/PPSF1.root \
   --Output Sys/v17/PPSFSys1.root \
   --DirectMode true --Scheme DirectMaximum
./Execute --Variation Sys/v17/PPSF2.root --Reference Sys/v17/PPSF3.root \
   --Output Sys/v17/PPSFSys2.root \
   --DirectMode true --Scheme DirectMaximum
./Execute --Variation Sys/v17/PPSFSys1.root --Reference Sys/v17/PPSFSys2.root \
   --Output Sys/v17/PPSFCombined.root \
   --DirectMode true --Scheme DirectQuadraticSum

# Centrality definition
./Execute --Variation Root/DataHiBinUp.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbHiBinUp.root \
   --Scheme RMS
./Execute --Variation Root/DataHiBinDown.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbHiBinDown.root \
   --Scheme RMS
./Execute --Variation Sys/v17/PbPbHiBinUp.root --Reference Sys/v17/PbPbHiBinDown.root \
   --Output Sys/v17/PbPbHiBin.root \
   --DirectMode true --Scheme DirectMaximum

# vz cut
# ./Execute --Variation Root/Data_VZ1.root --Reference Root/Data.root \
#    --Output Sys/v17/PbPbVZ1.root \
#    --Scheme Maximum
# ./Execute --Variation Root/Data_VZ2.root --Reference Root/Data.root \
#    --Output Sys/v17/PbPbVZ2.root \
#    --Scheme Maximum
# ./Execute --Variation Root/Data_VZ3.root --Reference Root/Data.root \
#    --Output Sys/v17/PbPbVZ3.root \
#    --Scheme Maximum
# ./Execute --Variation Root/Data_VZ4.root --Reference Root/Data.root \
#    --Output Sys/v17/PbPbVZ4.root \
#    --Scheme Maximum
# ./Execute --Variation Sys/v17/PbPbVZ1.root --Reference Sys/v17/PbPbVZ2.root \
#    --Output Sys/v17/PbPbVZ12.root \
#    --DirectMode true --Scheme DirectMaximum
# ./Execute --Variation Sys/v17/PbPbVZ3.root --Reference Sys/v17/PbPbVZ4.root \
#    --Output Sys/v17/PbPbVZ34.root \
#    --DirectMode true --Scheme DirectMaximum
# ./Execute --Variation Sys/v17/PbPbVZ12.root --Reference Sys/v17/PbPbVZ34.root \
#    --Output Sys/v17/PbPbVZ.root \
#    --DirectMode true --Scheme DirectMaximum

#tight/loose track selection
./Execute --Variation Root/DataLoose.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbLoose.root \
   --Scheme RMS
./Execute --Variation Root/DataTight.root --Reference Root/Data.root \
   --Output Sys/v17/PbPbTight.root \
   --Scheme RMS
./Execute --Variation Sys/v17/PbPbLoose.root --Reference Sys/v17/PbPbTight.root \
   --Output Sys/v17/PbPbTrackSel.root \
   --DirectMode true --Scheme DirectMaximum

# Now we combine everything
#./ExecuteCombine --File Sys/v17/PbPbMuMatch.root,Sys/v17/PbPbUE25.root,Sys/v17/PbPbSFCombined1.root,Sys/v17/PbPbSFCombined2.root,Sys/v17/PbPbSFCombined3.root,Sys/v17/PbPbHiBin.root,Sys/v17/PbPbTrackSel.root --Output Sys/v17/PbPbAll.root
./ExecuteCombine --File Sys/v17/PbPbMuMatch.root,Sys/v17/PbPbSFCombined1.root,Sys/v17/PbPbSFCombined2.root,Sys/v17/PbPbSFCombined3.root,Sys/v17/PbPbHiBin.root,Sys/v17/PbPbTrackSel.root --Output Sys/v17/PbPbAll.root
./ExecuteCombine --File Sys/v17/PPMuMatch.root,Sys/v17/PPPU.root,Sys/v17/PPSFCombined.root --Output Sys/v17/PPAll.root
