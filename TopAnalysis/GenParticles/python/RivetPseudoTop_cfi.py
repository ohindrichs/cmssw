import FWCore.ParameterSet.Config as cms

RivetPseudoTop = cms.EDProducer("RivetPseudoTopProducer",
		src = cms.InputTag("genParticles2HepMC:unsmeared"),
		JetPtMin = cms.double(25.),
		JetEtaMax = cms.double(2.4),
		LeptonPtMin = cms.double(30.),
		LeptonEtaMax = cms.double(2.4),
		LeptonIsoMax = cms.double(0.2),
		LeptonIsoDR = cms.double(0.4),
		LeptonVetoPtMin = cms.double(15.),
		LeptonVetoEtaMax = cms.double(2.4),
		PhotonPtMin = cms.double(15.),
		PhotonEtaMax = cms.double(2.4),
		PhotonIsoMax = cms.double(0.2),
		PhotonIsoDR = cms.double(0.4)
		)

