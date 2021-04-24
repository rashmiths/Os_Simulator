#include <bits/stdc++.h>
using namespace std;
void roundRobin()
{
    cout << "Enter the number of processes: ";
    int n, i, j;
    cin >> n;
    while (n < 0)
    {
        cout << "Wrong input, try again\nEnter number of processes: ";
        cin >> n;
    }
    vector<tuple<int, int, int, int, int>> times(n); // {at, bt, ct, tat, wt}

    for (i = 0; i < n; i++)
    {
        int t;
        cout << "For process " << i + 1 << ":" << endl;
        cout << "Arrival Time: ";
        cin >> t;
        while (t < 0)
        {
            cout << "Wrong input, try again\nArrival time: ";
            cin >> t;
        }
        get<0>(times[i]) = t; // Arrival time
        cout << "Burst Time: ";
        cin >> t;
        while (t < 0)
        {
            cout << "Wrong input, try again\nBurst time: ";
            cin >> t;
        }
        cout << endl;
        get<1>(times[i]) = t; // Burst time
        get<2>(times[i]) = 0; // Completion time
        get<3>(times[i]) = 0; // Turn around time
        get<4>(times[i]) = 0; // Waiting time
    }

    int ti = INT_MAX; // current time

    int slicetime;

    cout << "Enter slice time: ";
    cin >> slicetime;

    while (slicetime <= 0)
    {
        cout << "Wrong input, try again\nEnter slice time: ";
        cin >> slicetime;
    }

    for (i = 0; i < n; i++)
    {
        ti = min(ti, get<0>(times[i]));
    }

    int visited[n] = {0}, bt[n]; // completed programs and Burst time

    for (i = 0; i < n; i++)
    {
        bt[i] = get<1>(times[i]);
    }

    while (1)
    {

        int f = 0;

        for (i = 0; i < n; i++)
        {

            if (visited[i])
                continue;

            if (get<0>(times[i]) <= ti && get<1>(times[i]) > 0)
            {
                f = 1;
                ti += min(bt[i], slicetime);
                bt[i] = max(0, bt[i] - slicetime);

                if (bt[i] == 0)
                {
                    get<2>(times[i]) = ti;
                    get<3>(times[i]) = get<2>(times[i]) - get<0>(times[i]);
                    get<4>(times[i]) = get<3>(times[i]) - get<1>(times[i]);
                    visited[i] = 1;
                }
            }
        }

        if (f == 0)
        {
            ti++;
        }

        f = 0;

        // checking if all programs completed
        for (i = 0; i < n; i++)
        {
            if (visited[i] == 0)
            {
                f = 1;
                break;
            }
        }

        if (f == 0)
            break;
    }

    double TAT = 0, TWT = 0;

    for (i = 0; i < n; i++)
    {
        TAT += get<3>(times[i]);
        TWT += get<4>(times[i]);
    }

    cout << "\nProcess No.\tArrival Time\tBurst Time\tCompletion Time\t\tTurn-around Time\tWaiting Time\n";
    for (i = 0; i < n; i++)
    {
        cout << i + 1 << "\t\t" << get<0>(times[i]) << "\t\t" << get<1>(times[i]) << "\t\t" << get<2>(times[i]) << "\t\t\t" << get<3>(times[i]) << "\t\t\t" << get<4>(times[i]) << "\n";
    }

    TAT = TAT / (1.0 * n); // Average TAT
    TWT = TWT / (1.0 * n); // Average WT

    cout << "\nAverage Turn around time is: " << TAT << "\n";
    cout << "Average Waiting time is: " << TWT << "\n";

    return;
}

