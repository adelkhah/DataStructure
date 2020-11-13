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

ListNode* solve_probelm_4(ListNode *first)
{
	// time complexity of this algorithm is also O(size^2)
	ListNode *cur = first;
	ListNode *pre = nullptr;
	ListNode *lo = nullptr; // pointer to the last odd element
	ListNode *fo = nullptr; // pointer to the first odd element
	ListNode *fe = nullptr; // pointer to the first even element
	while(cur != nullptr){
		if(cur->val % 2 == 0 && fe == nullptr){
			fe = cur;
		}
		if(cur->val % 2 == 1 && fo == nullptr){
			fo = cur;
		}

		ListNode *tmp = cur->next;
		while(tmp != nullptr){ 
		// find the next element with same remainder devided by 2
			if(tmp->val % 2 == cur -> val % 2){ // found it
				break;
			}
			tmp = tmp -> next;
		}

		if(tmp == nullptr && cur -> val % 2 == 1){
			// there is no odd element after cur 
			// so cur is the last odd element
			lo = cur;
		}
		// link the 2 node with same remainder devided by 2
		// and go for the next node
		pre = cur;
		cur = cur -> next;
		pre -> next = tmp;
	}
	// link odd element to the even element
	lo -> next = fe;
	return fo;
}

int main()
{
	ListNode *a7 = new ListNode(6);
	ListNode *a6 = new ListNode(5, a7);
	ListNode *a5 = new ListNode(4, a6);
	ListNode *a4 = new ListNode(3, a5);
	ListNode *a3 = new ListNode(2, a4);
	ListNode *a2 = new ListNode(1, a3);
	ListNode *a1 = new ListNode(0, a2);
	show(a1);
	ListNode *ans = solve_probelm_4(a1);
	show(ans);
	return 0;
}


/**< WRITEN BY ALI ADELKHAH */







