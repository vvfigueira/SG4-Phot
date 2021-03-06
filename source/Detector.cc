// Includes do C++

#include <math.h>

// Includes da Simulação

#include "Detector.hh"
#include "CampoEletrico.hh"
#include "DetectorSensivel.hh"
#include "DetectorMens.hh"
#include "Constantes.hh"

// Includes de Geometria

#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "G4MultiUnion.hh"
#include "G4VisAttributes.hh"
#include "G4Region.hh"

// Include de Unidades

#include "G4SystemOfUnits.hh"
#include "PhysicalConstants.h"

// Includes do Campo

#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include "G4ElectroMagneticField.hh"
#include "G4UniformMagField.hh"
#include "G4UniformElectricField.hh"
#include "G4EqMagElectricField.hh"
#include "G4IntegrationDriver.hh"
#include "G4DormandPrince745.hh"
#include "G4ChordFinder.hh"

using namespace CLHEP;

Detector::Detector()
    : pressaogas(Dim::pressaogas),
    intcamp(100*volt/mm),
    temperaturagas(Dim::temperaturagas){
        detectormens = new DetectorMens(this);
}

Detector::~Detector(){delete detectormens;}

// Construção do Detector

G4VPhysicalVolume* Detector::Construct()
{   
    DefineMaterials();

    return DefineVolumes();
}

// Construção de Materiais

void Detector::DefineMaterials() {
    
    auto NistManager = G4NistManager::Instance();

    NistManager->FindOrBuildMaterial("G4_Al");
    NistManager->FindOrBuildMaterial("G4_Galactic");

    G4Element* C = NistManager->FindOrBuildElement("C", false);
    G4Element* O = NistManager->FindOrBuildElement("O", false);
    G4Element* Ne = NistManager->FindOrBuildElement("Ne", false);
    G4Element* Ar = NistManager->FindOrBuildElement("Ar", false);

    DensidadeCO2 = 0.610*mg/cm3;

    G4Material* CO2 = new G4Material("CO2", DensidadeCO2, 2, kStateGas, Dim::temperaturagas, Dim::pressaogas);
    CO2->AddElement(C, 1);
    CO2->AddElement(O, 2);

    DensidadeGas = 0.816*mg/cm3;

    G4Material* NeCO2_90_10 = new G4Material("NeCO2_90_10", DensidadeGas, 2, kStateGas, Dim::temperaturagas, Dim::pressaogas);
    NeCO2_90_10->AddElement(Ne, 0.9);
    NeCO2_90_10->AddMaterial(CO2, 0.1);

    DensidadeGas2 = 1.345*mg/cm3;

    G4Material* ArCO2_70_30 = new G4Material("ArCO2_70_30", DensidadeGas2,2, kStateGas, Dim::temperaturagas, Dim::pressaogas);
    ArCO2_70_30->AddElement(Ar, 0.7);
    ArCO2_70_30->AddMaterial(CO2,0.3);

    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}

// Construção da Geometria

G4VPhysicalVolume* Detector::DefineVolumes(){

    // Definição do Mundo

    auto SMundo = new G4Box("SMundo", Dim::tamanhomundo, Dim::tamanhomundo, Dim::tamanhomundo);
    auto VLMundo = new G4LogicalVolume(SMundo, G4Material::GetMaterial("G4_Galactic"), "VLMundo");
    auto VFMundo = new G4PVPlacement(0, {0, 0, 0}, VLMundo, "Mundo", 0, false, 0);

    // Definição do Gás Ativo
    
    /*auto SGas = new G4Tubs("SGas", 0, 10.45*cm, Dim::comprimento, 0, twopi);
    auto VLGas = new G4LogicalVolume(SGas, G4Material::GetMaterial("ArCO2_70_30"), "VLGas");
    VFGas = new G4PVPlacement(0, {0, 0, 0}, VLGas, "Gás Ativo", VLMundo, false, 0);*/
    
    // Definição do Cátodo Externo de Aluminio

    auto SAlum = new G4Box("SAlum",0.5*m,0.5*m,0.5*m); 
    auto VLAlum = new G4LogicalVolume(SAlum, G4Material::GetMaterial("G4_Al"), "VAlum");
    VFAlum = new G4PVPlacement(0, {0.5*m, 0, 0}, VLAlum, "Bloco de Alumínio", VLMundo, false, 0);

    // Atributos Visuais

    VLMundo->SetVisAttributes(G4VisAttributes::Invisible);

    G4VisAttributes* VisAttBlue = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0));
    G4VisAttributes* VisAttGreen = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0));
    G4VisAttributes* VisAttRed = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0));
    G4VisAttributes* VisAttWhite = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0));

    VLAlum->SetVisAttributes(VisAttRed);

    // Região de Validade do Detector Sensível

    auto DS = new DetectorSensivel("Bloco de Aluminio", GetFieldIntensity());
    VLAlum->SetSensitiveDetector(DS);
    
    return VFMundo;
}

// Construtor do Campo

void Detector::ConstructSDandField(){

    auto campoEletrico = new Campo(intcamp);
    auto campoManager = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    auto campoEq = new G4EqMagElectricField(campoEletrico);
    auto passo = new G4DormandPrince745(campoEq, Dim::variaveis);
    auto integrador = new G4IntegrationDriver<G4DormandPrince745>(Dim::passoMin, passo, Dim::variaveis);
    auto caminho = new G4ChordFinder(integrador);

    campoManager->SetDetectorField(campoEletrico);
    campoManager->SetChordFinder(caminho);
}