void sjf()
{

    int size;
    cout << "Enter the number of processes: ";
    cin >> size;

    int at[size]; //arrival time of each process
    int bt[size]; //burst time of each process

    for (int i = 0; i < size; i++)
    {
        cout << "For process " << i + 1 << ":" << endl;
        cout << "Arrival time: ";
        cin >> at[i];
        cout << "Burst time: ";
        cin >> bt[i];
        cout << endl;
    }

    long long wt[size], tat[size], total_WT = 0, total_TAT = 0;

    //finding waiting time
    long long rt[size];
    for (int i = 0; i < size; i++)
        rt[i] = bt[i];
    long long comp = 0, t = 0, minm = INT_MAX;
    long long shortest = 0, fin_time;
    bool check = false;
    while (comp != size)
    {
        for (int j = 0; j < size; j++)
        {
            if ((at[j] <= t) && (rt[j] < minm) && rt[j] > 0)
            {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }
        if (check == false)
        {
            t++;
            continue;
        }

        // decrementing the remaining time

        rt[shortest]--;
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completly executed

        if (rt[shortest] == 0)
        {
            comp++;
            check = false;
            fin_time = t + 1;

            // Calculate waiting time

            wt[shortest] = fin_time - bt[shortest] - at[shortest];
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        t++;
    }

    //turn around time
    for (int i = 0; i < size; i++)
        tat[i] = bt[i] + wt[i];

    cout << "\nProcess No.\tArrival Time\tBurst Time\tTurn-around Time\tWaiting Time\n";
    for (int i = 0; i < size; i++)
    {
        total_TAT += tat[i];
        total_WT += wt[i];
        cout << i + 1 << "\t\t" << at[i] << "\t\t" << bt[i] << "\t\t" << tat[i] << "\t\t\t" << wt[i] << "\n";
    }

    cout << "\nAverage Turn around time is: " << (double)total_TAT / size << "\n";
    cout << "Average Waiting time is: " << (double)total_WT / size << "\n";
}

void fcfs()
{

    cout << "\nEnter the number of processes: ";
    int n, i;
    cin >> n;
    while (n < 0)
    {
        cout << "Wrong input, try again"
             << "\nEnter number of processes: ";
        cin >> n;
    }
    vector<tuple<int, int, int, int, int>> times(n); // {at, bt, ct, tat, wt}

    cout << "Process Details" << endl
         << endl;
    for (i = 0; i < n; i++)
    {
        int t;
        cout << "For process " << i + 1 << ":" << endl;
        cout << "Arrival time: ";
        cin >> t;
        while (t < 0)
        {
            cout << "Wrong input, try again\nArrival Time P" << i << ": ";
            cin >> t;
        }
        get<0>(times[i]) = t; // Arrival time
        cout << "Burst time: ";
        cin >> t;
        while (t < 0)
        {
            cout << "Wrong input, try again\nBurst Time   P" << i << ": ";
            cin >> t;
        }
        cout << endl;
        get<1>(times[i]) = t; // Burst time
        get<2>(times[i]) = 0; // Completion time
        get<3>(times[i]) = 0; // Turn around time
        get<4>(times[i]) = 0; // Waiting time
    }

    sort(times.begin(), times.end()); // sorting according to Arrival time

    int ti = 0; // current time

    for (i = 0; i < n; i++)
    {

        if (ti < get<0>(times[i]))
            ti = get<0>(times[i]);

        get<2>(times[i]) = ti + get<1>(times[i]);
        ti += get<1>(times[i]);

        get<3>(times[i]) = get<2>(times[i]) - get<0>(times[i]);
        get<4>(times[i]) = get<3>(times[i]) - get<1>(times[i]);
    }

    double TAT = 0, TWT = 0;

    for (i = 0; i < n; i++)
    {
        TAT += get<3>(times[i]);
        TWT += get<4>(times[i]);
    }

    cout << "\n"
            "Process No.\tArrival Time\tBurst Time\tCompletion Time\t\tTurn-around Time\tWaiting Time\n";
    for (i = 0; i < n; i++)
    {
        cout << i + 1 << "\t\t" << get<0>(times[i]) << "\t\t" << get<1>(times[i]) << "\t\t" << get<2>(times[i]) << "\t\t\t" << get<3>(times[i]) << "\t\t\t" << get<4>(times[i]) << "\n";
    }

    TAT = TAT / (1.0 * n); // Average TAT
    TWT = TWT / (1.0 * n); // Average WT

    cout << "\nAverage Turn around time is: " << TAT << "\n";
    cout << "Average Waiting time is    : " << TWT << "\n";

    return;
}

void LJF()
{
    struct processes
    {
        int pid;
        int at;
        int bt;
        int ct;
        int tat;
        int wt;
    };

    int n, i, j, sumtat = 0, sumwt = 0;
    cout << "Enter no of processes" << endl;
    cin >> n;

    struct processes arr[n];
    struct processes k; // temporary structure used in swapping

    for (i = 0; i < n; i++)
    {
        cout << "For process " << i + 1 << ":" << endl;
        cout << "Arrival time: ";
        cin >> arr[i].at;
        cout << "Burst time: ";
        cin >> arr[i].bt;
        arr[i].pid = i + 1;
        cout << endl;
    }

    //sorting the array of structures according to arrival time and if arrival time is same then sorting it according to processid
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (arr[j].at > arr[j + 1].at)
            {

                k = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = k;
            }
            else if (arr[j].at == arr[j + 1].at)
            {
                if (arr[j].pid > arr[j + 1].pid)
                {

                    k = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = k;
                }
            }
        }
    }

    //finding the task which will be executed first
    int maxt, l = 0;
    maxt = arr[0].bt;

    for (i = 1; arr[i].at == arr[0].at; i++)
    {
        if (arr[i].bt > maxt)
        {
            maxt = arr[i].bt;
            l = i;
        }
    }
    k = arr[0];
    arr[0] = arr[l];
    arr[l] = k;

    arr[0].ct = arr[0].at + arr[0].bt;

    //sorting the array of structures according to largest burst times for arrival times less than the previous completion time

    for (i = 1; i < n; i++)
    {

        maxt = arr[i].bt;
        int val = i;
        for (j = i; j < n; j++)
        {
            if (arr[j].at <= arr[i - 1].ct && arr[j].bt > maxt)
            {
                maxt = arr[j].bt;
                val = j;
            }
        }

        k = arr[i];
        arr[i] = arr[val];
        arr[val] = k;

        //takes account of the case where if all the arrival times are greater than previous completion time
        if (arr[i].at > arr[i - 1].ct)
        {
            arr[i].ct = arr[i].at + arr[i].bt;
        }
        else
        {
            arr[i].ct = arr[i - 1].ct + arr[i].bt;
        }
    }

    //finding the turnaround time and the waiting time
    for (i = 0; i < n; i++)
    {
        arr[i].tat = arr[i].ct - arr[i].at;
        arr[i].wt = arr[i].tat - arr[i].bt;
        sumtat += arr[i].tat;
        sumwt += arr[i].wt;
    }

    cout << "\nProcess No.\tArrival Time\tBurst Time\tCompletion Time\t\tTurn-around Time\tWaiting Time\n";
    for (i = 0; i < n; i++)
    {
        cout << arr[i].pid << "\t" << arr[i].at << "\t" << arr[i].bt << "\t" << arr[i].ct << "\t" << arr[i].tat << "\t" << arr[i].wt << endl;
    }

    cout << "The average turnaround time is: " << float(sumtat) / float(n) << endl;
    cout << "The average waiting time is: " << float(sumwt) / float(n) << endl;
}
//
void LRTF()
{

    struct processes
    {
        int pid;
        int at;
        int bt;
        int ct;
        int tat;
        int wt;
        int rembt;
    };

    int n, i, j, sumtat = 0, sumwt = 0, timeslice;
    cout << "Enter no of processes: ";
    cin >> n;

    cout << "Enter the timeslice: ";
    cin >> timeslice;

    struct processes arr[n];
    struct processes k; // temporary structure used in swapping

    for (i = 0; i < n; i++)
    {
        cout << "For process " << i + 1 << ":" << endl;
        cout << "Arrival time: ";
        cin >> arr[i].at;
        cout << "Burst time: ";
        cin >> arr[i].bt;
        arr[i].rembt = arr[i].bt;
        arr[i].pid = i + 1;
        cout << endl;
    }

    //sorting the array of structures according to arrival time and if arrival time is same then sorting it according to processid
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - 1; j++)
        {
            if (arr[j].at > arr[j + 1].at)
            {

                k = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = k;
            }
            else if (arr[j].at == arr[j + 1].at)
            {
                if (arr[j].pid > arr[j + 1].pid)
                {

                    k = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = k;
                }
            }
        }
    }

    //finding the task which will be executed first
    int maxt, l = 0;
    maxt = arr[0].bt;

    for (i = 1; arr[i].at == arr[0].at; i++)
    {
        if (arr[i].bt > maxt)
        {
            maxt = arr[i].bt;
            l = i;
        }
    }
    k = arr[0];
    arr[0] = arr[l];
    arr[l] = k;

    int comptasks = 0, currtime = 0;
    l = 0;
    bool chk[n] = {false};

    while (comptasks != n)
    {
        if (arr[l].at > currtime)
        {
            currtime = arr[l].at;
        }

        if (arr[l].rembt <= timeslice)
        {
            currtime += arr[l].rembt;
            arr[l].rembt = 0;
            arr[l].ct = currtime;
            comptasks++;
        }
        else
        {
            currtime += timeslice;
            arr[l].rembt -= timeslice;
        }

        maxt = arr[l].rembt;
        for (i = 0; i < n; i++)
        {
            if (arr[i].at <= currtime && arr[i].rembt > maxt)
            {
                maxt = arr[i].rembt;
                l = i;
            }
            else if (arr[i].at <= currtime && arr[i].rembt == maxt && arr[i].rembt != 0)
            {
                if (i < l)
                {
                    l = i;
                }
            }
        }

        if (maxt == 0)
        {
            for (i = 0; i < n; i++)
            {
                if (arr[i].rembt > 0)
                {
                    l = i;
                    break;
                }
            }
        }
    }

    //finding the turnaround time and the waiting time
    for (i = 0; i < n; i++)
    {
        arr[i].tat = arr[i].ct - arr[i].at;
        arr[i].wt = arr[i].tat - arr[i].bt;
        sumtat += arr[i].tat;
        sumwt += arr[i].wt;
    }

    cout << "The table is as follows: (its shown according to the process that happens first) " << endl;
    cout << "\nProcess No.\tArrival Time\tBurst Time\tCompletion Time\t\tTurn-around Time\tWaiting Time\n";
    for (i = 0; i < n; i++)
    {
        cout << arr[i].pid << "\t\t" << arr[i].at << "\t\t" << arr[i].bt << "\t\t" << arr[i].ct << "\t\t\t\t" << arr[i].tat << "\t\t" << arr[i].wt << endl;
    }

    cout << "The average turnaround time is: " << float(sumtat) / float(n) << endl;
    cout << "The average waiting time is: " << float(sumwt) / float(n) << endl;
}

