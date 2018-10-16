//
//  ISM_Overlay.h
//  IndoorLocationTest
//
//  Created by ylf on 16/4/5.
//  Copyright © 2016年 YLF. All rights reserved.
//

#import <QuartzCore/QuartzCore.h>
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "INNSMap_Annotation.h"
#import "INGeometry.h"


@protocol INNSMap_Overlay <INNSMap_Annotation>

@optional

/*! 对象本身对应的原始点的坐标 */
@property (nonatomic, assign) ISM_MAP_POINT addPoint;

@end

@interface INNSMap_Overlay : CALayer<INNSMap_Overlay>

/*! 透明度 */
@property (nonatomic, assign) CGFloat   alpha;

/*! 图形上的点对应的矩阵的变化 */
@property (nonatomic, assign) CGAffineTransform transform_2D;

/*! 对象本身对应的原始地图点的坐标 */
@property (nonatomic, assign) ISM_MAP_POINT addPoint;

/*! 覆盖物对应tag (默认是0,跟系统UIView的tag用法相似,但只做标识)*/
@property (nonatomic, assign) int tag;

/*! 覆盖物是否可拾取 (默认可拾取)*/
@property (nonatomic, assign) BOOL pickup;

/*! 覆盖物是否可拖动 (默认不可拖动) 点集覆盖物和多边形覆盖物不可拖动 */
@property (nonatomic, assign) BOOL drag;

/*! 覆盖物的分类分层 */  //同类的覆盖物处于同一层，层越大，覆盖物越在上面，覆盖物之间重叠隐藏只在相同层之间处理
@property (nonatomic, assign) int overlayType;

@end








