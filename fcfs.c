#include <stdio.h>
#include <stdlib.h>

typedef struct proces
{
	int pid;
	int at;	 // arrival time
	int bt;	 // burst time
	int ct;	 // complete time = bt + at
	int tat; // turn around time = ct - at
	int wt;	 // waiting time = tat - bt
	int rt;	 // response time = st - at
	int st;

} process;

int cmpfunc(const void *p1, const void *p2)
{
	int a = ((process *)p1)->at;
	int b = ((process *)p2)->at;

	if (a < b)
	{
		return -1;
	}
	else
	{
		return 1;
	}
}

int main()
{
	int n;
	printf("Enter the Number of processes : ");
	scanf("%d", &n);
	process a[n];
	int cycleLength, idle_time = 0;
	for (int i = 0; i < n; i++)
	{
		a[i].pid = i + 1;
		printf("Enter the arrival time and Burst Time of process id %d: \n", i + 1);
		scanf("%d%d", &a[i].at, &a[i].bt);
	}

	qsort((void *)a, n, sizeof(process), cmpfunc);

	a[0].st = a[0].at;
	a[0].ct = a[0].bt + a[0].st;
	a[0].tat = a[0].ct - a[0].at;
	a[0].wt = a[0].tat - a[0].bt;
	a[0].rt = a[0].st - a[0].at;

	for (int i = 1; i < n; i++)
	{
		if (a[i - 1].ct >= a[i].at)
		{
			a[i].st = a[i - 1].ct;
		}
		else
		{
			a[i].st = a[i].at;
			if (a[i].at > a[i - 1].ct)
				idle_time += (a[i].at - a[i - 1].ct);
		}
		a[i].ct = a[i].st + a[i].bt;
		a[i].tat = a[i].ct - a[i].at;
		a[i].wt = a[i].tat - a[i].bt;
		a[i].rt = a[i].st - a[i].at;
	}
	float avgTat = 0, avgWt = 0, avgrt = 0, cpu_utilization, through_put;
	cycleLength = a[n - 1].ct - a[0].st;
	cpu_utilization = (cycleLength - idle_time) / (float)cycleLength * 100;
	through_put = (float)n / cycleLength;
	printf("\n\npid	|	at	|	bt	|	st	|	ct	|	tat	|	wt	|	rt\n");
	printf("________________________________________________________________________________________________________________________\n\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d	|	%d	|	%d	|	%d	|	%d	|	%d	|	%d	|	%d\n", a[i].pid, a[i].at, a[i].bt, a[i].st, a[i].ct, a[i].tat, a[i].wt, a[i].rt);
		avgTat += a[i].tat;
		avgWt += a[i].wt;
		avgrt += a[i].rt;
	}
	avgTat = avgTat / n;
	avgWt = avgWt / n;
	avgrt = avgrt / n;
	printf("Average Turn around Time : %f\n", avgTat);
	printf("Average Waiting Time : %f\n", avgWt);
	printf("Average Response Time : %f\n", avgrt);
	printf("Cpu utilization is : %f\n", cpu_utilization);
	printf("Through Put is : %f\n", through_put);
}