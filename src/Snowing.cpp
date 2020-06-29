#include <windows.h>
#include <GL\gl.h>
#include <GL\glu.h>
#include <math.h>
#include <stdlib.h>
#include "App.h"
#include "Window/Win32.h"

const int N=500;

struct tsnow {
	float x, y, sp;
	int angle;
} Point[N];

struct tobject {
	float x, y, z;
} Circle[100], Haos[100], Some[100], Haos2[100];

struct tmorph {
	float x, y, z, xs, ys, zs;
} ObjectX[100];

int i;

HWND hWnd;
HGLRC hglrc;
HDC hDC;
GLfloat angle=0, rad=3.14/180;
bool keys[256];
bool Morphing=FALSE;
int StepMorph=1;
bool Exit=FALSE;
float Ex=1;
bool ShowMorph=TRUE;

void ProcessKeys(void)
{
	if (keys[VK_ESCAPE])
		Exit=TRUE;
	if (keys[VK_SPACE])
	{
		if (ShowMorph==TRUE) ShowMorph=FALSE;
		else ShowMorph=TRUE;
	}
}

void InitGL(void)
{
	for (i=0; i<N; i++)
	{
		Point[i].x=((GLfloat) (rand()%120))/100-0.6;
		Point[i].y=((GLfloat) (rand()%100))/100-0.5;
		Point[i].sp=(GLfloat) (1+rand()%3)/1000;
		Point[i].angle=rand()%360;
	}
	
	float step=100/(2*3.141592);
	float aangle=0;
	for (i=0; i<100; i++)
	{
		Some[i].x=0.1*cos(aangle*rad);
		Some[i].y=0.1*sin(aangle*rad);
		Some[i].z=0.1*cos(aangle*rad)*sin(aangle*rad);

		Circle[i].x=0.1*cos(aangle*rad);
		Circle[i].y=0.1*sin(aangle*rad);
		Circle[i].z=0.1*cos(aangle*rad);
		aangle=aangle+step;
		Haos[i].x=(GLfloat) (rand()%30)/100-0.15;
		Haos[i].y=(GLfloat) (rand()%30)/100-0.15;
		Haos[i].z=(GLfloat) (rand()%30)/100-0.15;

		Haos2[i].x=0.1*sin(aangle*rad)*cos(aangle*rad);
		Haos2[i].y=0.1*cos(aangle*rad);
		Haos2[i].z=0.1*sin(aangle*rad)*cos(aangle*rad);
	}
	for (int i=0; i<100; i++)
	{
		ObjectX[i].x=Haos2[i].x;
		ObjectX[i].y=Haos2[i].y;
		ObjectX[i].z=Haos2[i].z;
	}
	angle=0;

	glClearColor(0, 0, 0, 0);

    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat aspect = (GLfloat) GetSystemMetrics(SM_CXSCREEN) / GetSystemMetrics(SM_CYSCREEN);
    gluPerspective( 45.0, aspect, 0.1, 100.0 );
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);	
	glDepthFunc(GL_LEQUAL);	

	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
}

