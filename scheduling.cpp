#include <bits/stdc++.h>
using namespace std;
void roundRobin()
{
    //Taking input from the user for number of processes
    int n;
    cout << "Enter the number of processes \n";
    cin >> n;

    //Creating 3 arrays for burst time, arrival time and process id
    int bur_time[n];
    int arr_time[n];
    int pro[n];
    int q;

    //Entering the process id
    for (int i = 0; i < n; i++)
        pro[i] = i + 1;
    cout << "\n";

    //Taking arrival time of the processes
    cout << "Enter the arrival time of the processes \n";
    for (int i = 0; i < n; i++)
        cin >> arr_time[i];

    //Taking burst time of the processes
    cout << "Enter burst time of the processes \n";
    for (int i = 0; i < n; i++)
        cin >> bur_time[i];

    //taking time quantum for the processes
    cout << "Enter the time quantam for each process: ";
    cin >> q;

    /*calling the avgtime function to calculate 
    avg waiting time and average turn around time */
    //creating two arrays wait_time and turn_time
    //to store waiting time and turn aroung time of each process
    int wait_time[n], turn_time[n];

    // creating remaining_time array to maintain remaining time for each process
    int remaining_time[n];

    for (int i = 0; i < n; i++)
        remaining_time[i] = bur_time[i];

    int rem = n; // variable for remaining processes
    int elapsed_time = 0, flag = 0;
    int i = 0; // variable for maintaining process number

    // looping till all the processes are done
    while (rem != 0)
    {
        //if remaining time of process is less than quantum time
        //then the remaining time is set to 0
        if (remaining_time[i] <= q && remaining_time[i] > 0)
        {
            elapsed_time += remaining_time[i];
            remaining_time[i] = 0;
            flag = 1;
        }

        //if remaining time of a process is greater than 0
        //quantum time is subtracted from the remaining time
        else if (remaining_time[i] > 0)
        {
            remaining_time[i] -= q;
            elapsed_time += q;
        }

        if (remaining_time[i] == 0 && flag)
        {
            //if a process is completed the remaining process decreases by one
            rem--;

            //turnaround time of a a process is calculated as elapsed time - arrival time
            turn_time[i] = elapsed_time - arr_time[i];

            //wait time is calculated as turnaround time - burst time
            wait_time[i] = elapsed_time - arr_time[i] - bur_time[i];
            flag = 0;
        }

        if (i == n - 1)
            i = 0;
        else if (arr_time[i + 1] <= elapsed_time)
            i++;
        else
            i = 0;
    }
    //Displaying the processes with all details
    cout << "ProcessID   "
         << "Arrival time    "
         << "Burst time       "
         << "Waiting time  "
         << "Turnaround Time  "
         << "\n";
    int wtsum = 0;
    int tatsum = 0;
    for (int i = 0; i < n; i++)
    {
        tatsum += turn_time[i];
        wtsum += wait_time[i];
        cout << "   " << pro[i] << "\t\t " << arr_time[i] << "\t\t " << bur_time[i] << "\t\t " << wait_time[i] << "\t\t " << turn_time[i] << "\n";
    }
    cout << "\n";

    //Displaying average wating time
    cout << "Average waiting time = " << (float)wtsum / n;
    cout << "\n";

    //Diplaying average turn around time
    cout << "Average turn around time = " << (float)tatsum / n;
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

    for (int i = 0; i < size; i++)
    {
        // calculating total for the average
        total_TAT += tat[i];
        total_WT += wt[i];
        //printing
        cout << "Process: " << i + 1 << " ";
        cout << "Waiting Time: " << wt[i] << " ";
        cout << "Turn Around Time: " << tat[i] << endl;
        cout << endl;
    }
    //printing averages
    cout << "Average Waiting Time : " << (double)total_WT / size << endl;
    cout << "Average Turn Around Time : " << (double)total_TAT / size << endl;
}

