#include "RunAcao.hh"
#include "GeradorPrimarias.hh"
#include "Detector.hh"
#include "Analise.hh"
#include "Constantes.hh"

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"

RunAcao::RunAcao()
    : G4UserRunAction(), EleOutpG(0), energam(0.), fEleEner(0.), fEleEnerMed(0.){
        std::ofstream ofs;
        ofs.open("PhotFrac.tsv", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        ofs.open("EleMundMed.tsv", std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        dFile.open("EleMundMed.tsv", std::ofstream::app);
        cFile.open("PhotFrac.tsv", std::ofstream::app);
}

RunAcao::~RunAcao(){cFile.close();dFile.close();}

void RunAcao::BeginOfRunAction(const G4Run* run){
    EleOutpG = 0;
    fEleEner = 0.;
    fEleEnerMed = 0.;
}

void RunAcao::EndOfRunAction(const G4Run* run){

    if(EleOutpG != 0) fEleEnerMed = fEleEner/(EleOutpG*1.0);
    if(fEleEnerMed != 0){
        dFile << fEleEnerMed << "\t" << energam << "\n";
    }
    double res = EleOutpG/(run->GetNumberOfEvent()*1.0);
    if(res != 0){
        cFile << res << "\t" << energam << "\n";
    }
}