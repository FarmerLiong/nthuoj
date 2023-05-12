#include<stdio.h>
#if !defined(N)
#define N 3
#endif

int main(void)
{
    int mat[N][N];
    int sgn, det, i, j, k=0, l;
    int A[N], D[N], flag=1;
    int max, maxidx;
    int tmp, tmpidx;

    for(i=0; i<N; i++){
        for(j=0; j<N; j++){
            scanf("%d",  &mat[i][j]);
        }
    }

    printf("Input matrix is\n");
    for(i=0; i<N; i++){
        printf("  ");
        for(j=0; j<N; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }

    for(j=0; j<N; j++){
        A[j] = j;
        D[j] = -1;
    }

    sgn = 1;
    while(flag){
        max = 0; flag = 0;
        det = 1;
        for(j=0; j<N; j++){
            tmp = 0;
            tmpidx = 0;
            if(j>0 && D[A[j]-1]<0 && A[j]>A[j-1]){
                tmp = A[j];
                tmpidx = j;
                flag = 1;
            }
            else if(j<N-1 && D[A[j]-1]>0 && A[j]>A[j+1]){
                tmp = A[j];
                tmpidx = j;
                flag = 1;
            }
            if(tmp > max){
                max = tmp;
                maxidx = tmpidx;
            }

            det *= mat[j][A[j]];
            det = det*sgn;
        }
        sgn = sgn*-1;

        if(D[max - 1] < 0){
            A[maxidx] = A[maxidx-1];
            A[maxidx-1] = max;
        }
        else if(D[max - 1] > 0){
            A[maxidx] = A[maxidx+1];
            A[maxidx+1] = max;
        }

        for(j=0; j<N; j++){
            if(A[j] > max){
                D[A[j]-1] *= -1;
            }
        }
        k += det;
    }
    printf("Det = %d\n", k);

    return 0;
}