#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "kruskal.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QFile>
#include <QDebug>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //给显示建筑物的表格设置表头
    QStringList header;
    header << "建筑名称" << "X坐标" << "Y坐标";
    ui->tableWidget_buildings->setHorizontalHeaderLabels(header);
    buildings.push_back(Building());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addBuilding()
{
    ui->tableWidget_buildings->setRowCount(int(buildings.size())-1);
    QTableWidgetItem *Name = new QTableWidgetItem(QString(buildings.back().name.c_str()));
    QTableWidgetItem *X = new QTableWidgetItem(QString::number(buildings.back().x, 10, 2));
    QTableWidgetItem *Y = new QTableWidgetItem(QString::number(buildings.back().y, 10, 2));
    ui->tableWidget_buildings->setItem(buildings.size()-2, 0, Name);
    ui->tableWidget_buildings->setItem(buildings.size()-2, 1, X);
    ui->tableWidget_buildings->setItem(buildings.size()-2, 2, Y);
    qDebug() << "添加：" << buildings.back().name.c_str() << buildings.back().x << buildings.back().y;
}

void MainWindow::on_action_import_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "选择要导入的文件", "/");
    if(fileName == NULL)
        return;
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    while(!file.atEnd())
    {
        QString line = file.readLine();
        buildings.push_back(Building(line.split(QRegExp("\\s+"))[0].toStdString(), line.split(QRegExp("\\s+"))[1].toDouble(), line.split(QRegExp("\\s+"))[2].toDouble()));
        addBuilding();
    }
    file.close();
    ui->widget_result->setBuildings(buildings);
    ui->widget_result->setResult(kruskal(buildings));
    ui->widget_result->repaint();
}

void MainWindow::on_action_exit_triggered()
{
    this->close();
}

void MainWindow::on_pushButton_add_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "名称", "请输入建筑名称：", QLineEdit::Normal, "", &ok);
    if(!ok) return;
    double x = QInputDialog::getDouble(this, "X坐标", "请输入X坐标（0-1000）：", 0.00, 0, 1000, 2, &ok);
    if(!ok) return;
    double y = QInputDialog::getDouble(this, "Y坐标", "请输入Y坐标（0-1000）：", 0.00, 0, 1000, 2, &ok);
    if(!ok) return;
    buildings.push_back(Building(name.toStdString(), x, y));
    ui->widget_result->setBuildings(buildings);
    ui->widget_result->setResult(kruskal(buildings));
    ui->widget_result->repaint();
    addBuilding();
}

void MainWindow::on_pushButton_random_clicked()
{
    static int click_num = 1;
    srand(clock());
    double x = rand() % 1000;
    double y = rand() % 1000;

    QString name = QString("test ") + QString::number(click_num++, 10);
    buildings.push_back(Building(name.toStdString(), x, y));
    ui->widget_result->setBuildings(buildings);
    ui->widget_result->setResult(kruskal(buildings));
    ui->widget_result->repaint();
    addBuilding();
}

void MainWindow::on_pushButton_delete_clicked()
{
    int row = ui->tableWidget_buildings->currentRow();
    if(row == -1)
    {
         QMessageBox::information(this, "缺少目标", "请在右侧窗口选中要删除的目标后再进行删除", QMessageBox::Ok, QMessageBox::Ok);
         return;
    }
    qDebug() << "删除：" << buildings[row+1].name.c_str() << buildings[row+1].x << buildings[row+1].y;

    ui->tableWidget_buildings->removeRow(row);
    buildings.erase(buildings.begin() + row + 1);

    ui->widget_result->setBuildings(buildings);
    ui->widget_result->setResult(kruskal(buildings));
    ui->widget_result->repaint();
}

void MainWindow::on_pushButton_clear_clicked()
{
    buildings.clear();
    buildings.push_back(Building());
    ui->widget_result->setBuildings(buildings);
    ui->widget_result->setResult(kruskal(buildings));
    ui->tableWidget_buildings->clearContents();
    ui->tableWidget_buildings->setRowCount(int(buildings.size())-1);
    ui->widget_result->repaint();
    qDebug() << "清空";
}

void MainWindow::on_tableWidget_buildings_activated()
{
    ui->widget_result->setActivatedRadio(ui->tableWidget_buildings->currentRow());
    qDebug() << "高亮：" << buildings[ui->tableWidget_buildings->currentRow()+1].name.c_str();
}
