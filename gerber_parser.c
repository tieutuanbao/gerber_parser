#include "gerber_parser.h"
#include <stdlib.h>
/* ----------------------------------------------------------------------
                            Support Function
---------------------------------------------------------------------- */
static inline char Gerber_GetChar(Gerber_File_t *gerberFile) {
    if(gerberFile->currentPointer >= gerberFile->endPointer) {
        return GERBER_END_OF_FILE;
    }
    return (char *)(gerberFile->currentPointer++);
}

static inline NumberConvert Gerber_GetInt(char *dataPointer) {
    NumberConvert returnResult;
    char *endPointer;
    returnResult.value = strtol(dataPointer, &endPointer, 10);
    if (errno) {
	    GERBER_LOGE("Failed to read integer");
        returnResult.length = 0;
        return returnResult;
    }
    returnResult.length = endPointer - dataPointer;
    return returnResult;
}

static inline void G_parser(Gerber_File_t *gerberFile) {
    NumberConvert result = Gerber_GetInt(gerberFile);
    char readChar;
    if(result.length > 0) {
        gerberFile->currentPointer += result.length;
        switch ((uint8_t)result.value) {
            case 0: {
                gerberFile->stats.G0++;
                break;
            }
            case 1: {
                gerberFile->state.interpolation = Gerber_Interpolation_LinearX1;
                gerberFile->stats.G1++;
                break;
            }
            case 2: {
                gerberFile->state.interpolation = Gerber_Interpolation_CW_Circular;
                gerberFile->stats.G2++;
                break;
            }
            case 3: {
                gerberFile->state.interpolation = Gerber_Interpolation_CCW_Circular;
                gerberFile->stats.G3++;
                break;
            }
            case 4: {
                /* Bỏ qua mọi ký tự cho đến * */
                while ((readChar = Gerber_GetChar(gerberFile)) != GERBER_END_OF_FILE) {
                    if (readChar == '*') {
                        return;
                    }
                }
                gerberFile->stats.G4++;
                return OK;
            }
            case 10: {
                gerberFile->state.interpolation = Gerber_Interpolation_LinearX10;
                gerberFile->stats.G10++;
                break;
            }
            case 11: {
                gerberFile->state.interpolation = Gerber_Interpolation_LinearX01;
                gerberFile->stats.G11++;
                break;
            }
            case 12: {
                gerberFile->state.interpolation = Gerber_Interpolation_LinearX001;
                gerberFile->stats.G12++;
                break;
            }
            case 36: {
                gerberFile->state.prevInterpolation = gerberFile->state.interpolation;
                gerberFile->state.interpolation = Gerber_Interpolation_Polygon_Start;
                gerberFile->state.changed = 1;
                gerberFile->stats.G36++;
                break;
            }
            case 37: {
                gerberFile->state.interpolation = Gerber_Interpolation_Polygon_End;
                gerberFile->state.changed = 1;
                gerberFile->stats.G37++;
                break;
            }
            case 54: {
                GERBER_LOGW("G54 is superfluous and deprecated");
                gerberFile->stats.G54++;
                break;
            }
            case 70: {
                if(gerberFile->currentPointer[0] != '*') {
                    return UnknownFormat;
                }
                // gerberFile->state. = GerberUnitInches;
                gerberFile->stats.G70++;
                break;
            }
            case 71: {
                // gerberFile->unit = GerberUnitMillimeters;
                gerberFile->stats.G71++;
                break;
            }
            case 74: {
                gerberFile->state.multiquadrant = false;
                gerberFile->stats.G74++;
                break;
            }
            case 75: {
                gerberFile->state.multiquadrant = true;
                gerberFile->stats.G75++;
                break;
            }
            case 90: {
                gerberFile->state.coordinateFormat = Gerber_Coordinate_Absolute;
                gerberFile->stats.G90++;
                break;
            }
            case 91: {
                gerberFile->state.coordinateFormat = Gerber_Coordinate_Incremental;
                gerberFile->stats.G91++;
                break;
            }
            default:
                GERBER_LOGW("G-Code unknown");
                gerberFile->stats.G_unknown++;
                return;
        }
    }
}

