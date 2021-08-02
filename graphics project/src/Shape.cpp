#include "Shape.h"
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif



int Round(double x){
    return (int) x+0.5;
}
bool PointClipping(int x,int y,int xleft, int ytop, int xright,int ybottom){
    bool z;
    if(x>xleft && x<xright && y>ytop && y<ybottom)
        z=true;
    else
        z= false;
    return z;
}
//10
void DrawLineParametric(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c){
    int dx=x2-x1, dy=y2-y1;
    double dt= 1.0/max(abs(dx),abs(dy));
    for(double t=0;t<=1;t+=dt){
        int x=Round(x1+t*dx);
        int y=Round(y1+t*dy);
        SetPixel(hdc,x,y,c);
    }
    cout<<"Parametric Line"<<endl;
}
//8
void DrawLineDDA(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c){
    int dx=x2-x1,dy=y2-y1;
    if(abs(dy)<=abs(dx)){
        if(x2<x1){
            swap(x1,x2);
            swap(y1,y2);
        }
        double m= (double)dy/dx;
        int x=x1;
        double y=y1;
        SetPixel(hdc,x,y,c);
        while(x<x2){
            x++;
            y+=m;
            SetPixel(hdc,x,Round(y),c);
        }
    }
    else{
        if(y1>y2){
            swap(x1,x2);
            swap(y1,y2);
        }
        double m=(double)dx/dy;
        int y=y1;
        double x=x1;
        SetPixel(hdc,x,y,c);
        while(y<y2){
            y++;
            x+=m;
            SetPixel(hdc,Round(x),y,c);
        }
    }
    cout<<"DDA Line"<<endl;
}
//9
void DrawLineMidPoint(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c){
    int x=x1, y=y1;
    double dx=x2-x1,dy=y2-y1;
    SetPixel(hdc,x,y,c);
    if((dx==0||dy/dx>1)&&dy>0&&dx>=0)
    {
        int d=2*dx-dy,d1=2*dx,d2=2*dx-2*dy;
        while(y!=y2)
        {
            if(d<=0)
            {
                y++;
                d+=d1;
            }
            else
            {
                x++;
                y++;
                d+=d2;
            }
            SetPixel(hdc,x,y,c);
        }
    }
    else if(dy/dx>=0&&dy/dx<=1&&dy>=0&&dx>0)
    {
        int d=dx-2*dy,d1=-2*dy,d2=2*dx-2*dy;
        while(x!=x2)
        {
            if(d>0)
            {
                x++;
                d+=d1;
            }
            else
            {
                x++;
                y++;
                d+=d2;
            }
            SetPixel(hdc,x,y,c);
        }
    }
    else if(dy/dx<0&&dy/dx>=-1&&dy<=0&&dx>0)
    {
        int d=-dx-2*dy,d1=-2*dy,d2=-2*dx-2*dy;
        while(x!=x2)
        {
            if(d<=0)
            {
                x++;
                d+=d1;
            }
            else
            {
                x++;
                y--;
                d+=d2;
            }
            SetPixel(hdc,x,y,c);
        }
    }
    else if((dx==0||dy/dx<-1)&&dy<0&&dx>=0)
    {
        int d=-2*dx-dy,d1=-2*dx,d2=-2*dx-2*dy;
        while(y!=y2)
        {
            if(d>0)
            {
                y--;
                d+=d1;
            }
            else
            {
                x++;
                y--;
                d+=d2;
            }
            SetPixel(hdc,x,y,c);
        }
    }
    else if((dx==0||dy/dx>1)&&dy<0&&dx<=0)
    {
        int d=-2*dx+dy,d1=-2*dx,d2=-2*dx+2*dy;
        while(y!=y2)
        {
            if(d<=0)
            {
                y--;
                d+=d1;
            }
            else
            {
                x--;
                y--;
                d+=d2;
            }
            SetPixel(hdc,x,y,c);
        }
    }
    else if(dy/dx>=0&&dy/dx<=1&&dy<=0&&dx<0)
    {
        int d=-dx+2*dy,d1=2*dy,d2=-2*dx+2*dy;
        while(x!=x2)
        {
            if(d>0)
            {
                x--;
                d+=d1;
            }
            else
            {
                x--;
                y--;
                d+=d2;
            }
            SetPixel(hdc,x,y,c);
        }
    }
    else if(dy/dx<0&&dy/dx>=-1&&dy>=0&&dx<0)
    {
        int d=dx+2*dy,d1=2*dy,d2=2*dx+2*dy;
        while(x!=x2)
        {
            if(d<=0)
            {
                x--;
                d+=d1;
            }
            else
            {
                x--;
                y++;
                d+=d2;
            }
            SetPixel(hdc,x,y,c);
        }
    }
    else if((dx==0||dy/dx<-1)&&dy>0&&dx<=0)
    {
        int d=2*dx+dy,d1=2*dx,d2=2*dx+2*dy;
        while(y!=y2)
        {
            if(d>0)
            {
                y++;
                d+=d1;
            }
            else
            {
                x--;
                y++;
                d+=d2;
            }
            SetPixel(hdc,x,y,c);
        }
    }
    cout<<"Midpoint Line"<<endl;


}