struct priority_process
{
    int bt, at, ct, wt, st, pno, tt, cbt, pr;
};

int get(struct priority_process arr[], int t, int n)
{
    int imin, min = 9999, i;
    for (i = 0; i < n; i++)
    {
        if (arr[i].at <= t && arr[i].st == 0)
            if (min > arr[i].pr)
            {
                min = arr[i].pr;
                imin = i;
            }
    }
    return imin;
}

void final_output(struct priority_process arr[], int p[], int n, int nop)
{
    int i, a[100], s = 0;
    float avgtat = 0, avgwt = 0;
    for (i = 0; i < n; i++)
    {
        while (i < n - 1 && p[i] == p[i + 1])
        {
            s++;
            i++;
        }
        s++;
        arr[p[i]].wt = s - arr[p[i]].at - arr[p[i]].tt;
    }
    for (i = 0; i < nop; i++)
    {
        arr[i].tt += arr[i].wt;
        avgwt += arr[i].wt;
        avgtat += arr[i].tt;
    }
    printf("\n\n");
    printf("Process\t|Priority\t|Arrival Time\t|Burst Time\t|Completion Time|Turnaround Time|Waiting Time\n");
    for (i = 0; i < nop; i++)
    {
        printf("[P%d]\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\n", arr[i].pno, arr[i].pr, arr[i].at,
               arr[i].cbt, arr[i].ct, arr[i].tt, arr[i].wt);
    }
    printf("\n");
    printf("Total wait time: %.2f\n", avgwt);
    printf("Total turnaround time: %.2f\n", avgtat);
    avgwt = avgwt / nop;
    avgtat = avgtat / nop;
    printf("Average Waiting Time : %.2f\n", avgwt);
    printf("Average Turnaround Time : %.2f\n", avgtat);
    return;
}

