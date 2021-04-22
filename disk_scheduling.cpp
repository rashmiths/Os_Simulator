#include <bits/stdc++.h>

using namespace std;

void disk_clook()
{
	int n, track;
	cout << "\nEnter Number Of Requests : ";
	cin >> n;
	cout << "\nEnter Number Of Tracks : ";
	cin >> track;
	int req[n + 1];
	cout << "\nEnter Current Postions of R/W Head : ";
	cin >> req[0];
	cout << "\nEnter the Requests\n";
	for (int i = 1; i <= n; i++)
		cin >> req[i];

	int first = req[0];
	sort(req, req + n + 1);
	int seek = 0, pos;
	for (int i = 0; i <= n; i++)
	{
		if (req[i] == first)
			pos = i;
	}

	cout << "\nHead Movement\n";
	for (int i = pos - 1; i >= 0; i--) // left
	{
		cout << req[i + 1] << "->" << req[i] << " : " << abs(req[i + 1] - req[i]) << "\n";
		seek += abs(req[i + 1] - req[i]);
	}

	if (pos != n) // go to right end
	{
		cout << req[0] << "--->" << req[n] << " : " << abs(req[n] - req[0]) << "\n";
		seek += abs(req[n] - req[0]);
	}

	for (int i = n; i > pos + 1; i--) // right to left
	{
		cout << req[i] << "->" << req[i - 1] << " : " << abs(req[i] - req[i - 1]) << "\n";
		seek += abs(req[i] - req[i - 1]);
	}

	cout << "\nTotal Head Movement : " << seek;
}

void disk_look()
{
	int n, track;
	cout << "\nEnter Number Of Requests : ";
	cin >> n;
	cout << "\nEnter Number Of Tracks : ";
	cin >> track;
	int req[n + 1];
	cout << "\nEnter Current Postions of R/W Head : ";
	cin >> req[0];
	cout << "\nEnter the Requests\n";
	for (int i = 1; i <= n; i++)
		cin >> req[i];

	int first = req[0];
	sort(req, req + n + 1);
	int seek = 0, pos;
	for (int i = 0; i <= n; i++)
	{
		if (req[i] == first)
			pos = i;
	}

	cout << "\nHead Movement\n";
	for (int i = pos - 1; i >= 0; i--) // head to left
	{
		cout << req[i + 1] << "->" << req[i] << " : " << abs(req[i + 1] - req[i]) << "\n";
		seek += abs(req[i + 1] - req[i]);
	}

	if (pos != n) // go to right
	{
		cout << req[0] << "->" << req[pos + 1] << " : " << abs(req[pos + 1] - req[0]) << "\n";
		seek += abs(req[pos + 1] - req[0]);
	}

	for (int i = pos + 2; i <= n; i++) // right to left
	{
		cout << req[i - 1] << "->" << req[i] << " : " << abs(req[i - 1] - req[i]) << "\n";
		seek += abs(req[i - 1] - req[i]);
	}

	cout << "\nTotal Head Movement : " << seek;
}
void disk_sstf()
{
	int n;
	cout << "\nEnter Number Of Requests : ";
	cin >> n;
	int req[n + 1];
	cout << "\nEnter Current Postions of R/W Head : ";
	cin >> req[0];
	cout << "\nEnter the Requests\n";
	for (int i = 1; i <= n; i++)
		cin >> req[i];

	int seek = 0, prev = req[0];
	int done[n + 1];
	memset(done, 0, sizeof(done));
	done[0] = 1;

	cout << "\nHead Movement\n";
	for (int i = 1; i <= n; i++)
	{
		int idx, small = 1e5;
		for (int j = 1; j <= n; j++)
		{
			if (done[j] != 1 && abs(req[j] - prev) < small)
			{
				idx = j;
				small = abs(req[j] - prev);
			}
		}
		done[idx] = 1;
		cout << prev << "->" << req[idx] << " : " << small << "\n";
		seek += small;
		prev = req[idx];
	}

	cout << "\nTotal Head Movement : " << seek;
}
void disk_fcfs()
{
	int queue[20], n, head, i, j, k, seek = 0, max, diff;
	float avg;
	printf("Enter the max range of disk\n");
	scanf("%d", &max);
	printf("Enter the size of queue request\n");
	scanf("%d", &n);
	printf("Enter the queue of disk positions to be read\n");
	for (i = 1; i <= n; i++)
		scanf("%d", &queue[i]);
	printf("Enter the initial head position\n");
	scanf("%d", &head);
	queue[0] = head;
	for (j = 0; j <= n - 1; j++)
	{
		diff = abs(queue[j + 1] - queue[j]);
		seek += diff;
		printf("Disk head moves from %d to %d with seek                                                                                       %d\n", queue[j], queue[j + 1], diff);
	}
	printf("Total seek time is %d\n", seek);
	avg = seek / (float)n;
	printf("Average seek time is %f\n", avg);
	return;
}