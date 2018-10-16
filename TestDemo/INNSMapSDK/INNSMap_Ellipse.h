//
//  INNSMap_Ellipse.h
//  IndoorLocationTest
//
//  Created by 黎仕仪 on 17/6/29.
//  Copyright © 2017年 YLF. All rights reserved.
//

#import "INNSMap_Point.h"

@interface INNSMap_Ellipse : INNSMap_Overlay
{
@public
    CGMutablePathRef pointPath; // 绘画点所对应的路径
}

/*! 覆盖物描边色 */
@property (nonatomic, strong) UIColor   *strokeColor;

/*! 覆盖物填充色 */
@property (nonatomic, strong) UIColor   *fillColor;

/*! 线条宽度 */
@property (nonatomic, assign) CGFloat   lineWidth;

/*! 圆的半径 (实际的米，默认为0)*/
@property (nonatomic, assign) CGFloat   ellipseRadius;

/*! 圆线型（1:实线;2:点划虚线;3:线划虚线;）*/
@property (nonatomic, assign) NSInteger   lineStyle;

/*!
 *  添加圆的初始化方法
 *  @param point     添加的圆心对应的位置
 *  @return INEllipse对象本身
 */
- (instancetype)initWithINPoint:(ISM_MAP_POINT)point;

@end
