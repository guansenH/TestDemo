//
//  INNSMap_Facility.h
//  IndoorLocationTest
//
//  Created by 黎仕仪 on 17/6/30.
//  Copyright © 2017年 YLF. All rights reserved.
//

#import "INNSMap_Overlay.h"

@interface INNSMap_Facility : INNSMap_Overlay

/*! 图例(设施)ID */
@property(nonatomic,assign)int facilityID;

/*! 图例图片 */
@property(nonatomic,strong)UIImage *facilityImage;

/*! 图例在地图上的坐标点 */
@property(nonatomic,assign)ISM_MAP_POINT facilityPoint;

/*!
 *   图例对应的初始化方法
 *  @param tuli_point   图例在地图上的坐标点
 *  @param image        图例图片
 *  @return INLine对象（图例对象）
 */
- (instancetype)initWithINLinePoint:(ISM_MAP_POINT)facility_point withImage:(UIImage *)image;

@end
