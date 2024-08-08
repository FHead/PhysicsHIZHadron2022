
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

BackgroundMC="   --DoBackground true --HFShift 742.192  --Tolerance 135.772 --ToleranceFraction 0.001 --Oversample 1 --HFCeiling 134000" # --MaximumCentrality 10
#BackgroundMC="   --DoBackground true --HFShift 682  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 1 --HFCeiling 134000"
BackgroundGenMC="--DoBackground true --HFShift 816.7 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 1 --HFCeiling 156000 --VZTolerance 2"
BackgroundData=" --DoBackground true --HFShift 660  --Tolerance 150.0   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"

BackgroundMCUEUp25="     --DoBackground true --HFShift 634.1   --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEUp25="  --DoBackground true --HFShift 837.1  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 1 --HFCeiling 156000 --VZTolerance 2"
BackgroundDataUEUp25="   --DoBackground true --HFShift 676.5 --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"
BackgroundMCUEDown25="   --DoBackground true --HFShift 603.2   --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEDown25="--DoBackground true --HFShift 796.3  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 1 --HFCeiling 156000 --VZTolerance 2"
BackgroundDataUEDown25=" --DoBackground true --HFShift 643.5 --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"

BackgroundMCUEUp30="     --DoBackground true --HFShift 702.5  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEUp30="  --DoBackground true --HFShift 1115.5 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEUp30="   --DoBackground true --HFShift 680    --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"
BackgroundMCUEDown30="   --DoBackground true --HFShift 661.5  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEDown30="--DoBackground true --HFShift 1050.5 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEDown30=" --DoBackground true --HFShift 640.2  --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"

BackgroundMCUEUp50="     --DoBackground true --HFShift 716.1  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEUp50="  --DoBackground true --HFShift 1137.2 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEUp50="   --DoBackground true --HFShift 693    --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"
BackgroundMCUEDown50="   --DoBackground true --HFShift 647.9  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEDown50="--DoBackground true --HFShift 1028.9 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEDown50=" --DoBackground true --HFShift 627  --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"

BackgroundMCUEUp100="     --DoBackground true --HFShift 750.2  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEUp100="  --DoBackground true --HFShift 1191.3 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEUp100="   --DoBackground true --HFShift 726    --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"
BackgroundMCUEDown100="   --DoBackground true --HFShift 613.8  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEDown100="--DoBackground true --HFShift 974.7 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEDown100=" --DoBackground true --HFShift 594  --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"

BackgroundMCUEUp200="     --DoBackground true --HFShift 818.4  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEUp200="  --DoBackground true --HFShift 1299.6 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEUp200="   --DoBackground true --HFShift 792    --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"
BackgroundMCUEDown200="   --DoBackground true --HFShift 545.6  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEDown200="--DoBackground true --HFShift 866.4 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEDown200=" --DoBackground true --HFShift 528  --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"

BackgroundMCUEUp500="     --DoBackground true --HFShift 1023  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEUp500="  --DoBackground true --HFShift 1624.5 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEUp500="   --DoBackground true --HFShift 990    --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"
BackgroundMCUEDown500="   --DoBackground true --HFShift 341  --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEDown500="--DoBackground true --HFShift 541.5 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEDown500=" --DoBackground true --HFShift 330  --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"

BackgroundMCUEUp1000="     --DoBackground true --HFShift 1364 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEUp1000="  --DoBackground true --HFShift 2166 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEUp1000="   --DoBackground true --HFShift 1320 --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"
BackgroundMCUEDown1000="     --DoBackground true --HFShift 0 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
BackgroundGenMCUEDown1000="  --DoBackground true --HFShift 0 --Tolerance 187.5 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
BackgroundDataUEDown1000="   --DoBackground true --HFShift 0 --Tolerance 150   --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"

PPSigBkgMC="   --DoBackground true --CheckForBackgroundZ true --HFShift 0 --Tolerance 1875 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 134000"
PPSigBkgGenMC="--DoBackground true --CheckForBackgroundZ true --HFShift 0 --Tolerance 1875 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
PPSigBkgData=" --DoBackground true --CheckForBackgroundZ true --HFShift 0 --Tolerance 1500 --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"

