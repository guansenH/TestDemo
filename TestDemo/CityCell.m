//
//  CityCell.m
//  TestDemo
//
//  Created by huang冠森 on 2018/3/30.
//  Copyright © 2018年 HGS. All rights reserved.
//

#import "CityCell.h"

@implementation CityCell

+ (instancetype)instanceFromNib
{
    return [[[NSBundle mainBundle]loadNibNamed:@"CityCell" owner:nil options:nil]lastObject];
}

- (void)awakeFromNib {
    [super awakeFromNib];
    self.textLabel.font = [UIFont systemFontOfSize:15];
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
