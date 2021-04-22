#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>
#include "scheduling.cpp"
#include "page_replacement.cpp"
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
    cout << "Press 7 to LRTF\n";
    cout << "Press 8 to exit Scheduling\n";
    cout << "Enter your choice:\n";
    cout << "Choice is " << choice << endl;
    while (1)
    {

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
            //    LJF();
            break;
        }
        case 7:
        {
            //LRTF();

            break;
        }
        case 8:
        {
            cout << "Bye From Scheduling";
            return;
            break;
        }
        default:
            printf("Wrong Input\n");
        }
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
    cout << "Enter your choice:\n";
    cout << "Choice is " << choice << endl;
    while (1)
    {

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
            //  mru_pra();
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
    }
}
sem_t s_empty;
sem_t full;
int buffersize, curr_time, max_rbt, reader_count;
pthread_mutex_t mex;

struct process
{
    int at, bt, pid;
} p_w[10], c_r[10];

//function for time delay
void waitFor(unsigned int secs)
{
    unsigned int retTime = time(0) + secs; // Get finishing time.
    while (time(0) < retTime)
        ; // Loop until it arrives.
}

bool proc_sorter(struct process p1, struct process p2)
{
    return p1.at < p2.at;
}
void *producer(void *pno)
{
    sem_wait(&s_empty);

    // wait while some other process in in Critical Section
    pthread_mutex_lock(&mex);
    //critical section
    cout << "t = " << curr_time << " : ----->producer " << p_w[*((int *)pno)].pid << " is producing\n";
    curr_time += p_w[*((int *)pno)].bt;

    //Release locks
    pthread_mutex_unlock(&mex);
    sem_post(&full);

    return NULL;
}

void *consumer(void *cno)
{
    sem_wait(&full);

    // wait if another process is using critical section
    pthread_mutex_lock(&mex);
    //critical section
    cout << "t = " << curr_time << " : ----->consumer " << c_r[*((int *)cno)].pid << " is consuming\n";
    curr_time += c_r[*((int *)cno)].bt;

    // release the locks
    pthread_mutex_unlock(&mex);
    sem_post(&s_empty);

    return NULL;
}

void producer_consumer_main()
{
    pthread_mutex_init(&mex, NULL);
    int i, n, m, p_i = 0, c_i = 0;
    cout << "\nEnter buffer size: ";
    cin >> buffersize;
    sem_init(&s_empty, 0, buffersize);
    sem_init(&full, 0, 0);

    //accept details about producers
    cout << "\nEnter number of Producers: ";
    cin >> n;
    pthread_t prod_thread[n];
    for (i = 0; i < n; i++)
    {
        cout << "\nEnter arrival time for producer " << i + 1 << " : ";
        cin >> p_w[i].at;
        cout << "Enter burst time for producer " << i + 1 << " : ";
        cin >> p_w[i].bt;
        p_w[i].pid = i + 1;
    }
    sort(p_w, p_w + n, proc_sorter);

    //accept details about consumers
    cout << "\nEnter number of Consumers: ";
    cin >> m;
    pthread_t cons_thread[m];
    for (i = 0; i < m; i++)
    {
        cout << "\nEnter arrival time for consumer " << i + 1 << " : ";
        cin >> c_r[i].at;
        cout << "Enter burst time for consumer " << i + 1 << " : ";
        cin >> c_r[i].bt;
        c_r[i].pid = i + 1;
    }
    sort(c_r, c_r + m, proc_sorter);

    cout << "\n";
    //schedule processes in fcfs manner with priority to producers
    int lpi, lci;
    while (p_i < n && c_i < m)
    {
        lpi = 0;
        lci = 0;
        if (p_w[p_i].at <= c_r[c_i].at)
        {
            if (curr_time < p_w[p_i].at)
                curr_time = p_w[p_i].at;
            pthread_create(&prod_thread[p_w[p_i].pid - 1], NULL, &producer, (void *)&(p_w[p_i]));
            waitFor(1);
            //processes that wait
            while (lpi < n && lci < m)
            {
                if (p_w[lpi].at < curr_time && p_w[lpi].at >= curr_time - p_w[p_i].bt && lpi != p_i)
                    cout << "t = " << p_w[lpi].at << " : producer " << p_w[lpi].pid << " is waiting\n";
                lpi++;

                if (c_r[lci].at < curr_time && c_r[lci].at >= curr_time - p_w[p_i].bt)
                    cout << "t = " << c_r[lci].at << " : consumer " << c_r[lci].pid << " is waiting\n";
                lci++;
            }
            p_i++;
        }
        else
        {
            if (curr_time < c_r[c_i].at)
                curr_time = c_r[c_i].at;
            pthread_create(&cons_thread[c_r[c_i].pid - 1], NULL, &consumer, (void *)&(c_r[c_i]));
            waitFor(1);
            //processes that wait
            while (lpi < n && lci < m)
            {
                if (p_w[lpi].at < curr_time && p_w[lpi].at >= curr_time - c_r[c_i].bt && lci != c_i)
                    cout << "t = " << p_w[lpi].at << " : producer " << p_w[lpi].pid << " is waiting\n";
                lpi++;

                if (c_r[lci].at < curr_time && c_r[lci].at >= curr_time - c_r[c_i].bt)
                    cout << "t = " << c_r[lci].at << " : consumer " << c_r[lci].pid << " is waiting\n";
                lci++;
            }
            c_i++;
        }
    }
    //remaining producers
    while (p_i < n)
    {
        if (curr_time < p_w[p_i].at)
            curr_time = p_w[p_i].at;
        pthread_create(&prod_thread[p_w[p_i].pid - 1], NULL, &producer, (void *)&(p_w[p_i]));
        p_i++;
        waitFor(1);
    }
    //remaining consumers
    while (c_i < m)
    {
        if (curr_time < c_r[c_i].at)
            curr_time = c_r[c_i].at;
        pthread_create(&cons_thread[c_r[c_i].pid - 1], NULL, &consumer, (void *)&(c_r[c_i]));
        c_i++;
        waitFor(1);
    }
    //join all threads
    for (int i = 0; i < n; i++)
    {
        pthread_join(prod_thread[i], NULL);
    }
    for (int i = 0; i < m; i++)
    {
        pthread_join(cons_thread[i], NULL);
    }

    cout << "t = " << curr_time << " : all processes completed.\n\n";
    pthread_mutex_destroy(&mex);
    sem_destroy(&s_empty);
    sem_destroy(&full);
    return;
}

