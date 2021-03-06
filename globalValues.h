#pragma once
#include<string>
#include<glut/glut.h>
#include<cmath>
#include<vector>
#include<map>
#include<algorithm>
#define WIN32_LEAN_AND_MEAN 
#include<windows.h>
using namespace std;

namespace globals {

	int Priority = 0;
	enum Pri {
		Highest = 154549847, Lowest = -145857587, Normal = 0
	};
	bool runing = true;
	double M_PI = 3.14159265358979323846;   // pi
	int win_w = 600;
	int win_h = 600;
	int pre_w = 600;
	int pre_h = 600;
	float scaleTimes = 1.0;
	int win_height()
	{
		return win_h/scaleTimes;
	}
	int win_width()
	{
		return win_w/scaleTimes;
	}

	int timeDelay = 0;
	bool eventAble = true;
	//设置鼠标移动时更新鼠标按下的x,y坐标
	int clickX = 0; int clickY = 0;
	//上一次viewport的位置
	int lastViewX = 0; int lastViewY = 0;
	//平移的位置
	float tX = -1.0; float tY = -1.0;
	bool useScale = true;
	int cOffsetx = 0;
	int cOffsety = 0;
	float transX(int x)
	{
		if (useScale)
			return x*2.0*scaleTimes/win_w;
		else return x*2.0/win_w;
	}

	float transY(int x)
	{
		if (useScale)
			return x*2.0*scaleTimes/win_h;
		else return x*2.0/win_h;
	}
	void glPixel(int x, int y)
	{
		glVertex2f(transX(x), transY(y));
	}
	string itos(int i)
	{
		char c[20];
		_itoa_s(i, c, 10, 10);
		return string(c);
	}
	void debug(string s)
	{
		OutputDebugStringA((s+"\n").c_str());
	}
	void debug(int s)
	{
		OutputDebugStringA((itos(s)+"\n").c_str());
	}

	void debugAll(const char* c, int l)
	{
		int j = 0; char cc[300] = {};
		for (int i = 0; i<l; i++)
		{
			if (c[i]!='\0')
			{
				cc[j++] = c[i];
			}
		}
		cc[j] = '\0';
		OutputDebugStringA(cc);
	}

	void drawString(int x, int y, string s)
	{
		glRasterPos2f(transX(x), transY(y));
		for (int i = 0; i<s.length(); i++)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
		}
		glFlush();
	}

	class Color {
	public:
		Color() {
			r = 0; g = 0; b = 0; a = 1;
		}
		Color(float rr, float gg, float bb) {
			r = rr; g = gg; b = bb; a = 1;
		}
		Color(float rr, float gg, float bb, float aa) {
			r = rr; g = gg; b = bb; a = 1; a = aa;
		}
		Color(const Color& c)
		{
			r = c.r; b = c.b;
			g = c.g; a = c.a;
		}

		Color(Color& c)
		{
			r = c.r; b = c.b;
			g = c.g; a = c.a;
		}
		void operator=(Color co)
		{
			r = co.r; b = co.b;
			g = co.g; a = co.a;
		}
		float r;
		float g;
		float b;
		float a = 1;
	};

	class BasicGraphObject {//基本图形对象,不可实例化
	public:
		Color co;//绘图的颜色
		bool movable = true;
		bool showing = true;
		int priority = 0;
		int defaultpri = 0;
		//每个图形对象都必须实现draw（）函数
		virtual void draw() = 0;
		virtual void show(bool show)
		{
			showing = show;
		}

		BasicGraphObject() :co(20, 125, 255) {

		}
		void setColor(float r, float g, float b)
		{
			co.r = r; co.g = g; co.b = b;
		}
		void setColor(float r, float g, float b, float alpha)
		{
			co.r = r; co.g = g; co.b = b; co.a = alpha;
		}
		void setColor(const Color& color)
		{
			co = color;
		}

	};

}
