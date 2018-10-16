//
//  EditView.h
//  TestDemo
//
//  Created by huang冠森 on 2018/3/30.
//  Copyright © 2018年 HGS. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "INNSMap_Overlay.h"

@interface EditView : UIView

@property(nonatomic, copy) void(^OverlayBack)(INNSMap_Overlay *overlay);   //返回一个覆盖物
@property(nonatomic, copy) void(^RemoveAllOverlays)(void);   //删除所有覆盖物


- (instancetype)initWithFrame:(CGRect)frame;

@end
