#include <stdio.h>
float A[110][110]={0,}; //average search time
int R[110][110]={0,};  //number of Key

void optsearchtree(int n,float p[]){
    int i,j,k,dia;
    float sumP=0;
    
    for(i=1;i<=n;i++){  //initialize
        A[i][i-1]=0;
        A[i][i]=p[i];
        R[i][i]=i;
        R[i][i-1]=0;
    }
    A[n+1][n]=0;
    R[n+1][n]=0;
    
    for(dia=1;dia<=n-1;dia++){
        for(i=1;i<=n-dia;i++){
            j=i+dia;
            float min=1000;
            for(int m=i;m<=j;m++){ //Sum of pm (i<=m<=j)
                sumP+=p[m];
            }
            for(k=i;k<=j;k++){
                if(min>A[i][k-1]+A[k+1][j]){
                    min=A[i][k-1]+A[k+1][j]; //minimum(A[i][k-1]+A[k+1][j]) (i<=k<=j)
                    R[i][j]=k;  //a value of k that gave the minimum
                }
            }
            A[i][j]=min+sumP;
            sumP=0;
        }
    }
    
    printf("%.3f",A[1][n]);
}

void tree (int i, int j){ //Print preorder traversal of optimal tree
    int k;

    k=R[i][j];
    if(k==0);
    else{
        printf(" %d",R[i][j]);
        tree(i, k-1);
        tree(k+1,j);
    }
    
}


int main(){
    int n;
    scanf("%d",&n);
    
    float p[110]={0,};
    for(int i=1;i<=n;i++){
        scanf("%f",&p[i]);
    }
    
    optsearchtree(n,p);
    tree(1,n);
    
}