int iscomplete(struct priority_process arr[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        if (arr[i].st == 0)
            return 0;
    return 1;
}
void priority_premptive()
{
    int n, i, a, t = 0, j;
    int p[100];
    float avgwt = 0, avgtat = 0;
    struct priority_process arr[100];
    printf("Enter Number of Processes\n");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        printf("Enter Arrival Time, priority & Burst Time for Process [P%d]\n", i);
        scanf("%d%d%d", &arr[i].at, &arr[i].pr, &arr[i].bt);
        arr[i].pno = i;
        arr[i].cbt = arr[i].bt;
        arr[i].st = 0;
        arr[i].tt = arr[i].bt;
        arr[i].wt = 0;
    }
    i = 0;
    while (1)
    {
        if (iscomplete(arr, n))
            break;
        a = get(arr, t, n);
        p[i] = a;
        arr[a].bt -= 1;
        if (arr[a].bt == 0)
        {
            arr[a].st = 1;
            arr[a].ct = t + 1;
        }
        t = t + 1;
        i++;
    }
    final_output(arr, p, i, n);
    return;
}
//hrrn
struct node
{
    int pname;
    int btime;
    int atime;
    int wtime;
    float rr = 0;
} a[50];
void insert(int n)
{
    int i;
    for (int i = 0; i < n; i++)
    {
        cout << "For process " << i + 1 << ":" << endl;
        cout << "Arrival time: ";
        cin >> a[i].atime;
        cout << "Burst time: ";
        cin >> a[i].btime;
        a[i].rr = 0;
        a[i].pname = i + 1;
        a[i].wtime = -a[i].atime;
        cout << endl;
    }
}
bool btimeSort(node a, node b)
{
    return a.btime < b.btime;
}
bool atimeSort(node a, node b)
{
    return a.atime < b.atime;
}
bool rrtimeSort(node a, node b)
{
    return a.rr > b.rr;
}
void disp(int n)
{
    sort(a, a + n, btimeSort);
    sort(a, a + n, atimeSort);
    int ttime = 0, i;
    int j, tArray[n];
    for (i = 0; i < n; i++)
    {
        j = i;
        while (a[j].atime <= ttime && j != n)
        {
            j++;
        }
        for (int q = i; q < j; q++)
        {
            a[q].wtime = ttime - a[q].atime;
            a[q].rr = (float)(a[q].wtime + a[q].btime) / (float)a[q].btime;
        }
        sort(a + i, a + j, rrtimeSort);
        tArray[i] = ttime;
        cout << endl;
        ttime += a[i].btime;
    }
    tArray[i] = ttime;
    float averageWaitingTime = 0;
    float averageResponseTime = 0;
    float averageTAT = 0;
    cout << "\nProcess No.\tArrival Time\tBurst Time\tCompletion Time\t\tTurn-around Time\tWaiting Time\n";
    for (i = 0; i < n; i++)
    {
        cout << 'P' << a[i].pname << "\t\t";
        cout << a[i].atime << "\t\t";
        cout << a[i].btime << "\t\t";
        cout << tArray[i + 1] << "\t\t";
        cout << tArray[i] - a[i].atime + a[i].btime << "\t\t";
        averageTAT += tArray[i] - a[i].atime + a[i].btime;
        cout << a[i].wtime << "\t\t";
        averageWaitingTime += tArray[i] - a[i].atime;
        cout << tArray[i] - a[i].atime << "\t\t";
        averageResponseTime += tArray[i] - a[i].atime;
        cout << "\n";
    }
    cout << "\n";
    cout << "\n";
    cout << "Average Response time: " << (float)averageResponseTime / (float)n << endl;
    cout << "Average Waiting time: " << (float)averageWaitingTime / (float)n << endl;
    cout << "Average TA time: " << (float)averageTAT / (float)n << endl;
}
void hrrn()
{
    int nop, choice, i;
    cout << "Enter number of processes: ";
    cin >> nop;
    insert(nop);
    disp(nop);
    return;
}
//SRTF
struct process_srtf
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

