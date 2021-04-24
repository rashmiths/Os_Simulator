
#include <bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define GRN "\e[0;92m"
#define YEL "\e[0;93m"
#define RED "\e[0;91m"
#define reset "\e[0m"
using namespace std;

sem_t full;
sem_t empty;
pthread_mutex_t mex;

int buffer[10];
int n;

void *producer(void *param)
{
    printf("Producer %d is waiting\n", (*(int *)param));
    int item = rand() % 10;

    sem_wait(&empty);
    pthread_mutex_lock(&mex);
    printf(GRN "Producer %d produces data : %d \n" reset, (*(int *)param), item);
    buffer[++n] = item;
    sleep(2);

    pthread_mutex_unlock(&mex);
    sem_post(&full);
    return NULL;
}

void *consumer(void *param)
{
    printf("Consumer %d is waiting\n", (*(int *)param));

    sem_wait(&full);
    pthread_mutex_lock(&mex);

    printf(YEL "Consumer %d consumes item : %d \n" reset, (*(int *)param), buffer[n--]);
    sleep(1);
    pthread_mutex_unlock(&mex);
    sem_post(&empty);
    return NULL;
}

void producer_consumer()
{
    pthread_mutex_init(&mex, NULL);
    //pthread_mutex_init(&mutex,NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 10);
    n = 0;

    int i, n_p, n_c;

    cout << "\nEnter number of producers: ";
    cin >> n_p;

    cout << "Enter number of consumers: ";
    cin >> n_c;

    pthread_t producerThread[n_p], consumerThread[n_c];
    cout << "\n";

    int index[10];
    for (i = 0; i < 10; i++)
        index[i] = i + 1;

    for (i = 0; i < n_c; i++)
        pthread_create(&consumerThread[i], NULL, consumer, &index[i]);

    for (i = 0; i < n_p; i++)
        pthread_create(&producerThread[i], NULL, producer, &index[i]);

    for (i = 0; i < n_p; i++)
        pthread_join(producerThread[i], NULL);

    for (i = 0; i < n_c; i++)
        pthread_join(consumerThread[i], NULL);

    return;
}

sem_t wrt;
int val = 1, readerCount;

void *writer(void *param)
{
    printf("Writer %d is waiting\n", *(int *)param);
    sem_wait(&wrt);
    val = rand() % 10;
    printf(GRN "Writer %d writes data : %d \n" reset, (*(int *)param), val);
    sleep(2);

    sem_post(&wrt);
    return NULL;
}

void *reader(void *param)
{
    printf("Reader %d is waiting\n", (*(int *)param));
    pthread_mutex_lock(&mex);
    readerCount++;
    //if its the first reader, lock semaphore so writer cant write
    if (readerCount == 1)
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mex);
    printf(YEL "Reader %d reads data : %d \n" reset, (*(int *)param), val);
    sleep(5);

    pthread_mutex_lock(&mex);
    readerCount--;
    //if its the last reader then increment the time and let writer write
    if (readerCount == 0)
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mex);

    return NULL;
}

void reader_writer()
{
    readerCount = 0;
    pthread_mutex_init(&mex, NULL);
    sem_init(&wrt, 0, 1);

    int n_r, n_w, i;

    cout << "Enter number of readers: ";
    cin >> n_r;
    cout << "Enter number of writers: ";
    cin >> n_w;
    cout << "\n";

    pthread_t readerThread[n_r], writerThread[n_w];

    int index[20];
    for (i = 0; i < 20; i++)
        index[i] = i + 1;

    for (i = 0; i < n_w; i++)
        pthread_create(&writerThread[i], NULL, writer, &index[i]);

    for (i = 0; i < n_r; i++)
        pthread_create(&readerThread[i], NULL, reader, &index[i]);

    for (i = 0; i < n_w; i++)
    {
        pthread_join(writerThread[i], NULL);
    }
    for (i = 0; i < n_r; i++)
    {
        pthread_join(readerThread[i], NULL);
    }

    pthread_mutex_destroy(&mex);
    sem_destroy(&wrt);

    return;
}

//dining philo

sem_t allowed;
sem_t chopstick[10];

