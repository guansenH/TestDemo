//
//  EditCell.m
//  TestDemo
//
//  Created by huang冠森 on 2018/3/30.
//  Copyright © 2018年 HGS. All rights reserved.
//

#import "EditCell.h"

@implementation EditCell

+ (instancetype)instanceFromNib
{
    return [[[NSBundle mainBundle]loadNibNamed:@"EditCell" owner:nil options:nil]lastObject];
}

- (void)awakeFromNib {
    [super awakeFromNib];
    
    [self.textLabel setTextAlignment:NSTextAlignmentCenter];
    [self.textLabel setTextColor:[UIColor whiteColor]];
    [self setBackgroundColor:[UIColor clearColor]];
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
