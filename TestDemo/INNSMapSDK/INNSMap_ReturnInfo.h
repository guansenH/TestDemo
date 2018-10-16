//
//  INNSMap_ReturnInfo.h
//  test
//
//  Created by lj on 16/4/15.
//  Copyright © 2016年 lj. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "INNSMap_LocationInfo.h"

typedef enum{
    ISM_AUTHORIZATION_NO_ERROR = 0xA001,///<授权可用
    ISM_AUTHORIZATION_ILLEGAL = 0x1001,///<非法授权
    ISM_AUTHORIZATION_EXPIRED = 0x1002,///<授权过期
    ISM_AUTHORIZATION_FULL = 0x1003,///<授权已满
    ISM_AUTHORIZATION_NO_PASS = 0x1004,///<授权未用过审核
    ISM_AUTHORIZATION_FORBIDDEN = 0x1005,///<授权已被禁用
    ISM_APP_NO_REGISTER = 0x1006,///<应用未注册
    ISM_APP_FORBIDDEN = 0x1007,///<应用已被禁用
}AuthorizationError;

typedef enum{
    ISM_LOCATION_NO_ERROR = 0,///<查询正确返回
    ISM_LOCATION_ERROR_CODE = 1,///<错误状态码
    ISM_LOCATION_UPDATE_DATE_NULL = 2,///<上传数据为空
    ISM_LOCATION_RESULT_NULL = 3,///<定位结果为空
}LocationError;

@interface INNSMap_ReturnInfo : NSObject

/*! 返回代码 */
@property (nonatomic,assign)int code;

/*! 返回信息 */
@property (nonatomic,strong)NSString *message;

/*! 位置信息 */
@property (nonatomic,strong)INNSMap_LocationInfo *locationInfo;

@end
