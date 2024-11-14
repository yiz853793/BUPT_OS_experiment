#include<stdio.h>

int main(){
    int a = 0;
    while(true){
        a++;
        putchar((a % 10) ^ 0x30);
    }
    return 0;
}