static inline void D_Parser(Gerber_File_t *gerberFile) {
    NumberConvert result = Gerber_GetInt(gerberFile);
    if(result.length > 0) {
        gerberFile->currentPointer += result.length;
        switch((uint32_t)result.value) {
            case 1 : {
                gerberFile->state.apertureState = Gerber_ApertureState_On;
	            gerberFile->state.changed = 1;
                gerberFile->stats.D1++;
                break;
            }
            case 2 : {
                gerberFile->state.apertureState = Gerber_ApertureState_Off;
	            gerberFile->state.changed = 1;
                gerberFile->stats.D2++;
                break;
            }
            case 3 : {
                gerberFile->state.apertureState = Gerber_ApertureState_Off;
	            gerberFile->state.changed = 1;
                gerberFile->stats.D3++;
                break;
            }
            default : {
                if((result.value >= GERBER_APERTURE_MIN) && (result.value <= GERBER_APERTURE_MAX)) {
                    gerberFile->state.currAperture = result.value;
                }
                else {
                    GERBER_LOGW("Aperture is out of size. D%d\r\n", result.value);
                }
	            gerberFile->state.changed = 0;
                break;
            }
        }
    }
}
static inline int M_Parser(Gerber_File_t *gerberFile) {
    NumberConvert result = Gerber_GetInt(gerberFile);
    if(result.length > 0) {
        gerberFile->currentPointer += result.length;
        switch((uint32_t)result.value) {
            case 0 : {
                gerberFile->stats.M0++;
	            return 1;
                break;
            }
            case 1 : {
                gerberFile->stats.M1++;
	            return 2;
                break;
            }
            case 2 : {
                gerberFile->stats.M2++;
	            return 3;
                break;
            }
            default : {
                gerberFile->stats.M_unknown++;
                return 0;
                break;
            }
        }        
    }
}
/**
 * @brief Thực thi lệnh gerberFile
 * @param gerberFile File gerberFile đang dùng
 * 
 */
Gerber_ParseStatus_t Gerber_Exec(Gerber_Parse_t *gerberFile) {    
    switch((uint32_t)gerberFile->currentAperture->type) {
        case Aperture_Circle : {
            // gerberFile->Primitive_Circle();
            break;
        }
        case Aperture_Rectangle : {
            break;
        }
        case Aperture_Obround : {
            break;
        }
        case Aperture_Polygon : {
            break;
        }
        case Aperture_Unknown : {
            break;
        }
        case Aperture_Macro : {
            break;
        }
    }
}


static bool Gerber_AddTrailingZeros(int *coord, int omitted_num,
		gerbv_format_t *format)
{
	if (format
	&&  format->omit_zeros == GERBV_OMIT_ZEROS_TRAILING
	&&  omitted_num > 0) {
		for (int i = 0; i < omitted_num; i++)
			*coord *= 10;

		return TRUE;
	}

	return FALSE;
} 

/**
 * @brief Chuyển đổi chuỗi ký tự sang số thực
 * 
 * @return uint8_t độ dài số thực, bao gồm dấu ngăn cách [.]
 */
bool Gerber_ParserFile(Gerber_File_t *gerberFile) {
    char currentChar = 0;
    bool foundEOF = false;
    /* Parse Block */
    while((currentChar = Gerber_GetChar(gerberFile)) != GERBER_END_OF_FILE) {
        switch(currentChar) {
            case 'G': { // Parse G-Code
                G_parser(gerberFile);
                break;
            }
            case 'D': { // Parse D-Code
                D_Parser(gerberFile);
                break;
            }
            case 'M': { // Parse M-Code
                switch(M_Parser(gerberFile)) {
                    case 1 :
                    case 2 :
                    case 3 :
                        foundEOF = true;
                        break;
                    default : {
                        GERBER_LOGW("Unknown M code\r\n");
                        break;
                    }
                }
                break;
            }
            case 'X': {
                gerberFile->stats.X++;
                NumberConvert result = Gerber_GetInt(gerberFile);
                if(result.length > 0) {
                    gerberFile->currentPointer += result.length;
                    switch((uint32_t)result.value) {

                    }
                break;
            }
            case 'Y': {
                NumberConvert num = Gerber_StringToDouble(gerberFile->endPointer);
                if(num.length > 0) {
                    gerberFile->currentPointer += num.length;
                    gerberFile->oldY = gerberFile->Y;
                    gerberFile->Y = num.value;
                }
                else {
                    // Trả về lỗi, Y không mang giá trị
                    return UnknownFormat;
                }
                break;
            }
            case '%': {
                Parameter_Parser(gerberFile);
                break;
            }
            case '*': {
                /* Thực thi lệnh */
                
                break;
            }
            case 0: {
                break;
            }
            default: {
                break;
            }
        }
    }
}
