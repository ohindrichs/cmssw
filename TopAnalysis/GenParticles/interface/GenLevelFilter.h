#ifndef GenLEVELFILTER_H
#define GenLEVELFILTER_H


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"


using namespace std;

class GenLevelFilter : public edm::EDFilter
{
	private:
		double all = 0.;
		double failed = 0.;
		edm::EDGetTokenT<reco::GenParticleCollection> TokenPartonLevel;
		//edm::EDGetTokenT<reco::GenParticleCollection> TokenParticleLevel;
		edm::EDGetTokenT<reco::GenParticleCollection> TokenRivetPS;

	public:
		GenLevelFilter(const edm::ParameterSet& iConfig);
		~GenLevelFilter(){}

		virtual void beginJob(const edm::EventSetup& iEventSetup){}
		virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iEventSetup);
		virtual void endJob(){}
};

DEFINE_FWK_MODULE(GenLevelFilter);
#endif
