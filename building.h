#ifndef BUILDING_H
#define BUILDING_H

#include <string>

//建筑物：名称，X 坐标，Y 坐标
class Building
{
public:
    Building(std::string a = std::string(""), double b = 0.0, double c = 0.0)
        :name(a), x(b), y(c){}

    std::string name;
    double x, y;
};

//两个建筑物之间的边：起始编号，目标编号，距离
class Edge
{
public:
    Edge(){}

    int x, y;
    double dis;
};

#endif // BUILDING_H