SigBkgMC="   --DoBackground true --CheckForBackgroundZ true --HFShift 0 --Tolerance 1875 --ToleranceFraction 0.001 --Oversample 5 --HFCeiling 134000"
SigBkgGenMC="--DoBackground true --CheckForBackgroundZ true --HFShift 0 --Tolerance 1875 --ToleranceFraction 0.001 --Oversample 10 --HFCeiling 156000 --VZTolerance 10000"
SigBkgData=" --DoBackground true --CheckForBackgroundZ true --HFShift 0 --Tolerance 1500 --ToleranceFraction 0.001 --Oversample 25 --HFCeiling  70000"

PPSigBkgMCCent10=" --DoBackground true --CheckForBackgroundZ true --HFShift 0  --Tolerance 10000000 --ToleranceFraction 0.001 --VZTolerance 10000000 --Oversample 10 --HFCeiling 134000 --MaximumCentrality 10"
SigBkgMCCent10="   --DoBackground true --CheckForBackgroundZ true --HFShift 0  --Tolerance 1875 --ToleranceFraction 0.001 --VZTolerance 2 --Oversample 20 --HFCeiling 134000 --MaximumCentrality 10"

BackgroundGenMCCent10="--DoBackground true --HFShift 816.7 --Tolerance 10000000 --ToleranceFraction 0.001 --Oversample 1 --HFCeiling 156000 --VZTolerance 10000000 --MaximumCentrality 10"
BackgroundMCCent10="--DoBackground true --HFShift 742.192 --Tolerance 10000000 --ToleranceFraction 0.001 --Oversample 1 --HFCeiling 134000 --VZTolerance 10000000 --MaximumCentrality 10"

DHSet Setting.dh PPSignalMCCent10    Nominal string "$Common $MC    --IsPP true  $AODPF     $PPJetMC      $PbPbRecoTrack  $PPSigBkgMCCent10"
DHSet Setting.dh PbPbSignalMCCent10  Nominal string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $SigBkgMCCent10"
DHSet Setting.dh PbPbBackgroundMCCent10 Nominal string "$Common $MC --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCCent10"
DHSet Setting.dh PbPbBackgroundGenMCCent10 Nominal string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack $BackgroundGenMCCent10"
DHSet Setting.dh PPSignalMC          Nominal string "$Common $MC    --IsPP true  $AODPF     $PPJetMC      $PbPbRecoTrack  $PPSigBkgMC"
DHSet Setting.dh PPSignalGenMC       Nominal string "$Common $MCGen --IsPP true  $AODPF     $PPJetMC      $GenTrack       $PPSigBkgGenMC"
DHSet Setting.dh PPSignalData        Nominal string "$Common $Data  --IsPP true  $AODPF     $PbPbJetData  $PbPbRecoTrack  $PPSigBkgData"
DHSet Setting.dh PbPbSignalMC        Nominal string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $SigBkgMC"
DHSet Setting.dh PbPbSignalGenMC     Nominal string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $SigBkgGenMC"
DHSet Setting.dh PbPbSignalData      Nominal string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $SigBkgData"
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
DHSet Setting.dh PbPbBackgroundMC    UEUp50   string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEUp50"
DHSet Setting.dh PbPbBackgroundGenMC UEUp50   string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEUp50"
DHSet Setting.dh PbPbBackgroundData  UEUp50   string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEUp50"
DHSet Setting.dh PbPbBackgroundMC    UEDown50 string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEDown50"
DHSet Setting.dh PbPbBackgroundGenMC UEDown50 string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEDown50"
DHSet Setting.dh PbPbBackgroundData  UEDown50 string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEDown50"
DHSet Setting.dh PbPbBackgroundMC    UEUp100   string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEUp100"
DHSet Setting.dh PbPbBackgroundGenMC UEUp100   string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEUp100"
DHSet Setting.dh PbPbBackgroundData  UEUp100   string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEUp100"
DHSet Setting.dh PbPbBackgroundMC    UEDown100 string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEDown100"
DHSet Setting.dh PbPbBackgroundGenMC UEDown100 string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEDown100"
DHSet Setting.dh PbPbBackgroundData  UEDown100 string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEDown100"
DHSet Setting.dh PbPbBackgroundMC    UEUp200   string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEUp200"
DHSet Setting.dh PbPbBackgroundGenMC UEUp200   string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEUp200"
DHSet Setting.dh PbPbBackgroundData  UEUp200   string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEUp200"
DHSet Setting.dh PbPbBackgroundMC    UEDown200 string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEDown200"
DHSet Setting.dh PbPbBackgroundGenMC UEDown200 string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEDown200"
DHSet Setting.dh PbPbBackgroundData  UEDown200 string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEDown200"
DHSet Setting.dh PbPbBackgroundMC    UEUp500   string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEUp500"
DHSet Setting.dh PbPbBackgroundGenMC UEUp500   string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEUp500"
DHSet Setting.dh PbPbBackgroundData  UEUp500   string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEUp500"
DHSet Setting.dh PbPbBackgroundMC    UEDown500 string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEDown500"
DHSet Setting.dh PbPbBackgroundGenMC UEDown500 string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEDown500"
DHSet Setting.dh PbPbBackgroundData  UEDown500 string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEDown500"
DHSet Setting.dh PbPbBackgroundMC    UEUp1000   string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEUp1000"
DHSet Setting.dh PbPbBackgroundGenMC UEUp1000   string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEUp1000"
DHSet Setting.dh PbPbBackgroundData  UEUp1000   string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEUp1000"
DHSet Setting.dh PbPbBackgroundMC    UEDown1000 string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack  $BackgroundMCUEDown1000"
DHSet Setting.dh PbPbBackgroundGenMC UEDown1000 string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack       $BackgroundGenMCUEDown1000"
DHSet Setting.dh PbPbBackgroundData  UEDown1000 string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack  $BackgroundDataUEDown1000"

