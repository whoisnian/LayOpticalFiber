#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "building.h"
#include <vector>

void headadjust(int num, int nowedge, std::vector<Edge> &edges)
{
    if(nowedge > num / 2)
        return;

    int minedge = nowedge;;
    double mindis = edges[nowedge].dis;

    if(mindis > edges[2 * nowedge].dis)
    {
        minedge = 2 * nowedge;
        mindis = edges[2 * nowedge].dis;
    }
    if(2 * nowedge + 1 <= num&&mindis > edges[2 * nowedge + 1].dis)
    {
        minedge = 2 * nowedge + 1;
        mindis = edges[2 * nowedge + 1].dis;
    }
    if(minedge != nowedge)
    {
        std::swap(edges[nowedge], edges[minedge]);
        headadjust(num, minedge, edges);
    }
}

void heapsort(int num, std::vector<Edge> &edges)
{
    for(int i = num / 2;i >= 1;i--)
        headadjust(num, i, edges);
}

#endif // HEAPSORT_H