void srtf()
{

    int n;
    struct process_srtf p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int burst_remaining[100];
    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));

    cout << setprecision(2) << fixed;

    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "For process " << i + 1 << ":" << endl;
        cout << "Arrival Time: ";
        cin >> p[i].arrival_time;
        cout << "Burst time"
             << ": ";
        cin >> p[i].burst_time;
        p[i].pid = i + 1;
        burst_remaining[i] = p[i].burst_time;
        cout << endl;
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while (completed != n)
    {
        int idx = -1;
        int mn = 10000000;
        for (int i = 0; i < n; i++)
        {
            if (p[i].arrival_time <= current_time && is_completed[i] == 0)
            {
                if (burst_remaining[i] < mn)
                {
                    mn = burst_remaining[i];
                    idx = i;
                }
                if (burst_remaining[i] == mn)
                {
                    if (p[i].arrival_time < p[idx].arrival_time)
                    {
                        mn = burst_remaining[i];
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1)
        {
            if (burst_remaining[idx] == p[idx].burst_time)
            {
                p[idx].start_time = current_time;
                total_idle_time += p[idx].start_time - prev;
            }
            burst_remaining[idx] -= 1;
            current_time++;
            prev = current_time;

            if (burst_remaining[idx] == 0)
            {
                p[idx].completion_time = current_time;
                p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
                p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
                p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

                total_turnaround_time += p[idx].turnaround_time;
                total_waiting_time += p[idx].waiting_time;
                total_response_time += p[idx].response_time;

                is_completed[idx] = 1;
                completed++;
            }
        }
        else
        {
            current_time++;
        }
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for (int i = 0; i < n; i++)
    {
        min_arrival_time = min(min_arrival_time, p[i].arrival_time);
        max_completion_time = max(max_completion_time, p[i].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    // cpu_utilisation = ((max_completion_time - total_idle_time) / (float)max_completion_time) * 100;
    // throughput = float(n) / (max_completion_time - min_arrival_time);

    cout << endl
         << endl;

    cout << "\nProcess No.\tArrival Time\tStart Time\tBurst Time\tCompletion Time\t\tTurn-around Time\tWaiting Time\tResponse Time\n";
    for (int i = 0; i < n; i++)
    {
        cout << p[i].pid << "\t\t" << p[i].arrival_time << "\t\t" << p[i].burst_time << "\t\t" << p[i].start_time << "\t\t" << p[i].completion_time << "\t\t\t\t" << p[i].turnaround_time << "\t\t" << p[i].waiting_time << "\t\t" << p[i].response_time << "\t\t"
             << "\n"
             << endl;
    }
    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
}
