/*
2.0
更新内容:
    游戏模式增加
*/
/*
 * main.c:
 *  进行整个游戏的控制:打印菜单,控制循环以重复开始游戏
 *  并调用错误输入的处理函数
 */
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "snake.h"//包含了所有的函数声明,和为了与c++兼容设置的bool宏

int main() {
    printMenu();//第一次进入循环前先初始化一次菜单
    char c;
    while (1) {//控制主循环
        gotoxy(37, 17);//定位到输入栏
        c = _getch();//vs2022要求将getch()更换为_getch()---标准c编译器换回getch()(?)
        if (c == '1') {
            initGame(1);//游戏数据初始化
            start(1);//正式开始一局经典模式游戏
            system("cls");//游戏结束清屏
            printMenu();//重新打印菜单
        } else if (c == '2') {
            initGame(2);//游戏数据初始化
            start(2);//正式开始一局无尽模式游戏
            system("cls");//游戏结束清屏
            printMenu();//重新打印菜单
        } else if (c == '3') {
            system("cls");
            printf("正在开发中...");
            Sleep(1000);
            system("cls");
            printMenu();
            /*initGame(3);//游戏数据初始化
            start(3);//正式开始一局对战模式游戏
            system("cls");//游戏结束清屏
            printMenu();//重新打印菜单*/
        } else if (c == '4') {
            color(7);//将颜色设置回白色
            gotoxy(0, 18);
            printf("游戏结束!\n");
            break;//跳出循环,结束游戏
        } else wrongInput();//输入非法,打印错误信息
    }
    return 0;
}