#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "snake.h"

//nemu
void printMenu() {
	const char* logo[10] = { "   ________\n",
							 "  / ______ \\    v1.0.1~~~\n",
							 " / /      \\ \\                                 ___\n",
							 " | \\      |_|                                 | | \n",
							 "  \\ \\______     ___ ______       ____   ___   | | __    ______\n",
							 "   \\______ \\    | |/ ____ \\     / __ \\_/  /   | |/ /   /  ___ \\\n",
							 " _        \\ \\   | | /    \\ \\   / /  \\    /    |   /   |  /___\\ \\\n",
							 "| |        | |  |  /     | |  | |    |   |    |   \\   |  _______|\n",
							 " \\ \\_______| |  | |      | |  |  \\__/ __  \\   | |\\ \\   \\ \\______\n",
							 "  \\_________/   |_|      |_|   \\_____/  \\__\\  |_| \\_\\   \\______/\n"
	};

	for (int i = 0; i < 10; ++i) {//打印标题
		color(i + 1);
		printf("%s", logo[i]);
	}
	const char* select[8] = {
		"        _______________________________________________\n",
		"        |                                             |\n",
		"        |        请输入编号:                          |\n",
		"        |       1.开始游戏     2.退出游戏             |\n",
		"        |                                             |\n",
		"        |                                             |\n",
		"        -----------------------------------------------\n",
		"                    请输入编号[1/2]:[ ]"
	};
	for (int i = 0; i < 8; ++i) {//打印菜单
		color(i + 2);
		printf("%s", select[i]);
	}
}
void initGame() {//初始化各项数据
	system("cls");
	setDifficulty();
	printBox();
	initSnakeAndApple();
}
void showRank() {
	;
}
void wrongInput() {//处理错误的键盘输入---打印报错信息
	gotoxy(43, 17);
	printf("输入错误!");
	Sleep(1000);//停顿一秒后清除信息
	gotoxy(43, 17);
	printf("         ");
	gotoxy(39, 17);
}