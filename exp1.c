#include <stdio.h>

typedef struct {
    		int id;
    		int burst_time;
    		int arrival_time;
 	     int waiting_time;
    		int turnaround_time;
    		int completed;
	    int priority;
  		  int remaining_time;
  		  int remaining_burst;
} Process;


void fcfs(Process processes[], int n)
{
      	printf("Enter arrival time and burst time for each process:\n");
 	   for (int i = 0; i < n; ++i) {
        		printf("Process %d:\n", i + 1);
        		printf("Arrival Time: ");
       		 scanf("%d", &processes[i].arrival_time);
       		 printf("Burst Time: ");
      		  scanf("%d", &processes[i].burst_time);
        		processes[i].id = i + 1;
    }
   
    for (int i = 0; i < n - 1; ++i) {
        	for (int j = 0; j < n - i - 1; ++j) {
            		if (processes[j].arrival_time > processes[j + 1].arrival_time) {
               		  Process temp = processes[j];
              			  processes[j] = processes[j + 1];
               		 processes[j + 1] = temp;
            		}
        		}
    }

  int completionTime = 0;
   float totalTurnaroundTime = 0;
   float totalWaitingTime = 0;

    		printf("\nProcess Execution Order:\n");
   		 printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
   			 for (int i = 0; i < n; ++i) {
   	    				 if (processes[i].arrival_time > completionTime)
            				completionTime = processes[i].arrival_time;
        					completionTime += processes[i].burst_time;

        				int turnaroundTime = completionTime - processes[i].arrival_time;
     			   int waitingTime = turnaroundTime - processes[i].burst_time;

        					totalTurnaroundTime += turnaroundTime;
       					totalWaitingTime += waitingTime;

       					 printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].id, processes[i].arrival_time,
            			   processes[i].burst_time, completionTime, turnaroundTime, waitingTime);
    }

    float avgTurnaroundTime = totalTurnaroundTime / n;
    float avgWaitingTime = totalWaitingTime / n;
    			printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);
    			printf("Average Waiting Time: %.2f\n", avgWaitingTime);
 
}
void sjf(Process processes[], int n) {
   
     	for (int i = 0; i < n; ++i) {
        			processes[i].id = i + 1;
        			printf("Enter the arrival time and burst time for process %d: ", i + 1);
        			scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        			processes[i].completed = 0;
     }
    int current_time = 0;
    int completed_processes = 0;
    int process_sequence[n];
    int seq_index = 0;

int shortest_index = -1;
    while (completed_processes < n) {
       
        int shortest_burst = 999999;

        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && !processes[i].completed) {
                if (processes[i].burst_time < shortest_burst) {
                    shortest_burst = processes[i].burst_time;
                    shortest_index = i;
                }
            }
        }

        if (shortest_index == -1) {
            printf("Idle ");
            current_time++;
        } else {
           
            		processes[shortest_index].waiting_time = current_time - processes[shortest_index].arrival_time;
            		current_time += processes[shortest_index].burst_time;
            		processes[shortest_index].turnaround_time = current_time - processes[shortest_index].arrival_time;
            		processes[shortest_index].completed = 1;
           		 completed_processes++;
        }
    }
   
}



