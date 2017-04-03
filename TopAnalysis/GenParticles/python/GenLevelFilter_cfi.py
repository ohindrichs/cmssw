import FWCore.ParameterSet.Config as cms

genlevelselection = cms.EDFilter(
      "GenLevelFilter",
      RivetPSObjects = cms.InputTag('RivetPseudoTop', 'pseudotop'),
      PartonLevelObjects = cms.InputTag('GenTTbar')
      )