void Draw4points(HDC hdc, int xc, int yc, int x, int y, COLORREF c){
    SetPixel(hdc,xc+x,yc+y,c);
    SetPixel(hdc,xc-x,yc+y,c);
    SetPixel(hdc,xc+x,yc-y,c);
    SetPixel(hdc,xc-x,yc-y,c);
}

void Draw8points(HDC hdc, int xc, int yc, int x, int y, COLORREF c)
{
    SetPixel(hdc,xc+x,yc+y,c);
    SetPixel(hdc,xc-x,yc+y,c);
    SetPixel(hdc,xc+x,yc-y,c);
    SetPixel(hdc,xc-x,yc-y,c);
    SetPixel(hdc,xc+y,yc+x,c);
    SetPixel(hdc,xc+y,yc-x,c);
    SetPixel(hdc,xc-y,yc-x,c);
    SetPixel(hdc,xc-y,yc+x,c);
}
void Draw8points_4th(HDC hdc, int xc, int yc, int x, int y, COLORREF f)
{

    for(int i=xc;i<xc+x;i++)SetPixel(hdc,i,yc+y,f);
    for(int i=xc;i<xc+y;i++)SetPixel(hdc,i,yc+x,f);
    //DrawLineMidPoint(hdc,xc,yc,xc+x,yc+y,f);
    //DrawLineMidPoint(hdc,xc,yc,xc+y,yc+x,f);
}
void Draw8points_3rd(HDC hdc, int xc, int yc, int x, int y, COLORREF f)
{
    for(int i=xc;i>xc-x;i--)SetPixel(hdc,i,yc+y,f);
    for(int i=xc;i>xc-y;i--)SetPixel(hdc,i,yc+x,f);
    //DrawLineMidPoint(hdc,xc,yc,xc-x,yc+y,f);
    //DrawLineMidPoint(hdc,xc,yc,xc-y,yc+x,f);
}
void Draw8points_2nd(HDC hdc, int xc, int yc, int x, int y, COLORREF f)
{
    for(int i=xc;i>xc-x;i--)SetPixel(hdc,i,yc-y,f);
    for(int i=xc;i>xc-y;i--)SetPixel(hdc,i,yc-x,f);
    //DrawLineMidPoint(hdc,xc,yc,xc-x,yc-y,f);
    //DrawLineMidPoint(hdc,xc,yc,xc-y,yc-x,f);
}
void Draw8points_1st(HDC hdc, int xc, int yc, int x, int y, COLORREF f)
{
    for(int i=xc;i<xc+x;i++)SetPixel(hdc,i,yc-y,f);
    for(int i=xc;i<xc+y;i++)SetPixel(hdc,i,yc-x,f);
    //DrawLineMidPoint(hdc,xc,yc,xc+x,yc-y,f);
    //DrawLineMidPoint(hdc,xc,yc,xc+y,yc-x,f);
}

void DrawQCircleMidPoint(HDC hdc, int xc, int yc, int R, COLORREF c,int q){
    int x=0,y=R,d=1-R,d1=3,d2=5-2*R;
    if(q==18)
        Draw8points_1st(hdc, xc, yc, x,y,c);
    else if(q==19)
        Draw8points_2nd(hdc, xc, yc, x,y,c);
    else if (q==20)
        Draw8points_3rd(hdc, xc, yc, x,y,c);
    else if(q==21)
        Draw8points_4th(hdc, xc, yc, x,y,c);
    while(x<y){
        if(d<=0){
            d+=d1;
            d2+=2;
        }
        else{
            d+=d2;
            d2+=4;
            y--;
        }
        x++;
        d1+=2;
        if(q==18)
            Draw8points_1st(hdc, xc, yc, x,y,c);
        else if(q==19)
            Draw8points_2nd(hdc, xc, yc, x,y,c);
        else if (q==20)
            Draw8points_3rd(hdc, xc, yc, x,y,c);
        else if(q==21)
            Draw8points_4th(hdc, xc, yc, x,y,c);
    }
}

