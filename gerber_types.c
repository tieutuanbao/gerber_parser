#include "gerber_types.h"

Gerber_ParseStatus_t Gerber_GotoNewLine(Gerber_Parse_t *gerber) {
    /* Đi đến dòng mới */
    while(1) {
        gerber->file.pointer++;
        switch(gerber->file.pointer[0]) {
            case '\n' : {
                return OK;
            }
            case ' ':
            case '\t':
            case '\r': {
                break;
            }
            default: {
                return EndFile;
            }
        }
    }
}

NumberConvert Gerber_StringToDouble(char *numInString) {
    NumberConvert returnConvert;
    uint32_t divDec = 1;
    bool isRealNum = false;
    returnConvert.value = 0;
    returnConvert.length = 0;
    while((numInString[0] >= '0') && (numInString[0] <= '9')) {
        if(isRealNum == true) {
            divDec *= 10;
        }
        returnConvert.value *= 10;
        returnConvert.value += numInString[0] - '0';
        numInString++;
        returnConvert.length++;
        if((numInString[0] == '.')) {
            if(isRealNum == true) {
                returnConvert.length = 0;
                return returnConvert;
            }
            isRealNum = true;
            numInString++;
        }
    }
    returnConvert.value /= (double)divDec;
    return returnConvert;
}


char *Gerber_MacroFind(Gerber_Parse_t *gerber, char *macroName, uint8_t nameLength) {
    for(uint32_t indexMacro = 0; indexMacro < gerber->macroCount; indexMacro++) {
        if(memcmp(gerber->macro[indexMacro], macroName, nameLength) == 0) {
            if((gerber->macro[nameLength] == '*') && (macroName[nameLength] == '*')) {
                return gerber->macro[indexMacro];
            }
        }
    }
    return 0;
}