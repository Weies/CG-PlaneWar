#pragma once
#include"glut/glut.h"
#include"events.h"
#include"canvas.h"
using namespace std;
using namespace events;
using namespace globals;

struct Area {
	Area(int a, int b, int c, int d) {
		x = a; y = b; w = c; h = d;
	}

	Area() { x = 0; y = 0; w = 0; h = 0; }
	bool inArea(int xx, int yy)
	{
		 bool ret = (x + offsetx < xx&& y + offsety < yy
			&& yy < y + offsety + h && xx < x + offsetx + w);
		 return ret;
	}

	void setOffset(int x, int y)//设置响应中心的偏移量
	{							//，用于绘图中心不是左下角的
		offsetx = x;
		offsety = y;
	}

	void setArea(int a, int b, int c, int d)
	{
		x = a; y = b; w = c; h = d;
	}

	int offsetx = 0;
	int offsety = 0;
	int x; int y;
	int w; int h;

};

struct point {
	point() {};
	point(float xx, float yy) {
		x = xx;
		y = yy;
	}
	bool operator<(point& otr)
	{
		return y < otr.y;
	}
	float x, y;
};

point rot(float dx, float dy, float deg) {
	point ret;
	double a = deg * M_PI / 180.0;
	double a1 = atan(dy * 1.0 / dx);
	if (dx < 0)
	{
		a1 += M_PI;
	}
	float c = a1 - a;
	double length = sqrt(dx * dx + dy * dy);
	ret.x = length * cos(c);
	ret.y = length * sin(c);
	return ret;
}

//抽象可移动对象,需要实现draw()函数
class AbstractMovableObject : public BasicGraphObject {
public:
	Area area;//点击响应的区域
	float posx;//绘图中心的x,y坐标
	float posy;

	function<void(int, int, int, int)> onclick = 0;
	function<void(int, int)> onmove = 0;
	function<void(int, int, int, int)> onstick = 0;
	function<void(int, int)> onkeydown = 0;
	function<void(int, int)> onkeyup = 0;
	function<void(int, int, int)> onmouseup = 0;

	void setOnClick(function<void(int, int, int, int)> func) {
		onclick = func;
	}
	void setOnMouseUp(function<void(int, int, int)> func) {
		onmouseup = func;
	}
	void setOnMove(function<void(int, int)> func) {
		onmove = func;
	}
	void setOnStick(function<void(int, int, int, int)> func) {
		onstick = func;
	}
	void setOnKeyDown(function<void(int, int)> func) {
		onkeydown = func;
	}
	void setOnKeyUp(function<void(int, int)> func) {
		onkeyup = func;
	}

	AbstractMovableObject() {
		area.w = 200;
		area.h = 200;
		priority = Priority++;
		defaultpri = priority;
		displayList.push(this);
		posx = 0; posy = 0;
	}

	void moveto(int xx, int yy) {
		posx = xx ; posy = yy ;
		area.x = xx ; area.y = yy ;
	};

	virtual void rotate(float deg) {};

	virtual void resize(int w, int h)
	{
		area.w = w;
		area.h = h;
		canvas.repaint();
	}
};

void arrangeMove(int x, int y);
void arrangeClick(int b, int state, int x, int y);
void arrangeStick(int b, int state, int x, int y);
void arrangeMouseUp(int b, int x, int y);
bool comp(AbstractMovableObject* a1, AbstractMovableObject* a2)
{
	if (a1->priority > a2->priority)
		return true;
	return false;
}

class BlockManager {
public:

	BlockManager() {
		arrangeMoveFunc = arrangeMove;
		arrangeClickFunc = arrangeClick;
		arrangeStickFunc = arrangeStick;
		arrangeMouseUpFunc = arrangeMouseUp;
	}

	void resort()
	{
		sort(list.begin(), list.end(), comp);
	}

	void push(AbstractMovableObject* win)
	{
		list.push_back(win);
		sort(list.begin(), list.end(), comp);
	}

	vector<AbstractMovableObject*> list;
};

BlockManager block;


void updatePri()//使设置的优先级生效
{
	block.resort();
	displayList.resort();
}

//鼠标事件安排函数
void arrangeMove(int x, int y)
{
	for (int i = 0; i < block.list.size(); i++)
	{
		if (block.list[i]->area.inArea(x, y))
		{
			moveHandled = true;
			if(block.list[i]->onmove&& block.list[i]->movable)
			block.list[i]->onmove(x, y);
			break;
		}
	}
}

void arrangeClick(int b, int state, int x, int y)
{
	for (int i = 0; i < block.list.size(); i++)
	{
		if (block.list[i]->area.inArea(x, y))
		{
			if (block.list[i]->onclick)
				block.list[i]->onclick(b, state, x, y);
			break;
		}
	}
}

void arrangeStick(int b, int state, int x, int y)
{
	for (int i = 0; i < block.list.size(); i++)
	{
		if (block.list[i]->area.inArea(x, y))
		{
			if (block.list[i]->onstick)
				block.list[i]->onstick(b, state, x, y);
			break;
		}
	}
}

void arrangeMouseUp(int b, int x, int y)
{
	for (int i = 0; i < block.list.size(); i++)
	{
		if (block.list[i]->area.inArea(x, y))
		{
			if (block.list[i]->onmouseup)
				block.list[i]->onmouseup(b, x, y);
			break;
		}
	}
}

//可移动对象
class MovableObject : public AbstractMovableObject {
public:
	MovableObject()
	{
		block.push(this);
	}

	void setPriority(int pri)
	{
		priority = pri;
		updatePri();
	}

	void setDefaultPri(int pri)
	{
		defaultpri = pri;
	}
	
	void resetPri()
	{
		priority =defaultpri;
		updatePri();
	}
	virtual void draw() {}
};

//抽象不可以动对象
class FixedObject : public BasicGraphObject {
public:
	float posx;//绘图中心的x,y坐标
	float posy;

	FixedObject() {
		displayList.push(this);
		setPriority(Pri::Lowest);
		posx = 0; posy = 0;
	}

	void setPriority(int pri)
	{
		priority = pri;
		updatePri();
	}

	void setDefaultPri(int pri)
	{
		defaultpri = pri;
	}

	void resetPri()
	{
		priority = defaultpri;
		updatePri();
	}
	virtual void moveto(int xx, int yy) {
		posx = xx; posy = yy;
	};

	virtual void rotate(float deg) {};

};


class Line {
public:
	Line(){}

	Line(int x, int y, int a, int b)
	{
		p1.x = x; p1.y = y;
		p2.x = a; p2.y = b;
		if (x || y || a || b)need = true;
	}
	bool need = false;
	point p1;
	point p2;
};