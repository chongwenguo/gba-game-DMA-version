#include <stdlib.h>
#include <stdio.h>
#include "myLib.h"
#include "text.h"
#include "splash.h"
#include "black.h"
#include "end.h"
#include "bg.h"
#include "heart.h"

//chongwen guo
#define REG_DISPCTL *(u16 *)0x4000000


int splash();
void win();
int game();
void lose();
enum {SPLASH, GAME, WIN, LOSE};

int main()
{
	int seed = 0;
	int state = SPLASH;
	while(1)
	{
		switch(state)
		{
		case SPLASH:
			seed = splash();
			state = GAME;
			break;
		case GAME:
			state = game(seed);
			break;
		case WIN:
			win();
			state = SPLASH;
			break;
		case LOSE:
			lose();
			state = SPLASH;
			break;
		}
	}
}

int splash()
{
	int seed = 0;
	//u16 *ptr = videoBuffer;
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	drawPicture(start);
	drawString(150, 0, "Press Start", YELLOW);
	while(!KEY_DOWN_NOW(BUTTON_START))
	{
		seed++;
	}
	while(KEY_DOWN_NOW(BUTTON_START));
	return seed;
}

void win()
{
	drawPicture(bg);

	drawString(70, 10, ":) YOU WIN!!!", YELLOW);
	drawString(90, 10, "Press Start", YELLOW);
	while(!KEY_DOWN_NOW(BUTTON_START));
	while(KEY_DOWN_NOW(BUTTON_START));
}

void lose()
{
	drawPicture(end);
	drawString(150, 0, "Press Start", YELLOW);
	drawString(130, 0, ":( YOU LOST, TRY AGAIN?", YELLOW);
	while(!KEY_DOWN_NOW(BUTTON_START));
	while(KEY_DOWN_NOW(BUTTON_START));
}

