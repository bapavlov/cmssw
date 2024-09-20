#include "DataFormats/RPCDigi/interface/RPCDigiPhase2Time.h"


RPCDigiPhase2Time::RPCDigiPhase2Time(const RPCDigiPhase2 & adigi):theDigi(adigi){}

float RPCDigiPhase2Time::time(){
  return 25.*theDigi.bx() + 2.5*theDigi.sbx();
}

