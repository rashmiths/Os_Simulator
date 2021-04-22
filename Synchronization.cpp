
#include <bits/stdc++.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t s_empty;
sem_t full;
sem_t wrt;
int buffersize, curr_time , max_rbt = 0, reader_count = 0;
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

void producer_consumer()
{
    curr_time = 0;
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

    sem_wait(&wrt);

    //critical section
    cout << "t = " << curr_time << " : ----->writer " << c_r[*((int *)wno)].pid << " is writing\n";
    curr_time += c_r[*((int *)wno)].bt;

    sem_post(&wrt);
    return NULL;
}

void *reader(void *rno)
{
    // wait if another process is using critical section
    pthread_mutex_lock(&mex);
    reader_count++;
    //if its the first reader, lock semaphore so writer cant write
    if (reader_count == 1)
        sem_wait(&wrt);
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
        sem_post(&wrt);
    }
    // release the lock on mutex
    pthread_mutex_unlock(&mex);
    return NULL;
}

void reader_writer()
{
    curr_time = 0;

    pthread_mutex_init(&mex, NULL);
    sem_init(&wrt,0,1);
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
            cout <<"entered\n";
            if (curr_time < p_w[w_i].at)
                curr_time = p_w[w_i].at;
            cout << "writer " << p_w[w_i].pid << "\n";
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
    return ;
}