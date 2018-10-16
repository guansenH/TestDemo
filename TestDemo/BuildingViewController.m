//
//  BuildingViewController.m
//  TestDemo
//
//  Created by huang冠森 on 2018/3/30.
//  Copyright © 2018年 HGS. All rights reserved.
//

#import "BuildingViewController.h"
#import "INNSMap_ServicesResourceData.h"
#import "INNSMap_MapView.h"
#import "INNSMap_Image.h"
#import "FloorProperty.h"
#import "EditView.h"
#import <CoreLocation/CoreLocation.h>

#define kWidth [UIScreen mainScreen].bounds.size.width
#define kHeight [UIScreen mainScreen].bounds.size.height

@interface BuildingViewController ()<INNSMap_MapViewDelegate>
@property(nonatomic, strong) INNSMap_ServicesResourceData *ResourceManger;  //网络请求管理类
@property(nonatomic, strong) INNSMap_MapView *INNSMapView;    //MapView;
@property(nonatomic, strong) EditView *EditView;    //编辑view
@property(nonatomic, assign) BOOL LocationIsOpen;    //定位是否开启
@property(nonatomic, copy) NSMutableArray *LocationPOIArr;    //定位存放POI数组
@property(nonatomic, strong) NSString *CurrentFloorID;     //当前楼层ID
@end

@implementation BuildingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    [self.view setBackgroundColor:[UIColor whiteColor]];
    
    _LocationIsOpen = NO;
    
    [self SetUI];
    
    //获取楼宇数据
    [self GetBuildData];
}


/**
 设置UI
 */
-(void)SetUI
{
    _INNSMapView = [[INNSMap_MapView alloc]initWithFrame:CGRectMake(0, 64, kWidth, kHeight-64-50)];
    _INNSMapView.delegate = self;
    [_INNSMapView setPoiSelectState:YES];
    [self.view addSubview:_INNSMapView];
    UIBarButtonItem *lestBtn = [[UIBarButtonItem alloc]initWithTitle:@"返回" style:UIBarButtonItemStylePlain target:self action:@selector(BackAction)];
    self.navigationItem.leftBarButtonItem = lestBtn;
    
    UIBarButtonItem *rightBtn = [[UIBarButtonItem alloc]initWithTitle:@"编辑" style:UIBarButtonItemStylePlain target:self action:@selector(EditAction)];
    self.navigationItem.rightBarButtonItem = rightBtn;
    
    UILabel *beginLoca = [[UILabel alloc]initWithFrame:CGRectMake(10, kHeight - 50, 50, 20)];
    beginLoca.text = @"寻找路径";
    beginLoca.font = [UIFont systemFontOfSize:12];
    [self.view addSubview:beginLoca];
    
    UISwitch *locaSwitch = [[UISwitch alloc]initWithFrame:CGRectMake(70, kHeight - 50, 50, 20)];
    [locaSwitch addTarget:self action:@selector(OpenLocation:) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:locaSwitch];
    
    _LocationPOIArr = [NSMutableArray arrayWithCapacity:0];
}
-(void)OpenLocation:(UISwitch *)sender
{
    if (sender.on)
    {
        _LocationIsOpen = YES;
    }
    else
    {
        _LocationIsOpen = NO;
        [_LocationPOIArr removeAllObjects];
    }
}

/**
 返回按钮响应事件
 */
-(void)BackAction
{
    [self dismissViewControllerAnimated:NO completion:nil];
}

/**
 编辑响应事件
 */
-(void)EditAction
{
    if(!_EditView)
    {
        _EditView = [[EditView alloc]initWithFrame:CGRectMake(60, 80, 200, 400)];
        [self.view addSubview:_EditView];
        
        __weak __typeof(self)weakSelf = self;
        
        _EditView.OverlayBack=^(INNSMap_Overlay *overlay)
        {
            [weakSelf.INNSMapView addOverlay:overlay];
            
            weakSelf.EditView.hidden = YES;
        };
        
        _EditView.RemoveAllOverlays = ^{
            
            [weakSelf.INNSMapView removeAllOverlays];
            weakSelf.EditView.hidden = YES;
        };
    }
    else
    {
        if (_EditView.hidden)
        {
            _EditView.hidden = NO;
        }
        else
        {
            _EditView.hidden = YES;
        }
    }
}

/**
 获取楼宇数据
 */
-(void)GetBuildData
{
    _ResourceManger = [[INNSMap_ServicesResourceData alloc]init];
    
    [_ResourceManger INNSMap_getBuildingPropertyWithBuildingID:_BuildingID success:^(BuildingProperty *buildingPropertyObj) {
        
        NSMutableArray *floorArray =[NSMutableArray arrayWithCapacity:0];
        for (int i=buildingPropertyObj.UndergroundCnt-1; i>=0; i--) {
            UndergroundFloorObj *underObj=buildingPropertyObj.UndergroundFloorArray[i];
            FloorProperty *floor=[[FloorProperty alloc]init];
            floor.floorName =underObj.undergroundFloorName;
            floor.floorId   = underObj.floorId;
            [floorArray addObject:floor];
        }
        for (int i=0; i<buildingPropertyObj.OvergroundCnt; i++) {
            FloorProperty *floor=[[FloorProperty alloc]init];
            OvergroundFloorObj *overObj = buildingPropertyObj.OvergroundFloorArray[i];
            floor.floorName =overObj.overgroundFloorName;
            floor.floorId   =overObj.floorId;
            [floorArray addObject:floor];
        }
        
        if (floorArray.count==0) {
            return;
        }
        FloorProperty *floor=[[FloorProperty alloc]init];
        floor = floorArray[0];
        _CurrentFloorID = floor.floorId;
        dispatch_async(dispatch_get_main_queue(), ^{ //main
            
            [_INNSMapView loadMapViewWithBuildID:_BuildingID withFloorID:floor.floorId success:^{
                
                dispatch_async(dispatch_get_main_queue(), ^{
                    
                });
                //地址文字更新
                if ([buildingPropertyObj.buildAddr isEqual:[NSNull null]]) {
                    NSString *cityName   = [NSString stringWithFormat:@"%@",buildingPropertyObj.cityName];
                    NSString *countyName = [NSString stringWithFormat:@"%@",buildingPropertyObj.countyName];
                    NSString *addrStr    = [NSString stringWithFormat:@"%@ %@",cityName,countyName];
                   
                    self.navigationItem.title = addrStr;
                    
                }else{
                    self.navigationItem.title = @"未知";
                }
                
            } failure:^(NSString *error) {
                NSLog(@"读地图失败%@",error);
                dispatch_async(dispatch_get_main_queue(), ^{
                    NSLog(@"加载地图失败");
                });
                
            }];
            
        });//main
        
    } failure:^(NSString *error) {
        
    }];
}

