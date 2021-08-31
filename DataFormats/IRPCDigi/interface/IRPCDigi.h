#ifndef IRPCDigi_IRPCDigi_h
#define IRPCDigi_IRPCDigi_h

/** \class IRPCDigi
 *
 * Digi for Rsisitive Plate Chamber
 *  
 *
 * \author I. Segoni -- CERN & M. Maggi -- INFN Bari
 * 
 * modified by Borislav Pavlov - University of Sofia
 * modification to be used for upgrade and for "pseudodigi"
 * Additional modification to match the new readout
*/

#include <cstdint>
#include <iosfwd>

class IRPCDigi {
public:
  explicit IRPCDigi(int strip, int bx);
  explicit IRPCDigi(int strip, int bx, int sbx);
  IRPCDigi();

  bool operator==(const IRPCDigi& digi) const;
  bool operator<(const IRPCDigi& digi) const;
  void print() const;
  int strip() const { return strip_; }
  int bx() const { return bx_; }
  int sbx() const { return sbx_; }
  double time() const { return 0; } //to be implemented
  

private:
  uint16_t strip_;
  int32_t bx_;
  int32_t sbx_;
};

std::ostream& operator<<(std::ostream& o, const IRPCDigi& digi);

#endif
