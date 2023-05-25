// Header File
#include<stdio.h> 			// 입출력 관련 
#include<stdlib.h> 			// 문자열 변환, 메모리 관련 
#include<unistd.h> 			// POSIX 운영체제 API에 대한 액세스 제공 
#include<fcntl.h> 			// 타겟시스템 입출력 장치 관련 
#include<sys/types.h> 			// 시스템에서 사용하는 자료형 정보 
#include<sys/ioctl.h> 			// 하드웨어의 제어와 상태 정보 
#include<sys/stat.h> 			// 파일의 상태에 대한 정보 
#include <string.h> 			// 문자열 처리 
#include <time.h> 			// 시간 관련 

// Target System
#define fnd "/dev/fnd" 		// 7-Segment FND 
#define dot "/dev/dot" 		// Dot Matrix
#define tact "/dev/tactsw" 	// Tact Switch
#define led "/dev/led" 		// LED 
#define dip "/dev/dipsw"	// Dip Switch
#define clcd "/dev/clcd" 	// Character LCD

// 카드관련 전역 변수 설정
#define CARD_NUM 13

// 함수 전역변수 설정
int looptime(int s, int end);
int BETTING_START();
void PRINT(char p[]);
void shuffle_card(int* cards);
void prepare(int* cards1, int* cards2);
int compare_card(int com_card, int user_card);
int win_lose(int user_answer, int correct_answer);
void WIN_LED(int user_win);
void start(int* cards1, int* cards2);



// 장치들 전역 변수 설정
int dipsw;
int leds;
int dot_mtx;
int tactsw;
int clcds;
int fnds;


//카드 관련 전역 변수 설정 
int usercards[CARD_NUM] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
int comcards[CARD_NUM] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};


// fnd led 관련 전역 변수 설정
unsigned char fnd_num[4] = {0,};
unsigned char Time_Table[] = {~0x3f, ~0x06, ~0x5b, ~0x4f, ~0x66, ~0x6d, ~0x7d, ~0x07, ~0x7f, ~0x67, ~0x00};


// switch 장치들 입력 변수(확인용)
// dipswitch를 조작하거나 tactswitch를 이용해 베팅했을 때 리턴해주기 위함
unsigned char d;  // dip switch 값 변수
unsigned char t;  // tact switch 값 변수


// 게임 시작 시 CLCD에 출력하는 함수(Dip Switch를 조작해야 0 리턴)
int INTRO(){
	clcds = open(clcd, O_RDWR);
	if(clcds < 0){
    printf("Can't open Character LCD.\n"); 
    exit(0);
  }


	char pr_clcd[40] = " PRESS ANY KEY!  USE DIP SWITCH ";
	write(clcds, pr_clcd, strlen(pr_clcd));  usleep(2000000);
	close(clcds);

	// fnd Led 10초

   // dip switch 입력했냐 안 했냐
	while(1){
		dipsw = open(dip, O_RDWR);
		if (dip < 0) {printf("Can't open Dip Switch\n"); exit(0);}
		read(dipsw, &d, sizeof(d));
		close(dipsw);
		
	  	if (d != 0){
	  		return 1;
		}
	}
}


int BETTING_START(int com_card){
      // fnd 10초 시작
   PRINT(" PLEASE BETTING  USE TACTSWITCH ");  usleep(2000000);
      // dotmatrix 출력
      printf("dotmatrix: %d",com_card);
      // tactswitch 베팅 입력
	  int user_answer = tactsw_get_with_timer(10);
      // return 베팅 입력값
      return user_answer;
}


// 베팅 전 CLCD에 출력하는 함수(Tact Switch를 조작해야 t값 리턴)
// int BETTING_PRINT(){
// 	clcds = open(clcd, O_RDWR);
// 	if(clcds < 0){
//     printf("Can't open Character LCD.\n"); 
//     exit(0);
//   }
// 	char pr_clcd[40] = " PLEASE BETTING  USE TACTSWITCH ";
// 	write(clcds, pr_clcd, strlen(pr_clcd));
// 	close(clcds);
	
// 	while(1){
// 		tactsw = open(tact, O_RDWR);
// 		if (tact < 0) {printf("Can't open tact Switch\n"); exit(0);}
// 		read(tactsw, &t, sizeof(t));
// 		close(tactsw);
		
// 	  	if (t != 0){
// 	  		return t;
// 		}
// 	}
// }

// CLCD 기본 출력 함수 
void PRINT(char P[]){
	clcds = open(clcd, O_RDWR);
	if(clcds < 0){printf("Can't open Character LCD.\n"); exit(0);}
	write(clcds, P, strlen(P));
	close(clcds);
}


//카드 섞기 함수
void shuffle_card(int* cards){
   srand(time(NULL));
   int temp;
   int rn;
   int i; 
   for( i = 0; i < CARD_NUM; i++){
      rn = rand() % CARD_NUM;
      while (rn == i) {
         rn = rand() % CARD_NUM;
      }
      temp = cards[i];
      cards[i] = cards[rn];
      cards[rn] = temp;
   }
}

