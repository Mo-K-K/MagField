#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_hh

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4FieldManager.hh"

#include <vector>

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;

namespace MF
{

class MagneticField;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    MyDetectorConstruction();
    ~MyDetectorConstruction() override;

    G4VPhysicalVolume* Construct() override;
    void ConstructSDandField() override;

    //void SetArmAngle(G4double val);
    //G4double GetArmAngle() { return fArmAngle; }

    void ConstructMaterials();

  private:
    void DefineCommands();

    G4GenericMessenger* fMessenger;

    static G4ThreadLocal MagneticField* fMagneticField;
    static G4ThreadLocal G4FieldManager* fFieldMgr;

    G4LogicalVolume* logicDetector;
    G4LogicalVolume* fMagneticLogical = nullptr;

    std::vector<G4VisAttributes*> fVisAttributes;

    //G4double fArmAngle = 30.*CLHEP::deg;
    //G4RotationMatrix* fArmRotation = nullptr;
    //G4VPhysicalVolume* fSecondArmPhys = nullptr;
};

}


#endif
