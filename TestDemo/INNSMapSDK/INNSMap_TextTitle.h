//
//  INTextTitle.h
//  IndoorLocationTest
//
//  Created by ylf on 16/3/19.
//  Copyright © 2016年 YLF. All rights reserved.
//

#import "INNSMap_Overlay.h"


@interface INNSMap_TextTitle : INNSMap_Overlay
/**
 *  POI的标题名称
 */
@property (nonatomic, strong) NSString *titleString;
/**
 *  字体的颜色
 */
@property (nonatomic, strong) UIColor  *fontColor;
/**
 *  字体的大小
 */
@property (nonatomic, assign) CGFloat   fontSize;
/**
 *  字体的名称如（微软雅黑） 暂不支持
 */
@property (nonatomic, strong) NSString *fontTitle; //暂不生效
/**
 *  点击选中时的POI 的 Id
 */
@property (nonatomic, assign) NSInteger poiId;


/*! 文字底色 (默认透明) */
@property (nonatomic, strong) UIColor   *fillColor;


@end
