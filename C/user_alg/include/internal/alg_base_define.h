#ifndef __ALG_BASE_DEFINE_H__
#define __ALG_BASE_DEFINE_H__

// 多边形最大边个数
#ifndef BASE_POLYGON_MAX_EDGES
#define BASE_POLYGON_MAX_EDGES          (32)
#endif  // BASE_POLYGON_MAX_EDGES

typedef struct {
    short int                           x;                                      // 横坐标
    short int                           y;                                      // 纵坐标
} base_point_t;

typedef struct {
    unsigned int                        point_num;                              // 多边形点数
    base_point_t                        points[BASE_POLYGON_MAX_EDGES];         // 多边形点坐标数组
} base_polygon_t;

#endif  // __ALG_BASE_DEFINE_H__
