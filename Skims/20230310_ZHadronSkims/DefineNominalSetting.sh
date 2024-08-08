
Common="--MinZPT 5 --MinTrackPT 0.5 --DoSumET false --DoExtraAxes true"

MC="--DoGenLevel true --DoGenCorrelation false --IsData false"
MCGen="--DoGenLevel true --DoGenCorrelation true --GenCorrelationCharged true --IsData false"
Data="--DoGenLevel false --IsData true"

AODPF="--PFTree \"pfcandAnalyzer/pfTree\""
MiniAODPF="--PFTree \"particleFlowAnalyser/pftree\""

PPJECMC=Spring18_ppRef5TeV_RAAV3_MC
PPJECData=Spring18_ppRef5TeV_RAAV3_DATA
PbPbJECMC=Autumn18_HI_RAAV3_MC
PbPbJECData=Autumn18_HI_RAAV3_DATA

JECBase=${ProjectBase}/CommonCode/text/JEC/

PPJetMC="    --DoJet true --Jet \"ak3PFJetAnlayzer/t\"   --JEC ${JECBase}/$PPJECMC/${PPJECMC}_L2Relative_AK3PF.txt"
PPJetData="  --DoJet true --Jet \"ak3PFJetAnlayzer/t\"   --JEC ${JECBase}/$PPJECData/${PPJECData}_L2Relative_AK3PF.txt,$JECBase/$PPJECData/${PPJECData}_L2L3Residual_AK3PF.txt"
PbPbJetMC="  --DoJet true --Jet \"akCs3PFJetAnlayzer/t\" --JEC ${JECBase}/$PbPbJECMC/${PbPbJECMC}_L2Relative_AK3PF.txt"
PbPbJetData="--DoJet true --Jet \"akCs3PFJetAnlayzer/t\" --JEC ${JECBase}/$PbPbJECData/${PbPbJECData}_L2Relative_AK3PF.txt,$JECBase/$PbPbJECData/${PbPbJECData}_L2L3Residual_AK3PF.txt"

TrackResidualPathPbPb="${ProjectBase}/CommonCode/root/20230522_TrackResidualCorrection_V9_0_20.root,${ProjectBase}/CommonCode/root/20230522_TrackResidualCorrection_V9_20_60.root,${ProjectBase}/CommonCode/root/20230522_TrackResidualCorrection_V9_60_100.root,${ProjectBase}/CommonCode/root/20230522_TrackResidualCorrection_V9_100_200.root"
TrackResidualPathPP="${ProjectBase}/CommonCode/root/20230531_TrackResidualCorrection_V12_pp.root"

GenTrack="--DoTrackEfficiency false --TrackEfficiencyPath ${ProjectBase}/CommonCode/root/ --DoTrackResidual false"
PPRecoTrack="--DoTrackEfficiency true --TrackEfficiencyPath ${ProjectBase}/CommonCode/root/ --DoTrackResidual true --TrackResidualPath $TrackResidualPathPP"
PbPbRecoTrack="--DoTrackEfficiency true --TrackEfficiencyPath ${ProjectBase}/CommonCode/root/ --DoTrackResidual true --TrackResidualPath $TrackResidualPathPbPb"

BackgroundMC="   --DoBackground true --HFShift 682  --Tolerance 90 --ToleranceFraction 0.005 --Oversample 10 --HFCeiling 134000"
BackgroundGenMC="--DoBackground true --HFShift 1083 --Tolerance 90 --ToleranceFraction 0.005 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundData=" --DoBackground true --HFShift 660  --Tolerance 75 --ToleranceFraction 0.005 --Oversample 25 --HFCeiling  70000"

BackgroundMCUEUp25="     --DoBackground true --HFShift 699   --Tolerance 90 --ToleranceFraction 0.05 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEUp25="  --DoBackground true --HFShift 1110  --Tolerance 10 --ToleranceFraction 0.01 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEUp25="   --DoBackground true --HFShift 676.5 --Tolerance 0  --ToleranceFraction 0.01 --Oversample 10 --HFCeiling  70000"
BackgroundMCUEDown25="   --DoBackground true --HFShift 665   --Tolerance 20 --ToleranceFraction 0.05 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEDown25="--DoBackground true --HFShift 1056  --Tolerance 10 --ToleranceFraction 0.01 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEDown25=" --DoBackground true --HFShift 643.5 --Tolerance 0  --ToleranceFraction 0.01 --Oversample 10 --HFCeiling  70000"

