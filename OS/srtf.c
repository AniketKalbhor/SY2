#include <stdio.h> 
#include <stdbool.h> 

#define MAX_PROCESSES 7

struct process { 
	int pid; 
	int arrival_time; 
	int burst_time; 
	int remaining_time; 
}; 

int main() { 
	int n; 
	struct process Proc[MAX_PROCESSES]; 
	bool completed[MAX_PROCESSES] = {false}; 
	int current_time = 0; 
	int shortest_time = 0; 
	int shortest_index = 0; 

	printf("Number of processes: "); 
	scanf("%d", &n); 

	for (int i = 0; i < n; i++) { 
		printf("Enter arrival time and burst time for process %d: ", i+1); 
		scanf("%d %d", &Proc[i].arrival_time, &Proc[i].burst_time); 
		Proc[i].pid = i+1; 
		Proc[i].remaining_time = Proc[i].burst_time; 
	} 
	printf("\n"); 

	while (true) { 
		bool completed_all = true; 
		for (int i = 0; i < n; i++) 
			if (!completed[i]) { 
				bool all_completed = false; 
				if (Proc[i].arrival_time <= current_time && Proc[i].remaining_time < Proc[shortest_index].remaining_time)
					shortest_index = i; 
			} 
		if (completed_all){
			break; 
        }
		if (shortest_index != -1) { 
			Proc[shortest_index].remaining_time--; 
            printf("Process %d is running, remaining time = %d\n", Proc[shortest_index].pid, Proc[shortest_index].remaining_time);
			if (Proc[shortest_index].remaining_time == 0)
				completed[shortest_index] = true; 
		} 
		current_time++;
		// shortest_index = -1; 
	} 

	printf("Process\tArrival Time\tBurst Time\tWaiting Time\n"); 
	int total_waiting_time = 0; 
	for (int i = 0; i < n; i++) { 
		int waiting_time = 0; 
		waiting_time = current_time - Proc[i].burst_time - Proc[i].arrival_time; 
		total_waiting_time += waiting_time; 
		printf("%d\t %d\t\t %d\t\t %d\n", Proc[i].pid, Proc[i].arrival_time, Proc[i].burst_time, waiting_time); 
	} 

	float avg_waiting_time = (float) total_waiting_time / n; 
	printf("The Average Waiting Time: %.2f\n", avg_waiting_time); 
	return 0; 
}
