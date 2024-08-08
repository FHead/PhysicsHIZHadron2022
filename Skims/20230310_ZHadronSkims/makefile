PbPbBackgroundData   := $(shell DHQuery Setting.dh Sample PbPbBackgroundData)
PbPbSignalDoubleMuon  = /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HIDoubleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIDoubleMuon/20221101_ZHadronDoubleMuonWithMuTree/221101_212941/
PbPbSignalSingleMuon := $(shell DHQuery Setting.dh Sample PbPbSignalData)
PbPbSignalMC         := $(shell DHQuery Setting.dh Sample PbPbSignalMC)
PbPbBackgroundMC     := $(shell DHQuery Setting.dh Sample PbPbBackgroundMC)
PPSignalMC           := $(shell DHQuery Setting.dh Sample PPSignalMC)
PPSignalData         := $(shell DHQuery Setting.dh Sample PPSignalData)

default: Prepare TestRun

Prepare:
	bash DefineNominalSetting.sh
	chmod u+x Expand
	
Execute: DoZHadronSkim.cpp
	g++ DoZHadronSkim.cpp -I. -I$(ProjectBase)/CommonCode/include \
		-o Execute `root-config --cflags --libs` -std=c++17 \
		$(ProjectBase)/CommonCode/library/Messenger.o \
		# $(FJExtra) $(FJCExtra)

TestRun: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_867.root \
		--Output /tmp/$(USER)/Test.root --Fraction 1 --WithProgressBar true \
		`./Expand Setting.dh PbPbSignalData Nominal`
	
TestRunMC: Execute
	time ./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_144.root,$(PbPbSignalMC)/HiForestMiniAOD_145.root,$(PbPbSignalMC)/HiForestMiniAOD_146.root,$(PbPbSignalMC)/HiForestMiniAOD_147.root,$(PbPbSignalMC)/HiForestMiniAOD_148.root \
		--Output TestMC10.root --Fraction 1 --WithProgressBar true \
		`./Expand Setting.dh PbPbSignalMC Nominal`

TestRunGen: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_114.root \
		--Output /tmp/$(USER)/TestGenMC.root --Fraction 0.1 --WithProgressBar true \
		`./Expand Setting.dh PbPbSignalGenMC Nominal`

TestRunGenPP: Execute
	./Execute --Input `ls $(PPSignalMC)/*root | head -n 2 | tr '\n' ','` \
		--Output /tmp/$(USER)/TestGenPP.root --Fraction 1 --WithProgressBar true \
		`./Expand Setting.dh PPSignalGenMC Nominal`

TestRunBackground: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		--Background $(PbPbBackgroundData)/HiForestMiniAOD_118.root,$(PbPbBackgroundData)/HiForestMiniAOD_123.root,$(PbPbBackgroundData)/HiForestMiniAOD_127.root,$(PbPbBackgroundData)/HiForestMiniAOD_138.root,$(PbPbBackgroundData)/HiForestMiniAOD_148.root,$(PbPbBackgroundData)/HiForestMiniAOD_16.root,$(PbPbBackgroundData)/HiForestMiniAOD_17.root,$(PbPbBackgroundData)/HiForestMiniAOD_184.root,$(PbPbBackgroundData)/HiForestMiniAOD_18.root,$(PbPbBackgroundData)/HiForestMiniAOD_194.root \
		`./Expand Setting.dh PbPbSignalData Nominal`

TestRunPP: Execute
	./Execute --Input `ls $(PPSignalMC)/*root | head -n 2 | tr '\n' ','` \
		--Output /tmp/$(USER)/TestPP.root --Fraction 0.1 --WithProgressBar true \
		`./Expand Setting.dh PPSignalMC Nominal`

TestRunPPData: Execute
	./Execute --Input $(PPSignalData)/0000/HiForestAOD_12.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 --WithProgressBar true \
		`./Expand Setting.dh PPSignalData Nominal`

