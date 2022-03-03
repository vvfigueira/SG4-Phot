#ifndef RunAcao_h
#define RunAcao_h 1

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "fstream"

class RunAcao : public G4UserRunAction
{
    public:
        RunAcao();
        virtual ~RunAcao();

        virtual void BeginOfRunAction(const G4Run*);
        virtual void EndOfRunAction(const G4Run*);

        inline void AddEOutG(int de, double ener){EleOutpG+=de; energam = ener;}
        inline void AddEleEner(double de){fEleEner+=de;}

    private:

        int EleOutpG;
        double energam, fEleEner, fEleEnerMed;
        std::ofstream cFile, dFile;
};

#endif