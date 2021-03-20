#include"canvas.h"
#include"graphBasic.h"
using namespace events;

class Window:public MovableObject {
public:
	int width = 200;
	int height = 50;

	Window() {

		onmove = [=](int x, int y) {
			this->setPriority(Pri::Highest);
			moveto(x - width / 2, y - height / 2);
			canvas.repaint();
		};

		onmouseup = [=](int b, int x, int y) {
			resetPri();
		};

	};

	virtual void resize(int w, int h)
	{
		width = w;
		height = h;
		area.w = w;
		area.h = h;
		canvas.repaint();
	}

	Window(int x, int y) { posx = x; posy = y; };
	virtual void draw()
	{
		canvas.setColor(255, 255, 0);
		fillRect(posx, posy, width, height);
	}
};

class Button :public Window {
public:
	Button(string s)
	{
		setPriority(100);
		str = s;
		resize(s.length() * 20, 40);
		moveto(400, 400);
		area = Area(400, 400, 200, 60);
	}
	void setMovable(bool m )
	{
		movable = m;
	}
	virtual void draw()
	{
		useScale = false;
		canvas.setColor(235, 2, 2);
		fillRect(posx, posy, width, height);
		canvas.setColor(20, 20, 20);
		canvas.drawRect(posx, posy, posx + width, posy + height);
		drawString(posx + 15, posy + 13, str);
		useScale = true;
	}

	void setText(string s)
	{
		str = s;
		resize(s.length() * 20, 40);
	}

	string str;
};