void *writer(void *wno)
{

    sem_wait(&full);

    //critical section
    cout << "t = " << curr_time << " : ----->writer " << c_r[*((int *)wno)].pid << " is writing\n";
    curr_time += c_r[*((int *)wno)].bt;

    sem_post(&full);
    return NULL;
}

void *reader(void *rno)
{
    // wait if another process is using critical section
    pthread_mutex_lock(&mex);
    reader_count++;
    //if its the first reader, lock semaphore so writer cant write
    if (reader_count == 1)
        sem_wait(&full);
    pthread_mutex_unlock(&mex);
    //critical section
    cout << "t = " << curr_time << " : ----->reader " << p_w[*((int *)rno)].pid << " is reading\n";
    max_rbt = p_w[*((int *)rno)].bt > max_rbt ? c_r[*((int *)rno)].bt : max_rbt;
    waitFor(0.5);

    pthread_mutex_lock(&mex);
    reader_count--;
    //if its the last reader then increment the time and let writer write
    if (reader_count == 0)
    {
        curr_time += max_rbt;
        max_rbt = 0;
        sem_post(&full);
    }
    // release the lock on mutex
    pthread_mutex_unlock(&mex);
    return NULL;
}

void reader_writer_main()
{

    pthread_mutex_init(&mex, NULL);
    int i, n, m, w_i = 0, r_i = 0;
    //accepting details about writers
    cout << "\nEnter number of Writers: ";
    cin >> n;
    pthread_t write_thread[n];
    for (i = 0; i < n; i++)
    {
        cout << "\nEnter arrival time for writer " << i + 1 << " : ";
        cin >> p_w[i].at;
        cout << "Enter burst time for writer " << i + 1 << " : ";
        cin >> p_w[i].bt;
        p_w[i].pid = i + 1;
    }
    sort(p_w, p_w + n, proc_sorter);
    //accept details about readers
    printf("\nEnter number of Readers: ");
    cin >> m;
    pthread_t read_thread[m];
    for (i = 0; i < m; i++)
    {
        cout << "\nEnter arrival time for reader " << i + 1 << " : ";
        cin >> c_r[i].at;
        cout << "Enter burst time for reader " << i + 1 << " : ";
        cin >> c_r[i].bt;
        c_r[i].pid = i + 1;
    }
    sort(c_r, c_r + m, proc_sorter);
    cout << "\n";
    //schedule processes using fcfs, with priority to writer
    int lwi, lri;
    while (w_i < n && r_i < m)
    {
        lwi = 0;
        lri = 0;
        if (p_w[w_i].at <= c_r[r_i].at)
        {
            if (curr_time < p_w[w_i].at)
                curr_time = p_w[w_i].at;
            pthread_create(&write_thread[p_w[w_i].pid - 1], NULL, &writer, (void *)&(p_w[w_i]));
            waitFor(1);
            //print all the waiting processes
            while (lwi < n && lri < m)
            {
                if (p_w[lwi].at < curr_time && p_w[lwi].at >= curr_time - p_w[w_i].bt && lwi != w_i)
                    cout << "t = " << p_w[lwi].at << " : writer " << p_w[lwi].pid << " is waiting\n";
                lwi++;

                if (c_r[lri].at < curr_time && c_r[lri].at >= curr_time - p_w[w_i].bt)
                    cout << "t = " << c_r[lri].at << " : reader " << c_r[lri].pid << " is waiting\n";
                lri++;
            }
            w_i++;
        }
        else
        {
            //accept all readers that have arrived
            while (c_r[r_i].at <= curr_time && r_i < m)
            {
                pthread_create(&read_thread[c_r[r_i].pid - 1], NULL, &reader, (void *)&(c_r[r_i]));
                r_i++;
            }
            waitFor(1);
        }
    }
    //remaining writers
    while (w_i < n)
    {
        if (curr_time < p_w[w_i].at)
            curr_time = p_w[w_i].at;
        pthread_create(&write_thread[p_w[w_i].pid - 1], NULL, &writer, (void *)&(p_w[w_i]));
        w_i++;
        waitFor(1);
    }
    //remaining readers
    while (r_i < m)
    {
        if (curr_time < c_r[r_i].at)
            curr_time = c_r[r_i].at;
        pthread_create(&read_thread[c_r[r_i].pid - 1], NULL, &reader, (void *)&(c_r[r_i]));
        r_i++;
    }
    //join all threads
    for (int i = 0; i < n; i++)
    {
        pthread_join(write_thread[i], NULL);
    }
    for (int i = 0; i < m; i++)
    {
        pthread_join(read_thread[i], NULL);
    }

    cout << "t = " << curr_time << " : all processes completed.\n\n";
    pthread_mutex_destroy(&mex);
    sem_destroy(&full);
    return;
}

