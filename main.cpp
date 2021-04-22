#include <bits/stdc++.h>
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
    cout << "Press 7 for LRTF\n";
    cout<< "Press 8 for HRRN\n"; 
    cout << "Press 9 to exit Scheduling\n";
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

class Bankers_Table { // All the contents of the table

    public:
        int r_no, p_no; // Number of resources, Number of processes
        
        int *instances; // To store the number of instances for each resource
        int *available; // To store the available resources

        int **allocated; // To store the allocated resource for each process
        int **max_need; // To store the maximum required resource for each process
        int **need; // To store the required number of resources for each process.

        void available_resources(){ // Function to calculate available resource instances
            int sum, i, j;
            for(i=0; i<r_no; i++){
                sum = 0;
                for(j=0; j<p_no; j++){
                    sum += allocated[j][i];
                }
                available[i] = instances[i] - sum;
            }
        }

        void remaining_required(){
            int i, j;
            for(i=0; i<p_no; i++)
                for(j=0; j<r_no; j++)
                    need[i][j] = max_need[i][j] - allocated[i][j];
        }

        // Prints the table
        void print_table(){
            int i, j;

            cout << "\nInstances: ";
            for(i=0; i<r_no; i++) cout << instances[i] << " ";
            
            cout << "\nInitially Available: ";
            for(i=0; i<r_no; i++) cout << available[i] << " ";

            cout << "\nID | Allocated | Total Need | Remaining Need\n";
            for( i=0; i<p_no; i++){
                cout << "P" << i+1 << " | ";
                for( j=0; j<r_no; j++ ) cout << allocated[i][j] << " "; // Allocated instances
                cout << " | ";
                for( j=0; j<r_no; j++ ) cout << max_need[i][j] << " "; // Maximum required
                cout << " | ";
                for( j=0; j<r_no; j++ ) cout << need[i][j] << " "; // Remaining instances required
                cout << "\n";
            }
            cout << "\n";
        }

};

int *array_memory_allocation(int size) { // Memory Allocation Function for 1-D array
    int *p = new int [size];
    return p;
}

int **matrix_memory_allocation(int col, int row) { // Memory Allocation Function for 2-D array
    int **p;
    p = new int* [col];
    for(int i=0; i<col; i++ ) p[i] = new int [row];
    return p;
}

void bankers_algorithm(Bankers_Table a, int* v, int* f) {

    int i, j, k, count, flag;

    int temp_avail[a.r_no];
    for( i=0; i<a.r_no; i++) 
        temp_avail[i] = a.available[i];

    count = 0;
    while( count < (a.p_no-1) ) {
        flag = 0;
        for( i=0; i<a.p_no; i++ ) {
            if( f[i] == 0 )
            {
                for( j=0; j<a.r_no; j++ ) 
                    if( a.need[i][j] > temp_avail[i] ) 
                        break;
                
                if( j == a.r_no ) {
                    for( k=0; k<a.r_no; k++ )
                        temp_avail[k] += a.max_need[i][k];

                    v[count++] = i;
                    f[i] = 1;
                    flag = 1;
                }
            }
        }
    }
    if( flag == 0) {
        cout << "\nNo sequence found, Execution UNSAFE\n";
        return ;
    }

    cout << "\nSafe sequence found, Execution SAFE\nSequence: ";
    for( i=0; i<a.p_no; i++ )
        cout << "P" << v[i] +1 << " ";
    cout << "\n\n";
}

