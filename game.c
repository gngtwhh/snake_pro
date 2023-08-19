#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include "snake.h"

//游戏数据
typedef struct snake {
    int x, y;
    struct snake *prior, *next;
} snake;//蛇身体的一个结点的类型
snake *head, *tail;//指向蛇头和蛇尾结点的指针

struct APPLE {
    int x, y;
} apple;//苹果的坐标数据

int score, pre_x, pre_y, wait = 500;//得分;前一个x,y坐标;等待时长(和游戏难度有关---改变蛇移动的速度)
int HEIGHT = 30;//地图高度
int WIDTH = 30;//地图宽度
int curSnakeLen = 0;//当前的蛇身长度
int maxSnakeLen = 0;//地图能容纳的最大蛇身长度,达到这个长度意味着游戏胜利

//starting
void printBox() {
    bool flag = 1;
    int n;
    //用户自定义地图大小,并进行计算应该生成的各项数据
    gotoxy(0, 0);
    printf("请输入地图大小(范围15~30,包括边界,按回车键确认):\n");
    printf("请输入宽度:");
    while (flag) {
        if (scanf("%d", &n) && n >= 15 && n <= 30) {
            flag = 0;
            WIDTH = n;
        } else {
            system("cls");
            gotoxy(0, 0);
            printf("请输入宽度:");
            gotoxy(0, 1);
            printf("输入错误!");
            gotoxy(11, 0);
            rewind(stdin);
        }
    }

    system("cls");

    gotoxy(0, 0);
    printf("请输入高度:");
    flag = 1;
    while (flag) {
        if (scanf("%d", &n) && n >= 15 && n <= 30) {
            flag = 0;
            HEIGHT = n;
        } else {
            system("cls");
            gotoxy(0, 0);
            printf("请输入高度:");
            gotoxy(0, 1);
            printf("输入错误!");
            gotoxy(11, 0);
            rewind(stdin);
        }
    }

    //+=2的原因是方块字符并非ASCII字符,占用两个字节大小---坐标每次需要+2而不是+1
    //打印围墙
    system("cls");
    for (int i = 0; i < WIDTH * 2; i += 2) {//上下
        gotoxy(i, 0);
        printf("□");
        gotoxy(i, HEIGHT - 1);
        printf("□");
    }
    for (int i = 1; i <= HEIGHT - 1; i++) {//左右
        gotoxy(0, i);
        printf("□");
        gotoxy(WIDTH * 2 - 2, i);
        printf("□");
    }
    //打印盒子内部
    color(7);
    for (int j = 1; j <= HEIGHT - 2; j++) {
        for (int i = 2; i < WIDTH * 2 - 2; i += 2) {
            gotoxy(i, j);
            printf("□");
        }
        putchar('\n');
    }
}

void initSnakeAndApple() {//缺陷:此函数未处理malloc可能的错误
    //初始化数据
    //以双向链表存储整条蛇,方便进行向前/向后遍历

    //创建蛇头
    head = (snake *) malloc(sizeof(snake));
    head->next = head->prior = NULL;
    head->x = 16;
    head->y = 4;
    //创建剩余3个普通蛇身结点---游戏开局蛇的长度默认为4
    snake *temp = head;
    for (int i = 1; i <= 3; ++i) {
        temp->next = (snake *) malloc(sizeof(snake));
        temp->next->prior = temp;
        temp = temp->next;

        temp->x = (head->x) + i * 2;
        temp->y = 4;
    }
    temp->next = NULL;
    tail = temp;
    curSnakeLen = 4;//初始时蛇的长度为4
    maxSnakeLen = (WIDTH - 2) * (HEIGHT - 2);//根据地图大小计算游戏胜利蛇应该达到的长度

    //打印蛇头
    temp = head;
    color(2);
    gotoxy(temp->x, temp->y);
    printf("■");
    //打印蛇身
    temp = temp->next;
    color(6);
    while (NULL != temp) {
        gotoxy(temp->x, temp->y);
        printf("■");
        temp = temp->next;
    }

    //初始化苹果并打印---游戏开局第一个苹果的位置默认为(8,4)
    apple.x = 8;
    apple.y = 4;
    color(4);
    gotoxy(8, 4);
    printf("■");

    //记录蛇尾
    pre_x = tail->x;
    pre_y = tail->y;
    return;
}

