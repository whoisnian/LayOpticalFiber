#include "imagedialog.h"
#include "ui_imagedialog.h"
#include <QDebug>
#include <QInputDialog>
#include <QPainter>

ImageDialog::ImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImageDialog)
{
    ui->setupUi(this);
    buildings.push_back(Building());
}

ImageDialog::~ImageDialog()
{
    delete ui;
}

void ImageDialog::setimage(QString filename, int mw, int mh)
{
    QImage img;
    img.load(filename);
    if(img.width() * mh < img.height() * mw)
        img = img.scaledToHeight(mh);
    else
        img = img.scaledToWidth(mw);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap::fromImage(img)));
    this->setPalette(palette);
    this->setFixedSize(img.width(), img.height());
    this->setWindowTitle(QString("已选取建筑： 0"));
}

void ImageDialog::mouseReleaseEvent(QMouseEvent *event)
{
    bool ok;
    QString name = QInputDialog::getText(this, "名称", "请输入建筑名称：", QLineEdit::Normal, "", &ok);
    if(!ok) return;
    this->setWindowTitle(QString("已选取建筑： ") + QString::number(buildings.size(), 10));
    buildings.push_back(Building(name.toStdString(), double(event->x()), double(event->y())));
    QRadioButton *radio = new QRadioButton(this);
    radio->setGeometry(event->x() - 10, event->y() - 10, 20, 20);
    radio->setToolTip(name);
    radio->setToolTipDuration(-1);
    radio->setCheckable(false);
    radio->setStyleSheet(QString("QRadioButton::indicator {\nbackground-color: red;\nborder-style:solid;\nborder-width: 3px;\nborder-color: white;\n}"));
    radio->setVisible(true);
}
