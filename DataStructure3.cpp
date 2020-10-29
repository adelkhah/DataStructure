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

class normal_queue
{
	int front = 0;
	int last = 0;
	char *a; // array
public:
	normal_queue(int k){
		a = new char[k]; // creat array of size k
	}
	void insert(char x){
		a[last] = x;
		last++;
	}
	void popFront(){
		front++;
	}
	char getFront(){
		return a[front];
	}
	~normal_queue(){
		delete[] a;
	}
	
};

struct pairing
{
	int cnt = 0; // or some negative number 
	char c = '0'; // something except letter
};

// problem 2
int solve_problem_2(string tasks, int t) // like tasks = "AAABBCD" , t = 3
{
	/*
you can think about the proof for this algorithm and share it with me see if you guessed right or not :)
	let's say the tasks is like : "AAAAAAA BBBBBB CCCC DDD EE F"
	we put the task in a queue as follow
	A B C D E F ... A B C D E ... A B C D ... A B C ... A B ... A B ... A
	the (...) is the waiting time for CPU depending on value of t 
	and we only need to check the time between 2 A (most apearing task)
	*/
	int n = tasks.size();
	pairing a[n]; // see how many times each task appears 
	for(int i = 0; i < n; i++){
		bool found = false;
		for(int j = 0; j < n; j++){
			if(a[j].c == tasks[i]){ // we found a similar task
				a[j].cnt++;
				found = true;
				break;
			}
		}
		if(found == false){ // it is a new task
			for(int j = 0; j < n; j++){
				if(a[j].c == '0'){
					a[j].c = tasks[i];
					a[j].cnt = 1;
					break;
				}
			}
		}
	}
	
	// sort the "array a" in decreasing order like (5 4 3 2 1 0 0 0 0 0)
	for(int i = 0; i < n; i++){
		for(int j = i+1; j < n; j++){ 
			if(a[i].cnt < a[j].cnt){ // swap a[i], a[j]
				pairing tmp;
				tmp.c = a[i].c;
				tmp.cnt = a[i].cnt;
				a[i].c = a[j].c;
				a[i].cnt = a[j].cnt;
				a[j].c = tmp.c;
				a[j].cnt = tmp.cnt;
			}
		}
	}
	
	// lets put the task in the queue
	normal_queue q(n);
	int remaining_task = n;
	while(remaining_task > 0){ 
		for(int i = 0; i < n; i++){
			if(a[i].cnt > 0){
				q.insert(a[i].c);
				a[i].cnt--;
				remaining_task--;
			}
		}
	}

	char c = a[0].c; // first char
	int time = 0; // time for waiting
	int ans = 0; // the amount of time we used to do all tasks
	for(int i = 0; i < n; i++){
		if(q.getFront() == c){ // we should wait "time" second for this
			while(time){
				cout << "idle ";
				time--; // one second passed
				ans++;
			}
			cout << q.getFront() << " " ;
			q.popFront(); // task done
			ans++;
			time = t; // update t
			continue; // we should go for the next task
		}
		cout << q.getFront() << " ";
		q.popFront(); // task done
		time--; // one second passed
		ans++;
	}
	cout << endl;
	return ans; 
}




int main()
{
	string s = "ADDDDAACBBB";
	int t = 3;
	cout << solve_problem_2(s, t) << endl;
	return 0;
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