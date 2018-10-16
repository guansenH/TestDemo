//
//  INPoint.h
//  IndoorLocationTest
//
//  Created by ylf on 16/3/23.
//  Copyright © 2016年 YLF. All rights reserved.
//

#import "INNSMap_Overlay.h"
#import "INGeometry.h"

@interface INNSMap_Points : INNSMap_Overlay
{
@public
    CGMutablePathRef pointPath; // 绘画点所对应的路径
}

/*! 描边色 */
@property (nonatomic, strong) UIColor   *strokeColor;

/*! 填充色 */
@property (nonatomic, strong) UIColor   *fillColor;

/*! 线条宽度 */
@property (nonatomic, assign) CGFloat   lineWidth;

/*! 点的半径 */
@property (nonatomic, assign) CGFloat  pointRadius;

/* 点集 */
@property (nonatomic, strong) NSArray *pointArray;

/* 点集的数量 */
@property (nonatomic, assign) int pointnum;

/*!
 *  添加一个覆盖物多个点的初始化方法
 *  @param pointArray     添加的点对应的位置的集合
 *  @param num            点的数量
 *  @return INPoint对象本身
 */
- (instancetype)initWithINPoints:(ISM_MAP_POINT *)pointArray pointNum:(int)num;

/*! 距离在distance内的点不显示 (distance单位是屏幕尺寸) */
@property (nonatomic, assign) CGFloat distance;

@property (nonatomic, assign) CGRect mapViewFrame;

- (void)updateINPoint;

- (void)updateINPointBefore;

@end