//14
void DrawCirclePolar(HDC hdc, int xc, int yc, int R, COLORREF c){
    double dtheta=1.0/R;
    for(double theta=0;theta<6.28;theta+=dtheta){
        int x= Round(xc+R*cos(theta));
        int y=Round(yc+R*sin(theta));
        SetPixel(hdc,x,y,c);
    }
    cout<<"Polar Circle"<<endl;
}
//15
void DrawCirclePolarIterative(HDC hdc, int xc, int yc, int R, COLORREF col){
    double dt=1.0/R;
    double c= cos(dt), s=sin(dt);
    double x=R,y=0;
    Draw8points(hdc,xc,yc,x,y,col);
    while(x>y){
        double x1= x*c-y*s;
        y=x*s+y*c;
        x=x1;
        Draw8points(hdc,xc,yc,Round(x),Round(y),col);
    }
    cout<<"Polar Iterative Circle"<<endl;
}
//13
void DrawCircleCartesian(HDC hdc, int xc, int yc, int R, COLORREF col){
    int x=0, y=R;
    Draw8points(hdc,xc,yc,x,y,col);
    while(x<y){
        x++;
        y=sqrt(R*R-x*x);
        Draw8points(hdc,xc,yc,x,y,col);
    }
    cout<<"Cartesian"<<endl;
}
//12
void DrawCircleMidPoint(HDC hdc, int xc, int yc, int R, COLORREF c){
    int x=0,y=R,d=1-R;
    Draw8points(hdc, xc, yc, x,y,c);
    while(x<y){
        if(d<0){
            d+=2*x+3;
            x++;
        }
        else{
            d+=2*(x-y)+5;
            x++;
            y--;
        }
        Draw8points(hdc,xc,yc,x,y,c);
    }
    cout<<"Midpoint Circle"<<endl;
}
//11
void DrawCircleMidPointModification(HDC hdc, int xc, int yc, int R, COLORREF c){
    int x=0,y=R,d=1-R,d1=3,d2=5-2*R;
    Draw8points(hdc, xc, yc, x,y,c);
    while(x<y){
        if(d<=0){
            d+=d1;
            d2+=2;
        }
        else{
            d+=d2;
            d2+=4;
            y--;
        }
        x++;
        d1+=2;
        Draw8points(hdc,xc,yc,x,y,c);
    }
    cout<<"Midpoint Mod Circle"<<endl;
}
//16
void DrawEllipsePolar(HDC hdc, int xc, int yc, int A,int B, COLORREF c){
    double dtheta=1.0/max(A,B);
    for(double theta=0;theta<6.28;theta+=dtheta){
        int x= Round(xc+A*cos(theta));
        int y=Round(yc+B*sin(theta));
        SetPixel(hdc,x,y,c);
    }
    cout<<"Polar Ellipse"<<endl;
}
//17
void DrawEllipsePolarIterative(HDC hdc, int xc, int yc, int A,int B, COLORREF col){
    double dtheta=1.0/max(A,B);
    double cd= cos(dtheta), sd=sin(dtheta);
    double x=xc+A, y= yc;
    double ct= (x-xc)/A;
    double st=(y-yc)/B;
    for(double theta=0;theta<6.28;theta+=dtheta){
        SetPixel(hdc,Round(x),Round(y),col);
        x= x*cd-st*A*sd;
        y= y*cd+ct*B*sd;
        ct= (x-xc)/A;
        st=(y-yc)/B;
        }
    cout<<"Polar Iterative Ellipse"<<endl;
}

