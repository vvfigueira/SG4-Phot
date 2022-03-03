#include "StepAcao.hh"
#include "Analise.hh"
#include "colors.hh"
#include "Constantes.hh"
#include "G4VProcess.hh"

StepAcao::StepAcao(const Detector* detec1, EventoAcao* event1)
    :G4UserSteppingAction(), detec12(detec1), event12(event1){
        std::ofstream ofs;
        ofs.open("EleMund.tsv", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        xFile.open("EleMund.tsv", std::ofstream::app);
    }

StepAcao::~StepAcao(){xFile.close();}

void StepAcao::UserSteppingAction(const G4Step* step){
    
    /*if(step->GetTrack()->GetParticleDefinition()->GetParticleName() == "e-" && 
        (step->IsFirstStepInVolume() && step->GetTrack()->GetVolume()->GetName() == "Bloco de Alumínio")){
            event12->AddElecpG();
        }*/
    
    if(step->IsFirstStepInVolume() && 
        (step->GetTrack()->GetParticleDefinition()->GetParticleName() == "e-" && 
        step->GetTrack()->GetVolume()->GetName() == "Mundo")){
            if(step->GetTrack()->GetKineticEnergy() != 0){
                xFile << step->GetTrack()->GetKineticEnergy()/eV << "\t" 
                    << event12->GetGEner() << "\n";
                event12->AddElecOut();
                event12->AddEEner(step->GetTrack()->GetKineticEnergy()/eV);
            }
    }
}