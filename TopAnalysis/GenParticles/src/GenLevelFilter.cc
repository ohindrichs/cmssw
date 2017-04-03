#include "../interface/GenLevelFilter.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/Math/interface/LorentzVector.h"


#include <iostream>

using namespace std;

//////////////////////GenLevelFilter/////////////////////////

GenLevelFilter::GenLevelFilter(const edm::ParameterSet& iConfig):
	TokenPartonLevel(consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("PartonLevelObjects"))),
	//TokenParticleLevel(consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("ParticleLevelObjects"))),
	TokenRivetPS(consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("RivetPSObjects")))
{
}


bool GenLevelFilter::filter(edm::Event& iEvent, const edm::EventSetup& iEventSetup)
{
	all++;

	edm::Handle<reco::GenParticleCollection> PartonLevel;
	iEvent.getByToken(TokenPartonLevel, PartonLevel);
	if(!PartonLevel.isValid()) {return false;}

	int leptons = 0;
	int tops = 0;
	for(size_t n = 0 ; n < PartonLevel->size() ; ++n)
	{
		reco::GenParticleRef gp(PartonLevel, n); 
		int abspdgid = abs(gp->pdgId());
		if(abspdgid == 11 ||  abspdgid == 13) leptons++;
		if(abspdgid == 6) tops++;
	}
	if(tops != 2) return false;

	if(leptons >= 1) return true;


//	edm::Handle<reco::GenParticleCollection> ParticleLevel;
//	iEvent.getByToken(TokenParticleLevel, ParticleLevel);
//	if(!ParticleLevel.isValid()) {return true;}
//
//	leptons = 0;
//	for(size_t n = 0 ; n < ParticleLevel->size() ; ++n)
//	{
//		reco::GenParticleRef gp(ParticleLevel, n); 
//		int abspdgid = abs(gp->pdgId());
//		if(abspdgid == 11 ||  abspdgid == 13) leptons++;
//	}
//	if(leptons >= 1) return true;


	edm::Handle<reco::GenParticleCollection> RivetPS;
	iEvent.getByToken(TokenRivetPS, RivetPS);
	if(!RivetPS.isValid()) {return true;}

	leptons = 0;
	for(size_t n = 0 ; n < RivetPS->size() ; ++n)
	{
		reco::GenParticleRef gp(RivetPS, n); 
		int abspdgid = abs(gp->pdgId());
		if(abspdgid == 11 ||  abspdgid == 13) leptons++;
	}
	if(leptons >= 1) return true;

	failed++;
	return false;
}


