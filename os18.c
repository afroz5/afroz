QUESTION 18: A uniprocessor system has n number of CPU intensive processes; each process has its own requirement of CPU burst.
The process with lowest CPU burst is given the highest priority. A late arriving higher priority process can pre-empt a currently running process with lower priority.
Simulate a scheduler that is scheduling the processes in such a way that higher priority process is never starved due to the execution of lower priority process.
What should be its average waiting time and average turnaround time if no two processes are arriving at same time.

  
  
  
  
   Code: 
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX_P 5

struct Process{
	int at,bt,pt,wt,ct,tat,flag;
	char name[4];
};

struct Process initialize(int at,int bt,int pt,int name){
	struct Process X;
	X.at = at;
	X.bt = bt;
	X.pt = pt;
	X.flag=0;

	sprintf(X.name,"P%d",name+1);

	return X;
}

int main(){

    int d,i,j,count=0;
	
	struct Process P[MAX_P+1];

	P[0] = initialize(0,9,5,0);
	P[1] = initialize(1,4,3,1);
	P[2] = initialize(2,5,1,2);
	P[3] = initialize(3,7,2,3);
	P[4] = initialize(4,3,4,4);


	int total_bt=0;
	//sort for arrival
	for(i=1; i<MAX_P; i++){
		for(j=0; j<MAX_P-i; j++){
			if(P[j].at<P[j+1].at){
				struct Process temp = P[j];
				P[j] = P[j+1];
				P[j+1] = temp;
			}
		}
	}

	
	int elapsed_time=0,time, highest_pt=-1;
	float wait_time = 0, turnaround_time = 0;

	for(i=0; i<MAX_P; i++)
		total_bt+=P[i].bt;

	printf("\nTotal Burst Time : %d\n",total_bt);
	
	P[MAX_P].pt = -9999; //idle sate process

	printf("\nP.Name\tArrival\tBurst\tPriority\tComplete\tWaiting T\tTurnAT");
	
	for(time = P[0].at; time < total_bt;){
	    highest_pt = MAX_P;
		for(i = 0; i < MAX_P; i++){
	    	if(P[i].at < time && P[i].flag == 0 && P[i].pt> P[highest_pt].pt){
	    		highest_pt = i;
	    		
	    	}
	    }
	    elapsed_time += P[highest_pt].bt;
	    time+=P[highest_pt].bt;
	    P[highest_pt].ct = elapsed_time;
	    P[highest_pt].wt = P[highest_pt].ct - P[highest_pt].at - P[highest_pt].bt;//-P[0].wt;
	    P[highest_pt].tat = P[highest_pt].ct - P[highest_pt].at;
	    P[highest_pt].flag = 1;
	    wait_time += P[highest_pt].wt;
	    turnaround_time += P[highest_pt].tat;
	    
	    printf("\n%s\t%d\t%d\t%d\t\t%d\t\t%d\t\t%d", P[highest_pt].name, P[highest_pt].at, P[highest_pt].bt, P[highest_pt].pt, P[highest_pt].ct,P[highest_pt].wt,P[highest_pt].tat);
	}


	printf("\n\nAverage Waiting Time    :\t%f\n", wait_time*1.0/(MAX_P-1));
	printf("Average Turnaround Time :\t%f\n", turnaround_time*1.0/(MAX_P-1));
	
	return 0*printf("\nSUCCESSFUL EXIT\n");
}
