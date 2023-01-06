#include "mo_parser.h"

Gerber_ParseStatus_t MO_Parser(Gerber_Parse_t *gerber) {
    Gerber_ParseStatus_t status = Busy;
    if(gerber->file.pointer > gerber->file.endPointer) {
        return EndFile;
    }
    /* IN | MM */
    if((gerber->file.pointer[0] == 'I') && (gerber->file.pointer[1] == 'N')) {
        gerber->file.pointer += 2;
        gerber->unit = GerberUnitInches;
    }
    else if((gerber->file.pointer[0] == 'M') && (gerber->file.pointer[1] == 'M')) {
        gerber->file.pointer += 2;
        gerber->unit = GerberUnitMillimeters;
    }
    else {
        gerber->file.pointer++;
        status = UnknownFormat;
        return status;
    }
    /* *% */
    if(gerber->file.pointer > gerber->file.endPointer) {
        return EndFile;
    }
    if(gerber->file.pointer[0] == '*') {
        gerber->file.pointer++;
        if(gerber->file.pointer > gerber->file.endPointer) {
            return EndFile;
        }
        if(gerber->file.pointer[0] == '%') {
            gerber->file.pointer++;
            return OK;
        }
        else {
            return UnknownFormat;            
        }
    }
    else {
        return UnknownFormat;            
    }
}