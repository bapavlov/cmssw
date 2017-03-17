#include "CondFormats/MuonSystemAging/interface/MuonSystemAging.h"
MuonSystemAging::MuonSystemAging(){
  m_RPCchambers.reserve(600000);
  m_CSCineff = 0.0;
}
