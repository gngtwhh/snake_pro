#define bool int//纯c语言,需要宏定义bool类型
#define false 0
#define true 1
#define MAX_IS(a,b) ((a)>(b)?(1):(2))

//蛇链表结点数据结构
#ifndef SNAKE_NODE
#define SNAKE_NODE
typedef struct snake {
    int x, y;
    struct snake *prior, *next;
} snake;//蛇身体的一个结点的类型
#endif

//存储苹果
#ifndef APPLE_NODE
#define APPLE_NODE
typedef struct APPLE {
    int x, y;
} APPLE;
#endif

//main nemu---主菜单
void printMenu();//打印菜单界面
void initGame(int model);//初始化游戏数据总控制函数
void wrongInput();//菜单选择错误输入处理
//void showRank();显示分数排行,暂未实现

//starting---各个游戏数据初始化函数
void printBox();//打印地图
void initSnakeAndApple(int id,int head_x, int head_y, snake **head,
                       snake **tail);//初始化蛇和苹果
void setDifficulty();//设置游戏难度

//game begin---游戏逻辑主体
void start(int model);//游戏主循环(总控制)
//void snakeBehavior(snake*head,snake*tail,int id,int flag);//蛇的行为控制,包括移动,增长和吃到苹果的处理,4个参数分别为蛇头,蛇尾,蛇编号,方向
bool againstTheWall(int id);//检查蛇是否撞墙
bool againstSelf(int id);//检查蛇是否撞到自己
void gameover();//游戏结束处理
void gamewin(int flag);//游戏胜利界面
void snakeGrowth(int id);//吃到苹果时蛇增长
void moveSnake(int id,int flag, int model);//移动蛇,三个参数为蛇编号,方向,游戏模式
void eatApple(int id);//吃到了苹果时的处理---包括苹果的重新生成和蛇的增长
bool isOverlap();//生成苹果时检查是否错误地生成在蛇身体上
void destoryGameData();//当前一局游戏结束时释放空间

//system---系统相关的函数
void gotoxy(int, int);//光标重定位
void color(int);//设置打印颜色
int keyboard(int);//无缓冲键盘输入支持