void fcfs()
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
    }
    int wt[size];  //waiting time of each process
    int tat[size]; //turn around time for each process
    int total_TAT = 0, total_WT = 0;

    //finding waiting time
    //Exec stores execution time for each process
    int Exec[size];
    //Execution and waiting time for process 0 is 0
    Exec[0] = 0;
    wt[0] = 0;
    for (int i = 1; i < size; i++)
    {
        Exec[i] = Exec[i - 1] + bt[i - 1];
        // wt is Execution time - arrival time clearly
        wt[i] = Exec[i] - at[i];
        if (wt[i] < 0)
        {
            wt[i] = 0;
        }
    }

    //tat = wt + bt for each process clearly
    for (int i = 0; i < size; i++)
    {
        tat[i] = bt[i] + wt[i];
    }

    cout << endl;
    for (int i = 0; i < size; i++)
    {
        // calculating total for the average
        total_TAT += tat[i];
        total_WT += wt[i];
        cout << "Process: " << i + 1 << " ";
        cout << "Waiting Time: " << wt[i] << " ";
        cout << "Turn Around Time: " << tat[i] << endl;
        cout << endl;
    }
    //printing averages
    cout << "Average Waiting Time : " << (double)total_WT / size << endl;
    cout << "Average Turn Around Time : " << (double)total_TAT / size << endl;
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

    cout << "Enter the processid, arrival time and burst time for each process" << endl;

    for (i = 0; i < n; i++)
    {
        cin >> arr[i].pid >> arr[i].at >> arr[i].bt;
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

    cout << "PID\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (i = 0; i < n; i++)
    {
        cout << arr[i].pid << "\t" << arr[i].at << "\t" << arr[i].bt << "\t" << arr[i].ct << "\t" << arr[i].tat << "\t" << arr[i].wt << endl;
    }

    cout << "The average turnaround time is: " << float(sumtat) / float(n) << endl;
    cout << "The average waiting time is: " << float(sumwt) / float(n) << endl;
}

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
    cout << "Enter no of processes" << endl;
    cin >> n;

    cout << "Enter the timeslice" << endl;
    cin >> timeslice;

    struct processes arr[n];
    struct processes k; // temporary structure used in swapping

    cout << "Enter the processid, arrival time and burst time for each process" << endl;

    for (i = 0; i < n; i++)
    {
        cin >> arr[i].pid >> arr[i].at >> arr[i].bt;
        arr[i].rembt = arr[i].bt;
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
    cout << "PID\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (i = 0; i < n; i++)
    {
        cout << arr[i].pid << "\t" << arr[i].at << "\t" << arr[i].bt << "\t" << arr[i].ct << "\t" << arr[i].tat << "\t" << arr[i].wt << endl;
    }

    cout << "The average turnaround time is: " << float(sumtat) / float(n) << endl;
    cout << "The average waiting time is: " << float(sumwt) / float(n) << endl;
}

//priority premptive
struct Process
{
    int processID;
    int burstTime;
    int tempburstTime;
    int responsetime;
    int arrivalTime;
    int priority;
    int outtime;
    int intime;
};

// It is used to include all the valid and eligible
// processes in the heap for execution. heapsize defines
// the number of processes in execution depending on
// the current time currentTime keeps a record of
// the current CPU time.
void insert(Process Heap[], Process value, int *heapsize,
            int *currentTime)
{
    int start = *heapsize, i;
    Heap[*heapsize] = value;
    if (Heap[*heapsize].intime == -1)
        Heap[*heapsize].intime = *currentTime;
    ++(*heapsize);

    // Ordering the Heap
    while (start != 0 && Heap[(start - 1) / 2].priority >
                             Heap[start].priority)
    {
        Process temp = Heap[(start - 1) / 2];
        Heap[(start - 1) / 2] = Heap[start];
        Heap[start] = temp;
        start = (start - 1) / 2;
    }
}

// It is used to reorder the heap according to
// priority if the processes after insertion
// of new process.
void order(Process Heap[], int *heapsize, int start)
{
    int smallest = start;
    int left = 2 * start + 1;
    int right = 2 * start + 2;
    if (left < *heapsize && Heap[left].priority <
                                Heap[smallest].priority)
        smallest = left;
    if (right < *heapsize && Heap[right].priority <
                                 Heap[smallest].priority)
        smallest = right;

    // Ordering the Heap
    if (smallest != start)
    {
        Process temp = Heap[smallest];
        Heap[smallest] = Heap[start];
        Heap[start] = temp;
        order(Heap, heapsize, smallest);
    }
}

