#include "math.h"

#include "CampoEletrico.hh"
#include "Constantes.hh"

#include "G4SystemOfUnits.hh"
#include "globals.hh"

using namespace CLHEP;

// Definindo a Classe Campo como Campo Elétrico

Campo::Campo(G4double intcamp): intensidade(intcamp)
    {

}

Campo::~Campo(){
    
}

G4bool Campo::DoesFieldChangeEnergy() const{
    return true;
}

// Definição da Classe Campo

void Campo::GetFieldValue(const G4double Point[4], G4double field[6]) const{

    field[0]=0.*tesla;
    field[1]=0.*tesla;
    field[2]=0.*tesla;
    field[3]=intensidade;
    field[4]=0.*volt/mm;
    field[5]=0.*volt/mm;

}