#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4FieldManager.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "detector.hh"

#include <vector>

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;

class MagneticField;

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    virtual G4VPhysicalVolume *Construct();

    void ConstructSDandField();

    void ConstructMaterials();


  private:
    static G4ThreadLocal MagneticField* fMagneticField;
    static G4ThreadLocal G4FieldManager* fFieldMgr;

    G4LogicalVolume* logicDetector;
    G4LogicalVolume* fMagneticLogical = nullptr;

};



#endif