void *tryEat(void *num)
{
    int phil = *(int *)num;
    printf(YEL "\nPhilosopher %d is hungry" reset, phil);
    sem_wait(&allowed);
    sem_wait(&chopstick[phil]);
    printf(GRN "\nPhilosopher %d picked up chopstick %d" reset, phil, phil);
    sem_wait(&chopstick[(phil + 1) % n]);
    printf(GRN "\nPhilosopher %d picked up chopstick %d" reset, phil, (phil + 1) % n);

    printf(RED "\nPhilosopher %d is eating" reset, phil);

    sleep(2);
    printf("\nPhilosopher %d is thinking", phil);

    sem_post(&chopstick[(phil + 1) % 5]);
    sem_post(&chopstick[phil]);
    sem_post(&allowed);
    return NULL;
}

void dining_philosopher()
{
    cout << "\nEnter number of philosophers : ";
    cin >> n;
    int i, index[n];
    pthread_t tid[n];

    sem_init(&allowed, 0, n - 1);

    for (i = 0; i < n; i++)
        sem_init(&chopstick[i], 0, 1);
    cout << "\nAll philosophers are thinking";
    for (i = 0; i < n; i++)
    {
        index[i] = i;
        pthread_create(&tid[i], NULL, tryEat, (void *)&index[i]);
    }
    for (i = 0; i < n; i++)
        pthread_join(tid[i], NULL);
    cout << "\n";

    for (i = 0; i < n; i++)
        sem_destroy(&chopstick[i]);
    sem_destroy(&allowed);
}


sem_t barberBusy, waitingRoom, wakeUpCall;
int freeWRSeats, haircuts;


void *barber(void *params)
{
    haircuts = *(int *) params;
    while(true)
    {
        sem_wait(&wakeUpCall); //waccept a wake up call
        sem_wait(&waitingRoom); // accept a customer so one seat frees up in the waiting room
        freeWRSeats++;
        sem_post(&barberBusy); //barber cuts hair
        haircuts--;
        printf(GRN "Barber is cutting hair\n" reset);
        sleep(1);
        sem_post(&waitingRoom); // realease mutex 
        printf("Number of free waiting room seats = %d\n", freeWRSeats);
        if(haircuts<=0)
            break;
    }
    printf("\nBarber goes back to sleep\n\n");

    return NULL;

}

void *customer(void * params)
{   
    sem_wait(&waitingRoom);
    if(freeWRSeats>0)
    {
        freeWRSeats--;
        printf(YEL "Customer %d takes a seat in the waiting room\n" reset, (*(int *)params));
            sem_post(&wakeUpCall); // send a wake upcall if the barber is asleep
            sleep(1);
            sem_post(&waitingRoom);
            sem_wait(&barberBusy); //wait if the barber is already cutting hair
            printf(GRN "Customer %d is getting a haircut\n" reset,*(int *)params );
    }
    else
    {
        haircuts--;
        sem_post(&waitingRoom);
        printf(RED "Customer %d couldn't get a haircut \nNumber of free waiting room seats = %d\n" reset, *(int *)params, freeWRSeats );
    }

    return NULL;

}


void sleeping_barber()
{
    int i, n_customers, n;
    printf("\nEnter number of waiting room seats: ");
    scanf("%d",&n);

    sem_init(&barberBusy,0,0); //barber is initially asleep
    sem_init(&waitingRoom,0,1); //mutex for waiting room seats (freeWRSeats)
    sem_init(&wakeUpCall,0,0); // number of wake up calls issued by customers
    freeWRSeats=n;

    printf("Enter number of customers: ");
    cin >> n_customers;
    pthread_t customersThread[n_customers];
    pthread_t barberThread;
    pthread_create(&barberThread, NULL, barber, (void *)&n_customers);  

    int index[n_customers];
    cout << endl;
    for(i=0; i<n_customers; i++)
    {
        index[i] = i+1;
        pthread_create(&customersThread[i], NULL, customer, (void *)&index[i]);
    }

    pthread_join(barberThread, NULL);

    for(i=0; i<n_customers; i++)
        pthread_join(customersThread[i], NULL);
    
    sem_destroy(&barberBusy);
    sem_destroy(&waitingRoom);
    sem_destroy(&wakeUpCall);

}