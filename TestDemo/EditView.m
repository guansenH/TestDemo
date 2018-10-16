//
//  EditView.m
//  TestDemo
//
//  Created by huang冠森 on 2018/3/30.
//  Copyright © 2018年 HGS. All rights reserved.
//

#import "EditView.h"
#import "EditCell.h"
#import "INNSMap_Point.h"
#include "INNSMap_Line.h"
#import "INNSMap_Ellipse.h"
#import "INNSMap_Points.h"
#import "INNSMap_Bubble.h"
#import "INNSMap_Facility.h"
#import "INNSMap_TextTitle.h"
#import "INNSMap_Image.h"
#import "INNSMap_Polygon.h"
#import "INGeometry.h"

@interface EditView()<UITableViewDelegate,UITableViewDataSource>
@property(nonatomic, strong) UITableView *OperationList;   //操作列表
@property(nonatomic, strong) NSArray *Operations;    //操作数组
@end

@implementation EditView

- (instancetype)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self)
    {
        [self setBackgroundColor:[UIColor blackColor]];
        
        self.alpha = 0.7;
        
        _Operations = [NSArray arrayWithObjects:@"添加点覆盖物",@"添加线覆盖物",@"添加圆形覆盖物",@"添加点集覆盖物",@"添加多边形覆盖物",@"添加文字覆盖物",@"添加图片覆盖物",@"添加气泡覆盖物",@"删除所有覆盖物", nil];
        
        _OperationList = [[UITableView alloc]initWithFrame:CGRectMake(0, 0, self.frame.size.width, self.frame.size.height) style:UITableViewStyleGrouped];
        _OperationList.delegate = self;
        _OperationList.dataSource = self;

        [_OperationList setBackgroundColor:[UIColor clearColor]];
        [self addSubview:_OperationList];
    }
    return self;
}

-(CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section
{
    return 0.0001;
}
-(CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section
{
    return 0.0001;
}
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return _Operations.count;
}

-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 44;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
{
    static NSString *CellIdentifier = @"EditCell";
    EditCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    if (!cell) {
        cell = [EditCell instanceFromNib];
        cell.selectionStyle = UITableViewCellSelectionStyleNone;
    }
    
    cell.textLabel.text = _Operations[indexPath.row];
    
    return cell;
}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    INNSMap_Overlay *overlay = nil;
    
    switch (indexPath.row)
    {
        case 0:    //点
        {
            ISM_MAP_POINT point;
            point.x = 50.00;
            point.y = 50.00;
            
            INNSMap_Point *innsMapPoint = [[INNSMap_Point alloc]initWithINPoint:point];
            innsMapPoint.strokeColor = [UIColor redColor];
            innsMapPoint.pointRadius = 5;
            innsMapPoint.fillColor = [UIColor greenColor];
            innsMapPoint.lineWidth = 1;
            
            overlay = innsMapPoint;
        }
            break;
        case 1:    //点集
        {
            ISM_MAP_POINT points[2];
            
            ISM_MAP_POINT pointA;
            pointA.x = 80.00;
            pointA.y = 80.00;
            points[0] = pointA;
            
            ISM_MAP_POINT pointB;
            pointB.x = 120.00;
            pointB.y = 120.00;
            points[1] = pointB;
            
            INNSMap_Line *line = [[INNSMap_Line alloc]initWithINLinePoints:points pointNum:2];
            line.strokeColor = [UIColor redColor];
            line.fillColor = [UIColor greenColor];
            line.lineWidth = 1;
            
            overlay = line;
        }
            break;
        case 2:    //圆
        {
            ISM_MAP_POINT point;
            point.x = 100.00;
            point.y = 100.00;
            
            INNSMap_Ellipse *ellipse = [[INNSMap_Ellipse alloc]initWithINPoint:point];
            ellipse.ellipseRadius = 10;
            ellipse.lineWidth = 2;
            ellipse.strokeColor = [UIColor redColor];
            ellipse.fillColor = [UIColor yellowColor];
            ellipse.lineStyle = 1;
            
            overlay = ellipse;
        }
            break;
        case 3:    //点集覆盖物
        {
            ISM_MAP_POINT points[600];
            for (int i=0; i<600; i++) {
                points[i].x = arc4random()%40 + 50;
                points[i].y = arc4random()%40 + 50;
            }
            INNSMap_Points *ps = [[INNSMap_Points alloc]initWithINPoints:points pointNum:600];
            ps.fillColor = [UIColor redColor];
            ps.pointRadius = 5;
            ps.distance = 20;
            
            overlay = ps;
        }
            break;
        case 4:    //多边形
        {
            ISM_MAP_POINT points[3];
            
            ISM_MAP_POINT pointA;
            pointA.x = 80.00;
            pointA.y = 80.00;
            points[0] = pointA;
            
            ISM_MAP_POINT pointB;
            pointB.x = 120.00;
            pointB.y = 120.00;
            points[1] = pointB;
            
            ISM_MAP_POINT pointC;
            pointC.x = 80.00;
            pointC.y = 120.00;
            points[2] = pointC;
            
            INNSMap_Polygon *polygon = [[INNSMap_Polygon alloc]initWithPolygonPoints:points pointNum:3];
            polygon.strokeColor = [UIColor redColor];
            polygon.fillColor = [UIColor greenColor];
            polygon.lineWidth = 1;
            polygon.title = @"三角形";
            polygon.titleSize = 15;
            polygon.titleColor = [UIColor grayColor];
            
            overlay = polygon;
        }
            break;
        case 5:    //文字
        {
            ISM_MAP_POINT point;
            point.x = 60.00;
            point.y = 60.00;
            
            INNSMap_TextTitle *textTitle = [[INNSMap_TextTitle alloc]init];
            textTitle.titleString = @"Hello!";
            textTitle.fontColor = [UIColor redColor];
            textTitle.fontSize = 17;
            textTitle.addPoint = point;
            
            overlay = textTitle;
        }
            break;
        case 6:    //图片
        {
            ISM_MAP_POINT point;
            point.x = 30.00;
            point.y = 30.00;
            
            UIImage *image = [UIImage imageNamed:@"起点"];
            
            INNSMap_Image *innsMapImage = [[INNSMap_Image alloc]initWithINImage:image withInPoint:point];
            innsMapImage.imageTitle = @"谁";
            innsMapImage.fontSize = 15;
            innsMapImage.titleColor = [UIColor redColor];
            
            overlay = innsMapImage;
        }
            break;
        case 7:    //气泡
        {
            ISM_MAP_POINT point;
            point.x = 100.00;
            point.y = 100.00;
            
            NSString *connet = @"Hello!";
            
            INNSMap_Bubble *bubble = [[INNSMap_Bubble alloc]initWithTitle:connet addPoint:point];
            bubble.titleColor = [UIColor greenColor];
            bubble.fontSize = 12;
            
            overlay = bubble;
        }
            break;
        case 8:    //删除所有覆盖物
        {
            if (_RemoveAllOverlays)
            {
                _RemoveAllOverlays();
            }
            
            return;
        }
            break;
            
        default:
            break;
    }

    
    
    if(_OverlayBack)
    {
        _OverlayBack(overlay);
    }
}


@end
