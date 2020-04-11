#include "mainwindow.h"
#include "ui_mainwindow.h"

QImage image(500, 500, QImage::Format_RGB888);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(image));
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

void MainWindow::move(int j,int h,int &x,int &y)
{
    int x_old, y_old;
    x_old = x;
    y_old = y;

    if(j==1)
        y-=h;
    else if(j==2)
        x+=h;
    else if(j==3)
        y+=h;
    else if(j==4)
        x-=h;
    dda(x_old, y_old, x, y);
}


void MainWindow::hilbert(int r,int d,int l,int u,int i,int h,int &x,int &y)
{
    if(i>0)
    {
        i--;
        hilbert(d,r,u,l,i,h,x,y);
        move(r,h,x,y);
        hilbert(r,d,l,u,i,h,x,y);
        move(d,h,x,y);
        hilbert(r,d,l,u,i,h,x,y);
        move(l,h,x,y);
        hilbert(u,l,d,r,i,h,x,y);
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    int x0=100,y0=100,x,y,h=20,r=2,d=3,l=4,u=1;

    int n = 4;
    x=x0;y=y0;

    hilbert(r,d,l,u,n,h,x,y);

    for (int c = 1; c <= 32767; c++)
    {

        for (int d = 1; d <= 32767; d++)
        {
                // for producing delay
        }
    }
}