// This function is used to find the process with
// highest priority from the heap. It also reorders
// the heap after extracting the highest priority process.
Process extractminimum(Process Heap[], int *heapsize,
                       int *currentTime)
{
    Process min = Heap[0];
    if (min.responsetime == -1)
        min.responsetime = *currentTime - min.arrivalTime;
    --(*heapsize);
    if (*heapsize >= 1)
    {
        Heap[0] = Heap[*heapsize];
        order(Heap, heapsize, 0);
    }
    return min;
}

// Compares two intervals according to staring times.
bool compare(Process p1, Process p2)
{
    return (p1.arrivalTime < p2.arrivalTime);
}

int prevtime = -1;
// This function is responsible for executing
// the highest priority extracted from Heap[].
void scheduling(Process Heap[], Process array[], int n,
                int *heapsize, int *currentTime)
{

    if (heapsize == 0)
        return;

    Process min = extractminimum(Heap, heapsize, currentTime);
    min.outtime = *currentTime + 1;
    --min.burstTime;
    if (prevtime != *currentTime)
    {
        printf("  %d\t   %d \n",
               *currentTime, min.processID);
        prevtime = *currentTime;
    }

    // If the process is not yet finished
    // insert it back into the Heap*/
    if (min.burstTime > 0)
    {
        insert(Heap, min, heapsize, currentTime);
        return;
    }

    for (int i = 0; i < n; i++)
        if (array[i].processID == min.processID)
        {
            array[i] = min;
            break;
        }
}

// This function is responsible for
// managing the entire execution of the
// processes as they arrive in the CPU
// according to their arrival time.
void priority(Process array[], int n)
{
    sort(array, array + n, compare);

    int totalwaitingtime = 0, totalbursttime = 0,
        totalturnaroundtime = 0, i, insertedprocess = 0,
        heapsize = 0, currentTime = array[0].arrivalTime,
        totalresponsetime = 0;

    Process Heap[4 * n];

    // Calculating the total burst time
    // of the processes
    for (int i = 0; i < n; i++)
    {
        totalbursttime += array[i].burstTime;
        array[i].tempburstTime = array[i].burstTime;
    }
    printf("At\tProcess\n");
    // Inserting the processes in Heap
    // according to arrival time
    do
    {
        if (insertedprocess != n)
        {
            for (i = 0; i < n; i++)
            {
                if (array[i].arrivalTime == currentTime)
                {
                    ++insertedprocess;
                    array[i].intime = -1;
                    array[i].responsetime = -1;
                    insert(Heap, array[i], &heapsize, &currentTime);
                }
            }
        }

        scheduling(Heap, array, n, &heapsize, &currentTime);
        ++currentTime;
        if (heapsize == 0 && insertedprocess == n)
            break;
    } while (1);

    for (int i = 0; i < n; i++)
    {
        totalresponsetime += array[i].responsetime;
        totalwaitingtime += (array[i].outtime - array[i].intime -
                             array[i].tempburstTime);
        totalbursttime += array[i].burstTime;
    }
    printf("Average waiting time = %f\n",
           ((float)totalwaitingtime / (float)n));
    printf("Average response time =%f\n",
           ((float)totalresponsetime / (float)n));
    printf("Average turn around time = %f\n",
           ((float)(totalwaitingtime + totalbursttime) / (float)n));
}

// Driver code
void priority_premptive()
{
    int n, i;
    cout << "Enter the number of processes: ";
    cin >> n;

    Process a[n];
    for (i = 0; i < n; i++)
    {
        a[i].processID = i + 1;
        printf("Enter the Arrival time of Process[%d]: ", i + 1);
        cin >> a[i].arrivalTime;
        printf("Enter the Burst time of Process[%d]: ", i + 1);
        cin >> a[i].burstTime;
        printf("Enter the Priority of Process[%d]: ", i + 1);
        cin >> a[i].priority;
    }

    priority(a, n);
    return;
}