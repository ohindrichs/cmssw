#ifndef RivetPseudoTopProducer_H
#define RivetPseudoTopProducer_H

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/JetReco/interface/GenJetCollection.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"

#include "CMSPseudoTop.hh"
#include "Rivet/AnalysisHandler.hh"

class RivetPseudoTopProducer : public edm::EDProducer
{
	public:
		RivetPseudoTopProducer(const edm::ParameterSet& pset);
		virtual ~RivetPseudoTopProducer() {}
		virtual void produce(edm::Event& event, const edm::EventSetup& eventSetup) override;
		virtual void endJob()
		{
			analysisHandler_.finalize();
		}

	private:
		template<typename T> reco::Candidate::LorentzVector p4(const T& p) const
		{
			return reco::Candidate::LorentzVector(p.px(), p.py(), p.pz(), p.energy());
		}

		const edm::EDGetTokenT<edm::HepMCProduct> srcToken_;

		const std::string projection_;

		reco::Particle::Point genVertex_;

		Rivet::CMSPseudoTop* rivet_;
		Rivet::AnalysisHandler analysisHandler_;
};

DEFINE_FWK_MODULE(RivetPseudoTopProducer);
#endif
