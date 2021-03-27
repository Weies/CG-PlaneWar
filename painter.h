#pragma once
#include"graphBasic.h"
#define pntr painter
#define ptr painter
class Painter {
public:
	Painter() :co(0, 0, 0) {}

	void setColor(float r, float g, float b, float a = 1)
	{
		co = Color(r, g, b, a);
		glColor4f(r*1.0/255, g*1.0/255, b*1.0/255, a);
	}
	void setColor(const Color& c) {
		co = c;
		glColor4f(co.r*1.0/255, co.g*1.0/255, co.b*1.0/255, co.a);
	}

	static void drawRect(int xx, int yy, int ex, int ey)
	{
		glBegin(GL_LINE_STRIP);
		glPixel(xx, yy);
		glPixel(xx, ey);
		glPixel(ex, ey);
		glPixel(ex, yy);
		glPixel(xx, yy);
		glEnd();
	}

	static void drawLine(int xx, int yy, int ex, int ey)
	{
		glBegin(GL_LINES);
		glPixel(xx, yy);
		glPixel(ex, ey);
		glEnd();
	}

	static void drawCircle(int x, int y, int r)
	{
		int startpos = x-sqrt(2)/2*r;
		glBegin(GL_POINTS);
		for (int i = startpos; i<=x; i++)
		{
			float py = sqrt(r*r-i*i+2*x*i-x*x);
			glPixel(i, py+y);
			glPixel(i, -py+y);
			glPixel(2*x-i, py+y);
			glPixel(2*x-i, -py+y);
			glPixel(py+x, y+i-x);
			glPixel(py+x, y+x-i);
			glPixel(x-py, y+i-x);
			glPixel(x-py, y+x-i);
		}
		glEnd();
	}

	static void fillCircle(int xx, int yy, int rr)
	{
		int sx = xx-rr; int ex = xx+rr;
		int sy = yy-rr; int ey = yy+rr;
		int k1 = rr*rr-xx*xx-yy*yy; int k2 = 2*xx; int k3 = 2*yy;
		glBegin(GL_POINTS);
		for (int i = sx; i<ex; i++)
		{
			for (int j = sy; j<ey; j++)
			{
				if (i*i+j*j<k1+k2*i+k3*j)
				{
					glPixel(i, j);
				}
			}
		}
		glEnd();
	}

	static void drawPoint(float x, float y)
	{
		glBegin(GL_POINTS);
		glPixel(x, y);
		glEnd();
	}

	static void fillRect(float x, float y, int b)
	{
		glRectf(transX(x*30), transY(y*30+b), transX(x*30+30), transY(y*30+b+30));
		drawPoint(x*30, y*30+b);
	}

	static void fillRect(int x, int y, int width, int height)
	{
		glRectf(transX(x), transY(y), transX(x+width), transY(y+height));
	}

	static void fillTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
	{
		glBegin(GL_TRIANGLES);
		glPixel(x1, y1);
		glPixel(x2, y2);
		glPixel(x3, y3);
		glEnd();
	}

	static void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
	{
		glBegin(GL_LINES);
		glPixel(x1, y1);
		glPixel(x2, y2);
		glPixel(x3, y3);
		glPixel(x1, y1);
		glEnd();
	}

	static void fillTriangle(point p1, point p2, point p3)
	{
		glBegin(GL_TRIANGLES);
		glPixel(p1.x, p1.y);
		glPixel(p2.x, p2.y);
		glPixel(p3.x, p3.y);
		glEnd();
	}

	static void drawTriangle(point p1, point p2, point p3)
	{
		glBegin(GL_LINES);
		glPixel(p1.x, p1.y);
		glPixel(p2.x, p2.y);
		glPixel(p3.x, p3.y);
		glEnd();
	}

	static void repaint()
	{
		canvas.repaint();
	}
	
	Color co;
};
Painter painter;