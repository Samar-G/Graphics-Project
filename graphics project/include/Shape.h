#ifndef SHAPE_H
#define SHAPE_H
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
#include<iostream>
#include<cmath>
#include <tchar.h>
#include <windows.h>
#include<iostream>
#include<vector>
#include<fstream>
using namespace std;
class Shape
{
    public:
        int x1,y1,x2,y2,x3=0,y3=0,dA;
        COLORREF c;
        virtual ~Shape();
        virtual void draw(HDC hdc)=0;
        virtual void drawcliped(HDC hdc,int x1,int y1,int x2,int y2)=0;
};
class Line : public Shape
{
    public:
    Line(int x1,int y1,int x2,int y2,COLORREF c,int dA);
    void drawcliped(HDC hdc,int x1,int y1,int x2,int y2);
    void draw(HDC hdc);
};
class Ellipsee : public Shape
{
    public:
    Ellipsee(int x1,int y1,int x2,int y2,int x3,int y3,COLORREF c,int dA);
    void drawcliped(HDC hdc,int x1,int y1,int x2,int y2);
    void draw(HDC hdc);
};
class Circle : public Shape
{
    public:
    Circle(int x1,int y1,int x2,int y2,COLORREF c,int dA);
     void drawcliped(HDC hdc,int x1,int y1,int x2,int y2);
    void draw(HDC hdc);
};
class QuarterFilledCircle : public Shape
{
    public:
    void drawcliped(HDC hdc,int x1,int y1,int x2,int y2);
    QuarterFilledCircle(int x1,int y1,int x2,int y2,COLORREF c,int dA);
    void draw(HDC hdc);
};
class RectangleWindow:public Shape
{
    public:
    RectangleWindow(int x1,int y1,int x2,int y2,COLORREF c,int dA);
    void draw(HDC hdc);
    void drawcliped(HDC hdc,int x1,int y1,int x2,int y2);
};

class Shapevector
{
    public:
    vector<Shape*> shapes;
    int xl,yt,xr,yb;
    void addshape(Shape *s);
    void drawShapes(HDC hdc);
    void clearshapes();
    void saveshapes(string path);
    void loadshapes(string path);

};
#endif // SHAPE_H
