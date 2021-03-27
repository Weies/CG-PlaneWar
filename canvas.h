#pragma once
#include"events.h"
using namespace events;

void _reshape(int w, int h);

class Canvas {
public:
	Canvas(int ww, int hh, const Color& co = Color(255, 255, 255)) :backcolor(co) {
		win_w = ww;
		win_h = hh;
		init();
		setHook(); 
	}

	void setColor(float r, float g, float b, float a = 1)
	{
		co = Color(r, g, b, a);
		glColor4f(r * 1.0 / 255, g * 1.0 / 255, b * 1.0 / 255, a);
	}
	void setColor(const Color& c) {
		co = c;
		glColor4f(co.r * 1.0 / 255, co.g * 1.0 / 255, co.b * 1.0 / 255, co.a);
	}
	void setWindowSize(int ww, int hh)
	{
		win_w = ww;
		win_h = hh;
		glutReshapeWindow(win_w, win_h);
	}
	void init() {
		glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);
		glutInitWindowPosition(300, 100);
		glutInitWindowSize(win_w, win_h);
		glutCreateWindow("Weies's Drawing");
		glMatrixMode(GL_PROJECTION);
		glTranslated(-1, -1, 0);
		glViewport(0, 0, win_w, win_h);
		glutMotionFunc(doWhenMouseMove);
		glutReshapeFunc(_reshape);
		glutMouseFunc(doWhenClick);
		glutDisplayFunc(doWhenDisplay);
	}

	void setTimer(int delay, function<void()> timefunc, int id=0)
	{
		timeDelay = delay;
		timerFunc = timefunc;
		runing = true;
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
	void setSingleTimer(int delay, function<void(int id)> timefunc, int id=0)
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
		glutReshapeFunc(_reshape);
	}

	void setMouseMove(function<void(int x, int y)>move)
	{
		mouseMoveHandler = move;
		glutMotionFunc(doWhenMouseMove);
	}
	void setMouseClick(function<void(int b, int state, int x, int y)>move)
	{
		mouseClickHandler = move;
		glutMouseFunc(doWhenClick);
	}
	void setMouseStick(function<void(int b, int state, int x, int y)>handler)
	{
		mouseStickHandler = handler;
	}
	void setMouseHover(function<void(int x, int y)>handler) {
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
	Color co;
	Color backcolor;
};

//画布，用来管理绘图
Canvas canvas(800, 600, Color(200, 200, 200));

void _reshape(int w, int h)
{
	pre_w = win_w;
	pre_h = win_h;
	win_w = w;
	win_h = h;
	glViewport(0, 0, w, h);
	if (reshapeFunc)
		reshapeFunc(w, h);
	canvas.repaint();
}
