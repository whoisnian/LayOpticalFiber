#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include "building.h"
#include <QDialog>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QRadioButton>
#include <QButtonGroup>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImageDialog(QWidget *parent = 0);
    ~ImageDialog();

    std::vector<Building> buildings; //在图片上选择的建筑物
    void setimage(QString filename, int mx, int mh); //要打开的图片

private:
    Ui::ImageDialog *ui;

protected:
    void mouseReleaseEvent(QMouseEvent *event); //点击事件触发时记录坐标
};

#endif // IMAGEDIALOG_H
