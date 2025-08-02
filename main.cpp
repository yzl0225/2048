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

#define random(l,r) (rand()%r+l) //�����ȡ��

int wflag;
int score; //����
int now_max; //��ǰ��󷽿�
int game_; //��Ϸʱ��

//��ʼ����
void init1(); //��ʼ�� 
void init2(); //��Ϸ���ܳ�ʼ��
void init3(); //����ҳ��ĳ�ʼ��
void rgbInit(); //ANSI�ĺ���
void colorInit(); //���÷�����ɫ 
//��������
void pr(int w,int b,int x,int y); //�����ɫRGB��λ�� 
void pr(int w,int x,int y,string s); //�򵥵��ַ������ 
void getKey(int i); //���̶���
//��Ϸ����
void runGame(); //������Ϸ
void work(); //�滻 
bool isCanRun(); //�ж��Ƿ��ܼ���
void Game(int f); //�ƶ�
void printNumber(); //ˢ�½�������
void ab(int &a,int &b);//�غ�

//��ת���� 
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

//ANSI�ĺ���
void rgbInit(){
	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);//������
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);//������
	DWORD dwInMode, dwOutMode;
	GetConsoleMode(hIn, &dwInMode);//��ȡ����̨����ģʽ
	GetConsoleMode(hOut, &dwOutMode);//��ȡ����̨���ģʽ
	dwInMode |= 0x0200;//����
	dwOutMode |= 0x0004;
	SetConsoleMode(hIn, dwInMode);//���ÿ���̨����ģʽ 
	SetConsoleMode(hOut, dwOutMode);//���ÿ���̨���ģʽ
}

//���÷�����ɫ 
void colorInit(){
	for(int i=1;i<=11;i++){
		int m=1<<i;
		color[m]=old_color[i];
	}
}

//�����ɫRGB��λ�� 
void pr(int w,int b,int x,int y){
	//����RGB 
	int wr=w/0x10000;
	int wg=w/0x100%0x100;
	int wb=w%0x100;
	int br=b/0x10000;
	int bg=b/0x100%0x100;
	int bb=b%0x100;
	printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,br,bg,bb);
	//��ɫȷ��
	//��λ 
    COORD  coord;    
    coord.X=x;         
    coord.Y=y;
    HANDLE a=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,coord);
}

//�򵥵��ַ������ 
void pr(int w,int x,int y,string s){
	pr(w,BLACK,x,y);
	cout<<s;
	pr(W,BLACK,0xffffff,0xffffff);
}

//��ʼ�� 
void init1(){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
	rgbInit();
	colorInit();
	
	
	SetConsoleTitleA("2048��Ϸ");
	CONSOLE_CURSOR_INFO cursorInfo = { 1, FALSE };  // �����Ϣ
}

//��Ϸ���ܳ�ʼ��
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

//ͼ��ʼ�� 
void init3(){
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(handle, &CursorInfo);//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = false; //���ؿ���̨���
	SetConsoleCursorInfo(handle, &CursorInfo);//���ÿ���̨���״̬
	system("cls");
	pr(0x989898,BLACK,0,0);
	printf("�÷�score:\n");
	printf("��ǰ��󷽿�����:"); 
	pr(0x989898,BLACK,0,15);
	printf("�����Ϸ������������⣬�밴 r ���ָ�\n���ո��������Ϸ���˳�");
	pr(0x4169E1,BLACK,36,5);
	printf("��Ϸ˵��");
	pr(0x29CC50,BLACK,36,6);
	printf("ÿ�ο���ѡ��������������һ������ȥ����");
	pr(0x29CC50,BLACK,36,7);
	printf("ÿ����һ�Σ����е����ַ��鶼���������ķ���£");
	pr(0x29CC50,BLACK,36,7);
	printf("ϵͳҲ���ڿհ׵ĵط���������һ�����ַ���");
	pr(0x29CC50,BLACK,36,8);
	printf("��ͬ���ֵķ����ڿ�£����ײʱ�����");
	pr(0x29CC50,BLACK,36,9);
	printf("ϵͳ��������ַ��鲻��2����4");
	pr(0x29CC50,BLACK,36,10);
	printf("Ҫ��취����СС��16��Χ�дճ���2048��������ַ�����Ϸʤ��");	;
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

//���̶��� 
void getKey(int i){
	while(1){
		key = getch();  // ��ȡ����������ַ�
	 	if (key == '\xE0') {  // ����������ַ�(���ͷ��)
	  		key = getch(); // ������ȡһ���ַ�
	  		
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

//ˢ�½�������
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

//��ת���� 
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
//�滻 
void work(){
    for(int i=1;i<=4;i++){
	    for(int j=1;j<=4;j++)
	    	a[i][j]=b[i][j];
	}
}

//�غ�
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

//�ƶ� 
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

//�ж��Ƿ��ܼ���
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

//������Ϸ
void runGame(){
	init2();
	int tu=0,tu4=0;
	now_max=2;
	while(tu<2){
		//��������������
		for(int i=1;i<=4&&tu<2;i++){
			for(int j=1;j<=4&&tu<2;j++){
				if(random(1,1000)==random(2,992)&&a[i][j]==-1){
					if(random(1,10)==1&&tu4==0) a[i][j]=4,tu4=1,now_max=4;
					else a[i][j]=2;
					tu++;
				}
			}
		}	
	}
	game_=1; //������Ϸ
	printNumber();
	init3();
	while(game_==1){
		printNumber();
		getKey(wasd);
		if(key=='r'||key=='R'){
			//����ҳ��
			init3();
			continue;
		}
		if(key==' '){
			//��ͣ����
			int result = MessageBox(NULL, "�Ƿ��������˳�?", "��ʾ", MB_YESNO | MB_ICONQUESTION);
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

		Game(akey[key]); //�ƶ�����
		while(wflag&&tu<1&&!flag){
			//�����µķ���
			flag=1;
			for(int i=1;i<=4&&tu<1;i++){
				for(int j=1;j<=4&&tu<1;j++){
					if(a[i][j]==-1) flag=0;
					if(random(1,1000)==random(5,7)&&a[i][j]==-1){
						if(random(1,10)==1&&tu4==0) a[i][j]=4,tu4=1,now_max=max(now_max,4);
						else a[i][j]=2;
						tu++;
					}
				}
			}
		}
		if(now_max==2048) game_=2; //�ϳ�2048
		else if(isCanRun()) game_=3; //��·����
	}
	printNumber(); 
	if(game_==2){
		pr(BLACK,W,5,7);
		printf("��ϳɳ���2048��\n��esc�˳���Ϸ�����ո�����һ��");
	}
	else if(game_==3){
		pr(BLACK,W,6,7);
		printf("���Ѿ���·���� \n��esc�˳���Ϸ�����ո�����һ��");
	}
	else if(game_==4){
		pr(BLACK,W,8,7);
		printf("��ѡ�������� \n��esc�˳���Ϸ�����ո�����һ��");
	}
	getKey(next1);
}
