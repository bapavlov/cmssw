#ifndef RPCDigi_RPCDigi_h
#define RPCDigi_RPCDigi_h

/** \class RPCDigi
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

class RPCDigi {
public:
  explicit RPCDigi(int strip, int bx);
  explicit RPCDigi(int strip, int bx, int sbx);
  RPCDigi();

  bool operator==(const RPCDigi& digi) const;
  bool operator<(const RPCDigi& digi) const;
  void print() const;
  int strip() const { return strip_; }
  int bx() const { return bx_; }
  int sbx() const { return sbx_; }
  double time() const { return 0; } //to be implemented


  //!!!
  bool hasTime() const {return true;} // to be removed                         
  bool hasX() const {return false;} // to be removed                           
  bool hasY() const {return false;} // to be removed                        

  float coordinateX() const {return 0;}  // to be removed 
  float coordinateY() const {return 0;}  // to be removed 

  

private:
  uint16_t strip_;
  int32_t bx_;
  int32_t sbx_;
};

std::ostream& operator<<(std::ostream& o, const RPCDigi& digi);

#endif
