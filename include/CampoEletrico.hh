#ifndef CampoEletrico_h
#define CampoEletrico_h 1

#include "G4ElectroMagneticField.hh"

class Campo : public G4ElectroMagneticField {

    public:
        Campo(G4double intcamp);
        ~Campo();

        virtual void  GetFieldValue(const G4double Point[4], G4double *Bfield ) const override;
        virtual G4bool DoesFieldChangeEnergy() const override;
    
    private:

        double intensidade;
};
#endif