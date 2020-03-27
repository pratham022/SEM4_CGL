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
        image.setPixel(x1, y1, qRgb(0, 255, 0));
        x1 += xinc;
        y1 += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::dotted(float x1, float y1, float x2, float y2)
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
        if(i%4==0)
            image.setPixel(x1, y1, qRgb(0, 255, 0));
        x1 += xinc;
        y1 += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::dashed(float x1, float y1, float x2, float y2)
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
        if(i%10>=5)
            image.setPixel(x1, y1, qRgb(0, 255, 0));
        x1 += xinc;
        y1 += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::dotDashed(float x1, float y1, float x2, float y2)
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
        if(i%11==3 || i%11==4 || i%11==6 ||i%11==7)
        {}
        else
            image.setPixel(x1, y1, qRgb(0, 255, 0));
        x1 += xinc;
        y1 += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::thick(float x1, float y1, float x2, float y2)
{
    float m, wx, wy;
    int x, y, dx, dy, p, i;
    x=x1;   y=y1;
    dx=x2-x1;
    dy=y2-y1;
    if(dx==0)
        m=999999;
    else
        m=dy/dx;

    if(m<1)
    {
        wy=(10-1)*sqrt(pow((x2-x1),2)+pow((y2-y1),2))/(2*fabs(x2-x1));
        for(i=0;i<wy;i++)
        {
            dda(x1,y1-i,x2,y2-i);
            dda(x1,y1+i,x2,y2+i);
        }
    }
     else
    {
        wx=(10-1)*sqrt(pow((x2-x1),2)+pow((y2-y1),2))/(2*fabs(y2-y1));
        for(i=0;i<wx;i++)
        {
            dda(x1-i,y1,x2-i,y2);
            dda(x1+i,y1,x2+i,y2);
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    float x1 = ui->textEdit->toPlainText().toFloat();
    float y1 = ui->textEdit_2->toPlainText().toFloat();
    float x2 = ui->textEdit_3->toPlainText().toFloat();
    float y2 = ui->textEdit_4->toPlainText().toFloat();
    dda(x1, y1, x2, y2);
}

void MainWindow::on_pushButton_2_clicked()
{
    float x1 = ui->textEdit->toPlainText().toFloat();
    float y1 = ui->textEdit_2->toPlainText().toFloat();
    float x2 = ui->textEdit_3->toPlainText().toFloat();
    float y2 = ui->textEdit_4->toPlainText().toFloat();
    dotted(x1, y1, x2, y2);
}

void MainWindow::on_pushButton_3_clicked()
{
    float x1 = ui->textEdit->toPlainText().toFloat();
    float y1 = ui->textEdit_2->toPlainText().toFloat();
    float x2 = ui->textEdit_3->toPlainText().toFloat();
    float y2 = ui->textEdit_4->toPlainText().toFloat();
    dashed(x1, y1, x2, y2);
}

void MainWindow::on_pushButton_4_clicked()
{
    float x1 = ui->textEdit->toPlainText().toFloat();
    float y1 = ui->textEdit_2->toPlainText().toFloat();
    float x2 = ui->textEdit_3->toPlainText().toFloat();
    float y2 = ui->textEdit_4->toPlainText().toFloat();
    dotDashed(x1, y1, x2, y2);
}

void MainWindow::on_pushButton_5_clicked()
{
    float x1 = ui->textEdit->toPlainText().toFloat();
    float y1 = ui->textEdit_2->toPlainText().toFloat();
    float x2 = ui->textEdit_3->toPlainText().toFloat();
    float y2 = ui->textEdit_4->toPlainText().toFloat();
    thick(x1, y1, x2, y2);
}
