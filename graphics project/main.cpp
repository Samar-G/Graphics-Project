#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <Shape.h>
///////////////////////////
#define Red RGB(255,0,0)
#define Black RGB(0,0,0)
#define Blue RGB(0,0,255)
#define Green RGB(0,110,0)
#define Yellow RGB(255,255,0)
#define Sea_Green RGB(2,150,90)
#define Cyan RGB(0,255,255)
#define Rose RGB(246,169,161)
#define Violet RGB(199,21,133)
#define Indian_Red RGB(205,85,85)
#define Purple RGB(147,112,219)
#define Steel_Blue RGB(104,131,139)
#define Khaki RGB(205,198,115)
#define Orange RGB(255,165,0)
#define Maroon RGB(139,0,0)
///////////////////////////////
#define Clear_Menue 0
///////////////////////////////
#define File_Menue_Save 1
#define File_Menue_Load 2
///////////////////////////////
#define Color_Menue_Red 3
#define Color_Menue_Green 4
#define Color_Menue_Blue 5
#define Color_Menue_Yellow 6
#define Color_Menue_Black 7
#define Color_Menue_Sea_Green 23
#define Color_Menue_Cyan 24
#define Color_Menue_Rose 25
#define Color_Menue_Violet 26
#define Color_Menue_Indian_Red 27
#define Color_Menue_Purple 28
#define Color_Menue_Steel_Blue 29
#define Color_Menue_Khaki 30
#define Color_Menue_Orange 31
#define Color_Menue_Maroon 32
//////////////////////////////
#define Line_Menue_DDA 8
#define Line_Menue_MidPoint 9
#define Line_Menue_Parametric 10
/////////////////////////////
#define Circle_Menue_MidPointModification 11
#define Circle_Menue_MidPoint 12
#define Circle_Menue_Cartesian 13
#define Circle_Menue_Polar 14
#define Circle_Menue_IterativePolar 15
/////////////////////////////
#define Ellipse_Menue_Polar 16
#define Ellipse_Menue_IterativePolar 17
#define Ellipse_Menue_Cartesian 22
/////////////////////////////
#define Filling_Menue_Circle1STQuarterFilling 18
#define Filling_Menue_Circle2NDQuarterFilling 19
#define Filling_Menue_Circle3RDQuarterFilling 20
#define Filling_Menue_Circle4THQuarterFilling 21
/////////////////////////////
#define Clipped_Menue_Line 33
#define Clipped_Menue_Circle 34
#define Clipped_Menue_Ellipse 35
#define Rectangle_Menue_Clipping 36

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Paint");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_HAND);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Paint"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           800,                 /* The programs width */
           800,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

string load(HWND hwnd)
{
    string path;
    OPENFILENAME ofn;
    char file_name[100];
    ZeroMemory(&ofn,sizeof(OPENFILENAME));
    ofn.lStructSize=sizeof(OPENFILENAME);
    ofn.hwndOwner=hwnd;
    ofn.lpstrFile=file_name;
    ofn.lpstrFile[0]='\0';
    ofn.nMaxFile=100;
    ofn.lpstrFilter="Text Files\0*.txt\0";
    ofn.nFilterIndex=1;
    GetOpenFileName(&ofn);
    path=ofn.lpstrFile;
    return path;
}
string save(HWND hwnd)
{
    string path;
    OPENFILENAME ofn;
    char file_name[100];
    ZeroMemory(&ofn,sizeof(OPENFILENAME));

    ofn.lStructSize=sizeof(OPENFILENAME);
    ofn.hwndOwner=hwnd;
    ofn.lpstrFile=file_name;
    ofn.lpstrFile[0]='\0';
    ofn.nMaxFile=100;
    ofn.lpstrFilter="Text Files\0*.txt\0";
    ofn.nFilterIndex=1;
    ofn.lpstrDefExt="*.txt";
    GetSaveFileName(&ofn);
    path=ofn.lpstrFile;
    return path;
}

