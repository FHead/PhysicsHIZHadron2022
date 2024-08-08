OutputBase = '/store/group/phys_heavyions/chenyi/pp2017/Forest'
# DatasetName = '/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/HINPbPbSpring21MiniAOD-FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/MINIAODSIM'
# DatasetName = '/HIHardProbes/HIRun2018A-PbPb18_MiniAODv1-v2/MINIAOD'
DatasetName = '/HighEGJet/Run2017G-17Nov2017-v2/AOD'
Tag = '20231020_ZHadronSingleElectronWithMuTree'

from WMCore.Configuration import Configuration
config = Configuration()
config.section_("General")
config.General.requestName = Tag

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'runForestAOD_pp_DATA_94X.py'
config.JobType.allowUndistributedCMSSW = True
config.JobType.maxMemoryMB = 5000
config.JobType.maxJobRuntimeMin = 4800
# config.JobType.inputFiles = ['']

config.section_("Data")
config.Data.inputDataset = DatasetName
config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/global/DBSReader/'
# config.Data.inputDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSReader/'
config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 1
config.Data.publication = False
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
config.Data.outputDatasetTag = Tag
config.Data.outLFNDirBase = OutputBase + DatasetName + '/'
config.Data.ignoreLocality = True
config.Data.allowNonValidInputDataset = True

config.section_("Site")
config.Site.blacklist = ['T2_IT_Pisa']
config.Site.whitelist = ['T2_US_*', 'T2_CH_CERN']
config.Site.storageSite = 'T2_CH_CERN'

