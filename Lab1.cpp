//// ComputerGraphics.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
////
//#include"widget.h"
//#include"graphOBJ.h"
//using namespace std;
//
//extern Canvas canvas;
//Circle pie(400, 300, 100);
//Triangle tri(200, 200);
//LineOBJ line1(0, 0, win_width(), win_height());
//LineOBJ line2(0, win_height(), win_width(), 0);
//Circle center(400, 200, 50);
//Rect rect(600, 200, 100, 200);
//Button btn("stop");
//
//void rotating()
//{
//	tri.rotate(5);
//	pie.rotate(2);
//	center.rotate(2);
//	canvas.repaint();
//}
//
//int main(int argc, char* argv[])
//{
//
//	tri.setPriority(100);
//	int label = 0;
//	btn.onclick = [=, &label](int b, int s, int x, int y) {
//		if (label)
//		{
//			btn.str = "stop";
//			canvas.setTimer(20, rotating, 10);
//			label = 0;
//		}
//		else
//		{
//			btn.str = "start";
//			canvas.killTimer();
//			label = 1;
//		}
//		canvas.repaint();
//	};
//	canvas.setMouseStick([=](int b, int s, int c, int y) {
//		if (b == GLUT_LEFT)
//			scaleTimes *= 0.99;
//		else scaleTimes *= 1.01;
//		});
//	canvas.setMouseMove([=](int x, int y) {
//		glTranslated(deltaX / win_width() * 2, deltaY / win_height() * 2, 0);
//		canvas.repaint();
//		});
//	canvas.setBGC(200, 200, 200);
//	canvas.setTimer(20, rotating, 10);
//	center.rotate(180);
//	canvas.eventloop();
//	return 0;
//}
//