# Finally set sample locations

#DHSet Setting.dh Sample PbPbBackgroundData string /eos/cms/store/group/phys_heavyions/mitaylor/PhotonJet/HIMinimumBias4/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias4/20230203PbPbMB/230203_165233/0000/
DHSet Setting.dh Sample PbPbBackgroundData string /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/HIMinimumBias4/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HIMinimumBias4/20230130PbPbMB/230130_223511/
DHSet Setting.dh Sample PbPbSignalData string /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/HISingleMuon/HIRun2018A-PbPb18_MiniAODv1-v1/MINIAOD/HISingleMuon/20231024_ZHadronSingleMuonWithMuTree/231024_154233/
DHSet Setting.dh Sample PbPbSignalMC string /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/HINPbPbSpring21MiniAOD-mva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/20231020_ZHadronMCDY/231020_151547/0000/
DHSet Setting.dh Sample PbPbBackgroundMC string /eos/cms/store/group/phys_heavyions/chenyi/Samples/store/user/mitaylor/PhotonJet/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20230127PbPbMCMB/230127_211118/
#DHSet Setting.dh Sample PbPbBackgroundMC string /eos/cms/store/group/phys_heavyions/chenyi/PbPb2018/Forest/MinBias_Hydjet_Drum5F_2018_5p02TeV/HINPbPbSpring21MiniAOD-NoPUmva98_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM/MinBias_Hydjet_Drum5F_2018_5p02TeV/20221017_ZHadronInitialRunMCMB/221017_113057/0000/
DHSet Setting.dh Sample PPSignalMC string /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/RunIIpp5Spring18DR-94X_mc2017_realistic_forppRef5TeV-v2/AODSIM/DYJetsToLL_MLL-50_TuneCP5_5020GeV-amcatnloFXFX-pythia8/20231020_ZHadronMLLWithMuTreePP/231020_152224/0000/
DHSet Setting.dh Sample PPSignalData string /eos/cms/store/group/phys_heavyions/chenyi/pp2017/Forest/SingleMuon/Run2017G-17Nov2017-v1/AOD/SingleMuon/20231024_ZHadronSingleMuonWithMuTreePP/231024_154426/

