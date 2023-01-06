#include "parameter_parser.h"

Gerber_ParseStatus_t Parameter_Parser(Gerber_Parse_t *gerber) {
    Gerber_ParseStatus_t status = UnknownFormat;
    if((gerber->file.pointer[0] == 'F') && (gerber->file.pointer[1] == 'S')) {
        gerber->file.pointer += 2;
        if(gerber->file.pointer < gerber->file.endPointer) {
            status = FS_Parser(gerber);
        }
        else {
            return EndFile;
        }
        return status;
    }
    else if((gerber->file.pointer[0] == 'M') && (gerber->file.pointer[1] == 'O')) {
        gerber->file.pointer += 2;
        if(gerber->file.pointer < gerber->file.endPointer) {
            status = MO_Parser(gerber);
        }
        else {
            return EndFile;
        }
        return status;
    }
    else if((gerber->file.pointer[0] == 'A') && (gerber->file.pointer[1] == 'D')) {
        gerber->file.pointer += 2;
        if(gerber->file.pointer < gerber->file.endPointer) {
            status = AD_Parser(gerber);
        }
        else {
            return EndFile;
        }
        return status;
    }
    else if((gerber->file.pointer[0] == 'A') && (gerber->file.pointer[1] == 'M')) {
        gerber->file.pointer += 2;
        if(gerber->file.pointer < gerber->file.endPointer) {
            status = AM_Parser(gerber);
        }
        else {
            return EndFile;
        }
        return status;
    }
    else if((gerber->file.pointer[0] == 'S') && (gerber->file.pointer[1] == 'R')) {
        gerber->file.pointer += 2;
        return status;
    }
    else if((gerber->file.pointer[0] == 'L') && (gerber->file.pointer[1] == 'P')) {
        gerber->file.pointer += 2;
        return status;
    }
    else {
        return UnknownFormat;
    }
}
