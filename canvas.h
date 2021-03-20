#pragma once
#include"events.h"
using namespace events;

void reshape(int w, int h);

class Canvas {
public:
	Canvas(int ww, int hh, const Color& co = Color(255, 255, 255)) :backcolor(co) {
		win_width = ww;
		win_height = hh;
		init();
		setHook();
	}
	void setColor(float r, float g, float b, float a = 0)
	{
		glColor4f(r * 1.0 / 255, g * 1.0 / 255, b * 1.0 / 255, a);
	}
	void setColor(const Color& co) {
		glColor4f(co.r * 1.0 / 255, co.g * 1.0 / 255, co.b * 1.0 / 255, co.a);
	}
	void setWindowSize(int ww, int hh)
	{
		win_width = ww;
		win_height = hh;
		glutReshapeWindow(win_width, win_height);
	}
	void init() {
		glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
		glutInitWindowPosition(300, 100);
		glutInitWindowSize(win_width, win_height);
		glutCreateWindow("Weies's Drawing");
		glMatrixMode(GL_PROJECTION);
		glTranslated(-1, -1, 0);
		glViewport(0, 0, win_width, win_height);
		glutMotionFunc(doWhenMouseMove);
		glutReshapeFunc(reshape);
		glutMouseFunc(doWhenClick);
		glutDisplayFunc(doWhenDisplay);
	}

	void setTimer(int delay, function<void()> timefunc, int id)
	{
		timeDelay = delay;
		timerFunc = timefunc;
		glutTimerFunc(delay, doWhenTimeout, id);
	}
	void killTimer()
	{
		runing = false;
	}
	void killEvent()
	{
		eventAble = false;
	}
	void setSingleTimer(int delay, function<void(int id)> timefunc, int id)
	{
		singleTimerFunc = timefunc;
		glutTimerFunc(delay, doWhenSingleTimeout, id);
	}

	void eventloop()
	{
		glutMainLoop();
	}
	void setWindowTitle(char* c)
	{
		glutSetWindowTitle(c);
	}

	void setReshapeFunc(void func(int w, int h))
	{
		reshapeFunc = func;
		glutReshapeFunc(reshape);
	}

	void setMouseMove(void move(int x, int y))
	{
		mouseMoveHandler = move;
		glutMotionFunc(doWhenMouseMove);
	}
	void setMouseClick(void move(int b, int state, int x, int y))
	{
		mouseClickHandler = move;
		glutMouseFunc(doWhenClick);
	}
	void setMouseStick(void handler(int b, int state, int x, int y))
	{
		mouseStickHandler = handler;
	}
	void setMouseHover(void handler(int x, int y)) {
		mouseHoverHandler = handler;
	}

	void setKeyFunc(function<void(unsigned char key, int x, int y)> func)
	{
		keyFunc = func;
		glutKeyboardFunc(doWhenKeyDown);
		glutSpecialFunc(doWhenSpecialDown);
	}

	void setKeyUpFunc(function<void(unsigned char key, int x, int y)> func)
	{
		keyUpFunc = func;
		glutKeyboardUpFunc(doWhenKeyUp);
	}

	void setDisplayFunc(void draw())
	{
		displayFunc = draw;
		glutDisplayFunc(doWhenDisplay);
	}
	void update() {
		glFlush();
	}
	void drawLine(int xx, int yy, int ex, int ey);
	void drawRect(int xx, int yy, int ex, int ey);
	void drawCircle(int xx, int yy, int rr);

	void repaint()
	{
		clean();
		doWhenDisplay();
	}

	void setBGC(float r, float g, float b)
	{
		glClearColor(r * 1.0 / 255, g * 1.0 / 255, b * 1.0 / 255, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		backcolor = Color(r, g, b);
		glFlush();
	}

	void setBGC(const Color& co)
	{
		glClearColor(co.r * 1.0 / 255, co.g * 1.0 / 255, co.b * 1.0 / 255, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		backcolor = Color(co.r, co.g, co.b);
	}
	void useBGC()
	{
		setColor(backcolor);
	}
	void clean()
	{
		setBGC(backcolor);
	}
	void setScale(float s)
	{
		scaleTimes = s;
	}
	Color backcolor;
};
void Canvas::drawRect(int xx, int yy, int ex, int ey)
{
	glBegin(GL_LINE_STRIP);
	glPixel(xx, yy);
	glPixel(xx, ey);
	glPixel(ex, ey);
	glPixel(ex, yy);
	glPixel(xx, yy);
	glEnd();
}

void Canvas::drawLine(int xx, int yy, int ex, int ey)
{
	glBegin(GL_LINES);
	glPixel(xx, yy);
	glPixel(ex, ey);
	glEnd();
}

void Canvas:: drawCircle(int xx, int yy, int rr)
{
	float r = rr;
	float y = yy;
	float x = xx;
	int startpos = x - sqrt(2) / 2 * r;
	int endpos = x + sqrt(2) / 2 * r;
	int startposY = y - sqrt(2) / 2 * r;
	int endposY = y + sqrt(2) / 2 * r;
	glBegin(GL_POINTS);
	for (int i = startpos; i <= endpos; i++)
	{
		float py = sqrt(r * r - i * i + 2 * x * i - x * x);
		glPixel(i, round(py + y));
		glPixel(i, round(-py + y));
	}
	for (int i = startposY; i <= endposY; i++)
	{
		float px = sqrt(r * r - i * i + 2 * y * i - y * y);
		glPixel(round(px + x), i);
		glPixel(round(-px + x), i);
	}
	glEnd();
}
//画布，用来管理绘图
Canvas canvas(800, 600, Color(200, 200, 200));

void reshape(int w, int h)
{
	win_width = w;
	win_height = h;
	glViewport(0, 0, w, h);
	canvas.repaint();
	if (reshapeFunc)
		reshapeFunc(w, h);
}
