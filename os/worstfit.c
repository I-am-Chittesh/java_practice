#include<stdio.h>
#define max 25

void main() {
    int frag[max], b[max], f[max], i, j, nb, nf, temp;
    static int bf[max], ff[max]; // bf = block status, ff = file to block map
    
    printf("\nEnter the number of blocks:");
    scanf("%d", &nb);
    printf("Enter the number of files:");
    scanf("%d", &nf);
    
    printf("\nEnter the size of the blocks:-\n");
    for(i = 1; i <= nb; i++) {
        printf("Block %d:", i);
        scanf("%d", &b[i]);
    }
    
    printf("Enter the size of the files :-\n");
    for(i = 1; i <= nf; i++) {
        printf("File %d:", i);
        scanf("%d", &f[i]);
    }
    
    // THE MANUAL'S "WORST-FIT" LOGIC
    for(i = 1; i <= nf; i++) {         // For each file
        for(j = 1; j <= nb; j++) {     // Check each block
            if(bf[j] != 1) {           // If block is free
                temp = b[j] - f[i];    // Calculate leftover space
                if(temp >= 0) {        // If it fits
                    ff[i] = j;         // Map file i to block j
                    break;             // Stop searching
                }
            }
        }
        frag[i] = temp;                // Store the leftover space (fragmentation)
        bf[ff[i]] = 1;                 // Mark the block as used
    }
    
    // Display results
    printf("\nFile_no:\tFile_size:\tBlock_no:\tBlock_size:\tFragement");
    for(i = 1; i <= nf; i++) {
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d", i, f[i], ff[i], b[ff[i]], frag[i]);
    }
}