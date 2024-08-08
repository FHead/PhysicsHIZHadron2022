PbPbBackgroundData   := $(shell DHQuery Setting.dh Sample PbPbBackgroundData)
PbPbSignalDoubleMuon  = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIDoubleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIDoubleMuon/20221101_ZHadronDoubleMuonWithMuTree/221101_212941/
PbPbSignalSingleMuon := $(shell DHQuery Setting.dh Sample PbPbSignalData)
PbPbSignalMC         := $(shell DHQuery Setting.dh Sample PbPbSignalMC)
PbPbBackgroundMC     := $(shell DHQuery Setting.dh Sample PbPbBackgroundMC)
#PbPbBackgroundPJMC   := $(shell DHQuery Setting.dh Sample PbPbBackgroundPJMC)
PPSignalMC           := $(shell DHQuery Setting.dh Sample PPSignalMC)
PPSignalData         := $(shell DHQuery Setting.dh Sample PPSignalData)

#YiEOS =  /eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230310_ZHadronSkims/
#EOSBase = /eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230625_ZHadronSkims
EOSBase = /eos/cms/store/group/phys_heavyions/pchou
CERNBOX = /eos/home-p/pchou

default: Prepare TestRun

Prepare:
	#ln -sf $(ProjectBase)/Skims/20230310_ZHadronSkims/Setting.dh .
	bash DefineNominalSetting.sh
	chmod u+x Expand
	
Execute: DoZHadronSkim.cpp
	g++ DoZHadronSkim.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o

TestRun: Execute
	./Execute --Input $(CERNBOX)/OutputMC_v18_PFmuon_mZ/Result10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		`./Expand Setting.dh PbPbBackgroundMC Nominal` \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root \
		--ReuseBackground true --WithProgressBar true

TestRunCent10: Execute
	./Execute --Input $(CERNBOX)/OutputMC_v18_PFmuon_mZ/Result11.root \
		--Output TestCent10.root --Fraction 1 \
		`./Expand Setting.dh PbPbBackgroundMCCent10 Nominal` \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root \
		--ReuseBackground true --WithProgressBar true

TestRunMCGenBackground: Execute
	./Execute --Input $(CERNBOX)/OutputMCGen_v18_PFmuon/Result10.root \
		--Output /tmp/$(USER)/TestMCGen.root --Fraction 0.1 \
		`./Expand Setting.dh PbPbBackgroundGenMC Nominal` \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_34.root,$(PbPbBackgroundMC)/HiForestMiniAOD_17.root,$(PbPbBackgroundMC)/HiForestMiniAOD_20.root \
		--ReuseBackground true --WithProgressBar true

TestRunMCSigBkg: Execute
	./Execute --Input $(EOSBase)/OutputMC_v17_PFmuon/Result73.root \
		--Output /tmp/$(USER)/TestMCSigBkg.root --Fraction 0.1 \
		`./Expand Setting.dh PbPbSignalMC Nominal` \
		--Background $(PbPbSignalMC)/HiForestMiniAOD_12.root,$(PbPbSignalMC)/HiForestMiniAOD_24.root,$(PbPbSignalMC)/HiForestMiniAOD_35.root,$(PbPbSignalMC)/HiForestMiniAOD_46.root,$(PbPbSignalMC)/HiForestMiniAOD_60.root \
		--ReuseBackground false --CheckForBackgroundZ true --WithProgressBar true