int BankersAlgo() {

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
    for( i=0; i < t.r_no; i++ ) {
        printf("%c: ", i+65);
        cin >> t.instances[i];
    }

    cout << "\nEnter the number of Processes: ";
    cin >> t.p_no;

    t.allocated = matrix_memory_allocation(t.p_no, t.r_no);
    t.max_need = matrix_memory_allocation(t.p_no, t.r_no);
    t.need = matrix_memory_allocation(t.p_no, t.r_no);

    cout << "Enter the allocated resources of each process(A B C ...)\n";
    for( i=0; i<t.p_no; i++ ) {
        
        cout << "Process P" << i+1 << ": ";
        for( j=0; j < t.r_no; j++ )
            cin >> t.allocated[i][j];
    }

    cout << "Enter the Maximum required resources of each process(A B C ...)\n";
    for( i=0; i < t.p_no; i++ ) {

        cout << "Process P" << i+1 << ": ";
        for( j=0; j < t.r_no; j++ )
            cin >> t.max_need[i][j];
    }

    t.available_resources(); // Calculates the available resources
    t.remaining_required(); // Updates the value of remaining resources required for each process
    t.print_table(); // Prints the table
    bankers_algorithm(t, v, f);

    return 0;
}

void pagingFIFO () {
    int vs; //virtual memory size
    int ps; // physical memory size
    int page; // page size
    int nf; // number of frames
    int np; // number of pages
    int pagetable [100]; //page table
    int frames [2][100]; // frames
    bool fs[100]={false}; // checking if frame is empty or not
    int loop=1; // loop variable
    int pageno;// page number holder
    int offset;// offset holder
    float pagefaults=0;// fault counter
    int flag=0; // flag variable
    int i; //loop variable
    int index=0; // storing index
    float input=0; // input counter;

    cout<<"Enter the Virtual/Logical Memory Size: ";
    cin>>vs;
    cout<<"Enter the Physical Memory Size: "; 
    cin>>ps;
    cout<<"Enter the Size of the page: "; 
    cin>>page;

    np=vs/page;
    nf=ps/page;

    for(i=0;i<np;i++) {
        pagetable[i]=-1;
    }

    for(i=0;i<nf;i++) {
        frames[0][i]=-1;
    }

cout<<"Number of pages in virtual memory:"<<np<<endl;
cout<<"Number of pages in physical memory:"<<nf<<endl;

while(loop==1) {
     cout<<endl;
     cout<<"Press 1 to add a page into a frame"<<endl;
     cout<<"Press 2 to stop"<<endl;
     cin>>loop;
     if (loop!=1)
        break;

    cout<<"Enter the virtual address as told below:"<<endl;;
    cout<<"Enter the Page number: "<<endl;
    cin>>pageno;
    if(pageno>np) {
        cout<<"Page can't exist due to Virtual Memory Constraint"<<endl;
        continue;
    }


    cout<<"Enter the Offset: ";
    cin>>offset;


    input++;
        for (i=0;i<nf;i++) {
            if (frames[0][i]==pageno) {
                flag=1;
                break;
            }
        }
    if(flag==1){
        cout<<endl<<"The Physical Address for the above virtual address is : "<<endl;
        cout<<"Frame: "<<i<<endl;
        cout<<"Offset: "<<offset;
        flag=0;

        }
    else { 
            pagefaults=pagefaults+1;


            if(fs[index]==false) {
                cout<<"Page "<<pageno<<" is not present in the physical memory so page "<< pageno << " is accomodated into frame "<<index;
                frames[0][index]=pageno;
                frames[1][index]=offset;
                fs[index]=true;
                pagetable[pageno]=index;
                
            index++;
            }

            else {   
                cout<<"Page "<<pageno<<" is not present in the physical memory";
                cout<<"Page "<<pageno<<"is accomodated in frame"<<index<<" after removing page "<<frames[0][index];
                pagetable[frames[0][index]]=-1;
                frames[0][index]=pageno;
                frames[1][index]=offset;
                pagetable[pageno]=index;
                index++;
            }

            if(index==nf) {
                    index=0;
                }

        }

 }
        
        cout<<endl<<"Total number of inputs:"<<input;
        cout<<endl<<"Total number of page faults:"<<pagefaults;

        cout<<endl<<"Page Fault Ratio is: "<<pagefaults/input;
        cout<<endl;
        cout<<endl<<"Page Table";
        cout<<endl<<"Page number - Frame number"<<endl;
        for (i=0;i<np;i++)
        {
            cout<<i<<" - "<<pagetable[i]<<endl;
        }

        cout<<endl;
        cout<<endl<<"Memory Table";
        cout<<endl<<"Frame Number - Page Contained"<<endl;
        for (i=0;i<nf;i++)
        {
            cout<<i<<" - "<<frames[0][i]<<endl;
        }
}

