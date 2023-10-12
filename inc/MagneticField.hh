
#ifndef MagneticField_H
#define MagneticField_H 

#include "globals.hh"
#include "G4MagneticField.hh"

#include <CLHEP/Units/SystemOfUnits.h>

namespace MF
{

class MagneticField : public G4MagneticField
{
  public:
    MagneticField();
    ~MagneticField() override;

    void GetFieldValue(const G4double point[4],double* bField ) const override;

    void SetField(G4double val) {fBy = val; }
    G4double GetField() const { return fBy; }

  private:
    G4double fBy = 1.0*CLHEP::tesla;
};

}

#endif
