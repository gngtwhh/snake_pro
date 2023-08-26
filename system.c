//与控制台相关的函数
//控制光标位置,当前打印颜色,检测键盘输入
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "snake.h"

//system
//涉及到windows的API
void color(int i) {//更改文字颜色
    //SetConsoleTextAttribute是API设置控制台窗口字体颜色和背景色的函数
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), i);
}

//游戏中每次调用gotoxy时的参数都是根据游戏菜单字符位置/当前坐标计算好传递过来的
void gotoxy(int x, int y) {
    COORD c;
    static HANDLE h;
    h = GetStdHandle(STD_OUTPUT_HANDLE);//从标准设备获取句柄
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(h, c);
}

int keyboard(int pre) {//键盘输入判断
    char c;
    int n = pre;
    if (_kbhit()) {//检查是否有键盘输入
        c = _getch();//如果有,则进行一次读取
        if (c == 'w' || c == 'W')
            n = 1;
        else if (c == 'a' || c == 'A')
            n = 2;
        else if (c == 's' || c == 'S')
            n = 3;
        else if (c == 'd' || c == 'D')
            n = 4;
        else if (c == 'i' || c == 'I')
            n = 6;
        else if (c == 'j' || c == 'J')
            n = 7;
        else if (c == 'k' || c == 'K')
            n = 8;
        else if (c == 'l' || c == 'L')
            n = 9;
        else if (c == ' ')
            n = 5;
    }
    rewind(stdin);//fflush(stdin); 刷新缓冲区,在VS2015之后不再起作用(编译成功但无效果)
    if ((pre == 1 && n == 3) || (pre == 2 && n == 4) || (pre == 3 && n == 1) ||
        (pre == 4 && n == 2))
        return pre;//如果键盘要求蛇180度转向,则转向失败,蛇仍然按照原来的方向前进
    if ((pre == 6 && n == 8) || (pre == 7 && n == 9) || (pre == 8 && n == 6) ||
        (pre == 9 && n == 7))
        return pre;//如果键盘要求蛇180度转向,则转向失败,蛇仍然按照原来的方向前进
    return n;//成功转向,返回下一步前进的方向
}

int keyboard_2() {
    int n = 0;
    char hits[10] = {0, 'w', 'a', 's', 'd', ' ', 'i', 'j', 'k', 'l'};
    if (_kbhit()) {
        n = _getch();
        for (int i = 1; i < 10; ++i) {
            if (n == hits[i])
                return i;
        }
    }
    return 0;
}