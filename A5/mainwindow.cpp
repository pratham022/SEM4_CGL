#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include "iostream"
using namespace std;

QImage image(600, 600, QImage::Format_RGB888);



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap::fromImage(image));
}

MainWindow::~MainWindow()
{
    delete ui;
}

class Point
{
    double x_co, y_co;
    friend class MainWindow;
};
Point centrePts[10];
Point centrePtsRot[10];

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


void MainWindow::bresErase(float x1, float y1, float x2, float y2)      // erasing the old lines
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
            image.setPixel(x1, y1, qRgb(0, 0, 0));
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
            image.setPixel(x1, y1, qRgb(0, 0, 0));
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
        image.setPixel(x1, y1, qRgb(0, 0, 0));
        x1++;
        y1++;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}


void MainWindow::on_pushButton_clicked()
{
    float x = 70;
    double one = x/2;
    double three = 3*x/2;
    double five = 5*x/2;
    double seven = 7*x/2;
    float x1, y1, x2, y2;
    int i;
    for(i=0;i<5;i++)
    {
        bresenham(i*x, 0, i*x, 4*x);            // drawing vertical lines
    }
    for(i=0;i<5;i++)
    {
        bresenham(0, i*x, 4*x, i*x);            // horizontal lines
    }
    centrePts[0].x_co = three;
    centrePts[0].y_co = one;

    centrePts[1].x_co = seven;
    centrePts[1].y_co = one;

    centrePts[2].x_co = one;
    centrePts[2].y_co = three;

    centrePts[3].x_co = five;
    centrePts[3].y_co = three;

    centrePts[4].x_co = three;
    centrePts[4].y_co = five;

    centrePts[5].x_co = seven;
    centrePts[5].y_co = five;

    centrePts[6].x_co = one;
    centrePts[6].y_co = seven;

    centrePts[7].x_co = five;
    centrePts[7].y_co = seven;
    // we have stored the centre points of the coloured boxes in centrePts object array
    for(int i=0;i<8;i++)
    {
        cout<<"initial centre pts"<<endl;
        cout<<centrePts[i].x_co<<" "<<centrePts[i].y_co<<endl;
    }
    for(int i=0;i<8;i++)
    {
        boundary(centrePts[i].x_co, centrePts[i].y_co, qRgb(255, 0, 0), qRgb(0, 255, 0));   // filling alternate boxes
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::boundary(int x, int y, QRgb fillcol, QRgb boundcol)
{
    QRgb tempcol = image.pixel(x, y);
    if(tempcol!=boundcol && tempcol!=fillcol)
    {
        image.setPixel(x, y, fillcol);
        boundary(x+1, y, fillcol, boundcol);
        boundary(x, y+1, fillcol, boundcol);
        if(x-1>0)
            boundary(x-1, y, fillcol, boundcol);
        if(y-1>0)
            boundary(x, y-1, fillcol, boundcol);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    erase();
    rotate();
}

void MainWindow::erase()
{
    float x = 70;
    int one = x/2;
    int three = 3*x/2;
    int five = 5*x/2;
    int seven = 7*x/2;
    float x1, y1, x2, y2;
    int i;

    //removing the color of initial boxes
    for(i=0;i<8;i++)
    {
        boundary(centrePts[i].x_co, centrePts[i].y_co, qRgb(0, 0, 0), qRgb(0, 0, 0));
    }

    for(i=0;i<5;i++)
    {
        bresErase(i*x, 0, i*x, 4*x);            // erasing vertical lines
    }
    for(i=0;i<5;i++)
    {
        bresErase(0, i*x, 4*x, i*x);            // horizontal lines
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}


void MainWindow::rotate()
{
    float x = 70;

    double angle = (-1)*45*3.14/180;
    double rotationMat[3][3];       // 3x3 rotation matrix
    double initialMat[1][3];
    double finalMat[1][3];

    double res_hori[10][2];           // to store the initial vertices on horizontal axis after rotation
    double res_vert[10][2];           // to store the initial vertices on vertical axis after rotation
    int t1=0, t2=0;

    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            rotationMat[i][j] = 0;
        }
    }
    rotationMat[0][0] = rotationMat[1][1] = cos(angle);
    rotationMat[0][1] = -1*sin(angle);
    rotationMat[1][0] = sin(angle);
    rotationMat[2][2] = 1;
    // rotation matrix initialised

    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            initialMat[0][0] = j*x;
            initialMat[0][1] = i*x;
            initialMat[0][2] = 1;
            // initial matrix initialised

            finalMat[0][0] = finalMat[0][1] = finalMat[0][2] = 0;
            // final matrix also intialised

            for(int p=0;p<1;p++)
            {
                for(int q=0;q<3;q++)
                {
                    for(int r=0;r<3;r++)
                    {
                        finalMat[p][q] += initialMat[p][r] * rotationMat[r][q];
                    }
                }
            }
//            // plot the resultant point
            finalMat[0][0] += 250;
            finalMat[0][1] += 150;
            image.setPixel(finalMat[0][0], finalMat[0][1], qRgb(255, 0, 0));

            if(i==0 || i==4)
            {
                res_vert[t1][0] = finalMat[0][0];
                res_vert[t1][1] = finalMat[0][1];
                t1++;
            }
            if(j==0 || j==4)
            {
                res_hori[t2][0] = finalMat[0][0];
                res_hori[t2][1] = finalMat[0][1];
                t2++;
            }
        }
    }

    // finding the co-ordinates of centre points after rotation
    for(int i=0;i<8;i++)
    {
        initialMat[0][0] = centrePts[i].x_co;
        initialMat[0][1] = centrePts[i].y_co;
        initialMat[0][2] = 1;
        // initial matrix initialised

        finalMat[0][0] = finalMat[0][1] = finalMat[0][2] = 0;
        // final matrix also intialised

        for(int p=0;p<1;p++)
        {
            for(int q=0;q<3;q++)
            {
                for(int r=0;r<3;r++)
                {
                    finalMat[p][q] += initialMat[p][r] * rotationMat[r][q];
                }
            }
        }
        finalMat[0][0] += 250;
        finalMat[0][1] += 150;
        centrePtsRot[i].x_co = finalMat[0][0];
        centrePtsRot[i].y_co = finalMat[0][1];
    }

    for(int i=0;i<8;i++)
    {
        cout<<"center position after rotation"<<endl;
        cout<<centrePtsRot[i].x_co<<" "<<centrePtsRot[i].y_co<<endl;
    }


    for(int i=0;i<5;i++)
    {
        dda(res_vert[5+i][0], res_vert[5+i][1], res_vert[i][0], res_vert[i][1]);
        cout<<"line drawn"<<endl;
    }
    for(int i=0;i<9;i+=2)
    {
        dda(res_hori[i][0], res_hori[i][1], res_hori[i+1][0], res_hori[i+1][1]);
    }

    for(int i=0;i<8;i++)
    {
        boundary(centrePtsRot[i].x_co, centrePtsRot[i].y_co, qRgb(255, 0, 0), qRgb(0, 255, 0));
    }
     ui->label->setPixmap(QPixmap::fromImage(image));
}
