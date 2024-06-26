### HiForest Configuration
# Input: miniAOD
# Type: mc

import FWCore.ParameterSet.Config as cms
from Configuration.Eras.Era_Run2_2018_pp_on_AA_cff import Run2_2018_pp_on_AA
from Configuration.ProcessModifiers.run2_miniAOD_pp_on_AA_103X_cff import run2_miniAOD_pp_on_AA_103X
process = cms.Process('HiForest', Run2_2018_pp_on_AA,run2_miniAOD_pp_on_AA_103X)

###############################################################################

# HiForest info
process.load("HeavyIonsAnalysis.EventAnalysis.HiForestInfo_cfi")
process.HiForestInfo.info = cms.vstring("HiForest, miniAOD, 112X, mc")

# import subprocess, os
# version = subprocess.check_output(
#     ['git', '-C', os.path.expandvars('$CMSSW_BASE/src'), 'describe', '--tags'])
# if version == '':
#     version = 'no git info'
# process.HiForestInfo.HiForestVersion = cms.string(version)

###############################################################################

# input files
process.source = cms.Source("PoolSource",
    duplicateCheckMode = cms.untracked.string("noDuplicateCheck"),
    fileNames = cms.untracked.vstring(
        # 'file:/afs/cern.ch/work/m/mnguyen/public/integration/CMSSW_11_2_4_patch4/src/step3_inMINIAODSIM.root'
        # '/store/himc/HINPbPbSpring21MiniAOD/DiJet_pThat-15_TuneCP5_HydjetDrumMB_5p02TeV_Pythia8/MINIAODSIM/FixL1CaloGT_112X_upgrade2018_realistic_HI_v9-v1/250000/9d0206aa-0edd-4e1d-a08c-49d2ce491bc6.root'
        '/store/himc/HINPbPbSpring21MiniAOD/DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8/MINIAODSIM/mva98_112X_upgrade2018_realistic_HI_v9-v1/240000/adc0ba32-0aa3-4cc7-ab74-df02789a72d7.root'
        # '__INPUT__'
    ),
)

# number of events to process, set to -1 to process all events
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
    )

###############################################################################

# load Global Tag, geometry, etc.
process.load('Configuration.Geometry.GeometryDB_cff')
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')


from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2018_realistic_hi', '')
process.HiForestInfo.GlobalTagLabel = process.GlobalTag.globaltag
process.GlobalTag.snapshotTime = cms.string("9999-12-31 23:59:59.000")
process.GlobalTag.toGet.extend([
    cms.PSet(record = cms.string("BTagTrackProbability3DRcd"),
             tag = cms.string("JPcalib_MC103X_2018PbPb_v4"),
             connect = cms.string("frontier://FrontierProd/CMS_CONDITIONS")
         )
])


###############################################################################

# root output
process.TFileService = cms.Service("TFileService",
    fileName = cms.string("HiForestMiniAOD.root"))

# # edm output for debugging purposes
# process.output = cms.OutputModule(
#     "PoolOutputModule",
#     fileName = cms.untracked.string('HiForestEDM.root'),
#     outputCommands = cms.untracked.vstring(
#         'keep *',
#         )
#     )

# process.output_path = cms.EndPath(process.output)

###############################################################################

#############################
# Gen Analyzer
#############################
process.load('HeavyIonsAnalysis.EventAnalysis.HiGenAnalyzer_cfi')
# making cuts looser so that we can actually check dNdEta
process.HiGenParticleAna.ptMin = cms.untracked.double(0.) # default is 5
process.HiGenParticleAna.etaMax = cms.untracked.double(5.) # default is 2.5
process.HiGenParticleAna.stableOnly = cms.untracked.bool(False)

# event analysis
process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.particleFlowAnalyser_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hievtanalyzer_mc_cfi')
#process.load('HeavyIonsAnalysis.EventAnalysis.hltanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.skimanalysis_cfi')
process.load('HeavyIonsAnalysis.EventAnalysis.hltobject_cfi')
#process.load('HeavyIonsAnalysis.EventAnalysis.l1object_cfi')

process.particleFlowAnalyser.ptMin = 0
process.particleFlowAnalyser.absEtaMax = 7

from HeavyIonsAnalysis.EventAnalysis.hltobject_cfi import trigger_list_mc
process.hltobject.triggerNames = trigger_list_mc

