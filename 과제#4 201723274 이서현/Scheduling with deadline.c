#include <stdio.h>

typedef struct{
    int job;
    int deadline;
    int profit;
}job_node;

job_node J[110];
job_node in;

int feasible(job_node K[], int n){  //test feasible
    int result=0;
    for(int i=1;i<=n;i++){
        if(K[i].deadline>=i){result=1;} //if true, return 1
        else {result=0;break;}          //if false, return 0
    }
    return result;
}

void schedule(int n){
    job_node result[110];
    int r_L=2;    //length of result
    int sum=0;
    result[1]=J[1];
    
    for(int i=2;i<=n;i++,r_L++){
        //insert sorting
        J[0]=J[i]; int j=r_L-1;
        while(J[0].deadline<J[j].deadline){
            J[j+1]=J[j]; j--;
        }J[j+1]=J[0];
        
        if(feasible(J, r_L)){ //true
            for(int l=1;l<=r_L;l++) //Copy J to result
                result[l]=J[l];
            
        }
        else{  //false
            for(int l=1;l<r_L;l++)  //Discard the newly added data
                J[l]=result[l];
            r_L--;
        }
        
    }
    for(int i=1;i<r_L;i++)  //Add all of profits of J.
        sum+=result[i].profit;
    printf("%d",sum);
    
    for(int i=1;i<r_L;i++)
        printf(" %d",result[i].job);
    
}

int main(){
    int n;
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++)
        scanf("%d %d %d",&J[i].job,&J[i].deadline,&J[i].profit);
    
    schedule(n);
}