double dy_dx(int x,double A,double B)
{
    int y=B*sqrt(1-(pow(x,2)/pow(A,2)));
    return (-x*pow(B,2))/(y*pow(A,2));
}
//22
void DrawEllipseDirectU(HDC hdc, int xc, int yc, int A,int B, COLORREF col){
    int x=0,y=B;
    Draw4points(hdc,xc,yc,x,y,col);
    while(x!=A && y!=0)
    {
        if(dy_dx(x,A,B)<=1)
        {
            x++;
            y=(B*sqrt(1-(pow(x,2)/pow(A,2))));
            Draw4points(hdc,xc,yc,x,y,col);
        }
    }
    x=A, y=0;
    Draw4points(hdc,xc,yc,x,y,col);
    while((y!=B && x!=0))
    {
        if((dy_dx(x,B,A)<1))
        {
            y++;
            x=(A*sqrt(1-(pow(y,2)/pow(B,2))));
            Draw4points(hdc,xc,yc,x,y,col);
        }
    }
    cout<<"Cartesian Ellipse"<<endl;
}
//36
void DrawRect(HDC hdc, double x1, double y1, double x2, double y2, COLORREF c){
DrawLineMidPoint(hdc,x1,y1,x2,y1,c);

DrawLineMidPoint(hdc,x2,y1,x2,y2,c);

DrawLineMidPoint(hdc,x1,y2,x2,y2,c);

DrawLineMidPoint(hdc,x1,y1,x1,y2,c);
cout<<"Rectangle Window"<<endl;
}
//34
void DrawCircleClip(HDC hdc,int xc,int yc, int R,int xl, int yt,int xr,int yb , COLORREF c){

    double dtheta=1.0/R;
    for(double theta=0;theta<6.28;theta+=dtheta){
        int x= Round(xc+R*cos(theta));
        int y=Round(yc+R*sin(theta));
        if(PointClipping(x,y,xl,yt,xr,yb))
            SetPixel(hdc,x,y,c);
    }
    cout<<"Clipped Circle"<<endl;
}

//35
void DrawEllipseClip(HDC hdc, int xc, int yc, int A,int B, COLORREF c,double xl,double yt,double xr,double yb){
    double dtheta=1.0/max(A,B);
    double cd= cos(dtheta), sd=sin(dtheta);
    double x=xc+A, y= yc;
    double ct= (x-xc)/A;
    double st=(y-yc)/B;
    for(double theta=0;theta<6.28;theta+=dtheta){
        if(PointClipping(x,y,xl,yt,xr,yb))
            SetPixel(hdc,Round(x),Round(y),c);
        x= x*cd-st*A*sd;
        y= y*cd+ct*B*sd;
        ct= (x-xc)/A;
        st=(y-yc)/B;
        }
    cout<<"Cliped Ellipse"<<endl;
}

union OutCode
{
    unsigned All:4;
    struct
    {
        unsigned left:1,top:1,right:1,bottom:1;
    };
};

OutCode GetOutCode(double x,double y,int xleft,int ytop,int xright,int ybottom)
{
    OutCode out;
    out.All=0;
    if(x<xleft)
        out.left=1;
    else if(x>xright)
        out.right=1;
    if(y<ytop)
        out.top=1;
    else if(y>ybottom)
        out.bottom=1;
    return out;
}
void VIntersect(double xstart,double ystart,double xend,double yend,int x,double *xi,double *yi)//xleft, right
{
    *xi=x;
    *yi=ystart+(x-xstart)*(yend-ystart)/(xend-xstart);
}
void HIntersect(double xstart,double ystart,double xend,double yend,int y,double *xi,double *yi)//ytop, bottom
{
    *yi=y;
    *xi=xstart+(y-ystart)*(xend-xstart)/(yend-ystart);
}
//33
void CohenSuthLineClipping(HDC hdc,int x1,int y1,int x2,int y2,int xleft,int ytop,int xright,int ybottom,COLORREF c)
{
    OutCode out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
    OutCode out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
    while( (out1.All || out2.All) && !(out1.All & out2.All)) //no two bite are equal (&Bit wise)
    {
        double xi,yi;
        if(out1.All)
        {
            if(out1.left)
                VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out1.top)
                HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out1.right)
                VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else
                HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x1=xi;
            y1=yi;
            out1=GetOutCode(x1,y1,xleft,ytop,xright,ybottom);
        }
        if(out2.All)
        {
            if(out2.left)
                VIntersect(x1,y1,x2,y2,xleft,&xi,&yi);
            else if(out2.top)
                HIntersect(x1,y1,x2,y2,ytop,&xi,&yi);
            else if(out2.right)
                VIntersect(x1,y1,x2,y2,xright,&xi,&yi);
            else
                HIntersect(x1,y1,x2,y2,ybottom,&xi,&yi);
            x2=xi;
            y2=yi;
            out2=GetOutCode(x2,y2,xleft,ytop,xright,ybottom);
        }
    }
    if(!out1.All && !out2.All)
    {
        DrawLineMidPoint(hdc,Round(x1),Round(y1),Round(x2),Round(y2),c);
    }
    cout<<"Clipped Line"<<endl;
}


