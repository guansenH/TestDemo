//
//  INMapView.h
//  IndoorLocationTest
//
//  Created by ylf on 16/3/15.
//  Copyright © 2016年 YLF. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "INGeometry.h"
#import "INNSMap_Overlay.h"
#import "INNSMap_Compass.h"
#import "INNSMap_POI.h"
#import "INNSMap_Facility.h"

@protocol INNSMap_MapViewDelegate;

@interface INNSMap_MapView : UIView

/*! ISM_MapView 的最大缩放比例 */
@property (nonatomic, assign) CGFloat  max_zoom;

/*! ISM_MapView 的最小缩放比例 */
@property (nonatomic, assign) CGFloat  min_zoom;

/*! 是否启用点击手势 (默认启用) */
@property (nonatomic, assign) BOOL tapGestureEnabled;

/*! 是否启用平移手势 (默认启用) */
@property (nonatomic, assign) BOOL panGestureEnabled;

/*! 是否启用旋转手势 (默认启用) */
@property (nonatomic, assign) BOOL rotationGestureEnabled;

/*! 是否启用捏合手势 (默认启用) */
@property (nonatomic, assign) BOOL pinchGestureEnabled;

/*! 是否启用长按手势 (默认启用) */
@property (nonatomic, assign) BOOL longPressGestureEnabled;

/*! mapView的代理 */
@property (nonatomic, weak) id<INNSMap_MapViewDelegate> delegate;

#pragma mark - 暂不开放
/* 是否从缓存中加载地图,默认是YES,有缓存就加载缓存,没有就重新下载 */
@property (nonatomic, assign) BOOL fromCache;

/*!
 *  ISM_MapView初始化
 *
 *  @param frame   ISM_MapView对象的 frame
 *  @return ISM_MapView对象
 */
- (instancetype)initWithFrame:(CGRect)frame;

/*!
 *  设置指北针的位置
 *  @param position  指北针位置坐标 (注意此方法要写在初始化之后，地图加载之前,不调用默认在左上角)
 */
- (void)setCompassPosition:(CGPoint)position;

/*!
 *  设置比例尺的位置
 *  @param position 比例尺位置坐标 (注意此方法要写在初始化之后，地图加载之前,不调用默认在左下角)
 */
-(void)setMeasurePosition:(CGPoint)position;

/*!
 *  设置是否显示比例尺
 *  @param isShow  显示(不显示) 默认是显示的
 */
-(void)setMeasureShow:(BOOL)isShow;

/*!
 *  在view上加载地图
 *
 *  @param buildID 地图对应的buildID
 *  @param floorId 地图对应的 floorId
 *  @param success 成功的回调，无返回信息
 *  @param failure 失败回调，如果失败，返回信息是加载失败的原因
 */
- (void)loadMapViewWithBuildID:(NSString *)buildID withFloorID:(NSString *)floorId success:(void(^)(void))success
                failure:(void(^)(NSString *error))failure;

/*!
 *  设置地图的旋转角度(0-360)  （地图加载前设置会自动适配屏幕，加载后只旋转）
 *  @param rotation   旋转度数(旋转基于地图初始位置)
 */
- (void)setMapRotation:(float)rotation;

/*!
 *  获取覆盖物是否支持点击长按事件状态(是否可选中)
 *  @return BOOL 支持（不支持)
 */
- (BOOL)getOverlaySelectState;

/*!
 *  设置覆盖物支持点击长按事件 默认值为NO
 *  @param state 支持（不支持）
 */
- (void)setOverlaySelectState:(BOOL)state;

/*!
 *  获取poi拾取状态  是否可以拾取
 *  @return BOOL 能（不能）
 */
-(BOOL)getPoiSelectState;

/*!
 *  设置poi是否可以拾取
 *  @param state 能（不能） 默认值为NO
 */
-(void)setPoiSelectState:(BOOL)state;

/*!
 *  将多个POI在地图上高亮显示出来 (如搜索POI使其高亮)
 *  @param poi_id_array 搜索到的POI的id，以数组方式存储
 */
- (void)setPoisHighlight:(NSArray *)poi_id_array;

/*!
 *  设置单独一个Poi高亮
 *  @param PoiID POI的ID
 */
- (void)setSinglePoiHighlight:(NSInteger)PoiID;

/*!取消所有Poi高亮*/
-(void)cancelAllPoiAreaHighlight;

/*!
 *  设置一些公共设施的图例显示(楼梯，电梯，扶梯，洗手间，出口)   (如搜索公共设施使其高亮)
 *  @param   tuliArray 查询到的公共设施数组
 */
-(void)setPublicFacilitiesTuliShow:(NSArray *)tuliArray;

/*!设置本楼层所有的公共设施的图例显示(楼梯，电梯，扶梯，洗手间，出口)*/
-(void)setAllPublicFacilitiesTuliShow;

/*!
 *  获取地图上所有的POI
 *  @return NSMutableArray POI数组
 */
-(NSMutableArray *)getAllPoiArrayWithLoadMapView;

/*!
 *  寻径画路径
 *  @param pathArray 存储着从服务器获得的寻径的点的坐标
 */
- (void)drawNavigationRoute:(NSArray *)pathArray;

/*!清除寻径*/
- (void)clearNavigationRoute;

/*!
 *  获取当前缩放比例
 *  @return CGFloat 比例值
 */
- (CGFloat)getCurrentZoom;

/*
 *  获取当前的旋转角度
 *  @CGFloat 角度值
 */
- (CGFloat)getCurrentRotationAngle;

/*!
 *  得到指北针
 *  @return INNSMap_Compass 指北针对象
 */
