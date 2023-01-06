#include "ad_parser.h"
#include "gerber_types.h"

// static inline Gerber_ParseStatus_t AD_AddApertureCircle(Gerber_Parse_t *gerber, uint32_t DCode) {
//     gerber->aperture[DCode].name = Aperture_Circle;
//     /* Kiểm tra ký tự ',' */
//     if(gerber->file.pointer[0] != ',') {
//         return UnknownFormat;
//     }
//     else {
//         gerber->file.pointer++;
//     }
//     /* Lấy giá trị outsize diameter */
//     NumberConvert num = Gerber_StringToDouble(gerber->file.pointer);
//     if(num.length > 0) {
//         gerber->aperture[DCode].Cirle.OutsideDiameter = num.value;
//         gerber->file.pointer += num.length;
//     }
//     else {
//         return UnknownFormat;
//     }
//     /* Kiểm tra dấu ngăn cách - Nếu có */
//     if(gerber->file.pointer[0] == 'X') {
//         gerber->file.pointer++;
//         num = Gerber_StringToDouble(gerber->file.pointer);
//         if(num.length > 0) {
//             gerber->file.pointer += num.length;
//             gerber->aperture[DCode].Cirle.XHoleDimension = num.value;
//             /* Kiểm tra dấu ngăn cách - Nếu có */
//             if(gerber->file.pointer[0] == 'X') {
//                 gerber->file.pointer++;
//                 num = Gerber_StringToDouble(gerber->file.pointer);
//                 if(num.length > 0) {
//                     gerber->file.pointer += num.length;
//                     gerber->aperture[DCode].Cirle.YHoleDimension = num.value;
//                 }
//                 else {
//                     return UnknownFormat;
//                 }
//             }
//         }
//         else {
//             return UnknownFormat;
//         }
//     }
//     /* Kiểm tra ký tự * */
//     if(gerber->file.pointer[0] == '*') {
//         /* Kiểm tra ký tự kết thúc Block '%' */
//         if(gerber->file.pointer[0] == '%') {
//             return OK;
//         }
//         else {
//             return UnknownFormat;
//         }
//     }
//     return UnknownFormat;
// }

// static inline Gerber_ParseStatus_t AD_AddApertureRectangle(Gerber_Parse_t *gerber, uint32_t DCode) {
//     gerber->aperture[DCode].name = Aperture_Rectangle;
//     /* Kiểm tra ký tự ',' */
//     if(gerber->file.pointer[0] != ',') {
//         return UnknownFormat;
//     }
//     else {
//         gerber->file.pointer++;
//     }
//     /* Lấy giá trị X Dimension */
//     NumberConvert num = Gerber_StringToDouble(gerber->file.pointer);
//     if(num.length > 0) {
//         gerber->file.pointer += num.length;
//         gerber->aperture[DCode].Rectangle.XDimension = num.value;
//     }
//     else {
//         return UnknownFormat;
//     }
//     /* Lấy giá trị Y Dimension */
//     NumberConvert num = Gerber_StringToDouble(gerber->file.pointer);
//     if(num.length > 0) {
//         gerber->file.pointer += num.length;
//         gerber->aperture[DCode].Rectangle.YDimension = num.value;
//     }
//     else {
//         return UnknownFormat;
//     }
//     /* Kiểm tra dấu ngăn cách - Nếu có */
//     if(gerber->file.pointer[0] == 'X') {
//         gerber->file.pointer++;
//         num = Gerber_StringToDouble(gerber->file.pointer);
//         if(num.length > 0) {
//             gerber->file.pointer += num.length;
//             gerber->aperture[DCode].Rectangle.XHoleDimension = num.value;
//             /* Kiểm tra dấu ngăn cách - Nếu có */
//             if(gerber->file.pointer[0] == 'X') {
//                 gerber->file.pointer++;
//                 num = Gerber_StringToDouble(gerber->file.pointer);
//                 if(num.length > 0) {
//                     gerber->file.pointer += num.length;
//                     gerber->aperture[DCode].Rectangle.YHoleDimension = num.value;
//                 }
//                 else {
//                     return UnknownFormat;
//                 }
//             }
//         }
//         else {
//             return UnknownFormat;
//         }
//     }
//     /* Kiểm tra ký tự * */
//     if(gerber->file.pointer[0] == '*') {
//         /* Kiểm tra ký tự kết thúc Block '%' */
//         if(gerber->file.pointer[0] == '%') {
//             return OK;
//         }
//         else {
//             return UnknownFormat;
//         }
//     }
//     return UnknownFormat;
// }

