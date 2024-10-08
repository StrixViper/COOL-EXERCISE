// C# program for insertion and
// deletion in Circular Queue
using System;
using System.Collections.Generic;

public class CircularQueue{
	
	// Declaring the class variables.
	private int size, front, rear;
	
	// Declaring array list of integer type.
	private List<int> queue = new List<int>();
	
	// Constructor
	CircularQueue(int size)
	{
		this.size = size;
		this.front = this.rear = -1;
	}
	
	// Method to insert a new element in the queue.
	public void enQueue(int data)
	{
		
		// Condition if queue is full.
		if((front == 0 && rear == size - 1) ||
		(rear == (front - 1) % (size - 1)))
		{
			Console.Write("Queue is Full");
		}
	
		// condition for empty queue.
		else if(front == -1)
		{
			front = 0;
			rear = 0;
			queue.Add(data);
		}
	
		else if(rear == size - 1 && front != 0)
		{
			rear = 0;
			queue[rear]=data;
		}
	
		else
		{
			rear = (rear + 1);
		
			// Adding a new element if
			if(front <= rear)
			{
				queue.Add(data);
			}
		
			// Else updating old value
			else
			{
				queue[rear]=data;
			}
		}
	}
	
	// Function to dequeue an element
	// form th queue.
	public int deQueue()
	{
		int temp;
	
		// Condition for empty queue.
		if(front == -1)
		{
			Console.Write("Queue is Empty");
			
			// Return -1 in case of empty queue
			return -1;
		}
	
		temp = queue[front];
	
		// Condition for only one element
		if(front == rear)
		{
			front = -1;
			rear = -1;
		}
	
		else if(front == size - 1)
		{
			front = 0;
		}
		else
		{
			front = front + 1;
		}
		
		// Returns the dequeued element
		return temp;
	}
	
	// Method to display the elements of queue
	public void displayQueue()
	{
		
		// Condition for empty queue.
		if(front == -1)
		{
			Console.Write("Queue is Empty");
			return;
		}
	
		// If rear has not crossed the max size
		// or queue rear is still greater then
		// front.
		Console.Write("Elements in the circular queue are: ");
	
		if(rear >= front)
		{
		
			// Loop to print elements from
			// front to rear.
			for(int i = front; i <= rear; i++)
			{
				Console.Write(queue[i]);
				Console.Write(" ");
			}
			Console.Write("\n");
		}
	
		// If rear crossed the max index and
		// indexing has started in loop
		else
		{
			
			// Loop for printing elements from
			// front to max size or last index
			for(int i = front; i < size; i++)
			{
				Console.Write(queue[i]);
				Console.Write(" ");
			}
	
			// Loop for printing elements from
			// 0th index till rear position
			for(int i = 0; i <= rear; i++)
			{
				Console.Write(queue[i]);
				Console.Write(" ");
			}
			Console.Write("\n");
		}
	}
	
	// Driver code
	static public void Main (){
		// Initialising new object of
		// CircularQueue class.
		CircularQueue q = new CircularQueue(5);
		
		q.enQueue(14);
		q.enQueue(22);
		q.enQueue(13);
		q.enQueue(-6);
		
		q.displayQueue();
	
		int x = q.deQueue();
	
		// Checking for empty queue.
		if(x != -1)
		{
			Console.Write("Deleted value = ");
			Console.Write(x+"\n");
		}
	
		x = q.deQueue();
	
		// Checking for empty queue.
		if(x != -1)
		{
			Console.Write("Deleted value = ");
			Console.Write(x+"\n");
		}
	
		q.displayQueue();
		
		q.enQueue(9);
		q.enQueue(20);
		q.enQueue(5);
		
		q.displayQueue();
		
		q.enQueue(20);
	}
}

// This code is contributed by shruti456rawal