TestRunBackgroundSimple: Execute
	./Execute --Input $(PbPbSignalSingleMuon)/0000/HiForestMiniAOD_14.root \
		--Output /tmp/$(USER)/Test.root --Fraction 1 \
		--Background $(PbPbBackgroundData)/HiForestMiniAOD_118.root \
		`./Expand Setting.dh PbPbSignalData Nominal`

TestRunMCBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root \
		`./Expand Setting.dh PbPbBackgroundMC Nominal`

TestRunMCGenBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root \
		`./Expand Setting.dh PbPbSignalMC Nominal`

#BackgroundCount = 37
#BackgroundFiles = `ls $(PbPbBackgroundMC)/* | shuf | head -n$(BackgroundCount) | tr '\n' ',' | sed "s/,$//"`

#37
BackgroundFiles = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_36.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_21.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_24.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_32.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_5.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_8.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_27.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_20.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_12.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_17.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_2.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_34.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_4.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_22.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_6.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_15.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_13.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_11.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_30.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_26.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_25.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_7.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_28.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_3.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_29.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_31.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_1.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_37.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_9.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_16.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_33.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_10.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_35.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_23.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_19.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_18.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_14.root

#12
#BackgroundFiles = /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_36.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_21.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_24.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_32.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_5.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_8.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_27.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_20.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_12.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_17.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_2.root,/eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118//HiForestMiniAOD_34.root,

TestRunRandomMCBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		--Background $(BackgroundFiles) \
		`./Expand Setting.dh PbPbBackgroundMC Nominal`

TestRunRandomMCGenBackground: Execute
	./Execute --Input $(PbPbSignalMC)/HiForestMiniAOD_10.root \
		--Output /tmp/$(USER)/Test.root --Fraction 0.1 \
		--Background $(BackgroundFiles) \
		`./Expand Setting.dh PbPbSignalMC Nominal`

# EOSBase = /eos/cms/store/group/phys_heavyions/chenyi/PhysicsWorkspace/HIZHadron2022/Skims/20230310_ZHadronSkims
EOSBase = /eos/cms/store/group/phys_heavyions/pchou
# EOSBase = /eos/home-p/pchou
# AFSBase = /afs/cern.ch/user/p/pchou
CERNBOX = /eos/home-p/pchou

PrepareToRun:
	bash PrepareInput.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		5 LogData_v18_PFmuon_mZ/ $(EOSBase)/OutputData_v18_PFmuon_mZ/ \
		--Fraction 1 `./Expand Setting.dh PbPbSignalData Nominal`

PrepareToRunMC:
	bash PrepareInput.sh \
		$(PbPbSignalMC)/ \
		5 LogMC_v18_PFmuon_mZ/ $(CERNBOX)/OutputMC_v18_PFmuon_mZ/ \
		--Fraction 1 `./Expand Setting.dh PbPbSignalMC Nominal`

PrepareToRunLoose:
	bash PrepareInput.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		5 LogDataLoose_v17_PFmuon/ $(EOSBase)/OutputDataLoose_v17_PFmuon/ \
		--Fraction 1 `./Expand Setting.dh PbPbSignalData Loose`

PrepareToRunMCLoose:
	bash PrepareInput.sh \
		$(PbPbSignalMC)/ \
		5 LogMCLoose_v17_PFmuon/ $(EOSBase)/OutputMCLoose_v17_PFmuon/ \
		--Fraction 1 `./Expand Setting.dh PbPbSignalMC Loose`

PrepareToRunTight:
	bash PrepareInput.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		5 LogDataTight_v17_PFmuon/ $(EOSBase)/OutputDataTight_v17_PFmuon/ \
		--Fraction 1 `./Expand Setting.dh PbPbSignalData Tight`

PrepareToRunMCTight:
	bash PrepareInput.sh \
		$(PbPbSignalMC)/ \
		5 LogMCTight_v17_PFmuon/ $(EOSBase)/OutputMCTight_v17_PFmuon/ \
		--Fraction 1 `./Expand Setting.dh PbPbSignalMC Tight`

