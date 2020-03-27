#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"

QImage image(800, 800, QImage::Format_RGB888);
int x_co[20];
int y_co[20];
int r = 0;
int g = 0;
int b = 0;
int x1, y1, x2, y2;
int i = 0;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::dda(float x1, float y1, float x2, float y2)
{
    float xinc, yinc, steps, dx, dy;
    dx = x2-x1;
    dy = y2-y1;
    if(abs(dx) > abs(dy))
        steps = abs(dx);
    else
        steps = abs(dy);
    xinc = dx/steps;
    yinc = dy/steps;
    for(int i=0;i<steps;i++)
    {
        image.setPixel(x1, y1, qRgb(r, g, b));
        x1 += xinc;
        y1 += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_clicked()
{
    dda(100, 100, 600, 100);
    dda(100, 600, 100, 100);
    dda(100, 600, 600, 600);
    dda(600, 100, 600, 600);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        x1 = event->pos().x();
        y1 = event->pos().y();
        image.setPixel(x1, y1, qRgb(0, 255, 0));
        x_co[i] = x1;
        y_co[i] = y1;
        i++;
        ui->label->setPixmap(QPixmap::fromImage(image));
    }
    else if(event->button() == Qt::RightButton)
    {
        x1 = event->pos().x();
        y1 = event->pos().y();
        image.setPixel(x1, y1, qRgb(0, 255, 0));
        ui->label->setPixmap(QPixmap::fromImage(image));
        x_co[i] = x1;
        y_co[i] = y1;
        i++;
        int j;
        for(j=0;j<i-1;j++)
        {
            dda(x_co[j+1], y_co[j+1], x_co[j], y_co[j]);
        }
        dda(x_co[j], y_co[j], x_co[0], y_co[0]);
        ui->label->setPixmap(QPixmap::fromImage(image));
        i = 0;
    }
}

void MainWindow::on_pushButton_2_clicked()
{

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    r = ui->horizontalSlider->value();
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    g = ui->horizontalSlider_2->value();
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value)
{
    b = ui->horizontalSlider_3->value();
}