void setDifficulty() {
    bool flag = 1;
    int n, difficulties[6] = {0, 1000, 800, 600, 400, 200};//5种游戏难度---对应不同的等待时间
    gotoxy(0, 0);//每次的跳转都是根据提示信息计算好的,不能轻易改动
    printf("请输入难度[1~5](按回车键确认):");
    while (flag) {
        if (scanf("%d", &n) && n > 0 && n < 6)
            flag = 0;//输入成功则跳出循环
        else {
            system("cls");
            gotoxy(0, 0);
            printf("请输入难度[1~5](按回车键确认):");
            gotoxy(0, 1);
            printf("输入错误!");
            gotoxy(30, 0);
            rewind(stdin);
        }
    }
    //wait = 1100 - n * 200;
    wait = difficulties[n];//设置等待时间

    //初始化分数
    score = 0;

    rewind(stdin);//刷新缓冲区
    system("cls");//清屏
    return;
}

//game bejin
void start() {
    int flag = 2, flag2;//初始向左运动
    bool pause_game = false;
    //打印提示区域
    gotoxy(WIDTH * 2 + 4, 3);
    color(7);
    printf("wasd控制,空格键暂停");
    gotoxy(WIDTH * 2 + 4, 5);
    printf("score:");

    while (1) {
        if (againstTheWall() || againstSelf()) {//判断游戏结束
            gameover();//进行游戏结束的处理
            return;//处理完毕后结束这一局的游戏,跳转回主控制循环
        }
        //打印当前成绩
        gotoxy(WIDTH * 2 + 10, 5);
        color(7);
        printf("%d", score);
        //蛇运动
        flag2 = flag;//保存当前的前进方向
        flag = keyboard(flag);//获取新的(可能发生改变的)移动方向
        if (flag <= 4)
            moveSnake(flag);
        else if (flag == 5) {//5代表输入了空格,意味着暂停游戏
            pause_game = true;//设置暂停标志位
            flag = flag2;//前进方向重置为原来的方向
        }
        if (head->x == apple.x && head->y == apple.y) {//吃到苹果
            snakeGrowth();//蛇长长

            if (curSnakeLen == maxSnakeLen) {
                gamewin();//游戏胜利
                return;
            }
            //进行下一个苹果的生成(随机)
            srand((unsigned int) time(NULL));
            do {
                apple.x = ((rand() % (WIDTH - 2)) + 1) * 2;
                apple.y = (rand() % (HEIGHT - 2)) + 1;
            } while (isOverlap());//直到苹果生成在正确的(没有生成在蛇身体上---需要对蛇的链表进行遍历)位置
            gotoxy(apple.x, apple.y);//跳转到该坐标并进行打印苹果
            color(4);
            printf("■");
            score++;//分数+1
        }
        if (pause_game) {//如果暂停标志位设置为true则暂停游戏
            gotoxy(WIDTH * 2 + 4, 4);
            color(7);
            printf("pause    ");
            char c;
            while (c = _getch() != ' ');//暂停的死循环---直到键入空格,跳出循环,游戏继续
            rewind(stdin);
            pause_game = false;
            gotoxy(WIDTH * 2 + 4, 4);
            color(7);
            printf("          ");//覆盖暂停提示信息
        }
        Sleep(wait);//等待一段时间再继续运行
        rewind(stdin);//刷新游戏缓冲区
    }
}

bool againstTheWall() {//检查撞墙即检查蛇头的坐标是否和墙壁的坐标重合
    if (head->x == 0 || head->x == WIDTH * 2 - 2 ||
        head->y == 0 || head->y == HEIGHT - 1)
        return true;
    return false;
}

