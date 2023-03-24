#include <stdio.h>

int main(){
    char c;
    int numVar = 0b0000;
    scanf("%c", &c);
    numVar = numVar | (1 << (c - 'A'));
    printf("%c", '1' & '0');
    return 0;
}