void prio(Process processes[], int n) {
    		int current_time = 0;
    		int completed_processes = 0;

      for (int i = 0; i < n; ++i) {
        		processes[i].id = i + 1;
        		printf("Enter the arrival time, burst time, and priority for process %d: ", i + 1);
        		scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
       		 processes[i].completed = 0;
        		processes[i].waiting_time = 0;
    }
   
    while (completed_processes < n) {
       		 int highest_priority_index = -1;
        		int highest_priority = -1; // A large number to start with

        for (int i = 0; i < n; ++i) {
          	  if (processes[i].arrival_time <= current_time && !processes[i].completed) {
           		     if (processes[i].priority > highest_priority) {
                		    highest_priority = processes[i].priority;
                 		   highest_priority_index = i;
                		}
         		  }
        }

        if (highest_priority_index == -1) {
            printf("No process available at time %d\n", current_time);
            current_time++;
        } else {
            processes[highest_priority_index].waiting_time = current_time - processes[highest_priority_index].arrival_time;
            current_time += processes[highest_priority_index].burst_time;
            processes[highest_priority_index].turnaround_time = current_time - processes[highest_priority_index].arrival_time;
            processes[highest_priority_index].completed = 1;
            completed_processes++;
        }
    }
}
void rr(Process processes[], int n, int quantum) {

    		int total_waiting_time = 0;
   		 int total_turnaround_time = 0;

   		 for (int i = 0; i < n; i++) {
        			processes[i].remaining_burst = processes[i].burst_time;
   		 }

  	  int current_time = 0;
    		int completed = 0;

    			while (completed < n) {
      				  for (int i = 0; i < n; i++) {
          					  if ( processes[i].remaining_burst> 0) {
            						    if ( processes[i].remaining_burst> quantum) {
                   							 current_time += quantum;
                   	 						 processes[i].remaining_burst -= quantum;
             							   } else {
                    							current_time +=  processes[i].remaining_burst;
                   								 processes[i].waiting_time = current_time - processes[i].burst_time - processes[i].arrival_time;
                   								 processes[i].turnaround_time = current_time - processes[i].arrival_time;
                   								 total_waiting_time +=  processes[i].waiting_time;
                 								   total_turnaround_time += processes[i].turnaround_time;
                    							 processes[i].remaining_burst = 0;
                    							completed++;
                									}
          					  }
     			   }
    }
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    			for (int i = 0; i < n; i++) {
      			  printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].arrival_time, processes[i].burst_time,  processes[i].waiting_time, processes[i].turnaround_time);
  			  }
   				 printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    				printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}
void display_table(Process processes[], int n) {
   		 printf("\nProcess\tBurst Time\tArrival Time\tWaiting Time\tTurnaround Time\n");
    				for (int i = 0; i < n; ++i) {
     	 			  printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, processes[i].arrival_time,
              			 processes[i].waiting_time, processes[i].turnaround_time);
   			 }
}

int main() {
    	int n,z;
   	  float total_waiting_time = 0, total_turnaround_time = 0;
    		 int quantum;
    				printf("Enter the number of processes: ");
   				 scanf("%d", &n);
 				Process processes[n];
   				 printf("ENTER THE CPU SCHEDULING \n1.FCFS SCHEDULING \n2.SJF SCHEDULING \n3.PRIORITY SCHEDULING \n4.ROUND ROBIN \n");
    				scanf("%d",&z);
    switch(z){
        case 1:
        fcfs(processes, n);
        break;
       
        case 2:
       sjf(processes, n);

    			for (int i = 0; i < n; ++i) {
        				total_waiting_time += processes[i].waiting_time;
       				 total_turnaround_time += processes[i].turnaround_time;
   			 }

    				printf("\nAverage Waiting Time: %.2f\n", total_waiting_time / n);
    				printf("Average Turnaround Time: %.2f\n", total_turnaround_time / n);

    				display_table(processes, n);
     	break;
     case 3:
   
      prio(processes, n);
      printf("Process\tBurst Time\tArrival Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, processes[i].arrival_time,
               processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
    }
     break;
     case 4:
     printf("Enter the time quantum: ");
     scanf("%d", &quantum);
     
    printf("Enter process details (PID, arrival Time, burst Time):\n");
    			for (int i = 0; i < n; i++) {
        				printf("Process %d: ", i + 1);
        				scanf("%d %d %d", &processes[i].id, &processes[i].arrival_time, &processes[i].burst_time);
        				processes[i].remaining_burst = processes[i].burst_time;
   			 }
    		rr(processes, n, quantum);
     break;
    }
   
    return 0;
}
