#ifndef __GERBER_PARSER_H__
#define __GERBER_PARSER_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>

#include "gerber_types.h"

/* Define debug logger */
#define ANSI_COLOR_LOG      "I "
#define ANSI_COLOR_WARN     "W "
#define ANSI_COLOR_ERROR    "\x1b[31mE "
#define ANSI_COLOR_DEBUG    "\x1b[33mD "

#ifndef GERBER_LOGE
#define GERBER_LOGE(...)    printf(ANSI_COLOR_ERROR __VA_ARGS__); \
                            printf("\033[0m")
#endif

#ifndef GERBER_LOGW
#define GERBER_LOGW(...)    printf(ANSI_COLOR_WARN __VA_ARGS__); \
                            printf("\033[0m")
#endif

#define GERBER_APERTURE_MIN 10
#define GERBER_APERTURE_MAX 9999

Gerber_ParseStatus_t Gerber_Parser(Gerber_Parse_t *gerber);

#ifdef __cplusplus
}
#endif

#endif
