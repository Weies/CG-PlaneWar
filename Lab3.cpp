//#include"widget.h"
//#include"graphOBJ.h"
//#include<time.h>
//#include<vector>
//Tailor win(400, 300);
//vector<state> list(100);
//void display()
//{
//	glBlendFunc(GL_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	canvas.setColor(25, 125, 255,1);
//	for (int i = 0; i < lines.size(); i++)
//	{
//		ptr.drawLine(lines[i].p1.x, lines[i].p1.y,
//			lines[i].p2.x,lines[i].p2.y);
//	}
//}
//void reshape(int x, int y)
//{
//	lines.resize(0);
//	for (int i = 0; i < 15; i++)
//	{
//		lines.push_back(Line(0, rand() % win_height(), win_width(), rand() % win_height()));
//		lines.push_back(Line(rand() % win_width(), 0, rand() % win_width(), win_height()));
//	}
//}
//int cur = 0;
//int frame = 0;
//int main()
//{
//	glEnable(GL_BLEND);
//	srand(time(0));
//	win.setColor(255,255,255,0.8);
//	lines.push_back(Line(100,0,100,600));
//	for (int i = 0; i < 15; i++)
//	{
//		lines.push_back(Line(0, rand() % win_height(), win_width(), rand() % win_height()));
//		lines.push_back(Line(rand() % win_width(), 0, rand() % win_width(), win_height()));
//	}
//	canvas.setTimer(1, []() {
//		if (frame < 80)
//		{
//			win.gotoState(list[cur]);
//			frame++;
//		}
//		else cur=(cur+1)%100,frame=0;
//	}, 10);
//
//	canvas.setReshapeFunc(reshape);
//	canvas.setDisplayFunc(display);
//	canvas.eventloop();
//}