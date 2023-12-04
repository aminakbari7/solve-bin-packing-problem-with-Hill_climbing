#include<iostream>
#include <windows.h>
#include<time.h>
#include<fstream>
using namespace std;
class Bin_packing
{

public:
    int a[200];
    int bestsize = 0;
    int size = 0;
    Bin_packing()
    {
        setarray();
		buildrandomarray();
		bestsize = countbin();
    }
    void setarray()
    {
		fstream f("BinTest.txt");
		if (!f) {
			cout << "Error opening file" << endl;
			return;
		}
		int x = 0;
		while (f >> x)
		{
			a[size]=x;
			size++;
		}
		f.close();
    }
	int countbin()
	{
		int sum = 0;
		int countbox = 0;
		for (int i = 0; i < 200; i++)
		{
			sum += a[i];
			if (sum <= 100000)
			{
				continue;
			}
			else
			{
				sum = a[i];
				countbox++;
			}
		}
		return countbox;
	}
	int randynum()
	{
		return rand() % (200);
	}
	void print()
	{
		int sum = 0;
		int box = 1;
		cout << "---------------------------" << box << endl;
		box++;
		for (int i = 0; i < 200; i++)
		{
			sum += a[i];
			if (sum <= 100000)
			{
				cout << a[i] << endl;
			}
			else
			{
				cout << "---------------------------" <<box<< endl;
				cout << a[i] << endl;
				sum = a[i];
				box++;
			}
		}
	}
	void buildrandomarray()
	{
		int b[200];
		for (int i = 0; i < 200; i++)
		{
			b[i] = a[i];
			a[i] = 0;
		}
		for (int q = 0; q < 200;)
		{
			int p = randynum();
			if (b[p] != 0)
			{
				a[q] = b[p];
				b[p] = 0;
				q++;
			}

		}
	}
	
};
int main()
{
	srand(time(0));
	int start_time = time(0);
	Bin_packing bin;
	int neighbor = 0;
	int flat = 0;
	while (true)
	{
		if (flat == 100000000)break;
		int p = bin.randynum();
		int q = bin.randynum();
		if (p == q)continue;
		int t1 = bin.a[p];
		int t2 = bin.a[q];
		bin.a[p] = t2;
		bin.a[q] = t1;
		neighbor = bin.countbin();
		if (neighbor >bin.bestsize)
		{
			bin.a[p] = t1;
			bin.a[q] = t2;
			flat++;
			continue;
		}
		else
		{
			if (neighbor != bin.bestsize)
			{
				cout <<"count box :" << bin.bestsize << "        time :" << time(0) - start_time << endl;
				flat = 0;
			}
			bin.bestsize = neighbor;	
		}
	}
	bin.print();
    system("pause");
    return 0;
}
