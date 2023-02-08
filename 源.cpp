#define _CRT_SECURE_NO_WARNINGS 1 
#include<stdio.h>
#include<graphics.h>
#include<string.h>

#define WIN_WIDTH  800
#define WIN_HEIGTH  600

IMAGE imgMUYU[16];
int textX;
int textY;

void init()//初始化
{
	loadimage(&imgMUYU[0], "res/muy.jpg");
	int w = imgMUYU[0].getwidth();//获取图片宽度
	int h = imgMUYU[0].getheight();//获取图片高度
	//float k = 1;
	for (int i = 1; i < 8; i++)
	{
		//k -= 0.02;
		float k = 1 - 0.02 * i;//缩小图片
		loadimage(&imgMUYU[i], "res/muy.jpg", w * k, h * k, true);

	}
	for (int i = 8; i < 16; i++)
	{
		//k = +0.02;
		float k = 0.86 + (i - 8) * 0.02;//放大图片
		loadimage(&imgMUYU[i], "res/muy.jpg", w * k, h * k, true);
	}
	initgraph(WIN_WIDTH, WIN_HEIGTH);//创建窗口
	//设置字体
	LOGFONT f;
	gettextstyle(&f);//获取当前字体
	f.lfHeight = 40;//设置字体位置
	f.lfWidth = 0;
	strcpy(f.lfFaceName, "微软雅黑");//设置字体样式
	f.lfQuality = ANTIALIASED_QUALITY;//让字体看上去更平滑
	setbkmode(TRANSPARENT);//字体的背景变为透明效果
	settextstyle(&f);

}
void updateWindow()
{
	BeginBatchDraw();//开始绘制，但并不直接输出到窗口，而是放到显出里
	//刷新画面
	int centX = WIN_WIDTH / 2;
	int centY = WIN_HEIGTH / 2 + 100;
	int tmeY = textY;

	int color = 0xFFFFFF;

	for (int i = 0; i < 16; i++)
	{
		//先擦除窗口
		setbkcolor(BLACK);
		cleardevice();//使用当前窗口颜色填充整个背景
		int x = centX - imgMUYU[i].getwidth() / 2;
		int y = centY - imgMUYU[i].getheight() / 2;

		putimage(x, y,&imgMUYU[i]);
		
		//设置文字颜色
		settextcolor(color);
		color = color - 0x111111;//颜色变淡
		outtextxy(textX,tmeY,"功德+1");

		tmeY = tmeY - 10;
		EndBatchDraw();
		
		Sleep(5);

	}
}

bool keyEvent()//鼠标的控制
{
	ExMessage msg;
	if (peekmessage(&msg) && msg.message == WM_LBUTTONDOWN)
	{
		textX = msg.x;//获取鼠标点击位置
		textY = msg.y;
		return true;
	}
	return false;
}

/*void setziti()
{
	LOGFONT f;
	gettextstyle(&f);//获取当前字体
	f.lfHeight = 40;//设置字体位置
	f.lfWidth = 0;
	strcpy(f.lfFaceName, "微软雅黑");//设置字体样式
	f.lfQuality = ANTIALIASED_QUALITY;//让字体看上去更平滑
	setbkmode(TRANSPARENT);//字体的背景变为透明效果
	settextstyle(&f);
}*/

int main()
{
	init();
	//setziti();

	int x = WIN_WIDTH / 2 - imgMUYU[0].getwidth() / 2;
	int y = WIN_HEIGTH / 2 - imgMUYU[0].getheight() / 2 + 100;

	putimage(x,y,&imgMUYU[0]);
	while (1)
	{
		if (keyEvent())
		{
		updateWindow();
		}
	}
	return 0;
}