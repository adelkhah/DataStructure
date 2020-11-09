#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 10000;

class RecentRequestCounter
{
	int front = 0;
	int last = 0;
	int a[MAX_N];
private:
	int getSize(){
		return last - front;
	}
	void popFront(){
		front++;
	}
	void insertLast(int t){
		a[last] = t;
		last++;
	}
public:
	void ResetCounter(){
		front = 0;
		last = 0;
	}
	int ping(int t) { 
		insertLast(t);
		while(a[front] < t - 3000){
			popFront();
		}
		return getSize();
	}
	
};

int main()
{
	RecentRequestCounter a;
	a.ResetCounter();
	cout << a.ping(1) << endl;
	cout << a.ping(100) << endl;
	cout << a.ping(3001) << endl;
	cout << a.ping(3002) << endl;

	return 0;
}