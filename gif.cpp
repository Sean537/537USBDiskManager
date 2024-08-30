/*
537 USB Disk Manager
Version 1.0 Beta

gif.cpp

Copyright (C) 537 Studio. 2024. All rights reserved.
*/
#include "include/graphics.h"
#include <stdio.h>
#include "include/gif.h"

//���캯��
Gif::Gif(const WCHAR* gifFileName, HDC hdc)
{
	init();
	if (gifFileName != NULL)
		load(gifFileName);
	bind(hdc);
}

//���ƹ��캯��
Gif::Gif(const Gif& gif)
{
	copy(gif);
}

//��������
Gif::~Gif()
{
	delete gifImage;
	delete pItem;
	delete graphics;
}

//��ֵ����������
Gif & Gif::operator=(const Gif & gif)
{
	if (this == &gif)		return *this;
	if (graphics != NULL)	delete graphics;
	if (pItem != NULL)		delete pItem;
	if (gifImage != NULL)	delete gifImage;

	copy(gif);

	return *this;
}

//��ʼ��
void Gif::init()
{
	x = y = 0;
	width = height = 0;
	hdc = 0;
	gifImage = NULL;
	graphics = NULL;
	pItem = NULL;
	visible = true;

	resetPlayState();
}

//����ͼ��
void Gif::load(const WCHAR * gifFileName)
{
	if (gifImage != NULL)
		delete gifImage;
	gifImage = new Gdiplus::Bitmap(gifFileName);

	read();
}

//�󶨻���Ŀ��HDC
void Gif::bind(HDC hdc)
{
	this->hdc = hdc;
	if (graphics != NULL)
		delete graphics;
	graphics = Gdiplus::Graphics::FromHDC(hdc);
}

//�󶨻���Ŀ�굽����
void Gif::bindWindow()
{
	if (hdc != getHDC())
		bind(getHDC());
}

//������ص�ͼ��
void Gif::clear()
{
	if (gifImage) {
		delete gifImage;
		gifImage = NULL;
	}

	if (pItem) {
		delete pItem;
		pItem = NULL;
	}
	frameCount = 0;
}

//��ȡͼ��ԭ����
int Gif::getOrginWidth() const
{
	if (!gifImage)
		return 0;
	return gifImage->GetWidth();
}

//��ȡͼ��ԭ����
int Gif::getOrginHeight() const
{
	if (!gifImage)
		return 0;
	return gifImage->GetHeight();
}

void Gif::setPos(int x, int y)
{
	this->x = x;
	this->y = y;
}

//����ͼ���С
void Gif::setSize(int width, int height)
{
	this->width = width;
	this->height = height;
}

//�ڵ�ǰλ�û��Ƶ�ǰ֡
void Gif::draw()
{
	draw(x, y);
}

//��ָ��λ�û��Ƶ�ǰ֡
void Gif::draw(int x, int y)
{
	updateTime();
	drawFrame(curFrame, x, y);
}

//�ڵ�ǰλ�û���ָ��֡
void Gif::drawFrame(int frame)
{
	drawFrame(frame, x, y);
}

//��ָ��λ�û���ָ��֡
void Gif::drawFrame(int frame, int x, int y)
{
	if (!visible)
		return;
	int w = width, h = height;
	if (w == 0 && h == 0) {
		w = gifImage->GetWidth();
		h = gifImage->GetHeight();
	}
	if (frameCount != 0 && gifImage && 0 <= frame) {
		frame %= frameCount;
		gifImage->SelectActiveFrame(&Gdiplus::FrameDimensionTime, frame);
		graphics->DrawImage(gifImage, x, y, w, h);
	}
}

//��ȡGif��ָ��֡�������浽pimg��
void Gif::getimage(PIMAGE pimg, int frame)
{
	if (frame < 0 || frameCount <= frame)
		return;

	int width = gifImage->GetWidth(), height = gifImage->GetHeight();

	if (width != getwidth(pimg) || height != getheight(pimg))
		resize(pimg, width, height);

	//�Զ���ͼ�񻺴���(ARGB��
	Gdiplus::BitmapData bitmapData;
	bitmapData.Stride = width * 4;
	int buffSize = width * height * sizeof(color_t);
	bitmapData.Scan0 = getbuffer(pimg);

	gifImage->SelectActiveFrame(&Gdiplus::FrameDimensionTime, frame);
	Gdiplus::Rect rect(0, 0, width, height);
	//��32λ����ARGB��ʽ��ȡ�� �Զ��建����

	gifImage->LockBits(&rect,
		Gdiplus::ImageLockModeRead | Gdiplus::ImageLockModeUserInputBuf, PixelFormat32bppARGB, &bitmapData);
	gifImage->UnlockBits(&bitmapData);
}

