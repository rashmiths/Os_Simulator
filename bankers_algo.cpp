#include <bits/stdc++.h>
using namespace std;

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