#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "building.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addBuilding(); //向表格中加入建筑物使其显示

private slots:
    void on_action_import_triggered(); //从文件导入数据

    void on_action_image_triggered();

    void on_action_exit_triggered(); //退出程序

    void on_pushButton_add_clicked(); //添加建筑

    void on_pushButton_random_clicked(); //随机加入建筑

    void on_pushButton_delete_clicked(); //删除选中的建筑

    void on_pushButton_clear_clicked(); //清空建筑

    void on_tableWidget_buildings_activated(); //选中建筑后高亮图中对应的点

private:
    Ui::MainWindow *ui;
    std::vector<Building> buildings; //当前建筑物
};

#endif // MAINWINDOW_H