# process.load('HeavyIonsAnalysis.EventAnalysis.particleFlowAnalyser_cfi')
################################
# electrons, photons, muons
process.load('HeavyIonsAnalysis.EGMAnalysis.ggHiNtuplizer_cfi')
process.ggHiNtuplizer.doGenParticles = cms.bool(True)
process.load("TrackingTools.TransientTrack.TransientTrackBuilder_cfi")
################################
# jet reco sequence
process.load('HeavyIonsAnalysis.JetAnalysis.akCs4PFJetSequence_pponPbPb_mc_cff')
################################
# tracks
process.load("HeavyIonsAnalysis.TrackAnalysis.TrackAnalyzers_cff")
# muons
process.load("HeavyIonsAnalysis.MuonAnalysis.unpackedMuons_cfi")
process.load("HeavyIonsAnalysis.MuonAnalysis.hltMuTree_cfi")

###############################################################################



###############################################################################
# main forest sequence
process.forest = cms.Path(
    process.HiForestInfo +
    process.hltanalysis +
    process.hltobject +
    process.trackSequencePbPb +
    # process.unpackedTracksAndVertices +
    process.particleFlowAnalyser +
    process.hiEvtAnalyzer +
    process.HiGenParticleAna +
    process.unpackedMuons +
    process.ggHiNtuplizer +
    # process.akCs4PFJetAnalyzer
    process.hltMuTree
    )

#customisation

addRXJets = True

if addRXJets :
    process.akCs4PFJetAnalyzer.jetPtMin = 0

    process.load("HeavyIonsAnalysis.JetAnalysis.extraJets_cff")
    from HeavyIonsAnalysis.JetAnalysis.clusterJetsFromMiniAOD_cff import setupHeavyIonJets
    # setupHeavyIonJets('akCs1PF',  process.extraJetsMC, process, isMC = 1, radius = 0.15, JECTag = 'AK4PF')
    # setupHeavyIonJets('akCs2PF',  process.extraJetsMC, process, isMC = 1, radius = 0.20, JECTag = 'AK4PF')
    # setupHeavyIonJets('akCs3PF',  process.extraJetsMC, process, isMC = 1, radius = 0.30, JECTag = 'AK3PF')
    setupHeavyIonJets('akCs0PF',  process.extraJetsMC, process, isMC = 1, radius = 0.40, JECTag = 'AK4PF')
    # setupHeavyIonJets('akCs5PF',  process.extraJetsMC, process, isMC = 1, radius = 0.50, JECTag = 'AK4PF')
    # setupHeavyIonJets('akCs6PF',  process.extraJetsMC, process, isMC = 1, radius = 0.60, JECTag = 'AK4PF')
    # setupHeavyIonJets('akCs7PF',  process.extraJetsMC, process, isMC = 1, radius = 0.80, JECTag = 'AK4PF')
    # setupHeavyIonJets('akCs8PF',  process.extraJetsMC, process, isMC = 1, radius = 1.00, JECTag = 'AK4PF')
    # setupHeavyIonJets('akCs9PF',  process.extraJetsMC, process, isMC = 1, radius = 1.20, JECTag = 'AK4PF')
    # process.akCs1PFpatJetCorrFactors.levels = ['L2Relative', 'L3Absolute']
    # process.akCs2PFpatJetCorrFactors.levels = ['L2Relative', 'L3Absolute']
    # process.akCs3PFpatJetCorrFactors.levels = ['L2Relative', 'L3Absolute']
    process.akCs0PFpatJetCorrFactors.levels = ['L2Relative', 'L3Absolute']
    # process.akCs5PFpatJetCorrFactors.levels = ['L2Relative', 'L3Absolute']
    # process.akCs6PFpatJetCorrFactors.levels = ['L2Relative', 'L3Absolute']
    # process.akCs7PFpatJetCorrFactors.levels = ['L2Relative', 'L3Absolute']
    # process.akCs8PFpatJetCorrFactors.levels = ['L2Relative', 'L3Absolute']
    # process.akCs9PFpatJetCorrFactors.levels = ['L2Relative', 'L3Absolute']
    # process.akCs1PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs1PFpatJets", genjetTag = "ak1GenJetsNoNu", rParam = 0.15)
    # process.akCs2PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs2PFpatJets", genjetTag = "ak2GenJetsNoNu", rParam = 0.20)
    # process.akCs3PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs3PFpatJets", genjetTag = "ak3GenJetsNoNu", rParam = 0.30)
    print(process.akCs4PFJetAnalyzer.jetTag)
    process.akCs4PFJetAnalyzer.jetTag = cms.InputTag('akCs0PFpatJets')
    print(process.akCs4PFJetAnalyzer.jetTag)
    # process.akCs5PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs5PFpatJets", genjetTag = "ak5GenJetsNoNu", rParam = 0.50)
    # process.akCs6PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs6PFpatJets", genjetTag = "ak6GenJetsNoNu", rParam = 0.60)
    # process.akCs7PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs7PFpatJets", genjetTag = "ak7GenJetsNoNu", rParam = 0.80)
    # process.akCs8PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs8PFpatJets", genjetTag = "ak8GenJetsNoNu", rParam = 1.00)
    # process.akCs9PFJetAnalyzer = process.akCs4PFJetAnalyzer.clone(jetTag = "akCs9PFpatJets", genjetTag = "ak9GenJetsNoNu", rParam = 1.20)

    process.hiPuRhoAnalyzer = cms.EDAnalyzer(
      'HiFJRhoAnalyzer',
      etaMap        = cms.InputTag('hiPuRho','mapEtaEdges','HiForest'),
      rho           = cms.InputTag('hiPuRho','mapToRho'),
      rhom          = cms.InputTag('hiPuRho','mapToRhoM'),
      useModulatedRho = cms.bool(False),
      )

    process.forest += process.extraJetsMC
    # process.forest += process.akCs1PFJetAnalyzer
    # process.forest += process.akCs2PFJetAnalyzer
    # process.forest += process.akCs3PFJetAnalyzer
    process.forest += process.akCs4PFJetAnalyzer
    # process.forest += process.akCs5PFJetAnalyzer
    # process.forest += process.akCs6PFJetAnalyzer
    # process.forest += process.akCs7PFJetAnalyzer
    # process.forest += process.akCs8PFJetAnalyzer
    # process.forest += process.akCs9PFJetAnalyzer
    process.forest += process.hiPuRhoAnalyzer




