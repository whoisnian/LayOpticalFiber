#ifndef RESULTWIDGET_H
#define RESULTWIDGET_H

#include "building.h"
#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>

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
    void updateRadio(void); //显示代表建筑物的点

private:
    Ui::ResultWidget *ui;
    std::vector<Building> buildings; //当前建筑物
    std::vector<Edge> result; //当前建筑物之间的线
    QButtonGroup radiogroup; //代表建筑物的点

    //用于适当缩小生成的图形并移动到窗口中央
    double ori_x; //X坐标偏移量
    double ori_y; //Y坐标偏移量
    double improve; //坐标缩小倍数

protected:
    void paintEvent(QPaintEvent *); //绘制线条
    void resizeEvent(QResizeEvent *); //窗口大小调整时重绘
};

#endif // RESULTWIDGET_H
