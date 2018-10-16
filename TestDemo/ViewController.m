//
//  ViewController.m
//  TestDemo
//
//  Created by huang冠森 on 2018/3/30.
//  Copyright © 2018年 HGS. All rights reserved.
//

#import "ViewController.h"
#import "CityCell.h"
#import "INNSMap_ServicesResourceData.h"
#import "BuildingViewController.h"

#define HeightViewHeight (40)
#define CellViewHeight (40)

@interface ViewController ()<UITableViewDelegate,UITableViewDataSource>

@property(nonatomic, strong) UITableView *CityList;   //城市列表
@property(nonatomic, strong) NSArray *CityArr;   //城市数组
@property(nonatomic, strong) NSArray *BuildingArr;   //建筑数组
@property(nonatomic, strong) INNSMap_ServicesResourceData *ResourceManger;  //网络请求管理类
@property(nonatomic, assign) NSInteger CurrentSection;   //当前section
@property(nonatomic, assign) NSInteger OldSection;   //上一个section
@property(nonatomic, assign) BOOL Close;   //闭合section
@property(nonatomic, strong) BuildingViewController *BuildingViewC;   //建筑控制器


@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    _OldSection = -1;
    _Close = NO;
    _BuildingViewC = [[BuildingViewController alloc]init];
    
    //UI设置
    [self SetUI];
    //获取城市数据
    [self GetCityData];
}

/**
 UI设置
 */
-(void)SetUI
{
    UILabel *headLbl = [[UILabel alloc]initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, 64)];
    [headLbl setText:@"城市列表"];
    headLbl.font = [UIFont systemFontOfSize:20];
    [headLbl setTextAlignment:NSTextAlignmentCenter];
    [headLbl setBackgroundColor:[UIColor yellowColor]];
    [self.view addSubview:headLbl];
    
    _CityList = [[UITableView alloc]initWithFrame:CGRectMake(0, 64, self.view.frame.size.width, self.view.frame.size.height-64) style:UITableViewStyleGrouped];
    _CityList.delegate = self;
    _CityList.dataSource = self;
    [self.view addSubview:_CityList];
}

/**
 获取城市数据
 */
-(void)GetCityData
{
    //获取城市列表
    _ResourceManger = [[INNSMap_ServicesResourceData alloc]init];
    
    [_ResourceManger INNSMap_getAuthorizedCityListWithSuccess:^(NSMutableArray *cityMutableArr) {
        _CityArr = cityMutableArr;
        
        [_CityList reloadData];
    } failure:^(NSString *error) {
        NSLog(@"%@",error);
    }];
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return _CityArr.count;
}

-(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return HeightViewHeight;
}

-(CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 0.1;
}

-(UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section
{
    UIView *backView = [[UIView alloc]initWithFrame:CGRectMake(0, 0, tableView.frame.size.width, HeightViewHeight)];
    
    UIButton *btn = [[UIButton alloc]initWithFrame:CGRectMake(10, 0, tableView.frame.size.width-20, HeightViewHeight-1)];
    btn.tag = section;
    CityProperty *cp = _CityArr[section];
    [btn setTitle:cp.regionName forState:UIControlStateNormal];
    [btn setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    btn.contentHorizontalAlignment = UIControlContentHorizontalAlignmentLeft;
    [btn addTarget:self action:@selector(GetBuildingData:) forControlEvents:UIControlEventTouchUpInside];
    [backView addSubview:btn];
    
    UIView *line = [[UIView alloc]initWithFrame:CGRectMake(10, HeightViewHeight-1, backView.frame.size.width-20, 1)];
    [line setBackgroundColor:[UIColor grayColor]];
    [backView addSubview:line];
    
    return backView;
}

-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (_Close) return 0;
    
    if(section == _CurrentSection)
    {
        return _BuildingArr.count;
    }
    else
    {
        return 0;
    }
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return CellViewHeight;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
{
    static NSString *CellIdentifier = @"CityCell";
    CityCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (!cell) {
        cell = [CityCell instanceFromNib];
    }
    if (_CurrentSection == indexPath.section)
    {
        CityBuilding *cb = _BuildingArr[indexPath.row];
        cell.textLabel.text = cb.buildingNameStr;
    }
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    CityBuilding *cb = _BuildingArr[indexPath.row];
    _BuildingViewC.BuildingID = cb.buildingCodeStr;
    UINavigationController *buildNVC = [[UINavigationController alloc]initWithRootViewController:_BuildingViewC];
    [self presentViewController:buildNVC animated:YES completion:nil];
}


/**
 获取建筑物数据
 */
-(void)GetBuildingData:(UIButton *)sender
{
    _CurrentSection = sender.tag;
    if (_CurrentSection != _OldSection)
    {
        CityProperty *cp = _CityArr[sender.tag];
        
        [_ResourceManger INNSMap_getCityBuildingListWithCountryID:86 withCityID:cp.regionId success:^(NSMutableArray *buildingMutableArr) {
            if (buildingMutableArr.count >0)
            {
                _BuildingArr = buildingMutableArr;
                [self RefreshView];
            }
        } failure:^(NSString *error) {
            
        }];
    }
    
}

/**
 刷新显示
 */
-(void)RefreshView
{
    if (_OldSection != -1)
    {
        _Close = YES;
        
        [_CityList reloadSections:[NSIndexSet indexSetWithIndex:_OldSection] withRowAnimation:UITableViewRowAnimationNone];
    }
    
    _Close = NO;
    [_CityList reloadSections:[NSIndexSet indexSetWithIndex:_CurrentSection] withRowAnimation:UITableViewRowAnimationNone];
    _OldSection = _CurrentSection;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


@end
