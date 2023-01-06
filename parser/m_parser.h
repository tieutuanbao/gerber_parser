#ifndef __GERBER_M_PARSER_H__
#define __GERBER_M_PARSER_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include "gerber_types.h"

typedef enum {
    ProgramStop     = 1,
    OptionalStop    = 2,
    EndOfProgram    = 3
} M_Command_t;

#ifdef __cplusplus
}
#endif

#endif