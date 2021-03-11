#include <stdio.h>
typedef struct {
    int job;
    int dl;
}jobnode;

jobnode K[101];
int feasible(jobnode K[], int n){
    int result=0;
    for(int i=1;i<=n;i++){
        if(K[i].dl>=i){result=0;}
        else {result=i;break;}
    }
    
    return result;
}

void schedule(int n, int deadline[],int profit[]){
    int i; int J[101]={0,}; int sum=0; int klength=2;
    J[1]=1; K[1].job=1; K[1].dl=deadline[1];
    
    for(i=2;i<=n;i++,klength++){
        //insert sorting
        int j=klength-1;
        K[0].dl=deadline[i]; K[0].job=i;
        while(K[0].dl<K[j].dl){
            K[j+1]=K[j];
            j--;
        }K[j+1]=K[0];
        int f=feasible(K, klength);
        if(!f){
            for(int w=1;w<=i;w++)
                J[w]=K[w].job;
        }
        else{
            for(int y=f;y<i;y++)
                K[y]=K[y+1];
            klength--;
        }

    }
    
    for(i=1;i<klength;i++)
        sum+=profit[J[i]];
    printf("%d",sum);
     for(i=1;i<klength;i++)
         printf(" %d",J[i]);
}

int main(){
    int n,job = 0; int deadline[101]={0,}; int profit[101]={0,};
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++)
        scanf("%d %d %d",&job,&deadline[i],&profit[i]);
    
    schedule(n, deadline,profit);
}
