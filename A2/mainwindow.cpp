#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"

QImage image(600, 600, QImage::Format_RGB888);
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
        image.setPixel(x1, y1, qRgb(0, 255, 255));
        x1 += xinc;
        y1 += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::drawCircle(float xc, float yc, float x, float y)
{
    image.setPixel(xc+x, yc+y, qRgb(0, 255, 255));
    image.setPixel(xc-x, yc+y, qRgb(0, 255, 255));
    image.setPixel(xc+x, yc-y, qRgb(0, 255, 255));
    image.setPixel(xc-x, yc-y, qRgb(0, 255, 255));
    image.setPixel(xc+y, yc+x, qRgb(0, 255, 255));
    image.setPixel(xc-y, yc+x, qRgb(0, 255, 255));
    image.setPixel(xc+y, yc-x, qRgb(0, 255, 255));
    image.setPixel(xc-y, yc-x, qRgb(0, 255, 255));
}
void MainWindow::bresCircle(float xc, float yc, float r)
{
    float p, x, y;

    x=0;
    y=r;
    p = 3-2*r;
    drawCircle(xc, yc, x, y);
    while(x<=y)
    {
        x++;
        if(p>0)
        {
            y--;
            p= p+4*(x-y)+10;
        }
        else
            p=p+4*x+6;
        drawCircle(xc, yc, x, y);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::ddaCircle(float xc,float yc, float r)
{
    float xc1,xc2,yc1,yc2,eps,sx,sy;
    int i, val;
    xc1=r;
    yc1=0;
    sx=xc1;
    sy=yc1;
    i=0;

    do{
        val=pow(2, i);
        i++;
    }while(val<r);
    eps = 1/pow(2,i-1);
    do{
        xc2 = xc1 + yc1*eps;
        yc2 = yc1 - eps*xc2;
        image.setPixel(xc+xc2,yc-yc2, qRgb(0, 255, 255));
        xc1=xc2;
        yc1=yc2;
       }while((yc1-sy)<eps || (sx-xc1)>eps);
    ui->label->setPixmap(QPixmap::fromImage(image));

}

void MainWindow::on_pushButton_clicked()
{
    float r = ui->textEdit->toPlainText().toFloat();
    float xc = ui->textEdit_2->toPlainText().toFloat();
    float yc = ui->textEdit_3->toPlainText().toFloat();

    bresCircle(xc, yc, r);
    dda(xc, (yc-r), (xc-1.71*r/2), (yc+r/2));
    dda((xc-1.71*r/2), (yc+r/2), (xc+1.71*r/2), (yc+r/2));
    dda(xc, (yc-r), (xc+1.71*r/2), (yc+r/2));
    ddaCircle(xc, yc, r/2);
}
