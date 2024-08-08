

default: TestRun #TestRunGenRecoPlot

Prepare:
	ln -sf /eos/cms/store/group/phys_heavyions/pchou/ PinChunOutput
	ln -sf /eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230310_ZHadronSkims/ YiOutput

TestRun: Execute
	./Execute --Input PinChunOutput/OutputData_v17_PFmuon/Result14.root --Output Test.root

TestRunPlot: ExecutePlot
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_10_20_PV_0_1      --Output Plots_0_30_40_1_2.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_20_50_PV_0_1      --Output Plots_0_30_40_2_5.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_50_100_PV_0_1     --Output Plots_0_30_40_5_10.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_100_1000_PV_0_1   --Output Plots_0_30_40_10_100.pdf
	./ExecutePlot --Tag Centrality_30_90_ZPT_40_200_TrackPT_10_20_PV_0_1     --Output Plots_30_90_40_1_2.pdf
	./ExecutePlot --Tag Centrality_30_90_ZPT_40_200_TrackPT_20_50_PV_0_1     --Output Plots_30_90_40_2_5.pdf
	./ExecutePlot --Tag Centrality_30_90_ZPT_40_200_TrackPT_50_100_PV_0_1    --Output Plots_30_90_40_5_10.pdf
	./ExecutePlot --Tag Centrality_30_90_ZPT_40_200_TrackPT_100_1000_PV_0_1  --Output Plots_30_90_40_10_100.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_10_20_PV_2_10     --Output PlotsPV_0_30_40_1_2.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_20_50_PV_2_10     --Output PlotsPV_0_30_40_2_5.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_50_100_PV_2_10    --Output PlotsPV_0_30_40_5_10.pdf
	./ExecutePlot --Tag Centrality_0_30_ZPT_40_200_TrackPT_100_1000_PV_2_10  --Output PlotsPV_0_30_40_10_100.pdf
	cp Plots*.pdf ~/public/html/

TestRunPUPlot: ExecutePUPlot
	./ExecutePUPlot

TestRunGenRecoPlot: ExecuteGenRecoPlot
	./ExecuteGenRecoPlot --Gen PPMCGen.root --Reco PPMC.root --OutputTag PP \
		--Tag Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_10
	./ExecuteGenRecoPlot --Gen MCGen.root --Reco MC.root --OutputTag PbPb0To30 \
		--Tag Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_10
	./ExecuteGenRecoPlot --Gen MCGen.root --Reco MC.root --OutputTag PbPb30To90 \
		--Tag Centrality_30_90_ZPT_40_200_TrackPT_10_1000_PV_0_10
	./ExecuteGenRecoPlot --Gen PPMCGen.root --Reco PPMCNoResidual.root --OutputTag PPNoResidual \
		--Tag Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_10
	./ExecuteGenRecoPlot --Gen MCGen.root --Reco MCNoResidual.root --OutputTag PbPb0To30NoResidual \
		--Tag Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_10
	./ExecuteGenRecoPlot --Gen MCGen.root --Reco MCNoResidual.root --OutputTag PbPb30To90NoResidual \
		--Tag Centrality_30_90_ZPT_40_200_TrackPT_10_1000_PV_0_10

