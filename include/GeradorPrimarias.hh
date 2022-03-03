#ifndef GeradorPrimarias_h
#define GeradorPrimarias_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4Event.hh"

class G4GeneralParticleSource;

class GeradorPrimarias : public G4VUserPrimaryGeneratorAction
{
    public:
        GeradorPrimarias();
        ~GeradorPrimarias();

        virtual void GeneratePrimaries(G4Event*);

    private:

        G4GeneralParticleSource*  mParticleGun;
};

#endif