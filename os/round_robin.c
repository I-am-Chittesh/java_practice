#include <stdio.h>
int main() {
    int c, j, n, t, remaining, flag = 0, tq;
    int wt = 0, tat = 0, at[10], bt[10], rt[10];
    
    printf("Enter Total Process: ");
    scanf("%d", &n);
    remaining = n;
    
    for(c = 0; c < n; c++) {
        printf("Enter Arrival Time and Burst Time for Process %d: ", c+1);
        scanf("%d", &at[c]);
        scanf("%d", &bt[c]);
        rt[c] = bt[c];
    }
    
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
    printf("\nProcess\t Turnaround Time Waiting Time\n\n");
    
    for(t = 0, c = 0; remaining != 0;) {
        if(rt[c] <= tq && rt[c] > 0) {
            t += rt[c];
            rt[c] = 0;
            flag = 1;
        } else if(rt[c] > 0) {
            rt[c] -= tq;
            t += tq;
        }
        
        if(rt[c] == 0 && flag == 1) {
            remaining--;
            printf("P[%d]\t\t%d\t\t%d\n", c+1, t-at[c], t-at[c]-bt[c]);
            wt += t - at[c] - bt[c];
            tat += t - at[c];
            flag = 0;
        }
        
        if(c == n - 1)
            c = 0;
        else if(at[c+1] <= t)
            c++;
        else
            c = 0;
    }
    
    printf("\nAverage Waiting Time: %f\n", wt * 1.0 / n);
    printf("Average Turnaround Time: %f", tat * 1.0 / n);
    return 0;
}