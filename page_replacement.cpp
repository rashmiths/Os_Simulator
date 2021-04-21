#include <bits/stdc++.h>

using namespace std;

int fifo_pra()
{
    vector<int> frame;

    int num_frm = 0, pg;
    int page_faults = 0;
    int flag = 0, x, i, j, choice;
    int update_index;

    cout << "Page Replacement - FIFO\n\nEnter the number of frames: ";
    cin >> num_frm;

    update_index = 0;
    choice = 1;
    i = 0;

    while (1)
    {

        cout << "1. Add Page\t2. Exit\nEnter Choice: ";
        cin >> choice;

        if (choice == 2)
            break;
        else if (choice != 1)
        {
            cout << "Invalid Choice\n";
            continue;
        }

        i++;
        printf("Enter the Page Number (%d): ", i);
        cin >> pg;
        flag = 0;
        if (frame.size() < num_frm)
        {
            for (int j = 0; j < frame.size(); j++)
            {
                if (pg == frame[j])
                {
                    cout << "Page " << pg << " is already present in F" << j << "\n\n";
                    flag = 1;
                    break;
                }
            }
            if (flag)
                continue;
            cout << "Page " << pg << " has been accomodated in F" << i - 1 << "\n\n";
            page_faults++;
            frame.push_back(pg);
            continue;
        }

        flag = 0;
        for (int k = 0; k < num_frm; k++)
        {
            if (pg == frame[k])
            {
                cout << "Page " << pg << " is already present in F" << k << "\n\n";
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            x = frame[update_index];
            cout << "Page " << pg << " has been accomodated into F" << update_index << " replacing Page " << x << "\n\n";
            frame[update_index] = pg;
            page_faults++;

            if (update_index == (num_frm - 1))
                update_index = 0;
            else
                update_index++;
        }
    }

    cout << "\nTotal Number of Page Faults: " << page_faults << "\nPage Faults Ratio = " << (float(page_faults) / float(i)) << "\n\n";
    return 0;
}

int lru_pra()
{
    vector<int> input;
    vector<int> frame;

    int num_frm = 0, pg;
    int page_faults = 0;
    int flag = 0, i, k, choice;
    int lru;

    cout << "Page Replacement - LRU\n\nEnter the number of frames: ";
    cin >> num_frm;

    choice = 1;
    i = 0;
    while (1)
    {

        cout << "1. Add Page\t2. Exit\nEnter Choice: ";
        cin >> choice;

        if (choice == 2)
            break;
        else if (choice != 1)
        {
            cout << "Invalid Choice\n";
            continue;
        }

        i++;
        printf("Enter the Page Number (%d): ", i);
        cin >> pg;
        flag = 0;
        if (frame.size() < num_frm)
        {
            for (int j = 0; j < frame.size(); j++)
            {
                if (pg == frame[j])
                {
                    cout << "Page " << pg << " is already present in F" << j << "\n\n";
                    flag = 1;
                    break;
                }
            }
            if (flag)
                continue;
            cout << "Page " << pg << " has been accomodated in F" << i - 1 << "\n\n";
            page_faults++;
            input.push_back(pg);
            frame.push_back(pg);
            continue;
        }

        flag = 0;
        for (k = 0; k < num_frm; k++)
        {
            if (pg == frame[k])
            {

                cout << "Page " << pg << " is already present in F" << k << "\n\n";
                for (auto j = input.begin(); j != input.end(); j++)
                {
                    if (pg == *j)
                    {
                        input.erase(j);
                        input.push_back(pg);
                        break;
                    }
                }

                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            lru = input[0];

            for (k = 0; k < num_frm; k++)
            {
                if (lru == frame[k])
                {
                    break;
                }
            }
            frame[k] = pg;
            cout << "Page " << pg << " has been accomodated in F" << k << " replacing Page " << lru << "\n\n";

            input.erase(input.begin());
            input.push_back(pg);
            page_faults++;
        }
    }

    cout << "\nTotal Number of Page Faults: " << page_faults << "\nPage Faults Ratio = " << (float(page_faults) / float(i)) << "\n\n";
    return 0;
}

bool search(int key, vector<int> &fr)
{
    for (int i = 0; i < fr.size(); i++)
        if (fr[i] == key)
            return true;
    return false;
}

// Function to find the frame that will not be used
// recently in future after given index in pg[0..pn-1]
int predict(int pg[], vector<int> &fr, int pn, int index)
{
    // Store the index of pages which are going
    // to be used recently in future
    int res = -1, farthest = index;
    for (int i = 0; i < fr.size(); i++)
    {
        int j;
        for (j = index; j < pn; j++)
        {
            if (fr[i] == pg[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    res = i;
                }
                break;
            }
        }

        // If a page is never referenced in future,
        // return it.
        if (j == pn)
            return i;
    }

    // If all of the frames were not in future,
    // return any of them, we return 0. Otherwise
    // we return res.
    return (res == -1) ? 0 : res;
}

void optimalPage(int pg[], int pn, int fn)
{
    // Create an array for given number of
    // frames and initialize it as empty.
    vector<int> fr;

    // Traverse through page reference array
    // and check for miss and hit.
    int hit = 0;
    for (int i = 0; i < pn; i++)
    {

        // Page found in a frame : HIT
        if (search(pg[i], fr))
        {
            hit++;
            continue;
        }

        // Page not found in a frame : MISS

        // If there is space available in frames.
        if (fr.size() < fn)
            fr.push_back(pg[i]);

        // Find the page to be replaced.
        else
        {
            int j = predict(pg, fr, pn, i + 1);
            fr[j] = pg[i];
        }
    }
    cout << "No. of hits = " << hit << endl;
    cout << "No. of misses = " << pn - hit << endl;
}

int optimal_pra()
{
    int pg[100];
    int i, n;
    int fn;
     cout << "Page Replacement - Optimal\n\nEnter the number of frames: ";
    cin >> fn;
    cout << "Enter the number of pages to get";
    cin >> n;
    cout << "Enter the list of pages to get";
    for (i = 0; i < n; i++)
    {
        scanf("%d", &pg[i]);
    }

    int pn = sizeof(pg) / sizeof(pg[0]);

    optimalPage(pg, pn, fn);
    return 0;
}