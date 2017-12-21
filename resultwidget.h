#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include "building.h"
#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>
#include <QTableWidget>
#include <QStatusBar>

namespace Ui {
class ResultWidget;
}

class ResultWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ResultWidget(QWidget *parent = 0);
    ~ResultWidget();

    void setBuildings(std::vector<Building> buildings); //设置代表建筑物的点
    void setResult(std::vector<Edge> result); //设置连接建筑物之间的线
    void setActivatedRadio(int index); //高亮某个点
    void setBuildingTable(QTableWidget *table); //关联显示建筑物的表格
    void setBar(QStatusBar *bar); //关联主窗口状态栏
    void updateRadio(void); //显示代表建筑物的点

private slots:
    void radiogroup_buttonClicked(); //选中图中的点后高亮表中对应的建筑

private:
    Ui::ResultWidget *ui;
    std::vector<Building> buildings; //当前建筑物
    std::vector<Edge> result; //当前建筑物之间的线
    QButtonGroup *radiogroup; //代表建筑物的点
    QTableWidget *buildingtable; //显示建筑物的表格
    QStatusBar *statusbar; //状态栏

    //用于适当缩小生成的图形并移动到窗口中央
    double ori_x; //X坐标偏移量
    double ori_y; //Y坐标偏移量
    double improve; //坐标缩小倍数

protected:
    void paintEvent(QPaintEvent *); //绘制线条
    void resizeEvent(QResizeEvent *); //窗口大小调整时重绘
};

#endif // RESULTWIDGET_H