Execute: FillHistogram.cpp
	g++ FillHistogram.cpp -o Execute `root-config --cflags --libs` \
		-I$(ProjectBase)/CommonCode/include $(ProjectBase)/CommonCode/library/*.o

RunAll: RunMix RunNoMix RunGen RunNoResidual RunHiBin RunMuMatch RunDataMixUE RunExtraZWeight RunMCMixUEUp RunMCMixUEDown RunMCLoose RunMCTight RunDataLoose RunDataTight RunVZ RunLoose

RunMix: RunDataMix RunMCMix

RunNoMix: RunData RunMC RunPPMC RunPPData

RunGen: RunPPGen RunMCGen RunMCSignalGen

RunNoResidual: RunMCNoResidual RunPPMCNoResidual RunDataNoResidual RunPPDataNoResidual

RunHiBin: RunDataHiBinUp RunDataHiBinDown RunDataMixHiBinUp RunDataMixHiBinDown

RunVZ: RunDataVZ RunMCVZ RunPPDataVZ RunPPMCVZ

RunLoose: RunDataLoose RunMCLoose

RunData: Execute
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output Data.root --IsPP false --IsMC false

RunDataNoResidual: Execute
	./Execute --Input `ls PinChunOutput/OutputData_v14/*root | tr '\n' ','` --Output DataNoResidual.root --IsPP false --IsMC false --SkipResidual true

RunDataLoose: Execute
	./Execute --Input `ls YiOutput/OutputDataLoose_v15c/*root | tr '\n' ','` --Output DataLoose.root --IsPP false --IsMC false

RunDataMix: Execute
	./Execute --Input `ls PinChunOutput/OutputDataSigBkg_v17d_PFmuon_10HF/*root | tr '\n' ','` --Output DataMix.root --IsPP false --IsMC false

RunDataMixUE: Execute
	./Execute --Input `ls PinChunOutput/OutputDataBackgroundUEUp25_v17_PFmuon/*root | tr '\n' ','` --Output DataMixUEUp25.root --IsPP false --IsMC false
	./Execute --Input `ls PinChunOutput/OutputDataBackgroundUEDown25_v17_PFmuon/*root | tr '\n' ','` --Output DataMixUEDown25.root --IsPP false --IsMC false

RunDataHiBinUp: Execute
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataHiBinUp.root --IsPP false --IsMC false --RedoHiBin true --HiBinVariation 1

RunDataHiBinDown: Execute
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataHiBinDown.root --IsPP false --IsMC false --RedoHiBin true --HiBinVariation -1

RunDataMixHiBinUp: Execute
	./Execute --Input `ls PinChunOutput/OutputDataSigBkg_v17d_PFmuon_10HF/*root | tr '\n' ','` --Output DataMixHiBinUp.root --IsPP false --IsMC false --RedoHiBin true --HiBinVariation 1

RunDataVZ: Execute
	./Execute --Input `ls PinChunOutput/OutputData_v14/*root | tr '\n' ','` --Output DataVZ1.root --IsPP false --IsMC false --MinVZ -1000 --MaxVZ -5
	./Execute --Input `ls PinChunOutput/OutputData_v14/*root | tr '\n' ','` --Output DataVZ2.root --IsPP false --IsMC false --MinVZ -5 --MaxVZ 0
	./Execute --Input `ls PinChunOutput/OutputData_v14/*root | tr '\n' ','` --Output DataVZ3.root --IsPP false --IsMC false --MinVZ 0 --MaxVZ 5
	./Execute --Input `ls PinChunOutput/OutputData_v14/*root | tr '\n' ','` --Output DataVZ4.root --IsPP false --IsMC false --MinVZ 5 --MaxVZ 1000

RunMCVZ: Execute
	./Execute --Input `ls PinChunOutput/OutputMC_v14/*root | tr '\n' ','` --Output MCVZ1.root --IsPP false --IsMC true --MinVZ -1000 --MaxVZ -5
	./Execute --Input `ls PinChunOutput/OutputMC_v14/*root | tr '\n' ','` --Output MCVZ2.root --IsPP false --IsMC true --MinVZ -5 --MaxVZ 0
	./Execute --Input `ls PinChunOutput/OutputMC_v14/*root | tr '\n' ','` --Output MCVZ3.root --IsPP false --IsMC true --MinVZ 0 --MaxVZ 5
	./Execute --Input `ls PinChunOutput/OutputMC_v14/*root | tr '\n' ','` --Output MCVZ4.root --IsPP false --IsMC true --MinVZ 5 --MaxVZ 1000

RunPPDataVZ: Execute
	./Execute --Input `ls PinChunOutput/OutputPPData_v14/*root | tr '\n' ','` --Output PPDataVZ1.root --IsPP true --IsMC false --MinVZ -1000 --MaxVZ -5
	./Execute --Input `ls PinChunOutput/OutputPPData_v14/*root | tr '\n' ','` --Output PPDataVZ2.root --IsPP true --IsMC false --MinVZ -5 --MaxVZ 0
	./Execute --Input `ls PinChunOutput/OutputPPData_v14/*root | tr '\n' ','` --Output PPDataVZ3.root --IsPP true --IsMC false --MinVZ 0 --MaxVZ 5
	./Execute --Input `ls PinChunOutput/OutputPPData_v14/*root | tr '\n' ','` --Output PPDataVZ4.root --IsPP true --IsMC false --MinVZ 5 --MaxVZ 1000

RunPPMCVZ: Execute
	./Execute --Input `ls PinChunOutput/OutputPPMC_v14/*root | tr '\n' ','` --Output PPMCVZ1.root --IsPP true --IsMC true --MinVZ -1000 --MaxVZ -5
	./Execute --Input `ls PinChunOutput/OutputPPMC_v14/*root | tr '\n' ','` --Output PPMCVZ2.root --IsPP true --IsMC true --MinVZ -5 --MaxVZ 0
	./Execute --Input `ls PinChunOutput/OutputPPMC_v14/*root | tr '\n' ','` --Output PPMCVZ3.root --IsPP true --IsMC true --MinVZ 0 --MaxVZ 5
	./Execute --Input `ls PinChunOutput/OutputPPMC_v14/*root | tr '\n' ','` --Output PPMCVZ4.root --IsPP true --IsMC true --MinVZ 5 --MaxVZ 1000

RunDataMixHiBinDown: Execute
	./Execute --Input `ls PinChunOutput/OutputDataSigBkg_v17d_PFmuon_10HF/*root | tr '\n' ','` --Output DataMixHiBinDown.root --IsPP false --IsMC false --RedoHiBin true --HiBinVariation -1

RunMC: Execute
	time ./Execute --Input `ls PinChunOutput/OutputMC_v17_PFmuon/*root | tr '\n' ','` --Output MC.root --IsPP false --IsMC true --Fraction 1.0

RunMCMix: Execute
	# ./Execute --Input `ls YiOutput/OutputMCBackground_v17_PFmuon/*root | tr '\n' ','` --Output MCMix.root --IsPP false --IsMC true --Fraction 0.1
	time ./Execute --Input `ls PinChunOutput/OutputMCSigBkg_v17d_PFmuon_350_ov5_10HF/*root | tr '\n' ','` --Output MCMix.root --IsPP false --IsMC true --Fraction 1.0
	#time ./Execute --Input `ls YiOutputNew/OutputMCBackground_v17_PFmuon/*root | tr '\n' ','` --Output MCMix.root --IsPP false --IsMC true --Fraction 1.0

RunMCMixTest: Execute
	time ./Execute --Input `ls YiOutputNew/OutputMCBackground_v15/*root | head -n 1` --Output MCMixTest.root --IsPP false --IsMC true --Fraction 1.0

RunMCMixAdHoc: Execute
	# ./Execute --Input `ls YiOutput/OutputMCBackground_v17_PFmuon/*root | tr '\n' ','` --Output MCMix.root --IsPP false --IsMC true --Fraction 0.1
	time ./Execute --Input `ls PinChunOutput/OutputMCSigBkg_v17d_PFmuon_350_ov5_10HF/*root | tr '\n' ','` --Output MCMixAdHoc.root --IsPP false --IsMC true --Fraction 1.0 --DoAdHocSignalHF true

RunMCMixUEUp: Execute
	./Execute --Input `ls PinChunOutput/OutputMCBackgroundUEUp25_v17d_PFmuon/*root | tr '\n' ','` --Output MCMixUEUp25.root --IsPP false --IsMC true

RunMCMixUEDown: Execute
	./Execute --Input `ls PinChunOutput/OutputMCBackgroundUEDown25_v17d_PFmuon/*root | tr '\n' ','` --Output MCMixUEDown25.root --IsPP false --IsMC true

RunPPMC: Execute
	./Execute --Input `ls PinChunOutput/OutputPPMC_v17_PFmuon/*root | tr '\n' ','` --Output PPMC.root --Fraction 1.0 --IsPP true --IsMC true

RunPPData: Execute
	./Execute --Input `ls PinChunOutput/OutputPPData_v17_PFmuon/*root | tr '\n' ','` --Output PPData.root --Fraction 1.0 --IsPP true --IsMC false

RunPPDataNoResidual: Execute
	./Execute --Input `ls PinChunOutput/OutputPPData_v14/*root | tr '\n' ','` --Output PPDataNoResidual.root --Fraction 1.0 --IsPP true --IsMC false --SkipResidual true

RunPPGen: Execute
	./Execute --Input `ls PinChunOutput/OutputPPMCGen_v17_PFmuon/*root | tr '\n' ','` --Output PPMCGen.root --Fraction 1.0 --IsPP true --IsMC true --DoGen true

RunMCGen: Execute
	./Execute --Input `ls PinChunOutput/OutputMCGen_v17_PFmuon/*root | tr '\n' ','` --Output MCGen.root --IsPP false --IsMC true --Fraction 1.0 --DoGen true

RunMCSignalGen: Execute
	./Execute --Input `ls PinChunOutput/OutputMCGen_v17_PFmuon/*root | tr '\n' ','` --Output MCSignalGen.root --IsPP false --IsMC true --Fraction 1.0 --DoGen true --DoSignalEvent true

RunMCNoResidual: Execute
	./Execute --Input `ls PinChunOutput/OutputMC_v17_PFmuon/*root | tr '\n' ','` --Output MCNoResidual.root --IsPP false --IsMC true --Fraction 1.0 --SkipResidual true

RunPPMCNoResidual: Execute
	./Execute --Input `ls PinChunOutput/OutputPPMC_v17_PFmuon/*root | tr '\n' ','` --Output PPMCNoResidual.root --Fraction 1.0 --IsPP true --IsMC true --SkipResidual true

RunMuMatch: Execute
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataMuMatch.root --IsPP false --IsMC false --AlternateMuTag true --MuTagRange 0.0025
	./Execute --Input `ls PinChunOutput/OutputPPData_v17_PFmuon/*root | tr '\n' ','` --Output PPDataMuMatch.root --Fraction 1.0 --IsPP true --IsMC false --AlternateMuTag true --MuTagRange 0.0025

RunExtraZWeight: Execute
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight0.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 0
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight1.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 1
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight2.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 2
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight3.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 3
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight4.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 4
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight5.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 5
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight6.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 6
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight7.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 7
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight8.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 8
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight9.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 9
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight10.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 10
	./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output DataExtraZWeight11.root -IsPP false --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 11
	./Execute --Input `ls PinChunOutput/OutputPPData_v17_PFmuon/*root | tr '\n' ','` --Output PPDataExtraZWeight0.root -IsPP true --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 0
	./Execute --Input `ls PinChunOutput/OutputPPData_v17_PFmuon/*root | tr '\n' ','` --Output PPDataExtraZWeight1.root -IsPP true --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 1
	./Execute --Input `ls PinChunOutput/OutputPPData_v17_PFmuon/*root | tr '\n' ','` --Output PPDataExtraZWeight2.root -IsPP true --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 2
	./Execute --Input `ls PinChunOutput/OutputPPData_v17_PFmuon/*root | tr '\n' ','` --Output PPDataExtraZWeight3.root -IsPP true --IsMC false --DoExtraZWeight true --ExtraZWeightIndex 3

RunMCLoose: Execute
	time ./Execute --Input `ls PinChunOutput/OutputMCLoose_v17_PFmuon/*root | tr '\n' ','` --Output MCLoose.root --IsPP false --IsMC true

RunMCTight: Execute
	time ./Execute --Input `ls PinChunOutput/OutputMCTight_v17_PFmuon/*root | tr '\n' ','` --Output MCTight.root --IsPP false --IsMC true

RunDataLoose: Execute
	time ./Execute --Input `ls PinChunOutput/OutputDataLoose_v17_PFmuon/*root | tr '\n' ','` --Output DataLoose.root --IsPP false --IsMC false

RunDataTight: Execute
	time ./Execute --Input `ls PinChunOutput/OutputDataTight_v17_PFmuon/*root | tr '\n' ','` --Output DataTight.root --IsPP false --IsMC false

RunMCVZ: Execute
	time ./Execute --Input `ls PinChunOutput/OutputMC_v17_PFmuon/*root | tr '\n' ','` --Output MC_VZ10.root --IsPP false --IsMC false --Fraction 1.0  --VZMin -10 --VZMax 10
	time ./Execute --Input `ls PinChunOutput/OutputMC_v17_PFmuon/*root | tr '\n' ','` --Output MC_VZ20.root --IsPP false --IsMC false --Fraction 1.0  --VZMin -20 --VZMax 20
	#time ./Execute --Input `ls PinChunOutput/OutputMC_v17_PFmuon/*root | tr '\n' ','` --Output MC_VZ1.root --IsPP false --IsMC true --Fraction 1.0  --VZMax -5
	#time ./Execute --Input `ls PinChunOutput/OutputMC_v17_PFmuon/*root | tr '\n' ','` --Output MC_VZ2.root --IsPP false --IsMC true --Fraction 1.0  --VZMin -5 --VZMax 0
	#time ./Execute --Input `ls PinChunOutput/OutputMC_v17_PFmuon/*root | tr '\n' ','` --Output MC_VZ3.root --IsPP false --IsMC true --Fraction 1.0  --VZMin 0 --VZMax 5
	#time ./Execute --Input `ls PinChunOutput/OutputMC_v17_PFmuon/*root | tr '\n' ','` --Output MC_VZ4.root --IsPP false --IsMC true --Fraction 1.0  --VZMin 5

RunDataVZ: Execute
	time ./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output Data_VZ10.root --IsPP false --IsMC false --Fraction 1.0  --VZMin -10 --VZMax 10
	time ./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output Data_VZ20.root --IsPP false --IsMC false --Fraction 1.0  --VZMin -20 --VZMax 20
	#time ./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output Data_VZ1.root --IsPP false --IsMC false --Fraction 1.0  --VZMax -5
	#time ./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output Data_VZ2.root --IsPP false --IsMC false --Fraction 1.0  --VZMin -5 --VZMax 0
	#time ./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output Data_VZ3.root --IsPP false --IsMC false --Fraction 1.0  --VZMin 0 --VZMax 5
	#time ./Execute --Input `ls PinChunOutput/OutputData_v17_PFmuon/*root | tr '\n' ','` --Output Data_VZ4.root --IsPP false --IsMC false --Fraction 1.0  --VZMin 5
>>>>>>> 235dae3ff51bb22d93c46df70206746dd5b85221

ExecutePlot: MakePlots.cpp
	g++ MakePlots.cpp -o ExecutePlot `root-config --cflags --libs` \
		-I$(ProjectBase)/CommonCode/include

ExecutePUPlot: MakePUPlots.cpp
	g++ MakePUPlots.cpp -o ExecutePUPlot `root-config --cflags --libs` \
		-I$(ProjectBase)/CommonCode/include

ExecuteGenRecoPlot: MakeGenRecoClosure.cpp
	g++ MakeGenRecoClosure.cpp -o ExecuteGenRecoPlot `root-config --cflags --libs` \
		-I$(ProjectBase)/CommonCode/include

