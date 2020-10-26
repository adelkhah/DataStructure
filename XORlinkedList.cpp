

#include <bits/stdc++.h>
using namespace std;


class Node
{
public:
    int data; 
    Node *npx = NULL; // XOR of next and previous node 
};

Node* XOR(Node *a, Node *b) // return ^ of 2 nodes
{
    return (Node*) ((unsigned int) (a) ^ (unsigned int) (b));
}

class XOR_LinkedList
{
    
public:
    Node *start;
    XOR_LinkedList(){
        start = NULL;
    }
    void insert(int data){
        // create new node
        Node *new_node = new Node(); 
        new_node->data = data; 

        // new_node start ... 
        new_node->npx = start;

        // if the list is not empty then the list is like below
        // new_node  start  start->npx(can be null);
        // so we need to update (start->npx)
        if (start != NULL) 
        { 
            start->npx = XOR(new_node, start->npx); 
        } 

        // now new_node is the start pointer
        start = new_node; 

        // the order of insertion is like below
        // 1
        // 2 1
        // 3 2 1
        // 4 3 2 1
        // ...
        
    }
    void traverse(){
        Node *curr = start; 
        Node *prev = NULL; 
        Node *next; 
        while (curr != NULL) 
        { 
            // print current node 
            cout<<curr->data<<" "; 

            // get address of next node: curr->npx is 
            // next^prev, so curr->npx^prev will be 
            // next^prev^prev which is next 
            next = XOR (prev, curr->npx); 

            // update prev and curr for next iteration 
            prev = curr; 
            curr = next; 
        }
        cout << endl;  
    }

    void remove(int data){
        bool find_node = false;
        // check if a == start then the remove oppration is different
        if(data == start->data){
            // start next nextOFnext
            //       next nextOFnext
            Node *next = start->npx;
            Node *nextOFnext = XOR(next->npx, start);
            next->npx = nextOFnext;
            start = next;
            return;
        }
        // just traverse the list and find the Node*a
        Node *curr = start; 
        Node *prev = NULL; 
        Node *next; 
        while (curr != NULL) 
        { 
            next = XOR (prev, curr->npx); 
            if(curr->data == data){
                find_node = true;
                break;
            }
            prev = curr; 
            curr = next; 
        }
        if(find_node == false){
            cout << "there is no such a node to remove" << endl;
            return;
        }

        // preOFpre pre (curr) next nextOFnext
        // preOFpre pre        next nextOFnext
        Node *preOFpre = XOR(prev->npx, curr);
        Node *nextOFnext = XOR(next->npx, curr);
        prev->npx = XOR(preOFpre, next); 
        next->npx = XOR(nextOFnext, prev);
         
    }
};



int main () 
{ 
    // Create following Doubly Linked List 
    // 90 80 70 60 50 40 30 20 10
    XOR_LinkedList a;
    for(int i = 1; i < 10; i++){
        a.insert(i*10);
    }
    a.traverse();

    // testing remove oppration
    a.remove(100); // there is no such a node

    a.remove(90);
    a.traverse();

    a.remove(40);
    a.traverse();

    a.remove(80);
    a.traverse();

    a.remove(50);
    a.traverse();

    return 0; 
} 