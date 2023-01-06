#ifndef __GERBER_D_PARSER_H__
#define __GERBER_D_PARSER_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include "gerber_types.h"

typedef enum {
    DrawLineExposureOn  = 1,
    ExposureOff         = 2,
    FlashAperture       = 3
} D_Command_t;

#ifdef __cplusplus
}
#endif

#endif
