//--------------------------------------------------------------------
//
//  Laboratory 11, Programming Exercise 1                     ossim.cs
//
//  (Shell) Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "PriorityQueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
	int getPriority() const
	{
		return priority;
	}     // Returns the priority. Needed by the heap.

	int priority,                // Task's priority
		arrived;                 // Time when task was enqueued

};


//--------------------------------------------------------------------

int main()
{
	PriorityQueue<TaskData, int, Less<int> > taskPQ;   // Priority queue of tasks
	TaskData task;               // Task
	int simLength,               // Length of simulation (minutes)
		minute,                  // Current minute
		numPtyLevels,            // Number of priority levels
		numArrivals,             // Number of new tasks arriving
		j;                       // Loop counter

								 // Seed the random number generator
	// srand((unsigned int)time(NULL));

	cout << endl << "Enter the number of priority levels : ";
	cin >> numPtyLevels;

	cout << "Enter the length of time to run the simulator : ";
	cin >> simLength;

	for (minute = 1; minute < simLength; minute++)
	{
		// Dequeue the first task in the queue (if any).
		// Your code here
		if (!taskPQ.isEmpty())
		{
			task = taskPQ.dequeue();
			cout << "Current Minute: " << minute << endl;
			cout << "Task Priority: " << task.getPriority() << endl;
			cout << "Task Enqueue Time: " << task.arrived << endl;
			cout << "Task Wait Time: " << minute - task.arrived << endl;


		}

		// Determine the number of new tasks and add them to
		// the queue.
		// Your code here
		int k = rand() % 4;
		if (k == 1)
		{
			TaskData Task1;
			Task1.priority = rand() % numPtyLevels;
			Task1.arrived = minute;
			taskPQ.enqueue(Task1);
		}
		else if (k == 2)
		{
			TaskData Task1, Task2;
			Task1.priority = rand() % numPtyLevels;
			Task2.priority = rand() % numPtyLevels;

			Task1.arrived = minute;
			Task2.arrived = minute;
			taskPQ.enqueue(Task1);
			taskPQ.enqueue(Task2);
		}

		cout << endl;

		
	}
	return 0;
}