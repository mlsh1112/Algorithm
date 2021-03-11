#include <stdio.h>

int m, n;   //m is length of x sequence, n is length of y sequence
char x[110];
char y[110];
float gap_p, mis_p;
float opt[110][110];
char x_r[110], y_r[110] = { 0, };
//x_r is optimal alignment of x sequence, y_r is optimal alignment of y sequence.

typedef struct {
    int r;
    int c;
}visited;

visited v[200];

void sequencealignment() {
    int i, j; float penalty;
    v[0].r=m; v[0].c=n; int k=0;
    
    for (int w = 0; w <= m+1; w++) opt[w][n+1] = 10000;
    for (int k = 0; k <= n+1; k++)opt[m+1][k] = 10000;

    for (i = m; i >= 0; i--) {
        for (j = n; j >= 0; j--) {
            if (i == m)  //initialize
                opt[i][j] = gap_p * (n - j);
            else if (j == n)  //initialize
                opt[i][j] = gap_p * (m - i);
            else {
                //The order of inputted is opt[i+1][j+1], opt[i+1][j], and opt[i][j+1].
                if (x[i] == y[j])
                    penalty = 0;
                else
                    penalty = mis_p;


                if (opt[i + 1][j + 1] + penalty < opt[i + 1][j] + gap_p) {
                    if (opt[i + 1][j + 1] + penalty < opt[i][j + 1] + gap_p) { //When opt[i+1][j+1]+penalty is the smallest
                        opt[i][j] = opt[i + 1][j + 1] + penalty;
                        if(v[k].c==j+1&&v[k].r==i+1){
                            v[++k].r=i-1; v[k].c=j-1;
                            x_r[k]=x[i]; y_r[k]=y[j];
                        }
                    }
                    else{                                         //When opt[i][j+1]+gap_p is the smallest
                        opt[i][j] = opt[i][j + 1] + gap_p;
                        if(v[k].c==j+1&&v[k].r==i){
                            v[++k].r=i; v[k].c=j-1;
                            x_r[k]='-'; y_r[k]=y[j];
                        }
                    }
                } //end of if(opt[i+1][j+1]+penalty<opt[i+1][j]+gap_p)
                else {
                    if (opt[i + 1][j] + gap_p < opt[i][j + 1] + gap_p) {    //When opt[i+1][j]+gap_p is the smallest
                        opt[i][j] = opt[i + 1][j] + gap_p;
                        if(v[k].c==j&&v[k].r==i+1){
                            v[++k].r=i-1; v[k].c=j;
                            x_r[k]=x[i]; y_r[k]='-';
                        }
                    }
                    else {                                       //When opt[i][j+1]+gap_p is the smallest
                        opt[i][j] = opt[i][j + 1] + gap_p;
                        
                        if(opt[i][j+1]==opt[i+1][j]){
                            if((v[k].c==j&&v[k].r==i+1)||(v[k].c==j+1&&v[k].r==i)){
                               v[++k].r=i; v[k].c=j-1;
                               x_r[k]='-'; y_r[k]=y[j];
                            
                               v[++k].r=i-1; v[k].c=j;
                               x_r[k]=x[i]; y_r[k]='-';
                            }
                        }
                        else{
                            if(v[k].c==j+1&&v[k].r==i){
                               v[++k].r=i; v[k].c=j-1;
                               x_r[k]='-'; y_r[k]=y[j];
                            }
                        }
                    }
                } //end of else


            } //end of else
        } //end of for(j=n;j>=0;j--)
    } //end of for(i=m;i>=0;i--)

    printf("%.1f ", opt[0][0]);
    

}


int main() {


    scanf("%d %d %s %s %f %f", &m, &n, x, y, &gap_p, &mis_p);
    sequencealignment();

   
}
