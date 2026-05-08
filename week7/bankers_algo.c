#include <stdio.h>
#include <stdbool.h>

// Function to calculate Need matrix
void calculateNeed(int n, int m, int max[n][m], int alloc[n][m], int need[n][m]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            need[i][j] = max[i][j] - alloc[i][j];
}

// Function to check if system is in safe state
bool isSafe(int n, int m, int alloc[n][m], int need[n][m], int avail[m]) {
    bool finish[n];
    for (int i = 0; i < n; i++) finish[i] = false;

    int safeSeq[n], work[m];
    for (int j = 0; j < m; j++) work[j] = avail[j];

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
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            printf("\nSystem is not in a safe state.\n");
            return false;
        }
    }

    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if (i != n - 1) printf(" -> ");
    }
    printf("\n");
    return true;
}

// Function to handle resource request
bool requestResources(int process, int n, int m, int request[m],
                      int alloc[n][m], int need[n][m], int avail[m]) {
    // Check if request <= need
    for (int i = 0; i < m; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded maximum claim.\n");
            return false;
        }
    }

    // Check if request <= available
    for (int i = 0; i < m; i++) {
        if (request[i] > avail[i]) {
            printf("Resources not available. Process must wait.\n");
            return false;
        }
    }

    // Pretend to allocate
    for (int i = 0; i < m; i++) {
        avail[i] -= request[i];
        alloc[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check safety
    if (isSafe(n, m, alloc, need, avail))
        return true;
    else {
        // Rollback
        for (int i = 0; i < m; i++) {
            avail[i] += request[i];
            alloc[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return false;
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

    // Run safety check
    isSafe(n, m, alloc, need, avail);

    // Example resource request
    int *request = malloc(m * sizeof(int));
        request[0] = 1;
        request[1] = 0;
        request[2] = 2;

    requestResources(1, n, m, request, alloc, need, avail);

    return 0;
}