Line::Line(int x1,int y1,int x2,int y2,COLORREF c,int dA)
{
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
    this->c=c;
    this->dA=dA;
}
void Line::draw(HDC hdc)
{
    if(this->dA==8)
        DrawLineDDA(hdc,this->x1,this->y1,this->x2,this->y2,this->c);
    else if(this->dA==9)
        DrawLineMidPoint(hdc,this->x1,this->y1,this->x2,this->y2,this->c);
    else if(this->dA==10)
        DrawLineParametric(hdc,this->x1,this->y1,this->x2,this->y2,this->c);

}
void Line::drawcliped(HDC hdc,int x1,int y1,int x2,int y2)
{
    CohenSuthLineClipping(hdc,this->x1,this->y1,this->x2,this->y2,x1,y1,x2,y2,this->c);
}
Circle::Circle(int x1,int y1,int x2,int y2,COLORREF c,int dA)
{
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
    this->c=c;
    this->dA=dA;
}
void Circle::draw(HDC hdc)
{
    int r= sqrt(pow(this->x2 - this->x1,2)+pow(this->y2 - this->y1,2));
    if(this->dA==14)
        DrawCirclePolar(hdc,this->x1,this->y1,r,this->c);
    else if(this->dA==15)
        DrawCirclePolarIterative(hdc,this->x1,this->y1,r,this->c);
    else if(this->dA==13)
        DrawCircleCartesian(hdc,this->x1,this->y1,r,this->c);
    else if(this->dA==12)
        DrawCircleMidPoint(hdc,this->x1,this->y1,r,this->c) ;
    else if(this->dA==11)
        DrawCircleMidPointModification(hdc,this->x1,this->y1,r,this->c);
}
void Circle::drawcliped(HDC hdc,int x1,int y1,int x2,int y2)
{
    int r= sqrt(pow(this->x2 - this->x1,2)+pow(this->y2 - this->y1,2));
    DrawCircleClip(hdc,this->x1,this->y1,r,x1,y1,x2,y2,this->c);
}
Ellipsee::Ellipsee(int x1,int y1,int x2,int y2,int x3,int y3,COLORREF c,int dA)
{
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
    this->x3=x3;
    this->y3=y3;
    this->c=c;
    this->dA=dA;
}
void Ellipsee::draw(HDC hdc)
{
    int A= sqrt(pow(this->x2 - this->x1,2)+pow(this->y2 - this->y1,2));
    int B= sqrt(pow(this->x3 - this->x1,2)+pow(this->y3 - this->y1,2));
    if(this->dA==16)
        DrawEllipsePolar(hdc,x1,y1,A,B,this->c);
    else if(this->dA==17)
        DrawEllipsePolarIterative(hdc,x1,y1,A,B,this->c);
    else if(this->dA==22)
        DrawEllipseDirectU(hdc,x1,y1,A,B,this->c);
}
void Ellipsee::drawcliped(HDC hdc,int x1,int y1,int x2,int y2)
{
    int A= sqrt(pow(this->x2 - this->x1,2)+pow(this->y2 - this->y1,2));
    int B= sqrt(pow(this->x3 - this->x1,2)+pow(this->y3 - this->y1,2));
    DrawEllipseClip(hdc,this->x1,this->y1,A,B,this->c,x1,y1,x2,y2);
}
QuarterFilledCircle::QuarterFilledCircle(int x1,int y1,int x2,int y2,COLORREF c,int dA)
{
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
    this->c=c;
    this->dA=dA;
}
void QuarterFilledCircle::draw(HDC hdc)
{
    int r= sqrt(pow(this->x2 - this->x1,2)+pow(this->y2 - this->y1,2));
    DrawQCircleMidPoint(hdc,this->x1,this->y1,r,this->c,this->dA);
}
void QuarterFilledCircle::drawcliped(HDC hdc,int x1,int y1,int x2,int y2)
{
    //Ýí ÇáãÓÊÞÈá
}

