#include <stdio.h>
int main() {
    int at[10], bt[10], temp[10];
    int i, smallest, count = 0, time, limit;
    double wt = 0, tat = 0, end;
    float avg_wt, avg_tat;
    
    printf("Enter the Total Number of Processes: ");
    scanf("%d", &limit);
    printf("Enter Details of %d Processes:\n", limit);
    for(i = 0; i < limit; i++) {
        printf("Enter Arrival Time: ");
        scanf("%d", &at[i]);
        printf("Enter Burst Time: ");
        scanf("%d", &bt[i]);
        temp[i] = bt[i];
    }
    
    bt[9] = 9999;
    for(time = 0; count != limit; time++) {
        smallest = 9;
        for(i = 0; i < limit; i++) {
            if(at[i] <= time && bt[i] < bt[smallest] && bt[i] > 0) {
                smallest = i;
            }
        }
        bt[smallest]--;
        
        if(bt[smallest] == 0) {
            count++;
            end = time + 1;
            wt = wt + end - at[smallest] - temp[smallest];
            tat = tat + end - at[smallest];
        }
    }
    
    avg_wt = wt / limit;
    avg_tat = tat / limit;
    printf("\nAverage Waiting Time: %lf\n", avg_wt);
    printf("Average Turnaround Time: %lf\n", avg_tat);
    return 0;
}