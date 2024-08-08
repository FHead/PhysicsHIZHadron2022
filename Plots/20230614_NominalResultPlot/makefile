
default: Prepare TestRunCentrality

Prepare:
	ln -sf $(ProjectBase)/BasicDistribution/20230605_DeltaPhiReproduction Root
	ln -sf $(ProjectBase)/Systematics/20230616_SystematicsHarvesting/Sys/v17 Sys

TestRun: Execute
	./Execute --OutputBase Test --SkipSystematics true

TestRunCentrality: Execute
	./Execute --OutputBase MCCentrality \
		--DataFiles Root/MC.root,Root/MCMix.root --SkipSystematics true --SkipSelfSubtract true \
		--CurveLabels "MC","Mix" \
		--ToPlot "HiBin" \
		--Tags Centrality_0_30_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_0_10_ZPT_40_200_TrackPT_10_20_PV_0_10,Centrality_10_30_ZPT_40_200_TrackPT_10_20_PV_0_10 \
		--Labels "0-30%,0-10%,10-30%" \
   	--ExtraInfo "40 < p_{T}^{Z} < 200 GeV,1 < p_{T}^{trk} < 2 GeV" \
		--XAxisLabel hiBin --YAxisLabel 'a.u.' --RAxisLabel Difference \
		--XMin 0 --XMax 60 --YMin -0.02 --YMax 0.15 --RMin -0.02 --RMax 0.02 \
		--LegendLeft 0.08 --LegendBottom 0.40

Execute: MakePlot.cpp
	g++ MakePlot.cpp -o Execute `root-config --cflags --libs` -I$(ProjectBase)/CommonCode/include/

RunSystematics: Execute
	bash MakeSystematicPlots.sh

RunNominal: Execute
	bash MakeNominal.sh

RunMC: Execute
	bash MakeMC.sh