- (INNSMap_Compass *)getCompass;

/*!
 *  添加一个覆盖物
 *  @param overlay 覆盖物对象
 */
- (void)addOverlay:(id<INNSMap_Overlay>)overlay;

/*!
 *  添加多个覆盖物
 *  @param overlays 由覆盖物组成的数组
 */
- (void)addOverlays:(NSArray *)overlays;

/*!
 *  删除单个覆盖物
 *  @param overlay 覆盖物对象
 */
- (void)removeOverlay:(id<INNSMap_Overlay>)overlay;

/*!
 *  删除多个覆盖物
 *  @param overlays 由覆盖物组成的数组
 */
- (void)removeOverlays:(NSArray *)overlays;

/*!删除所有的覆盖物*/
- (void)removeAllOverlays;

/*!
 *  设置可响应的覆盖物层，改层下覆盖物都可响应   (默认覆盖物都是可响应的)
 *  @param typeArray   可响应覆盖物层的ID(NSNumber类型)数组
 *  @return 对象
 */
- (void)setOverlayEnabledWithTypes:(NSArray *)typeArray;

/*!
 *  设置不可响应的覆盖物层，该层下覆盖物都不可响应
 *  @param typeArray   不可响应覆盖物层的ID数组
 */
- (void)setOverlayDisabledWithTypes:(NSArray *)typeArray;

/*!
 *  设置覆盖物偏移
 *  @param offset  偏移值 （实际地图坐标-即米）
 *  @param overlay 要移动的覆盖物
 */
- (void)setOffset:(CGPoint)offset withOverlay:(id<INNSMap_Overlay>)overlay;

/*!
 *  转屏幕坐标，为地图坐标
 *  @param point 屏幕坐标
 *  @return 地图坐标
 */
- (ISM_MAP_POINT)convertPoint:(CGPoint)point;

/*!
 *  转地图坐标为屏幕坐标
 *  @param point 地图坐标
 *  @return 屏幕坐标
 */
- (CGPoint)convertINMap_Point:(ISM_MAP_POINT)point;

/*!
 *  开始定位加定位点
 *  @param point 地图坐标
 */
- (void)addLocationPoint:(ISM_MAP_POINT)point;

/*!停止定位移除定位点*/
- (void)removeLocationPoint;

/*!
 *  获取在地图上点击的地图点坐标
 *  @return ISM_MAP_POINT 地图点坐标
 */
-(ISM_MAP_POINT)getSelectedPointOfMap;

/*!
 *  设置某点为地图中心点
 *  @param point 地图点坐标
 */
-(void)setCenterByPoint:(ISM_MAP_POINT)point;

/*!
 *  截取当前显示的地图View转为图片
 *  @return image 截取出来的图片
 */
-(UIImage *)cutUpViewToImage;

/*!
 *  自定义View转图片
 *  @param customView 自定义View
 *  @return UIImage对象
 */
- (UIImage *)convertImageWithCustomView:(UIView *)customView;

/*!
 *  根据提供点集在mapView上设置热力图
 *  @param points 地图点坐标数组  (注意这里数组里面点坐标代表的是地图点坐标)
 *  @param weights 里面存每个点的权重  (NSNumber类型)
 */
-(void)setHeatMapWithPoints:(NSArray *)points weights:(NSArray *)weights;

/*!
 *  设置热力图是否显示
 *  @param isShow 是否显示热力图 (默认不显示)
 */
- (void)setHeatMapShow:(BOOL)isShow;

#pragma mark - 不开放给开发者方法
/*!
 *  根据文字长度与 "面长度"(实际是外切矩形)的比例设置文字是否显示
 *  @param set   是否人为配置文字过长问题 (默认不人为配置)
 *  @param scale 设置比例
 */
- (void)setTitle:(BOOL)set scale:(float)scale;


@end


@protocol INNSMap_MapViewDelegate <NSObject>

@optional

/*!
 *  地图单击事件
 *  @param tapGesture 点击手势
 */
- (void)mapViewDidTaped:(UITapGestureRecognizer *)tapGesture;

/*!
 *  地图平移事件
 *  @param panGesture 平移手势
 */
- (void)mapViewDidPaned:(UIPanGestureRecognizer *)panGesture;

/*!
 *  地图缩放事件
 *  @param pinchGesture 缩放手势
 */
- (void)mapViewDidPinched:(UIPinchGestureRecognizer *)pinchGesture;

/*!
 *  地图旋转事件
 *  @param rotationGesture 旋转手势
 */
- (void)mapViewDidRotationed:(UIRotationGestureRecognizer *)rotationGesture;

/*!
 *  地图长按事件
 *  @param longPressGesture 长按手势
 */
- (void)mapViewDidLongPressed:(UILongPressGestureRecognizer *)LongPressGesture;

/*!
 *  POI被选中事件
 *  @param POI POI信息对象
 */
- (void)mapViewPOIDidTaped:(INNSMap_POI *)POI;

/*!
 *  覆盖物被选中事件 -- 覆盖物轻拍
 *  @param overlay 覆盖物对象
 */
- (void)mapViewOverlayTaped:(id<INNSMap_Overlay>)overlay;

/*!
 *  覆盖物被选中事件 -- 覆盖物长按
 *  @param overlay 覆盖物对象
 */
- (void)mapViewOverlayLongPressed:(id<INNSMap_Overlay>)overlay;

/*!
 *  设施(图例)被选中事件 (单击)
 *  @param facility facility信息对象
 */
- (void)mapViewFacilityDidTaped:(INNSMap_Facility *)facility;


@end








