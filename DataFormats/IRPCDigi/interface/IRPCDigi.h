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
  explicit IRPCDigi(int strip, int bxLR, int bxHR, int sbxLR, int sbxHR, float tLR, float tHR); 
  IRPCDigi();

  bool operator==(const IRPCDigi& digi) const;
  bool operator<(const IRPCDigi& digi) const;
  void print() const;
  int strip() const { return strip_; }
  int bx() const { return bxLR_; }
  int sbx() const { return sbxLR_; }
  int bxLR() const { return bxLR_; }
  int bxHR() const { return bxHR_; }
  int sbxLR() const { return sbxLR_; }
  int sbxHR() const { return sbxHR_; }
  double coordinateY() const { return 0; } //to be properly implemented    
  double time() const { return 0; } //to be properly implemented

  // !!! //
  bool hasTime() const {return true;} // to be removed
  bool hasX() const {return false;} // to be removed
  bool hasY() const {return true;} // to be removed
  float coordinateX() const {return 0;}  // to be removed 

private:
  uint16_t strip_;
  int32_t bxLR_;    //BX from low radius FEB
  int32_t bxHR_;    //BX from high radius FEB 
  int32_t sbxLR_;   //sub-BX from low radius FEB     
  int32_t sbxHR_;   //sub-BX from high radius FEB  
  float tLR_;     //high resolution time rom low radius FEB       
  float tHR_;     //high resolution time rom high radius FEB 
};

std::ostream& operator<<(std::ostream& o, const IRPCDigi& digi);

#endif