void drawscene(void)
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	glLoadIdentity();
	glColor4f(1, 1, 1, Ex);
	glTranslatef(0, 0, -1);
	glPointSize(1);
	glBegin(GL_POINTS);
		for (i=0; i<N; i++)
			glVertex3f(Point[i].x+0.007*cos(Point[i].angle*rad), Point[i].y, 0);
	glEnd();

	if (ShowMorph==TRUE)
	{
		glLoadIdentity();
		glColor4f(1, 0, 1, Ex);
		glTranslatef(0, 0, -1);
		glRotatef(angle, sin(angle*rad), cos(angle*rad), 0);
		glPointSize(1.5);
		glBegin(GL_POINTS);
			for (i=0; i<100; i++)
				glVertex3f(ObjectX[i].x, ObjectX[i].y, ObjectX[i].z);
		glEnd();
	}

	for (i=0; i<N; i++)
	{
		Point[i].y=Point[i].y-Point[i].sp;
		Point[i].angle+=5;
		if (Point[i].y<-0.5)
		{
			Point[i].x=((GLfloat) (rand()%120))/100-0.6;
			Point[i].y=0.5;
			Point[i].angle=rand()%360;
		}
	}

	if (StepMorph==300) 
	{
		Morphing=FALSE;
		StepMorph=1;
	}
	if (StepMorph==200) 
	{
		int z=rand()%4;
		switch (z)
		{
		case 0:
			{
			for (int i=0; i<100; i++)
			{
				ObjectX[i].xs=(Haos[i].x-ObjectX[i].x)/100;
				ObjectX[i].ys=(Haos[i].y-ObjectX[i].y)/100;
				ObjectX[i].zs=(Haos[i].z-ObjectX[i].z)/100;
			}
			break;
			}
		case 1:
			{
			for (int i=0; i<100; i++)
			{
				ObjectX[i].xs=(Haos2[i].x-ObjectX[i].x)/100;
				ObjectX[i].ys=(Haos2[i].y-ObjectX[i].y)/100;
				ObjectX[i].zs=(Haos2[i].z-ObjectX[i].z)/100;
			}
			break;
			}
		case 2:
			{
			for (int i=0; i<100; i++)
			{
				ObjectX[i].xs=(Circle[i].x-ObjectX[i].x)/100;
				ObjectX[i].ys=(Circle[i].y-ObjectX[i].y)/100;
				ObjectX[i].zs=(Circle[i].z-ObjectX[i].z)/100;
			}
			break;
			}
		case 3:
			{
			for (int i=0; i<100; i++)
			{
				ObjectX[i].xs=(Some[i].x-ObjectX[i].x)/100;
				ObjectX[i].ys=(Some[i].y-ObjectX[i].y)/100;
				ObjectX[i].zs=(Some[i].z-ObjectX[i].z)/100;
			}
			break;
			}
		}
		Morphing=TRUE;
	}
	if (Morphing==TRUE)
	{
		for (i=0; i<100; i++)
		{
			ObjectX[i].x+=ObjectX[i].xs;
			ObjectX[i].y+=ObjectX[i].ys;
			ObjectX[i].z+=ObjectX[i].zs;
		}
	}

	StepMorph++;
	angle+=1;
	if (angle==360) angle=0;

	if (Exit==TRUE) Ex=Ex-0.005;
	if (Ex<0.1) SendMessage(hWnd, WM_DESTROY, 0, 0);

	SwapBuffers(hDC);
}

BOOL bSetupPixelFormat(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd, *ppfd;
    int pixelformat;

    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_RGBA;
    ppfd->cColorBits = 8;
    ppfd->cDepthBits = 16;
    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;

    if ( (pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0 )
    {
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE)

    {
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    return TRUE;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			if (!wglMakeCurrent(NULL, NULL))
				MessageBox(hWnd, "wglMakeCurrent", "Error", MB_OK);
			if (!wglDeleteContext(hglrc))
				MessageBox(hWnd, "wglDeleteContext", "Error", MB_OK);
			PostQuitMessage(0);
			break;

		case WM_CREATE:
			hDC=GetDC(hWnd);
			if (!bSetupPixelFormat(hDC))
				MessageBox(hWnd, "Setup pixel format", "Error", MB_OK);
			hglrc=wglCreateContext(hDC);
			if (hglrc==NULL) MessageBox(hWnd, "wglCreateContext", "Error", MB_OK);
			if (!wglMakeCurrent(hDC, hglrc))
				MessageBox(hWnd, "wglMakeCurrent", "Error", MB_OK);
			InitGL();
			break;
		
		case WM_KEYDOWN:
			keys[wParam] = true;
            ProcessKeys();
			break;

		case WM_KEYUP:
			keys[wParam] = false;
			break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	MessageBox(hWnd, "SNOWING\n\n"
					 "Code by Astakhov Nikolay\n"
					 "Made in Novouralsk 2003\n\n"
					 "Active keys:\n"
					 "'SPACE' - Morphing\n"
					 "'Esc' - exit", "SNOWING", MB_OK | MB_ICONINFORMATION);

	App* app = new App(new Win32(hInstance));
	app->Init();

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, nullptr, 0, 0)) {
			    break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		drawscene();
	}

	delete app;
	return 0;
}