void Synchronization()
{
    int ch;
    cout << "\n------------------SYNCHRONIZATION--------------------\n\n";
    while (1)
    {
        cout << "Press 1 for Producer Consumer Problem\n";
        cout << "Press 2 for Readers Writers Problem\n";
        cout << "Press 3 to exit Synchronization\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            curr_time = 0;
            producer_consumer_main();
            break;

        case 2:
            curr_time = 0;
            max_rbt = 0;
            reader_count = 0;
            reader_writer_main();
            break;

        case 3:
            cout << "Exiting Synchronization...";
            return;

        default:
            printf("Wrong Input\n");
        }
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

    void available_resources()
    { // Function to calculate available resource instances
        int sum, i, j;
        for (i = 0; i < r_no; i++)
        {
            sum = 0;
            for (j = 0; j < p_no; j++)
            {
                sum += allocated[j][i];
            }
            available[i] = instances[i] - sum;
        }
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

    cout << "Enter the allocated resources of each process(A B C ...)\n";
    for (i = 0; i < t.p_no; i++)
    {

        cout << "Process P" << i + 1 << ": ";
        for (j = 0; j < t.r_no; j++)
            cin >> t.allocated[i][j];
    }

    cout << "Enter the Maximum required resources of each process(A B C ...)\n";
    for (i = 0; i < t.p_no; i++)
    {

        cout << "Process P" << i + 1 << ": ";
        for (j = 0; j < t.r_no; j++)
            cin >> t.max_need[i][j];
    }

    t.available_resources(); // Calculates the available resources
    t.remaining_required();  // Updates the value of remaining resources required for each process
    t.print_table();         // Prints the table
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

// Function to display the menu
void menu()
{
    cout << "Press 1 for Scheduling algorithms\n";
    cout << "Press 2 for Synchronization algoritms\n";
    cout << "Press 3 for Bankers algorithm\n";
    cout << "Press 4 for Paging algorithm\n";
    cout << "Press 5 for Page Replacement algorihm\n";
    cout << "Press 6 for Disc Scheduling Algorithm\n";
    cout << "Press 7 to exit\n";
}

// Function to calculate and display the result
void result(int choice, int a, int b)
{

    // Display the result
    switch (choice)
    {
    case 1:
    {
        // Scheduling();
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
        // Paging();
        break;
    }
    case 5:
    {
        // PageReplacement();
        break;
    }
    case 6:
    {
        //    DiskScheduling();
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

    // Get the two numbers
    int a = 5, b = 7;

    int choice, res;

    // Display the menu
    menu();

    // Enter the choice
    cout << "Enter your choice:\n";
    cin >> choice;
    cout << "Choice is " << choice << endl;

    // Display the result
    // according to the choice
    result(choice, a, b);

    //these are the new codes I have added
    // fcfs();
    // sjf();
    // roundRobin();
    // pagingFIFO();

    return 0;
}
