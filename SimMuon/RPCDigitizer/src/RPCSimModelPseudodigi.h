#ifndef RPCDigitizer_RPCSimModelPseudodigi_h
#define RPCDigitizer_RPCSimModelPseudodigi_h

/** \class RPCSimAverage
 *   Class for the RPC strip response simulation based
 *   on a parametrized model (ORCA-based)
 *
 *  \author Borislav Pavlov -- University of Sofia
 */
#include "SimMuon/RPCDigitizer/src/RPCSim.h"
#include "SimMuon/RPCDigitizer/src/RPCSynchronizer.h"
#include "SimMuon/RPCDigitizer/src/RPCSimAsymmetricCls.h"
#include "SimMuon/RPCDigitizer/src/RPCSimAverageNoiseEffCls.h"

#include<cstring>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<stdlib.h>
#include <FWCore/Framework/interface/EventSetup.h>
#include "SimMuon/RPCDigitizer/src/RPCSimSetUp.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

class RPCGeometry;

namespace CLHEP {
  class HepRandomEngine;
}

class RPCSimModelPseudodigi : public RPCSim
{
 public:
  RPCSimModelPseudodigi(const edm::ParameterSet& config);
  ~RPCSimModelPseudodigi();
  void simulate(const RPCRoll* roll,
                const edm::PSimHitContainer& rpcHits,
                 CLHEP::HepRandomEngine*) override;
  void simulateNoise(const RPCRoll*,
                     CLHEP::HepRandomEngine*) override;
  int getClSize(uint32_t id,float posX, CLHEP::HepRandomEngine*);


  void handleDigi(int time_hit, double precise_time, 
		  double smearedPositionX,
		  double xErr, double smearedPositionY, 
		  double yErr, const PSimHit & hit );
  void handleNoiseDigi(int time_hit, double precise_time, 
		       double smearedPositionX,
		       double xErr, double smearedPositionY, 
		       double yErr);

 protected:
  void init(){};
  
  double aveEff;
  double aveCls;
  double resRPC;
  double timOff;
  double dtimCs;
  double resEle;
  double sspeed;
  double lbGate;
  bool rpcdigiprint;
  
  int N_hits;
  int nbxing;
  double rate;
  double gate;
  double frate;
  int N_strips;
  bool do_Y;
  double sigmaY;

  std::map< int, std::vector<double> > clsMap;
  std::vector<double> sum_clsize;
  std::vector<double> clsForDetId;
  std::ifstream *infile;

  RPCSynchronizer* _rpcSync;
};
#endif
