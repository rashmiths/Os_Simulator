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

                    if (!cnt)
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
    int totalsize, n, m, i, j, unusedspace, pid, mint;
    int partitioncnt = 0, a, sz, l;
    cout << "Enter the total size: ";
    cin >> totalsize;
    unusedspace = totalsize;

    int spaceleft = 0, tot_frag = 0;

    cout << "Enter the number of partitions: ";
    cin >> n;

    map<int, int> proc;

    int part[n];
    int ak;
    int allotted[n];
    for (i = 0; i < n; i++)
    {
        allotted[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        cout << "Enter the size of partition " << i + 1 << ": ";
        cin >> part[i];

        if (part[i] <= unusedspace)
        {
            unusedspace -= part[i];
            partitioncnt++;
            spaceleft += part[i];
        }
        else
        {
            cout << "Partition " << i + 1 << " cannot be alloted space because only " << unusedspace << "(units) space is remaining " << endl;
            part[i] = 0;
        }
    }
    int sc;
    bool flag;
    int dpno;
    while (1)
    {
        cout << "Enter the operation you want to perform :" << endl;
        cout << "1: Insert " << endl;
        cout << "2: Delete " << endl;
        cout << "3: Stop " << endl;
        cin >> a;
        switch (a)
        {
        case 1:
            cout << "Enter the process no you want to insert : ";
            cin >> pid;
            cout << "Enter the size of the process you want to insert :";
            cin >> sz;
            proc[pid] = sz;
            ak = 0;
            for (i = 0; i < n; i++)
            {
                if (sz <= part[i])
                {
                    if (allotted[i] == 0)
                    {
                        mint = part[i];
                        l = i;
                        ak = 4;
                        break;
                    }
                }
            }
            if (ak == 0)
            {
                flag = false;
                for (i = 0; i < n; i++)
                {
                    if (allotted[i] != 0)
                    {
                        sc = part[i] - proc[allotted[i]];
                        if (sz <= sc)
                        {
                            cout << "The process cannot be accomodated due to internal fragmentation " << endl;
                            flag = true;
                            break;
                        }
                    }
                }
                if (flag == false)
                {
                    if (sz <= spaceleft)
                    {
                        cout << "The process cannot be accomodated due to external fragmentation" << endl;
                    }
                    else
                    {
                        cout << "The process cannot be accomodated since it exceeds the size of all partitions " << endl;
                    }
                }
            }

            else
            {
                for (i = 0; i < n; i++)
                {
                    if (sz <= part[i] && allotted[i] == 0 && part[i] < mint)
                    {
                        mint = part[i];
                        l = i;
                    }
                }
                allotted[l] = pid;
                tot_frag += part[l] - sz;
                spaceleft -= sz;
                cout << "The process is allotted to partition " << l << endl;
            }

            break;

        case 2:

            cout << "Enter the processid which you want to delete :" << endl;
            cin >> dpno;

            for (i = 0; i < n; i++)
            {
                if (allotted[i] == dpno)
                {
                    allotted[i] = 0;
                    spaceleft += proc[dpno];
                    tot_frag -= part[i] - proc[dpno];
                    break;
                }
            }

            break;

        case 3:
            for (i = 0; i < n; i++)
            {
                if (allotted[i] == 0)
                {
                    cout << "Partition " << i << " is empty" << endl;
                }
                else
                {
                    cout << "Partition " << i << " contains process " << allotted[i] << endl;
                }
            }

            cout << endl;
            cout << "The unused space is " << unusedspace << endl;
            cout << "Total internal fragmentation is " << tot_frag << endl;
            return;
            break;
        }
    }
}

