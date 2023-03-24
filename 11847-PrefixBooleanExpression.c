#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    char data;
    struct _node *left, *right;
} BTnode;

char table[5][20] = {{"0000000011111111"}, {"0000111100001111"}, {"0011001100110011"}, {"0101010101010101"}};
char input[32];
int pos = 0;

int calcBT(int ans, int idth){
    char c = input[pos++];
    if(c == '&' || c == '|'){
        if(c == '&')  ans = calcBT(ans, idth) & calcBT(ans,idth);
        else if(c == '|')  ans = calcBT(ans, idth) | calcBT(ans,idth);
    }
    else if(c >= 'A' && c <= 'D')
        return (table[c - 'A'][idth] - '0');
    return ans;
}

int main(){
    scanf("%s", input);
    for(int i = 0; i < 16; i++){
        pos = 0;
        for(int j = 0; j < 4; j++) printf("%d ", table[j][i] - '0');
        printf("%d\n", calcBT(0, i));
    }
    return 0;
}