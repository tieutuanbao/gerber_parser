#ifndef __APERTURE_H__
#define __APERTURE_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

/**
 * @brief Hàm tạo hình tròn (Có fill)
 * @param exposure on/off phơi sáng
 * @param diameter Đường kính
 * @param x vị trí x của tâm
 * @param y vị trí y của tâm
 */
typedef void (*Primitive_Circle_t)(int8_t exposure, double diameter, double x, double y);
/**
 * @brief Hàm tạo Line theo tâm, hình dạng chữ nhật
 *                              width
 *           ____________________________________________
 *          |                                            |
 *  height  |                     C                      |
 *          |____________________________________________|
 * 
 *  C is center point
 * 
 * @param exposure on/off phơi sáng
 * @param width Chiều rộng của line
 * @param height Chiều cao của Line
 * @param x vị trí x của tâm
 * @param y vị trí y của tâm
 * @param degree góc xoay theo tâm (+ = xoay ngược chiều kim đồng hồ, - = xoay theo chiều kim đồng hồ)
 */
typedef void (*Primitive_LineCenter_t)(int8_t exposure, double width, double height, double x, double y, double degree);
/**
 * @brief Hàm tạo Line theo điểm Bottom Left, hình dạng chữ nhật
 *                              width
 *           ____________________________________________
 *          |                                            |
 *  height  |                                            |
 *          |____________________________________________|
 *         BL
 *  BL is Bottom Left
 * 
 * @param exposure on/off phơi sáng
 * @param n Số điểm của outline
 * @param width Chiều rộng của line
 * @param height Chiều cao của Line
 * @param x vị trí x của Bottom Left
 * @param y vị trí y của Bottom Left
 * @param degree góc xoay theo điểm Bottom Left (+ = xoay ngược chiều kim đồng hồ, - = xoay theo chiều kim đồng hồ)
 */
typedef void (*Primitive_LineBotLeft_t)(int8_t exposure, double width, double height, double x, double y, double degree);
/**
 * @brief Hàm tạo outline dựa theo các điểm, có thể khép kín hoặc không, nếu khép kín thì điểm đầu và điểm cuối phải có cùng tọa độ
 * @param exposure on/off phơi sáng
 * @param nPoints Số điểm của outline, không tính điểm bắt đầu
 * @param x tọa độ X của điểm bắt đầu
 * @param y tọa độ Y của điểm bắt đầu
 * @param points con trỏ danh sách điểm, quy ước: xPoint = points[i], yPoint = points[i + 1]
 * @param degree góc xoay theo điểm Bottom Left (+ = xoay ngược chiều kim đồng hồ, - = xoay theo chiều kim đồng hồ)
 */
typedef void (*Primitive_Outline_t)(int8_t exposure, uint32_t nPoints, double x, double y, double *points, double degree);
/**
 * @brief Hàm tạo Polygon khép kín theo tâm
 * @param exposure on/off phơi sáng
 * @param nVertices Số đỉnh của Polygon [3 - 10]
 * @param x tọa độ X của tâm
 * @param y tọa độ Y của tâm
 * @param diameter Đường kính của Polygon, đường được tạo bởi 1 đỉnh và đi qua tâm
 * @param degree góc xoay theo điểm Bottom Left (+ = xoay ngược chiều kim đồng hồ, - = xoay theo chiều kim đồng hồ)
 */
typedef void (*Primitive_Polygon_t)(int8_t exposure, uint32_t nPoints, double x, double y, double *points, double degree);
/**
 * @brief Hàm tạo hình Moiré: Nhiều đường tròn lồng vào nhau và có tâm tạo bởi 2 đường cắt dọc và ngang
 * @param x tọa độ x của tâm
 * @param y tọa độ y của tâm
 * @param outsideDiamter đường kính hình tròn ngoài cùng
 * @param lineThickness độ dày đường tròn ngoài
 * @param gap khoảng cách giữa các đường tròn
 * @param numCircle số đường tròn
 * @param crossHairThickness độ dày đường qua tâm
 * @param crossHairLength độ dài đường qua tâm
 * @param degree góc xoay theo tâm (+ = xoay ngược chiều kim đồng hồ, - = xoay theo chiều kim đồng hồ)
 */
typedef void (*Primitive_Moire_t)(double x, double y, double outsideDiamter, double lineThickness, double gap, uint32_t numCircle, double crossHairThickness, double crossHairLength, double degree);
/**
 * @brief Hàm tạo một Cross-hair giữa một hình tròn được định nghĩa bởi đường kính ngoài và đường kính trong
 * @param x tọa độ x của tâm
 * @param y tọa độ y của tâm
 * @param outsideDiameter đường kính ngoài
 * @param insideDiameter đường kính trong
 * @param crossHairThickness độ dày đường cross-hair
 * @param degree góc xoay theo tâm (+ = xoay ngược chiều kim đồng hồ, - = xoay theo chiều kim đồng hồ)
 * @param 
 */
typedef void (*Primitive_Thermal_t)(double x, double y, double outsideDiamter, double insideDiamter, double crossHairThickness, double degree);

/**
 * @brief Cấu trúc Aperture Macro, chỉ lấy vị trí Macro
 *        khi được gọi đến bằng lệnh Dnn thì giải mã và render
 * @param name Con trỏ đến Macro trong file
 * @param nameLength Độ dài tên (giới hạn tiêu chuẩn 127 ký tự)
 */

typedef enum {
    Aperture_Unknown,
    Aperture_Circle     = 'C',
    Aperture_Rectangle  = 'R',
    Aperture_Obround    = 'O',
    Aperture_Polygon    = 'P',
    Aperture_Macro
} Aperture_Type_t;

/**
 * @param type Loại Aperture
 * @param pointer Con trỏ đến Aperture hoặc Macro
 *        nếu là Aperture thì bỏ qua Type,
 *        nếu là Macro thì bắt đầu từ Name
 */
typedef struct {
    uint32_t DCode;
    Aperture_Type_t type;
    char *pointer;
} Aperture_t;

#include "gerber_types.h"

#ifdef __cplusplus
}
#endif

#endif