addCandidateTagging = False

if addCandidateTagging:
    process.load("HeavyIonsAnalysis.JetAnalysis.candidateBtaggingMiniAOD_cff")

    from PhysicsTools.PatAlgos.tools.jetTools import updateJetCollection
    updateJetCollection(
        process,
        jetSource = cms.InputTag('slimmedJets'),
        jetCorrections = ('AK4PFchs', cms.vstring(['L1FastJet', 'L2Relative', 'L3Absolute']), 'None'),
        btagDiscriminators = ['pfCombinedSecondaryVertexV2BJetTags', 'pfDeepCSVDiscriminatorsJetTags:BvsAll', 'pfDeepCSVDiscriminatorsJetTags:CvsB', 'pfDeepCSVDiscriminatorsJetTags:CvsL'], ## to add discriminators,
        btagPrefix = 'TEST',
    )

    process.updatedPatJets.addJetCorrFactors = False
    process.updatedPatJets.discriminatorSources = cms.VInputTag(
        cms.InputTag('pfDeepCSVJetTags:probb'),
        cms.InputTag('pfDeepCSVJetTags:probc'),
        cms.InputTag('pfDeepCSVJetTags:probudsg'),
        cms.InputTag('pfDeepCSVJetTags:probbb'),
    )

    process.akCs4PFJetAnalyzer.jetTag = "updatedPatJets"

    process.forest.insert(1,process.candidateBtagging*process.updatedPatJets)

    process.akCs4PFJetAnalyzer.addDeepCSV = True

#########################
# Event Selection -> add the needed filters here
#########################

process.load('HeavyIonsAnalysis.EventAnalysis.collisionEventSelection_cff')
process.pclusterCompatibilityFilter = cms.Path(process.clusterCompatibilityFilter)
process.pprimaryVertexFilter = cms.Path(process.primaryVertexFilter)
process.pAna = cms.EndPath(process.skimanalysis)

process.akCs4PFJetAnalyzer.jetTag = cms.InputTag('akCs0PFpatJets')

