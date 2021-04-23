
#include <bits/stdc++.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;


sem_t full;
sem_t empty;
pthread_mutex_t mex;


int buffer[10];
int n;

void *producer(void *param)
{
    cout << "Producer " << (*(int *)param) << " is waiting\n";
    int item = rand() % 10;

    sem_wait(&empty);
    pthread_mutex_lock(&mex);
    cout << "Producer " << (*(int *) param) << " produces data : " << item << "\n";
    buffer[++n]=item;
    sleep(2);
    
    pthread_mutex_unlock(&mex);
    sem_post(&full);
    return NULL;
}

void *consumer(void *param)
{
    cout << "Consumer " << (*(int *)param) << " is waiting\n";
    
    sem_wait(&full);
    pthread_mutex_lock(&mex);

    cout << "Consumer " << (*(int *) param) << " consumes item : " << buffer[n--] <<"\n";
    sleep(1);
    pthread_mutex_unlock(&mex);
    sem_post(&empty);   
    return NULL;
}

void producer_consumer()
{
    pthread_mutex_init(&mex, NULL);
    //pthread_mutex_init(&mutex,NULL);
    sem_init(&full,0,0);
    sem_init(&empty,0,10);
    n = 0;

    int i,n_p,n_c;

    cout << "\nEnter number of producers: ";
    cin >> n_p;

    cout << "Enter number of consumers: ";
    cin >> n_c;

    pthread_t producerThread[n_p], consumerThread[n_c];
    cout << "\n";

    int index[10];
    for(i=0; i<10; i++)
        index[i] = i+1;

    for(i=0;i<n_c;i++)
        pthread_create(&consumerThread[i],NULL,consumer,&index[i]);

    for(i=0;i<n_p;i++)
        pthread_create(&producerThread[i],NULL,producer,&index[i]);
    
    
    
    for(i=0;i<n_p;i++)
        pthread_join(producerThread[i],NULL);
    
    for(i=0;i<n_c;i++)
        pthread_join(consumerThread[i],NULL);
    
    return;
}

sem_t wrt;
int val = 1, readerCount;




void *writer(void *param)
{
    cout << "Writer " << (*(int *)param) << " is waiting\n";
    sem_wait(&wrt);
    val = rand()%10;
    cout << "Writer " << (*(int *) param) << " writes data : " << val << "\n";
    sleep(2);

    sem_post(&wrt);
    return NULL;
}

void *reader(void *param)
{
    cout << "Reader " << (*(int *)param) << " is waiting\n";
    pthread_mutex_lock(&mex);
    readerCount++;
    //if its the first reader, lock semaphore so writer cant write
    if(readerCount==1)
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mex);
    cout << "Reader " << (*(int *) param) << " reads data : " << val << "\n";
    sleep(5);

    pthread_mutex_lock(&mex);
    readerCount--;
    //if its the last reader then increment the time and let writer write
    if(readerCount==0)
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
    sem_init(&wrt,0,1);


    int n_r, n_w, i;

    cout << "Enter number of readers: ";
    cin >> n_r;
    cout << "Enter number of writers: ";
    cin >> n_w;
    cout << "\n";

    pthread_t readerThread[n_r],writerThread[n_w];

    int index[20];
    for(i=0; i<20; i++)
        index[i] = i+1;

    for(i=0;i<n_w;i++)
        pthread_create(&writerThread[i],NULL,writer,&index[i]);

    for(i=0;i<n_r;i++)
        pthread_create(&readerThread[i],NULL,reader, &index[i]);


    for(i=0;i<n_w;i++)
    {
        pthread_join(writerThread[i],NULL);
    }
    for(i=0;i<n_r;i++)
    {
        pthread_join(readerThread[i],NULL);
    }

    pthread_mutex_destroy(&mex);
    sem_destroy(&wrt);

    return;
}

//dining philo

sem_t allowed;
sem_t chopstick[10];

void * tryEat(void * num)
{
    int phil = *(int *)num;
    printf("\nPhilosopher %d is hungry", phil);
    sem_wait(&allowed);    
    sem_wait(&chopstick[phil]);
    printf("\nPhilosopher %d picked up chopstick %d", phil, phil);
    sem_wait(&chopstick[(phil+1)%n]);
    printf("\nPhilosopher %d picked up chopstick %d" , phil, (phil+1)%n);

    printf("\n->Philosopher %d is eating", phil);

    sleep(2);
    printf("\nPhilosopher %d is thinking", phil);

    sem_post(&chopstick[(phil+1)%5]);
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

    sem_init(&allowed,0,n-1);

    for(i=0;i<n;i++)
        sem_init(&chopstick[i],0,1);
    cout << "\nAll philosophers are thinking";
    for(i=0;i<n;i++){
        index[i] = i;
        pthread_create(&tid[i],NULL, tryEat,(void *)&index[i]);
    }
    for(i=0;i<n;i++)
        pthread_join(tid[i],NULL);
    cout << "\n";

    for(i=0;i<n;i++)
        sem_destroy(&chopstick[i]);
    sem_destroy(&allowed);
}