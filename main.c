/*
更新内容:
	补全大量注释,并进行一些细节的修改,修复内存泄漏的漏洞(未销毁链表)
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include "snake.h"//包含了所有的函数声明,和为了与c++兼容设置的bool宏
int main() {
	printMenu();//第一次进入循环前先初始化一次菜单
	char c;
	while (1) {//控制主循环
		gotoxy(37, 17);//定位到输入栏
		c = _getch();//vs2022要求将getch()更换为_getch()---标准c编译器换回getch()(?)
		if (c == '1') {
			initGame();//游戏数据初始化
			start();//正式开始一局游戏
			system("cls");//游戏结束清屏
			printMenu();//重新打印菜单
		}
		else if (c == '2') {
			color(7);//将颜色设置回白色
			gotoxy(0, 18);
			printf("游戏结束!\n");
			break;//跳出循环,结束游戏
		}
		else wrongInput();//输入非法,打印错误信息
	}
	return 0;
}