int game(int seed)
{
	REG_DISPCTL = MODE3 | BG2_ENABLE;
	int live = 5;
	char buffer[41];
	int speed = 1;

	int num = 100;
	int objx = 70;
	int objy = 50;

	drawPicture(black);
	
	WALL wall0;
	wall0.i = 80;
	wall0.gate = 90;
	wall0.gateSize = 10;
	wall0.color = WHITE;
	
	WALL wall1;
	wall1.i = 100;
	wall1.gate = 90;
	wall1.gateSize = 10;
	wall1.color = MAGENTA;

	WALL wall2;
	wall2.i = 120;
	wall2.gate = 30;
	wall2.gateSize = 30;
	wall2.color = RED;
	
	WALL wall3;
	wall3.i = 140;
	wall3.gate = 150;
	wall3.gateSize = 30;
	wall3.color = BLUE;

	WALL wall4;
	wall4.i = 160;
	wall4.gate = 0;
	wall4.gateSize = 20;
	wall4.color = GREEN;

	WALL wall5;
	wall5.i = 180;
	wall5.gate = 130;
	wall5.gateSize = 20;
	wall5.color = BLUE;
	
	WALL wall6;
	wall6.i = 200;
	wall6.gate = 130;
	wall6.gateSize = 15;
	wall6.color = CYAN;
	

	// Game Loop
	while(1)
	{
		
		int oldx = objx;
		int oldy = objy;
		
		drawRect(oldx,oldy,1,1, BLACK);


		if(KEY_DOWN_NOW(BUTTON_SELECT))
		{	
			
		 	objx = 70;
			objy = 50;
			live = 5;
			drawRect(150,0,60,30,BLACK);
			drawString(150, 0, "Score: 0", YELLOW);

		}
		
				
		if(KEY_DOWN_NOW(BUTTON_UP))
		{
			objx-=speed;
			if(objx < 0)
			{
				objx = 0;
			}
			
		}
		if(KEY_DOWN_NOW(BUTTON_DOWN))
		{
			objx+=speed;
			if(objx > 159)
			{
				objx = 159;
			}
		
		}
		
		if(KEY_DOWN_NOW(BUTTON_A))
		{
			speed = 2;
		
		}
		if(KEY_DOWN_NOW(BUTTON_B))
		{
			speed = 1;
			
		}
		if(KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			objy++;
	
		}
		if(KEY_DOWN_NOW(BUTTON_LEFT))
		{
			objy--;
			if(objy <= 0)
			{
				objy= 0;
			}
	
		}
	
		drawRect(objx,objy,1,1, RED);
		
		drawWall(wall0.i, wall0.gate, wall0.gateSize, wall0.color);
		
		if(num < 50) 
		{
			if(num <= 0)
			{
				num = 100;
			}
			
			drawWall(wall1.i, wall1.gate++, wall1.gateSize, wall1.color);
			drawWall(wall2.i, wall2.gate-=2, wall2.gateSize, wall2.color);
			drawWall(wall3.i, wall3.gate+=3, wall3.gateSize, wall3.color);
			drawWall(wall4.i, wall4.gate-=3, wall4.gateSize, wall4.color);
			drawWall(wall5.i, wall5.gate+=3, wall5.gateSize, wall5.color);
			drawWall(wall6.i, wall6.gate+=3, wall6.gateSize, wall6.color);
		}
		else 
		{
			drawWall(wall1.i, wall1.gate--, wall1.gateSize, wall1.color);
			drawWall(wall2.i, wall2.gate+=2, wall2.gateSize, wall2.color);
			drawWall(wall3.i, wall3.gate-=3, wall3.gateSize, wall3.color);
			drawWall(wall4.i, wall4.gate+=3, wall4.gateSize, wall4.color);
			drawWall(wall5.i, wall5.gate-=3, wall5.gateSize, wall5.color);
			drawWall(wall6.i, wall6.gate-=3, wall6.gateSize, wall6.color);
		}
		num--;
		
		if(objy < wall0.i)
		{
			drawString(150, 0, "Score: 0", YELLOW);
		}

		if(objy == wall0.i)
		{
			if(objx < wall0.gate || objx > wall0.gate + wall0.gateSize)
			{
				live--;
				objy-=10;
				drawRect(objx,objy ,1,1, RED);

				if (live == 0)
				{
					return LOSE;
				}
			}
			drawRect(150,0,60,30,BLACK);
			
			drawString(150, 0, "Score: 1", YELLOW);
		}
		if(objy == wall1.i)
		{
			if(objx < wall1.gate || objx > wall1.gate + wall1.gateSize)
			{
				live--;
				objy-=10;
				drawRect(objx,objy ,1,1, RED);
				if (live == 0)
				{
					return LOSE;
				}
			}
			drawRect(150,0,60,30,BLACK);
			drawString(150, 0, "Score: 2", YELLOW);
		}
		if(objy == wall2.i)
		{
			if(objx < wall2.gate || objx > wall2.gate + wall2.gateSize)
			{
				live--;
				objy-=10;
				drawRect(objx,objy ,1,1, RED);
				if (live == 0)
				{
					return LOSE;
				}
			}
			drawRect(150,0,60,30,BLACK);
			drawString(150, 0, "Score: 3", YELLOW);
		}
		if(objy == wall3.i)
		{
			if(objx < wall3.gate || objx > wall3.gate + wall3.gateSize)
			{
				live--;
				objy-=10;
				drawRect(objx,objy ,1,1, RED);
				if (live == 0)
				{
					return LOSE;
				}
			}
			drawRect(150,0,60,30,BLACK);
			drawString(150, 0, "Score: 4", YELLOW);
		}
		if(objy == wall4.i)
		{
			if(objx < wall4.gate || objx > wall4.gate + wall4.gateSize)
			{
				live--;
				objy-=10;
				drawRect(objx,objy ,1,1, RED);
				if (live == 0)
				{
					return LOSE;
				}
			}
			drawRect(150,0,60,30,BLACK);
			drawString(150, 0, "Score: 5", YELLOW);
		}
		if(objy == wall5.i)
		{
			if(objx < wall5.gate || objx > wall5.gate + wall5.gateSize)
			{
				live--;
				objy-=10;
				drawRect(objx,objy ,1,1, RED);
				if (live == 0)
				{
					return LOSE;
				}
			}
			drawRect(150,0,60,30,BLACK);
			drawString(150, 0, "Score: 6", YELLOW);
		}
		if(objy == wall6.i)
		{
			if(objx < wall6.gate || objx > wall6.gate + wall6.gateSize)
			{
				live--;
				objy-=10;
				drawRect(objx,objy ,1,1, RED);
				if (live == 0)
				{
					return LOSE;
				}
			}
			drawRect(150,0,60,30,BLACK);
			drawString(150, 0, "Score: 7", YELLOW);
		}
		
		if(objy > wall6.i +5)
		{
			return WIN;
		}
		drawRect(5,5,60,30,BLACK);
		waitForVblank();
		drawImage3(0,0,30,30,heart);
		sprintf(buffer, " %d", live);
		drawString(10, 30, buffer, YELLOW);
		drawString(80,210, "EXIT", YELLOW);
	
		
	}

		
}

