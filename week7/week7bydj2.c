#include <stdio.h>
#include <stdbool.h>

// Function to calculate Need matrix
void calculateNeed(int n, int m, int max[n][m], int alloc[n][m], int need[n][m]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

// Function to detect deadlock
void detectDeadlock(int n, int m, int alloc[n][m], int need[n][m], int avail[m]) {
    bool finish[n];
    for (int i = 0; i < n; i++)
        finish[i] = false;

    int work[m];
    for (int j = 0; j < m; j++)
        work[j] = avail[j];

    int count = 0;
    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < m; j++)
                    if (need[i][j] > work[j])
                        break;
                if (j == m) {
                    for (int k = 0; k < m; k++)
                        work[k] += alloc[i][k];
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            break;
    }

    bool deadlock = false;
    int deadlockedProcs[n], deadlockedCount = 0;
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            deadlock = true;
            deadlockedProcs[deadlockedCount++] = i;
        }
    }

    if (!deadlock) {
        printf("No deadlock detected.\n");
    } else {
        printf("Deadlocked processes: ");
        for (int i = 0; i < deadlockedCount; i++) {
            printf("P%d", deadlockedProcs[i]);
            if (i != deadlockedCount - 1)
                printf(", ");
        }
        printf("\n");
    }
}

int main() {
    int n, m;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Maximum Demand Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    // Calculate Need
    calculateNeed(n, m, max, alloc, need);

    printf("\n=== Deadlock Detection ===\n");
    detectDeadlock(n, m, alloc, need, avail);

    return 0;
}