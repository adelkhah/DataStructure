#include <bits/stdc++.h>
using namespace std;


// problem 1
class DoubleEndedCircular
{
	int front = 0;
	int last = 1;
	int size; // size of the queue 
	int cnt; // the number of elements in the queue
	int *a; // array

public:

	/// not a main function
	void show(){ // just to have a quick look at the queue   not a main fucktion
		for(int i = (front+1)%size; i != last; i++,i %= size){
			cout << i << "  " << a[i] << endl;
		}
		return;
	}
	/// not a main function


	DoubleEndedCircular(int k){
		a = new int[k]; // creat array of size k
		size = k;
	}

	bool insertFront(int x){
		if(isFull()){
			return false;
		}
		a[front] = x;
		front--;
		// just in case that front gets equel to -1
		front += size; // you can also check it by if(front==-1)
		front %= size;
		cnt++;
		return true;
	}

	bool insertLast(int x){
		if(isFull()){
			return false;
		}
		a[last] = x;
		last++;
		last %= size;
		cnt++;
		return true;
	}

	bool deleteFront(){
		if(isEmpty()){
			return false;
		}
		front++;
		front %= size;
		cnt--;
		return true;
	}

	bool deleteLast(){
		if(isEmpty()){
			return false;
		}
		last--;
		// just in case that last gets equel to -1
		last += size; // you can also check it by if(front==-1)
		last %= size;
		cnt--;
		return true;
	}

	int getFront(){
		if(isEmpty()){
			return -1;
		}
		int f = front;
		f++;
		f %= size;
		return a[f];
	}

	int getLast(){
		if(isEmpty()){
			return -1;
		}
		int l = last;
		l--;
		l += size;
		l %= size;
		return a[l];
	}

	bool isEmpty(){
		if(cnt == 0){
			return true;
		}
		return false;
	}

	bool isFull(){
		if(cnt == size){
			return true;
		}
		return false;
	}

	~DoubleEndedCircular(){
		delete[] a; // delete the array otherwise leak memory happens
	}
	
};



int main()
{
	
	DoubleEndedCircular q(10);
	q.insertLast(10);
	q.insertLast(3);
	q.insertLast(123);
	q.insertFront(4);
	q.insertFront(6);
	q.insertFront(444);
	q.show();
	cout << q.getFront() << endl;
	cout << q.getLast() << endl;
	q.deleteLast();
	q.deleteLast();
	q.deleteLast();
	q.deleteLast();
	cout << q.getLast() << endl;
	q.show();
	// we can see that every thing is fine :)
	return 0;
}