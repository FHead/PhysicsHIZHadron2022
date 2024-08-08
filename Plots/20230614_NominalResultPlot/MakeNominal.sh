#!/bin/bash

mkdir -p /eos/user/p/pchou/figs/ResultNominal/20240129/v17d_NoShiftNoSelfSub

for CRange in 0:30 0:10 10:30 30:90 30:50 50:90 50:70 70:90
do
   CMin=`echo $CRange | tr ':' ' ' | awk '{print $1}'`
   CMax=`echo $CRange | tr ':' ' ' | awk '{print $2}'`

   Tags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_10,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_10
   SecondTags=Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_10_20_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_20_40_PV_0_1,Centrality_${CMin}_${CMax}_ZPT_40_200_TrackPT_40_100_PV_0_1
   Labels="1 < p_{T}^{trk} < 2 GeV","2 < p_{T}^{trk} < 4 GeV","4 < p_{T}^{trk} < 10 GeV"
   PPExtraInfo="40 < p_{T}^{Z} < 200 GeV"
   ExtraInfo="40 < p_{T}^{Z} < 200 GeV,${CMin}-${CMax}%"
   Plotting="--XAxisLabel |#Delta#phi_{trk,Z}| --YAxisLabel dN_{ch}/d#Delta#phi/N_{Z} --RAxisLabel Difference --XMin 0 --XMax 3.1415926535 --YMin -6 --YMax 15 --RMin -7 --RMax 7 --LegendLeft 0.08 --LegendBottom 0.40"
   Suffix="C$CMin$CMax"
   TagShifts=Count_ZPT_40_200_Cent_0_10_TrackPT_1p00_2p00,Count_ZPT_40_200_Cent_${CMin}_${CMax}_TrackPT_2p00_4p00,Count_ZPT_40_200_Cent_${CMin}_${CMax}_TrackPT_4p00_10p00,

   ./Execute --OutputBase /eos/user/p/pchou/figs/ResultNominal/20240129/v17d_NoShiftNoSelfSub/ResultNominal$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SubtractFiles None,Root/DataMix.root --SkipSubtract false --SkipSelfSubtract true \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll_UE.root --SkipSystematics false \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaPhi" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" --TagShifts "$TagShifts" --SkipShifting true \
      $Plotting

   #Plotting="--XAxisLabel |#Delta#eta_{trk,Z}| --YAxisLabel <#DeltaN_{ch}>/event --RAxisLabel Difference --XMin 0 --XMax 3.5 --YMin -6 --YMax 12 --RMin -7 --RMax 7 --LegendLeft 0.08 --LegendBottom 0.40"
#
   #./Execute --OutputBase Plots/ResultNominal/v17/ResultNominalEta$Suffix \
   #   --DataFiles Root/PPData.root,Root/Data.root \
   #   --SubtractFiles None,Root/DataMix.root --SkipSubtract false --SkipSelfSubtract true \
   #   --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root --SkipSystematics false \
   #   --CurveLabels "pp","PbPb" \
   #   --ToPlot "DeltaEta" \
   #   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   #   $Plotting
   #./Execute --OutputBase Plots/ResultNominal/v17/ResultNominalEtaJetSide$Suffix \
   #   --DataFiles Root/PPData.root,Root/Data.root \
   #   --SubtractFiles None,Root/DataMix.root --SkipSubtract false --SkipSelfSubtract true \
   #   --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root --SkipSystematics false \
   #   --CurveLabels "pp","PbPb" \
   #   --ToPlot "DeltaEtaJetSide" \
   #   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   #   $Plotting
   #./Execute --OutputBase Plots/ResultNominal/v17/ResultNominalEtaZSide$Suffix \
   #   --DataFiles Root/PPData.root,Root/Data.root \
   #   --SubtractFiles None,Root/DataMix.root --SkipSubtract false --SkipSelfSubtract true \
   #   --SystematicFiles Sys/PPAll.root,Sys/PbPbAll.root --SkipSystematics false \
   #   --CurveLabels "pp","PbPb" \
   #   --ToPlot "DeltaEtaZSide" \
   #   --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
   #   $Plotting

   Plotting="--XAxisLabel |#Deltay_{trk,Z}| --YAxisLabel dN_{ch}/d#Deltay/N_{Z} --RAxisLabel Difference --XMin 0 --XMax 3.5 --YMin -6 --YMax 12 --RMin -7 --RMax 7 --LegendLeft 0.08 --LegendBottom 0.40"

   ./Execute --OutputBase /eos/user/p/pchou/figs/ResultNominal/20240129/v17d_NoShiftNoSelfSub/ResultNominalY$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SubtractFiles None,Root/DataMix.root --SkipSubtract false --SkipSelfSubtract true \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll_UE.root --SkipSystematics false  --TagShifts "$TagShifts" --SkipShifting true \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaY" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase /eos/user/p/pchou/figs/ResultNominal/20240129/v17d_NoShiftNoSelfSub/ResultNominalYJetSide$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SubtractFiles None,Root/DataMix.root --SkipSubtract false --SkipSelfSubtract true \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll_UE.root --SkipSystematics false  --TagShifts "$TagShifts" --SkipShifting true \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaYJetSide" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase /eos/user/p/pchou/figs/ResultNominal/20240129/v17d_NoShiftNoSelfSub/ResultNominalYZSide$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SubtractFiles None,Root/DataMix.root --SkipSubtract false --SkipSelfSubtract true \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll_UE.root --SkipSystematics false  --TagShifts "$TagShifts" --SkipShifting true \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaYZSide" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting

   Plotting="--XAxisLabel |#Delta#eta_{trk,Z}| --YAxisLabel dN_{ch}/d#Delta#eta/N_{Z} --RAxisLabel Difference --XMin 0 --XMax 3.5 --YMin -6 --YMax 12 --RMin -7 --RMax 7 --LegendLeft 0.08 --LegendBottom 0.40"

   ./Execute --OutputBase /eos/user/p/pchou/figs/ResultNominal/20240129/v17d_NoShiftNoSelfSub/ResultNominalEta$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SubtractFiles None,Root/DataMix.root --SkipSubtract false --SkipSelfSubtract true \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll_UE.root --SkipSystematics false  --TagShifts "$TagShifts" --SkipShifting true \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaEta" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase /eos/user/p/pchou/figs/ResultNominal/20240129/v17d_NoShiftNoSelfSub/ResultNominalEtaJetSide$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SubtractFiles None,Root/DataMix.root --SkipSubtract false --SkipSelfSubtract true \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll_UE.root --SkipSystematics false  --TagShifts "$TagShifts" --SkipShifting true \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaEtaJetSide" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting
   ./Execute --OutputBase /eos/user/p/pchou/figs/ResultNominal/20240129/v17d_NoShiftNoSelfSub/ResultNominalEtaZSide$Suffix \
      --DataFiles Root/PPData.root,Root/Data.root \
      --SubtractFiles None,Root/DataMix.root --SkipSubtract false --SkipSelfSubtract true \
      --SystematicFiles Sys/PPAll.root,Sys/PbPbAll_UE.root --SkipSystematics false  --TagShifts "$TagShifts" --SkipShifting true \
      --CurveLabels "pp","PbPb" \
      --ToPlot "DeltaEtaZSide" \
      --Tags "$Tags" --Labels "$Labels" --ExtraInfo "$ExtraInfo" \
      $Plotting


done



