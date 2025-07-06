#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PROCCESS 100
#define QUANTOM 4

//#######-----QUEUE IMPLEMENTATION------########


typedef struct Proccess {
    int pid;
    char processName[100]; // safer than char*
    int burstTime;
    int remainingTime;
    int arrivalTime;
} Proccess;

typedef struct ProccessQueue {
    Proccess proccess[MAX_PROCCESS];
    int front, rear, size;
} ProccessQueue;

void initQueue(ProccessQueue *q) {
    q->front = 0;
    q->rear = -1;
    q->size = 0;
}

bool isFull(ProccessQueue *q) {
    return q->size == MAX_PROCCESS;
}

bool isEmpty(ProccessQueue *q) {
    return q->size == 0;
}

void enqueue(ProccessQueue *q, Proccess *p) {
    if (isFull(q)) {
        printf("The Queue is Full!\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_PROCCESS;
    q->proccess[q->rear] = *p; // Copy the process struct
    q->size++;
}

Proccess dequeue(ProccessQueue *q) {
    Proccess empty = {0}; // default if empty
    if (isEmpty(q)) {
        printf("The queue is empty already!\n");
        return empty;
    }
    Proccess item = q->proccess[q->front];
    q->front = (q->front + 1) % MAX_PROCCESS;
    q->size--;
    return item;
}


//#####-------BASIC ROUND RUBIN IMPLEMENTATION------######

void roundRubin(ProccessQueue* q, int quantom)
{

    while(!isEmpty(q))
    {
        Proccess p = dequeue(q);
        int timeSpent = (p.remainingTime > quantom) ? quantom : p.remainingTime;
        
         printf("Running process %s (PID %d) for %d units\n", p.processName, p.pid, timeSpent);
         p.remainingTime -= timeSpent;

         if(p.remainingTime > 0)
         {
            enqueue(q,&p);
         }
         else
         {
            printf("Process %s (PID %d) completed.\n", p.processName, p.pid);
         }
    }
}

//####----DIFFERENT ARRIVAL TIME----#####

void roundRubinDifferentArrivalTime(ProccessQueue *waitingQueue, int quantum) {
    ProccessQueue readyQueue;
    initQueue(&readyQueue);

    int currentTime = 0;

    while (!isEmpty(waitingQueue) || !isEmpty(&readyQueue)) {

        // Step 1: Move arrived processes from waiting to ready
        int n = waitingQueue->size;
        for (int i = 0; i < n; i++) {
            Proccess p = dequeue(waitingQueue);
            if (p.arrivalTime <= currentTime) {
                enqueue(&readyQueue, &p);
            } else {
                enqueue(waitingQueue, &p); // Not yet arrived, put it back
            }
        }

        // Step 2: Run round-robin if readyQueue not empty
        if (!isEmpty(&readyQueue)) {
            Proccess p = dequeue(&readyQueue);

            int timeSpent = (p.remainingTime > quantum) ? quantum : p.remainingTime;
            printf("Time %d: Running process %s (PID %d) for %d units\n", currentTime, p.processName, p.pid, timeSpent);

            p.remainingTime -= timeSpent;
            currentTime += timeSpent;

            // After running, re-check arrivals during that time
            int m = waitingQueue->size;
            for (int i = 0; i < m; i++) {
                Proccess temp = dequeue(waitingQueue);
                if (temp.arrivalTime <= currentTime) {
                    enqueue(&readyQueue, &temp);
                } else {
                    enqueue(waitingQueue, &temp);
                }
            }

            // If not finished, re-add to readyQueue
            if (p.remainingTime > 0) {
                enqueue(&readyQueue, &p);
            } else {
                printf("Time %d: Process %s (PID %d) completed.\n", currentTime, p.processName, p.pid);
            }
        } else {
            // No process ready, idle time
            printf("Time %d: CPU is idle.\n", currentTime);
            currentTime++;
        }
    }
}
