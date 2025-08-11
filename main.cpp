#include<bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
bool flag=0,flag2=0;
int b[5][5],a[5][5];
int keya[4]={'w','a','s','d'};
int keyb[4]={'H','K','M','P'};
int keyc[4]={'8','4','2','6'};
map<char,int>akey;
const int old_color[12]={-1,
0xEAEADC,0xEBDFC7,0xE0B884,0xF7926A,
0xE5A4A1,0xF3ADA2,0xFFC2C5,0xE89EA4,
0xC8CE3A,0xE0D444,0xFFDF3A};
map<int,int>color;

#define WHITE 0xffffff
#define W 0xffffff
#define BLACK 0x000000
#define RED 0xff0000
#define GREEN 0x00ff00
#define BLUE 0x0000ff
#define A1 0xB7ADA2
#define A2 0xC9BFB5

char key;
int jkey;

#define wasd 0xAAA001
#define next1 0xAAA002
#define key_w 1

#define random(l,r) (rand()%r+l) //随机数取数

int wflag;
int score; //方数
int now_max; //当前最大方块
int game_; //游戏时刻

//初始设置
void init1(); //初始化 
void init2(); //游戏功能初始化
void init3(); //对于页面的初始化
void rgbInit(); //ANSI的函数
void colorInit(); //设置方块颜色 
//基本功能
void pr(int w,int b,int x,int y); //输出颜色RGB、位置 
void pr(int w,int x,int y,string s); //简单的字符串输出 
void getKey(int i); //键盘读入
//游戏功能
void runGame(); //进行游戏
void work(); //替换 
bool isCanRun(); //判断是否能继续
void Game(int f); //移动
void printNumber(); //刷新界面数字
void ab(int &a,int &b);//重合

//旋转方向 
void work0(); 
void work1(); 
void work2();
void work3();

int main(){
	init1();
	while(1){
		runGame();
		if(key==27) return 0;
	}
	return 0;
}

//ANSI的函数
void rgbInit(){
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);//输入句柄
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//输出句柄
	DWORD dwInMode, dwOutMode;
	GetConsoleMode(hIn, &dwInMode);//获取控制台输入模式
	GetConsoleMode(hOut, &dwOutMode);//获取控制台输出模式
	dwInMode |= 0x0200;//更改
	dwOutMode |= 0x0004;
	SetConsoleMode(hIn, dwInMode);//设置控制台输入模式 
	SetConsoleMode(hOut, dwOutMode);//设置控制台输出模式
}

//设置方块颜色 
void colorInit(){
	for(int i=1;i<=11;i++){
		int m=1<<i;
		color[m]=old_color[i];
	}
}

//输出颜色RGB、位置 
void pr(int w,int b,int x,int y){
	//定义RGB 
	int wr=w/0x10000;
	int wg=w/0x100%0x100;
	int wb=w%0x100;
	int br=b/0x10000;
	int bg=b/0x100%0x100;
	int bb=b%0x100;
	printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,br,bg,bb);
	//颜色确定
	//定位 
    COORD  coord;    
    coord.X=x;         
    coord.Y=y;
    HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,coord);
}

//简单的字符串输出 
void pr(int w,int x,int y,string s){
	pr(w,BLACK,x,y);
	cout<<s;
	pr(W,BLACK,0xffffff,0xffffff);
}

//初始化 
void init1(){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	rgbInit();
	colorInit();
	
	
	SetConsoleTitleA("2048游戏");
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // 光标信息
}

//游戏功能初始化
void init2(){
	srand(time(NULL));
	score=0;
	akey['a']=akey['A']=akey['K']=akey['4']=3;
	akey['w']=akey['W']=akey['H']=akey['8']=0;
	akey['d']=akey['D']=akey['M']=akey['6']=1;
	akey['s']=akey['S']=akey['P']=akey['2']=2;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			a[i][j]=-1;
		}
	}	
	
}

