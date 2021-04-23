#include <bits/stdc++.h>
#include "header.h"
#define CYN "\e[0;96m"
#define CYNB "\e[1;96m"
#define reset "\e[0m"

using namespace std;

void Scheduling()
{
    int choice;

    while (1)
    {
        cout << "-------------------------------\n";
        printf(CYNB "Scheduling Algorithms\n" reset);
        cout << "\t1. FCFS\n";
        cout << "\t2. SJF\n";
        cout << "\t3. RoundRobin\n";
        cout << "\t4. Priority_Pre-emptive\n";
        cout << "\t5. SRTF\n";
        cout << "\t6. LJF\n";
        cout << "\t7. LRTF\n";
        cout << "\t8. HRRN\n";
        cout << "\t9. Exit Scheduling\n";
        cout << "-------------------------------\n";

        cout << "\nEnter your choice: ";
        scanf("%d", &choice);
        cout << "\n";
        if (choice != 9)
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
            cout << "Priority_Pre-emptive\n";
            priority_premptive();
            break;
        }
        case 5:
        {
            cout << "SRTF\n";
            srtf();
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
            hrrn();
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
        {
            cout << "\033[1;31mWrong Input\033[0m\n";
            break;
        }
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
        printf(CYNB "Page Replacement Algorithms\n" reset);
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
        {
            cout << "\033[1;31mWrong Input\033[0m\n";
            break;
        }
        }
        printf("\n\n");
    }
}
void DiskScheduling()
{

    int choice;

    while (1)
    {
        cout << "-------------------------------\n";
        printf(CYNB "Disk Scheduling\n" reset);
        cout << "\t1. FIFO\n";
        cout << "\t2. SCAN\n";
        cout << "\t3. CSCAN\n";
        cout << "\t4. LOOK\n";
        cout << "\t5. CLOOK\n";
        cout << "\t6. SSTF\n";
        cout << "\t7. Exit Disk Scheduling\n";
        cout << "-------------------------------\n";

        cout << "\nEnter your choice: ";
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
            disk_scan();
            break;
        }
        case 3:
        {
            disk_cscan();
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
            cout << "______________________________________________________________\n\n";
            cout << "Exit Disk Scheduling........\n";
            cout << "______________________________________________________________\n\n";
            return;

            break;
        }
        default:
        {
            cout << "\033[1;31mWrong Input\033[0m\n";
            break;
        }
        }
        printf("\n\n");
    }
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
    printf(CYNB "Memory Management\n" reset);
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
            return;
            break;
        }
        default:
        {
            cout << "\033[1;31mWrong Input\033[0m\n";
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
            return;
            break;
        }
        default:
        {
            cout << "\033[1;31mWrong Input\033[0m\n";
            break;
        }
        }
    }
}

void Synchronization()
{
    int ch;

    while (1)
    {
        cout << "\n-------------------------------\n";
        printf(CYNB "Synchronization\n" reset);
        cout << "\t1. Producer Consumer Problem\n";
        cout << "\t2. Readers Writers Problem\n";
        cout << "\t3. Dining Philosophers Problem\n";
        cout << "\t4. Exit Synchronization\n";
        cout << "-------------------------------\n";
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
            dining_philosopher();
            break;

        case 4:
            cout << "______________________________________________________________\n";
            cout << "\nExit Synchronization........\n";
            cout << "______________________________________________________________\n\n";
            return;

        default:
            cout << "\033[1;31mWrong Input\033[0m\n";
            break;
        }
    }
}

// Function to display the menu
void menu()
{
    printf(CYN "\n\t-------------------------------\n" reset);
    printf("\t\t\033[1;37mMain Menu\n\033[0m");
    printf(CYN "\t-------------------------------\n" reset);
    printf(CYN "\t1. Scheduling algorithms\n" reset);
    printf(CYN "\t2. Synchronization algoritms\n" reset);
    printf(CYN "\t3. Bankers algorithm\n" reset);
    printf(CYN "\t4. Memory Management\n" reset);
    printf(CYN "\t5. Page Replacement algorihm\n" reset);
    printf(CYN "\t6. Disc Scheduling Algorithm\n" reset);
    printf(CYN "\t7. exit\n" reset);
    printf(CYN "\t-------------------------------\n" reset);
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
    {
        cout << "\033[1;31mWrong Input\033[0m\n";
        break;
    }
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
