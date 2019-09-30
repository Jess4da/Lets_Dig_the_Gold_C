<<<<<<< HEAD
#include <stdio.h>
#include <time.h> //ใช้ในการสุ่ม
#include <stdlib.h> 
#include <conio.h> //ใช้ getch ตอนท้าย

int table[64];  //สร้างตาราง 64 ช่อง
int diamond[64];    //สร้างตารางเก็บเพชร 64 ช่อง
int gold[64];   //สร้างตารางเก็บทอง 64 ช่อง
int trash[64];  //สร้างตารางเก็บขยะ 64 ข่อง

int unavailable[64];    //สร้างตารางเก็บช่องว่าง

//คะแนนของผู้เล่น
int P1Score;
int P2Score;

//จำนวนตาการเล่น
int PTurn[2];

//ฟังก์ชั่นเคลียร์สกรีน
void clrcon(){
    system("@cls||clear");
}

//ฟังก์ชั่นสุ่มตำแหน่งเพชร
void RandomDiamond(int num){
    int i;
    for (i = 0; i < num; i++){
        int ran_num = (rand() % 64) + 1;
        diamond[i] = ran_num;
        int j;
        for (j = 0; j < i; j++){
            if (diamond[j] == ran_num)
                i -= 1;
        }
    }
}

//ฟังก์ชั้นสุ่มตำแหน่งทอง
void RandomGold(int gnum, int dnum){
    int i;
    for (i = 0; i < gnum; i++){
        int ran_num = (rand() % 64) + 1;
        gold[i] = ran_num;
        int j;
        for (j = 0; j < i; j++){
            if (gold[j] == ran_num)
                i -= 1;
        }
        for (j = 0; j < dnum; j++)
            if (diamond[j] == ran_num)
                i -= 1;
    }
}

//ฟังก์ชั่นสุ่มตำแหน่งขยะ
void RandomTrash(int tnum, int gnum, int dnum){
    int i;
    for (i = 0; i < tnum; i++){
        int ran_num = (rand() % 64) + 1;
        trash[i] = ran_num;
        int j;
        for (j = 0; j < i; j++){
            if (trash[j] == ran_num)
                i -= 1;
        }
        for (j = 0; j < gnum; j++)
            if (gold[j] == ran_num)
                i -= 1;
        for (j = 0; j < dnum; j++)
            if (diamond[j] == ran_num)
                i -= 1;
    }
}

//ฟังก์ชั่นเช็คการวางหมาก
int CheckPlace(int turn, int num,int dnum, int gnum, int tnum){
    int i;
    int score[] = {
        0, 0
    };
    //ลูปเช็คว่าตำแหน่งที่วางหมากนั้นเจอเพชรหรือไม่
    for (i = 0; i < dnum; i++)
        if (num == diamond[i]){
            score[turn - 1] += 1500;
            P1Score += score[0];
            P2Score += score[1];
            return 1;
        }
    //ลูปเช็คว่าตำแหน่งที่วางหมากนั้นเจอทองหรือไม่
    for (i = 0; i < gnum; i++)
        if (num == gold[i]){
            score[turn - 1] += 500;
            P1Score += score[0];
            P2Score += score[1];
            return 2;
        }
    //ลูปเช็คว่าตำแหน่งที่วางหมากนั้นเจอขยะหรือไม่
    for (i = 0; i < tnum; i++)
        if (num == trash[i]){
            score[turn - 1] -= 300;
            P1Score += score[0];
            P2Score += score[1];
            return 3;
        }
    return 0;
}

//ฟังก์ชั่นเช็คว่าช่องนั้นว่างหรือเปล่า
int CheckAvailable(int num){
    if (unavailable[num-1] == num)
        return 0;
    return 1;
}

//ฟังก์ชั่นวาดตารางออกมา
void Draw(){
    clrcon();
    printf("\033[0m");
    printf("\t  -------------------------\n");
    printf("\t     \033[1;32mScore Player 1 : %d\033[0m  \n", P1Score);
    printf("\t  -------------------------\n");
    printf("\t     \033[1;31mScore Player 2 : %d\033[0m  \n", P2Score);
    printf("\t  -------------------------\n");
    printf("Player 1:%d Turn Left\t   Player 2:%d Turn Left\n", PTurn[0], PTurn[1]);
    printf("------------------------------------------------\n");

    int i;
    for (i = 0; i < 64; i++){
        if (i+1 < 10 && CheckAvailable(table[i]) == 1)
            printf("|  %d |", table[i]);
        else if (CheckAvailable(table[i]) == 0)
            printf("|\033[1;31m XX \033[0m|");
        else
            printf("| %d |", table[i]);
        if ((i+1) % 8 == 0)
            printf("\n");
    }
    printf("------------------------------------------------\n");
}

