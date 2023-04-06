#include <stdio.h>
#define N 3

int main (void){
    int A[N], D[N];
    int max = 0, maxidx = 0, flag = 1;
    
    for(int i = 0; i < N; i++){
        A[i] = i + 1;
        D[i] = -1;
    }
    
    while(flag){
        flag = 0, max = 0;
        for(int i = 0; i < N; i++){         //1: largest mobile num, max
            int tmp = 0, tmpidx = 0;
            if(i > 0 && D[A[i] - 1] < 0 && A[i] > A[i-1]){
                tmp = A[i];
                tmpidx = i;
                flag = 1;
            }
            else if(i < N-1 && D[A[i] - 1] > 0 && A[i] > A[i+1]){
                tmp = A[i];
                tmpidx = i;
                flag = 1;
            }
            if(tmp > max){
                max = tmp;
                maxidx = tmpidx;
            } 
            printf(" %d", A[i]);
        }

        // swapping
        if(D[max - 1] < 0){
            A[maxidx] = A[maxidx - 1];
            A[maxidx - 1] = max;
        }
        else if(D[max - 1] > 0){
            A[maxidx] = A[maxidx + 1];
            A[maxidx + 1] = max;
        }
        
        for(int i = 0; i < N; i++){
            if(A[i] > max){
                D[A[i] - 1] *= -1;
            }
        }
        printf("\n");
    }
    return 0;
}
