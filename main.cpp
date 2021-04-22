#include <bits/stdc++.h>
// #include "scheduling.cpp"
// #include "page_replacement.cpp"
// #include "disk_scheduling.cpp"
#include "header.h"
using namespace std;

void Scheduling()
{

    int choice;
    cout << "Press 1 for FCFS\n";
    cout << "Press 2 for SJF\n";
    cout << "Press 3 for RoundRobin\n";
    cout << "Press 4 for Priority\n";
    cout << "Press 5 for SRTF\n";
    cout << "Press 6 for LJF\n";
    cout << "Press 7 for LRTF\n";
    cout << "Press 8 for HRRN\n";
    cout << "Press 9 to exit Scheduling\n";

    while (1)
    {
        cout << "Enter your choice: ";
        scanf("%d", &choice);
        cout << "Choice is " << choice << endl;

        switch (choice)
        {
        case 1:
        {
            fcfs();
            break;
        }
        case 2:
        {
            sjf();
            break;
        }
        case 3:
        {
            roundRobin();
            break;
        }
        case 4:
        {
            //Priority();
            break;
        }
        case 5:
        {
            // SRTF();
            break;
        }
        case 6:
        {
            LJF();
            break;
        }
        case 7:
        {
            LRTF();

            break;
        }
        case 8:
        {
            //HRRN();
            break;
        }
        case 9:
        {
            cout << "\n\nBye From Scheduling\n\n";
            return;
            break;
        }
        default:
            printf("Wrong Input\n");
        }
        printf("\n\n");
    }
}

void PageReplacement()
{

    int choice;
    cout << "Press 1 for FCFS\n";
    cout << "Press 2 for LRU\n";
    cout << "Press 3 for MRU\n";
    cout << "Press 4 for Optimal\n";
    cout << "Press 5 to exit Scheduling\n";

    while (1)
    {
        cout << "Enter your choice:\n";
        scanf("%d", &choice);
        cout << "Choice is " << choice << endl;

        switch (choice)
        {
        case 1:
        {
            fifo_pra();
            break;
        }
        case 2:
        {
            lru_pra();
            break;
        }
        case 3:
        {
            mru_pra();
            break;
        }
        case 4:
        {
            optimal_pra();
            break;
        }
        case 5:
        {
            cout << "Bye From PageReplacement";
            return;

            break;
        }
        default:
            printf("Wrong Input\n");
        }
        printf("\n\n");
    }
}
void DiskScheduling()
{

    int choice;
    cout << "Press 1 for FIFO\n";
    cout << "Press 2 for SCAN\n";
    cout << "Press 3 for CSCAN\n";
    cout << "Press 4 for LOOK\n";
    cout << "Press 5 for CLOOK\n";
    cout << "Press 6 for SSTF\n";
    cout << "Press 7 to exit Scheduling\n";

    while (1)
    {
        cout << "Enter your choice:\n";
        scanf("%d", &choice);
        cout << "Choice is " << choice << endl;

        switch (choice)
        {
        case 1:
        {
            disk_fcfs();
            break;
        }
        case 2:
        {
            //disk_scan();
            break;
        }
        case 3:
        {
            //  disk_cscan();
            break;
        }
        case 4:
        {
            disk_look();
            break;
        }
        case 5:
        {
            disk_clook();
            break;
        }
        case 6:
        {
            disk_sstf();
            break;
        }
        case 7:
        {
            cout << "Bye From Disk Scheduling";
            return;

            break;
        }
        default:
            printf("Wrong Input\n");
        }
        printf("\n\n");
    }
}

class Bankers_Table
{ // All the contents of the table

public:
    int r_no, p_no; // Number of resources, Number of processes

    int *instances; // To store the number of instances for each resource
    int *available; // To store the available resources

    int **allocated; // To store the allocated resource for each process
    int **max_need;  // To store the maximum required resource for each process
    int **need;      // To store the required number of resources for each process.

    int available_resources()
    { // Function to calculate available resource instances
        int sum, i, j, flag = 0;
        for (i = 0; i < r_no; i++)
        {
            sum = 0;
            for (j = 0; j < p_no; j++)
            {
                sum += allocated[j][i];
            }
            available[i] = instances[i] - sum;
            if (available[i] < 0)
                flag = 1;
        }
        if (flag == 1)
            return -1;
        return 1;
    }

    void remaining_required()
    {
        int i, j;
        for (i = 0; i < p_no; i++)
            for (j = 0; j < r_no; j++)
                need[i][j] = max_need[i][j] - allocated[i][j];
    }

    // Prints the table
    void print_table()
    {
        int i, j;

        cout << "\nInstances: ";
        for (i = 0; i < r_no; i++)
            cout << instances[i] << " ";

        cout << "\nInitially Available: ";
        for (i = 0; i < r_no; i++)
            cout << available[i] << " ";

        cout << "\nID | Allocated | Total Need | Remaining Need\n";
        for (i = 0; i < p_no; i++)
        {
            cout << "P" << i + 1 << " | ";
            for (j = 0; j < r_no; j++)
                cout << allocated[i][j] << " "; // Allocated instances
            cout << " | ";
            for (j = 0; j < r_no; j++)
                cout << max_need[i][j] << " "; // Maximum required
            cout << " | ";
            for (j = 0; j < r_no; j++)
                cout << need[i][j] << " "; // Remaining instances required
            cout << "\n";
        }
        cout << "\n";
    }
};

