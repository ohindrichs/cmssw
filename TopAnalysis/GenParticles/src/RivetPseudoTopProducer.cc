#include "../interface/RivetPseudoTopProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/Common/interface/RefToPtr.h"
#include "DataFormats/METReco/interface/METFwd.h"
#include "DataFormats/METReco/interface/MET.h"
#include "RecoJets/JetProducers/interface/JetSpecific.h"
#include "CommonTools/Utils/interface/PtComparator.h"


using namespace std;
using namespace edm;
using namespace reco;

RivetPseudoTopProducer::RivetPseudoTopProducer(const edm::ParameterSet& pset):
	srcToken_(consumes<edm::HepMCProduct>(pset.getParameter<edm::InputTag>("src"))),
	rivet_(new Rivet::CMSPseudoTop)
{
	rivet_->cmsinit(pset);
	analysisHandler_.addAnalysis(rivet_);
	analysisHandler_.setIgnoreBeams(true);

	genVertex_ = reco::Particle::Point(0,0,0);

	produces<reco::GenParticleCollection>("pseudotop");
	produces<reco::GenParticleCollection>("particles");
}

void RivetPseudoTopProducer::produce(edm::Event& event, const edm::EventSetup& eventSetup)
{
	std::unique_ptr<reco::GenParticleCollection> pseudotop(new reco::GenParticleCollection);
	std::unique_ptr<reco::GenParticleCollection> particles(new reco::GenParticleCollection);

	edm::Handle<HepMCProduct> srcHandle;
	event.getByToken(srcToken_, srcHandle);

	//Rivet::Event genEvent(srcHandle->GetEvent());
	const HepMC::GenEvent* genEvent = srcHandle->GetEvent();
//int n =0;
//	for(HepMC::GenEvent::particle_const_iterator it = genEvent->particles_begin() ; it != genEvent->particles_end() ; ++it)
//	{
//		cout << (++n) << ": " << (*it)->status() << " " << (*it)->pdg_id() << " " << (*it)->production_vertex() << " " << (*it)->end_vertex() << endl;
//		if((*it)->production_vertex() != nullptr)
//		{
//			for(HepMC::GenVertex::particles_in_const_iterator itpar = (*it)->production_vertex()->particles_in_const_begin() ; itpar != (*it)->production_vertex()->particles_in_const_end() ; ++itpar)
//			{
//				cout << "-- " << (*itpar)->pdg_id() << endl;
//			}
//		}
//if(abs((*it)->pdg_id()) == 6)	cout << (++n) << ": " << (*it)->status() << " " << (*it)->pdg_id() << " " << (*it)->production_vertex() << " " << (*it)->end_vertex() << endl;
//}


//cout << "INFO: " << analysisHandler_.sqrtS() << " " << analysisHandler_.beamIds().first << " " << analysisHandler_.beamIds().second << endl;

	analysisHandler_.analyze(*genEvent);

	particles->resize(rivet_->allObjects().size());
	for(size_t n = 0 ; n < rivet_->allObjects().size() ; ++n)
	{
		const Rivet::Particle& par = rivet_->allObjects()[n];
		const Rivet::ParticleInfo& parinfo = rivet_->allObjectInfos()[n];

		if(abs(par.pdgId()) < 7)//Jets
		{
			float id = parinfo.m_lepdecay ? parinfo.m_pdgidconst + 0.5 : parinfo.m_pdgidconst;
			(*particles)[n] = reco::GenParticle(0, p4(par), reco::Particle::Point(id, parinfo.m_xb, 0.), par.pdgId(), 1, true);
		}
		else
		{
			(*particles)[n] = reco::GenParticle(par.charge(), p4(par), reco::Particle::Point(parinfo.m_iso, 0., 0.), par.pdgId(), 1, true);
		}

	}

	if(rivet_->topEvent())
	{
		pseudotop->resize(8);

		const Rivet::Particle& top = rivet_->top();
		(*pseudotop)[0] = reco::GenParticle(top.charge(), p4(top), genVertex_, top.pdgId(), 1, true);
		const Rivet::Particle& top_b = rivet_->top_b();
		(*pseudotop)[1] = reco::GenParticle(top_b.charge(), p4(top_b), genVertex_, top_b.pdgId(), 1, true);
		const Rivet::Particle& top_wdown = rivet_->top_wdown();
		(*pseudotop)[2] = reco::GenParticle(top_wdown.charge(), p4(top_wdown), genVertex_, top_wdown.pdgId(), 1, true);
		const Rivet::Particle& top_wup = rivet_->top_wup();
		(*pseudotop)[3] = reco::GenParticle(top_wup.charge(), p4(top_wup), genVertex_, top_wup.pdgId(), 1, true);

		const Rivet::Particle& topbar = rivet_->topbar();
		(*pseudotop)[4] = reco::GenParticle(topbar.charge(), p4(topbar), genVertex_, topbar.pdgId(), 1, true);
		const Rivet::Particle& topbar_b = rivet_->topbar_b();
		(*pseudotop)[5] = reco::GenParticle(topbar_b.charge(), p4(topbar_b), genVertex_, topbar_b.pdgId(), 1, true);
		const Rivet::Particle& topbar_wdown = rivet_->topbar_wdown();
		(*pseudotop)[6] = reco::GenParticle(topbar_wdown.charge(), p4(topbar_wdown), genVertex_, topbar_wdown.pdgId(), 1, true);
		const Rivet::Particle& topbar_wup = rivet_->topbar_wup();
		(*pseudotop)[7] = reco::GenParticle(topbar_wup.charge(), p4(topbar_wup), genVertex_, topbar_wup.pdgId(), 1, true);

		for (const Rivet::Particle& par : rivet_->additionalObjects())
		{
			pseudotop->push_back(reco::GenParticle(0, p4(par), genVertex_, par.pdgId(), 1, true));
		}
	}
	event.put(std::move(pseudotop), "pseudotop");
	event.put(std::move(particles), "particles");
}

