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
	int n, h;
	vector<int> track(n);
	cout << "Enter total tracks:";
	cin >> n;
	cout << "Enter requested track position:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "\t" << i + 1 << ":";
		cin >> track[i];
	}
	cout << "Enter initial head position:";
	cin >> h;
	int seek_time = 0;
	vector<int> seek_sequence;
	for (int i = 0; i < n; i++)
	{
		seek_time += abs(track[i] - h);
		h = track[i];
		seek_sequence.push_back(track[i]);
	}
	cout << "Final output:" << endl;
	cout << "Total seek time = " << seek_time << endl;
	cout << "Seek sequence is: ";
	for (int i = 0; i < n; i++)
	{
		cout << seek_sequence[i] << " ";
	}
}