BackgroundMCUEUp30="     --DoBackground true --HFShift 702.5  --Tolerance 20 --ToleranceFraction 0.05 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEUp30="  --DoBackground true --HFShift 1115.5 --Tolerance 10 --ToleranceFraction 0.01 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEUp30="   --DoBackground true --HFShift 680    --Tolerance 0  --ToleranceFraction 0.01 --Oversample 10 --HFCeiling  70000"
BackgroundMCUEDown30="   --DoBackground true --HFShift 661.5  --Tolerance 20 --ToleranceFraction 0.05 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEDown30="--DoBackground true --HFShift 1050.5 --Tolerance 10 --ToleranceFraction 0.01 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEDown30=" --DoBackground true --HFShift 640.2  --Tolerance 0  --ToleranceFraction 0.01 --Oversample 10 --HFCeiling  70000"

DHSet Setting.dh PPSignalMC          Nominal string "$Common $MC    --IsPP true  $AODPF     $PPJetMC      $PPRecoTrack"
DHSet Setting.dh PPSignalGenMC       Nominal string "$Common $MCGen --IsPP true  $AODPF     $PPJetMC      $GenTrack"
DHSet Setting.dh PPSignalData        Nominal string "$Common $Data  --IsPP true  $AODPF     $PbPbJetData  $PPRecoTrack"
DHSet Setting.dh PbPbSignalMC        Nominal string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack"
DHSet Setting.dh PbPbSignalGenMC     Nominal string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack"
DHSet Setting.dh PbPbSignalData      Nominal string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack"
DHSet Setting.dh PbPbBackgroundMC    Nominal string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMC"
DHSet Setting.dh PbPbBackgroundGenMC Nominal string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMC"
DHSet Setting.dh PbPbBackgroundData  Nominal string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundData"
DHSet Setting.dh PbPbBackgroundMC    UEUp25   string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEUp25"
DHSet Setting.dh PbPbBackgroundGenMC UEUp25   string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEUp25"
DHSet Setting.dh PbPbBackgroundData  UEUp25   string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEUp25"
DHSet Setting.dh PbPbBackgroundMC    UEDown25 string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEDown25"
DHSet Setting.dh PbPbBackgroundGenMC UEDown25 string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEDown25"
DHSet Setting.dh PbPbBackgroundData  UEDown25 string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEDown25"
DHSet Setting.dh PbPbBackgroundMC    UEUp30   string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEUp30"
DHSet Setting.dh PbPbBackgroundGenMC UEUp30   string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEUp30"
DHSet Setting.dh PbPbBackgroundData  UEUp30   string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEUp30"
DHSet Setting.dh PbPbBackgroundMC    UEDown30 string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEDown30"
DHSet Setting.dh PbPbBackgroundGenMC UEDown30 string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEDown30"
DHSet Setting.dh PbPbBackgroundData  UEDown30 string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEDown30"

LooseTrack="--DoAlternateTrackSelection true --AlternateTrackSelection 1"
DHSet Setting.dh PbPbSignalData      Loose string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack $LooseTrack"
DHSet Setting.dh PbPbSignalMC        Loose string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack $LooseTrack"

TightTrack="--DoAlternateTrackSelection true --AlternateTrackSelection 2"
DHSet Setting.dh PbPbSignalData      Tight string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack $TightTrack"
DHSet Setting.dh PbPbSignalMC        Tight string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack $TightTrack"

# Finally set sample locations

# DHSet Setting.dh Sample PbPbBackgroundData string /eos/cms/store/group/phys_heavyions/mitaylor/PhotonJet/HIMinimumBias4/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias4/20230203PbPbMB/230203_165233/0000/
DHSet Setting.dh Sample PbPbBackgroundData string /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/HIMinimumBias4/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias4/20230130PbPbMB/230130_223511/
DHSet Setting.dh Sample PbPbSignalData string /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HISingleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HISingleMuon/20231024_ZHadronSingleMuonWithMuTree/231024_154233/
DHSet Setting.dh Sample PbPbSignalMC string /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20231020_ZHadronMCDY/231020_151547/0000/
DHSet Setting.dh Sample PbPbBackgroundMC string /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118/
DHSet Setting.dh Sample PPSignalMC string /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20231020_ZHadronMLLWithMuTreePP/231020_152224/0000/
DHSet Setting.dh Sample PPSignalData string /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/SingleMuon/Run2017G-17Nov2017-v1/AOD/SingleMuon/20231024_ZHadronSingleMuonWithMuTreePP/231024_154426/

