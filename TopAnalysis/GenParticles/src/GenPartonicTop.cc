#include "../interface/GenPartonicTop.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/Math/interface/LorentzVector.h"


#include <iostream>

using namespace std;

//////////////////////GenPartonicTop/////////////////////////

GenPartonicTop::GenPartonicTop(const edm::ParameterSet& iConfig):
	TokengenParticles(consumes<reco::GenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticleLabel"))),
	TokengenParticlesS1(consumes<pat::PackedGenParticleCollection>(iConfig.getParameter<edm::InputTag>("genParticleS1Label"))),
	TokenLHERunInfo(consumes<LHERunInfoProduct,edm::InRun>(edm::InputTag("externalLHEProducer")))
{
	produces<reco::GenParticleCollection>();
}


void GenPartonicTop::produce(edm::Event& iEvent, const edm::EventSetup& iEventSetup)
{
	std::auto_ptr<reco::GenParticleCollection> particles(new reco::GenParticleCollection);
	edm::Handle<reco::GenParticleCollection> GenParticles;
	iEvent.getByToken(TokengenParticles, GenParticles);
	if(!GenParticles.isValid()) {iEvent.put(particles); return;}

	particles->resize(8);
	int topcounter = 0;
	for(size_t n = 0 ; n < GenParticles->size() ; ++n)
	{
		reco::GenParticleRef gp(GenParticles, n); 
		if(gp->status() > 60 && gp->status() < 70)
		{
			if(gp->pdgId() == 6)
			{
				topcounter++;
				(*particles)[0] = *gp;
			}
			else if(gp->pdgId() == -6)
			{
				topcounter++;
				(*particles)[4] = *gp;
			}
		}
		if(gp->status() > 21 && gp->status() < 30 && gp->numberOfMothers() != 0)
		{
			if(gp->pdgId() == 5 && gp->mother(0)->pdgId() == 6)
			{
				(*particles)[1] = *gp;
			}
			else if(gp->pdgId() == -5 && gp->mother(0)->pdgId() == -6)
			{
				(*particles)[5] = *gp;
			}
			else if(gp->pdgId() < 0 && gp->pdgId() > -6 && gp->mother(0)->pdgId() == 24)
			{
				(*particles)[2] = *gp;
			}
			else if(gp->pdgId() > 0 && gp->pdgId() < 6 && gp->mother(0)->pdgId() == 24)
			{
				(*particles)[3] = *gp;
			}
			else if(gp->pdgId() < 0 && gp->pdgId() > -6 && gp->mother(0)->pdgId() == -24)
			{
				(*particles)[6] = *gp;
			}
			else if(gp->pdgId() > 0 && gp->pdgId() < 6 && gp->mother(0)->pdgId() == -24)
			{
				(*particles)[7] = *gp;
			}
		}

		if(gp->pdgId() < -10 && gp->pdgId() > -18 && gp->mother(0)->pdgId() == 24)
		{
			(*particles)[2] = *gp;
		}
		else if(gp->pdgId() > 10 && gp->pdgId() < 18 && gp->mother(0)->pdgId() == 24)
		{
			(*particles)[3] = *gp;
		}
		else if(gp->pdgId() < -10 && gp->pdgId() > -18 && gp->mother(0)->pdgId() == -24)
		{
			(*particles)[6] = *gp;
		}
		else if(gp->pdgId() > 10 && gp->pdgId() < 18 && gp->mother(0)->pdgId() == -24)
		{
			(*particles)[7] = *gp;
		}

	}
	//Herwig
	if(topcounter != 2) 
	{
		particles->clear();
		particles->resize(8);
		topcounter = 0;
		for(size_t n = 0 ; n < GenParticles->size() ; ++n)
		{
			reco::GenParticleRef gp(GenParticles, n); 
			if(gp->status() == 11)
			{
				if(gp->pdgId() == 6 && gp->daughter(0)->pdgId() != 6)
				{
					topcounter++;
					(*particles)[0] = *gp;
				}
				else if(gp->pdgId() == -6 && gp->daughter(0)->pdgId() != -6)
				{
					topcounter++;
					(*particles)[4] = *gp;
				}
				if(gp->numberOfMothers() != 0)
				{
					if(gp->pdgId() == 5 && gp->mother(0)->pdgId() == 6)
					{
						(*particles)[1] = *dynamic_cast<const reco::GenParticle*>(gp->daughter(0)->daughter(0));
					}
					else if(gp->pdgId() == -5 && gp->mother(0)->pdgId() == -6)
					{
						(*particles)[5] = *dynamic_cast<const reco::GenParticle*>(gp->daughter(0)->daughter(0));
					}

					if(gp->pdgId() < 0 && gp->pdgId() > -6 && gp->mother(0)->pdgId() == 24)
					{
						(*particles)[2] = *dynamic_cast<const reco::GenParticle*>(gp->daughter(0));
					}
					else if(gp->pdgId() > 0 && gp->pdgId() < 6 && gp->mother(0)->pdgId() == 24)
					{
						(*particles)[3] = *dynamic_cast<const reco::GenParticle*>(gp->daughter(0));
					}
					else if(gp->pdgId() < 0 && gp->pdgId() > -6 && gp->mother(0)->pdgId() == -24)
					{
						(*particles)[6] = *dynamic_cast<const reco::GenParticle*>(gp->daughter(0));
					}
					else if(gp->pdgId() > 0 && gp->pdgId() < 6 && gp->mother(0)->pdgId() == -24)
					{
						(*particles)[7] = *dynamic_cast<const reco::GenParticle*>(gp->daughter(0));
					}

					if(gp->pdgId() < -10 && gp->pdgId() > -18 && gp->mother(0)->pdgId() == 24)
					{
						(*particles)[2] = *dynamic_cast<const reco::GenParticle*>(gp->daughter(0));
					}
					else if(gp->pdgId() > 10 && gp->pdgId() < 18 && gp->mother(0)->pdgId() == 24)
					{
						(*particles)[3] = *dynamic_cast<const reco::GenParticle*>(gp->daughter(0));
					}
					else if(gp->pdgId() < -10 && gp->pdgId() > -18 && gp->mother(0)->pdgId() == -24)
					{
						(*particles)[6] = *dynamic_cast<const reco::GenParticle*>(gp->daughter(0));
					}
					else if(gp->pdgId() > 10 && gp->pdgId() < 18 && gp->mother(0)->pdgId() == -24)
					{
						(*particles)[7] = *dynamic_cast<const reco::GenParticle*>(gp->daughter(0));
					}
				}

			}
		}
	}
if(topcounter != 2) particles->clear();

//all++;
//if(abs((*particles)[2].pdgId()) < 6 && abs((*particles)[6].pdgId()) < 6) had++;
//else if(abs((*particles)[2].pdgId()) < 6 || abs((*particles)[6].pdgId()) < 6) sem++;
//else if(abs((*particles)[2].pdgId()) > 6 && abs((*particles)[6].pdgId()) > 6) lep++;
//cout << had/all << " " << sem/all << " " << lep/all << endl;
//for(size_t i = 0 ; i < particles->size() ; ++i)
//{
//	cout << i << " " << (*particles)[i].pdgId() << endl;
//}

iEvent.put(particles);
}


void GenPartonicTop::endRun(edm::Run const& iRun, edm::EventSetup const& es)
{
	edm::Handle<LHERunInfoProduct> run;
	//iRun.getByLabel( src_, run );

	iRun.getByToken(TokenLHERunInfo, run);
	if(!run.isValid()) return;

	//	for (LHERunInfoProduct::headers_const_iterator iter=run->headers_begin() ; iter != run->headers_end() ; iter++)
	//	{
	//		std::cout << "TAG: " << iter->tag() << std::endl;
	//		std::vector<std::string> lines = iter->lines();
	//		for (unsigned int iLine = 0; iLine<lines.size(); iLine++)
	//		{
	//			std::cout << iLine << " " <<  lines.at(iLine);
	//		}
	//	}
	//
	//
	//	const lhef::HEPRUP thisHeprup_ = run->heprup();
	//
	//	std::cout << "HEPRUP \n" << std::endl;
	//	std::cout << "IDBMUP " << std::setw(14) << std::fixed << thisHeprup_.IDBMUP.first 
	//		<< std::setw(14) << std::fixed << thisHeprup_.IDBMUP.second << std::endl; 
	//	std::cout << "EBMUP  " << std::setw(14) << std::fixed << thisHeprup_.EBMUP.first 
	//		<< std::setw(14) << std::fixed << thisHeprup_.EBMUP.second << std::endl; 
	//	std::cout << "PDFGUP " << std::setw(14) << std::fixed << thisHeprup_.PDFGUP.first 
	//		<< std::setw(14) << std::fixed << thisHeprup_.PDFGUP.second << std::endl; 
	//	std::cout << "PDFSUP " << std::setw(14) << std::fixed << thisHeprup_.PDFSUP.first 
	//		<< std::setw(14) << std::fixed << thisHeprup_.PDFSUP.second << std::endl; 
	//	std::cout << "IDWTUP " << std::setw(14) << std::fixed << thisHeprup_.IDWTUP << std::endl; 
	//	std::cout << "NPRUP  " << std::setw(14) << std::fixed << thisHeprup_.NPRUP << std::endl; 
	//	std::cout << "        XSECUP " << std::setw(14) << std::fixed 
	//		<< "        XERRUP " << std::setw(14) << std::fixed 
	//		<< "        XMAXUP " << std::setw(14) << std::fixed 
	//		<< "        LPRUP  " << std::setw(14) << std::fixed << std::endl;
	//	for ( unsigned int iSize = 0 ; iSize < thisHeprup_.XSECUP.size() ; iSize++ ) {
	//		std::cout  << std::setw(14) << std::fixed << thisHeprup_.XSECUP[iSize]
	//			<< std::setw(14) << std::fixed << thisHeprup_.XERRUP[iSize]
	//			<< std::setw(14) << std::fixed << thisHeprup_.XMAXUP[iSize]
	//			<< std::setw(14) << std::fixed << thisHeprup_.LPRUP[iSize] 
	//			<< std::endl;
	//	}
	//	std::cout << " " << std::endl;

}

