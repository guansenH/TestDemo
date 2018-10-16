//
//  INNSMAP_Polygon.h
//  IndoorLocationTest
//
//  Created by 黎仕仪 on 17/6/29.
//  Copyright © 2017年 YLF. All rights reserved.
//

#import "INNSMap_Overlay.h"

@interface INNSMap_Polygon : INNSMap_Overlay

/*!
 *  Polygon对应的初始化方法
 *  @param  pointArray  组成多边形的点(地图)坐标的数组
 *  @param  num         点的数量 (若传入数量比真实数量多，多的用(0,0)点补，比真实数量少，后面的点不会被画出)
 *  @return INNSMap_Polygon对象
 */
- (instancetype)initWithPolygonPoints:(ISM_MAP_POINT *)pointArray pointNum:(int)num;

/*! 画轮廓图或平面图的点的集合 */
@property (nonatomic, assign) ISM_MAP_POINT     *point;

/*! 线型（1:实线;2:点划虚线;3:线划虚线;）*/
@property (nonatomic, assign) NSInteger         lineStyle;

/*! 所画的图形的路径 */
@property (nonatomic, assign) CGMutablePathRef  linePath;

/*! 描边色 */
@property (nonatomic, strong) UIColor   *strokeColor;

/*! 填充色 */
@property (nonatomic, strong) UIColor   *fillColor;

/*! 线条宽度 */
@property (nonatomic, assign) CGFloat   lineWidth;


#pragma mark - 注意，添加多边形覆盖物的时候，设置了文字，SDK会自己计算文字该添加的中心点，但可能不规则的多边形，计算出的中心点并不是很合适，所以开发者可以自己设置添加中心点，设置后使用开发者设置的中心点为文字中心点
/*! 多边形覆盖物文字 */
@property (nonatomic, copy) NSString *title;

/*! 多边形覆盖物文字大小 */
@property (nonatomic, assign) float titleSize;

/*! 多边形覆盖物文字颜色 */
@property (nonatomic, strong) UIColor *titleColor;

#pragma mark - 若对SDK算出中心点不满意，可自己设置中心点
/*! 多边形文字所出中心点 (实际地图坐标)*/
@property (nonatomic, assign) ISM_MAP_POINT titlePoint;

@end