// static inline Gerber_ParseStatus_t AD_AddApertureObround(Gerber_Parse_t *gerber, uint32_t DCode) {
//     gerber->aperture[DCode].name = Aperture_Obround;
//     /* Kiểm tra ký tự ',' */
//     if(gerber->file.pointer[0] != ',') {
//         return UnknownFormat;
//     }
//     else {
//         gerber->file.pointer++;
//     }
//     /* Lấy giá trị X Dimension */
//     NumberConvert num = Gerber_StringToDouble(gerber->file.pointer);
//     if(num.length > 0) {
//         gerber->file.pointer += num.length;
//         gerber->aperture[DCode].Obround.XDimension = num.value;
//     }
//     else {
//         return UnknownFormat;
//     }
//     /* Lấy giá trị Y Dimension */
//     NumberConvert num = Gerber_StringToDouble(gerber->file.pointer);
//     if(num.length > 0) {
//         gerber->file.pointer += num.length;
//         gerber->aperture[DCode].Obround.YDimension = num.value;
//     }
//     else {
//         return UnknownFormat;
//     }
//     /* Kiểm tra dấu ngăn cách - Nếu có */
//     if(gerber->file.pointer[0] == 'X') {
//         gerber->file.pointer++;
//         num = Gerber_StringToDouble(gerber->file.pointer);
//         if(num.length > 0) {
//             gerber->file.pointer += num.length;
//             gerber->aperture[DCode].Obround.XHoleDimension = num.value;
//             /* Kiểm tra dấu ngăn cách - Nếu có */
//             if(gerber->file.pointer[0] == 'X') {
//                 gerber->file.pointer++;
//                 num = Gerber_StringToDouble(gerber->file.pointer);
//                 if(num.length > 0) {
//                     gerber->file.pointer += num.length;
//                     gerber->aperture[DCode].Obround.YHoleDimension = num.value;
//                 }
//                 else {
//                     return UnknownFormat;
//                 }
//             }
//         }
//         else {
//             return UnknownFormat;
//         }
//     }
//     /* Kiểm tra ký tự * */
//     if(gerber->file.pointer[0] == '*') {
//         /* Kiểm tra ký tự kết thúc Block '%' */
//         if(gerber->file.pointer[0] == '%') {
//             return OK;
//         }
//         else {
//             return UnknownFormat;
//         }
//     }
//     return UnknownFormat;
// }

// static inline Gerber_ParseStatus_t AD_AddAperturePolygon(Gerber_Parse_t *gerber, uint32_t DCode) {
//     gerber->aperture[DCode].name = Aperture_Polygon;
//     /* Kiểm tra ký tự ',' */
//     if(gerber->file.pointer[0] != ',') {
//         return UnknownFormat;
//     }
//     else {
//         gerber->file.pointer++;
//     }
//     /* Lấy giá trị Outside Dimesion */
//     NumberConvert num = Gerber_StringToDouble(gerber->file.pointer);
//     if(num.length > 0) {
//         gerber->file.pointer += num.length;
//         gerber->aperture[DCode].Polygon.OutsizeDimension = num.value;
//     }
//     else {
//         return UnknownFormat;
//     }
//     /* Lấy giá trị Number Of Sides */
//     NumberConvert num = Gerber_StringToDouble(gerber->file.pointer);
//     if(num.length > 0) {
//         gerber->file.pointer += num.length;
//         gerber->aperture[DCode].Polygon.NumberOfSides = num.value;
//     }
//     else {
//         return UnknownFormat;
//     }
//     /* Kiểm tra dấu ngăn cách - Nếu có */
//     if(gerber->file.pointer[0] == 'X') {
//         gerber->file.pointer++;
//         num = Gerber_StringToDouble(gerber->file.pointer);
//         if(num.length > 0) {
//             gerber->file.pointer += num.length;
//             gerber->aperture[DCode].Polygon.DegreeOfRotataion = num.value;
//             /* Kiểm tra dấu ngăn cách - Nếu có */
//             if(gerber->file.pointer[0] == 'X') {
//                 gerber->file.pointer++;
//                 num = Gerber_StringToDouble(gerber->file.pointer);
//                 if(num.length > 0) {
//                     gerber->file.pointer += num.length;
//                     gerber->aperture[DCode].Polygon.XHoleDimension = num.value;
//                     /* Kiểm tra dấu ngăn cách - Nếu có */
//                     if(gerber->file.pointer[0] == 'X') {
//                         gerber->file.pointer++;
//                         num = Gerber_StringToDouble(gerber->file.pointer);
//                         if(num.length > 0) {
//                             gerber->file.pointer += num.length;
//                             gerber->aperture[DCode].Polygon.YHoleDimension = num.value;
//                         }
//                         else {
//                             return UnknownFormat;
//                         }
//                     }
//                 }
//                 else {
//                     return UnknownFormat;
//                 }
//             }
//         }
//         else {
//             return UnknownFormat;
//         }
//     }
//     /* Kiểm tra ký tự * */
//     if(gerber->file.pointer[0] == '*') {
//         /* Kiểm tra ký tự kết thúc Block '%' */
//         if(gerber->file.pointer[0] == '%') {
//             return OK;
//         }
//         else {
//             return UnknownFormat;
//         }
//     }
//     return UnknownFormat;
// }

