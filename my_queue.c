#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int front;
    int rear;
    int capacity;
    int* queue;
} Queue;

Queue* createQueue(int k); 
void enqueue(Queue* q, int data); 
void dequeue(Queue* q); 
bool isFull(Queue* q); 
bool isEmpty(Queue* q); 
void display(Queue* q); 
int Peek(Queue* q); 
bool contains(Queue* q, int target); 


int main() {
    Queue* q = createQueue(5);
    
    enqueue(q, 10);
    enqueue(q, 20);
    enqueue(q, 30);
    enqueue(q, 40);
    
    display(q); // Should print: 10 20 30 40
    
    dequeue(q);
    display(q); // Should print: 20 30 40
    
    printf("\nDoes queue contain 30? %s\n", contains(q, 30) ? "Yes" : "No");
    printf("Does queue contain 50? %s\n", contains(q, 50) ? "Yes" : "No");

    return 0;
}

Queue* createQueue(int k) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->capacity = k;
    q->rear = -1;
    q->front = 0;
    q->queue = (int*)malloc(q->capacity * sizeof(int));
    return q;
}

bool isFull(Queue* q) {
    return q->rear == q->capacity - 1;
}

bool isEmpty(Queue* q) {
    return q->rear < q->front;
}

bool contains(Queue* q, int target) {
    if (isEmpty(q)) return false;
    
    for (int i = q->front; i <= q->rear; i++) {
        if (q->queue[i] == target) {
            return true;
        }
    }
    return false;
}

void display(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty!\n");
    } else {
        for (int i = q->front; i <= q->rear; i++) {
            printf("%d ", q->queue[i]);
        }
        printf("\n");
    }
}

int Peek(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty!\n");
        return -1;
    } else {
        return q->queue[q->front];
    }
}

void dequeue(Queue* q) {
    if (isEmpty(q)) {
        printf("Queue is Empty\n");
    } else {
        q->front++;  // Just increment front to simulate removing an element
        if (q->front > q->rear) {
            q->front = 0;
            q->rear = -1; // Reset queue if empty after dequeue
        }
    }
}

void enqueue(Queue* q, int data) {
    if (isFull(q)) {
        printf("Queue is Full, can't add\n");
    } else {
        q->rear++;
        q->queue[q->rear] = data;
    }
}