TestRunDataSigBkg: Execute
	./Execute --Input $(EOSBase)/OutputData_v17_PFmuon/Result10.root \
		--Output /tmp/$(USER)/TestDataSigBkg.root --Fraction 0.1 \
		`./Expand Setting.dh PbPbSignalData Nominal` \
		--Background $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_10.root,$(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root,$(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_15.root,$(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_16.root \
		--ReuseBackground true --CheckForBackgroundZ true --WithProgressBar true

TestRunPPMCSigBkg: Execute
	./Execute --Input $(EOSBase)/OutputPPMC_v17_PFmuon/Result7.root \
		--Output /tmp/$(USER)/TestPPMCSigBkg.root --Fraction 0.1 \
		`./Expand Setting.dh PPSignalMC Nominal` \
		--Background $(PPSignalMC)/HiForestAOD_12.root,$(PPSignalMC)/HiForestAOD_24.root,$(PPSignalMC)/HiForestAOD_35.root,$(PPSignalMC)/HiForestAOD_46.root,$(PPSignalMC)/HiForestAOD_60.root \
		--ReuseBackground true --CheckForBackgroundZ true --WithProgressBar true

TestRunPPDataSigBkg: Execute
	./Execute --Input $(EOSBase)/OutputPPData_v17_PFmuon/Result7.root \
		--Output /tmp/$(USER)/TestPPDataSigBkg.root --Fraction 0.1 \
		`./Expand Setting.dh PPSignalData Nominal` \
		--Background $(PPSignalData)/0000/HiForestAOD_12.root,$(PPSignalData)/0000/HiForestAOD_24.root,$(PPSignalData)/0000/HiForestAOD_35.root,$(PPSignalData)/0000/HiForestAOD_46.root,$(PPSignalData)/0000/HiForestAOD_60.root \
		--ReuseBackground true --CheckForBackgroundZ true --WithProgressBar true

>>>>>>> 235dae3ff51bb22d93c46df70206746dd5b85221
PrepareToRunRandomMCBackground:
	bash PrepareInputRandomBackground.sh \
		$(CERNBOX)/OutputMC_v18_PFmuon_mZ/ LogMCBackground_v18_mZ_742_v2/ $(CERNBOX)/OutputMCBackground_v18_mZ_742_v2/ $(PbPbBackgroundMC)/ 37 \
		`./Expand Setting.dh PbPbBackgroundMC Nominal`

PrepareToRunRandomMCBackgroundCent10:
	bash PrepareInputRandomBackground.sh \
		$(CERNBOX)/OutputMC_v18_PFmuon_mZ/ LogMCBackground_v18_mZ_cent10/ $(CERNBOX)/OutputMCBackground_v18_mZ_cent10/ $(PbPbBackgroundMC)/ 37 \
		`./Expand Setting.dh PbPbBackgroundMCCent10 Nominal`

#PrepareToRunRandomPJMCBackground:
#	bash PrepareInputRandomBackground.sh \
#		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackground_v17d_PJov1/ $(EOSBase)/OutputMCBackground_v17d_PJov1/ $(PbPbBackgroundPJMC)/ 37 \
#		`./Expand Setting.dh PbPbBackgroundMC Nominal`

PrepareToRunRandomDataBackground:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataBackground_v17_10HF/ $(EOSBase)/OutputDataBackground_v17_10HF/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData Nominal`

PrepareToRunRandomMCGenBackground:
	bash PrepareInputRandomBackground.sh \
		$(CERNBOX)/OutputMCGen_v18_PFmuon_mZ/ LogMCGenbkg_v18_230127_mZ/ $(CERNBOX)/OutputMCGenbkg_v18_230127_mZ/ $(PbPbBackgroundMC)/ 37 \
		`./Expand Setting.dh PbPbBackgroundGenMC Nominal`

PrepareToRunRandomMCGenBackgroundUEUp25:
	bash PrepareInputRandomBackground.sh \
		$(CERNBOX)/OutputMCGen_v18_PFmuon_mZ/ LogMCGenbkgUEUp25_v18_230127_mZ/ $(CERNBOX)/OutputMCGenbkgUEUp25_v18_230127_mZ/ $(PbPbBackgroundMC)/ 37 \
		`./Expand Setting.dh PbPbBackgroundGenMC UEUp25`

PrepareToRunRandomMCGenBackgroundUEDown25:
	bash PrepareInputRandomBackground.sh \
		$(CERNBOX)/OutputMCGen_v18_PFmuon_mZ/ LogMCGenbkgUEDown25_v18_230127_mZ/ $(CERNBOX)/OutputMCGenbkgUEDown25_v18_230127_mZ/ $(PbPbBackgroundMC)/ 37 \
		`./Expand Setting.dh PbPbBackgroundGenMC UEDown25`

#PrepareToRunRandomPJMCGenBackground:
#	bash PrepareInputRandomBackground.sh \
#		$(EOSBase)/OutputMCGen_v17_PFmuon/ LogMCGenbkg_v17d_PJov1/ $(EOSBase)/OutputMCGenbkg_v17d_PJov1/ $(PbPbBackgroundPJMC)/ 37 \
#		`./Expand Setting.dh PbPbBackgroundGenMC Nominal`

PrepareToRunRandomMCRecGenBackground:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCRecGenbkg_v17d_wVZ/ $(EOSBase)/OutputMCRecGenbkg_v17d_wVZ/ $(PbPbBackgroundMC)/ 37 \
		`./Expand Setting.dh PbPbBackgroundGenMC Nominal`

PrepareToRunRandomMCGenBackgroundCent10:
	bash PrepareInputRandomBackground.sh \
		$(CERNBOX)/OutputMCGen_v18_PFmuon/ LogMCGenbkg_v18_230127_cent10_ov1/ $(CERNBOX)/OutputMCGenbkg_v18_230127_cent10_ov1/ $(PbPbBackgroundMC)/ 37 \
		`./Expand Setting.dh PbPbBackgroundGenMCCent10 Nominal`

PrepareToRunRandomMCBackgroundUEUp25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v18_PFmuon_mZ/ LogMCBackgroundUEUp25_v18_PFmuon_mZ_618/ $(EOSBase)/OutputMCBackgroundUEUp25_v18_PFmuon_mZ_618/ $(PbPbBackgroundMC)/ 37 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp25`

PrepareToRunRandomDataBackgroundUEUp25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataBackgroundUEUp25_v17_PFmuon/ $(EOSBase)/OutputDataBackgroundUEUp25_v17_PFmuon/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEUp25`

PrepareToRunRandomMCBackgroundUEDown25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v18_PFmuon_mZ/ LogMCBackgroundUEDown25_v18_PFmuon_mZ_618/ $(EOSBase)/OutputMCBackgroundUEDown25_v18_PFmuon_mZ_618/ $(PbPbBackgroundMC)/ 37 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown25`

PrepareToRunRandomDataBackgroundUEDown25:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataBackgroundUEDown25_v17_PFmuon/ $(EOSBase)/OutputDataBackgroundUEDown25_v17_PFmuon/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEDown25`

PrepareToRunRandomMCBackgroundUEUp30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEUp30_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEUp30_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEUp30`

PrepareToRunRandomDataBackgroundUEUp30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataBackgroundUEUp30_v17_PFmuon/ $(EOSBase)/OutputDataBackgroundUEUp30_v17_PFmuon/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEUp30`

PrepareToRunRandomMCBackgroundUEDown30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCBackgroundUEDown30_v17_PFmuon/ $(EOSBase)/OutputMCBackgroundUEDown30_v17_PFmuon/ $(PbPbBackgroundMC)/ 20 \
		`./Expand Setting.dh PbPbBackgroundMC UEDown30`

PrepareToRunRandomDataBackgroundUEDown30:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataBackgroundUEDown30_v17_PFmuon/ $(EOSBase)/OutputDataBackgroundUEDown30_v17_PFmuon/ $(PbPbBackgroundData)/ 200 \
		`./Expand Setting.dh PbPbBackgroundData UEDown30`

PrepareToRunRandomMCSigBkg:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCSigBkg_v17d_PFmuon_350_10HF_ov20/ $(EOSBase)/OutputMCSigBkg_v17d_PFmuon_350_10HF_ov20/ $(PbPbSignalMC)/ 350 \
		`./Expand Setting.dh PbPbSignalMC Nominal`

PrepareToRunRandomDataSigBkg:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputData_v17_PFmuon/ LogDataSigBkg_v17d_PFmuon_10HF/ $(EOSBase)/OutputDataSigBkg_v17d_PFmuon_10HF/ '$(PbPbSignalSingleMuon)/*/' 200 \
		`./Expand Setting.dh PbPbSignalData Nominal`

PrepareToRunRandomMCGenSigBkg:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMCGen_v17_PFmuon/ LogMCGenSigBkg_v17d_PFmuon_10HF/ $(EOSBase)/OutputMCGenSigBkg_v17d_PFmuon_10HF/ $(PbPbSignalMC)/ 50 \
		`./Expand Setting.dh PbPbSignalGenMC Nominal`

PrepareToRunRandomPPMCSigBkg:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputPPMC_v17_PFmuon/ LogPPMCSigBkg_v17d_PFmuon_143_10HF/ $(EOSBase)/OutputPPMCSigBkg_v17d_PFmuon_143_10HF/ $(PPSignalMC)/ 143 \
		`./Expand Setting.dh PPSignalMC Nominal`

PrepareToRunRandomPPDataSigBkg:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputPPData_v17_PFmuon/ LogPPDataSigBkg_v17d_PFmuon_10HF/ $(EOSBase)/OutputPPDataSigBkg_v17d_PFmuon_10HF/ '$(PPSignalData)/*/' 200 \
		`./Expand Setting.dh PPSignalData Nominal`

PrepareToRunRandomMCSigBkgCent10:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputMC_v17_PFmuon/ LogMCSigBkg_v17d_Cent10_350_10HF_ov20/ $(EOSBase)/OutputMCSigBkg_v17d_Cent10_350_10HF_ov20/ $(PbPbSignalMC)/ 350 \
		`./Expand Setting.dh PbPbSignalMCCent10 Nominal`

PrepareToRunRandomPPMCSigBkgCent10:
	bash PrepareInputRandomBackground.sh \
		$(EOSBase)/OutputPPMC_v17_PFmuon/ LogPPMCSigBkg_v17d_Cent10_143/ $(EOSBase)/OutputPPMCSigBkg_v17d_Cent10_143/ $(PPSignalMC)/ 143 \
		`./Expand Setting.dh PPSignalMCCent10 Nominal`
