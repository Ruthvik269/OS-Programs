#include <stdio.h>
#include <stdlib.h>

typedef struct process {
    int Id, AT, BT, CT, TAT, WT, flag;
} pro;

void swap(pro *a, pro *b) {
    pro temp = *a;
    *a = *b;
    *b = temp;
}

void sort(pro *p, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].AT > p[j + 1].AT) {
                swap(&p[j], &p[j + 1]);
            }
        }
    }
}

int main() {
    int n, total_WT = 0, total_TAT = 0, quantum;
    float avg_WT = 0, avg_TAT = 0;

    printf("\nEnter the number of processes:\n");
    scanf("%d", &n);

    pro *p = (pro *)malloc(n * sizeof(pro));
    int *tempBT = (int *)malloc(n * sizeof(int));

    printf("\nEnter the arrival time and burst time of the process:\n");
    printf("AT BT\n");
    for (int i = 0; i < n; i++) {
        p[i].Id = (i + 1);
        scanf("%d%d", &p[i].AT, &p[i].BT);
        tempBT[i] = p[i].BT;
        p[i].flag = 0;
    }

    printf("\nEnter the time quantum:\n");
    scanf("%d", &quantum);

    sort(p, n);

    // A queue is required for demonstrating this algorithm
    int completed = 0, curIndex, curTime = p[0].AT;
    int *waitQueue = (int *)malloc(n * sizeof(int));
    int front = 0, rear = 0;
    waitQueue[rear] = 0;
    p[0].flag = 1;

    printf("\nGantt Chart:\n\n");
    while (completed != n) {
        curIndex = waitQueue[front];
        front = (front + 1) % n;

        if (p[curIndex].BT > quantum) {
            p[curIndex].BT -= quantum;
            curTime += quantum;
            printf("| P%d (%d) %d", p[curIndex].Id, quantum, curTime);
        } else {
            curTime += p[curIndex].BT;
            printf("| P%d (%d) %d", p[curIndex].Id, p[curIndex].BT, curTime);
            p[curIndex].BT = 0;
            p[curIndex].CT = curTime;
            p[curIndex].TAT = p[curIndex].CT - p[curIndex].AT;
            total_TAT += p[curIndex].TAT;
            p[curIndex].WT = p[curIndex].TAT - tempBT[p[curIndex].Id - 1];
            total_WT += p[curIndex].WT;
        }

        for (int i = 0; i < n && p[i].AT <= curTime; i++) {
            if (i == curIndex || p[i].flag == 1 || p[i].BT == 0)
                continue;
            rear = (rear + 1) % n;
            p[i].flag = 1;
            waitQueue[rear] = i;
        }

        if (p[curIndex].BT > 0) {
            rear = (rear + 1) % n;
            waitQueue[rear] = curIndex;
        } else {
            completed++;
        }
    }
    printf("|\n");

    avg_TAT = (float)total_TAT / n;
    avg_WT = (float)total_WT / n;

    // Printing the table of processes with details
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].Id, p[i].AT, tempBT[i], p[i].CT, p[i].TAT, p[i].WT);
    }

    printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", avg_TAT, avg_WT);

    // Freeing allocated memory
    free(p);
    free(tempBT);
    free(waitQueue);

    return 0;
}
