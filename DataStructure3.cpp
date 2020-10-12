#include <bits/stdc++.h>
using namespace std;

const int MAX_SIZE = 10000;

class PriorityQueue
{
	int size = 0;
	int a[MAX_SIZE];
private:
	int find_highest_priority(){ // returns the index of that element
		int index;
		int maximum = 0;
		for(int i = 0; i < size; i++){
			if(a[i] > maximum){
				maximum = a[i];
				index = i;
			}
		}
		return index;
	}
public:
	void insert(int x){
		a[size] = x;
		size++;
	}
	void remove(){
		int index = find_highest_priority();
		for(int i = index; i < size; i++){ // shift [index,size) to left
			a[i] = a[i+1];
		}
		size--;
	}

	bool empty(){
		if(size == 0){
			return true;
		}
		return false;
	}

};

class Deque // implementing input-restricted which insertion is one sided
{
	int size = 0;
	int a[MAX_SIZE];
public:
	void remove_back(){
		size--;
	}
	void remove_front(){
		for(int i = 0; i < size; i++){ // shift [1,size) to left
			a[i] = a[i+1];
		}
		size--;
	}
	void insert(int x){
		a[size] = x;
		size++;
	}
	
};

int main()
{
	// no need to test :)
	return 0;
}