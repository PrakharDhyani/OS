#include <bits/stdc++.h>

using namespace std;

struct Process
{

    int pid; // Process ID
    int bt;  // Burst Time
    int at;  // Arrival Time
    int ct;  // complete time = bt + at
    int tat; // turn around time = ct - at
    int wt;  // waiting time = tat - bt
    int rt;  // response time = st - at
    int st;
};

void findWaitingTime(Process arr[], int n)
{

    int complete = 0, t = 0, minm = INT_MAX;
    int CurrIndex = 0, finish_time;
    bool check = false;

    while (complete != n)
    {
        for (int j = 0; j < n; j++)
        {
            if ((arr[j].at <= t) && (arr[j].bt < minm) && arr[j].bt > 0)
            {
                minm = arr[j].bt;
                CurrIndex = j;
                check = true;
            }
        }

        if (check == false)
        {
            t++;
            continue;
        }
        else
            arr[CurrIndex].st = min(arr[CurrIndex].st, t);

        arr[CurrIndex].bt--;
        minm = arr[CurrIndex].bt;

        if (minm == 0)
            minm = INT_MAX;

        if (arr[CurrIndex].bt == 0)
        {
            complete++;
            check = false;
            finish_time = t + 1;
            arr[CurrIndex].ct = finish_time;
            arr[CurrIndex].wt = finish_time - arr[CurrIndex].bt - arr[CurrIndex].at;
            if (arr[CurrIndex].wt < 0)
                arr[CurrIndex].wt = 0;
        }
        t++;
    }
}

void findTurnAroundTime(Process arr[], int n)
{
    for (int i = 0; i < n; i++)
        arr[i].tat = arr[i].bt + arr[i].wt;
}

void findavgTime(Process arr[], int n)
{
    int total_wt = 0, total_tat = 0, total_rt = 0, idle_time = 0;
    int bt[n];
    for (int i = 0; i < n; i++)
        bt[i] = arr[i].bt;
    findWaitingTime(arr, n);
    findTurnAroundTime(arr, n);
    for (int i = 0; i < n; i++)
        arr[i].bt = bt[i];

    cout << " P\t\t"
         << "AT\t\t"
         << "BT\t\t"
         << "ST\t\t"
         << "CT\t\t"
         << "WT\t\t"
         << "TAT\t\t"
         << "RT\t\t" << endl;

    for (int i = 0; i < n; i++)
    {
        arr[i].rt = arr[i].st - arr[i].at;
        arr[i].wt = arr[i].tat - arr[i].bt;
        total_wt += arr[i].wt;
        total_tat += arr[i].tat;
        total_rt += arr[i].rt;
        if (i != 0 && arr[i].at > arr[i - 1].ct)
            idle_time += (arr[i].at - arr[i - 1].ct);
        cout
            << " " << arr[i].pid
            << "\t\t " << arr[i].at
            << "\t\t " << arr[i].bt
            << "\t\t " << arr[i].st
            << "\t\t " << arr[i].ct
            << "\t\t " << arr[i].wt
            << "\t\t " << arr[i].tat
            << "\t\t " << arr[i].rt
            << endl;
    }
    float cpu_utilization, through_put, cycleLength;
    cycleLength = arr[n - 1].ct - arr[0].st;
    cpu_utilization = (cycleLength - idle_time) / (float)cycleLength * 100;
    through_put = n / cycleLength;
    cout << "\nAverage waiting time = " << (float)total_wt / (float)n;
    cout << "\nAverage turn around time = " << (float)total_tat / (float)n;
    cout << "\nAverage response  time = " << (float)total_rt / (float)n;
    cout << "\nCpu utilization is : " << cpu_utilization;
    cout << "\nThrough Put is : " << through_put;
}

int main()
{
    int n;
    cout << "Enter the number of process : " << endl;
    cin >> n;
    Process arr[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the arrival and burst time for " << i + 1 << " process " << endl;
        arr[i].pid = i + 1;
        arr[i].st = INT_MAX;
        cin >> arr[i].at >> arr[i].bt;
    }

    findavgTime(arr, n);
    return 0;
}