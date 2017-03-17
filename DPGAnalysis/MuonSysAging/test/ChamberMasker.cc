// -*- C++ -*-
//
// Class:      ChamberMasker
// 
//
// Original Author:  Sunil Bansal
//         Created:  Wed, 29 Jun 2016 16:27:31 GMT
//
//


// system include files
#include <memory>
#include <regex>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/IOVSyncValue.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"

#include "CondFormats/MuonSystemAging/interface/MuonSystemAging.h"
#include "CondCore/DBOutputService/interface/PoolDBOutputService.h"
//
// class declaration
//

class ChamberMasker : public edm::one::EDAnalyzer<edm::one::WatchRuns>  
{

public:
  explicit ChamberMasker(const edm::ParameterSet&);
  ~ChamberMasker();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
  
private:
  
  virtual void beginJob() override;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&) override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endRun(const edm::Run&, const edm::EventSetup&) override { };
  virtual void endJob() override;
  
  void createDtAgingMap(edm::ESHandle<DTGeometry> & dtGeom);
  
  std::vector<int> m_maskedRPCIDs;
  std::vector<std::string> m_ChamberRegEx;
  std::map<uint32_t, float> m_DTChambEffs;
  double m_ineffCSC;      
  
  // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
ChamberMasker::ChamberMasker(const edm::ParameterSet& iConfig)

{  
   m_ineffCSC     = iConfig.getParameter<double>("CSCineff"); 
   m_ChamberRegEx = iConfig.getParameter<std::vector<std::string>>("chamberRegEx"); 
   for ( auto rpc_ids : iConfig.getParameter<std::vector<int>>("maskedRPCIDs"))
    {
      m_maskedRPCIDs.push_back(rpc_ids);
      std::cout << rpc_ids << std::endl;
    }

}


ChamberMasker::~ChamberMasker()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//


// ------------ method called once each job just before starting event loop  ------------
void 
ChamberMasker::beginJob()
{
}

// ------------ method called at the beginning of each run ------------
void
ChamberMasker::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{

  edm::ESHandle<DTGeometry> dtGeom;
  iSetup.get<MuonGeometryRecord>().get(dtGeom);

  createDtAgingMap(dtGeom);
  
}

// ------------ method called for each event  ------------
void
ChamberMasker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   MuonSystemAging* muonSystAging = new MuonSystemAging();
   for(unsigned int i = 0; i < m_maskedRPCIDs.size();++i){
     muonSystAging->m_RPCchambers.push_back(m_maskedRPCIDs.at(i));
   }

   muonSystAging->m_DTChambEffs = m_DTChambEffs;

   muonSystAging->m_CSCineff = m_ineffCSC; 
   edm::Service<cond::service::PoolDBOutputService> poolDbService;
   if( poolDbService.isAvailable() ) poolDbService->writeOne( muonSystAging, poolDbService->currentTime(),"MuonSystemAgingRcd" );
   
}

// ------------ method called once each job just after ending the event loop  ------------
void 
ChamberMasker::endJob() 
{
}

void
ChamberMasker::createDtAgingMap(edm::ESHandle<DTGeometry> & dtGeom)
{

  const std::vector<const DTChamber*> chambers = dtGeom->chambers();

  std::cout << chambers.size() << std::endl;

  for ( const DTChamber *ch : chambers)
   {

     DTChamberId chId = ch->id();

     std::string chTag = "WH" + std::to_string(chId.wheel())
                       + "_ST" + std::to_string(chId.station())
                       + "_SEC" + std::to_string(chId.sector());

     float eff = 1.;

     for (auto & chRegExStr : m_ChamberRegEx)
       {

	 std::string effTag(chRegExStr.substr(chRegExStr.find(":")));

	 const std::regex chRegEx(chRegExStr.substr(0,chRegExStr.find(":")));
	 const std::regex effRegEx("(\\d*\\.\\d*)");

	 std::smatch effMatch;

	 if ( std::regex_search(chTag, chRegEx) &&
	      std::regex_search(effTag, effMatch, effRegEx))
	   {
	     std::string effStr = effMatch.str();
	     eff = std::atof(effStr.c_str());
	   }

       } 

     m_DTChambEffs[chId.rawId()] = eff;

     std::cout << chId << " " << eff << std::endl;
         
   }
  
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ChamberMasker::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ChamberMasker);
