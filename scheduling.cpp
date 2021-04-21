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
     cout << "ProcessID   " << "Arrival time    " << "Burst time       " << "Waiting time  " <<"Turnaround Time  " << "\n";
         int wtsum = 0;
         int tatsum = 0;
    for (int i = 0; i < n; i++)
    {
        tatsum += turn_time[i];
        wtsum += wait_time[i];
        cout << "   " << pro[i] << "\t\t " << arr_time[i] << "\t\t " << bur_time[i]<< "\t\t " << wait_time[i] << "\t\t " << turn_time[i] << "\n";
    }
    cout << "\n";

    //Displaying average wating time
    cout << "Average waiting time = " << (float)wtsum / n;
    cout << "\n";

    //Diplaying average turn around time
    cout << "Average turn around time = " <<(float)tatsum / n;
}

void sjf() {

  int size;
  cout << "Enter the number of processes: ";
  cin >> size;

  int at[size];//arrival time of each process
  int bt[size];//burst time of each process

  for (int i = 0; i < size; i++) {
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
  while (comp != size) {
    for (int j = 0; j < size; j++) {
      if ((at[j] <= t) && (rt[j] < minm) && rt[j] > 0) {
        minm = rt[j];
        shortest = j;
        check = true;
      }
    }
    if (check == false) {
      t++;
      continue;
    }

    // decrementing the remaining time

    rt[shortest]--;
    minm = rt[shortest];
    if (minm == 0)
      minm = INT_MAX;

    // If a process gets completly executed

    if (rt[shortest] == 0) {
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

  for (int i = 0; i < size; i++) {
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

void fcfs() {
    int size;
    cout << "Enter the number of processes: ";
    cin >> size;

    int at[size];//arrival time of each process
    int bt[size];//burst time of each process

    for (int i = 0; i < size; i++) {
        cout << "For process " << i + 1 << ":" << endl;
        cout << "Arrival time: ";
        cin >> at[i];
        cout << "Burst time: ";
        cin >> bt[i];
    }
    int wt[size];//waiting time of each process
    int tat[size];//turn around time for each process
    int total_TAT = 0, total_WT = 0;

    //finding waiting time
    //Exec stores execution time for each process
    int Exec[size];
    //Execution and waiting time for process 0 is 0
    Exec[0] = 0;
    wt[0] = 0;
    for (int i = 1; i < size; i++) {
        Exec[i] = Exec[i - 1] + bt[i - 1];
        // wt is Execution time - arrival time clearly
        wt[i] = Exec[i] - at[i];
        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }

    //tat = wt + bt for each process clearly
    for (int i = 0; i < size; i++) {
        tat[i] = bt[i] + wt[i];
    }

    cout << endl;
    for (int i = 0; i < size; i++) {
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