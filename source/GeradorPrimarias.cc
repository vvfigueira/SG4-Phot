#include "GeradorPrimarias.hh"

#include "G4GeneralParticleSource.hh"

GeradorPrimarias::GeradorPrimarias()
    : G4VUserPrimaryGeneratorAction(), 
    mParticleGun( new G4GeneralParticleSource() ){}

GeradorPrimarias::~GeradorPrimarias(){ delete mParticleGun;}

void GeradorPrimarias::GeneratePrimaries(G4Event* anEvent)
{
    mParticleGun->GeneratePrimaryVertex(anEvent);   
}