void MFTworstfit()
{
    int totalsize, n, m, i, j, unusedspace, pid, maxt;
    int partitioncnt = 0, a, sz, l;
    cout << "Enter the total size: ";
    cin >> totalsize;
    unusedspace = totalsize;

    int spaceleft = 0, tot_frag = 0;

    cout << "Enter the number of partitions: ";
    cin >> n;

    map<int, int> proc;

    int part[n];
    int ak;
    int allotted[n];
    for (i = 0; i < n; i++)
    {
        allotted[i] = 0;
    }

    for (i = 0; i < n; i++)
    {
        cout << "Enter the size of partition " << i + 1 << ": ";
        cin >> part[i];

        if (part[i] <= unusedspace)
        {
            unusedspace -= part[i];
            partitioncnt++;
            spaceleft += part[i];
        }
        else
        {
            cout << "Partition " << i + 1 << " cannot be alloted space because only " << unusedspace << "(units) space is remaining " << endl;
            part[i] = 0;
        }
    }
    int sc;
    bool flag;
    int dpno;
    while (1)
    {
        cout << "Enter the operation you want to perform :" << endl;
        cout << "1: Insert " << endl;
        cout << "2: Delete " << endl;
        cout << "3: Stop " << endl;
        cin >> a;
        switch (a)
        {
        case 1:
            cout << "Enter the process no you want to insert : ";
            cin >> pid;
            cout << "Enter the size of the process you want to insert :";
            cin >> sz;
            proc[pid] = sz;
            ak = 0;
            for (i = 0; i < n; i++)
            {
                if (sz <= part[i])
                {
                    if (allotted[i] == 0)
                    {
                        maxt = part[i];
                        l = i;
                        ak = 4;
                        break;
                    }
                }
            }
            if (ak == 0)
            {
                flag = false;
                for (i = 0; i < n; i++)
                {
                    if (allotted[i] != 0)
                    {
                        sc = part[i] - proc[allotted[i]];
                        if (sz <= sc)
                        {
                            cout << "The process cannot be accomodated due to internal fragmentation " << endl;
                            flag = true;
                            break;
                        }
                    }
                }
                if (flag == false)
                {
                    if (sz <= spaceleft)
                    {
                        cout << "The process cannot be accomodated due to external fragmentation" << endl;
                    }
                    else
                    {
                        cout << "The process cannot be accomodated since it exceeds the size of all partitions " << endl;
                    }
                }
            }

            else
            {
                for (i = 0; i < n; i++)
                {
                    if (sz <= part[i] && allotted[i] == 0 && part[i] > maxt)
                    {
                        maxt = part[i];
                        l = i;
                    }
                }
                allotted[l] = pid;
                tot_frag += part[l] - sz;
                spaceleft -= sz;
                cout << "The process is allotted to partition " << l << endl;
            }

            break;

        case 2:

            cout << "Enter the processid which you want to delete :" << endl;
            cin >> dpno;

            for (i = 0; i < n; i++)
            {
                if (allotted[i] == dpno)
                {
                    allotted[i] = 0;
                    spaceleft += proc[dpno];
                    tot_frag -= part[i] - proc[dpno];
                    break;
                }
            }

            break;

        case 3:
            for (i = 0; i < n; i++)
            {
                if (allotted[i] == 0)
                {
                    cout << "Partition " << i << " is empty" << endl;
                }
                else
                {
                    cout << "Partition " << i << " contains process " << allotted[i] << endl;
                }
            }

            cout << endl;
            cout << "The unused space is " << unusedspace << endl;
            cout << "Total internal fragmentation is " << tot_frag << endl;
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
    int i, j;

    cout << "Enter the total size ";
    cin >> totsize;

    int a, spaceleft = totsize;

    struct partition k;

    vector<partition> v = {{-1, totsize}};
    while (1)
    {
        cout << "Enter the operation you want to perfrom: " << endl;
        cout << "1.Insert Process" << endl;
        cout << "2.Delete Process" << endl;
        cout << "0.Exit" << endl;

        int pid, sz, idx;

        cin >> a;

        switch (a)
        {
        case 1:
            cout << "Enter processid : ";
            cin >> pid;
            cout << "Enter it's size : ";
            cin >> sz;
            idx = -1;
            for (i = 0; i < (int)v.size(); i++)
            {
                if (v.size() == 1)
                {
                    idx = 0;
                    break;
                }
                else if (v[i].process == -1 && v[i].size >= sz) //if no process is allocated to that partition and size of block > = size of process
                {
                    idx = i;
                    break;
                }
            }

            if (idx == -1) //if no process is allocated
            {
                if (sz <= spaceleft)
                {
                    cout << pid << " can't be accomodated due to external fragmentation" << endl;
                }
                else
                {
                    cout << pid << " can't be accomodated as only " << spaceleft << " KB are remaining" << endl;
                }
                break;
            }
            k.process = pid;
            k.size = sz;
            spaceleft -= sz;
            v[idx].size -= sz;
            v.push_back(k);

            for (i = (int)v.size() - 1; i > idx; i--)
            {
                swap(v[i - 1], v[i]);
            }

            break;

        case 2:
            cout << "Enter the processid which you want to delete :";
            cin >> pid;

            for (i = 0; i < (int)v.size(); i++)
            {
                if (v[i].process == pid)
                {
                    idx = i;
                    break;
                }
            }

            v[idx].process = -1;
            spaceleft += v[idx].size;

            for (i = 0; i < (int)v.size(); i++)
            {
                for (j = i + 1; j < (int)v.size(); j++)
                {
                    if (v[i].process == -1 && v[j].process == -1)
                    {
                        v[i].size += v[j].size;
                        v[j].size = 0;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            break;

        case 0:

            for (i = 0; i < (int)v.size(); i++)
            {
                if (v[i].size > 0)
                {
                    if (v[i].process != -1)
                    {
                        cout << "Partition " << i + 1 << " has P " << v[i].process << " with size " << v[i].size << endl;
                    }
                    else
                    {
                        cout << "Partition " << i + 1 << " is empty with size " << v[i].size << endl;
                    }
                }
            }

            return;
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
    int i, j;

    cout << "Enter the total size ";
    cin >> totsize;

    int a, spaceleft = totsize;

    struct partition k;

    vector<partition> v = {{-1, totsize}};

    while (1)
    {
        cout << "Enter the operation you want to perfrom: " << endl;
        cout << "1.Insert Process" << endl;
        cout << "2.Delete Process" << endl;
        cout << "0.Exit" << endl;

        int pid, sz, idx, minsize;

        cin >> a;

        switch (a)
        {
        case 1:
            cout << "Enter processid : ";
            cin >> pid;
            cout << "Enter it's size : ";
            cin >> sz;
            idx = -1;
            minsize = INT_MAX;
            if (spaceleft < sz)
            {
                cout << pid << " can't be accomodated as only " << spaceleft << "KB are remaining" << endl;
                break;
            }
            for (int i = 0; i < (int)v.size(); i++)
            {
                if (v.size() == 1)
                {
                    idx = 0;
                    minsize = v[i].size;
                }
                else if (v[i].size >= sz && v[i].size < minsize && v[i].process == -1)
                {
                    idx = i;
                    minsize = v[i].size;
                }
            }
            if (idx == -1)
            {
                cout << pid << " can't be accomodated due to external fragmentation" << endl;
                break;
            }
            k.process = pid;
            k.size = sz;
            spaceleft -= sz;
            v[idx].size -= sz;
            v.push_back(k);
            for (int i = v.size() - 1; i > idx; i--)
            {
                swap(v[i - 1], v[i]);
            }

            break;

        case 2:
            cout << "Enter the processid which you want to delete :";
            cin >> pid;

            for (i = 0; i < (int)v.size(); i++)
            {
                if (v[i].process == pid)
                {
                    idx = i;
                    break;
                }
            }

            v[idx].process = -1;
            spaceleft += v[idx].size;

            for (i = 0; i < (int)v.size(); i++)
            {
                for (j = i + 1; j < (int)v.size(); j++)
                {
                    if (v[i].process == -1 && v[j].process == -1)
                    {
                        v[i].size += v[j].size;
                        v[j].size = 0;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            break;

        case 0:

            for (i = 0; i < (int)v.size(); i++)
            {
                if (v[i].size > 0)
                {
                    if (v[i].process != -1)
                    {
                        cout << "Partition " << i + 1 << " has P " << v[i].process << " with size " << v[i].size << endl;
                    }
                    else
                    {
                        cout << "Partition " << i + 1 << " is empty with size " << v[i].size << endl;
                    }
                }
            }

            return;
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
    int i, j;

    cout << "Enter the total size ";
    cin >> totsize;

    int a, spaceleft = totsize;

    struct partition k;

    vector<partition> v = {{-1, totsize}};

    while (1)
    {
        cout << "Enter the operation you want to perfrom: " << endl;
        cout << "1.Insert Process" << endl;
        cout << "2.Delete Process" << endl;
        cout << "0.Exit" << endl;

        int pid, sz, idx, maxsize;

        cin >> a;

        switch (a)
        {
        case 1:
            cout << "Enter processid : ";
            cin >> pid;
            cout << "Enter it's size : ";
            cin >> sz;
            maxsize = INT_MIN;
            for (i = 0; i < (int)v.size(); i++)
            {
                if (v.size() == 1)
                {
                    idx = 0;
                    maxsize = v[i].size;
                }
                else if (v[i].size > maxsize && v[i].process == -1)
                {
                    idx = i;
                    maxsize = v[i].size;
                }
            }
            if (v[idx].size >= sz)
            {

                k.process = pid;
                k.size = sz;
                spaceleft -= sz;
                v[idx].size -= sz;
                v.push_back(k);

                for (i = (int)v.size() - 1; i > idx; i--)
                {
                    swap(v[i - 1], v[i]);
                }
            }
            else
            {
                if (sz <= spaceleft)
                {
                    cout << pid << " can't be accomodated due to external fragmentation" << endl;
                }
                else
                {
                    cout << pid << " can't be accomodated as only " << spaceleft << "KB are remaining" << endl;
                }
                break;
            }
            break;

        case 2:
            cout << "Enter the processid which you want to delete :";
            cin >> pid;

            for (i = 0; i < (int)v.size(); i++)
            {
                if (v[i].process == pid)
                {
                    idx = i;
                    break;
                }
            }

            v[idx].process = -1;
            spaceleft += v[idx].size;

            for (i = 0; i < (int)v.size(); i++)
            {
                for (j = i + 1; j < (int)v.size(); j++)
                {
                    if (v[i].process == -1 && v[j].process == -1)
                    {
                        v[i].size += v[j].size;
                        v[j].size = 0;
                    }
                    else
                    {
                        break;
                    }
                }
            }

            break;

        case 0:

            for (i = 0; i < (int)v.size(); i++)
            {
                if (v[i].size > 0)
                {
                    if (v[i].process != -1)
                    {
                        cout << "Partition " << i + 1 << " has P " << v[i].process << " with size " << v[i].size << endl;
                    }
                    else
                    {
                        cout << "Partition " << i + 1 << " is empty with size " << v[i].size << endl;
                    }
                }
            }

            return;
            break;
        }
    }
}