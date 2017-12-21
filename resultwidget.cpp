#include "resultwidget.h"
#include "ui_resultwidget.h"
#include <QPainter>
#include <QRadioButton>
#include <QStatusBar>
#include <algorithm>

ResultWidget::ResultWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResultWidget)
{
    ui->setupUi(this);
    radiogroup = new QButtonGroup;
    connect(radiogroup , SIGNAL(buttonClicked(int)),this,SLOT(radiogroup_buttonClicked()));
}

ResultWidget::~ResultWidget()
{
    delete ui;
}

void ResultWidget::setBuildings(std::vector<Building> buildings)
{
    this->buildings = buildings;
    this->updateRadio();
}

void ResultWidget::setResult(std::vector<Edge> result)
{
    this->result = result;
}

void ResultWidget::setActivatedRadio(int index)
{
    radiogroup->button(index)->setChecked(true);
}

void ResultWidget::setBuildingTable(QTableWidget *table)
{
    buildingtable = table;
}

void ResultWidget::setBar(QStatusBar *bar)
{
    statusbar = bar;
}

void ResultWidget::updateRadio(void)
{

    double min_x = 1000, min_y = 1000, max_x = 0, max_y = 0;
    for(int i = 1;i < int(buildings.size());i++)
    {
        min_x = std::min(buildings[i].x, min_x);
        min_y = std::min(buildings[i].y, min_y);
        max_x = std::max(buildings[i].x, max_x);
        max_y = std::max(buildings[i].y, max_y);
    }
    //当只有一个点时，直接画到中间，不需要缩放
    if(buildings.size() > 2)
        improve = std::max((max_x - min_x) / (this->width() - 50), (max_y - min_y) / (this->height() - 50));
    else
        improve = 1;
    ori_x = min_x / improve - (this->width() - (max_x - min_x) / improve) / 2;
    ori_y = min_y / improve - (this->height() - (max_y - min_y) / improve) / 2;


    QList<QAbstractButton *> buttons = radiogroup->buttons();
    for(int i = 0;i < buttons.size();i++)
    {
        buttons.at(i)->setVisible(false);
        radiogroup->removeButton(buttons.at(i));
    }
    for(int i = 1;i < int(buildings.size());i++)
    {
        QRadioButton *radio = new QRadioButton(this);
        radio->setGeometry(int(buildings[i].x / improve - ori_x) - 10, int(buildings[i].y / improve - ori_y) - 10, 20, 20);
        radio->setToolTip(QString(buildings[i].name.c_str()));
        radio->setToolTipDuration(-1);
        radio->setCheckable(true);
        radio->setVisible(true);
        radiogroup->addButton(radio);
        radiogroup->setId(radio, i-1);
    }
}

void ResultWidget::radiogroup_buttonClicked()
{
    radiogroup->checkedId();
    buildingtable->selectRow(radiogroup->checkedId());
    statusbar->showMessage(radiogroup->checkedButton()->toolTip());
}

void ResultWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    for(int i = 1;i < int(result.size());i++)
    {
        painter.drawLine(QPoint(int(buildings[result[i].x].x / improve - ori_x), int(buildings[result[i].x].y / improve - ori_y)), QPoint(int(buildings[result[i].y].x / improve - ori_x), int(buildings[result[i].y].y / improve - ori_y)));
    }
}

void ResultWidget::resizeEvent(QResizeEvent *)
{
    this->updateRadio();
    this->repaint();
}
