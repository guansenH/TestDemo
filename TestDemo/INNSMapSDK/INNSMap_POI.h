//
//  ISM_POI.h
//  IndoorLocationTest
//
//  Created by ylf on 16/4/19.
//  Copyright © 2016年 YLF. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "INGeometry.h"

@interface INNSMap_POI : NSObject

/*! poi的ID */
@property (nonatomic, assign) NSInteger       poi_id;

/*! poi的title */
@property (nonatomic, strong) NSString       *poi_title;

/*! poi在地图上的坐标点 */
@property (nonatomic, assign) ISM_MAP_POINT   poi_center;

/*! poi所属小类ID */
@property (nonatomic, assign) NSInteger poiS_Type_id;

/*! poi所属大类ID */
@property (nonatomic, assign) NSInteger poiB_Type_id;

@end
