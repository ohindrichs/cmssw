import FWCore.ParameterSet.Config as cms

GenTTbar = cms.EDProducer(
	'GenPartonicTop',
	genParticleLabel = cms.InputTag('prunedGenParticles'),
	genParticleS1Label = cms.InputTag('packedGenParticles'),
)        

