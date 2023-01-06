#ifndef __GERBER_TYPES_H__
#define __GERBER_TYPES_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
#include <stdbool.h>

#define GERBER_END_OF_FILE  -1

typedef struct {
    double value;
    uint8_t length;
} NumberConvert;

typedef enum {
    OK,
    UnknownFormat,
    EndFile,
    Busy
} Gerber_ParseStatus_t;

typedef enum {
    GerberUnitInches,
    GerberUnitMillimeters
} Gerber_Unit;

/**
 * @brief ------------ Format Statement ------------
 */
typedef struct {
    struct {
        bool trailing;
        uint32_t XInt;
        uint32_t XDec;
        uint32_t YInt;
        uint32_t YDec;
    } format;
    bool incremental;
} FS_Param_t;

/**
 * @brief ------------ Aperture ------------
 */
typedef enum {
    AM_Circle,
    AM_LineVector,
    AM_LineCenter,
    AM_LineLowerLeft,
    AM_OutLine,
    AM_Polygon,
    AM_Moire,
    AM_Thermal,
    AM_EndOfFile
} ApertureMacro_PrimitiveDescription_t;

typedef struct {
    ApertureMacro_PrimitiveDescription_t description;
    struct {
        double X;
        double Y;
    } arg[100];
} ApertureMacro_Primitive_t;


#include "aperture.h"
#include "fs_parser.h"
#include "mo_parser.h"
#include "ad_parser.h"
#include "am_parser.h"
#include "g_parser.h"
#include "d_parser.h"
#include "m_parser.h"
#include "parameter_parser.h"

typedef struct Gerber_Cirseg {
    double cp_x;
    double cp_y;
    double width;
    double height;
    double angle1;
    double angle2;
} Gerber_Cirseg_t;

typedef struct Gerber_RenderSize {
    double left;
    double right;
    double bottom;
    double top;
} Gerber_RenderSize_t;

typedef enum Gerber_ApertureState {
    Gerber_ApertureState_Off,
    Gerber_ApertureState_On,
    Gerber_ApertureState_Flash
} Gerber_ApertureState_t;

typedef enum Gerber_Interpolation {
    Gerber_Interpolation_LinearX1,
    Gerber_Interpolation_LinearX10,
    Gerber_Interpolation_LinearX01,
    Gerber_Interpolation_LinearX001,
    Gerber_Interpolation_CW_Circular,
    Gerber_Interpolation_CCW_Circular,
    Gerber_Interpolation_Polygon_Start,
    Gerber_Interpolation_Polygon_End,
    Gerber_Interpolation_Deleted
} Gerber_Interpolation_t;

typedef enum Gerber_Coordinate {
    Gerber_Coordinate_Absolute,
    Gerber_Coordinate_Incremental
} Gerber_Coordinate_t;

typedef struct Gerber_NetState {
    double startX;
    double startY;
    double stopX;
    double stopY;
    Gerber_RenderSize_t boundingBox;
    int aperture;
    Gerber_ApertureState_t apertureState;
    Gerber_Interpolation_t interpolation;
    Gerber_Cirseg_t* cirseg;
    struct gerbv_net* next;
    gerbv_layer_t* layer;
    gerbv_netstate_t* state;
} Gerber_NetState_t;

typedef struct {
    int currentX;
    int currentY;
    int prevX;
    int prevY;
    int deltaX;
    int deltaY;
    int currAperture;
    int changed;
    Gerber_ApertureState_t apertureState;
    Gerber_Interpolation_t interpolation;
    Gerber_Interpolation_t prevInterpolation;
    bool multiquadrant;
    Gerber_Coordinate_t coordinateFormat;
} Gerber_State_t;

typedef struct {
    int layer_count;
    int G0;
    int G1;
    int G2;
    int G3;
    int G4;
    int G10;
    int G11;
    int G12;
    int G36;
    int G37;
    int G54;
    int G55;
    int G70;
    int G71;
    int G74;
    int G75;
    int G90;
    int G91;
    int G_unknown;

    int D1;
    int D2;
    int D3;
/*    GHashTable *D_user_defined; */
    int D_unknown;
    int D_error;

    int M0;
    int M1;
    int M2;
    int M_unknown;

    int X;
    int Y;
    int I;
    int J;

    /* Must include % RS-274 codes */
    int star;
    int unknown;
} Gerber_Statistics_t;

typedef struct {
    struct {
        char *pointer;
        char *endPointer;
    } file;
    size_t currentLine;
    uint32_t NCode;
    /** @brief Aperture Macro
     *  @param macro Danh sách con trỏ, trỏ đến macro trong file
     *  @param
     */
    void **macro;
    uint16_t macroCount;
    /** @brief Danh sách Aperture map vào Dnn
     *  @param 
     */
    Aperture_t *aperture;
    uint16_t apertureCount;
    /**
     * @brief Aperture đang dùng 
     */
    Aperture_t *currentAperture;
    /**
     * @brief D code đang dùng 
     */
    uint32_t currentDCode;
    /**
     * @brief Định dạng tọa độ 
     */
    FS_Param_t FS;
    /**
     * @brief Định dạng khoảng cách (inch hoặc met)
     */
    Gerber_Unit unit;
    /**
     * @brief Callback draw 
     */
    Primitive_Circle_t Primitive_Circle;
    Primitive_LineCenter_t Primitive_LineCenter;
    Primitive_LineBotLeft_t Primitive_LineBotLeft;
    Primitive_Outline_t Primitive_Outline;
    Primitive_Polygon_t Primitive_Polygon;
    Primitive_Moire_t Primitive_Moire;
    Primitive_Thermal_t Primitive_Thermal;
    
} Gerber_Parse_t;

typedef struct Gerber_File {
    char *beginPointer;
    char *currentPointer;
    char *endPointer;
    Gerber_State_t **state;
    Gerber_Statistics_t stats;
} Gerber_File_t;

Gerber_ParseStatus_t Gerber_GotoNewLine(Gerber_Parse_t *gerber);
NumberConvert Gerber_StringToInt(char *numInString);
NumberConvert Gerber_StringToDouble(char *numInString);
char *Gerber_MacroFind(Gerber_Parse_t *gerber, char *macroName, uint8_t nameLength);

Aperture_t *Aperture_Find(Gerber_Parse_t *gerber, uint32_t DCode);

Gerber_ParseStatus_t Parameter_Parser(Gerber_Parse_t *gerber);
Gerber_ParseStatus_t FS_Parser(Gerber_Parse_t *gerber);
Gerber_ParseStatus_t MO_Parser(Gerber_Parse_t *gerber);
Gerber_ParseStatus_t AD_Parser(Gerber_Parse_t *gerber);
Gerber_ParseStatus_t AM_Parser(Gerber_Parse_t *gerber);

Gerber_ParseStatus_t G_parser(Gerber_Parse_t *gerber);
Gerber_ParseStatus_t D_Parser(Gerber_Parse_t *gerber);
Gerber_ParseStatus_t M_Parser(Gerber_Parse_t *gerber);

#ifdef __cplusplus
}
#endif

#endif
