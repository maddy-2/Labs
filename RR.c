#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE_SIZE 20

struct Process {
    int pId;
    int burstTime;
    int waitingTime;
    int arrivalTime;
    int turnaroundTime;
    int completionTime;
    int remainingBurstTime;
    int preemptedTime;
    int executedTime;
} ganttChart[100];

typedef struct Process Process;

int queuePtr = 0;
int ganttChartIndex = 0;

void roundRobin(Process*, int, int);
void enqueue(Process *[20], Process*);
Process* dequeue(Process *[20]);
int processIdComparator(const void*, const void*);
int arrivalTimeComparator(const void*, const void*);
void printGanttChart(const Process*, int);
void printProcessArray(const Process* processes, int n);

int main() {

    int n, timeQuantum;

    printf("Enter time quantum: ");
    scanf("%d", &timeQuantum);

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[10];

    for (int i = 0; i < n; ++i) {
        processes[i].pId = i+1;

        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &processes[i].burstTime);

        printf("Enter arrival time for process %d: ", i+1);
        scanf("%d", &processes[i].arrivalTime);

        processes[i].remainingBurstTime = processes[i].burstTime;

    }

    
    qsort((void*) processes, n, sizeof(Process), arrivalTimeComparator);
    roundRobin(processes, n, timeQuantum);

    qsort((void*) processes, n, sizeof(Process), processIdComparator);
    printProcessArray(processes, n);

    printf("\nGantt Chart:\n\n");
    printGanttChart(ganttChart, ganttChartIndex);

    
    float wt = 0;
    for (int l = 0; l < n; ++l) {
        wt += processes[l].waitingTime;
    }
    wt /= n;
    printf("\nAverage waiting time: %g\n", wt);

    
    float tat = 0;
    for (int m = 0; m < n; ++m) {
        tat += processes[m].turnaroundTime;
    }
    tat /= n;

    printf("Average turnaround time: %g\n", tat);

    return 0;
}

void roundRobin(Process *processes, int n, int timeQuantum) {

    Process *queue[MAX_QUEUE_SIZE];
    int processTablePtr = 0;
    Process* currentProcess = &processes[0];
    int time = currentProcess->arrivalTime;

    enqueue(queue, &processes[processTablePtr++]);

    while (true) {

        currentProcess = dequeue(queue);

        if (currentProcess == NULL)
            break;

        ganttChart[ganttChartIndex] = *currentProcess;

        if (ganttChartIndex > 0)
            ganttChart[ganttChartIndex - 1].preemptedTime = time;

        if (ganttChartIndex > 1) {
            ganttChart[ganttChartIndex - 1].executedTime =
                    ganttChart[ganttChartIndex - 1].preemptedTime - ganttChart[ganttChartIndex - 2].preemptedTime;
        }
        ganttChartIndex++;

        time += timeQuantum;

        for (int i = processTablePtr; i < n; ++i) {
            if (processes[processTablePtr].arrivalTime <= time) {
                enqueue(queue, &processes[processTablePtr++]);
            } else
                break;
        }

        if (currentProcess->remainingBurstTime <= timeQuantum) {
            time = time - (timeQuantum - currentProcess->remainingBurstTime);
            currentProcess->remainingBurstTime = 0;
        }
        else {
            currentProcess->remainingBurstTime = currentProcess->remainingBurstTime - timeQuantum;
            enqueue(queue, currentProcess);
        }

        if (currentProcess->remainingBurstTime == 0) {
            currentProcess->completionTime = time;
            currentProcess->turnaroundTime = currentProcess->completionTime -
                    currentProcess->arrivalTime;
            currentProcess->waitingTime = currentProcess->turnaroundTime - currentProcess->burstTime;
        }
    }

    ganttChart[ganttChartIndex-1].preemptedTime = time;
    ganttChart[ganttChartIndex-1].executedTime = ganttChart[ganttChartIndex-1].preemptedTime - ganttChart[ganttChartIndex-2].preemptedTime;

    ganttChart[0].executedTime = ganttChart[1].preemptedTime - ganttChart[0].arrivalTime;

    
    if (ganttChart[0].arrivalTime != 0) {
        for (int i = ganttChartIndex; i > 0 ; i--) {
            ganttChart[i] = ganttChart[i-1];
        }
        ganttChartIndex++;
        Process emptyProcess;
        emptyProcess.pId = -1;
        emptyProcess.preemptedTime = ganttChart[1].arrivalTime;
        emptyProcess.executedTime = ganttChart[1].arrivalTime;
        emptyProcess.arrivalTime = 0;
        ganttChart[0] = emptyProcess;
        ganttChart[1].executedTime = ganttChart[1].preemptedTime - ganttChart[0].preemptedTime;
    }
}

void printProcessArray(const Process* processes, int n) {

    printf("\nProcess\tArrival time\t\tBurst time\t\tCompletion time\t\tTurnaround time\t\tWaiting time\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t%d\t\t\t\t\t%d\n",
               processes[i].pId, processes[i].arrivalTime, processes[i].burstTime,
               processes[i].completionTime, processes[i].turnaroundTime, processes[i].waitingTime);
    }
}

void enqueue(Process *queue[MAX_QUEUE_SIZE], Process *process) {

    if (queuePtr == MAX_QUEUE_SIZE) {
        printf("\nQueue is full\n");
        exit(0);
    }

    queue[queuePtr] = process;
    queuePtr = queuePtr + 1;
}

Process* dequeue(Process *queue[MAX_QUEUE_SIZE]) {

    if (queuePtr < 0) {
        printf("\nQueue is empty\n");
        return NULL;
    }

    Process *ptr = queue[0];

    for (int i = 0; i < queuePtr-1; ++i) {
        queue[i] = queue[i+1];
    }

    queuePtr = queuePtr - 1;
    queue[queuePtr] = NULL;

    return ptr;
}

int processIdComparator(const void *p, const void *q) {

    int a = (*(Process *) p).pId;
    int b = (*(Process *) q).pId;

    return (a - b);
}

int arrivalTimeComparator(const void *p, const void *q) {

    int a = (*(Process *) p).arrivalTime;
    int b = (*(Process *) q).arrivalTime;

    return (a - b);
}

void printGanttChart(const Process* p, int n) {

    int i, j;

 
    printf(" ");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].executedTime; j++) printf("--");
        printf(" ");
    }
    printf("\n|");


    for(i=0; i<n; i++) {
        for(j=0; j<p[i].executedTime - 1; j++) printf(" ");
        if (p[i].pId > 0)
            printf("P%d", p[i].pId);
        else
            printf("  ");
        for(j=0; j<p[i].executedTime - 1; j++) printf(" ");
        printf("|");
    }
    printf("\n ");
 
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].executedTime; j++) printf("--");
        printf(" ");
    }
    printf("\n");


    printf("0");
    for(i=0; i<n; i++) {
        for(j=0; j<p[i].executedTime; j++) printf("  ");
        if(p[i].preemptedTime > 9) printf("\b"); 
        printf("%d", p[i].preemptedTime);
    }
    printf("\n");

}
