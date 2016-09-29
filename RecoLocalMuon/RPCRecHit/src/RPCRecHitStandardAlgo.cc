/*
 *  See header file for a description of this class.
 *
 *  \author M. Maggi -- INFN
 */

#include "RPCCluster.h"
#include "RecoLocalMuon/RPCRecHit/src/RPCRecHitStandardAlgo.h"
#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "Geometry/RPCGeometry/interface/RPCRoll.h"
#include "Geometry/CommonTopologies/interface/StripTopology.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Utilities/interface/Exception.h"

// First Step
bool RPCRecHitStandardAlgo::compute(const RPCRoll& roll,
				    const RPCCluster& cluster,
				    LocalPoint& Point,
				    LocalError& error,
            float& time, float& timeErr)  const
{
  // Get Average Strip position
  float x, xx;
  if ( cluster.hasX() ) {
    x = (cluster.firstX()+cluster.lastX())/2;
//    const float dx = cluster.lastX()-cluster.firstX();
    const float dx = cluster.DeltaX();
    xx = dx*dx/12;
  }
  else {
    const float fstrip = (roll.centreOfStrip(cluster.firstStrip())).x();
    const float lstrip = (roll.centreOfStrip(cluster.lastStrip())).x();
    x = (fstrip + lstrip)/2;
    xx = LocalError(roll.localError((cluster.firstStrip()+cluster.lastStrip())/2.)).xx();
  }

  const float y = cluster.y();
  Point = LocalPoint(x, y, 0);

  float yy;
  if ( !cluster.hasY() ) {
    yy = LocalError(roll.localError((cluster.firstStrip()+cluster.lastStrip())/2.)).yy();
  }
  else {
    // Maximum estimate of local y error, (distance to the boundary)/sqrt(3)
    // which gives consistent error to the default one at y=0
    const float stripLen = roll.specificTopology().stripLength();
    const float maxDy = stripLen/2 - std::abs(cluster.y());
    yy = maxDy*maxDy/3;
  }
  error = LocalError(xx, 0, yy); // xx, xy, yy

  if ( cluster.hasTime() ) {
    time = cluster.time();
    timeErr = cluster.timeRMS();
  }
  else {
    time = 0;
    timeErr = -1;
  }

  return true;
}

bool RPCRecHitStandardAlgo::compute(const RPCRoll& roll,
                                    const RPCCluster& cl,
                                    const float& angle,
                                    const GlobalPoint& globPos,
                                    LocalPoint& Point,
                                    LocalError& error,
                                    float& time, float& timeErr)  const
{
  this->compute(roll,cl,Point,error,time,timeErr);
  return true;
}

