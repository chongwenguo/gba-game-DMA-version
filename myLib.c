#include "myLib.h"


u16 *videoBuffer = (u16 *)0x6000000;

void setPixel(int r, int c, u16 color)
{
	videoBuffer[OFFSET(r, c, 240)] = color;
}

void drawRect(int x, int y, int width, int height, u16 color)
{
	int x1,y1;
	for(x1=0; x1<height; x1++)
	{
		for(y1=0; y1<width; y1++)
		{
			setPixel(x+x1, y+y1, color);
		}
	}
}	

void drawHollowRect(int x, int y, int width, int height, u16 color)
{
	int x1;
	for(x1 = 0; x1< height; x1++)
	{
		setPixel(x+x1, y, color);
	}
	for(x1 = 0; x1< height; x1++)
	{
		setPixel(x+x1, y + width, color);
	}
	int y1;
	for(y1 = 0; y1< width; y1++)
	{
		setPixel(x, y+y1, color);
	}
	for(y1 = 0; y1<= width; y1++)
	{
		setPixel(x + height, y+y1, color);
	}
}

void drawWall(int y, int gate, int gateSize, u16 color)
{
	
	int x;
	for(x = 0; x < gate; x++)
	{
		setPixel(x, y, color);
	}
	for(x = gate; x < gate + gateSize; x++)
	{
		setPixel(x, y, BLACK);
	}
	for(x = gate + gateSize; x < 240; x++)
	{
		setPixel(x, y, color);
	}
}


void drawPicture(const unsigned short arr[])
{
	DMA[3].src = arr;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = (160*240) | DMA_ON;
}

void drawImage3(int r, int c, int width, int height, const u16* image)
{
	
	for (int x = 0; x < height; x++) {
	DMA[3].src = &image[OFFSET(x, 0, width)];
	DMA[3].dst = &videoBuffer[OFFSET(r + x, c, 240)];
	DMA[3].cnt = (width) | DMA_ON;
	}
}

void waitForVblank()
{
	while(SCANLINECOUNTER >160);
	while(SCANLINECOUNTER < 160);
}
	



