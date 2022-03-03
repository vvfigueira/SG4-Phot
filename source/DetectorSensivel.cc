#include "DetectorSensivel.hh"
#include "DetectorMens.hh"
#include "Detector.hh"
//#include "Analise.hh"

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

#include "G4VProcess.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ios.hh"
#include "G4Track.hh"
#include "G4StepStatus.hh"

DetectorSensivel::DetectorSensivel(const G4String &name,G4double intensidade) 
    : G4VSensitiveDetector(name), campoInt(intensidade){}

DetectorSensivel::~DetectorSensivel(){}

G4bool DetectorSensivel::ProcessHits(G4Step*aStep, G4TouchableHistory*ROhist){

    /*int ne = 0;

    pName = aStep->GetTrack()->GetParticleDefinition()->GetParticleName();
    std::string PName = aStep->GetTrack()->GetStep()->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
    energia = aStep->GetPreStepPoint()->GetKineticEnergy();
    nVol = aStep->GetPreStepPoint()->GetPhysicalVolume()->GetName();
    pressao = aStep->GetTrack()->GetVolume()->GetMotherLogical()->GetMaterial()->GetPressure();
    temperatura = aStep->GetTrack()->GetVolume()->GetMotherLogical()->GetMaterial()->GetTemperature();
    bool fStep = aStep->GetTrack()->GetStep()->IsFirstStepInVolume();
    double ed = aStep->GetTrack()->GetStep()->GetTotalEnergyDeposit();

    std::ofstream xFile ("EleEner.tsv", std::ofstream::app);
    std::ofstream aFile ("NPhot.tsv", std::ofstream::app);
    std::ofstream bFile ("DPhot.tsv", std::ofstream::app);
    std::ofstream cFile ("DEle.tsv", std::ofstream::app);
    std::ofstream dFile ("PName.tsv", std::ofstream::app);

    //xFile << energia/eV << "\n";
    dFile << pName << "\t" << PName << "\n";*/

    return 0;
}