#include <bits/stdc++.h>
using namespace std;


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
}