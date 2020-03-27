#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMouseEvent"
#include "math.h"
#include "iostream"
using namespace std;
QImage image(600, 600,QImage::Format_RGB888);

class Matrix
{
    int mat[1][3];
    friend class MainWindow;
public:
    Matrix()
    {
        mat[0][0] = mat[0][1] = 0;
        mat[0][2] = 0;
    }
    Matrix operator *(double TranslationMat[][3])
    {
        Matrix temp;
        for(int i=0;i<1;i++)
        {
            for(int j=0;j<3;j++)
            {
                for(int k=0;k<3;k++)
                {
                    temp.mat[i][j] += mat[i][k] *   TranslationMat[k][j];
                }
            }
        }
        return temp;
    }
};
Matrix initial;                 // [x, y, 1] matrix
Matrix final;                   // [x', y', 1] matrix


float input[20][2];             // to store the coordinates of input(initial) points
float output[20][2];            // to store the coordinates of final points (after transformation)
int i = 0;
int n, j;

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

void MainWindow::dda(float x1, float y1, float x2, float y2)    // dda() to draw line
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

void MainWindow::mousePressEvent(QMouseEvent *event)        // draw the polygon using mouse interfacing
{
    if(event->button() == Qt::LeftButton)
    {
        input[i][0] = event->pos().x();
        input[i][1] = event->pos().y();
        image.setPixel(input[i][0], input[i][1], qRgb(0, 255, 0));
        cout<<input[i][0]<<" "<<input[i][1]<<endl;
        ui->label->setPixmap(QPixmap::fromImage(image));
        i++;
    }
    else if(event->button() == Qt::RightButton)
    {
        input[i][0] = event->pos().x();
        input[i][1] = event->pos().y();
        image.setPixel(input[i][0], input[i][1], qRgb(0, 255, 0));
        cout<<input[i][0]<<" "<<input[i][1]<<endl;
        ui->label->setPixmap(QPixmap::fromImage(image));
        i++;
        n = i;                                                      // n contains total number of vertices
        for(j=1;j<=i-1;j++)
        {
            dda(input[j][0], input[j][1], input[j-1][0], input[j-1][1]);
        }
        dda(input[j-1][0], input[j-1][1], input[0][0], input[0][1]);
    }
}

void MainWindow::on_pushButton_clicked()
{
    float tx = ui->textEdit->toPlainText().toFloat();
    float ty = ui->textEdit_2->toPlainText().toFloat();
    translate(tx, ty);
    drawPolygon();
}

void MainWindow::translate(float tx, float ty)
{
        double TranslationMat[3][3];       // 3x3 translation matrix
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                TranslationMat[i][j] = 0;
            }
        }
        TranslationMat[0][0] = TranslationMat[1][1] = TranslationMat[2][2] = 1;
        TranslationMat[2][0] = tx;
        TranslationMat[2][1] = ty;
        // translation matrix initialised

        for(i=0;i<n;i++)
        {
            initial.mat[0][0] = input[i][0];
            initial.mat[0][1] = input[i][1];
            initial.mat[0][2] = 1;              // initialising initial matrix [x y 1]

            final = initial*TranslationMat;

            output[i][0] = final.mat[0][0];
            output[i][1] = final.mat[0][1];
        }
}

void MainWindow::drawPolygon()
{
    for(j=1;j<=i-1;j++)
    {
        dda(output[j][0], output[j][1], output[j-1][0], output[j-1][1]);
    }
    dda(output[j-1][0], output[j-1][1], output[0][0], output[0][1]);
}

void MainWindow::on_pushButton_2_clicked()
{
    float sx = ui->textEdit_3->toPlainText().toFloat();
    float sy = ui->textEdit_4->toPlainText().toFloat();
    scale(sx, sy);
    drawPolygon();
}

void MainWindow::scale(float sx, float sy)
{
    double ScaleMat[3][3];       // 3x3 scaling matrix
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            ScaleMat[i][j] = 0;
        }
    }
    ScaleMat[0][0] = sx;
    ScaleMat[1][1] = sy;
    ScaleMat[2][2] = 1;
    // scaling matrix initialised

    for(i=0;i<n;i++)
    {
        initial.mat[0][0] = input[i][0];
        initial.mat[0][1] = input[i][1];
        initial.mat[0][2] = 1;              // initialising initial matrix [x y 1]

        final = initial*ScaleMat;

        output[i][0] = final.mat[0][0];
        output[i][1] = final.mat[0][1];
        cout<<output[i][0]<<" "<<output[i][1]<<endl;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    double angle = ui->textEdit_5->toPlainText().toDouble();
    angle = angle*3.14/180;                 // angle converted to radians
    rotation(angle);
    drawPolygon();
}

void MainWindow::rotation(double angle)
{
    double rotationMat[3][3];       // 3x3 rotation matrix
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

    for(i=0;i<n;i++)
    {
        initial.mat[0][0] = input[i][0];
        initial.mat[0][1] = input[i][1];
        initial.mat[0][2] = 1;              // initialising initial matrix [x y 1]

        final = initial*rotationMat;

        output[i][0] = final.mat[0][0];
        output[i][1] = final.mat[0][1];
        cout<<output[i][0]<<" "<<output[i][1]<<endl;
    }
}
