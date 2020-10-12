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
	void addPQ(int x){
		a[size] = x;
		size++;
	}
	void deletePQ(){
		int index = find_highest_priority();
		for(int i = index; i < size; i++){
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

int main()
{
	// code
	return 0;
}