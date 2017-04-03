#ifndef GenPartonicTop_H
#define GenPartonicTop_H


#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"

using namespace std;

class GenPartonicTop : public edm::EDProducer
{
	private:
		//double all = 0.;
		//double had = 0.;
		//double sem = 0.;
		//double lep = 0.;
		edm::EDGetTokenT<reco::GenParticleCollection> TokengenParticles;
		edm::EDGetTokenT<pat::PackedGenParticleCollection> TokengenParticlesS1;
		edm::EDGetTokenT<LHERunInfoProduct> TokenLHERunInfo;

	public:
		GenPartonicTop(const edm::ParameterSet& iConfig);
		~GenPartonicTop(){}

		virtual void beginJob(const edm::EventSetup& iEventSetup){}
		virtual void endRun(edm::Run const& iRun, edm::EventSetup const& es);
		virtual void produce(edm::Event& iEvent, const edm::EventSetup& iEventSetup);
		virtual void endJob(){}
};

DEFINE_FWK_MODULE(GenPartonicTop);
#endif