//图初始化 
void init3(){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//获取控制台光标信息
	CursorInfo.bVisible = false; //隐藏控制台光标
	SetConsoleCursorInfo(handle, &CursorInfo);//设置控制台光标状态
	system("cls");
	pr(0x989898,BLACK,0,0);
	printf("得分score:\n");
	printf("当前最大方块数字:"); 
	pr(0x989898,BLACK,0,15);
	printf("如果游戏画面出现了问题，请按 r 键恢复\n按空格键重新游戏或退出");
	pr(0x4169E1,BLACK,36,5);
	printf("游戏说明");
	pr(0x29CC50,BLACK,36,6);
	printf("每次可以选择上下左右其中一个方向去滑动");
	pr(0x29CC50,BLACK,36,7);
	printf("每滑动一次，所有的数字方块都会往滑动的方向靠拢");
	pr(0x29CC50,BLACK,36,7);
	printf("系统也会在空白的地方乱数出现一个数字方块");
	pr(0x29CC50,BLACK,36,8);
	printf("相同数字的方块在靠拢、相撞时会相加");
	pr(0x29CC50,BLACK,36,9);
	printf("系统给予的数字方块不是2就是4");
	pr(0x29CC50,BLACK,36,10);
	printf("要想办法在这小小的16格范围中凑出“2048”这个数字方块游戏胜利");	;
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			pr(A1,A1,i*5,j*3-1);
			printf("     ");
			pr(A1,A1,i*5,j*3+1);
			printf("     ");
			pr(A1,A1,i*5-1,j*3);
			printf(" ");
			if(i==4){
				pr(A1,A1,i*6+1,j*3);
				printf("     ");
				pr(A1,A1,i*6+1,j*3+1);
				printf("     ");
				pr(A1,A1,i*6+1,j*3+-1);
				printf("     ");
			}

			if(i==1){
				pr(A1,A1,0,j*3);
				printf("     ");
				pr(A1,A1,0,j*3+1);
				printf("     ");
				pr(A1,A1,0,j*3+-1);
				printf("     ");
			}
		} 
	}
	pr(BLACK,BLACK,0,0);
}

//键盘读入 
void getKey(int i){
	while(1){
		key = getch();  // 读取键盘输入的字符
	 	if (key == '\xE0') {  // 如果是特殊字符(如箭头键)
	  		key = getch(); // 继续读取一个字符
	  		
	  		if(i==wasd){
				for(int i=0;i<=3;i++){
					if(key==keyb[i]) return;
				}
			}
		}
		else{
			if(i==key) return ;
			if(i==wasd){
				for(int i=0;i<=3;i++){
					if(key==keya[i]||key==keya[i]-'a'+'A') return;
				}
				for(int i=0;i<=3;i++){
					if(key==keyc[i]) return;
				}
				if(key==' ') return; 
				if(key=='r'||key=='R') return ;
			}
			if(i==next1){
				if(key==27||key==32) return ;
			}
		}
	}
}

//刷新界面数字
void printNumber(){
	pr(W,BLACK,10,0);
	printf("%d",score);
	pr(color[now_max],BLACK,17,1);
	cout<<now_max;  
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(a[i][j]==-1){
				pr(A2,A2,i*5,j*3);
				printf("     ");
			}
			else{
				pr(0xffffff-color[a[i][j]],color[a[i][j]],i*5,j*3);
				printf("%d     ",a[i][j]);
			}
			pr(A1,A1,i*5-1,j*3);
			printf(" ");
			if(i==4){
				pr(A1,A1,24,j*3);
				printf("     ");
			}
			
		} 
	}
	pr(BLACK,BLACK,0,0);
}

//旋转方向 
void work0(){
    for(int i=1;i<=4;i++){
	    for(int j=1;j<=4;j++)
	    	b[i][j]=a[i][j];
	}
}
void work1(){
    for(int i=1;i<=4;i++){
        for(int j=1;j<=4;j++)
        	b[j][4-i+1]=a[i][j];
    }
}
void work2(){
    for(int i=1;i<=4;i++)
    {
        for(int j=1;j<=4;j++)
       		b[4-i+1][4-j+1]=a[i][j];
    }
}
void work3(){
	for(int i=1;i<=4;i++)
    {
        for(int j=1;j<=4;j++)
        	b[4-j+1][i]=a[i][j];
    }
}
//替换 
void work(){
    for(int i=1;i<=4;i++){
	    for(int j=1;j<=4;j++)
	    	a[i][j]=b[i][j];
	}
}