//ฟังก์ชั่นตั้งค่าโปรแกรมเริ่มต้น
void initial(){
    P1Score = 0;
    P2Score = 0;
    
    PTurn[0] = 20;
    PTurn[1] = 20;

    srand ( time(NULL) );

    int i;
    for (i = 0; i < 64; i++){
        table[i] = i + 1;
        unavailable[i] = 0;
    }
}

void delay(int number_of_seconds) 
{ 
    int milli_seconds = 1000 * number_of_seconds; 
  
    clock_t start_time = clock(); 

    while (clock() < start_time + milli_seconds) 
        ; 
} 


int main(){

    initial();  //เรียกใช้ฟังก์ชั่นเซตค่าเริ่มต้น

    int available = 64;
    int diamond_num;
    //ลูปเพื่อใส่ค่าจำนวนเพชร
    do{
        clrcon();
        printf("Choose Number of Diamond [%d upto %d] : ", 0, available);
        scanf("%d", &diamond_num);
    }
    while (diamond_num < 0 || diamond_num > available);
    RandomDiamond(diamond_num);     //เรียกใช้ฟังก์ชั่นสุ่มตำแหน่งเพชรตามจำนวนที่รับมา
    available -= diamond_num;       //ช่องว่างของตาราง - จำนวนเพชร

    int gold_num;
    //ลูปเพื่อใส่ค่าจำนวนทอง
    do{
        clrcon();
        printf("Choose Number of Gold [%d upto %d] : ", 0, available);
        scanf("%d", &gold_num);
    }
    while (gold_num < 0 || gold_num > available);
    RandomGold(gold_num, diamond_num);  //เรียกใช้งานฟังกฺชั่นสุ่มตำแหน่งทองตามจำนวนที่รับมา
    available -= gold_num;      //ช่องว่างที่เหลื่อเท่ากับลบด้วยจำนวนทอง

    int trash_num;
    //ลูปเพื่อใส่่ค่าจำนวนขยะ
    do{
        clrcon();
        printf("Choose Number of Trash [%d upto %d] : ", 0, available);
        scanf("%d", &trash_num);
    }
    while (trash_num < 0 || trash_num > available);
    RandomTrash(trash_num, gold_num, diamond_num);  //เรียกใช้ฟังก์ชั่นสุ่มตำแหน่งขยะตามจำนวนที่รับมา
    available -= trash_num;     //ช่องว่างที่เหลือเท่ากับลบด้วยจำนวนขยะ

    int turn = 1;
    int number;
    int which = 0;

    //สร้างอาเรย์เก็บค่าสตริง
    char NArray[][10] = {
        "Diamond", "Gold", "Trash"
    };
    //สร้างอาเรย์เก็บโค้ดสี
    char CArray[][10] = {
        "\033[1;36m", "\033[1;33m", "\033[1;31m"
    };
    //ลูปเล่นเกม

    while (PTurn[0] > 0 && PTurn[1] > 0){
        //ลูปวาดตารางและใส่ค่า
        do{ 
            Draw(); //เรียกฟังก์ชั่นวาดตาราง

            if (which > 0)
                printf("%s!!Previous Player Got %s!!\033[0m\n", CArray[which-1], NArray[which-1]);

            printf("Player %d Choose a Number : ", turn);
            scanf("%d", &number);

            //เรียกใช้ฟังก์ชั่นเช็คช่องว่าง
            if (CheckAvailable(number) == 1)
                which = CheckPlace(turn, number, diamond_num, gold_num, trash_num); //เรียกฟังก์ชั่นวางหมากลงตาราง
        }
        while (number < 0 || number > 64 || CheckAvailable(number) == 0);

        unavailable[number - 1] = number;

        //ถ้าคะแนนใครมากกว่า 5000 จะหยุดลูป
        if (P1Score >= 5000 || P2Score >= 5000)
            break;

        //สลับเทิร์นของผู่เล่น
        PTurn[turn-1] -= 1;
        turn += 1;
        if (turn > 2)
            turn = 1;
        
    }
    Draw();
    
    if (P1Score > P2Score)
        printf("\033[1;33m=== Player 1 WIN ===\033[0m\n");
    else if (P2Score > P1Score)
        printf("\033[1;33m=== Player 2 WIN ===\033[0m\n");
    else
        printf("\033[1;33m=== DRAW ===\033[0m\n", turn);
    
    printf("Press any key to continue...");

    getch();
    
    return 0;
}
=======

>>>>>>> 93886bbb3c2c7ed13ce860cd6fdbf76c195742d4
