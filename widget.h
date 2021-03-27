#include"canvas.h"
#include"graphBasic.h"
#include"painter.h"
using namespace events;

class Window :public MovableObject {
public:
	int width = 200;
	int height = 50;

	Window(int w, int h)
	{
		resize(w, h);
		addEvent();
	}

	Window() {
		addEvent();
	};
	void addEvent()
	{
		onmove = [=](int x, int y) {
			this->setPriority(Pri::Highest);
			moveto(x - width / 2, y - height / 2);
			canvas.repaint();
		};

		onmouseup = [=](int b, int x, int y) {
			resetPri();
		};
	}
	virtual void resize(int w, int h)
	{
		width = w;
		height = h;
		area.w = w;
		area.h = h;
		canvas.repaint();
	}

	virtual void draw()
	{
		canvas.setColor(co);
		painter.fillRect(posx, posy, width, height);
	}
};

class Button :public Window {
public:
	Button(string s)
	{
		setPriority(1000);
		str = s;
		resize(s.length() * 20, 40);
		moveto(400, 400);
		area = Area(400, 400, 200, 60);
	}
	void setMovable(bool m)
	{
		movable = m;
	}
	virtual void draw()
	{
		useScale = false;
		painter.setColor(235, 2, 2);
		pntr.fillRect(posx, posy, width, height);
		painter.setColor(20, 20, 20);
		painter.drawRect(posx, posy, posx + width, posy + height);
		drawString(posx + 15, posy + 13, str);
		useScale = true;
	}

	void setText(string s)
	{
		str = s;
		resize(s.length() * 20, 40);
		canvas.repaint();
	}

	string str;
};
vector<Line> lines;

struct state {
	state()
	{
		x = rand() % win_width()+10;
		y = rand() % win_height()+10;
		w = rand() % win_width();
		h = rand() % win_height();
	}
	int x;
	int y;
	int w;
	int h;
};

class Tailor : public Window {
public:
	Tailor(int w, int h) :Window(w, h) {
		onstick = [=](int b, int s, int x, int y) {
			if (b == GLUT_LEFT_BUTTON &&height<win_h)
			{
				resize(width *= 1.02, height *= 1.02);
			}
			else if (b == GLUT_RIGHT_BUTTON && height > win_h*0.1)
			{
				resize(width *= 0.98, height *= 0.98);
			}
		};
	}

	void draw()
	{
		canvas.setColor(co);
		pntr.fillRect(posx, posy, width, height);
		canvas.setColor(255, 0, 0);
		for (int i = 0; i < lines.size(); i++)
		{
			Line l = cut(lines[i].p1, lines[i].p2);
			if (l.need)
			{
				painter.drawLine(l.p1.x, l.p1.y, l.p2.x, l.p2.y);
				painter.fillCircle(l.p1.x, l.p1.y, 5);
				painter.fillCircle(l.p2.x, l.p2.y, 5);
			}
		}
	}

	Line cut(point p1, point p2)
	{
		point pp[6]; pp[0] = p1; pp[1] = p2;
		float k = (p2.y - p1.y) / (p2.x - p1.x);
		float kinver;
		if (k != 0)kinver = 1 / k;
		else kinver = 1e10;
		pp[2] = point(posx, p2.y - k * (p2.x - posx));
		pp[3] = point(p1.x - kinver * (p1.y - posy), posy);
		pp[4] = point(posx + width, p1.y - k * (p1.x - posx - width));
		pp[5] = point(p2.x - kinver * (p2.y - posy - height), posy + height);
		sort(pp, pp + 6);
		point mid((pp[2].x + pp[3].x) / 2, (pp[3].y + pp[2].y) / 2);
		if (posx < mid.x && mid.x < posx + width
			&& posy < mid.y && mid.y < posy + height)
		{
			Line l(pp[2].x, pp[2].y, pp[3].x, pp[3].y);
			l.need = true;
			return l;
		}
		return Line(0, 0, 0, 0);
	}

	void gotoState(state s)
	{
		moveto(posx+(s.x - posx) * 0.02,posy+(s.y - posy) * 0.02);
		resize(width+(s.w-width)*0.02,height+(s.h-height)*0.02);
	}
};