#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int *find_bad_coin(int *coins, int n);
int main(int argc, char *argv[])
{
    int i, n, fake;
    int *coins, *find_bad_coin;
    n = atoi(argv[1]);

    srand(time(NULL));
    coins = (int *) malloc( (n+1) * sizeof(int));

    for(i = 0; i < n + 1; i++) // 여분 짝수로 
        coins[i] = 10;;

    fake=rand()%n;//가짜동전의 위치
        coins[fake]=5;

    bad_coin=find_bad_coin(coins,n);
    printf("coins[%d]=%d:,coins[%d]=%d\n", fake,coins[fake],(int)(bad_coin-coins),*bad_coin);
}

int *find_bad_coin(int *coins, int n){
    int i, mid = (n + 1) / 2, sum1 = 0, sum2 = 0, *coins2;

    static int count = 0;

    if(n <= 1){
        printf("Found it! with %d iteration", count);
        return coins; // (coins[0] < coins[1]) ? coins : coins + 1;
    }

    coins2 = coins + mid;
    
    for(i = 0; i < mid; i++){
        sum1 += coins[i];
        sum2 += coins2[i];
    }

    count++;

    if(sum1 < sum2)
        return find_bad_coin(coins, mid);
    else
        return find_bad_coin(coins2, mid);
}