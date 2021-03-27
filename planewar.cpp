#pragma once
#include"widget.h"
#include"graphOBJ.h"
#include"painter.h"
#include<time.h>
#include"network.h"
Enemy enemy;
Plane plane;
int score = 0;
int toret = 0;
int tox = 0; int toy = 0;
int toshot = 0;
int lx; int ly;
Socket sock(getIP("welinn.com"), 12345);
float deltax;
float deltay;

void display()
{
	canvas.setColor(0, 0, 255);
	toret++;
	if (toret>15)
	{
		plane.setColor(25, 120, 255);
	}
	for (int i = 0; i<mybullet.size(); i++)
	{
		painter.fillCircle(mybullet[i].x, mybullet[i].y += 10, 4);
		if (enemy.area.inArea(mybullet[i].x, mybullet[i].y))
		{
			enemy.HP -= 3;
			score += 8;
			if (enemy.HP<0)
			{
				score += 100;
				enemy.HP = 1000;
			}
		}
	}
	canvas.setColor(255, 25, 125);
	for (int i = 0; i<hisbullet.size(); i++)
	{
		painter.fillCircle(hisbullet[i].X(), hisbullet[i].Y(), 4);
		if (plane.area.inArea(hisbullet[i].x, hisbullet[i].y))
		{
			plane.HP -= 0;
			plane.setColor(255, 0, 2);
			toret = 0;
			if (plane.HP<0)
			{
				canvas.killTimer();
				canvas.setBGC(255, 0, 0);
				canvas.setColor(255, 255, 255);
				painter.fillRect(200, 250, 220, 100);
				canvas.setColor(0, 255, 0);
				drawString(255, 310, "you died");
				drawString(215, 270, "you got "+itos(score)+" score");
				canvas.killEvent();
				plane.onmove = 0;
			}
		}
	}
}

bool selfpd = false;
bool himpd = false;

void timer()
{
	++toshot;
	enemy.moveto(enemy.posx+deltax, enemy.posy+deltay);
	if (toshot%8==0)
	{
		hisbullet.push_back(bullets(enemy.posx-3, enemy.posy-58));
		sock.send('*'+itos(win_width()-plane.posx)+"**"+itos(win_height()-plane.posy)+"*\n");
	}
	if (toshot>16)
	{
		toshot = 0;
		mybullet.push_back(point(plane.posx-3, plane.posy+55));
		mybullet.push_back(point(plane.posx-30, plane.posy+55));
		mybullet.push_back(point(plane.posx+24, plane.posy+55));
	}
	canvas.repaint();
}
bool start = false;
int main()
{
	Button btn("Prepare");
	sock.connect();
	hander = [=,&btn]() {
		string s = sock.msg.front();
		if (s[0]=='*')
		{
			tox = atoi(s.c_str()+s.find('*')+1);
			toy = atoi(s.c_str()+s.find("**")+2);
			deltax = (tox-enemy.posx)*0.13;
			deltay = (toy-enemy.posy)*0.13;
			if (!start)
			{
				btn.setText("Playing");
				canvas.setTimer(10, timer);
				start = true;
			}
		}
		else if (s[0]=='%')
		{
			himpd = true;
			btn.setText("Opposite prepared");
		}
		sock.msg.pop();
	};

	srand(time(0));
	enemy.moveto(400, 500);
	btn.moveto(400, 10);
	//canvas.setMouseStick([=](int b, int x, int y, int z) {
	//	if (b==GLUT_LEFT_BUTTON&&scaleTimes<10)
	//		scaleTimes *= 1.05;
	//	else if (b==GLUT_RIGHT_BUTTON&&scaleTimes>0.1)
	//		scaleTimes *= 0.95;
	//	canvas.repaint();
	//});
	scaleTimes = 0.5;
	mouseHoverHandler = [=](int x, int y) {
		if(start)
		plane.moveto(x/scaleTimes, y/scaleTimes);
	};
	btn.onclick = [=, &btn](int b, int s, int x, int y)
	{
		if (!start)
		{
			btn.setText("Prepared,waiting");
			selfpd = true;
			sock.send("%prepared\n");
			if (himpd)
			{
				canvas.setTimer(10, timer, 10);
				start = true;
				btn.setText("Playing");
			}
		}
	};
	btn.setMovable(false);

	canvas.setWindowSize(600, 600);
	canvas.setDisplayFunc(display);
	canvas.setBGC(230, 230, 230);
	canvas.eventloop();
}