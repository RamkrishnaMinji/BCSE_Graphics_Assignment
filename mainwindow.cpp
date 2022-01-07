#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QImage>
#include <iostream>
#include <QMouseEvent>
#include <QPainter>
#include <QPaintDevice>
#include <QPoint>
#include <QElapsedTimer>
#include <QDebug>
#include <QThread>
#include <vector>
#include <QPair>
#define max(a,b) (a>b)?a:b
#define min(a,b) (a<b)?a:b
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->x_axis->hide();
    ui->y_axis->hide();
    connect(ui->frame,SIGNAL(Mouse_Pos()),this,SLOT(Mouse_Pressed()));
    connect(ui->frame,SIGNAL(sendMousePosition(QPoint&)),this,SLOT(showMousePosition(QPoint&)));
    img=QImage(ui->frame->height(),ui->frame->width(),QImage::Format_RGB888);
}


void MainWindow::delay(int ms)
{
    QElapsedTimer timer;
    timer.start();

    while (!timer.hasExpired(ms))
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::point(int x,int y,int r=0,int g=0,int b=0)
{

    int k=ui->grid_size->value();
    int w=ui->frame->width();
    int h=ui->frame->height();

    if(k>1){
        for(int i=x/k*k+1;i<x/k*k+k;i++){
            for(int j=(y/k)*k+1;j<(y/k)*k+k;j++){
                    if(i<=w&&j<=h)
                    img.setPixel(i,j,qRgb(r,g,b));
            }
        }
    }
    else{
        for(int i=0;i<w;i++)
            for(int j=0;j<h;j++)
        img.setPixel(i,j,qRgb(r,g,b));
    }

    ui->frame->setPixmap(QPixmap::fromImage(img));
}
int MainWindow::changeX(int x){

    int w=ui->frame->width();
    int k=ui->grid_size->value();
    if(k==0)
        return x;
    int temp=x;
    x-=img.width()/2;
    x/=k;
    return x;

}

int MainWindow::changeY(int y){

    int h=ui->frame->height();
    int k=ui->grid_size->value();
    if(k==0)
        return y;
    int temp=y;
    y=h/2-y;
    y/=k;
//    if((temp/k)*k<h)
//        return y+1;
     return y;
}

void MainWindow::showMousePosition(QPoint &pos)
{
    ui->mouse_movement->setText(" X : "+QString::number(changeX(pos.x()))+", Y : "+QString::number(changeY((pos.y()))));
}

void MainWindow::Mouse_Pressed()
{
    ui->mouse_pressed->setText(" X : "+QString::number(changeX(ui->frame->x))+", Y : "+QString::number(changeY(ui->frame->y)));
    if(ui->paint->isChecked())
        return;
    point(ui->frame->x,ui->frame->y,0,0,250);

//    ui->x_axis->move(0,ui->frame->y);
//    ui->y_axis->move(ui->frame->x,0);
}

void MainWindow::on_show_grid_clicked()
{
//    int w=ui->frame->width();
//    int h=ui->frame->height();

    int k=ui->grid_size->value();

    if(k<1)
    {
        k=1;
    }
    for(int j=0;j<img.height();j++)
    {
        for(int i=0;i<img.width();i++)
        {
            img.setPixel(i,j,qRgb(0,0,0));
        }
    }
    ui->frame->setPixmap(QPixmap::fromImage(img));

    for(int i=0;i<=img.height();i+=k)
        for(int j=0;j<=img.width();j++)
            img.setPixel(i,j,qRgb(255,255,255));

    for(int i=0;i<img.width();i+=k)
        for(int j=0;j<img.height();j++)
            img.setPixel(j,i,qRgb(255,255,255));

    ui->frame->setPixmap(QPixmap::fromImage(img));

//    if(ui->show_axes->isChecked()){
//     on_show_axes-clicked();
//    }
    if(ui->show_axes->isChecked()){
        int h=ui->frame->height();
        int w=ui->frame->width();
        int k=ui->grid_size->value();
        if(k<=0)
         {
            return;
        }
        for(int i=0;i<=w;i+=k){
            point(i,h/2,0,255,0);
        }

        for(int j=0;j<=h;j+=k){
            point(w/2,j,0,255,0);
        }
    }
    else{
        int h=ui->frame->height();
        int w=ui->frame->width();
        int k=ui->grid_size->value();
        if(k<=0)
         {
            return;
        }
        for(int i=0;i<=w;i+=k){
            point(i,h/2,0,0,0);
        }

        for(int j=0;j<=h;j+=k){
            point(w/2,j,0,0,0);
        }
    }
}

void MainWindow::on_show_axes_clicked()
{

    if(ui->show_axes->isChecked()){
        int h=ui->frame->height();
        int w=ui->frame->width();
        int k=ui->grid_size->value();
        if(k<=0)
         {
            return;
        }
        for(int i=0;i<=w;i+=k){
            point(i,h/2,0,255,0);
        }

        for(int j=0;j<=h;j+=k){
            point(w/2,j,0,255,0);
        }
    }
    else{
        int h=ui->frame->height();
        int w=ui->frame->width();
        int k=ui->grid_size->value();
        if(k<=0)
         {
            return;
        }
        for(int i=0;i<=w;i+=k){
            point(i,h/2,0,0,0);
        }

        for(int j=0;j<=h;j+=k){
            point(w/2,j,0,0,0);
        }
    }


}

void MainWindow::on_set_point1_clicked()
{
    if(ui->draw_line->isChecked()){
        p1.setX(ui->frame->x);
        p1.setY(ui->frame->y);
    }
}

void MainWindow::on_set_point2_clicked()
{
    if(ui->draw_line->isChecked()){
        p2.setX(ui->frame->x);
        p2.setY(ui->frame->y);
    }
}

void MainWindow::on_set_center_clicked()
{
    if(ui->draw_circle->isChecked()){
        pc.setX(ui->frame->x);
        pc.setY(ui->frame->y);
    }
}

void MainWindow::on_set_ellipse_center_clicked()
{
    if(ui->draw_ellipse->isChecked()){
        pe.setX(ui->frame->x);
        pe.setY(ui->frame->y);
    }
}

void MainWindow::on_select_point_clicked()
{
    if(ui->paint->isChecked()){
        p.setX(ui->frame->x);
        p.setY(ui->frame->y);
    }

}

void MainWindow::on_pointc1_clicked()
{
    if(ui->clipping->isChecked()){
        tp1=(QPoint((ui->frame->x),(ui->frame->y)));
    }
}


void MainWindow::on_pointc2_clicked()
{
    if(ui->clipping->isChecked()){
        tp2=(QPoint((ui->frame->x),(ui->frame->y)));
    }
}

void MainWindow::on_select_point_top_left_clicked()
{
    wp.clear();
    if(ui->clipping->isChecked()){
        int k=ui->grid_size->value();
        wp.push_back((QPoint(((ui->frame->x)),(ui->frame->y))));
    }
}

//dda line drawing algorithm
void MainWindow::dda(int x0, int xn, int y0, int yn){
        int gridsize=ui->grid_size->value();
        x0=x0/gridsize;
        xn=xn/gridsize;
        y0=y0/gridsize;
        yn=yn/gridsize;
        float dx=fabs(xn-x0); //total span in x
        float dy=fabs(yn-y0); //total span in y


        float Dx,Dy; //incremental stemps in x & y


        // determine if slope m GT or LT 1
        if(dx>dy){
            Dx=1;
            Dy=dy/dx; // floating diviation , but only done once per line
        }
        else{
        Dx=dx/dy;
        Dy=1;}

        //change the direction of movement accordingly
        if (x0 > xn) Dx *= -1;
        if (y0 > yn) Dy *= -1;

        timer.start();

        double x = x0*gridsize; //adjusting the initial x coordinate according to the grid size
        double y = y0*gridsize; //adjusting the initial y coordinate according to the grid size
        int ix,iy; //pixel coords
        for(int k=0; k<=((dx>dy)?dx:dy);k++){

            ix=int(x/gridsize+0.5); //round to rearest pixel X coordinate
            iy=int(y/gridsize+0.5); //round to rearest pixel Y coordinate

            point(ix*gridsize,iy*gridsize,0,255,0);   //**

            x+=Dx*gridsize; //floating point calculations
            y+=Dy*gridsize;

        }
        long long int timeTook=timer.nsecsElapsed();
        ui->dda_time->setText(QString::number(timeTook)+" ns");
        timer.start();

 }

void MainWindow::on_dda_clicked()
{
    if(ui->draw_line->isChecked()){
        int x0=p1.x();
        int xn=p2.x();
        int y0=p1.y();
        int yn=p2.y();
        dda(x0,xn,y0,yn);
    }
}

void swap(int &a,int &b){
    int temp=a;
     a=b;
     b=temp;
}
//bresenham line drawing method
void MainWindow::bresenham(int x0,int xn,int y0,int yn){
    int gridsize=ui->grid_size->value();
    x0=x0/gridsize;
    xn=xn/gridsize;
    y0=y0/gridsize;
    yn=yn/gridsize;

    //required for evaluating the step count of the algorithm
    int dx = fabs(xn - x0);
    int dy = fabs(yn - y0);

    int Dx = (x0 > xn ? -1 : 1);
    int Dy = (y0 > yn ? -1 : 1);
    bool flag = 1;
    int x = x0*gridsize + gridsize/2; //adjusting the initial x coordinate according to the grid size
    int y = y0*gridsize + gridsize/2; //adjusting the initial y coordinate according to the grid size
    if(dy > dx) { // if slope > 1, then swap the elements
        swap(dx,dy);
        swap(x,y);
        swap(Dx,Dy);
        flag = 0;
    }

    //evauating the decision for pixel illumination
    int p = 2*dy - dx;

    timer.start();
    //evaluating the algorithm

    for(int steps=0;steps<=dx;steps++) {
        if(flag) {
            point(x,y,255,0,0);
            if(ui->animation->isChecked())
            delay(200*animation_time);
        }

        else {
            point(y,x,255,0,0);
            if(ui->animation->isChecked())
            delay(200*animation_time);
        }

        if(p < 0) {
            x += Dx*gridsize;
            p += 2*dy;
        } else {
            x += Dx*gridsize;
            y += Dy*gridsize;
            p += 2*dy - 2*dx;
        }
    }
    long long int timeTook = timer.nsecsElapsed();
    ui->bresenham_time->setText(QString::number(timeTook)+" ns");
    //cout<<"hello";
}

//perform bresenham line drawing
void MainWindow::on_bresenham_clicked()
{
    if(ui->draw_line->isChecked()){
        int x0=p1.x();
        int xn=p2.x();
        int y0=p1.y();
        int yn=p2.y();
        bresenham(x0,xn,y0,yn);
    }
}

//Drawing Circle using polar method
void MainWindow::on_polar_circle_draw_clicked()
{
    if(ui->draw_circle->isChecked()){
        int k=ui->grid_size->value();
        int x0=pc.x()/k;  //center
        int y0=pc.y()/k;
        x0=x0*k;
        y0=y0*k;

        double pi=3.14;
        double theta;
        int radius=ui->circle_radius->value();
        int x,y;
        timer.start();
        for(int deg=0;deg<=45;deg++){
            theta=pi*deg/180;

            x=radius*cos(theta)+0.5;
            x*=k;
            y=radius*sin(theta)+0.5;
            y*=k;
            point(x0+x,y0-y,100,255,0);
            point(x0+x,y0+y,100,255,0);
            point(x0-x,y0-y,100,255,0);
            point(x0-x,y0+y,100,255,0);
            point(x0+y,y0-x,100,255,0);
            point(x0+y,y0+x,100,255,0);
            point(x0-y,y0-x,100,255,0);
            point(x0-y,y0+x,100,255,0);

            if(ui->animation->isChecked())
            delay(200*animation_time);  //ms=0.2 * anim_t s

        }
        long long timeTook=timer.nsecsElapsed();
        ui->polar_circle_time->setText(QString::number(timeTook)+" ns");
    }

}

void MainWindow::on_bresenham_midpoint_circle_draw_clicked()
{
    if(ui->draw_circle->isChecked()){
        int k=ui->grid_size->value();
        int x0=pc.x()/k+0.5;
        int y0=pc.y()/k+0.5;
        x0=x0*k+0.5*k;
        y0=y0*k+0.5*k;
        int r=ui->circle_radius->value();
        int x=0,y=r*k;
        int p=(1-r)*k;

        timer.start();
        while(y>=x){
            point((x0 - x), y0 - y, 255, 0, 0);
            point(x0 + x, y0 - y, 255, 0, 0);
            point(x0 - x, y0 + y, 255, 0, 0);
            point(x0 + x, y0 + y, 255, 0, 0);
            point(x0 - y, y0 - x, 255, 0, 0);
            point(x0 + y, y0 - x, 255, 0, 0);
            point(x0 - y, y0 + x, 255, 0, 0);
            point(x0 + y, y0 + x, 255, 0, 0);
            x += k;
            if(p <= 0) {
                p = p + 2*x + 1;
            } else {
                p = p + 2*x + 1 - 2*y;
                y -= k;
            }
            if(ui->animation->isChecked())
            delay(200*animation_time);
        }
        long long timeTook=timer.nsecsElapsed();
        ui->midpoint_circle_time->setText(QString::number(timeTook)+" ns");

    }
}

void MainWindow::on_polar_ellipse_draw_clicked()
{
    if(ui->draw_ellipse->isChecked()){
        int k=ui->grid_size->value();
        int xc=pe.x()/k;
        int yc=pe.y()/k;
        xc=xc*k+0.5*k;
        yc=yc*k+0.5*k;
        int a=ui->X_radius->value();
        int b=ui->Y_radius->value();
        int x,y;
        timer.start();
        for(int deg=1;deg<=90;deg++){
            double theta=(3.14/180*deg);
            x=a*cos(theta)+0.5;
            y=b*sin(theta)+0.5;
            point(xc+x*k,yc+y*k,0,0,255);
            point(xc+x*k,yc-y*k,0,0,255);
            point(xc-x*k,yc+y*k,0,0,255);
            point(xc-x*k,yc-y*k,0,0,255);

            if(ui->animation->isChecked())
                delay(200*animation_time);
        }
        long long timeTook=timer.nsecsElapsed();
        ui->polar_ellipse_time->setText(QString::number(timeTook)+" ns");
    }
}

void MainWindow::on_midpoint_ellipse_draw_clicked()
{
    if(ui->draw_ellipse->isChecked()){
        int k=ui->grid_size->value();
        int xc=pe.x()/k;
        int yc=pe.y()/k;
        xc=xc*k+0.5*k;
        yc=yc*k+0.5*k;
        int a=ui->X_radius->value();
        int b=ui->Y_radius->value();
        int x=0,y=b;
       // ui->midpoint_circle_time->setText("hello");
        timer.start();
        double d1=b*b-a*a*b+(0.25*a*a);
        point(xc+x*k,yc+y*k,255,0,0);
        point(xc+x*k,yc-y*k,255,0,0);
        point(xc-x*k,yc+y*k,255,0,0);
        point(xc-x*k,yc-y*k,255,0,0);
        while(b*b*(x+1)<a*a*(y-0.5)){
            if(d1<0){
                d1+=b*b*(2*x+3);
            }
            else{
                d1+=b*b*(2*x+3)+a*a*(-2*y+2);
                y--;
            }
            x++;
            point(xc+x*k,yc+y*k,255,0,0);
            point(xc+x*k,yc-y*k,255,0,0);
            point(xc-x*k,yc+y*k,255,0,0);
            point(xc-x*k,yc-y*k,255,0,0);

            if(ui->animation->isChecked())
            delay(200*animation_time);
        }
        double d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
        while(y>0){
            if(d2<0){
                d2+=b*b*(2*x+2)+a*a*(-2*y+3);
                x++;
            }
            else d2+=a*a*(-2*y+3);
            y--;
            point(xc+x*k,yc+y*k,255,0,0);
            point(xc+x*k,yc-y*k,255,0,0);
            point(xc-x*k,yc+y*k,255,0,0);
            point(xc-x*k,yc-y*k,255,0,0);

            if(ui->animation->isChecked())
            delay(200*animation_time);
        }
        long long timeTook=timer.nsecsElapsed();
        ui->bresenham_midpoint_ellipse_time->setText(QString::number(timeTook)+" ns");
    }
}





void MainWindow::on_accept_point_clicked()
{
    if(ui->draw_polygon->isChecked()){
        pxy.push_back(QPoint(ui->frame->x,ui->frame->y));
    }
}

void MainWindow::draw_polygon(){
    if(pxy.size()>=3){
        int n=pxy.size();

        for(int i=0;i<n;i++){
            //bresenham(int x0,int xn,int y0,int yn)
            if(ui->transformation->isChecked()||ui->green->isChecked())
                dda(pxy[i].x(),pxy[(i+1)%n].x(),pxy[i].y(),pxy[(i+1)%n].y());
            else bresenham(pxy[i].x(),pxy[(i+1)%n].x(),pxy[i].y(),pxy[(i+1)%n].y());

        }

    }
}

void MainWindow::on_polygon_clicked()
{
    if(ui->draw_polygon->isChecked()){  //1 2 3   //1-2 2-3 3-1

        timer.start();
        draw_polygon();
        long long timeTook=timer.nsecsElapsed();
        ui->polygon_time->setText(QString::number(timeTook)+" ns");
    }
}

void MainWindow::_4_connected_boundaryfill_algo(int x,int y,QRgb edgecolor,int rn,int gn,int bn,int k){
        QRgb current=img.pixel((double)x+0.5,(double)y+0.5);
        QRgb newcolor=qRgb(rn,gn,bn);
        if(x>=ui->frame->height()||x<=0||y>=ui->frame->width()||y<=0)
            return;
        if(current!=edgecolor&&current!=newcolor){
            x=x/k;
            y=y/k;
            point(x*k+0.5*k,y*k+0.5*k,rn,gn,bn);
            if(ui->animation->isChecked())
            delay(200*animation_time*0.25);

          _4_connected_boundaryfill_algo((x+1)*k+0.5*k,y*k+0.5*k,edgecolor,rn,gn,bn,k);
          _4_connected_boundaryfill_algo((x-1)*k+0.5*k,y*k+0.5*k,edgecolor,rn,gn,bn,k);
          _4_connected_boundaryfill_algo(x*k+0.5*k,(y+1)*k+0.5*k,edgecolor,rn,gn,bn,k);
          _4_connected_boundaryfill_algo(x*k+0.5*k,(y-1)*k+0.5*k,edgecolor,rn,gn,bn,k);
        }
}

void MainWindow::on__4_connected_boundaryfill_clicked()
{
    int k=ui->grid_size->value();
    if(ui->paint->isChecked()){
        QRgb edgecolor=qRgb(255,0,0);

        timer.start();
        _4_connected_boundaryfill_algo(p.x(),p.y(),edgecolor,0,0,255,k);

        long long timeTook=timer.nsecsElapsed();
       // ui->_4_connected_boundaryfill_time->setText(QString::number(timeTook)+" ns");
    }
}
void MainWindow::on_scanline_paint_clicked()
{
    if(ui->paint->isChecked()){
        p.setX(ui->frame->x);
        p.setY(ui->frame->y);
    }
    on__4_connected_boundaryfill_clicked();
}


void MainWindow::_8_connected_boundaryfill_algo(int x,int y,QRgb edgecolor,int rn,int gn,int bn,int k){
        QRgb current=img.pixel((double)x+0.5,(double)y+0.5);
        QRgb newcolor=qRgb(rn,gn,bn);
        if(x>=ui->frame->height()||x<=0||y>=ui->frame->width()||y<=0)
            return;
        if(current!=edgecolor&&current!=newcolor){
            x=x/k;
            y=y/k;
            point(x*k+0.5*k,y*k+0.5*k,rn,gn,bn);
            if(ui->animation->isChecked())
            delay(200*animation_time*0.25);

          _8_connected_boundaryfill_algo((x+1)*k+0.5*k,y*k+0.5*k,edgecolor,rn,gn,bn,k);
          _8_connected_boundaryfill_algo((x-1)*k+0.5*k,y*k+0.5*k,edgecolor,rn,gn,bn,k);
          _8_connected_boundaryfill_algo(x*k+0.5*k,(y+1)*k+0.5*k,edgecolor,rn,gn,bn,k);
          _8_connected_boundaryfill_algo(x*k+0.5*k,(y-1)*k+0.5*k,edgecolor,rn,gn,bn,k);

          _8_connected_boundaryfill_algo((x+1)*k+0.5*k,(y+1)*k+0.5*k,edgecolor,rn,gn,bn,k);
          _8_connected_boundaryfill_algo((x-1)*k+0.5*k,(y-1)*k+0.5*k,edgecolor,rn,gn,bn,k);
          _8_connected_boundaryfill_algo((x-1)*k+0.5*k,(y+1)*k+0.5*k,edgecolor,rn,gn,bn,k);
          _8_connected_boundaryfill_algo((x+1)*k+0.5*k,(y-1)*k+0.5*k,edgecolor,rn,gn,bn,k);
        }
}

void MainWindow::on__8_connected_boundaryfill_clicked()
{
    int k=ui->grid_size->value();
    if(ui->paint->isChecked()){
        QRgb edgecolor=qRgb(255,0,0);

        timer.start();
        _8_connected_boundaryfill_algo(p.x(),p.y(),edgecolor,0,0,255,k);

        long long timeTook=timer.nsecsElapsed();
        ui->_8_connected_boundaryfill_time->setText(QString::number(timeTook)+" ns");
    }
}

void MainWindow::_4_connected_floodfill_algo(int x,int y,QRgb oldcolor,int rn,int gn,int bn,int k){
        QRgb current=img.pixel((double)x+0.5,(double)y+0.5);
        //QRgb newcolor=qRgb(rn,gn,bn);
        if(x>=ui->frame->height()||x<=0||y>=ui->frame->width()||y<=0)
            return;
        if(current==oldcolor){
            x=x/k;
            y=y/k;
            point(x*k+0.5*k,y*k+0.5*k,rn,gn,bn);
            if(ui->animation->isChecked())
            delay(200*animation_time*0.25);
          _4_connected_floodfill_algo((x+1)*k+0.5*k,y*k+0.5*k,oldcolor,rn,gn,bn,k);
          _4_connected_floodfill_algo((x-1)*k+0.5*k,y*k+0.5*k,oldcolor,rn,gn,bn,k);
          _4_connected_floodfill_algo(x*k+0.5*k,(y+1)*k+0.5*k,oldcolor,rn,gn,bn,k);
          _4_connected_floodfill_algo(x*k+0.5*k,(y-1)*k+0.5*k,oldcolor,rn,gn,bn,k);
        }
}

void MainWindow::on__4_connected_floodfill_clicked()
{
    int k=ui->grid_size->value();
    if(ui->paint->isChecked()){
        QRgb oldcolor=qRgb(0,0,0);

        timer.start();
        _4_connected_floodfill_algo(p.x(),p.y(),oldcolor,0,0,255,k);

        long long timeTook=timer.nsecsElapsed();
        ui->_4_connected_floodfill_time->setText(QString::number(timeTook)+" ns");
    }
}

void MainWindow::_8_connected_floodfill_algo(int x,int y,QRgb oldcolor,int rn,int gn,int bn,int k){
        QRgb current=img.pixel((double)x+0.5,(double)y+0.5);
        //QRgb newcolor=qRgb(rn,gn,bn);
        if(x>=ui->frame->height()||x<=0||y>=ui->frame->width()||y<=0)
            return;
        if(current==oldcolor){
            x=x/k;
            y=y/k;
            point(x*k+0.5*k,y*k+0.5*k,rn,gn,bn);
            if(ui->animation->isChecked())
            delay(200*animation_time*0.25);
          _8_connected_floodfill_algo((x+1)*k+0.5*k,y*k+0.5*k,oldcolor,rn,gn,bn,k);
          _8_connected_floodfill_algo((x-1)*k+0.5*k,y*k+0.5*k,oldcolor,rn,gn,bn,k);
          _8_connected_floodfill_algo(x*k+0.5*k,(y+1)*k+0.5*k,oldcolor,rn,gn,bn,k);
          _8_connected_floodfill_algo(x*k+0.5*k,(y-1)*k+0.5*k,oldcolor,rn,gn,bn,k);

          _8_connected_floodfill_algo((x+1)*k+0.5*k,(y+1)*k+0.5*k,oldcolor,rn,gn,bn,k);
          _8_connected_floodfill_algo((x-1)*k+0.5*k,(y-1)*k+0.5*k,oldcolor,rn,gn,bn,k);
          _8_connected_floodfill_algo((x-1)*k+0.5*k,(y+1)*k+0.5*k,oldcolor,rn,gn,bn,k);
          _8_connected_floodfill_algo((x-1)*k+0.5*k,(y-1)*k+0.5*k,oldcolor,rn,gn,bn,k);
        }
}

void MainWindow::on__8_connected_floodfill_clicked()
{
    int k=ui->grid_size->value();
    if(ui->paint->isChecked()){
        QRgb oldcolor=qRgb(0,0,0);

        timer.start();
        _8_connected_floodfill_algo(p.x(),p.y(),oldcolor,0,0,255,k);

        long long timeTook=timer.nsecsElapsed();
        ui->_8_connecte_floodfill_time->setText(QString::number(timeTook)+" ns");
    }
}


//Reset
void MainWindow::on_clear_clicked()
{
    int k = ui->grid_size->value();
    for(int j=0;j<img.height();j++)
    {
        for(int i=0;i<img.width();i++)
        {
            img.setPixel(i,j,qRgb(0,0,0));
        }
    }
    pxy.clear();
    wp.clear();
    pclip.clear();
    paf.clear();
    ui->frame->setPixmap(QPixmap::fromImage(img));
}

void mat_mult(double a[3][3], int b[3], double res[3]){
    int i,j;
    for(i=0;i<3;i++){
        res[i]=0;
        for(j=0;j<3;j++)
            res[i]+=(a[i][j]*b[j]);
    }

}

void MainWindow::on_translate_clicked()
{

    int k = ui->grid_size->value();
    int tx=(ui->tx_edit->text()).toInt();
    int ty=(ui->ty_edit->text()).toInt();
    tx*=k;
    ty*=k;
    ty=-ty;
    int i,len=pxy.size();

    timer.start();
     // matrix for translation
    double mat[3][3]={{1,0,tx*1.0},{0,1,ty*1.0},{0,0,1}};

    int coord[3];
    double res[3];
    for(i=0;i<len;i++)
    {
        coord[0]=pxy[i].x();
        coord[1]=pxy[i].y();
        coord[2]=1;
        mat_mult(mat,coord,res);
        pxy[i]= QPoint(res[0]/res[2],res[1]/res[2]);
    }

    long long timeTook=timer.nsecsElapsed();
    ui->translate_time->setText(QString::number(timeTook)+" ns");
    draw_polygon();

}


void MainWindow::on_scale_clicked()
{

        double sx = (ui->sx_edit->text()).toDouble();
        double sy = (ui->sy_edit->text()).toDouble();
        int gridsize = ui->grid_size->value();

        QVector<QPoint> old_vertex;
        for(int i=0;i<int(pxy.size());i++)
        {
            old_vertex.push_back(pxy[i]);
        }

        //Point about which to be scaled
        int piv_x= (ui->frame->x/gridsize)*gridsize+gridsize/2;
        int piv_y= (ui->frame->y/gridsize)*gridsize+gridsize/2;

        int i,len=pxy.size();

        // matrix for scaling
        timer.start();
        double mat[3][3]={{sx,0,0},{0,sy,0},{0,0,1}};
        int coord[3];
        double res[3];
        for(i=0;i<len;i++)
        {
            coord[0]=pxy[i].x()-piv_x;
            coord[1]=piv_y-pxy[i].y();
            coord[2]=1;
            mat_mult(mat,coord,res);

            pxy[i]=(QPoint((res[0]/res[2]+piv_x),(piv_y-res[1]/res[2])));

        }
        long long timeTook=timer.nsecsElapsed();
        ui->scaling_time->setText(QString::number(timeTook)+" ns");
        draw_polygon();
}

void MainWindow::on_shear_clicked()
{
    double shx = (ui->hx_edit->text()).toDouble();
    double shy = (ui->hy_edit->text()).toDouble();
    int gridsize = ui->grid_size->value();


    //Point about which to be sheared
    int piv_x=(ui->frame->x/gridsize)*gridsize+gridsize/2;
    int piv_y=(ui->frame->y/gridsize)*gridsize+gridsize/2;

    int i,len=pxy.size();
    timer.start();
    // matrix for shearing
    double mat[3][3]={{1,shx,0},{shy,1,0},{0,0,1}};
    int coord[3];
    double res[3];
    for(i=0;i<len;i++)
    {
        coord[0]=pxy[i].x()-piv_x;
        coord[1]=piv_y-pxy[i].y();
        coord[2]=1;
        mat_mult(mat,coord,res);
        pxy[i]=(QPoint(res[0]/res[2]+piv_x,piv_y-res[1]/res[2]));
    }

    long long timeTook=timer.nsecsElapsed();
    ui->shear_time->setText(QString::number(timeTook)+" ns");
    draw_polygon();
}


void MainWindow::on_rotation_clicked()
{
    if(ui->tangle->value()==0){
        draw_polygon();
        return;
    }
    double angle = ui->tangle->value();
    int gridsize = ui->grid_size->value();

    double dang=(double)angle*M_PI/180.0;
    double sinang=sin(dang);
    double cosang=cos(dang);

    //Point about which to be rotated
    int piv_x=(ui->frame->x/gridsize)*gridsize+gridsize/2;
    int piv_y=(ui->frame->y/gridsize)*gridsize+gridsize/2;

    int i,len=pxy.size();
    timer.start();
    // matrix for rotation
    double mat[3][3]={{cosang,-sinang,0},{sinang,cosang,0},{0,0,1}};
    int coord[3];
    double res[3];
    for(i=0;i<len;i++)
    {
        coord[0]=pxy[i].x()-piv_x;
        coord[1]=piv_y-pxy[i].y();
        coord[2]=1;
        mat_mult(mat,coord,res);
        pxy[i]=QPoint(res[0]/res[2]+piv_x,piv_y-res[1]/res[2]);
    }


    long long timeTook=timer.nsecsElapsed();
    ui->rotation_time->setText(QString::number(timeTook)+" ns");
    draw_polygon();
}

void MainWindow::on_reflection_clicked()
{
    if (ui->reflectionaxis->isChecked() == false) {
           int rx, ry;
       if (ui->reflectxaxis->isChecked()) {
           rx = 1, ry = -1;
       } else if (ui->reflectyaxis->isChecked()) {
           rx = -1, ry = 1;
       } else if (ui->reflectorigin->isChecked()) {
           rx = -1, ry = -1;
       } else {
           return;
       }
     //  vector<pair<int,int>> old_vertex = vertex_list;

       int gridsize=ui->grid_size->value();
//        rx*=k;
//        ry*=k;
       int i,len=pxy.size();
       // matrix for reflection
       double mat[3][3]={{rx*1.0,0,0},{0,ry*1.0,0},{0,0,1}};

       //Point about which to be reflected
       int piv_x=((ui->frame->width()/2)/gridsize)*gridsize+gridsize/2;
       int piv_y=((ui->frame->height()/2)/gridsize)*gridsize+gridsize/2;

       int coord[3];
       double res[3];
       for(i=0;i<len;i++)
       {
           coord[0]=pxy[i].x()-piv_x;
           coord[1]=piv_y-pxy[i].y();
           coord[2]=1;
           mat_mult(mat,coord,res);
           pxy[i]=QPoint(res[0]/res[2]+piv_x , piv_y-res[1]/res[2]);
       }
       draw_polygon();
       return;
   }
   int i,len=pxy.size();

   double dx=p1.x()-p2.x();
   double dy=p1.y()-p2.y();

   double a=-dy;
   double b=dx;
   double c=p1.x()*dy-p1.y()*dx;

   for(i=0;i<len;i++)
   {
       int x1=pxy[i].x();
       int y1=pxy[i].y();

       pxy[i]=QPoint((int)((double)x1-(double)(2*a*(a*x1+b*y1+c))/(double)((a*a+b*b))) , (int)((double)y1-(double)(2*b*(a*x1+b*y1+c))/(double)((a*a+b*b))));
   }
   draw_polygon();
}




void MainWindow::on_line_dda_clicked()
{
    pclip.push_back({tp1,tp2});
    dda(tp1.x(),tp2.x(),tp1.y(),tp2.y());

}
void MainWindow::on_create_window_clicked()
{
    int k=ui->grid_size->value();
    int x=ui->rx->value();
    int y=ui->ry->value();
    x*=k;
    y*=k;
    wp.push_back(QPoint(wp[0].x()+x,wp[0].y()));
    wp.push_back(QPoint(wp[0].x()+x,wp[0].y()+y));
    wp.push_back(QPoint(wp[0].x(),wp[0].y()+y));


    for(int i=0;i<4;i++){
        bresenham(wp[i].x(),wp[(i+1)%4].x(),wp[i].y(),wp[(i+1)%4].y());
    }
}
// Defining region codes
const int INSIDE = 0; // 0000
const int LEFT = 1;   // 0001
const int RIGHT = 2;  // 0010
const int BOTTOM = 4; // 0100
const int TOP = 8;    // 1000
int MainWindow::computeCode(int xa, int ya)
{
    int x_min=wp[0].x(),x_max=wp[2].x(),y_min=wp[0].y(),y_max=wp[2].y();

    // initialized as being inside
        int code = INSIDE;
        if (xa < x_min)       // to the left of rectangle
            code |= LEFT;
        else if (xa > x_max)  // to the right of rectangle
            code |= RIGHT;
        if (ya < y_min)       // below the rectangle
            code |= BOTTOM;
        else if (ya > y_max)  // above the rectangle
            code |= TOP;

        return code;
}
void MainWindow::cohenSutherlandClip()
{
        int x_min=min(wp[0].x(), wp[2].x());
        int x_max=max(wp[0].x(), wp[2].x());
        int y_min=min(wp[0].y(), wp[2].y());
        int y_max=max(wp[0].y(), wp[2].y());


        for(int i=0;i<pclip.size();i++){

            // Compute region codes for P1, P2
            int x1=pclip[i].first.x();
            int y1=pclip[i].first.y();
            int x2=pclip[i].second.x();
            int y2=pclip[i].second.y();
            int code1 = computeCode(x1, y1);
            int code2 = computeCode(x2, y2);

//            delay(200*20);
            // Initialize line as outside the rectangular window
            bool accept = false;

            while (true)
            {

                if ((code1 == 0) && (code2 == 0))
                {
                    // If both endpoints lie within rectangle
                    accept = true;
                    break;
                }
                else if (code1 & code2)
                {
                    // If both endpoints are outside rectangle,
                    // in same region
                    break;
                }
                else
                {
                    // Some segment of line lies within the
                    // rectangle
                    int code_out;
                    int x, y;

                    // At least one endpoint is outside the
                    // rectangle, pick it.
                    if (code1 != 0)
                        code_out = code1;
                    else
                        code_out = code2;

                    // Find intersection point;
                    // using formulas y = y1 + slope * (x - x1),
                    // x = x1 + (1 / slope) * (y - y1)
                    if (code_out & TOP)
                    {
                        // point is above the clip rectangle
                        x = x1 + (int)((double)(x2 - x1) *(double)(y_max - y1) /(double)(y2 - y1));
                        y = y_max;
                    }
                    else if (code_out & BOTTOM)
                    {
                        // point is below the rectangle
                        x = x1 + (int)((double)(x2 - x1) * (double)(y_min - y1) / (double)(y2 - y1));
                        y = y_min;
                    }
                    else if (code_out & RIGHT)
                    {
                        // point is to the right of rectangle
                        y = y1 + (int)((double)(y2 - y1) * (double)(x_max - x1) / (double)(x2 - x1));
                        x = x_max;
                    }
                    else if (code_out & LEFT)
                    {
                        // point is to the left of rectangle
                        y = y1 + (int)((double)(y2 - y1) * (double)(x_min - x1) / (double)(x2 - x1));
                        x = x_min;
                    }

                    // Now intersection point x,y is found
                    // We replace point outside rectangle
                    // by intersection point
                    if (code_out == code1)
                    {
                        x1 = x;
                        y1 = y;
                        code1 = computeCode(x1, y1);
                    }
                    else
                    {
                        x2 = x;
                        y2 = y;
                        code2 = computeCode(x2, y2);
                    }
                }
            }
            if (accept)
            {
                //If accepted
                //Just reset and draw the boundary and the line
                //Reset the screen and draw the grid

                tp1.setX(x1);
                tp1.setY(y1);

                tp2.setX(x2);
                tp2.setY(y2);

                paf.push_back({tp1,tp2});
            }
         }

}


void MainWindow::on_clip_line_clicked()
{
    cohenSutherlandClip();
    on_show_grid_clicked();
    on_create_window_clicked();
    for(int i=0;i<paf.size();i++){
        dda(paf[i].first.x(),paf[i].second.x(),paf[i].first.y(),paf[i].second.y());
    }

}

// *********************** POLYGON CLIPPING *************************************
//const int MAX_POINTS = 20;

// Returns x-value of point of intersectipn of two
// lines
int MainWindow::x_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4)
{
    y1=ui->frame->height()-y1+1;
    y2=ui->frame->height()-y2+1;
    y3=ui->frame->height()-y3+1;
    y4=ui->frame->height()-y4+1;
    int num = (x1*y2 - y1*x2) * (x3-x4) -
              (x1-x2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    int retx=num/den;
    return retx;
}

// Returns y-value of point of intersectipn of
// two lines
int MainWindow:: y_intersect(int x1, int y1, int x2, int y2,int x3, int y3, int x4, int y4)
{
    y1=ui->frame->height()-y1+1;
    y2=ui->frame->height()-y2+1;
    y3=ui->frame->height()-y3+1;
    y4=ui->frame->height()-y4+1;
    int num = (x1*y2 - y1*x2) * (y3-y4) -
              (y1-y2) * (x3*y4 - y3*x4);
    int den = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
    int rety= (ui->frame->height()-num/den+1);
    return rety;
}

// This functions clips all the edges w.r.t one clip
// edge of clipping area
void MainWindow::clip(int x1, int y1, int x2, int y2)
{
    int poly_size=pxy.size();
    int new_poly_size = 0;

    QVector<QPoint > new_points;

    // (ix,iy),(kx,ky) are the co-ordinate values of
    // the points
    for (int i = 0; i < poly_size; i++)
    {
        // i and k form a line in polygon

        int ix = pxy[i].x(), iy = pxy[i].y();
        int kx = pxy[(i+1)%poly_size].x(), ky = pxy[(i+1)%poly_size].y();

        // Calculating position of first and second point

        int i_pos,k_pos;
        if(x2==x1 && ix>x1) i_pos=1;
        else if(x2==x1 && ix<x1) i_pos=-1;
        else if(y2==y1 && iy<y1) i_pos=-1;
        else i_pos=1;

        if(x2==x1 && kx>x1) k_pos=1;
        else if(x2==x1 && kx<x1) k_pos=-1;
        else if(y2==y1 && ky<y1) k_pos=-1;
        else k_pos=1;

        if(y1<y2||x1>x2)
        {
            i_pos=(-1)*i_pos;
            k_pos=(-1)*k_pos;
        }

        // Case 1 : When both points are inside
        if (i_pos >= 0  && k_pos >= 0)
        {
            //Only second point is added
            new_points.push_back(QPoint(kx,ky));
            new_poly_size++;
        }

        // Case 2: When only first point is outside
        else if (i_pos < 0  && k_pos >= 0)
        {
            // Point of intersection with edge
            // and the second point is added

            new_points.push_back(QPoint(x_intersect(x1,y1, x2, y2, ix, iy, kx, ky),y_intersect(x1,y1, x2, y2, ix, iy, kx, ky)));
            new_poly_size++;

            new_points.push_back(QPoint(kx,ky));
            new_poly_size++;
        }

        // Case 3: When only second point is outside
        else if (i_pos >= 0  && k_pos < 0)
        {
            //Only point of intersection with edge is added

            new_points.push_back(QPoint(x_intersect(x1,y1, x2, y2, ix, iy, kx, ky),y_intersect(x1,y1, x2, y2, ix, iy, kx, ky)));
            new_poly_size++;
        }

        // Case 4: When both points are outside
        else
        {
            //No points are added
        }
    }

    // Copying new points into original array
    // and changing the no. of vertices
    //poly_size = new_poly_size;
    pxy.clear();
    for (int i = 0; i <new_points.size(); i++)
    {
        pxy.push_back(QPoint(new_points[i]));
    }


}

// Implements Sutherland–Hodgman algorithm
void MainWindow::suthHodgClip()
{
    //i and k are two consecutive indexes
    for (int i=0; i<4; i++)
    {
        // We pass the current array of vertices, it's size
        // and the end points of the selected clipper line
        clip(wp[i].x(), wp[i].y(), wp[(i+1)%4].x(), wp[(i+1)%4].y());
    }
ui->rotation_time->setText(QString::number(pxy.size())+" ns");
    on_show_grid_clicked();
    on_create_window_clicked();
    draw_polygon();
}
void MainWindow::on_polygonclipping_clicked()
{
    suthHodgClip();
}



