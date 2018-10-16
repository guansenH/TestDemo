//
//  INLine.h
//  IndoorLocationTest
//
//  Created by ylf on 16/3/15.
//  Copyright © 2016年 YLF. All rights reserved.
//

#import "INNSMap_Overlay.h"
#import "INGeometry.h"

@interface INNSMap_Line : INNSMap_Overlay   //修改线颜色属性请注意使用strokeColor，fillColor是线闭合区域的颜色

@property (nonatomic, strong)NSMutableArray *pointArr;  //判断点在线上做的数组

/*! 描边色 */
@property (nonatomic, strong) UIColor   *strokeColor;

/*! 填充色 */
@property (nonatomic, strong) UIColor   *fillColor;

/*! 线条宽度 */
@property (nonatomic, assign) CGFloat   lineWidth;


/*! 画轮廓图或平面图的点的集合 */
@property (nonatomic, assign) ISM_MAP_POINT     *point;

/*! 所画的图形的路径 */
@property (nonatomic, assign) CGMutablePathRef  linePath;

/*! 样式 */ //1代表poi
@property (nonatomic, assign) NSInteger         planeType;

/*! 线型（1:实线;2:点划虚线;3:线划虚线;）*/
@property (nonatomic, assign) NSInteger         lineStyle;

/*! 点击选中时的POI 的 Id */
@property (nonatomic, assign) NSInteger         poiId;

/*!
 *   INLine对应的初始化方法
 *  @param pointArray 点(地图)的坐标的数组
 *  @param num        点的数量 (若传入数量比真实数量多，多的用(0,0)点补，比真实数量少，后面的点不会被画出)
 *  @return INLine对象
 */
- (instancetype)initWithINLinePoints:(ISM_MAP_POINT *)pointArray pointNum:(int)num;

/*!更新线的路径，即更新平面图*/
- (void)updateLinePath;


#pragma mark - 不开放方法和属性
///*! 图例ID */
//@property(nonatomic,assign)int tuliID;
//
///*! 图例图片 */
//@property(nonatomic,strong)UIImage *tuliImage;
//
///*! 图例在地图上的坐标点 */
//@property(nonatomic,assign)ISM_MAP_POINT tuliPoint;
//
///*!
// *   图例对应的初始化方法
// *  @param tuli_point   图例在地图上的坐标点
// *  @param image        图例图片
// *  @return INLine对象（图例对象）
// */
//- (instancetype)initWithINLinePoint:(ISM_MAP_POINT)tuli_point withImage:(UIImage *)image;


@end
