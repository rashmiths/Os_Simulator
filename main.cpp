#include <bits/stdc++.h>
// #include "scheduling.cpp"
// #include "page_replacement.cpp"
// #include "disk_scheduling.cpp"
#include "header.h"
//#include <pthread.h>
//#include <semaphore.h>
using namespace std;

void Scheduling()
{
    int choice;

    while (1)
    {
        cout << "-------------------------------\n";
        cout << "Scheduling Algorithms\n";
        cout << "\t1. FCFS\n";
        cout << "\t2. SJF\n";
        cout << "\t3. RoundRobin\n";
        cout << "\t4. Priority\n";
        cout << "\t5. SRTF\n";
        cout << "\t6. LJF\n";
        cout << "\t7. LRTF\n";
        cout << "\t8. HRRN\n";
        cout << "\t9. Exit Scheduling\n";
        cout << "-------------------------------\n";

        cout << "\nEnter your choice: ";
        scanf("%d", &choice);
        cout << "\n";
        if( choice != 9 )
            cout << "-------------------------------\n";
        switch (choice)
        {
        case 1:
        {   
            cout << "FCFS\n";
            fcfs();
            break;
        }
        case 2:
        {
            cout << "SJF\n";
            sjf();
            break;
        }
        case 3:
        {
            cout << "RR (Round Robin)\n";
            roundRobin();
            break;
        }
        case 4:
        {
            cout << "Priority\n";
            //Priority();
            break;
        }
        case 5:
        {
            cout << "SRTF\n";
            // SRTF();
            break;
        }
        case 6:
        {
            cout << "LJF\n";
            LJF();
            break;
        }
        case 7:
        {
            cout << "LRTF\n";
            LRTF();

            break;
        }
        case 8:
        {
            cout << "HRRN\n";
            //HRRN();
            break;
        }
        case 9:
        {
            cout << "______________________________________________________________\n";
            cout << "\nExit Scheduling........\n";
            cout << "______________________________________________________________\n\n";
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


    while (1)
    {
        cout << "-------------------------------\n";
        cout << "Page Replacement Algorithms\n";
        cout << "\t1. FCFS\n";
        cout << "\t2. LRU\n";
        cout << "\t3. MRU\n";
        cout << "\t4. Optimal\n";
        cout << "\t5. Exit Page Replacement\n";
        cout << "-------------------------------\n";
        
        cout << "\nEnter your choice: ";
        scanf("%d", &choice);
        cout << "\n";
        // cout << "Choice is " << choice << endl;

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
            cout << "______________________________________________________________\n\n";
            cout << "Exit Page Replacement........\n";
            cout << "______________________________________________________________\n\n";
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
    cout << "-------------------------------\n";
    cout << "Disk Scheduling\n";
    cout << "\t1. FIFO\n";
    cout << "\t2. SCAN\n";
    cout << "\t3. CSCAN\n";
    cout << "\t4. LOOK\n";
    cout << "\t5. CLOOK\n";
    cout << "\t6. SSTF\n";
    cout << "\t7. Exit Disk Scheduling\n";
    cout << "-------------------------------\n";

    while (1)
    {
        cout << "\nEnter your choice:\n";
        scanf("%d", &choice);
        cout << "\n";

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
    cout << "-------------------------------\n";
    cout << "Memory Management\n";
    cout << "\t1. Fixed Partition " << endl;
    cout << "\t2. Variable Partitiion " << endl;
    cout << "-------------------------------\n";
    cout << "\nEnter Choice: ";
    cin >> a;
    cout << "\n";
    if (a == 1)
    {
        cout << "-------------------------------\n";
        cout << "Fixed partition: " << endl;
        cout << "\t1. First Fit " << endl;
        cout << "\t2. Best Fit " << endl;
        cout << "\t3. Worst Fit " << endl;
        cout << "\t4. Exit Memory Management" << endl; 
        cout << "-------------------------------\n";
        cout << "Enter Choice: ";
        cin >> b;
        cout << "\n";
        switch (b)
        {
        case 1:
        {
            cout << "-------------------------------\n";
            cout << "First Fit\n";
            MFTfirstfit();
            break;
        }
        case 2:
        {
            cout << "-------------------------------\n";
            cout << "Best Fit\n";
            MFTbestfit();
            break;
        }
        case 3:
        {
            cout << "-------------------------------\n";
            cout << "Worst Fit\n";
            MFTworstfit();
            break;
        }
        case 4:
        {
            cout << "______________________________________________________________\n";
            cout << "\nExit Memory Management........\n";
            cout << "______________________________________________________________\n\n";
            return ;
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
        cout << "-------------------------------\n";
        cout << "Variable Partition: " << endl;
        cout << "\t1. First Fit " << endl;
        cout << "\t2. Best Fit " << endl;
        cout << "\t3. Worst Fit " << endl;
        cout << "\t4. Exit Memory Management" << endl;
        cout << "-------------------------------\n";
        cout << "Enter Choice: ";
        cin >> b;
        cout << "\n";
        switch (b)
        {
        case 1:
        {   
            cout << "-------------------------------\n";
            cout << "First Fit\n";
            MVTfirstfit();
            break;
        }
        case 2:
        {
            cout << "-------------------------------\n";
            cout << "Best Fit\n";
            MVTbestfit();
            break;
        }
        case 3:
        {
            cout << "-------------------------------\n";
            cout << "Worst Fit\n";
            MVTworstfit();
            break;
        }
        case 4:
        {
            cout << "______________________________________________________________\n";
            cout << "\nExit Memory Management........\n";
            cout << "______________________________________________________________\n\n";
            return ;
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

void Synchronization()
{
    int ch;
    cout << "\n------------------SYNCHRONIZATION--------------------\n\n";
    while (1)
    {
        cout << "\t1. Producer Consumer Problem\n";
        cout << "\t2. Readers Writers Problem\n";
        cout << "\t3. Exit Synchronization\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            producer_consumer();
            break;

        case 2:
            reader_writer();
            break;

        case 3:
            cout << "Exiting Synchronization...";
            return;

        default:
            printf("Wrong Input\n");
        }
    }
}


// Function to display the menu
void menu()
{
    cout << "\n-------------------------------\n";
    cout << "\tMain Menu\n";
    cout << "-------------------------------\n";
    cout << "1. Scheduling algorithms\n";
    cout << "2. Synchronization algoritms\n";
    cout << "3. Bankers algorithm\n";
    cout << "4. Memory Management\n";
    cout << "5. Page Replacement algorihm\n";
    cout << "6. Disc Scheduling Algorithm\n";
    cout << "7. exit\n";
    cout << "-------------------------------\n";
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
        Synchronization();
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
        cout << "______________________________________________________________\n";
        cout << "\nThank you......\n";
        cout << "______________________________________________________________\n\n";
        exit(0);
        break;
    }
    default:
        printf("Wrong Input\n");
    }
}

int main()
{

    int choice, res;

    while (1)
    {
        // Display the menu
        menu();
        // Enter the choice
        cout << "\nEnter your choice: ";
        scanf("%d", &choice);
        cout << "\n";
        // cout << "Choice Selected: " << choice << "\n\n";

        // Display the result
        // according to the choice
        result(choice);
    }

    return 0;
}
