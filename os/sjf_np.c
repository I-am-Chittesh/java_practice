#include <stdio.h>

typedef struct {
    int pid, at, bt, rt, ct, tat, wt;
} Process;

int main() {
    int n;
    Process p[100];
    float total_tat = 0, total_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt; // Remaining time equals burst time initially
    }

    int current_time = 0, completed = 0;

    while (completed < n) {
        int idx = -1;
        int min_rt = 999999;

        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].rt > 0) {
                if (p[i].rt < min_rt) {
                    min_rt = p[i].rt;
                    idx = i;
                } else if (p[i].rt == min_rt && p[i].at < p[idx].at) {
                    idx = i; // Tie-breaker: arrival time
                }
            }
        }

        if (idx != -1) {
            p[idx].rt--;
            current_time++;

            if (p[idx].rt == 0) {
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                
                total_tat += p[idx].tat;
                total_wt += p[idx].wt;
                completed++;
            }
        } else {
            current_time++; // CPU is idle
        }
    }

    printf("\n--- SRTF (Preemptive) ---\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAvg Turnaround Time: %.2f\nAvg Waiting Time: %.2f\n", total_tat / n, total_wt / n);

    return 0;
}
