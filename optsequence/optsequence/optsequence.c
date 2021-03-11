#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>

int m, n;   //m is length of x sequence, n is length of y sequence
char x[110];
char y[110];
double gap_p, mis_p;
double opt[110][110];
char x_r[110], y_r[110] = { 0, };
//x_r is optimal alignment of x sequence, y_r is optimal alignment of y sequence.
double R(double num) { //Round to the second decimal point
    return(round((num) * (100)) / 100);
}

void sequencealignment() {
    int i, j; double penalty;

    for (int w = 0; w <= m + 1; w++) opt[w][n + 1] = 10000;
    for (int k = 0; k <= n + 1; k++) opt[m + 1][k] = 10000;

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
                    if (opt[i + 1][j + 1] + penalty < opt[i][j + 1] + gap_p)  //When opt[i+1][j+1]+penalty is the smallest
                        opt[i][j] = opt[i + 1][j + 1] + penalty;
                    else                                         //When opt[i][j+1]+gap_p is the smallest
                        opt[i][j] = opt[i][j + 1] + gap_p;
                } //end of if(opt[i+1][j+1]+penalty<opt[i+1][j]+gap_p)
                else {
                    if (opt[i + 1][j] + gap_p < opt[i][j + 1] + gap_p)     //When opt[i+1][j]+gap_p is the smallest
                        opt[i][j] = opt[i + 1][j] + gap_p;
                    else                                        //When opt[i][j+1]+gap_p is the smallest
                        opt[i][j] = opt[i][j + 1] + gap_p;
                } //end of else


            } //end of else
        } //end of for(j=n;j>=0;j--)
    } //end of for(i=m;i>=0;i--)

    printf("%.1f ", opt[0][0]);


    i = 0;  j = 0; int length = 0;

    while (!(i >= m && j >= n)) {
        if (x[i] != y[j]) penalty = mis_p;
        else penalty = 0;

        if (R(opt[i][j]) == R(opt[i + 1][j + 1] + penalty)) {
            x_r[length] = x[i]; y_r[length++] = y[j];
            i++; j++;
        }
        else if (R(opt[i][j]) == R(opt[i + 1][j] + gap_p) &&
            R(opt[i][j]) == R(opt[i][j + 1] + gap_p)) {
            x_r[length] = x[i]; y_r[length++] = '-';
            x_r[length] = '-'; y_r[length++] = y[j];
            i++;  j++;
        }
        else if (R(opt[i][j]) == R(opt[i + 1][j] + gap_p)) {
            x_r[length] = x[i]; y_r[length++] = '-';
            i++;
        }
        else if (R(opt[i][j]) == R(opt[i][j + 1] + gap_p)) {
            x_r[length] = '-'; y_r[length++] = y[j];
            j++;
        }
    }

    for (i = 0; i <= length; i++)
        printf("%c", x_r[i]);
    for (j = 0; j <= length; j++)
        printf("%c", y_r[j]);


}


int main() {

    scanf("%d %d %s %s %lf %lf", &m, &n, x, y, &gap_p, &mis_p);
    sequencealignment();
}