void MFTfirstfit()
{
    int tot_size, n;
    int cnt_prt = 0; // variable to hold the number of partitions alloted
    cout << "Enter the total size: \n";
    cin >> tot_size;
    cout << "Enter the total number of partitions: \n";
    cin >> n;

    int space = tot_size; // variable for storing remaining space

    //array for storing the partition sizes
    int part[n + 1];
    for (int i = 1; i <= n; i++)
    {
        cout << "Enter the size of the partition " << i << ": ";
        cin >> part[i];

        //if the partition size is less than remaining space
        //allot the partition with that partition size
        if (part[i] <= space)
        {
            space -= part[i];
            cnt_prt++;
        }

        //otherwise partition cannot be alloted due to less remaining space
        else
        {
            cout << "Partition " << i << " cannot be alloted space because only " << space << "(units) space is remaining \n";
            part[i] = 0;
        }
    }
    int temp[n + 1];
    for (int i = 1; i <= n; i++)
    {
        temp[i] = part[i];
    }
    int ch = 1;
    int cnt_pro = 0;
    int input = 1;
    int allot_pro[100] = {0};
    int tot_frag = 0;
    int store[n + 1];
    int size[100];
    int empty_space = tot_size;
    while (ch != 3)
    {
        cout << "1.Insert \n";
        cout << "2.Delete \n";
        cout << "3.Stop \n";

        cout << "Enter the choice \n";
        cin >> ch;
        if (ch == 3)
            break;

        if (ch == 1)
        {

            cout << "Enter the size of process " << input << "\n";
            cin >> size[input];

            bool flag = false;

            //if the no of alloted processes exceeds the number of partitions
            //then processes cant be allocated
            if (cnt_pro >= cnt_prt)
            {
                cout << "process " << input << " cannot be given partition because only " << cnt_prt << " partitons are available " << endl;
                flag = true;
            }
            for (int j = 1; j <= n; j++)
            {
                //if the partition size is 0
                //process cant be alloted to that partition
                //so continue
                if (temp[j] == 0)
                    continue;

                //otherwise allot the required size for the process to the partition
                //and add remaining space to the internal fragmentation
                //part[j] = 0, indicating that partition is alloted
                if (size[input] <= temp[j])
                {
                    allot_pro[input] = j;
                    cout << "Process " << input << " is allocated to the partition " << j << "\n";
                    store[j] = input;
                    tot_frag += (temp[j] - size[input]);
                    empty_space -= size[input];
                    temp[j] = 0;
                    cnt_pro++;
                    flag = true;
                    break;
                }
            }
            if (!flag)
            {
                if (empty_space >= size[input])

                {
                    int cnt = false;
                    for (int i = 1; i <= n; i++)
                    {
                        if (size[input] <= part[i])
                        {
                            cout << "Process " << input << " cannot be accomodated due to external fragmentation \n";
                            cnt = true;
                            break;
                        }
                    }

                    if(!cnt)
                    {
                         cout << "Process " << input << " can't be given partition because it exceeds the size of all partitions \n";
                    }
                }

                    else 
                    cout << "Process " << input << " can't be given partition because it exceeds the size of all partitions \n";
                }
                input++;
            }

            else if (ch == 2)
            {
                int x;
                cout << "Enter the process id to be deleted  \n";
                cin >> x;
                bool found = false;
                //traversing the store array to find the partition
                // in which process x is stored
                for (int i = 1; i <= n; i++)
                {
                    if (store[i] == x)
                    {
                        temp[i] = part[i];
                        cnt_pro--;
                        allot_pro[x] = 0;
                        tot_frag -= (part[i] - size[x]);
                        empty_space += part[i];
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    cout << "Process " << input << " is not present \n";
                }
            }
        }
        //printing the result
        for (int j = 1; j <= input; j++)
        {
            //if the process is allocated to some partition
            if (allot_pro[j] != 0)
                cout << "Process " << j << " is at partition " << allot_pro[j] << endl;
        }
        //printing the result
        cout << "\n";
        cout << "Space with no partition: " << space << "\n";
        cout << "Total internal fragmentation: " << tot_frag << "\n";
    
}

void MFTbestfit()
{
     int totalsize,n,m,i,j,unusedspace,pid,mint;
    int partitioncnt=0,a,sz,l; 
    cout<<"Enter the total size: ";
    cin>>totalsize;
    unusedspace = totalsize;

    int spaceleft=0,tot_frag=0;

    cout<<"Enter the number of partitions: ";
    cin>>n;
    
    map<int,int> proc;

    int part[n];
    int ak;
    int allotted[n];
    for(i=0;i<n;i++)
    {
        allotted[i]=0;
    }

    for(i=0;i<n;i++)
    {
        cout<<"Enter the size of partition "<< i + 1 <<": ";
        cin>>part[i];

        if(part[i] <= unusedspace)
		{
			unusedspace -= part[i];
			partitioncnt++;
            spaceleft+=part[i];
		}
		else
		{
			cout << "Partition " << i + 1 << " cannot be alloted space because only " << unusedspace << "(units) space is remaining "<<endl;
			part[i] = 0;
		}

    }
    int sc;
    bool flag;
    int dpno;
    while(1)
    {
            cout<<"Enter the operation you want to perform :"<<endl;
            cout<<"1: Insert "<<endl;
            cout<<"2: Delete "<<endl;
            cout<<"3: Stop "<<endl;
            cin>>a;
            switch(a)
            {
                case 1: 
                    cout<<"Enter the process no you want to insert : " ;
                    cin>>pid;
                    cout<<"Enter the size of the process you want to insert :";
                    cin>>sz;
                    proc[pid]=sz;
                    ak=0;
                    for(i=0;i<n;i++)
                    {
                            if(sz<=part[i])
                            {
                                if(allotted[i]==0)
                                {
                                    mint=part[i];
                                    l=i;
                                    ak=4;
                                    break;
                                }
                            }
                    }
                    if(ak==0)
                    {
                            flag=false;
                            for(i=0;i<n;i++)
                            {
                                if(allotted[i]!=0)
                                {
                                    sc=part[i]-proc[allotted[i]];
                                    if(sz<=sc)
                                    {
                                        cout<<"The process cannot be accomodated due to internal fragmentation "<<endl;
                                        flag=true;
                                        break;
                                    }
                                }
                            }
                            if(flag==false)
                            {
                                if(sz<=spaceleft)
                                {
                                    cout<<"The process cannot be accomodated due to external fragmentation"<<endl;
                                }
                                else
                                {
                                    cout<<"The process cannot be accomodated since it exceeds the size of all partitions "<<endl;
                                }
                            }

                    }
                      
                    
                    else
                    {
                            for(i=0;i<n;i++)
                            {
                                if(sz<=part[i] && allotted[i]==0 && part[i]<mint)
                                {
                                    mint=part[i];
                                    l=i;
                                }
                            }
                            allotted[l]=pid;
                            tot_frag+=part[l]-sz;
                            spaceleft-=sz;
                            cout<<"The process is allotted to partition "<<l<<endl;
                    }


                break;


                case 2:

                        cout<<"Enter the processid which you want to delete :"<<endl;
                        cin>>dpno;

                        for(i=0;i<n;i++)
                        {
                            if(allotted[i]==dpno)
                            {
                                allotted[i]=0;
                                spaceleft+=proc[dpno];
                                tot_frag-=part[i]-proc[dpno];
                                break;
                            }
                        }

                break;

                case 3:
                        for(i=0;i<n;i++)
                        {
                            if(allotted[i]==0)
                            {
                                cout<<"Partition "<<i<<" is empty"<<endl;
                            }
                            else
                            {
                                cout<<"Partition "<<i<<" contains process "<<allotted[i]<<endl;
                            }
                        }

                        cout<<endl;
                        cout<<"The unused space is "<<unusedspace<<endl;
                        cout<<"Total internal fragmentation is "<<tot_frag<<endl;
                        return;
                break;

            }
        }   
}

void MFTworstfit()
{
     int totalsize,n,m,i,j,unusedspace,pid,maxt;
    int partitioncnt=0,a,sz,l; 
    cout<<"Enter the total size: ";
    cin>>totalsize;
    unusedspace = totalsize;

    int spaceleft=0,tot_frag=0;

    cout<<"Enter the number of partitions: ";
    cin>>n;
    
    map<int,int> proc;

    int part[n];
    int ak;
    int allotted[n];
    for(i=0;i<n;i++)
    {
        allotted[i]=0;
    }

    for(i=0;i<n;i++)
    {
        cout<<"Enter the size of partition "<< i + 1 <<": ";
        cin>>part[i];

        if(part[i] <= unusedspace)
		{
			unusedspace -= part[i];
			partitioncnt++;
            spaceleft+=part[i];
		}
		else
		{
			cout << "Partition " << i + 1 << " cannot be alloted space because only " << unusedspace << "(units) space is remaining "<<endl;
			part[i] = 0;
		}

    }
    int sc;
    bool flag;
    int dpno;
    while(1)
    {
            cout<<"Enter the operation you want to perform :"<<endl;
            cout<<"1: Insert "<<endl;
            cout<<"2: Delete "<<endl;
            cout<<"3: Stop "<<endl;
            cin>>a;
            switch(a)
            {
                case 1: 
                    cout<<"Enter the process no you want to insert : " ;
                    cin>>pid;
                    cout<<"Enter the size of the process you want to insert :";
                    cin>>sz;
                    proc[pid]=sz;
                    ak=0;
                    for(i=0;i<n;i++)
                    {
                            if(sz<=part[i])
                            {
                                if(allotted[i]==0)
                                {
                                    maxt=part[i];
                                    l=i;
                                    ak=4;
                                    break;
                                }
                            }
                    }
                    if(ak==0)
                    {
                            flag=false;
                            for(i=0;i<n;i++)
                            {
                                if(allotted[i]!=0)
                                {
                                    sc=part[i]-proc[allotted[i]];
                                    if(sz<=sc)
                                    {
                                        cout<<"The process cannot be accomodated due to internal fragmentation "<<endl;
                                        flag=true;
                                        break;
                                    }
                                }
                            }
                            if(flag==false)
                            {
                                if(sz<=spaceleft)
                                {
                                    cout<<"The process cannot be accomodated due to external fragmentation"<<endl;
                                }
                                else
                                {
                                    cout<<"The process cannot be accomodated since it exceeds the size of all partitions "<<endl;
                                }
                            }

                    }
                      
                    
                    else
                    {
                            for(i=0;i<n;i++)
                            {
                                if(sz<=part[i] && allotted[i]==0 && part[i]>maxt)
                                {
                                    maxt=part[i];
                                    l=i;
                                }
                            }
                            allotted[l]=pid;
                            tot_frag+=part[l]-sz;
                            spaceleft-=sz;
                            cout<<"The process is allotted to partition "<<l<<endl;
                    }


                break;


                case 2:

                        cout<<"Enter the processid which you want to delete :"<<endl;
                        cin>>dpno;

                        for(i=0;i<n;i++)
                        {
                            if(allotted[i]==dpno)
                            {
                                allotted[i]=0;
                                spaceleft+=proc[dpno];
                                tot_frag-=part[i]-proc[dpno];
                                break;
                            }
                        }

                break;

                case 3:
                        for(i=0;i<n;i++)
                        {
                            if(allotted[i]==0)
                            {
                                cout<<"Partition "<<i<<" is empty"<<endl;
                            }
                            else
                            {
                                cout<<"Partition "<<i<<" contains process "<<allotted[i]<<endl;
                            }
                        }

                        cout<<endl;
                        cout<<"The unused space is "<<unusedspace<<endl;
                        cout<<"Total internal fragmentation is "<<tot_frag<<endl;
                        return;
                break;

            }
        }   
}

void MVTfirstfit()
{
    
    struct partition
    {
        int process;
        int size;
    };
    int totsize; 
    int i,j;

    cout<<"Enter the total size ";
    cin>>totsize;
    
    int a,spaceleft=totsize; 

    struct partition k; 

    vector <partition> v = {{-1,totsize}};
    while(1)
    {    
        cout<<"Enter the operation you want to perfrom: "<<endl;
        cout<<"1.Insert Process"<<endl;
        cout<<"2.Delete Process"<<endl;
        cout<<"0.Exit"<<endl;
       
        int pid,sz,idx;

        cin>>a;

        switch(a)
        {
            case 1: 
                cout<<"Enter processid : ";
                cin>> pid;
                cout<<"Enter it's size : ";
                cin>> sz; 
                idx=-1;
                for(i=0;i<(int)v.size();i++)
                {
                    if(v.size()==1)
                    {
                        idx=0;
                        break;
                    }
                    else if(v[i].process==-1 && v[i].size>=sz) //if no process is allocated to that partition and size of block > = size of process
                    {
                        idx=i;
                        break;
                    }
                }
                
                if(idx==-1) //if no process is allocated
                {   
                    if(sz<=spaceleft)
                    {
                        cout<<pid<<" can't be accomodated due to external fragmentation"<<endl;
                    }
                    else
                    {
                    cout<<pid<<" can't be accomodated as only "<<spaceleft<<" KB are remaining"<<endl;
                    }
                    break;
                }
                k.process=pid;
                k.size=sz;
                spaceleft-=sz;
                v[idx].size-=sz;
                v.push_back(k);

                for(i=(int)v.size()-1;i>idx;i--)
                {
                    swap(v[i-1],v[i]);
                }

            break;

            case 2:
            cout<<"Enter the processid which you want to delete :";
            cin>>pid;

            for(i=0;i<(int)v.size();i++)
            {
                if(v[i].process==pid)
                {
                   idx=i;
                    break;
                }
            }

                v[idx].process=-1;
				spaceleft+=v[idx].size;

           for(i=0;i<(int)v.size();i++)
				{
					for(j=i+1;j<(int)v.size();j++)
					{
						if(v[i].process==-1&&v[j].process==-1)
						{
							v[i].size+=v[j].size;
							v[j].size=0;
						}
						else
						{
							break;
						}

					}
                }
            
            break;

            case 0: 
            
            for(i=0;i<(int)v.size();i++)
            {
                if(v[i].size>0)
                {
                    if(v[i].process!=-1)
                    {
                        cout<<"Partition "<<i+1<< " has P "<<v[i].process<<" with size "<<v[i].size<<endl;
                    }
                    else
                    {
                        cout<<"Partition "<<i+1<<" is empty with size "<<v[i].size<<endl;
                    }
                }
            }

            return ;
            break;
            

        }   
    
    } 
      
}

void MVTbestfit()
{
    struct partition
    {
        int process;
        int size;
    };
    int totsize; 
    int i,j;

    cout<<"Enter the total size ";
    cin>>totsize;
    
    int a,spaceleft=totsize;

    struct partition k;

    vector <partition> v = {{-1,totsize}};

    while(1)
    {    
        cout<<"Enter the operation you want to perfrom: "<<endl;
        cout<<"1.Insert Process"<<endl;
        cout<<"2.Delete Process"<<endl;
        cout<<"0.Exit"<<endl;
       
        int pid,sz,idx,minsize;

        cin>>a;

        switch(a)
        {
            case 1: 
                cout<<"Enter processid : ";
                cin>> pid;
                cout<<"Enter it's size : ";
                cin>> sz;
                idx=-1;
                minsize=INT_MAX;
            if(spaceleft<sz)
				{
					cout<<pid<<" can't be accomodated as only "<<spaceleft<<"KB are remaining"<<endl;
					break;
				}
				for(int i=0;i<(int)v.size();i++)
				{
					if(v.size()==1)
					{
						idx=0;
						minsize=v[i].size;
					}
					else if(v[i].size>=sz &&v[i].size<minsize&&v[i].process==-1)
					{
						idx=i;
						minsize=v[i].size;
					}

				}
				if(idx==-1)
				{
					cout<<pid<<" can't be accomodated due to external fragmentation"<<endl;
					break;
				}
				k.process=pid;
				k.size=sz;
				spaceleft-=sz;
				v[idx].size-=sz;
				v.push_back(k);
				for(int i=v.size()-1;i>idx;i--)
				{
					swap(v[i-1],v[i]);
				}

            break;

            case 2:
            cout<<"Enter the processid which you want to delete :";
            cin>>pid;

            for(i=0;i<(int)v.size();i++)
            {
                if(v[i].process==pid)
                {
                   idx=i;
                    break;
                }
            }

                v[idx].process=-1;
				spaceleft+=v[idx].size;

           for(i=0;i<(int)v.size();i++)
				{
					for(j=i+1;j<(int)v.size();j++)
					{
						if(v[i].process==-1&&v[j].process==-1)
						{
							v[i].size+=v[j].size;
							v[j].size=0;
						}
						else
						{
							break;
						}

					}
                }
            
            break;

            case 0: 
            
            for(i=0;i<(int)v.size();i++)
            {
                if(v[i].size>0)
                {
                    if(v[i].process!=-1)
                    {
                        cout<<"Partition "<<i+1<< " has P "<<v[i].process<<" with size "<<v[i].size<<endl;
                    }
                    else
                    {
                        cout<<"Partition "<<i+1<<" is empty with size "<<v[i].size<<endl;
                    }
                }
            }

            return ;
            break;
            

        }   
    
    } 
}
void MVTworstfit()
{
       struct partition
    {
        int process;
        int size;
    };
    int totsize; 
    int i,j;

    cout<<"Enter the total size ";
    cin>>totsize;
    
    int a,spaceleft=totsize;

    struct partition k;

    vector <partition> v = {{-1,totsize}};

    while(1)
    {    
        cout<<"Enter the operation you want to perfrom: "<<endl;
        cout<<"1.Insert Process"<<endl;
        cout<<"2.Delete Process"<<endl;
        cout<<"0.Exit"<<endl;
       
        int pid,sz,idx,maxsize;

        cin>>a;

        switch(a)
        {
            case 1: 
                cout<<"Enter processid : ";
                cin>> pid;
                cout<<"Enter it's size : ";
                cin>> sz;
             maxsize=INT_MIN;
             for(i=0;i<(int)v.size();i++)
				{
					if(v.size()==1)
					{
						idx=0;
						maxsize=v[i].size;
					}
					else if(v[i].size>maxsize&&v[i].process==-1)
					{
						idx=i;
						maxsize=v[i].size;
					}

                }
                if(v[idx].size>=sz)
                {
                    
                    k.process=pid;
                    k.size=sz;
                    spaceleft-=sz;
                    v[idx].size-=sz; 
                    v.push_back(k);

                     for(i=(int)v.size()-1;i>idx;i--)
                    {
                    swap(v[i-1],v[i]);
                    }

                }
                else
                {   
                    if(sz<=spaceleft)
                    {
                        cout<<pid<<" can't be accomodated due to external fragmentation"<<endl;
                    }
                    else
                    {
                    cout<<pid<<" can't be accomodated as only "<<spaceleft<<"KB are remaining"<<endl;
                    }
                    break;
                }
            break;

            case 2:
            cout<<"Enter the processid which you want to delete :";
            cin>>pid;

            for(i=0;i<(int)v.size();i++)
            {
                if(v[i].process==pid)
                {
                   idx=i;
                    break;
                }
            }

                v[idx].process=-1;
				spaceleft+=v[idx].size;

           for(i=0;i<(int)v.size();i++)
				{
					for(j=i+1;j<(int)v.size();j++)
					{
						if(v[i].process==-1&&v[j].process==-1)
						{
							v[i].size+=v[j].size;
							v[j].size=0;
						}
						else
						{
							break;
						}

					}
                }
            
            break;

            case 0: 
            
            for(i=0;i<(int)v.size();i++)
            {
                if(v[i].size>0)
                {
                    if(v[i].process!=-1)
                    {
                        cout<<"Partition "<<i+1<< " has P "<<v[i].process<<" with size "<<v[i].size<<endl;
                    }
                    else
                    {
                        cout<<"Partition "<<i+1<<" is empty with size "<<v[i].size<<endl;
                    }
                }
            }

            return ;
            break;
            

        }   
    
    } 
}
void MemoryManagement()
{
        int a,b;
        cout<<"Enter 1 if you want to do fixed partion "<<endl;
        cout<<"Enter 2 if you want to do variable partitiion "<<endl; 
        cin>>a;
        if (a==1)
        {  
            cout<<"Enter the algo you want to perform for fixed partition: "<<endl;
            cout<<"1. First Fit "<<endl;
            cout<<"2. Best Fit "<<endl;
            cout<<"3. Worst Fit "<<endl;
            cin>>b;
            switch(b)
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
                cout<<"Wrong input "<<endl;
                break;
                }
            }

        }
        else
        {
            cout<<"Enter the algo you want to perform for variable partition: "<<endl;
            cout<<"1. First Fit "<<endl;
            cout<<"2. Best Fit "<<endl;
            cout<<"3. Worst Fit "<<endl;
            cin>>b;
            switch(b)
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
                cout<<"Wrong input "<<endl;
                break;
                }
            }

        }
        

}

// Function to display the menu
void menu()
{
    cout << "Press 1 for Scheduling algorithms\n";
    cout << "Press 2 for Synchronization algoritms\n";
    cout << "Press 3 for Bankers algorithm\n";
    cout << "Press 4 for Memory Management\n";
    cout << "Press 5 for Page Replacement algorihm\n";
    cout << "Press 6 for Disc Scheduling Algorithm\n";
    cout << "Press 7 to exit\n";
}
  
// Function to calculate and display the result
void result(int choice, int a, int b)
{
  
    // Display the result
    switch (choice) {
    case 1: {
        // Scheduling();
        break;
    }
    case 2: {
        // Synchronization();
        break;
    }
    case 3: {
        BankersAlgo();
        break;
    }
    case 4: {
        MemoryManagement();
        break;
    }
    case 5: {
        // PageReplacement();
        break;
    }
    case 6: {
    //    DiskScheduling();
        break;
    }
    case 7: {
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
    choice = 3;
    cout << "Choice is " << choice << endl;
  
    // Display the result
    // according to the choice
    // result(choice, a, b);

    //these are the new codes I have added
    // fcfs();
    // sjf();
    // roundRobin();
    // pagingFIFO();
  
    return 0;
}
