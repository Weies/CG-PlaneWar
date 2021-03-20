#pragma once
#include"globalValues.h"
#include<functional>
using namespace std;
using namespace globals;

namespace events {
	bool cmp(BasicGraphObject* a1, BasicGraphObject* a2)
	{
		if (a1->priority < a2->priority)
			return true;
		return false;
	}
	class DisplayManager {
	public:

		void push(BasicGraphObject* obj)
		{
			++Size;
			list.push_back(obj);
			sort(list.begin(), list.end(), cmp);
		}

		void erase(BasicGraphObject* obj)
		{
			//list.erase(obj);
		}
		void resort()
		{
			sort(list.begin(), list.end(), cmp);
		}
		auto begin()
		{
			return list.begin();
		}
		auto end()
		{
			return list.end();
		}
		int size() {
			return Size;
		}
		int Size = 0;

		vector<BasicGraphObject*> list;
	};

	DisplayManager displayList;

	function<void(int b, int state, int x, int y)> mouseClickHandler = 0;
	function<void(int x, int y)> mouseMoveHandler = 0;
	function<void(int b, int state, int x, int y)> mouseStickHandler;

	function<void(int x, int y)>  reshapeFunc = 0;

	function<void(unsigned char key, int x, int y)> keyFunc = 0;
	function<void(unsigned char key, int x, int y)>  keyUpFunc = 0;

	function<void(int x, int y)>  arrangeMoveFunc = 0;
	function<void(int b, int state, int x, int y)> arrangeClickFunc = 0;
	function<void(int b, int state, int x, int y)> arrangeStickFunc = 0;
	function<void(int b, int x, int y)> arrangeMouseUpFunc = 0;
	function<void()> timerFunc = 0;
	function<void(int id)> singleTimerFunc = 0;

	void (*displayFunc)() = 0;
	bool sticking = false; bool mouseMoved = false;
	int mouseX = 0; int mouseY = 0; int mBtn = 0; int mState = 0;
	float deltaX = 0; float deltaY = 0;

	void doWhenDisplay()
	{
		if (eventAble)
		{
			for (int i = 0; i < displayList.Size; i++)
			{
				if (displayList.list[i]->showing)
					displayList.list[i]->draw();
			}
			if (displayFunc)
				displayFunc();
			glFlush();
		}
	}

	void doWhenMouseMove(int x, int y)
	{
		if (eventAble)
		{
			deltaX = x - mouseX; deltaY = win_height - y - mouseY;
			mouseX = x; mouseY = win_height - y;
			mouseMoved = true;
			if (arrangeMoveFunc)
				arrangeMoveFunc(x, mouseY);
			if (mouseMoveHandler)
			{
				mouseMoveHandler(x, mouseY);
			}
		}
	}

	void doWhenMouseStick(int id)
	{
		if (eventAble) {
			if (sticking && !mouseMoved) {
				arrangeStickFunc(mBtn, mState, mouseX, mouseY);
				if (mouseStickHandler)mouseStickHandler(mBtn, mState, mouseX, mouseY);
				glutTimerFunc(10, doWhenMouseStick, 5566);
			}
		}

	}

	void doWhenClick(int b, int state, int x, int y)
	{
		if (eventAble) {
			if (state == GLUT_UP) {
				sticking = false;
				lastViewX = x - clickX + lastViewX;
				lastViewY = win_height - y - clickY + lastViewY;
				arrangeMouseUpFunc(b, x, win_height - y);
			}
			else
			{
				sticking = true;
				mouseMoved = false;
				mBtn = b; mState = state;
				clickX = x; clickY = win_height - y;
				mouseX = x; mouseY = win_height - y;
				arrangeClickFunc(b, state, x, mouseY);
				if (mouseClickHandler)
					mouseClickHandler(b, state, clickX, clickY);
				glutTimerFunc(400, doWhenMouseStick, 5566);
			}
		}

	}

	void doWhenKeyDown(unsigned char key, int x, int y)
	{
		if (eventAble) {
			if (keyFunc)
				keyFunc(key, x, y);
		}

	}
	void doWhenSpecialDown(int key, int x, int y)
	{
		if (eventAble) {
			if (keyFunc)
				keyFunc(key, x, y);
		}

	}
	void doWhenKeyUp(unsigned char key, int x, int y)
	{

		if (eventAble) {
			if (keyUpFunc)
				keyUpFunc(key, x, y);
		}

	}

	void doWhenTimeout(int id)
	{
		if (eventAble) {
			if (timerFunc && runing)
			{
				timerFunc();
				glutTimerFunc(timeDelay, doWhenTimeout, id);
			}
		}

	}

	void doWhenSingleTimeout(int id)
	{
		if (eventAble) {
			if (singleTimerFunc)
				singleTimerFunc(1);
		}

	}
}
