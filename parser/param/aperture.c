#include "aperture.h"

void ApertureMacro_Decode(Gerber_Parse_t *gerber, uint32_t DCode) {
    switch((uint32_t)DCode) {
        case Aperture_Circle : {
            break;
        }
        case Aperture_Rectangle : {
            break;
        }
        case Aperture_Obround : {
            break;
        }
        case Aperture_Polygon : {
            break;
        }
        case Aperture_Unknown : {
            break;
        }
        case Aperture_Macro : {
            break;
        }
    }
}

Aperture_t *Aperture_Find(Gerber_Parse_t *gerber, uint32_t DCode) {
    for(uint32_t indexAperture = 0; indexAperture < gerber->apertureCount; indexAperture++) {
        if(gerber->aperture[indexAperture].DCode == DCode) {
            return gerber->aperture + indexAperture;
        }
    }
}