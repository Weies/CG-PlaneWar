//#include"graphBasic.h"
//#include"widget.h"
//
//void DDA(float k, float b);
//void bresenham(float k, float b);
//void drawCir(int x, int y, int r);
//
//void drawGrid(int width)
//{
//	canvas.setColor(250, 250, 250);
//	glBegin(GL_LINES);
//	int lines = win_width / width * 100;
//	for (int i = -lines; i <= lines; i++)
//	{
//		glPixel(i * 30 + 1, -win_height / scaleTimes);
//		glPixel(i * 30 + 1, 2 * win_height / scaleTimes);
//	}
//	for (int i = -lines; i <= lines; i++)
//	{
//		glPixel(-win_height / scaleTimes, i * 30);
//		glPixel(2 * win_width / scaleTimes, i * 30);
//	}
//	glEnd();
//}
//
//int x = 0; int y = 0;
//float rety = 0;
//float retx;
//void DDA(float k, float b)
//{
//	rety = 0; x = 0; y = 0; retx = 0;
//	canvas.setColor(255, 100, 100);
//	if (abs(k) <= 1)
//	{
//		int total = 600 / scaleTimes;
//		for (int i = -total; i < total; i++)
//		{
//			if (y < rety)y++;
//			rety += k;
//			fillRect(round(x++), round(y), b);
//		}
//	}
//	else {
//		int total = 600 / scaleTimes;
//		for (int i = -total; i < total; i++)
//		{
//			if (x < retx)x++;
//			retx += 1 / k;
//			fillRect(round(x), round(y++), b);
//		}
//	}
//}
//
//void bresenham(float k, float b)
//{
//	rety = 0; x = 0; y = 0;
//	canvas.setColor(255, 100, 100);
//	int total = 600 / scaleTimes;
//	if (abs(k) < 1)
//	{
//		float p = 2 * k - 1;
//		float pp = 2 * k;
//		for (int i = -total; i < total; i++)
//		{
//			if (p < 0)
//			{
//				p += pp;
//				fillRect(x++, y, b);
//			}
//			else
//			{
//				p += pp - 2.0;
//				fillRect(x++, ++y, b);
//			}
//		}
//	}
//	else {
//		float p = 2 /k - 1;
//		float pp = 2 / k;
//		for (int i = -total; i < total; i++)
//		{
//			if (p < 0)
//			{
//				p += pp;
//				fillRect(x, y++, b);
//			}
//			else
//			{
//				p += pp - 2.0;
//				fillRect(x++, y++, b);
//			}
//		}
//	}
//
//}
//
//void drawCir(int xx, int yy, int rr)
//{
//	canvas.setColor(0, 255, 2);
//	float r = rr / 30;
//	float y = yy / 30;
//	float x = xx / 30;
//	int startpos = x - sqrt(2) / 2 * r;
//	int endpos = x + sqrt(2) / 2 * r;
//	int startposY = y - sqrt(2) / 2 * r;
//	int endposY = y + sqrt(2) / 2 * r;
//	for (int i = startpos; i <= endpos; i++)
//	{
//		float py = sqrt(r * r - i * i + 2 * x * i - x * x);
//		fillRect(i, round(py + y), 0);
//		fillRect(i, round(-py + y), 0);
//	}
//	for (int i = startposY; i <= endposY; i++)
//	{
//		float px = sqrt(r * r - i * i + 2 * y * i - y * y);
//		fillRect(round(px + x), i, 0);
//		fillRect(round(-px + x), i, 0);
//	}
//}
//
//void draw()
//{
//	DDA(2, 0);
//	bresenham(0.5, 0);
//	drawGrid(30);
//	canvas.setColor(255, 0, 0);
//	drawCir(1000, 1000, 1000);
//}
//
//void stickHandler(int b, int state, int xx, int yy)
//{
//	if (scaleTimes > 0.001 && b == GLUT_LEFT_BUTTON && state == GLUT_DOWN)scaleTimes *= 0.98;
//	else if (scaleTimes < 100 && b == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)scaleTimes /= 0.98;
//	canvas.repaint();
//}
//
//void mouseMove(int x, int y)
//{
//	//glViewport(x-clickX+lastViewX,y-clickY+lastViewY,win_width,win_height);
//	glTranslated(deltaX / win_width * 2, deltaY / win_height * 2, 0);
//	canvas.repaint();
//}
//
//int main(int ac, char** av)
//{
//	Button btn("Big");
//	btn.moveto(500, 400);
//	Button btn2("Small");
//	btn2.moveto(500, 450);
//	btn2.resize(80, 40);
//	btn.resize(80, 40);
//	btn.onclick = [=,&btn](int b,int s,int x,int y) {
//		for (int i = 0; i < 500; i++)
//		{
//			scaleTimes *= 1.001;
//			canvas.repaint();
//		}
//	};
//	btn2.onclick = [=, &btn](int b,int s,int x, int y) {
//		for (int i = 0; i < 500; i++)
//		{
//			scaleTimes *= 0.999;
//			canvas.repaint();
//		}
//	};
//	canvas.setWindowSize(600, 600);
//	canvas.setBGC(200, 200, 200);
//	canvas.setDisplayFunc(draw);
//	canvas.setMouseMove(mouseMove);
//	canvas.setMouseStick(stickHandler);
//	canvas.eventloop();
//}