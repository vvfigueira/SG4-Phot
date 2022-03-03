#ifndef EventoAcao_h
#define EventoAcao_h 1

#include "RunAcao.hh"

#include "G4UserEventAction.hh"
#include "globals.hh"

class EventoAcao : public G4UserEventAction
{
    public:
        
        EventoAcao(RunAcao* );
        virtual ~EventoAcao();

        virtual void  BeginOfEventAction(const G4Event*);
        virtual void    EndOfEventAction(const G4Event*);
        
        inline void AddElecOut(){fElecOutpgamma++;}
        inline double GetGEner(){return fEnergamma;}
        inline void AddEEner(double de){fEleEner += de;}

    private:

        int fElecOutpgamma;
        double fEnergamma, fEleEner;
        RunAcao * RUNACAO;
};

#endif