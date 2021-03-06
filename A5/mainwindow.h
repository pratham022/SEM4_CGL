#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void dda(float x1, float y1, float x2, float y2);
    void bresenham(float x1, float y1, float x2, float y2);
    void bresErase(float x1, float y1, float x2, float y2);
    void boundary(int x, int y, QRgb fillcol, QRgb boundcol);
    void rotate();
    void erase();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
