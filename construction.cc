
#include "construction.hh"
#include "MagneticField.hh"


#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4Mag_UsualEqRhs.hh"

#include "G4Material.hh"
#include "G4Element.hh"
#include "G4MaterialTable.hh"
#include "G4NistManager.hh"

#include "G4VSolid.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4UserLimits.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4RunManager.hh"
#include "G4GenericMessenger.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

G4ThreadLocal MagneticField* MyDetectorConstruction::fMagneticField = nullptr;
G4ThreadLocal G4FieldManager* MyDetectorConstruction::fFieldMgr = nullptr;


MyDetectorConstruction::MyDetectorConstruction()
{}


MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
  ConstructMaterials();
  auto air = G4Material::GetMaterial("G4_AIR");
  auto argonGas = G4Material::GetMaterial("G4_Ar");

  G4bool checkOverlaps = true;


  auto worldSolid
    = new G4Box("worldBox",0.5*m,0.5*m,0.5*m);
  auto worldLogical
    = new G4LogicalVolume(worldSolid,air,"worldLogical");
  auto worldPhysical = new G4PVPlacement(
    0, G4ThreeVector(0.,0.,0.), worldLogical, "worldPhysical", 0, false, 0, checkOverlaps);

  G4Box *solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m);

    logicDetector = new G4LogicalVolume(solidDetector, air, "logicalDetector");

    for(G4int i = 0; i< 100; i++)
    {
        for(G4int  j = 0; j< 100; j++)
        {
            G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m+(i+0.5)*m/100, -0.5*m+(j+0.5)*m/100, 0.49*m), logicDetector, "physDetector", worldLogical, false, j+i*100, true);
        }
    }

  auto magneticSolid
    = new G4Tubs("magneticTubs",0.,0.05*m,0.05*m,0.,360.*deg);

  fMagneticLogical
    = new G4LogicalVolume(magneticSolid, air, "magneticLogical");

  auto fieldRot = new G4RotationMatrix();
  fieldRot->rotateX(90.*deg);
  new G4PVPlacement(fieldRot,G4ThreeVector(0.,0.,0.3*m),fMagneticLogical,
                    "magneticPhysical",worldLogical,
                    false,0,checkOverlaps);

  auto userLimits = new G4UserLimits(1 * m);
  fMagneticLogical->SetUserLimits(userLimits);

  return worldPhysical;
}


void MyDetectorConstruction::ConstructSDandField()
{
  MySensitiveDetector * sensDet = new MySensitiveDetector("SensitiveDetector");

  fMagneticField = new MagneticField();
  fFieldMgr = new G4FieldManager();
  fFieldMgr->SetDetectorField(fMagneticField);
  fFieldMgr->CreateChordFinder(fMagneticField);
  G4bool forceToAllDaughters = true;
  fMagneticLogical->SetFieldManager(fFieldMgr, forceToAllDaughters);

  logicDetector->SetSensitiveDetector(sensDet);
}

void MyDetectorConstruction::ConstructMaterials()
{
  auto nistManager = G4NistManager::Instance();

  nistManager->FindOrBuildMaterial("G4_AIR");
  nistManager->FindOrBuildMaterial("G4_Ar");
}
