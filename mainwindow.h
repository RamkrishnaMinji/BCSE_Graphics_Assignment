#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QTimer>
#include <QElapsedTimer>
#include <QThread>
#include <vector>
namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public slots:
    void Mouse_Pressed();
    void showMousePosition(QPoint& pos);
public:
     QImage img;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void delay(int);

    void on_show_axes_clicked();

//    void on_Draw_clicked();

    void on_set_point1_clicked();

    void on_set_point2_clicked();

    void on_show_grid_clicked();

    int changeX(int a);

    int changeY(int b);

    void dda(int x1,int y1,int x2,int y2);

    void bresenham(int x1,int y1,int x2,int y2);

    void on_dda_clicked();

    void on_bresenham_clicked();

    void on_set_center_clicked();

    void on_polar_circle_draw_clicked();

    void on_bresenham_midpoint_circle_draw_clicked();

    void on_midpoint_ellipse_draw_clicked();

    void on_set_ellipse_center_clicked();

    void on_polar_ellipse_draw_clicked();

    void on_clear_clicked();

    void on__4_connected_boundaryfill_clicked();

    void on_select_point_clicked();

    void _4_connected_boundaryfill_algo(int,int,QRgb,int,int,int,int);

    void on__8_connected_boundaryfill_clicked();

    void _8_connected_boundaryfill_algo(int,int,QRgb,int,int,int,int);

    void on__4_connected_floodfill_clicked();

    void _4_connected_floodfill_algo(int,int,QRgb,int,int,int,int);

    void on__8_connected_floodfill_clicked();

    void _8_connected_floodfill_algo(int,int,QRgb,int,int,int,int);

    void on_accept_point_clicked();

    void on_polygon_clicked();

    void on_translate_clicked();
    void draw_polygon();

    void on_scale_clicked();

    void on_shear_clicked();

    void on_rotation_clicked();

//    void on_transform_clicked();

    void on_pointc1_clicked();

    void on_pointc2_clicked();

    void on_line_dda_clicked();

    void on_select_point_top_left_clicked();

    void on_clip_line_clicked();

    void on_create_window_clicked();

    int computeCode(int , int );

    void cohenSutherlandClip();

    void on_reflection_clicked();

    void on_polygonclipping_clicked();

    void suthHodgClip();

    void clip(int ,int ,int ,int );

    int x_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4);

    int y_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4);

    void on_scanline_paint_clicked();

private:
    QElapsedTimer timer;
    Ui::MainWindow *ui;
    QPoint p1,p2,pc,pe,p;
    QVector<QPoint> pxy;
    QPoint tp1,tp2;
    QVector<QPoint> wp;
    QVector<QPair<QPoint,QPoint> > pclip;
    QVector<QPair<QPoint,QPoint> > paf;
    int animation_time=1;   //0.2*animation_time (second) = animation speed
    void point(int,int,int,int,int);
    QVector<QPair<int,int> > vertex_list;
};

#endif // MAINWINDOW_H
