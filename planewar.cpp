#include"widget.h"
#include"graphOBJ.h"

Enemy enemy;
Plane plane;
int score = 0;
int toret = 0;

void display()
{
	canvas.setColor(0, 0, 255);
	toret++;
	if (toret > 20)
	{
		plane.setColor(25, 120, 255);
	}
	for (int i = 0; i < mybullet.size(); i++)
	{
		fillRect(mybullet[i].x, mybullet[i].y, 8, 8);
		if (enemy.area.inArea(mybullet[i].x, mybullet[i].y))
		{
			enemy.HP -= 10;
			score += 8;
			if (enemy.HP < 0)
			{
				enemy.HP = 1000;
				enemy.moveto(rand() % win_width + 50, rand() % (win_height - 300) + 300);
			}
		}
	}

	for (int i = 0; i < hisbullet.size(); i++)
	{
		canvas.setColor(0, 255, 255);
		fillRect(hisbullet[i].X(), hisbullet[i].Y(), 8, 8);
		if (plane.area.inArea(hisbullet[i].x, hisbullet[i].y))
		{
			plane.HP -= 100;
			plane.setColor(255, 0, 2);
			toret = 0;
			if (plane.HP < 0)
			{
				canvas.killTimer();
				canvas.setBGC(255, 0, 0);
				canvas.setColor(255, 255, 255);
				fillRect(200, 250, 220, 100);
				canvas.setColor(0, 255, 0);
				drawString(255, 310, "you died");
				drawString(215, 270, "you got " + itos(score) + " score");
				canvas.killEvent();
				plane.onmove = 0;
			}
		}
	}
}

int toshot = 0;
void timer()
{
	++toshot;
	if (toshot % 2 == 0)
	{
		hisbullet.push_back(bullets(enemy.posx - 3, enemy.posy - 58));
	}

	for (int i = 0; i < mybullet.size(); i++)
	{
		mybullet[i].y += 10;
		//hisbullet[i].y -= 10;
	}
	if (toshot > 8)
	{
		toshot = 0;

		mybullet.push_back(point(plane.posx - 3, plane.posy + 55));
	}

	canvas.repaint();
}

int main()
{
	enemy.moveto(400, 500);
	Button btn("Start");
	btn.moveto(500, 10);
	bool start = false;

	btn.onclick = [=, &start](int b, int s, int x, int y)
	{
		if (!start)
		{
			canvas.setTimer(20, timer, 10);
			start = true;
			mouseHoverHandler = [=](int x, int y) {
				plane.moveto(x, y);
			};
		}
	};
	btn.setMovable(false);

	canvas.setWindowSize(600, 600);
	canvas.setDisplayFunc(display);
	canvas.setBGC(230, 230, 230);
	canvas.eventloop();
}