#include "am_parser.h"

static inline Gerber_ParseStatus_t AM_AddNewMacro(Gerber_Parse_t *gerber, char *macroPointer) {
    if((gerber->macro == 0) && (gerber->macroCount == 0)) {
        gerber->macro = malloc(sizeof(void(*)));
    }
    else {
        gerber->macro = realloc(gerber->aperture, gerber->apertureCount * sizeof(void(*)));
    }
    if(gerber->macro) {
        gerber->macro[gerber->apertureCount] = macroPointer;
        gerber->apertureCount++;
    }
}

Gerber_ParseStatus_t AM_Parser(Gerber_Parse_t *gerber) {
    char *macroPointer;
    uint8_t macroNameLen = 0;
    macroPointer = gerber->file.pointer;
    /* Lấy tên Macro */
    while(1) {
        if(gerber->file.pointer >= gerber->file.endPointer) {
            return UnknownFormat;
        }
        macroNameLen++;
        gerber->file.pointer++;
        if(gerber->file.pointer >= gerber->file.endPointer) {
            return UnknownFormat;
        }
        if(macroNameLen > 127) {
            // Cảnh báo độ dài Macro lớn hơn tiêu chuẩn
            return UnknownFormat;
        }
        if(gerber->file.pointer[0] == '*') {
            break;
        }
    }
    /* Bỏ qua khoảng trắng hoặc xuống dòng */
    while(1) {
        if(gerber->file.pointer >= gerber->file.endPointer) {
            return EndFile;
        }
        if(gerber->file.pointer[0] == '\n') {
            gerber->file.pointer++;
            break;
        }
        gerber->file.pointer++;
    }
    /* Lấy macro */
    while(1) {
        if(gerber->file.pointer >= gerber->file.endPointer) {
            return EndFile;
        }
        /* Ký tự % kết thúc Macro */
        if(gerber->file.pointer[0] == '%') {
            gerber->file.pointer++;
            AM_AddNewMacro(gerber, macroPointer);
            return OK;
        }
        gerber->file.pointer++;
    }
}