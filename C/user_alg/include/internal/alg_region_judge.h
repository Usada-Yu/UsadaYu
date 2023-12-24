#ifndef __ALG_REGION_JUDGE_H__
#define __ALG_REGION_JUDGE_H__

#include "alg_base_define.h"

/********************************************************************************************
 * @brief   判断点base_point是否在点end_point1和点end_point2连成的线段上
 * 
 * @param   base_point: 被判断的点
 * @param   end_point1: 线段端点1
 * @param   end_point2: 线段端点2
 * @param   inaccuracies: 浮点类型误差，传入0则使用默认误差：1e-1
 * 
 * @return  OS_SOK: base_point在线段上
 * @return  OS_EFAIL: base_point不在线段上
 * 
 * @details 此函数根据目标点到线段两个端点的距离之和判断目标点是否在线段上
 * 
 * @note    浮点类型计算存在误差
********************************************************************************************/
int alg_region_point_on_line(base_point_t base_point,
                                base_point_t end_point1, base_point_t end_point2,
                                double inaccuracies);

/********************************************************************************************
 * @brief   判断点ponit是否在区域polygon内
 * 
 * @param   ponit: 点坐标信息
 * @param   polygon: 区域信息
 * 
 * @return  OS_SOK: ponit在区域polygon内
 * @return  OS_EFAIL: ponit不在区域polygon内
 * 
 * @details (1) 以射线法判断待测点和区域的关系
 *          (2) 以point为基点，向x无限大引出一条射线，此时射线方程为y = point.y(x >= point.x)
 *          (3) 线段方程根据两点式计算为：(y - y2) / (y1 - y2) = (x - x2) / (x1 - x2)
 * 
 * @note    (1) 坐标信息均以整型类型计算
 *          (2) 待测点point在多边形的边界上则返回OS_SOK
 *          (3) 调用alg_region_point_on_line()判断待测点是否在多边形边界上时注意误差的填写
********************************************************************************************/
int alg_region_point_in_polygon(base_point_t ponit, base_polygon_t polygon);

#endif  // __ALG_REGION_JUDGE_H__
