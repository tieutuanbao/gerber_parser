#include "fs_parser.h"
#include "gerber_types.h"

//
// TODO: Tiếp tục lấy tham số FS Parser theo cấu trúc Gerber
//
Gerber_ParseStatus_t FS_Parser(Gerber_Parse_t *gerber) {
    /* L | T */
    while(1) {
        if(gerber->file.pointer > gerber->file.endPointer) {
            return EndFile;
        }
        if(gerber->file.pointer[0] == 'L') {
            gerber->FS.format.trailing = false;
            gerber->file.pointer++;
            break;
        }
        else if(gerber->file.pointer[0] == 'T') {
            gerber->FS.format.trailing = true;
            gerber->file.pointer++;
            break;
        }
        else {
            gerber->file.pointer++;
            return UnknownFormat;
        }
    }
    /* A | I */
    while(1) {
        if(gerber->file.pointer > gerber->file.endPointer) {
            return EndFile;
        }
        if(gerber->file.pointer[0] == 'A') {
            gerber->FS.incremental = false;
            gerber->file.pointer++;
            break;
        }
        else if(gerber->file.pointer[0] == 'I') {
            gerber->FS.incremental = true;
            gerber->file.pointer++;
            break;
        }
        else {
            gerber->file.pointer++;
            return UnknownFormat;
        }
    }
    /* N | G */
    while(1) {
        if(gerber->file.pointer > gerber->file.endPointer) {
            return EndFile;
        }
        if(gerber->file.pointer[0] == 'N') {
            gerber->file.pointer++;
        }
        else if(gerber->file.pointer[0] == 'G') {
            gerber->file.pointer++;
        }
        else {
            break;
        }
    }
    /* X */
    if(gerber->file.pointer > gerber->file.endPointer) {
        return EndFile;
    }
    if(gerber->file.pointer[0] == 'X') {
        gerber->file.pointer++;
        gerber->FS.format.XInt = gerber->file.pointer[0] - '0';
        gerber->file.pointer++;
        gerber->FS.format.XDec = gerber->file.pointer[0] - '0';
        gerber->file.pointer++;
    }
    else {
        gerber->file.pointer++;
        return UnknownFormat;
    }
    /* Y */
    if(gerber->file.pointer > gerber->file.endPointer) {
        return EndFile;
    }
    if(gerber->file.pointer[0] == 'Y') {
        gerber->file.pointer++;
        gerber->FS.format.YInt = gerber->file.pointer[0] - '0';
        gerber->file.pointer++;
        gerber->FS.format.YDec = gerber->file.pointer[0] - '0';
        gerber->file.pointer++;
    }
    else {
        gerber->file.pointer++;
        return UnknownFormat;
    }
    /* D | M */
    while(1) {
        if(gerber->file.pointer > gerber->file.endPointer) {
            return EndFile;
        }
        if(gerber->file.pointer[0] == 'D') {
            gerber->file.pointer++;
        }
        else if(gerber->file.pointer[0] == 'M') {
            gerber->file.pointer++;
        }
        else {
            break;
        }
    }
    /* * */
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
        return UnknownFormat;
    }
    else {
        gerber->file.pointer++;
        return UnknownFormat;
    }
    return OK;
}
