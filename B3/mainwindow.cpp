#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "iostream"
using namespace std;


QImage image(500, 500, QImage::Format_RGB888);
int x1, x2, y1, y2;
int LEFT=1, RIGHT=2, BOTTOM=4, TOP=8;				// opcodes for regions
int xmin, xmax, ymin, ymax;

class Data{
public:
    int x1, y1, x2, y2;
    void setData(int x1, int y1, int x2, int y2)
    {
        this->x1=x1;
        this->y1=y1;
        this->x2=x2;
        this->y2=y2;
    }
};

Data obj[100];
int i;

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

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        x1 = event->pos().x();
        y1 = event->pos().y();
    }
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        x2 = event->pos().x();
        y2 = event->pos().y();
        dda(x1, y1, x2, y2);
        obj[i].setData(x1, y1, x2, y2);
        i++;
    }
}

void MainWindow::drawViewport()
{
    dda(x1, y1, x2, y1);
    dda(x1, y1, x1, y2);
    dda(x1, y2, x2, y2);
    dda(x2, y1, x2, y2);

    xmin = x1;
    ymin = y1;
    xmax = x2;
    ymax = y2;
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

void MainWindow::erase(float x1, float y1, float x2, float y2)
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
        image.setPixel(x1, y1, qRgb(0, 0, 0));
        x1 += xinc;
        y1 += yinc;
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}


void MainWindow::on_pushButton_clicked()
{
    erase(x1, y1, x2, y2);
    drawViewport();
}

int MainWindow::getCode(int x, int y)			//predefined algorithm
{
    int code = 0;
    if(y>ymax)
        code = code|BOTTOM;
    if(y<ymin)
        code = code|TOP;
    if(x<xmin)
        code = code|LEFT;
    if(x>xmax)
        code = code|RIGHT;
    return code;
}

void MainWindow::clip(int x1, int y1, int x2, int y2)	// predefined algorithm
{
    int ex1 = x1;
    int ey1 = y1;
    int ex2 = x2;
    int ey2 = y2;
    cout<<"Entered the function"<<endl;
    int outcode1 = getCode(x1, y1);
    int outcode2 = getCode(x2, y2);
    int accept = 0;
    int outcode3 = outcode1 && outcode2;
    int xmid, ymid;
    xmid=(x1+x2)/2;
    ymid=(y1+y2)/2;
    int outmid = getCode(xmid, ymid);
    while(1)
    {
        float m = (float)(y2-y1)/(x2-x1);

        if(outcode1==0 && outcode2==0)
        {
            // both points are inside viewport..accept line
            accept=1;
            break;
        }
        else if(outcode3!=0 && outmid !=0)
        {
            // both codes are not 0..thus line completely lies outside
            // viewport..reject the line
            cout<<"Entered in case2"<<endl;
            erase(ex1, ey1, ex2, ey2);
            break;
        }
        else
        {
            cout<<"candidate of clipping!"<<endl;
            // line is partially inside and parially outside
            int x, y;
            int temp;

            // deciding if point 1 is inside or not
            if(outcode1==0)
                temp=outcode2;
            else
                temp=outcode1;

            if(temp & TOP)
            {
                // line clips top edge
                x = x1 + (ymin-y1)/m;
                y = ymin;
            }
            else if(temp & BOTTOM)
            {
                // line clips bottom edge
                x = x1 + (ymax-y1)/m;
                y = ymax;
            }
            else if(temp & LEFT)
            {
                // line clips left edge
                y = y1 + m*(xmin-x1);
                x=  xmin;
            }
            else if(temp & RIGHT)
            {
                // line clips right edge
                y = y1 + m*(xmax-x1);
                x = xmax;
            }

            // check which pt we had selected as temp and assign its
            // co-ordinates
            if(temp == outcode1)
            {
                x1=x;
                y1=y;
                outcode1=getCode(x1, y1);
            }
            else
            {
                x2=x;
                y2=y;
                outcode2=getCode(x2, y2);
            }
        }
    }
    if(accept)
    {
        erase(ex1, ey1, ex2, ey2);
        drawClipped(x1, y1, x2, y2);
    }
}

void MainWindow::drawClipped(float x1, float y1, float x2, float y2)		// function that draws the final clipped line
{
    float xinc, yinc, steps, dx, dy;
    dx=x2-x1;
    dy=y2-y1;

    if(abs(dx)>abs(dy))
        steps=abs(dx);
    else
        steps=abs(dy);

    xinc=dx/steps;
    yinc=dy/steps;
    float x, y;
    x=x1;
    y=y1;
    for(int i=0;i<steps;i++)
    {
        image.setPixel(x, y, qRgb(0, 255, 0));
        x += xinc;
        y += yinc;
    }
     ui->label->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::on_pushButton_2_clicked()
{
    for(int j=1;j<i;j++)
    {
        clip(obj[j].x1, obj[j].y1, obj[j].x2, obj[j].y2);
    }
    ui->label->setPixmap(QPixmap::fromImage(image));
}
