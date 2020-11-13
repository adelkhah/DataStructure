// Ali Adelkhah
// 9812762372


#include <bits/stdc++.h>
using namespace std;


struct ListNode
{
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr){}
	ListNode(int x) : val(x), next(nullptr){}
	ListNode(int x, ListNode *next) : val(x), next(next){}
};

void show(ListNode *node) // showing the linked list
{
	while(node != nullptr){
		cout << (node->val) << " ";
		node = node -> next;
	}
	cout << endl;
}

bool solve_problem_2(ListNode *first)
{
	int size = 0; // size of the link list
	// solved without using any extra memory in time complexity of O(size^2)
	bool palindrom = true;
	ListNode *node = first;
	ListNode *check = first;
	int ind_node = 0;
	int ind_check = 0;
	while(node != nullptr){ // find the size of link list
		size++;
		node = node -> next;
	}
	node = first;
	while(ind_node < size/2){ // we need to check first half with the second half
		ind_check = 0;
		check = first;
		while(ind_check < size - ind_node - 1){ // put node "check" at index (size-ind_node-1) 
			check = check -> next;
			ind_check++;
		}
		if(check -> val != node -> val){ // check if they have equal value
			palindrom = false;
		}
		node = node -> next; // go for the next node
		ind_node++;
	}
	return palindrom;
}
	
int main()
{
	ListNode *a7 = new ListNode(6);
	ListNode *a6 = new ListNode(5, a7);
	ListNode *a5 = new ListNode(4, a6);
	ListNode *a4 = new ListNode(23, a5);
	ListNode *a3 = new ListNode(4, a4);
	ListNode *a2 = new ListNode(5, a3);
	ListNode *a1 = new ListNode(6, a2);
	show(a1);
	cout << solve_problem_2(a1) << endl;
	return 0;
}

/**< WRITEN BY ALI ADELKHAH */







