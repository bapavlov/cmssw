/** \file
 * 
 *
 * \author Ilaria Segoni
 *
 * modified by Borislav Pavlov - University of Sofia
 * modification to be used for upgrade and for "pseudodigi"
 *
 *
 */

#include "DataFormats/IRPCDigi/interface/IRPCDigi.h"
#include <iostream>

IRPCDigi::IRPCDigi(int strip, int bx)
    : strip_(strip),
      bx_(bx),
      sbx_(0){}

IRPCDigi::IRPCDigi(int strip, int bx, int sbx)
  : strip_(strip),
    bx_(bx),
    sbx_(sbx){}

IRPCDigi::IRPCDigi()
    : strip_(0),
      bx_(0),
      sbx_(0) {}

// Comparison
bool IRPCDigi::operator==(const IRPCDigi& digi) const {
  if (strip_ != digi.strip() || bx_ != digi.bx())
    return false;
  return true;
}

///Precedence operator
bool IRPCDigi::operator<(const IRPCDigi& digi) const {
  if (digi.bx() == this->bx())
    return digi.strip() < this->strip();
  else
    return digi.bx() < this->bx();
}

std::ostream& operator<<(std::ostream& o, const IRPCDigi& digi) { return o << " " << digi.strip() << " " << digi.bx(); }

void IRPCDigi::print() const { std::cout << "Strip " << strip() << " bx " << bx() << std::endl; }
