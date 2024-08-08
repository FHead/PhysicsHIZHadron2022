default: TestRun

TestRun: Execute
	mkdir -p log
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputData_v17/ \
		--Output GraphDataSignal_v17.root --Fraction 1 \
		 > log/GraphDataSignal_v17.out 2> log/GraphDataSignal_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputDataBackground_v15c/ \
		--Output GraphDataBackground_v17.root --Fraction 1 \
		 > log/GraphDataBackground_v17.out 2> log/GraphDataBackground_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v17/ \
		--Output GraphMCSignal_v17.root --Fraction 1 \
		 > log/GraphMCSignal_v17.out 2> log/GraphMCSignal_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCBackground_v15c/ \
		--Output GraphMCBackground_v17.root --Fraction 1 \
		 > log/GraphMCBackground_v17.out 2> log/GraphMCBackground_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v17/ \
		--Output GraphPPMC_v17.root --IgnoreCentrality true --Fraction 1 \
		 > log/GraphPPMC_v17.out 2> log/GraphPPMC_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMC_v17/ \
		--Output GraphPPMC0Sub_v17.root --IgnoreCentrality true --OnlyZeroSub true --Fraction 1 \
		 > log/GraphPPMC0Sub_v17.out 2> log/GraphPPMC0Sub_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v17/ \
		--Output GraphMCSignalGen_v17.root --Fraction 1 --DoGenCorrelation true \
		 > log/GraphMCSignalGen_v17.out 2> log/GraphMCSignalGen_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGen_v17/ \
		--Output GraphMCSignalGen0Sub_v17.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true \
		 > log/GraphMCSignalGen0Sub_v17.out 2> log/GraphMCSignalGen0Sub_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenbkg_v15c/ \
		--Output GraphMCBackgroundGen_v17.root --Fraction 1 --DoGenCorrelation true \
		 > log/GraphMCBackgroundGen_v17.out 2> log/GraphMCBackgroundGen_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMCGenbkg_v15c/ \
		--Output GraphMCBackgroundGen0Sub_v17.root --OnlyZeroSub true --Fraction 1 --DoGenCorrelation true \
		 > log/GraphMCBackgroundGen0Sub_v17.out 2> log/GraphMCBackgroundGen0Sub_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v17/ \
		--Output GraphPPMCGen_v17.root --IgnoreCentrality true --Fraction 1 --DoGenCorrelation true \
		 > log/GraphPPMCGen_v17.out 2> log/GraphPPMCGen_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPMCGen_v17/ \
		--Output GraphPPMCGen0NPU_v17.root --IgnoreCentrality true --OnlyZeroNPU true --Fraction 1 --DoGenCorrelation true \
		 > log/GraphPPMCGen0NPU_v17.out 2> log/GraphPPMCGen0NPU_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputMC_v17/ \
		--Output GraphMCSignal0Sub_v17.root --OnlyZeroSub true --Fraction 1 \
		 > log/GraphMCSignal0Sub_v17.out 2> log/GraphMCSignal0Sub_v17.err < /dev/null &
	./Execute --InputBase /eos/cms/store/group/phys_heavyions/pchou/OutputPPData_v17/ \
		--Output GraphPPData_v17.root --IgnoreCentrality true --Fraction 1 \
		 > log/GraphPPData_v17.out 2> log/GraphPPData_v17.err < /dev/null &

TestExploration: ExecuteExploration
	./ExecuteExploration --SignalFile GraphMCSignal.root --BackgroundFile GraphMCBackground.root \
		--Folder Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00 --Histogram HEtaPhi \
		--Output Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00_HEtaPhi.pdf
	./ExecuteExploration --SignalFile GraphMCSignal.root --BackgroundFile GraphMCBackground.root \
		--Folder Plot_ZPT_0_2000_Cent_0_10_TrackPT_0p00_1000p00 --Histogram HEtaPhi \
		--Output Plot_ZPT_0_2000_Cent_0_10_TrackPT_0p00_1000p00_HEtaPhi.pdf
	./ExecuteExploration --SignalFile GraphMCSignal.root --BackgroundFile GraphMCBackground.root \
		--Folder Plot_ZPT_0_2000_Cent_50_90_TrackPT_0p00_1000p00 --Histogram HEtaPhi \
		--Output Plot_ZPT_0_2000_Cent_50_90_TrackPT_0p00_1000p00_HEtaPhi.pdf
	./ExecuteExploration --SignalFile GraphMCSignal.root --BackgroundFile GraphMCBackground.root \
		--Folder Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00 --Histogram HWTAEtaPhi \
		--Output Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00_HWTAEtaPhi.pdf
	./ExecuteExploration --SignalFile GraphMCSignal.root --BackgroundFile GraphMCBackground.root \
		--Folder Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00 --Histogram HMaxOppositeHadronEtaPhi \
		--Output Plot_ZPT_0_2000_Cent_0_90_TrackPT_0p00_1000p00_HMaxOppositeHadronEtaPhi.pdf

Execute: ZTrackAnalysis.cpp
	g++ ZTrackAnalysis.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17

Draw: ExecuteDraw
	./ExecuteDraw

ExecuteDraw: ZtrackDraw.cpp
	g++ ZtrackDraw.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteDraw `root-config --cflags --libs` -std=c++17

ExecuteExploration: SimpleExploration.cpp
	g++ SimpleExploration.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteExploration `root-config --cflags --libs` -std=c++17

DrawZdPhi: ExecuteDrawZdPhi
	./ExecuteDrawZdPhi

ExecuteDrawZdPhi: ZdPhiDraw.cpp
	g++ ZdPhiDraw.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteDrawZdPhi `root-config --cflags --libs` -std=c++17

CheckSubtract: ExecuteCheckSubtract
	./ExecuteCheckSubtract

ExecuteCheckSubtract: ZcheckSubtract.cpp
	g++ ZcheckSubtract.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteCheckSubtract `root-config --cflags --libs` -std=c++17

CheckBasic: ExecuteZcheckBasic
	./ExecuteZcheckBasic

ExecuteZcheckBasic: ZcheckBasic.cpp
	g++ ZcheckBasic.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteZcheckBasic `root-config --cflags --libs` -std=c++17

DrawProj: ExecuteDrawProj
	./ExecuteDrawProj

ExecuteDrawProj: ZtrackProj.cpp
	g++ ZtrackProj.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteDrawProj `root-config --cflags --libs` -std=c++17

DrawBkgSub: ExecuteBkgSub
	./ExecuteBkgSub

ExecuteBkgSub: ZtrackBkgSub.cpp
	g++ ZtrackBkgSub.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteBkgSub `root-config --cflags --libs` -std=c++17

DrawBasicBkgSub: ExecuteBasicBkgSub
	./ExecuteBasicBkgSub

ExecuteBasicBkgSub: ZBasicBkgSub.cpp
	g++ ZBasicBkgSub.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o ExecuteBasicBkgSub `root-config --cflags --libs` -std=c++17

Draw2DBkgSub: Execute2DBkgSub
	./Execute2DBkgSub

Execute2DBkgSub: Z2DBkgSub.cpp
	g++ Z2DBkgSub.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute2DBkgSub `root-config --cflags --libs` -std=c++17
