#include "m_parser.h"
#include "gerber_types.h"

Gerber_ParseStatus_t M_Parser(Gerber_Parse_t *gerber) {
    NumberConvert getNum = Gerber_StringToInt(gerber->file.pointer);
    if(getNum.length > 0) {
        gerber->file.pointer += getNum.length;
        
    }
}