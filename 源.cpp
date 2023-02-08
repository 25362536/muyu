#define _CRT_SECURE_NO_WARNINGS 1 
#include<stdio.h>
#include<graphics.h>
#include<string.h>

#define WIN_WIDTH  800
#define WIN_HEIGTH  600

IMAGE imgMUYU[16];
int textX;
int textY;

void init()//��ʼ��
{
	loadimage(&imgMUYU[0], "res/muy.jpg");
	int w = imgMUYU[0].getwidth();//��ȡͼƬ���
	int h = imgMUYU[0].getheight();//��ȡͼƬ�߶�
	//float k = 1;
	for (int i = 1; i < 8; i++)
	{
		//k -= 0.02;
		float k = 1 - 0.02 * i;//��СͼƬ
		loadimage(&imgMUYU[i], "res/muy.jpg", w * k, h * k, true);

	}
	for (int i = 8; i < 16; i++)
	{
		//k = +0.02;
		float k = 0.86 + (i - 8) * 0.02;//�Ŵ�ͼƬ
		loadimage(&imgMUYU[i], "res/muy.jpg", w * k, h * k, true);
	}
	initgraph(WIN_WIDTH, WIN_HEIGTH);//��������
	//��������
	LOGFONT f;
	gettextstyle(&f);//��ȡ��ǰ����
	f.lfHeight = 40;//��������λ��
	f.lfWidth = 0;
	strcpy(f.lfFaceName, "΢���ź�");//����������ʽ
	f.lfQuality = ANTIALIASED_QUALITY;//�����忴��ȥ��ƽ��
	setbkmode(TRANSPARENT);//����ı�����Ϊ͸��Ч��
	settextstyle(&f);

}
void updateWindow()
{
	BeginBatchDraw();//��ʼ���ƣ�������ֱ����������ڣ����Ƿŵ��Գ���
	//ˢ�»���
	int centX = WIN_WIDTH / 2;
	int centY = WIN_HEIGTH / 2 + 100;
	int tmeY = textY;

	int color = 0xFFFFFF;

	for (int i = 0; i < 16; i++)
	{
		//�Ȳ�������
		setbkcolor(BLACK);
		cleardevice();//ʹ�õ�ǰ������ɫ�����������
		int x = centX - imgMUYU[i].getwidth() / 2;
		int y = centY - imgMUYU[i].getheight() / 2;

		putimage(x, y,&imgMUYU[i]);
		
		//����������ɫ
		settextcolor(color);
		color = color - 0x111111;//��ɫ�䵭
		outtextxy(textX,tmeY,"����+1");

		tmeY = tmeY - 10;
		EndBatchDraw();
		
		Sleep(5);

	}
}

bool keyEvent()//���Ŀ���
{
	ExMessage msg;
	if (peekmessage(&msg) && msg.message == WM_LBUTTONDOWN)
	{
		textX = msg.x;//��ȡ�����λ��
		textY = msg.y;
		return true;
	}
	return false;
}

/*void setziti()
{
	LOGFONT f;
	gettextstyle(&f);//��ȡ��ǰ����
	f.lfHeight = 40;//��������λ��
	f.lfWidth = 0;
	strcpy(f.lfFaceName, "΢���ź�");//����������ʽ
	f.lfQuality = ANTIALIASED_QUALITY;//�����忴��ȥ��ƽ��
	setbkmode(TRANSPARENT);//����ı�����Ϊ͸��Ч��
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