int *array_memory_allocation(int size)
{ // Memory Allocation Function for 1-D array
    int *p = new int[size];
    return p;
}

int **matrix_memory_allocation(int col, int row)
{ // Memory Allocation Function for 2-D array
    int **p;
    p = new int *[col];
    for (int i = 0; i < col; i++)
        p[i] = new int[row];
    return p;
}

void bankers_algorithm(Bankers_Table a, int *v, int *f)
{

    int i, j, k, count, flag;

    int temp_avail[a.r_no];
    for (i = 0; i < a.r_no; i++)
        temp_avail[i] = a.available[i];

    count = 0;
    while (count < (a.p_no - 1))
    {
        flag = 0;
        for (i = 0; i < a.p_no; i++)
        {
            if (f[i] == 0)
            {
                for (j = 0; j < a.r_no; j++)
                    if (a.need[i][j] > temp_avail[i])
                        break;

                if (j == a.r_no)
                {
                    for (k = 0; k < a.r_no; k++)
                        temp_avail[k] += a.max_need[i][k];

                    v[count++] = i;
                    f[i] = 1;
                    flag = 1;
                }
            }
        }
    }
    if (flag == 0)
    {
        cout << "\nNo sequence found, Execution UNSAFE\n";
        return;
    }

    cout << "\nSafe sequence found, Execution SAFE\nSequence: ";
    for (i = 0; i < a.p_no; i++)
        cout << "P" << v[i] + 1 << " ";
    cout << "\n\n";
}

int BankersAlgo()
{

    int *v; // Stores the sequence of processes that will be executed
    int *f; // Array to check if the process is executed

    int i, j;
    Bankers_Table t;

    cout << "Banker's Algorithm\n\nEnter the number of Resources: ";
    cin >> t.r_no;

    t.instances = array_memory_allocation(t.r_no);
    t.available = array_memory_allocation(t.r_no);
    v = array_memory_allocation(t.p_no); // Stores the sequence of processes
    f = array_memory_allocation(t.p_no); // Checks if the process is executed

    cout << "Enter the max number of each Resource\n";
    for (i = 0; i < t.r_no; i++)
    {
        printf("%c: ", i + 65);
        cin >> t.instances[i];
    }

    cout << "\nEnter the number of Processes: ";
    cin >> t.p_no;

    t.allocated = matrix_memory_allocation(t.p_no, t.r_no);
    t.max_need = matrix_memory_allocation(t.p_no, t.r_no);
    t.need = matrix_memory_allocation(t.p_no, t.r_no);

    cout << "Enter the allocated resources for each process (A B C ...)\n";
    for (i = 0; i < t.p_no; i++)
    {

        cout << "Process P" << i + 1 << ": ";
        for (j = 0; j < t.r_no; j++)
            cin >> t.allocated[i][j];
    }

    cout << "\nEnter the Maximum required resources for each process (A B C ...)\n";
    for (i = 0; i < t.p_no; i++)
    {

        cout << "Process P" << i + 1 << ": ";
        for (j = 0; j < t.r_no; j++)
            cin >> t.max_need[i][j];
    }

    int check = 0;

    check = t.available_resources(); // Calculates the available resources
    if (check == -1)
    {
        cout << "\nInvalid Number of Available Resources\nExiting Program......\n\n";
        return 0;
    }
    t.remaining_required(); // Updates the value of remaining resources required for each process
    t.print_table();        // Prints the table
    bankers_algorithm(t, v, f);

    return 0;
}