RectangleWindow::RectangleWindow(int x1,int y1,int x2,int y2,COLORREF c,int dA)
{
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
    this->c=c;
    this->dA=dA;
}
void RectangleWindow::draw(HDC hdc)
{
    DrawRect(hdc,this->x1,this->y1,this->x2,this->y2,this->c);
}
void RectangleWindow::drawcliped(HDC hdc,int x1,int y1,int x2,int y2)
{
    //Ýí ÇáãÓÊÞÈá
}
Shape::~Shape()
{
    //dtor
}

void Shapevector::addshape (Shape* shape)
{
    if(shape->dA==36)
        {
            this->xl=shape->x1;
            this->yt=shape->y1;
            this->xr=shape->x2;
            this->yb=shape->y2;
        }
    this->shapes.push_back(shape);
}
void Shapevector::drawShapes (HDC hdc)
{
    for(unsigned int i=0;i<shapes.size();i++)
    {
        if(shapes[i]->dA==36)
        {
            this->xl=shapes[i]->x1;
            this->yt=shapes[i]->y1;
            this->xr=shapes[i]->x2;
            this->yb=shapes[i]->y2;
        }
        if(shapes[i]->dA==33||shapes[i]->dA==34||shapes[i]->dA==35)
            shapes[i]->drawcliped(hdc,this->xl,this->yt,this->xr,this->yb);
        else
            shapes[i]->draw(hdc);

    }
}
void Shapevector::clearshapes()
{
    for(unsigned int i=0;i<shapes.size();i++)
    {
        delete shapes[i];
    }
    shapes.clear();
    system("CLS");
    cout<<"Shapes Cleared"<<endl;
}
void Shapevector::saveshapes(string path)
{
    ofstream save (path);
    {
        for(unsigned int i =0 ;i<this->shapes.size();i++)
        {
            if(shapes[i]->dA!=22&&shapes[i]->dA!=16&&shapes[i]->dA!=17&&shapes[i]->dA!=35)
                save<<shapes[i]->dA<<"\t"<<shapes[i]->x1<<"\t"<<shapes[i]->y1<<"\t"<<shapes[i]->x2<<"\t"<<shapes[i]->y2<<"\t"<<shapes[i]->c<<endl;
            else
            {
                int A= sqrt(pow(shapes[i]->x2 - shapes[i]->x1,2)+pow(shapes[i]->y2 - shapes[i]->y1,2));
                int B= sqrt(pow(shapes[i]->x3 - shapes[i]->x1,2)+pow(shapes[i]->y3 - shapes[i]->y1,2));
                save<<shapes[i]->dA<<"\t"<<shapes[i]->x1-A<<"\t"<<shapes[i]->y1-B<<"\t"<<shapes[i]->x1+A<<"\t"<<shapes[i]->y1+B<<"\t"<<shapes[i]->c<<endl;
            }
        }
    }
    save.close();
    cout<<"Shapes Saved"<<endl;
}
void Shapevector::loadshapes(string path)
{
    this->clearshapes();
    ifstream load (path);
    while(!load.eof())
        {
            int dA,x1,y1,x2,y2;
            COLORREF color;
            load>>dA>>x1>>y1>>x2>>y2>>color;
            if((dA>=8&&dA<=10)||dA==33)
            {
                Shape* nline=new Line(x1,y1,x2,y2,color,dA);
                this->addshape(nline);
            }
            else if((dA>=11&&dA<=15)||dA==34)
            {
                Shape* ncircle=new Circle(x1,y1,x2,y2,color,dA);
                this->addshape(ncircle);

            }
            else if(dA==16||dA==17||dA==22||dA==35)
            {
                Shape* nellipsee=new Ellipsee(x1+(x2-x1)/2,y1+(y2-y1)/2,x1,y1+(y2-y1)/2,x1+(x2-x1)/2,y1,color,dA);
                this->addshape(nellipsee);
            }
            else if(dA>=18&&dA<=21)
            {
                Shape* nfcircle=new QuarterFilledCircle(x1,y1,x2,y2,color,dA);
                this->addshape(nfcircle);
            }
            else if(dA==36)
            {
                this->xl=x1;
                this->yt=y1;
                this->xr=x2;
                this->yb=y2;
                 Shape* nrecwin=new RectangleWindow(x1,y1,x2,y2,color,dA);
                this->addshape(nrecwin);
            }
        }
        load.close();
    cout<<"Shapes Loaded"<<endl;
}
