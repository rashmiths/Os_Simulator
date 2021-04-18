#include <bits/stdc++.h>
using namespace std;
  
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
    switch (choice) {
    case 1: {
        Scheduling();
        break;
    }
    case 2: {
        Synchronization();
        break;
    }
    case 3: {
        BankersAlgo();
        break;
    }
    case 4: {
        Paging();
        break;
    }
    case 5: {
        PageReplacement();
        break;
    }
    case 6: {
       DiskScheduling();
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
    choice = 1;
    cout << "Choice is " << choice << endl;
  
    // Display the result
    // according to the choice
    result(choice, a, b);
  
    return 0;
}