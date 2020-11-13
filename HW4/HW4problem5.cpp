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

ListNode* reverse_linklist(ListNode *first) // from problem 2
{
	ListNode *cur = first -> next;
	ListNode *pre = first;
	pre -> next = nullptr;
	while(cur != nullptr){
		ListNode *tmp = cur;
		cur = cur->next;
		tmp->next = pre;
		pre = tmp;
	}
	return pre;
}

ListNode* solve_probelm_5(ListNode *a, ListNode *b)
{
	// time complexity of this algorithm is O(size(a) + size(b))
	show(a);
	show(b);
	ListNode *ar = reverse_linklist(a);
	ListNode *br = reverse_linklist(b);
	// reverse the linkedlist then start from the lowest digit
	// add every 2 corresponding digit
	ListNode *cura = ar;
	ListNode *curb = br;
	ListNode *ans = new ListNode(0); // the sum of two linked list
	ListNode *cur = ans;
	while(true){
		// null node at the end is like digit 0
		if(cura->next == nullptr){ 
			cura->next = new ListNode(0);
		}
		if(curb->next == nullptr){
			curb->next = new ListNode(0);
		}
		int sum = (cura->val) + (curb->val);
		cur->val = sum%10; // you can also chekc it by if(sum>10)
		cura = cura->next;
		curb = curb->next;
		cura->val += sum / 10; // you can also do it by if(sum>10) cura->val++
		if(cura->val == 0 && curb->val == 0){ // we reached to the end of linked list
			break;
		}
		cur->next = new ListNode(0); // add a digit zero to ans
		cur = cur -> next;
	}
	// the ans is in order of lowest to greatest (shows 321 like 123)
	// if we want greatest to lowest order we need to reverse it
	return reverse_linklist(ans);
}
	
int main()
{
	ListNode *a7 = new ListNode(9);
	ListNode *a6 = new ListNode(5, a7);
	ListNode *a5 = new ListNode(5, a6);
	ListNode *a4 = new ListNode(6, a5);
	ListNode *a3 = new ListNode(7, a4);
	ListNode *a2 = new ListNode(1, a3);
	ListNode *a1 = new ListNode(9, a2);

	ListNode *b7 = new ListNode(6);
	ListNode *b6 = new ListNode(5, b7);
	ListNode *b5 = new ListNode(4, b6);
	ListNode *b4 = new ListNode(5, b5);
	ListNode *b3 = new ListNode(5, b4);
	ListNode *b2 = new ListNode(1, b3);
	ListNode *b1 = new ListNode(3, b2);
	ListNode *ans = solve_probelm_5(a1, b1);
	show(ans);
	return 0;
}


/**< WRITEN BY ALI ADELKHAH */