//��ȡָ��֡����ʱʱ��
int Gif::getDelayTime(int frame) const
{
	if (frame < 0 || frameCount <= frame ||
		!pItem || pItem->length <= (unsigned int)frame)
		return 0;
	else
		return ((long*)pItem->value)[frame] * 10;
}

//����ָ��֡����ʱʱ��
void Gif::setDelayTime(int frame, long time_ms)
{
	if (frame < 0 || frameCount <= frame ||
		!pItem || pItem->length <= (unsigned int)frame)
		return;
	else
		((long*)pItem->value)[frame] = time_ms / 10;
}

//ͳһ��������֡����ʱʱ��
void Gif::setAllDelayTime(long time_ms)
{
	for (int i = 0; i < frameCount; i++)
		((long*)pItem->value)[i] = time_ms / 10;
}

//����
void Gif::play()
{
	playing = true;
	clock_t sysTime = clock();
	if (frameBaseTime == 0) {
		pauseTime = frameBaseTime = sysTime;
		curFrame = 0;
		frameDelayTime = getDelayTime(curFrame);
	}
	else
		frameBaseTime += sysTime - pauseTime;
}

//��ͣ
void Gif::pause()
{
	if (playing) {
		playing = false;
		this->pauseTime = clock();
	}
}

//������ͣ�л�
void Gif::toggle()
{
	playing ? pause() : play();
}

//���ò���״̬
void Gif::resetPlayState()
{
	curFrame = 0;
	curDelayTime = frameBaseTime = frameDelayTime = 0;
	pauseTime = 0;
	playing = false;
}

//����̨��ʾGif��Ϣ
void Gif::info() const
{
	printf("Gif Paint Size: %d x %d\n", getWidth(), getHeight());
	printf("Gif Normal Size: %d x %d\n", getOrginWidth(), getOrginHeight());
	int frameCnt = getFrameCount();
	printf("FPS: %d\n", getFrameCount());
	/*
	printf("The delay time of the frame:\n");
	
	for (int i = 0; i < frameCnt; i++)
		printf("Frame%3d:%4d ms\n", i, getDelayTime(i));
	*/
}

//��ȡͼ��
void Gif::read()
{
	/*��ȡͼ����Ϣ*/
	UINT count = gifImage->GetFrameDimensionsCount();
	GUID* pDimensionIDs = (GUID*)new GUID[count];
	gifImage->GetFrameDimensionsList(pDimensionIDs, count);
	//֡��
	frameCount = gifImage->GetFrameCount(&pDimensionIDs[0]);
	delete[] pDimensionIDs;

	if (pItem != NULL)
		delete pItem;

	//��ȡÿ֡����ʱ����
	int size = gifImage->GetPropertyItemSize(PropertyTagFrameDelay);
	pItem = (Gdiplus::PropertyItem*)malloc(size);
	gifImage->GetPropertyItem(PropertyTagFrameDelay, size, pItem);
}

//Gif����
void Gif::copy(const Gif& gif)
{
	hdc = gif.hdc;
	x = gif.x;
	y = gif.y;
	width = gif.width;
	height = gif.height;
	curFrame = gif.curFrame;
	pauseTime = gif.pauseTime;

	frameBaseTime = gif.frameBaseTime;
	curDelayTime = gif.curDelayTime;
	frameDelayTime = gif.frameDelayTime;

	frameCount = gif.frameCount;
	graphics = new Gdiplus::Graphics(hdc);
	gifImage = gif.gifImage->Clone(0, 0, gif.getWidth(), gif.getHeight(), gif.gifImage->GetPixelFormat());

	int size = gif.gifImage->GetPropertyItemSize(PropertyTagFrameDelay);
	pItem = (Gdiplus::PropertyItem*)malloc(size);
	memcpy(pItem, gif.pItem, size);
}

//Gifʱ����£����㵱ǰ֡
void Gif::updateTime()
{
	//ͼ��Ϊ�գ����߲��Ƕ�ͼ������û�е��ù�play()���ţ���
	if (frameCount <= 1 || frameBaseTime == 0
		|| (pItem && pItem->length == 0))
		return;

	//���ݲ��Ż���ͣ����֡����ʱ��
	curDelayTime = playing ? (clock() - frameBaseTime) : (pauseTime - frameBaseTime);

	int cnt = 0, totalTime = 0;

	//���ʱ��̫�����ܻ�������֡
	while (curDelayTime >= frameDelayTime) {
		curDelayTime -= frameDelayTime;
		frameBaseTime += frameDelayTime;

		//�л�����һ֡
		if (++curFrame >= frameCount)
			curFrame = 0;
		frameDelayTime = getDelayTime(curFrame);

		totalTime += frameDelayTime;

		//��֡ͼ�񣬵�����ʱʱ��Ϊ0�Ĵ���
		if (++cnt == frameCount && totalTime == 0)
			break;
	}
}
