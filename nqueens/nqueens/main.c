/*첫 번째 solution이 담겨있는 배열 col,
 backtracking algorithm이 탐색한 state space tree의 노드의 개수,
 promising nodes의 개수,
 모든 solution의 개수
 */

#include <stdio.h>
#include <stdlib.h>
int col[200];
int n;
int pro_n,sol_n,sst_n=0;
int hasSol=1;

int promissing(int i){
    int k; int swit;
    k=1;
    swit=1;
    while(k<i&&swit){
        if(col[i]==col[k]||abs(col[i]-col[k])==(i-k)){
            swit=0;
        }
        k++;
    }
    
    return swit;
}


void queens(int i){
    int j; sst_n++;
    if(promissing(i)){
        pro_n++;
        if(i==n){
            sol_n++;
            if(sol_n==1)
              for(int k=1;k<=n;k++){
                printf("%d ",col[k]);
               }
            hasSol=0;
        }
        else{
            for(j=1;j<=n;j++){
                col[i+1]=j;
                queens(i+1);
            }
        }
        
    }
}

int main(){

    scanf("%d",&n);
    
    queens(0);
    if(hasSol){ printf("No solution"); return 0;}
    printf("%d %d %d",sst_n,pro_n,sol_n);
    
    return 0;
}