HMENU hmenu;
void AddMenus(HWND hwnd)
{
    hmenu=CreateMenu();
    HMENU hFileMenue=CreateMenu();
    HMENU hColorMenue=CreateMenu();
    HMENU hLineMenue=CreateMenu();
    HMENU hCircleMenue=CreateMenu();
    HMENU hEllipseMenue=CreateMenu();
    HMENU hFillingMenue=CreateMenu();
    HMENU hClippingMenue=CreateMenu();
    /////////////////////////////////////
    AppendMenu(hFileMenue,MF_STRING,File_Menue_Save,"Save");
    AppendMenu(hFileMenue,MF_STRING,File_Menue_Load,"Load");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hFileMenue,"File");
    /////////////////////////////////////
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Red,"Red");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Green,"Green");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Blue,"Blue");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Yellow,"Yellow");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Black,"Black");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Sea_Green,"Sea Green");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Rose,"Rose");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Cyan,"Cyan");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Indian_Red,"Indian Red");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Violet,"Violet");

    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Steel_Blue,"Steel Blue");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Khaki,"Khaki");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Maroon,"Maroon");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Orange,"Orange");
    AppendMenu(hColorMenue,MF_STRING,Color_Menue_Purple,"Purple");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hColorMenue,"Color");
    /////////////////////////////////////
    AppendMenu(hLineMenue,MF_STRING,Line_Menue_DDA,"DDA");
    AppendMenu(hLineMenue,MF_STRING,Line_Menue_MidPoint,"MidPoint");
    AppendMenu(hLineMenue,MF_STRING,Line_Menue_Parametric,"Parametric");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hLineMenue,"Line");
    /////////////////////////////////////
    AppendMenu(hCircleMenue,MF_STRING,Circle_Menue_MidPointModification," MidPoint Modification");
    AppendMenu(hCircleMenue,MF_STRING,Circle_Menue_MidPoint,"MidPoint");
    AppendMenu(hCircleMenue,MF_STRING,Circle_Menue_Cartesian,"Cartesian");
    AppendMenu(hCircleMenue,MF_STRING,Circle_Menue_Polar,"Polar");
    AppendMenu(hCircleMenue,MF_STRING,Circle_Menue_IterativePolar,"Iterative Polar");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hCircleMenue,"Circle");
    /////////////////////////////////////
    AppendMenu(hEllipseMenue,MF_STRING,Ellipse_Menue_Polar,"Polar");
    AppendMenu(hEllipseMenue,MF_STRING,Ellipse_Menue_IterativePolar,"Iterative Polar");
    AppendMenu(hEllipseMenue,MF_STRING,Ellipse_Menue_Cartesian,"Cartesian");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hEllipseMenue,"Ellipse");
    /////////////////////////////////////
    AppendMenu(hFillingMenue,MF_STRING,Filling_Menue_Circle1STQuarterFilling,"Circle 1st Quarter Filling");
    AppendMenu(hFillingMenue,MF_STRING,Filling_Menue_Circle2NDQuarterFilling,"Circle 2nd Quarter Filling");
    AppendMenu(hFillingMenue,MF_STRING,Filling_Menue_Circle3RDQuarterFilling,"Circle 3rd Quarter Filling");
    AppendMenu(hFillingMenue,MF_STRING,Filling_Menue_Circle4THQuarterFilling,"Circle 4th Quarter Filling");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hFillingMenue,"Filling");
    /////////////////////////////////////
    AppendMenu(hClippingMenue,MF_STRING,Clipped_Menue_Line,"Clipped Line");
    AppendMenu(hClippingMenue,MF_STRING,Clipped_Menue_Circle,"Clipped Circle");
    AppendMenu(hClippingMenue,MF_STRING,Clipped_Menue_Ellipse,"Clipped Ellipse");
    AppendMenu(hClippingMenue,MF_STRING,Rectangle_Menue_Clipping,"Clipping Rectangle");
    AppendMenu(hmenu,MF_POPUP,(UINT_PTR)hClippingMenue,"Clipping");
    /////////////////////////////////////
    AppendMenu(hmenu,MF_STRING,Clear_Menue,"Clear");
    SetMenu(hwnd,hmenu);
}
int dA=0;
COLORREF color=Black;
int xs=0,ys=0,xf=0,yf=0;
Shapevector shapes;
Shape* nfcircle;
string path;
/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc=GetDC(hwnd);
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            AddMenus(hwnd);
            break;
        case WM_COMMAND:
            switch(wParam)
            {

                case Clear_Menue :
                    shapes.clearshapes();
                    InvalidateRect(hwnd, NULL, TRUE);    //clear window screen
                    break;
                //////////////////////////////
                case  File_Menue_Save :
                    path=save(hwnd);
                    if(path!="")
                        shapes.saveshapes(path);
                    break;
                case  File_Menue_Load :
                    path=load(hwnd);
                    if(path!="")
                        shapes.loadshapes(path);
                    shapes.drawShapes(hdc);
                    break;
                //////////////////////////////
                case  Color_Menue_Red :
                    color=Red;
                    cout<<"color=Red"<<endl;
                    break;
                case  Color_Menue_Green :
                    color=Green;
                    cout<<"color=Green"<<endl;
                    break;

                case  Color_Menue_Blue :
                    color=Blue;
                    cout<<"color=Blue"<<endl;
                    break;
                case  Color_Menue_Yellow :
                    color=Yellow;
                    cout<<"color=Yellow"<<endl;
                    break;
                case  Color_Menue_Black :
                    color=Black;
                    cout<<"color=Black"<<endl;
                    break;
                case  Color_Menue_Steel_Blue :
                    color=Steel_Blue;
                    cout<<"color=Steel Blue"<<endl;
                    break;
                case  Color_Menue_Sea_Green :
                    color=Sea_Green;
                    cout<<"color=Sea Green"<<endl;
                    break;
                case  Color_Menue_Cyan :
                    color=Cyan;
                    cout<<"color=Cyan"<<endl;
                    break;
                case  Color_Menue_Indian_Red :
                    color=Indian_Red;
                    cout<<"color=Indian Red"<<endl;
                    break;
                case  Color_Menue_Khaki :
                    color=Khaki;
                    cout<<"color=Khaki"<<endl;
                    break;
                case  Color_Menue_Maroon :
                    color=Maroon;
                    cout<<"color=Maroon"<<endl;
                    break;
                case  Color_Menue_Orange :
                    color=Orange;
                    cout<<"color=Orange"<<endl;
                    break;
                case  Color_Menue_Purple :
                    color=Purple;
                    cout<<"color=Purple"<<endl;
                    break;
                case  Color_Menue_Rose :
                    color=Rose;
                    cout<<"color=Rose"<<endl;
                    break;
                case  Color_Menue_Violet :
                    color=Violet;
                    cout<<"color=Violet"<<endl;
                    break;
                //////////////////////////////
                case  Line_Menue_DDA :
                    dA=Line_Menue_DDA;
                    break;
                case  Line_Menue_MidPoint :
                    dA=Line_Menue_MidPoint;
                    break;
                case  Line_Menue_Parametric :
                    dA=Line_Menue_Parametric;
                    break;
                /////////////////////////////
                case  Circle_Menue_MidPointModification :
                    dA=Circle_Menue_MidPointModification;
                    break;
                case  Circle_Menue_MidPoint :
                    dA=Circle_Menue_MidPoint;
                    break;
                case  Circle_Menue_Cartesian :
                    dA=Circle_Menue_Cartesian;
                    break;
                case  Circle_Menue_Polar :
                    dA=Circle_Menue_Polar;
                    break;
                case  Circle_Menue_IterativePolar :
                    dA=Circle_Menue_IterativePolar;
                    break;
                /////////////////////////////
                case Ellipse_Menue_Polar:
                    dA=Ellipse_Menue_Polar;
                    break;
                case Ellipse_Menue_IterativePolar:
                    dA=Ellipse_Menue_IterativePolar;
                    break;
                case Ellipse_Menue_Cartesian :
                    dA=Ellipse_Menue_Cartesian;
                    break;
                /////////////////////////////
                case  Filling_Menue_Circle1STQuarterFilling :
                    nfcircle=new QuarterFilledCircle(xs,ys,xf,yf,color,Filling_Menue_Circle1STQuarterFilling);
                    cout<<"("<<xs<<","<<ys<<")"<<":"<<"("<<xf<<","<<yf<<")"<<" -> ";
                    nfcircle->draw(hdc);
                    shapes.addshape(nfcircle);
                    break;
                case  Filling_Menue_Circle2NDQuarterFilling :
                    nfcircle=new QuarterFilledCircle(xs,ys,xf,yf,color,Filling_Menue_Circle2NDQuarterFilling);
                    cout<<"("<<xs<<","<<ys<<")"<<":"<<"("<<xf<<","<<yf<<")"<<" -> ";
                    nfcircle->draw(hdc);
                    shapes.addshape(nfcircle);
                    break;
                case  Filling_Menue_Circle3RDQuarterFilling :
                    nfcircle=new QuarterFilledCircle(xs,ys,xf,yf,color,Filling_Menue_Circle3RDQuarterFilling);
                    cout<<"("<<xs<<","<<ys<<")"<<":"<<"("<<xf<<","<<yf<<")"<<" -> ";
                    nfcircle->draw(hdc);
                    shapes.addshape(nfcircle);
                    break;
                case  Filling_Menue_Circle4THQuarterFilling :
                    nfcircle=new QuarterFilledCircle(xs,ys,xf,yf,color,Filling_Menue_Circle4THQuarterFilling);
                    cout<<"("<<xs<<","<<ys<<")"<<":"<<"("<<xf<<","<<yf<<")"<<" -> ";
                    nfcircle->draw(hdc);
                    shapes.addshape(nfcircle);
                    break;
                ///////////////////////////
                case Clipped_Menue_Line:
                    dA=Clipped_Menue_Line;
                    break;
                case Clipped_Menue_Circle:
                    dA=Clipped_Menue_Circle;
                    break;
                case Clipped_Menue_Ellipse :
                    dA=Clipped_Menue_Ellipse;
                    break;
                case Rectangle_Menue_Clipping :
                    dA=Rectangle_Menue_Clipping;
                    break;
            }
            break;
        case WM_LBUTTONDOWN :
            xs=LOWORD(lParam);
            ys=HIWORD(lParam);
            break;
        case WM_LBUTTONUP :
           xf=LOWORD(lParam);
            yf=HIWORD(lParam);
            if((dA>=8&&dA<=10)||dA==33)
            {
                Shape* nline=new Line(xs,ys,xf,yf,color,dA);
                cout<<"("<<xs<<","<<ys<<")"<<":"<<"("<<xf<<","<<yf<<")"<<" -> ";
                if(dA==33)
                    nline->drawcliped(hdc,shapes.xl,shapes.yt,shapes.xr,shapes.yb);
                else
                    nline->draw(hdc);
                shapes.addshape(nline);

                dA=-1;
            }
            else if((dA>=11&&dA<=15)||dA==34)
            {
                Shape* ncircle=new Circle(xs,ys,xf,yf,color,dA);
                cout<<"("<<xs<<","<<ys<<")"<<":"<<"("<<xf<<","<<yf<<")"<<" -> ";
                if(dA==34)
                    ncircle->drawcliped(hdc,shapes.xl,shapes.yt,shapes.xr,shapes.yb);
                else
                    ncircle->draw(hdc);
                shapes.addshape(ncircle);
                dA=-1;
            }
            else if(dA==16||dA==17||dA==22||dA==35)
            {
                Shape* nellipsee=new Ellipsee(xs+(xf-xs)/2,ys+(yf-ys)/2,xs,ys+(yf-ys)/2,xs+(xf-xs)/2,ys,color,dA);
                cout<<"("<<xs<<","<<ys<<")"<<":"<<"("<<xf<<","<<yf<<")"<<" -> ";
                if(dA==35)
                    nellipsee->drawcliped(hdc,shapes.xl,shapes.yt,shapes.xr,shapes.yb);
                else
                    nellipsee->draw(hdc);
                shapes.addshape(nellipsee);
                dA=-1;
            }
            else if(dA==36)
            {
                Shape* nrecwin=new RectangleWindow(xs,ys,xf,yf,color,dA);
                cout<<"("<<xs<<","<<ys<<")"<<":"<<"("<<xf<<","<<yf<<")"<<" -> ";
                nrecwin->draw(hdc);
                shapes.addshape(nrecwin);
                dA=-1;
            }
            break;
        case WM_SIZE:   // when minimized
            switch(wParam)
            {
                case SIZE_RESTORED:
                   shapes.drawShapes(hdc);
                   break;
            }
            break;
        case WM_DESTROY:
            shapes.clearshapes();
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
