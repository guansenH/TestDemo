//
//  INNSMap_Bubble.h
//  IndoorLocationTest
//
//  Created by 黎仕仪 on 17/7/11.
//  Copyright © 2017年 YLF. All rights reserved.
//

#import "INNSMap_Overlay.h"

@interface INNSMap_Bubble : INNSMap_Overlay

/*!
 *  INNSMap_Bubble对应的初始化方法 (气泡覆盖物)
 *  @param title   气泡要显示的文字 （最多显示15字）
 *  @param point   气泡出现的点  (气泡从哪里冒出来,此点为气泡中心点，设置偏移可以移动气泡位置)
 *  @return INLine对象
 */
-(instancetype)initWithTitle:(NSString *)title addPoint:(ISM_MAP_POINT)point;

/*! 文字大小 */
@property (nonatomic, assign)float   fontSize;

/*! 文字颜色 */
@property (nonatomic, strong)UIColor *titleColor;

/*! 文字 */
@property (nonatomic, copy)NSString  *title;

/*! 气泡的偏移 (单位是屏幕逻辑尺寸，基于起始气泡中心点偏移)*/
@property (nonatomic, assign)CGPoint offSet;


@end