void pagingFIFO()
{
    int vs;                 //virtual memory size
    int ps;                 // physical memory size
    int page;               // page size
    int nf;                 // number of frames
    int np;                 // number of pages
    int pagetable[100];     //page table
    int frames[2][100];     // frames
    bool fs[100] = {false}; // checking if frame is empty or not
    int loop = 1;           // loop variable
    int pageno;             // page number holder
    int offset;             // offset holder
    float pagefaults = 0;   // fault counter
    int flag = 0;           // flag variable
    int i;                  //loop variable
    int index = 0;          // storing index
    float input = 0;        // input counter;

    cout << "Enter the Virtual/Logical Memory Size: ";
    cin >> vs;
    cout << "Enter the Physical Memory Size: ";
    cin >> ps;
    cout << "Enter the Size of the page: ";
    cin >> page;

    np = vs / page;
    nf = ps / page;

    for (i = 0; i < np; i++)
    {
        pagetable[i] = -1;
    }

    for (i = 0; i < nf; i++)
    {
        frames[0][i] = -1;
    }

    cout << "Number of pages in virtual memory:" << np << endl;
    cout << "Number of pages in physical memory:" << nf << endl;

    while (loop == 1)
    {
        cout << endl;
        cout << "Press 1 to add a page into a frame" << endl;
        cout << "Press 2 to stop" << endl;
        cin >> loop;
        if (loop != 1)
            break;

        cout << "Enter the virtual address as told below:" << endl;
        ;
        cout << "Enter the Page number: " << endl;
        cin >> pageno;
        if (pageno > np)
        {
            cout << "Page can't exist due to Virtual Memory Constraint" << endl;
            continue;
        }

        cout << "Enter the Offset: ";
        cin >> offset;

        input++;
        for (i = 0; i < nf; i++)
        {
            if (frames[0][i] == pageno)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 1)
        {
            cout << endl
                 << "The Physical Address for the above virtual address is : " << endl;
            cout << "Frame: " << i << endl;
            cout << "Offset: " << offset;
            flag = 0;
        }
        else
        {
            pagefaults = pagefaults + 1;

            if (fs[index] == false)
            {
                cout << "Page " << pageno << " is not present in the physical memory so page " << pageno << " is accomodated into frame " << index;
                frames[0][index] = pageno;
                frames[1][index] = offset;
                fs[index] = true;
                pagetable[pageno] = index;

                index++;
            }

            else
            {
                cout << "Page " << pageno << " is not present in the physical memory";
                cout << "Page " << pageno << "is accomodated in frame" << index << " after removing page " << frames[0][index];
                pagetable[frames[0][index]] = -1;
                frames[0][index] = pageno;
                frames[1][index] = offset;
                pagetable[pageno] = index;
                index++;
            }

            if (index == nf)
            {
                index = 0;
            }
        }
    }

    cout << endl
         << "Total number of inputs:" << input;
    cout << endl
         << "Total number of page faults:" << pagefaults;

    cout << endl
         << "Page Fault Ratio is: " << pagefaults / input;
    cout << endl;
    cout << endl
         << "Page Table";
    cout << endl
         << "Page number - Frame number" << endl;
    for (i = 0; i < np; i++)
    {
        cout << i << " - " << pagetable[i] << endl;
    }

    cout << endl;
    cout << endl
         << "Memory Table";
    cout << endl
         << "Frame Number - Page Contained" << endl;
    for (i = 0; i < nf; i++)
    {
        cout << i << " - " << frames[0][i] << endl;
    }
}

void MemoryManagement()
{
    int a, b;
    cout << "Enter 1 if you want to do fixed partion " << endl;
    cout << "Enter 2 if you want to do variable partitiion " << endl;
    cin >> a;
    if (a == 1)
    {
        cout << "Enter the algo you want to perform for fixed partition: " << endl;
        cout << "1. First Fit " << endl;
        cout << "2. Best Fit " << endl;
        cout << "3. Worst Fit " << endl;
        cin >> b;
        switch (b)
        {
        case 1:
        {
            MFTfirstfit();
            break;
        }
        case 2:
        {
            MFTbestfit();
            break;
        }
        case 3:
        {
            MFTworstfit();
            break;
        }
        default:
        {
            cout << "Wrong input " << endl;
            break;
        }
        }
    }
    else
    {
        cout << "Enter the algo you want to perform for variable partition: " << endl;
        cout << "1. First Fit " << endl;
        cout << "2. Best Fit " << endl;
        cout << "3. Worst Fit " << endl;
        cin >> b;
        switch (b)
        {
        case 1:
        {
            MVTfirstfit();
            break;
        }
        case 2:
        {
            MVTbestfit();
            break;
        }
        case 3:
        {
            MVTworstfit();
            break;
        }
        default:
        {
            cout << "Wrong input " << endl;
            break;
        }
        }
    }
}

// Function to display the menu
void menu()
{
    cout << "\n     Main Menu       \n";
    cout << "Press 1 for Scheduling algorithms\n";
    cout << "Press 2 for Synchronization algoritms\n";
    cout << "Press 3 for Bankers algorithm\n";
    cout << "Press 4 for Memory Management\n";
    cout << "Press 5 for Page Replacement algorihm\n";
    cout << "Press 6 for Disc Scheduling Algorithm\n";
    cout << "Press 7 to exit\n";
}

// Function to calculate and display the result
void result(int choice)
{

    // Display the result
    switch (choice)
    {
    case 1:
    {
        Scheduling();
        break;
    }
    case 2:
    {
        // Synchronization();
        break;
    }
    case 3:
    {
        BankersAlgo();
        break;
    }
    case 4:
    {
        MemoryManagement();
        break;
    }
    case 5:
    {
        PageReplacement();
        break;
    }
    case 6:
    {
        DiskScheduling();
        break;
    }
    case 7:
    {
        cout << "Thank you\n";
        break;
    }
    default:
        printf("Wrong Input\n");
    }
}

int main()
{

    int choice, res;

    // Display the menu

    while (1)
    {
        menu();
        // Enter the choice
        cout << "Enter your choice:\n";
        scanf("%d", &choice);
        cout << "Choice is " << choice << endl;

        // Display the result
        // according to the choice
        result(choice);
    }

    return 0;
}
