#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int table[64];
int diamond[64];
int gold[64];
int trash[64];

int unavailable[64];

int P1Score;
int P2Score;

void clrcon(){
    system("@cls||clear");
}

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

int CheckPlace(int turn, int num,int dnum, int gnum, int tnum){
    int i;
    int score[] = {
        0, 0
    };
    for (i = 0; i < dnum; i++)
        if (num == diamond[i]){
            score[turn - 1] += 1500;
            P1Score += score[0];
            P2Score += score[1];
            return 1;
        }
    for (i = 0; i < gnum; i++)
        if (num == gold[i]){
            score[turn - 1] += 500;
            P1Score += score[0];
            P2Score += score[1];
            return 2;
        }
    for (i = 0; i < tnum; i++)
        if (num == trash[i]){
            score[turn - 1] -= 300;
            P1Score += score[0];
            P2Score += score[1];
            return 3;
        }
    return 0;
}

int CheckAvailable(int num){
    if (unavailable[num-1] == num)
        return 0;
    return 1;
}

void Draw(){
    clrcon();
    printf("\033[0m");
    printf("\t  -------------------------\n");
    printf("\t     \033[1;32mScore Player 1 : %d\033[0m  \n", P1Score);
    printf("\t  -------------------------\n");
    printf("\t     \033[1;31mScore Player 2 : %d\033[0m  \n", P2Score);
    printf("\t  -------------------------\n");
    printf("------------------------------------------------\n");

    int i;
    for (i = 0; i < 64; i++){
        if (i+1 < 10 && CheckAvailable(table[i]) == 1)
            printf("|  %d |", table[i]);
        else if (CheckAvailable(table[i]) == 0)
            printf("| XX |");
        else
            printf("| %d |", table[i]);
        if ((i+1) % 8 == 0)
            printf("\n");
    }
    printf("------------------------------------------------\n");
}

void initial(){
    P1Score = 0;
    P2Score = 0;

    srand ( time(NULL) );

    int i;
    for (i = 0; i < 64; i++){
        table[i] = i + 1;
        unavailable[i] = 0;
    }
}

int main(){

    initial();

    int available = 64;
    int diamond_num;
    do{
        clrcon();
        printf("Choose Number of Diamond [%d upto %d] : ", 0, available);
        scanf("%d", &diamond_num);
    }
    while (diamond_num < 0 || diamond_num > available);
    RandomDiamond(diamond_num);
    available -= diamond_num;

    int gold_num;
    do{
        clrcon();
        printf("Choose Number of Gold [%d upto %d] : ", 0, available);
        scanf("%d", &gold_num);
    }
    while (gold_num < 0 || gold_num > available);
    RandomGold(gold_num, diamond_num);
    available -= gold_num;

    int trash_num;
    do{
        clrcon();
        printf("Choose Number of Trash [%d upto %d] : ", 0, available);
        scanf("%d", &trash_num);
    }
    while (trash_num < 0 || trash_num > available);
    RandomTrash(trash_num, gold_num, diamond_num);
    available -= trash_num;

    int turn = 1;
    int number;
    int which = 0;
    char NArray[][10] = {
        "Diamond", "Gold", "Trash"
    };
    char CArray[][10] = {
        "\033[1;36m", "\033[1;33m", "\033[1;31m"
    };
    while (1){
        do{
            Draw();

            if (which > 0)
                printf("%s!!Previous Player Got %s!!\033[0m\n", CArray[which-1], NArray[which-1]);
            
            printf("Player %d Choose a Number : ", turn);
            scanf("%d", &number);

            if (CheckAvailable(number) == 1)
                which = CheckPlace(turn, number, diamond_num, gold_num, trash_num);
        }
        while (number < 0 || number > 64 || CheckAvailable(number) == 0);

        unavailable[number - 1] = number;

        if (P1Score >= 5000 || P2Score >= 5000)
            break;

        turn += 1;
        if (turn > 2)
            turn = 1;
        
    }
    Draw();
    printf("\033[1;33m=== Player %d WIN ===\033[0m", turn);

    getch();
    
    return 0;
}