/**
 * @brief Thêm mới Aperture và gán vào list
 * Thứ tự theo Dnn
 * 
 * @param gerber Gerber parse đang sử dụng
 * @return Gerber_ParseStatus_t 
 */
static inline Gerber_ParseStatus_t AD_AddNewAperture(Gerber_Parse_t *gerber, uint32_t DCode, char *aperture, Aperture_Type_t type) {
    if((gerber->aperture == 0) && (gerber->apertureCount == 0)) {
        gerber->aperture = malloc(sizeof(Aperture_t));
    }
    else {
        gerber->aperture = realloc(gerber->aperture, gerber->apertureCount * sizeof(Aperture_t));
    }
    if(gerber->aperture) {
        gerber->aperture[gerber->apertureCount].type = type;
        gerber->aperture[gerber->apertureCount].DCode = DCode;
        gerber->aperture[gerber->apertureCount].pointer = aperture;
        gerber->apertureCount++;
    }
}

/**
 * @brief Giải mã AD parameter
 * 
 * @param gerber Gerber Parse
 * @return Gerber_ParseStatus_t 
 */
Gerber_ParseStatus_t AD_Parser(Gerber_Parse_t *gerber) {
    Gerber_ParseStatus_t status = Busy;
    uint32_t DCode = 0;
    /* Giải mã D-Code cho aperture */
    if(gerber->file.pointer[0] == 'D') {
        gerber->file.pointer++;
        NumberConvert num = Gerber_StringToInt(gerber->file.pointer);
        DCode = num.value;
        if(num.length < 0) {
            return UnknownFormat;
        }
    }
    /* Kiểm tra Macro có sẵn nếu không phải Macro chuẩn */
    if(gerber->file.pointer[1] != ',') {
        uint8_t nameLength = 0;
        /* Lấy độ dài tên Macro */
        while((gerber->file.pointer + nameLength) < gerber->file.endPointer) {
            if(gerber->file.pointer[nameLength] != '*') {
                gerber->file.pointer++;
                nameLength++;
                if(nameLength >= 127) {
                    return UnknownFormat;
                }
            }
            else {
                break;
            }
        }
        /* Tìm Macro trong danh sách Macro */
        char *macroPointer = Gerber_MacroFind(gerber, gerber->file.pointer, nameLength);
        if(macroPointer == 0) {
            // Báo lỗi không tìm thấy Macro
            return UnknownFormat;
        }
        else {
            AD_AddNewAperture(gerber, DCode, macroPointer, Aperture_Macro);
        }
        return OK;
    }
    else if(gerber->file.pointer[1] == ',') {
        switch(gerber->file.pointer[0]) {
            case 'C': {
                gerber->file.pointer++;
                gerber->file.pointer++; // Bỏ qua ,
                AD_AddNewAperture(gerber, DCode, gerber->file.pointer, Aperture_Circle);
                break;
            }
            case 'R': {
                gerber->file.pointer++;
                gerber->file.pointer++; // Bỏ qua ,
                AD_AddNewAperture(gerber, DCode, gerber->file.pointer, Aperture_Circle);
                break;
            }
            case 'O': {
                gerber->file.pointer++;
                gerber->file.pointer++; // Bỏ qua ,
                AD_AddNewAperture(gerber, DCode, gerber->file.pointer, Aperture_Circle);
                break;
            }
            case 'P': {
                gerber->file.pointer++;
                gerber->file.pointer++; // Bỏ qua ,
                AD_AddNewAperture(gerber, DCode, gerber->file.pointer, Aperture_Circle);
                break;
            }
            default: {
                gerber->file.pointer++;
                gerber->file.pointer++; // Bỏ qua ,
                AD_AddNewAperture(gerber, DCode, gerber->file.pointer, Aperture_Circle);
                break;
            }
        }
    }
    else {
        return UnknownFormat;
    }
}
