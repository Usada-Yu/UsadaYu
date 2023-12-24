#include "os_common.h"
#include "alg_region_judge.h"

/********************************************************************************************
 * @brief   判断点base_point向x无限大方向作的射线是否穿过点end_point1和点end_point2；
 *          以及射线穿过点end_point1和点end_point2后的计数判断
 * 
 * @param   base_point: 被判断的点
 * @param   end_point1: 线段端点1
 * @param   end_point2: 线段端点2
 * @param   index_count: 引用计数
 * 
 * @return  OS_SOK: 射线穿过点end_point1
 * @return  OS_EFAIL: 射线不穿过点end_point1
 * 
 * @details 假设射线起点为待测点P(x0, y0)，然后向x无穷大作射线。
 *          再假设两个端点为A(x1, y1)，B(x2, y2)。如果射线穿过了点A。那么作如下规定：
 *          y0 == y1 && y1 <= y2，那么记为0个交点，引用计数不变；
 *          y0 == y1 && y1 > y2，那么记为1个交点，引用计数加1
 * 
 * @note    此函数仅判断待测点base_point引出的射线和点end_point1的关系，不判断和点end_point2的关系
********************************************************************************************/
static int _alg_region_point_x_with_endpoints(base_point_t base_point, base_point_t end_point1, base_point_t end_point2, int *index_count) {
    if (base_point.y != end_point1.y) {
        return OS_EFAIL;
    }

    if (end_point1.y > end_point2.y) {
        (*index_count)++;
    }

    return OS_SOK;
}

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
int alg_region_point_on_line(base_point_t base_point, base_point_t end_point1, base_point_t end_point2, double inaccuracies) {
    short       base_x  = base_point.x, base_y  = base_point.y;
    short       end1_x  = end_point1.x, end1_y  = end_point1.y;
    short       end2_x  = end_point2.x, end2_y  = end_point2.y;
    double      end1_to_end2_distance, base_to_end1_distance, base_to_end2_distance;
    double      default_inaccuracies = fabs(inaccuracies) > 1e-9 ? inaccuracies : 1e-1;

    end1_to_end2_distance   = sqrt(pow(end1_x - end2_x, 2) + pow(end1_y - end2_y, 2));
    base_to_end1_distance   = sqrt(pow(base_x - end1_x, 2) + pow(base_y - end1_y, 2));
    base_to_end2_distance   = sqrt(pow(base_x - end2_x, 2) + pow(base_y - end2_y, 2));

    return fabs(base_to_end1_distance + base_to_end2_distance - end1_to_end2_distance) < default_inaccuracies ? OS_SOK : OS_EFAIL;
}

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
int alg_region_point_in_polygon(base_point_t point, base_polygon_t polygon) {
    unsigned int                    i                   = 0;
    unsigned int                    index_count         = 2;    // 默认偶数，即点在区域外
    base_point_t                    point_start         = {0};
    base_point_t                    point_end           = {0};

    if (polygon.point_num <= 2) {
        OS_WARN("Insufficient number of coordinates to enclose an area\n");
        return OS_EFUNC_ARGUMENT;
    }

    for (i = 0; i < polygon.point_num; i++) {
        memcpy(&point_start, &(polygon.points[i]), sizeof(base_point_t));                           // 当前线段坐标出发点
        memcpy(&point_end, &(polygon.points[(i + 1) % polygon.point_num]), sizeof(base_point_t));   // 当前线段坐标目标点

        if (OS_isSuc(alg_region_point_on_line(point, point_start, point_end, 1e-3))) {                      // 待测点是否在线段上
            return OS_SOK;
        }

        if (OS_isSuc(_alg_region_point_x_with_endpoints(point, point_start, point_end, &index_count))) {    // 射线是否穿过端点
            continue;
        }

        if ((point.y > OS_MIN_T(point_start.y, point_end.y)) && (point.y < OS_MAX_T(point_start.y, point_end.y))) {
            if ((point.x <= (double)((point.y - point_end.y) * (point_start.x - point_end.x)) /
                        (double)(point_start.y - point_end.y) + point_end.x) ||
                    ((point_start.x == point_end.x) && (point.x < point_start.x))) {
                index_count++;
            }
        }
    }

    return index_count % 2 == 0 ? OS_EFAIL : OS_SOK;
}
