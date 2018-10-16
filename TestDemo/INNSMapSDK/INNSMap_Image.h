//
//  INImage.h
//  IndoorLocationTest
//
//  Created by ylf on 16/3/24.
//  Copyright © 2016年 YLF. All rights reserved.
//

#import "INNSMap_Overlay.h"

@interface INNSMap_Image : INNSMap_Overlay
/*!
 *  添加图像的初始化方法(带设置锚点)
 *
 *  @param imageName    图像的名称
 *  @param type         图像的类型
 *  @param point        图像所在位置对应的初始点
 *  @param AnchorPoint  锚点,如果x,y不在0~1范围内，还是以默认锚点(0.5,0.5)计算
 *  @return INImage对象
 */
- (instancetype)initWithINImage:(UIImage *)image withInPoint:(ISM_MAP_POINT)point withAnchorPoint:(CGPoint)anchorPoint;


/*!
 *  添加图像的初始化方法->默认锚点(0.5,0.5)
 *
 *  @param imageName    图像的名称
 *  @param type         图像的类型
 *  @param point        图像所在位置对应的初始点
 *  @return INImage对象
 */
- (instancetype)initWithINImage:(UIImage *)image withInPoint:(ISM_MAP_POINT)point;

/*! 图片覆盖物的图片*/
@property (nonatomic, strong)UIImage *image;

/*! inAnchorPoint  锚点,如果x,y不在0~1范围内，还是以默认锚点(0.5,0.5)计算*/
@property (nonatomic, assign) CGPoint inAnchorPoint;


#pragma mark - 如果需要图文覆盖物，可设置以下属性，排版将为：文字在图片正上方
/*! 图片的文字 */
@property (nonatomic, copy)NSString *imageTitle;

/*! 文字大小 */
@property (nonatomic, assign)float fontSize;

/*! 文字颜色 */
@property (nonatomic, strong)UIColor *titleColor;

/*! 内部用于获取文字的尺寸，做事件响应，开发者set此属性无效 */
@property (nonatomic, assign)CGRect titleRect;

@end
