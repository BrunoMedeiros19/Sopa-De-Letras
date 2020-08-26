#pragma once
#ifndef _LABH_		//protectes from multiple including...
#define _LABH_		//... needs an #endif at bottom

#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <locale.h>

#define false	0
#define true	1

#define MY_COLOR_BLACK			0
#define MY_COLOR_DARK_BLUE		1
#define MY_COLOR_SOFT_GREEN		2
#define MY_COLOR_SOFT_BLUE		3
#define MY_COLOR_DARK_RED		4
#define MY_COLOR_PURPLE			5
#define MY_COLOR_DARK_YELLOW	6
#define MY_COLOR_GRAY			7
#define MY_COLOR_DARK_GRAY		8
#define MY_COLOR_CYAN			9
#define MY_COLOR_LIGTH_GREEN	10
#define MY_COLOR_LIGTH_BLUE		11
#define MY_COLOR_LIGTH_RED		12
#define MY_COLOR_PINK			13
#define MY_COLOR_LIGTH_YELLOW	14
#define MY_COLOR_WHITE			15

//changes both foreground and background colors
void setColor(int foreGround, int backGround) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backGround * 16 + foreGround);
}
//changes foreground color while keeping background color
void setForeColor(int foreGround) {
	int backGround = MY_COLOR_BLACK;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	backGround = csbiInfo.wAttributes / 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backGround * 16 + foreGround);
}
//changes background color while keeping foreground color
void setBackColor(int backGround) {
	int foreGround = MY_COLOR_BLACK;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	foreGround = csbiInfo.wAttributes % 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), backGround * 16 + foreGround);
}
//Colors reset: foreground white, background black
void resetColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), MY_COLOR_BLACK * 16 + MY_COLOR_WHITE);
}

//allows to place the cursor at any given position
void gotoxy(int x, int y) {
	COORD c = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

#endif