// 게임 준비 함수
void prepare(int* cards1, int* cards2){
  //  print_card(cards1);
  //  print_card(cards2);
   shuffle_card(cards1);
   shuffle_card(cards2);
   shuffle_card(cards2); // 다르게 섞이기 위해 한 번 더 셔플
  //  print_card(cards1);
  //  print_card(cards2);
}

//게임 카드 비교 함수   
int compare_card(int com_card, int user_card){
   if(com_card==user_card){
      return 1;
   }
   else if(com_card>user_card){
      return 2;
   }
   else{
      return 3;
   }
}

//게임 OX반환 함수      
int win_lose(int user_answer, int correct_answer){
   if(user_answer == correct_answer){
      return 1;
   }
   else{
      return 0;
   }
}


// Chip LED를 이용한 승리 수 점등 함수
void WIN_LED(int user_win) {
    leds = open(led, O_RDWR);
    if (leds < 0) {
        printf("Can't open LED.\n");
        exit(0);
    }

    unsigned char data = 0xFF;
    int i;
    for (i = 0; i < user_win; i++) {
        data &= ~(1 << i);  // 해당 비트(LED)를 0으로 설정하여 켜기
    }

    write(leds, &data, sizeof(unsigned char));
    close(leds);        // 이거 하면 뭔가 꺼질거 같은데
}


// 게임 시작 함수
void start(int* cards1, int* cards2){
  int ROUND = 13;
  int com_score = 0;
  int user_score = 0;

  char round_clcd[32];
  char score_clcd[32];

  INTRO();

  PRINT("      GAME           START!     ");  usleep(2000000);
  PRINT("  INDIAN  GAME     GAME  RULE   ");  usleep(2000000);
  PRINT("     ON THE       TACT  SWITCH  ");  usleep(2000000);
  PRINT("  FIRST BUTTON    PLAYER = COM  ");  usleep(2000000);
  PRINT(" SECOND  BUTTON   PLAYER < COM  ");  usleep(2000000);
  PRINT("  THIRD BUTTON    PLAYER > COM  ");  usleep(2000000);

 	int i;
  for(i = 0; i < ROUND; i++){

    int com_card = cards1[i];
    int user_card = cards2[i];
    
    sprintf(round_clcd, "    ROUND  %d         START!     ", i+1);
    PRINT(round_clcd);  usleep(2000000);

    int user_answer = BETTING_START(com_card);         // 베팅 값 저장

    int correct_answer = compare_card(com_card, user_card);    // 카드 비교 결과 저장
    // com_dot_matrix(com_card);

    if(win_lose(user_answer, correct_answer)){           // 베팅 결과 확인
        user_score++;
        PRINT("     PLAYER           WIN!      "); usleep(2000000);
        WIN_LED(user_score);  // 유저 승리 수 만큼 LED 점등
    }
    else{
        com_score++;
        PRINT("     PLAYER           LOSE      "); usleep(2000000);
    }

    // 스코어 공개
    sprintf(score_clcd, "PLAYER SCORE = %d COM  SCORE = %d ", user_score, com_score);
    PRINT(score_clcd);  usleep(2000000);

    //사용자 카드 공개
    // user_dot_matrix(user_card);

    if(user_score>=7){
      PRINT("   GAME CLEAR      PLAYER WIN   ");   usleep(2000000);
      break;
    }
    if(com_score>=7){
      PRINT("   GAME  OVER     PLAYER  LOSE  ");   usleep(2000000);
        break;
    }
  }
}


//입력된 시간(초) 동안 tactsw가 0.01초마다 값을 읽고(10초입력시 1000번 읽음), 1초마다 fnd에 남은 제한시간을 출력하는 함수 //반환값 0: 입력없음 1~3: 입력값 4~12: 무시 
int tactsw_get_with_timer(int t_second) 
{   
	int selected_tact = 0;
	unsigned char b=0;
	int tactsw; 
	//tact switch 제한 시간이 0초 이하일 경우 입력값 없음 
	if(t_second <= 0){
		return 0;
	}
	
	if((tactsw = open( tact, O_RDWR )) < 0){     	// 예외처리    
		printf("tact open error");
		return 0;
	}
	
	int i,j;
	for(i = t_second; i>-1;i--){
		for(j = 100; j>0;j--){
			usleep(10000); //0.01 초 쉬기 
            read(tactsw, &b, sizeof(b));
            //printf("입력중 %u \n", b);
            	if(1<=b && b<=12){
            		switch (b){
					case 1:  selected_tact = 1 ; break;
					case 2:  selected_tact = 2 ; break;
					case 3:  selected_tact = 3 ; break;
					case 12: 
					{
					//12눌렀을 때 이전에 1이나 2나 3을 눌렀을 경우 
					if(selected_tact==1 ||selected_tact==2||selected_tact==3){
						printf("tactswitch 입력값: %d\n", selected_tact);
						return selected_tact;
					}
					//12를 먼저 누를 경우 
					else printf("press 12 after press 1 or 2 or 3\n");
					}
					//4~12무시 
					default: printf("press other key\n"); break; 		            
				}	
				}
		
		}//1초 지남 = 0.01초*100번 
		printf("%d초\n",i);
		
	}
	close(tactsw);
	return 0; //제한시간 끝	
}

int main(){
  if(INTRO()){
    prepare(usercards, comcards);
    start(usercards, comcards);
  }
  return 0;
}