PrepareToRunGenMC:
	bash PrepareInput.sh \
		$(PbPbSignalMC)/ \
		5 LogGenMC_v18_PFmuon_mZ/ $(CERNBOX)/OutputMCGen_v18_PFmuon_mZ/ \
 		--Fraction 1 `./Expand Setting.dh PbPbSignalGenMC Nominal`

PrepareToRunPP:
	bash PrepareInput.sh \
		$(PPSignalMC)/ \
		10 LogPP_v18_PFmuon_mZ/ $(CERNBOX)/OutputPPMC_v18_PFmuon_mZ/ \
 		--Fraction 1 `./Expand Setting.dh PPSignalMC Nominal`

PrepareToRunGenPP:
	bash PrepareInput.sh \
		$(PPSignalMC)/ \
		10 LogGenPP_v18_PFmuon_mZ/ $(CERNBOX)/OutputPPMCGen_v18_PFmuon_mZ/ \
 		--Fraction 1 `./Expand Setting.dh PPSignalGenMC Nominal`

PrepareToRunPPData:
	bash PrepareInput.sh \
		'$(PPSignalData)/*/' \
		10 LogPPData_v18_PFmuon_mZ/ $(CERNBOX)/OutputPPData_v18_PFmuon_mZ/ \
 		--Fraction 1 `./Expand Setting.dh PPSignalData Nominal`

PrepareToRunBackground:
	bash PrepareInput.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		10 LogDatabkg_v15/ $(EOSBase)/OutputDatabkg_v15/ \
		--Background /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_10.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_13.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_17.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_20.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_22.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_34.root,/eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/HiForestMiniAOD_37.root \
		`./Expand Setting.dh PbPbBackgroundMC Nominal`

PrepareToRunRandomBackground:
	bash PrepareInputRandomBackground.sh \
		'$(PbPbSignalSingleMuon)/*/' \
		10 LogDataBackground_v15/ $(EOSBase)/OutputDataBackground_v15/ \
		$(PbPbBackgroundData)/ 100 \
		`./Expand Setting.dh PbPbBackgroundData Nominal`

PrepareToRunMCBackground:
	bash PrepareInput.sh \
		$(PbPbSignalMC) \
		1 LogMCBackground_v15/ $(EOSBase)/OutputMCBackground_v15/ \
		--Background $(PbPbBackgroundMC)/HiForestMiniAOD_10.root,$(PbPbBackgroundMC)/HiForestMiniAOD_11.root,$(PbPbBackgroundMC)/HiForestMiniAOD_12.root,$(PbPbBackgroundMC)/HiForestMiniAOD_13.root,$(PbPbBackgroundMC)/HiForestMiniAOD_14.root,$(PbPbBackgroundMC)/HiForestMiniAOD_15.root,$(PbPbBackgroundMC)/HiForestMiniAOD_16.root,$(PbPbBackgroundMC)/HiForestMiniAOD_17.root,$(PbPbBackgroundMC)/HiForestMiniAOD_18.root,$(PbPbBackgroundMC)/HiForestMiniAOD_19.root,$(PbPbBackgroundMC)/HiForestMiniAOD_1.root,$(PbPbBackgroundMC)/HiForestMiniAOD_20.root \
		`./Expand Setting.dh PbPbBackgroundMC Nominal`

PrepareToRunRandomMCBackground:
	bash PrepareInputRandomBackground.sh \
		$(PbPbSignalMC) \
		1 LogMCBackground_v15/ $(EOSBase)/OutputMCBackground_v15_batch2/ \
		$(PbPbBackgroundMC)/ 15 \
		`./Expand Setting.dh PbPbBackgroundMC Nominal`

PrepareToRunRandomMCGenBackground:
	bash PrepareInputRandomBackground.sh \
		$(PbPbSignalMC) \
		10 LogMCGenbkg_v15/ $(EOSBase)/OutputMCbkgGen_v15/ \
		$(PbPbBackgroundMC)/ 5 \
 		`./Expand Setting.dh PbPbBackgroundGenMC Nominal`

