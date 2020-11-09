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

ListNode* solve_probelm_1(ListNode *first, int V)
{
	while(first -> val == V){ // delete all nodes in the begining with value of V
		first = first -> next;
	}
	// now first->val deffenitly is not V
	ListNode *pre = first;
	ListNode *cur = first -> next;
	while(cur != nullptr){
		if(cur -> val == V){ // delete "cur" and don't change "pre" 
			//	pre cur   cur->next
			//   a   V       b
			pre -> next = cur -> next; 
			cur = cur -> next;
			// pre   cur
			//  a     b
		}
		else{ // just move on
			pre = pre -> next; 
			cur = cur -> next; 
		}
	}
	return first;
}
	
int main()
{
	ListNode *a7 = new ListNode(6);
	ListNode *a6 = new ListNode(5, a7);
	ListNode *a5 = new ListNode(4, a6);
	ListNode *a4 = new ListNode(3, a5);
	ListNode *a3 = new ListNode(6, a4);
	ListNode *a2 = new ListNode(2, a3);
	ListNode *a1 = new ListNode(1, a2);
	show(a1);
	ListNode *ans = solve_probelm_1(a1, 6);
	show(ans);
	return 0;
}


/**< WRITEN BY ALI ADELKHAH */







