#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
using namespace std;

QImage image(500, 500, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
        image.setPixel(x1, y1, qRgb(0, 255, 0));
        x1 += xinc;
        y1 += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::bresenham(float x1, float y1, float x2, float y2)
{
    float dx, dy, m, p;
    dx = x2-x1;
    dy = y2-y1;
    if(dx == 0)
        m = 9999999;
    else
        m = dy/dx;

    if(m<1)
    {
        p = 2*dy-dx;
        while (x1<=x2)
        {
            image.setPixel(x1, y1, qRgb(0, 255, 0));
            if(p<0)
                p=p+2*dy;
            else
            {
                p=p+(2*dy)-(2*dx);
                y1++;
            }
            x1++;
        }
    }
    else if(m>1)
    {
        p=2*dx-dy;
        while(y1<=y2)
        {
            image.setPixel(x1, y1, qRgb(0, 255, 0));
            if(p<0)
                p=p+2*dx;
            else
            {
                p=p+(2*dx)-(2*dy);
                x1++;
            }
            y1++;
        }
    }
    else
    {
        image.setPixel(x1, y1, qRgb(0, 255, 0));
        x1++;
        y1++;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int l = ui->textEdit->toPlainText().toInt();
    int b = ui->textEdit_2->toPlainText().toInt();

    bresenham(150, 100, l+150, 100);
    bresenham(150, 100, 150, b+100);
    bresenham(150, b+100, l+150, b+100);
    bresenham(l+150, 100, l+150, b+100);

    dda((l/2)+150, 100, 150, (b/2)+100);
    dda(150, (b/2)+100, (l/2)+150, b+100);
    dda((l/2)+150, b+100, l+150, (b/2)+100);
    dda((l/2)+150, 100, l+150, (b/2)+100);

    bresenham((l/4)+150, (b/4)+100, (l/4)+150, (3*b/4)+100);
    bresenham((l/4)+150, (3*b/4)+100, (3*l/4)+150, (3*b/4)+100);
    bresenham((l/4)+150, (b/4)+100, (3*l/4)+150, (b/4)+100);
    bresenham((3*l/4)+150, (b/4)+100, (3*l/4)+150, (3*b/4)+100);
}