//重合
void ab(int &a,int &b){
	if(a==-1){
		if(b!=-1)wflag=1;
		if(b!=-1) flag2=0;
		swap(a,b);
		return ;
	}
	if(a==b&&flag==0){
		score+=a*2,now_max=max(now_max,a*2);
		wflag=1;
//		cout<<a<<' '<<b<<endl;
		flag=1;
		a*=2,b=-1;
		return ;
	}
	if(flag==1) flag=0;
	return ;
}

//移动 
void Game(int f){
	if(f==0) work0();
	if(f==1) work1();
	if(f==2) work2();
	if(f==3) work3();
	for(int i=1;i<=4;i++){
		flag=0;
		flag2=0;
		while(flag2==0){
			flag2=1;
			for(int j=1;j<=3;j++){	
				ab(b[i][j],b[i][j+1]);				
			}

		}
	}
	work();
	if(f==1) work3();
	if(f==2) work2();
	if(f==3) work1();
	work();
}

//判断是否能继续
bool isCanRun(){
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(a[i][j]==-1) return 0;
			int tx[4]={0,0,-1,1};
			int ty[4]={-1,1,0,0};
			for(int k=0;k<4;k++){
				if(a[i][j]==a[i+tx[k]][j+ty[k]]) return 0; 
			}
			
		}
	}
	return 1;
}

//运行游戏
void runGame(){
	init2();
	int tu=0,tu4=0;
	now_max=2;
	
	//新生成两个方块
	int random_maxNum=0x3f3f3f3f;
	pair<int,int>random_maxId=make_pair(-1,-1);
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(a[i][j]==-1){
				int random_nowNum=rand();
				if(random_nowNum<random_maxNum){
					random_maxNum=random_nowNum;
					random_maxId=make_pair(i,j);
				}
			}
		}
	}	
	int i=random_maxId.first;
	int j=random_maxId.second;
	if(random(1,10)==1) a[i][j]=4,now_max=4;
	else a[i][j]=2;
	
	random_maxNum=0x3f3f3f3f;
	random_maxId=make_pair(-1,-1);
	for(int i=1;i<=4;i++){
		for(int j=1;j<=4;j++){
			if(a[i][j]==-1){
				int random_nowNum=rand();
				if(random_nowNum<random_maxNum){
					random_maxNum=random_nowNum;
					random_maxId=make_pair(i,j);
				}
			}
		}
	}	
	i=random_maxId.first;
	j=random_maxId.second;
	if(random(1,10)==1) a[i][j]=4,now_max=4;
	else a[i][j]=2;
	
	game_=1; //进入游戏
	printNumber();
	init3();
	while(game_==1){
		printNumber();
		getKey(wasd);
		if(key=='r'||key=='R'){
			//重置页面
			init3();
			continue;
		}
		if(key==' '){
			//暂停界面
			int result = MessageBox(NULL, "是否重来或退出?", "提示", MB_YESNO | MB_ICONQUESTION);
			if (result == IDYES) {
				game_=4;
				break;
			}
			else if (result == IDNO) {
			    continue;
		    }
		}
		tu=0,tu4=0;
		bool flag=0;
		wflag=0;

		Game(akey[key]); //移动方块
		
		int random_maxNum=0x3f3f3f3f;
		pair<int，int>random_maxId=make_pair(-1,-1);
		for(int i=1;i<=4;i++){
			for(int j=1;j<=4;j++){
				if(a[i][j]==-1){
					int random_nowNum=rand();
					if(random_nowNum<random_maxNum){
						random_maxNum=random_nowNum;
						random_maxId=make_pair(i,j);
					}
				}
			}
		}	
		int i=random_maxId.first;
		int j=random_maxId.second;
		if(random(1，10)==1) a[i][j]=4,now_max=max(now_max,4);
		else a[i][j]=2;
		
		if(现在_max==2048) game_=2; //合成2048
		else if(isCanRun()) game_=3; //无路可走
	}
	printNumber(); 
	if(game_==2){
		pr(BLACK,W,5,7);
		printf("你合成出了2048！\n按esc退出游戏，按空格再来一局");
	}
	else if(game_==3){
		pr(BLACK,W,6,7);
		printf("你已经无路可走 \n按esc退出游戏，按空格再来一局");
	}
	else if(game_==4){
		pr(BLACK,W,8,7);
		printf("你选择了重来 \n按esc退出游戏，按空格再来一局");
	}
	getKey(next1);
}
