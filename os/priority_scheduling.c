#include <stdio.h>
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);
    int burst[n], priority[n], index[n];
    
    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time and Priority Value for Process %d: ", i+1);
        scanf("%d %d", &burst[i], &priority[i]);
        index[i] = i + 1;
    }
    
    for (int i = 0; i < n; i++) {
        int temp = priority[i], m = i;
        for (int j = i; j < n; j++) {
            if (priority[j] > temp) {
                temp = priority[j];
                m = j;
            }
        }
        swap(&priority[i], &priority[m]);
        swap(&burst[i], &burst[m]);
        swap(&index[i], &index[m]);
    }
    
    int t = 0;
    printf("Order of process Execution is\n");
    for (int i = 0; i < n; i++) {
        printf("P%d is executed from %d to %d\n", index[i], t, t + burst[i]);
        t += burst[i];
    }
    
    printf("\nProcess Id\tBurst Time\tWait Time\n");
    int wt = 0;
    int total_wt = 0;
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\n", index[i], burst[i], wt);
        total_wt += wt;
        wt += burst[i];
    }
    
    float avg_wt = (float)total_wt / n;
    printf("Average waiting time is %f\n", avg_wt);
    
    int total_tat = 0;
    for (int i = 0; i < n; i++) {
        total_tat += burst[i];
    }
    float avg_tat = (float)total_tat / n;
    printf("Average TurnAround Time is %f", avg_tat);
    return 0;
}