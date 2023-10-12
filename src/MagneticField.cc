#include "MagneticField.hh"

#include "G4GenericMessenger.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"

namespace MF
{

MagneticField::MagneticField()
{}
MagneticField::~MagneticField()
{}

void MagneticField::GetFieldValue(const G4double [4],double *bField) const
{
  bField[0] = 0.;
  bField[1] = fBy;
  bField[2] = 0.;
}

}