bool againstSelf() {//检查撞到自己即检查蛇头的坐标是否和任一蛇身的坐标重合
    snake *temp = head->next;
    while (temp != NULL) {//对链表进行遍历
        if (head->x == temp->x && head->y == temp->y)
            return true;
        temp = temp->next;
    }
    return false;
}

void gameover() {//游戏结束的处理
    system("cls");
    const char *endInterface[8] = {
            "        _______________________________________________\n",
            "        |                                             |\n",
            "        |        游戏结束:                            |\n",
            "        |        分数:",
            "\n",
            "        |                                             |\n",
            "        -----------------------------------------------\n",
            "                    按空格键确认:[ ]"
    };
    for (int i = 0; i < 4; ++i) {
        color(i + 2);
        printf("%s", endInterface[i]);
    }
    printf("%d", score);
    gotoxy(54, 3);
    putchar('|');
    for (int i = 4; i < 8; ++i) {
        color(i + 2);
        printf("%s", endInterface[i]);
    }
    gotoxy(34, 6);
    char c;
    while (c = _getch() != ' ');//直到键入空格才会返回
}

//代码冗余,尚未优化
void gamewin() {//游戏胜利的处理
    system("cls");
    const char *endInterface[8] = {
            "        _______________________________________________\n",
            "        |                                             |\n",
            "        |        游戏胜利:                            |\n",
            "        |        分数:",
            "\n",
            "        |                                             |\n",
            "        -----------------------------------------------\n",
            "                    按空格键确认:[ ]"
    };
    for (int i = 0; i < 4; ++i) {
        color(i + 2);
        printf("%s", endInterface[i]);
    }
    printf("%d", score);
    gotoxy(54, 3);
    putchar('|');
    for (int i = 4; i < 8; ++i) {
        color(i + 2);
        printf("%s", endInterface[i]);
    }
    gotoxy(34, 6);
    char c;
    while (c = _getch() != ' ');//同样等待输入
}

void moveSnake(int flag) {//蛇的正常前进
    int move[4][2] = {
            {0,  -1},
            {-2, 0},
            {0,  1},
            {2,  0}
    };//4种不同的移动方向对应的4种坐标变换
    flag--;//对应move数组的元素--从下标0开始
    //保存蛇尾位置
    pre_x = tail->x;
    pre_y = tail->y;
    //蛇尾,旧蛇头覆盖打印
    gotoxy(tail->x, tail->y);
    color(7);
    printf("□");

    gotoxy(head->x, head->y);
    color(6);
    printf("■");
    //蛇尾断开
    snake *temp = tail;
    tail = tail->prior;
    tail->next = NULL;
    //蛇尾结点作为新头,不需要删除创建,节省时间
    temp->next = head;
    temp->prior = NULL;
    head->prior = temp;
    head = temp;
    //新蛇头位置计算并打印
    head->x = head->next->x + move[flag][0];
    head->y = head->next->y + move[flag][1];
    gotoxy(head->x, head->y);
    color(2);
    printf("■");
}

void snakeGrowth() {//蛇的长度增长
    //新增蛇身结点---即在蛇尾新增一个结点并即刻打印(蛇此时已前进一格且吃到苹果
    tail->next = (snake *) malloc(sizeof(snake));
    tail->next->prior = tail;
    tail = tail->next;
    tail->next = NULL;
    tail->x = pre_x;
    tail->y = pre_y;
    ++curSnakeLen;//当前长度+1
    gotoxy(pre_x, pre_y);
    color(6);
    printf("■");//进行打印
    return;
}

bool isOverlap() {//检查新生成的苹果坐标是否和蛇身的任何一个部位重合
    snake *temp = head;
    while (temp != NULL) {//遍历蛇身链表
        if (apple.x == temp->x && apple.y == temp->y)
            return true;
        temp = temp->next;
    }
    return false;
}

void destoryGameData() {//主要任务即销毁链表
    snake *temp = head;
    snake *next = NULL;
    while (temp != NULL) {//遍历蛇身链表
        next = temp->next;//蛇最短也有4个结点,不存在temp和temp->next为NULL的情况
        free(temp);
        temp = next;
    }
}