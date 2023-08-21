#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "snake.h"

//nemu
void printMenu() {
    const char *logo[10] = {"   ________\n",
                            "  / ______ \\    v2.0.0~~~\n",
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
    const char *select[8] = {
            "        _______________________________________________\n",
            "        |                                             |\n",
            "        |        请输入编号:                          |\n",
            "        |       1.经典模式     2.无界模式             |\n",
            "        |       3.对战模式     4.退出游戏             |\n",
            "        |                                             |\n",
            "        -----------------------------------------------\n",
            "                    请输入编号[1/2]:[ ]"
    };
    for (int i = 0; i < 8; ++i) {//打印菜单
        color(i + 2);
        printf("%s", select[i]);
    }
}

void initGame(int model) {//初始化各项数据
    system("cls");
    setDifficulty();
    //2.0版本更新游戏模式,此处初始化游戏界面使用switch进行分情况处理
    //暂时3种游戏模式的初始界面相同,switch用于日后方便扩展功能
    extern snake *head_arr[3], *tail_arr[3];
    switch (model) {
        case 1:
            printBox();
            initSnakeAndApple(1, 8, 4, &head_arr[1], &tail_arr[1]);
            break;
        case 2:
            printBox();
            initSnakeAndApple(1, 8, 4, &head_arr[1], &tail_arr[1]);
            break;
        case 3:
            printBox();
            initSnakeAndApple(1, 8, 4, &head_arr[1], &tail_arr[1]);
            initSnakeAndApple(2, 8, 6, &head_arr[2], &tail_arr[2]);
            break;
    }

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