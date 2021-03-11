#include <iostream>
#include <cstdio>
#include <queue>
using namespace std;

typedef struct {
    int level;
    int path[100];
    int bound;
    int visited[100];
}node;
priority_queue<node,vector<node>> PQ;

int W[100][100]; int n;

void initialize(){
    if(PQ.empty()){
        return;
    }
    else{
        while(!PQ.empty()){
            PQ.pop();
        }
    }
}

int bound(node u){
    int i,w = 0;
    int bound=0;
    int bvisit[100]={0,};
    for(i=0;i<u.level;i++){
        bound+=W[u.path[i]][u.path[i+1]];
        u.visited[u.path[i]]=1; u.visited[u.path[i+1]]=1;
        bvisit[u.path[i]]=1; bvisit[u.path[i+1]]=1;
        w=u.path[i+1];
    }
    int min=10000; int n_min=0;
    for(i=u.level+1;i<=n;i++){
        
        for(int j=1;j<=n&&!bvisit[j];j++){
            if(min>W[w][j]){ min=W[w][j]; n_min=j; }
        }
        w=n_min; bound+=min; bvisit[w]=1;
    }
 
    
    return bound;
}

int length(node u){
    int leng=0;
    for(int i=0;i<n;i++)
        leng+=W[u.path[i]][u.path[i+1]];
    
    return leng;
}

void tsp( int minlength){
    node u,v;
    initialize();
    v.path[0]=1;
    v.visited[1]=1;
    v.bound=bound(v);
    minlength=100000;
    PQ.push(u);
    
    while(!PQ.empty()){
        v=PQ.pop();
        if(v.bound<minlength){
            u.level=v.level+1;
            for(int i=2;i<=n&&!v.visited[i];i++){
                for(int j=0;j<u.level;j++)
                    u.path[j]=v.path[j];
                u.path[u.level]=i;
                
                if(u.level==n-2){
                    for(int w=2;w<=n;w++)
                        if(!u.visited[w]){
                            u.path[u.level+1]=w;
                            u.path[u.level+2]=1; break;
                        }
                    if(length(u)<minlength){
                        minlength=length(u);
                        //opttour=u.path;
                    }
                }
                
                else{
                    u.bound=bound(u);
                    if(u.bound<minlength)
                        PQ.push(u);
                }
            }
            
        }
        

    }
}

void in(){
    scanf("%d",&n);
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",&W[i][j]);
}

int main(){

    in();
    int opt[100]; int ml = 0;
    tsp(ml);
    
}
