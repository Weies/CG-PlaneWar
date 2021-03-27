#pragma once
#include"graphBasic.h"
#include"canvas.h"
#include"painter.h"
class Circle :public MovableObject {
public:
	float r;//半径
	float px; float py;//旋转时圆心相对旋转中心的位置
	float rx; float ry;//旋转中心

	Circle(float xx, float yy, float rr) {
		moveto(xx, yy);
		r = rr;
		px = 150; py = 150;
		rx = 400; ry = 300;
		area.w = 2 * r;
		area.h = 2 * r;
		area.setOffset(-r, -r);
		onmove = [=](int x, int y) {
			moveto(x, y);
		};

		setColor(255, 65, 20);
	}

	void setRotateCenter(float xx, float yy)
	{
		rx = xx; ry = yy;
	}

	void draw()
	{
		canvas.setColor(co);
		int delta = r * scaleTimes;
		int rr = r * r * scaleTimes * scaleTimes;
		int x = posx * scaleTimes;
		int y = posy * scaleTimes;
		glBegin(GL_POINTS);
		useScale = false;
		for (int i = -delta; i < delta; i++)
		{
			for (int j =-delta; j <delta; j++)
			{
				if (i*i+j*j< rr)
					glPixel(x+i, y+j);
			}
		}
		useScale = true;
		glEnd();
	}

	void rotate(float deg) {
		point p = rot(px, py, deg);
		px = p.x;
		py = p.y;
		posx = rx + p.x;
		posy = ry + p.y;
		area.x = posx;
		area.y = posy;
	}

private:
};

class Triangle :public MovableObject {
public:
	float x1 = 0; float y1 = 100;
	float x2 = 100; float y2 = -80;
	float x3 = -100; float y3 = -40;

	Triangle(float xx, float yy) {
		posx = xx; posy = yy;
		area.setOffset(-100, -100);
		area.setArea(xx, yy, 200, 200);
		setColor(120, 160, 240);
		onmove = [=](int x, int y) {
			moveto(x, y);
		};
	}

	void rotate(float deg) {
		point p(0, 0);
		p = rot(x1, y1, deg);
		x1 = p.x;
		y1 = p.y;
		p = rot(x2, y2, deg);
		x2 = p.x;
		y2 = p.y;
		p = rot(x3, y3, deg);
		x3 = p.x;
		y3 = p.y;
	}

	void draw()
	{
		canvas.setColor(co);
		glBegin(GL_TRIANGLES);
		glPixel(posx + x1, posy + y1);
		glPixel(posx + x2, posy + y2);
		glPixel(posx + x3, posy + y3);
		glEnd();
	}
private:
};

class Rect :public MovableObject
{
public:
	int width; int height;//左上角的位置
	
	Rect(float xx, float yy, float w, float h) {
		posx = xx; posy = yy; height = h; width = w;
		area.setArea(xx, yy, w, h);
		setColor(0, 255, 0);
		onmove = [=](int x, int y) {
			this->setPriority(Pri::Highest);
			moveto(x - width / 2, y - height / 2);
			canvas.repaint();
		};

		onmouseup = [=](int b, int x, int y) {
			resetPri();
		};
	}
	
	void draw()
	{
		canvas.setColor(co);
		painter.fillRect(posx,posy,width,height);
	}
};

class LineOBJ :public FixedObject {
public:
	float ex;
	float ey;
	LineOBJ(float xx, float yy, float endx, float endy) {
		posx = xx; posy = yy; ex = endx; ey = endy;
		setColor(255, 0, 0);
	}

	void draw()
	{
		canvas.setColor(co);
		glBegin(GL_LINE_STRIP);
		glPixel(posx, posy);
		glPixel(ex, ey);
		glEnd();
	}
};

template<class T>
class CirList {
public:
	CirList(int n):list(n){
		maxSize = n;
	}
	void push_back(const T& t)
	{
		curr++;
		if (curr == maxSize)curr = 0;
		list[curr] = t;
	}
	T& operator[](int i)
	{
		if(i+curr<maxSize)
		return list[curr+i];
		return list[curr + i -maxSize];
	}
	int size()
	{
		return list.size();
	}
	int curr = 0;
	int maxSize;
	vector<T> list;
};

class bullets {
public:
	bullets(){}

	bullets(float xx, float yy)
	{
		x = xx; y = yy;
		dx = (rand() % 10000-5000)/500.0;
		dy = (rand() % 10000-5000) / 500.0;
	}

	float X()
	{
		return x += dx;
	}
	float Y()
	{
		return y += dy;
	}
	float x; float y;
	float dx;
	float dy;
};
CirList<point> mybullet(3000);
CirList<bullets> hisbullet(3000);

class Plane :public MovableObject {
public:
	int HP = 5000;
	int width = 100;
	int height = 100;
	Plane()
	{
		setPriority(Pri::Highest);
		area.setArea(300, 300, 60, 60);
		moveto(300, 300);
		area.setOffset(-50, -50);
		
		onclick = [=](int b, int s, int x, int y)
		{
			this->setPriority(Pri::Highest);
		};

		onmove = [=](int x, int y) {
			moveto(x , y);
		};

		onmouseup = [=](int b, int x, int y) {
			resetPri();
		};

		canvas.setKeyFunc([=](unsigned char key, int x, int y) {
			switch (key)
			{
			case GLUT_KEY_DOWN:
				moveto(posx, posy - 15);
				break;
			case GLUT_KEY_UP:
				moveto(posx, posy + 15);
				break;
			case GLUT_KEY_RIGHT:
				moveto(posx +15, posy);
				break;
			case GLUT_KEY_LEFT:
				moveto(posx -15, posy);
				break;
			default: break;
			}
			canvas.repaint();
		});
		setColor(25, 125, 255);
	}

	void draw()
	{
		canvas.setColor(co);
		glBegin(GL_TRIANGLES);
		glPixel(posx, posy);
		glPixel(posx, posy+50);
		glPixel(posx-50, posy-30);

		glPixel(posx+50, posy-30);
		glPixel(posx, posy);
		glPixel(posx, posy + 50);
		glEnd();
		canvas.setColor(0, 255, 0);
		pntr.fillRect(posx-25, posy+60, HP / 100, 5);
		canvas.setColor(0, 0, 255);
		painter.drawCircle(posx, posy, 30);
	}
};

class Enemy :public MovableObject {
public:
	int width = 100;
	int height = 100;
	int HP = 1000;
	Enemy()
	{
		setPriority(200);
		moveto(300, 300);
		area.setOffset(-50, -50);
		area.setArea(300, 300, 100, 100);
		onmove = 0;
	}
	void draw()
	{
		canvas.setColor(255, 0, 0);
		glBegin(GL_TRIANGLES);
		glPixel(posx, posy);
		glPixel(posx, posy - 50);
		glPixel(posx + 50, posy + 30);

		glPixel(posx - 50, posy + 30);
		glPixel(posx, posy);
		glPixel(posx, posy - 50);
		glEnd();
		canvas.setColor(255, 0, 0);
		pntr.fillRect(posx - 25, posy - 70, HP / 20, 5);
	}
};