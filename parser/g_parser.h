#ifndef __GERBER_G_PARSER_H__
#define __GERBER_G_PARSER_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include "gerber_types.h"

typedef enum {
    ErrorCode                       = -1,
    Move                            = 0,
    MoveLinearInterpolation         = 1,
    MoveCircularInterpolationCW     = 2,
    MoveCircularInterpolationCCW    = 3,
    IgnoreDataBlock                 = 4,
    LinearInterpolation10X          = 10,
    LinearInterpolation0_1X         = 11,
    LinearInterpolation0_01X        = 12,
    TurnOnPolygonAreaFill           = 36,
    TurnOffPolygonAreaFill          = 37,
    ToolPrepare                     = 54,
    SpecifyInches                   = 70,
    SpecifyMilimeters               = 71,
    Disable360CircularInterpolation = 74,
    Enable360CircularInterpolation  = 75,
    SpecifyAbsoluteFormat           = 90,
    SpecifyIncrementalFormat        = 91
} G_Command_t;

#ifdef __cplusplus
}
#endif

#endif
