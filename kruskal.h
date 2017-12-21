#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "heapsort.h"
#include "building.h"
#include <vector>
#include <cmath>

int u_find(int x, std::vector<int> &pre)//并查集_查找操作
{
    if(pre[x] != x)//如果当前结点所属集合编号不是自己
        pre[x] = u_find(pre[x], pre);//查找父节点的同时，更新自己所属集合的编号
    return pre[x];//返回所属集合编号
}

void u_union(int x, int y, std::vector<int> &pre)//并查集_合并操作
{
    int prex = u_find(x, pre);
    int prey = u_find(y, pre);
    pre[prex] = prey;//合并
}

std::vector<Edge> kruskal(std::vector<Building> &buildings)//克鲁斯卡尔算法：buildings内存储点的信息
{
    std::vector<int> pre;//并查集用
    std::vector<Edge> result;//保存结果边集用
    int i, j, edgenum = 0, buildingnum = int(buildings.size()) - 1;//为方便堆排序，数组从下标为1开始存储，故buildingnum表示点的数量
    Edge tempedge;
    std::vector<Edge> edges;//存储边集
    edges.clear();
    edges.push_back(tempedge);//随便在0下标处存一个东西
    for(i = 1;i < buildingnum;i++)//计算所有边长并保存
    {
        for(j = i + 1;j <= buildingnum;j++)
        {
            tempedge.x = i;
            tempedge.y = j;
            double disx, disy;
            disx = buildings[i].x - buildings[j].x;
            disy = buildings[i].y - buildings[j].y;
            tempedge.dis = sqrt(disx * disx + disy * disy);
            edges.push_back(tempedge);
            edgenum++;
        }
    }
    heapsort(edgenum, edges);//对边集进行堆排序初始化
    pre.clear();
    pre.push_back(0);//随便在0下标处存一个东西
    for(i = 1;i <= buildingnum;i++)
        pre.push_back(i);
    result.clear();
    result.push_back(tempedge);//随便在0下标处存一个东西
    while(int(result.size()) < buildingnum)
    {
        if(u_find(edges[1].x, pre) != u_find(edges[1].y, pre))//若当前边两个端点不属于同一集合
        {
            u_union(edges[1].x, edges[1].y, pre);//合并
            result.push_back(edges[1]);//将这条边加入答案
        }
        edges[1].dis = 999999.9;//相当于正无穷
        headadjust(edgenum, 1, edges);//调整堆
    }
    return result;
}

#endif // KRUSKAL_H
