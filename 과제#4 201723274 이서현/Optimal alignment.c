#include <stdio.h>

int m,n;   //m is length of x sequence, n is length of y sequence
char x[110];
char y[110];
float gap_p,mis_p;
float opt[110][110];
char x_r[110],y_r[110]={0,};
//x_r is optimal alignment of x sequence, y_r is optimal alignment of y sequence.

void sequencealignment(){
    int i,j; float penalty;

    for(i=m;i>=0;i--){
        for(j=n;j>=0;j--){
            if(i==m)  //initialize
                opt[i][j]=gap_p*(n-j);
            else if(j==n)  //initialize
                opt[i][j]=gap_p*(m-i);
            else{
                //The order of inputted is opt[i+1][j+1], opt[i+1][j], and opt[i][j+1].
                
                if(x[i]==y[j])
                    penalty=0;
                else
                    penalty=mis_p;
               
                if(opt[i+1][j+1]+penalty<opt[i+1][j]+gap_p){
                    if(opt[i+1][j+1]+penalty<opt[i][j+1]+gap_p)  //When opt[i+1][j+1]+penalty is the smallest
                        opt[i][j]=opt[i+1][j+1]+penalty;
                    else                                         //When opt[i][j+1]+gap_p is the smallest
                        opt[i][j]=opt[i][j+1]+gap_p;
                } //end of if(opt[i+1][j+1]+penalty<opt[i+1][j]+gap_p)
                else{
                    if(opt[i+1][j]+gap_p<opt[i][j+1]+gap_p)     //When opt[i+1][j]+gap_p is the smallest
                        opt[i][j]=opt[i+1][j]+gap_p;
                    else                                        //When opt[i][j+1]+gap_p is the smallest
                        opt[i][j]=opt[i][j+1]+gap_p;
                } //end of else
                
            } //end of else
        } //end of for(j=n;j>=0;j--)
    } //end of for(i=m;i>=0;i--)
    
    
    int length=0; j=0;  //length is length of optimal alignment.
    for(int i=0;i<=m;i++){
        //The order of tested is opt[i+1][j+1], opt[i+1][j], and opt[i][j+1].
        
        if(x[i]==y[j])  //When x[i]==y[j], then penalty is 0.
        {
            if(opt[i][j]==opt[i+1][j+1]) // When opt[i][j] and opt[i+1][j+1]+penalty are same.
            { x_r[length]=x[i]; y_r[length]=y[j]; j++; length++; continue;}
            // Input x[i] and y[j] into optiaml alignment.
        }
        else{   //When x[i]!=y[j], then penalty is mis_p.
            
            if(opt[i][j]-mis_p==opt[i+1][j+1]) // When opt[i][j] and opt[i+1][j+1]+penalty are same.
            { x_r[length]=x[i]; y_r[length]=y[j]; j++; length++; continue;}
            // Input x[i] and y[j] into each optiaml alignment.
            
            else if(opt[i][j]-gap_p==opt[i+1][j]) // When opt[i][j] and opt[i+1][j]+gap_p are same.
            {x_r[length]=x[i]; y_r[length]='-'; length++;}
            //Input x[i] into optimal alignment of x sequence.
            //Input '-' into optimal alignment of y sequence.
            if(opt[i][j]-gap_p==opt[i][j+1]) // When opt[i][j] and opt[i][j+1]+gap_p are same.
            {x_r[length]='-'; y_r[length]=y[j]; j++; length++;}
            //Input '-' into optimal alignment of x sequence.
            //Input y[j] into optimal alignment of y sequence.
        }
    }
    printf("%.1f ",opt[0][0]);
    
    
    for(i=0;i<length;i++)
        printf("%c",x_r[i]);
    printf(" ");
    for(j=0;j<length;j++)
        printf("%c",y_r[j]);
    
    
}


int main(){
    
    scanf("%d %d %s %s %f %f",&m,&n,x,y,&gap_p,&mis_p);
    sequencealignment();
    
}
