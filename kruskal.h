#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "heapsort.h"
#include "building.h"
#include <vector>
#include <cmath>

int u_find(int x, std::vector<int> &pre)
{
    if(pre[x] != x)
        pre[x] = u_find(pre[x], pre);
    return pre[x];
}

void u_union(int x, int y, std::vector<int> &pre)
{
    int prex = u_find(x, pre);
    int prey = u_find(y, pre);
    pre[prex] = prey;
}

std::vector<Edge> kruskal(std::vector<Building> &buildings)
{
    std::vector<int> pre;
    int i, j, edgenum = 0, buildingnum = int(buildings.size()) - 1;
    Edge tempedge;
    std::vector<Edge> edges;
    edges.clear();
    edges.push_back(tempedge);
    for(i = 1;i < buildingnum;i++)
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

    heapsort(edgenum, edges);
    pre.clear();
    pre.push_back(0);
    for(i = 1;i <= buildingnum;i++)
        pre.push_back(i);

    std::vector<Edge> result;
    result.clear();
    result.push_back(tempedge);
    while(int(result.size()) < buildingnum)
    {
        if(u_find(edges[1].x, pre) != u_find(edges[1].y, pre))
        {
            u_union(edges[1].x, edges[1].y, pre);
            result.push_back(edges[1]);
        }
        edges[1].dis = 999999.9;//相当于正无穷
        headadjust(edgenum, 1, edges);
    }
    return result;
}

#endif // KRUSKAL_H
