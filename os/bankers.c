#include <stdio.h>

int main() {
    int n, r, i, j, k;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &r);
    
    int alloc[n][r];
    int max[n][r];
    int avail[r];
    
    // 1. INPUT MATRICES
    printf("Enter the Allocation Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++)
            scanf("%d", &alloc[i][j]);
    }
    
    printf("Enter the Maximum Matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++)
            scanf("%d", &max[i][j]);
    }
    
    printf("Enter the Available Resources:\n");
    for (j = 0; j < r; j++)
        scanf("%d", &avail[j]);
        
    // 2. INITIALIZE TRACKING ARRAYS
    int f[n], ans[n], ind = 0;
    for (k = 0; k < n; k++) {
        f[k] = 0; // f array keeps track of finished processes
    }
    
    // 3. CALCULATE NEED MATRIX (Need = Max - Alloc)
    int need[n][r];
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++)
            need[i][j] = max[i][j] - alloc[i][j];
    }
    
    // 4. THE SAFETY ALGORITHM LOOP
    int y = 0;
    for (k = 0; k < n; k++) { // Loop enough times to finish all processes
        for (i = 0; i < n; i++) { // Loop through each process
            if (f[i] == 0) {      // If process is NOT finished yet
                int flag = 0;
                for (j = 0; j < r; j++) { // Check all resources for this process
                    if (need[i][j] > avail[j]) {
                        flag = 1; // It needs more than we have; cannot run
                        break;
                    }
                }
                
                // If the flag is still 0, it means the process CAN run
                if (flag == 0) {
                    ans[ind++] = i; // Add process to the safe sequence
                    for (y = 0; y < r; y++)
                        avail[y] += alloc[i][y]; // Return resources to available pool
                    f[i] = 1; // Mark process as finished
                }
            }
        }
    }
    
    // 5. PRINT THE SAFE SEQUENCE
    printf("The SAFE Sequence is as follows:\n");
    for (i = 0; i < n - 1; i++)
        printf("P%d -> ", ans[i]);
    printf("P%d\n", ans[n - 1]);
    
    return 0;
}