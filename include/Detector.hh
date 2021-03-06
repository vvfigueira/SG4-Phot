#ifndef Detector_h
#define Detector_h 1

#include "DetectorMens.hh"

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class DetectorMens;

class Detector : public G4VUserDetectorConstruction
{
    public:
        Detector();
        virtual ~Detector();

        const G4VPhysicalVolume* GetVFGas() const {return VFGas;};
        const G4VPhysicalVolume* GetVFTubo() const {return VFAlum;};

        inline void SetGasPressure(G4double d){pressaogas = d;};
        inline double GetGasPressure(){return pressaogas;};

        inline void SetGasTemperature(G4double d){temperaturagas = d;};
        inline double GetGasTemperature(){return temperaturagas;};
        
        inline void SetFieldIntensity(G4double d){intcamp = d;};
        inline double GetFieldIntensity(){return intcamp;};

        virtual void ConstructSDandField();

        virtual G4VPhysicalVolume* Construct() override;

    private:

        void DefineMaterials();
        G4VPhysicalVolume* DefineVolumes();

        G4VPhysicalVolume* VFGas, *VFAlum;

        DetectorMens* detectormens;

        G4double intcamp, temperaturagas, pressaogas, DensidadeGas, 
            DensidadeGas2, DensidadeCO2;

};

#endif