#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "building.h"
#include <vector>

void headadjust(int num, int nowedge, std::vector<Edge> &edges)//调整某个结点
{
    if(nowedge > num / 2)//当前点已没有子节点
        return;

    int minedge = nowedge;;
    double mindis = edges[nowedge].dis;

    if(mindis > edges[2 * nowedge].dis)//若左子节点权值较小
    {
        minedge = 2 * nowedge;
        mindis = edges[2 * nowedge].dis;
    }
    if(2 * nowedge + 1 <= num&&mindis > edges[2 * nowedge + 1].dis)//若右子节点权值较小
    {
        minedge = 2 * nowedge + 1;
        mindis = edges[2 * nowedge + 1].dis;
    }
    if(minedge != nowedge)//若三个点中最小的点不是当前点
    {
        std::swap(edges[nowedge], edges[minedge]);//交换当前点和最小点
        headadjust(num, minedge, edges);//更新下一层结点
    }
}

void heapsort(int num, std::vector<Edge> &edges)//初始化堆
{
    for(int i = num / 2;i >= 1;i--)
        headadjust(num, i, edges);
}

#endif // HEAPSORT_H