/*!
 *  地图单击事件
 *  @param tapGesture 点击手势
 */
- (void)mapViewDidTaped:(UITapGestureRecognizer *)tapGesture
{
}

-(void)FindRoute
{
    if (_LocationPOIArr.count < 2 )return;
    INNSMap_POI *beginPOI = _LocationPOIArr[0];
    INNSMap_POI *endOPOI = _LocationPOIArr[1];
    CGPoint beginPoint = CGPointMake(beginPOI.poi_center.x, beginPOI.poi_center.y);
    CGPoint endPoint = CGPointMake(endOPOI.poi_center.x, endOPOI.poi_center.y);
    
    [_ResourceManger INNSMap_getPathRequestWithBuildID:_BuildingID withStartFloorID:_CurrentFloorID withStartPOIID:(int)beginPOI.poi_id withStartPoint:beginPoint withEndFloorID:_CurrentFloorID withEndPOIID:(int)endOPOI.poi_id withEndPoint:endPoint success:^(NSMutableDictionary *SearchPathDic) {

        NSString *key = [SearchPathDic allKeys][0];
        NSArray *pointArr = SearchPathDic[key][0];
        NSLog(@"%@",pointArr);
        [_INNSMapView drawNavigationRoute: pointArr];
        
    } failure:^(NSString *error) {
        NSLog(@"%@",error);
    }];
}
/*!
 *  地图平移事件
 *  @param panGesture 平移手势
 */
- (void)mapViewDidPaned:(UIPanGestureRecognizer *)panGesture
{
    NSLog(@"地图被平移!");
}

/*!
 *  地图缩放事件
 *  @param pinchGesture 缩放手势
 */
- (void)mapViewDidPinched:(UIPinchGestureRecognizer *)pinchGesture
{
    NSLog(@"地图被缩放!");
}

/*!
 *  地图旋转事件
 *  @param rotationGesture 旋转手势
 */
- (void)mapViewDidRotationed:(UIRotationGestureRecognizer *)rotationGesture
{
    NSLog(@"地图被旋转!");
}

/*!
 *  地图长按事件
 *  @param LongPressGesture 长按手势
 */
- (void)mapViewDidLongPressed:(UILongPressGestureRecognizer *)LongPressGesture
{
    NSLog(@"地图被长按!");
}

/*!
 *  POI被选中事件
 *  @param POI POI信息对象
 */
- (void)mapViewPOIDidTaped:(INNSMap_POI *)POI
{
    if (_LocationIsOpen)
    {
        ISM_MAP_POINT point = [_INNSMapView getSelectedPointOfMap];
        
        switch (_LocationPOIArr.count)
        {
            case 0:
            {
                UIImage *image = [UIImage imageNamed:@"起点"];
                
                INNSMap_Image *innsMapImage = [[INNSMap_Image alloc]initWithINImage:image withInPoint:point];
                [_INNSMapView addOverlay:innsMapImage];
                
                [_LocationPOIArr addObject:POI];
            }
                break;
            case 1:
            {
                UIImage *image = [UIImage imageNamed:@"终点"];
                
                INNSMap_Image *innsMapImage = [[INNSMap_Image alloc]initWithINImage:image withInPoint:point];
                [_INNSMapView addOverlay:innsMapImage];
                
                [_LocationPOIArr addObject:POI];
                
                [self FindRoute];
            }
                break;
            case 2:
            {
                [_LocationPOIArr removeAllObjects];
                
                UIImage *image = [UIImage imageNamed:@"起点"];
                
                INNSMap_Image *innsMapImage = [[INNSMap_Image alloc]initWithINImage:image withInPoint:point];
                [_INNSMapView addOverlay:innsMapImage];
                
                [_LocationPOIArr addObject:POI];
            }
                break;
                
            default:
                break;
        }
    }
}

/*!
 *  覆盖物被选中事件 -- 覆盖物轻拍
 *  @param overlay 覆盖物对象
 */
- (void)mapViewOverlayTaped:(id<INNSMap_Overlay>)overlay
{
    NSLog(@"覆盖物被轻拍!");
}

/*!
 *  覆盖物被选中事件 -- 覆盖物长按
 *  @param overlay 覆盖物对象
 */
- (void)mapViewOverlayLongPressed:(id<INNSMap_Overlay>)overlay
{
    NSLog(@"覆盖物被长按!");
}

/*!
 *  设施(图例)被选中事件 (单击)
 *  @param facility facility信息对象
 */
- (void)mapViewFacilityDidTaped:(INNSMap_Facility *)facility
{
    NSLog(@"设施(图例)被单击!");
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
