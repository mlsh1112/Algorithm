
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 10000
#define FULL(n) (n==MAX_ELEMENT-1)
#define EMPTY(n) (!n)
typedef struct{
    int level;
    int path[MAX_ELEMENT];
    int bound;
    int visited[MAX_ELEMENT];
}node;

int n; int W[15][15]; int heapN=0;
node pq[MAX_ELEMENT]={0,};

void push(node u){
    int i;
//    if(FULL(heapN)){
//        fprintf(stderr, "The heap is full.");
//        exit(EXIT_FAILURE);
//    }
    i=++heapN;
    while((i!=1)&&(u.bound<pq[i/2].bound)){
        pq[i]=pq[i/2];
        i/=2;
    }
    pq[i]=u;
    
}

node pop(){
    int parent, child;
    node u, temp;
    
    if(EMPTY(heapN)){
        fprintf(stderr, "The heap is empty.");
        exit(EXIT_FAILURE);
    }
    u=pq[1];
    temp=pq[heapN--];
    parent=1;
    child=2;
    
    while(child<=heapN){
        if((child<heapN)&&(pq[child].bound>pq[child+1].bound)) child++;
        if(temp.bound<=pq[child].bound) break;
        
        pq[parent]=pq[child];
        parent=child;
        child*=2;
    }
    pq[parent]=temp;
    return u;
    
}

int bound(node u){
    int i,w = 0;
    int bound=0;
    int bvisit[100]={0,}; //bvisit[1]=1;
    for(i=0;i<u.level;i++){
        bound+=W[u.path[i]-1][u.path[i+1]-1];
        u.visited[u.path[i]]=1; u.visited[u.path[i+1]]=1;
        bvisit[u.path[i]]=1; bvisit[u.path[i+1]]=1;
    }
    w=u.path[u.level];
    bvisit[1]=0;
    
    for(i=u.level+1;i<=n;i++){
        int min=10000;
        for(int j=1;j<=n;j++){
            if(i==j) continue;
            if(u.level==1&&i==u.level+1&&j==1) continue;
            if(!bvisit[j])
                if(min>W[i-1][j-1])
                    min=W[i-1][j-1];
        }
        bound+=min;
    }
    
       
       return bound;
}

int length(node u){
    int leng=0;
    for(int i=0;i<n;i++)
        leng+=W[u.path[i]-1][u.path[i+1]-1];
       
    return leng;
}

void tsp(){
    node u={0,},v={0,};
    int opttour[100];
    v.level=0;
    v.path[0]=1;
    v.visited[1]=1;
    v.bound=bound(v);
    int minlength=100000;
    push(v);
    
    while(!EMPTY(heapN)){
        pop();
        if(u.bound<minlength){
            u.level=v.level+1;
            for(int i=2;i<=n;i++){
                if(!u.visited[i]){
                //for(int j=0;j<u.level;j++)
                  //  u.path[j]=v.path[j];
                *(u.path)=*v.path; *u.visited=*v.visited;
                    u.path[u.level]=i;
                    u.visited[u.path[u.level]]=1;
                    if(u.level==n-2){
                        int j=1;
                        for(;j<=n;j++)
                            if(!u.visited[j])
                                u.path[u.level+1]=j;
                        u.path[u.level+2]=1;
                        if(length(u)<minlength){
                            minlength=length(u);
                            for(int w=0;w<=n;w++)
                                opttour[w]=u.path[w];
                        }
                    }
                    else{
                        u.bound=bound(u);
                        if(u.bound<minlength)
                            push(u);
                        
                    }
                    u.visited[u.path[u.level]]=0;

              }
            }
        }
    }
    printf("%d\n",minlength);
    for(int i=0;i<=n;i++)
        printf("%d ",opttour[i]);
}

void in(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&W[i][j]);
}

int main(){
    in();
    tsp();
}
