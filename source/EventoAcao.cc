#include "EventoAcao.hh"
#include "Analise.hh"
#include "Constantes.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"

EventoAcao::EventoAcao(RunAcao *runacao)
    : G4UserEventAction(), fElecOutpgamma(0), 
    fEnergamma(0.), RUNACAO(runacao), fEleEner(0.){
}

EventoAcao::~EventoAcao(){}

void EventoAcao::BeginOfEventAction(const G4Event* event){

    fElecOutpgamma = 0;
    fEleEner = 0.;
    fEnergamma = event->GetPrimaryVertex()->GetPrimary()->GetKineticEnergy()/eV;
}

void EventoAcao::EndOfEventAction(const G4Event* event){

    if(fEleEner != 0.){
        RUNACAO->AddEleEner(fEleEner);
    }
    RUNACAO->AddEOutG(fElecOutpgamma, fEnergamma);
    
}