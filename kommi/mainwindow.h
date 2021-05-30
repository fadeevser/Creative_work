#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool matrixcheck();
    void draw();
    void drawarrow(int x1,int y1,int x2, int y2);

private slots:

    void on_horizontalSlider_sliderMoved(int position);

    void on_button_matrix_clicked();

    void on_button_ok_clicked();

    void on_button_calc_clicked();

    void on_button_clear_clicked();

    void on_button_random_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsEllipseItem *ellipse[21];
};
#endif // MAINWINDOW_H
