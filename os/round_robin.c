#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int pid, at, bt, rt, ct, tat, wt;
} Process;

// Sort processes by arrival time to manage the queue correctly
void sortByArrival(Process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j+1].at) {
                Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    int n, quantum;
    Process p[100];
    float total_tat = 0, total_wt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &quantum);

    sortByArrival(p, n);

    int current_time = p[0].at;
    int completed = 0;
    int queue[1000], front = 0, rear = 0;
    bool in_queue[100] = {false};

    queue[rear++] = 0;
    in_queue[0] = true;

    while (completed < n) {
        if (front == rear) { // If queue is empty, advance time
            current_time++;
            for (int i = 0; i < n; i++) {
                if (p[i].at <= current_time && !in_queue[i] && p[i].rt > 0) {
                    queue[rear++] = i;
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int idx = queue[front++]; // Dequeue

        int time_slice = (p[idx].rt > quantum) ? quantum : p[idx].rt;
        current_time += time_slice;
        p[idx].rt -= time_slice;

        // Check for new arrivals DURING the time slice
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !in_queue[i] && p[i].rt > 0) {
                queue[rear++] = i;
                in_queue[i] = true;
            }
        }

        // If the current process isn't done, put it back at the end of the queue
        if (p[idx].rt > 0) {
            queue[rear++] = idx;
        } else {
            p[idx].ct = current_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            
            total_tat += p[idx].tat;
            total_wt += p[idx].wt;
            completed++;
        }
    }

    printf("\n--- Round Robin (Quantum = %d) ---\nPID\tAT\tBT\tCT\tTAT\tWT\n", quantum);
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("\nAvg Turnaround Time: %.2f\nAvg Waiting Time: %.2f\n", total_tat / n, total_wt / n);

    return 0;
}
