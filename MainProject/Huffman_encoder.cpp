// IN THE NAME OF GOD

#include <bits/stdc++.h>
#define pb push_back
#define SALI main

using namespace std;
typedef pair<int,char> pic;


map<char,string> huff_code; // huffman code for charachters
string binary_huffman_tree = ""; // for creating canonical huffman code in decoder
map<char,string> cano_huff; // canonical huffman code for charachters

void increament(string &s) // increas binary string s by 1 _ s++
{
    bool all_one = true; // if its like 111 it becomes 1000
    for(int i = 0; i < s.size(); i++){
        if(s[i] != '1'){
            all_one = false;
        }
    }
    if(all_one){
        string ans = "1";
        for(int i = 0; i < s.size(); i++){
            ans.pb('0');
        }
        return;
    }
    // found the 0 digit like : 1111(0)0011
    int j = s.size();
    for(j = j-1; s[j] == '1'; j--){
        s[j] = '0';
    }
    s[j] = '1'; // and it becomes like : 0000(1)0011
    return;
}

void canonical() // makes canonical huffman code from the original huffman code
{
    vector<pic> v;
    for(auto &x : huff_code){
        v.pb(pic((x.second).size(), x.first));
    }
    sort(v.begin(), v.end());

    string s = "";
    for(int i = 0; i < v.size(); i++){

        while(s.size() < v[i].first ){
            s.pb('0');
        }
        cano_huff[v[i].second] = s;
        increament(s);
    }
}

class Node
{
public:
    int freq = 0;
    char c = '_';
    Node *left_child = nullptr;
    Node *right_child = nullptr;
    Node(int freq,char c)
    {
        this->freq = freq;
        this->c = c;
    }
    Node(int freq)
    {
        this->freq = freq;
    }
    Node()
    {

    }

};




class MinHeap
{
    vector<Node*> heap;
public:
    void show()
    {
        for(int i = 0; i < heap.size(); i++){
            cout << "[" << heap[i]->c << " " << heap[i]->freq << "] ";
        }
        cout << endl;
        cout << endl;
    }
    MinHeap() 
    {
        Node *zero = new Node(); // just a useless node
        heap.pb(zero);  // we want our minheap be 1 based
    }
    int get_size()
    {
        return heap.size();
    }
    Node* getMin()
    {
        if(heap.size() == 1){
            return nullptr;
        }
        return heap[1];
    }
    void add(Node *node)
    {
        int index = heap.size();
        heap.pb(node);
        while( (heap[index/2]->freq) > (heap[index]->freq) ){
            swap(heap[index/2], heap[index]);
            index /= 2;
        }

    }
    void removeMin()
    {
        int sz = heap.size();
        heap[1] = heap[sz-1];
        heap.pop_back();
        sz--;
        int index = 1;
        while(2*index < sz && 2*index+1 < sz){
            if( (heap[2*index]->freq) < (heap[2*index+1]->freq) ) { // node left is smaller than node right
                if( (heap[2*index]->freq) < (heap[index]->freq)){ // node left is smaller than current node
                    swap(heap[index], heap[2*index]); // swap them
                    index *= 2; // now current node is in the left
                }
                else{
                    break;
                }
            }
            else{ // node right is smaller than left node
                if( (heap[2*index+1]->freq) < (heap[index]->freq)){ // node left is smaller than current node
                    swap(heap[index], heap[2*index+1]); // swap them 
                    index *= 2; // now current node in the right
                    index++;
                }
                else{
                    break;
                }
            }
        }
        
    }
}minheap;


void creat_huffman_tree(string s) // creats huffman tree using minheap
{
    int cnt[256] = {0}; // counting frequancy of each charachter
    for(int i = 0; i < s.size(); i++){
        cnt[s[i]]++;
    }
    for(int i = 0; i < 256; i++){
        if(cnt[i] == 0){
            continue;
        }
        Node *node = new Node(cnt[i], i); // make a node with that frequancy and charachter
        minheap.add(node); // add it to minheap
        
    }
    while(minheap.get_size() > 2) // connect 2 less frequant charachters
    {
        Node *p1 = minheap.getMin();
        minheap.removeMin();
        Node *p2 = minheap.getMin();
        minheap.removeMin();
        int f = (p1->freq) + (p2->freq);
        Node *p3 = new Node(f);
        p3->left_child = p1;
        p3->right_child = p2;
        minheap.add(p3);
    }
}



string make_binary(int n) // ouputs a 8 bit string representing the binary form of n
{
    string ans = "";
    while(n){
        ans.pb( (n%2) + '0');
        n /= 2;
    }
    while(ans.size() != 8){
        ans.pb('0');
    }
    return ans;
}



void dfs(Node* u, string &code) // finding the code of each node using dfs algorithm
{
    if(u->left_child == nullptr && u->right_child == nullptr){
        huff_code[u->c] = code;
        return;
    }
    if(u->left_child != nullptr){
        code.pb('0');
        dfs(u->left_child, code);
        code.pop_back();
    }
    if(u->right_child != nullptr){
        code.pb('1');
        dfs(u->right_child, code);
        code.pop_back();
    }
}

string encode(string &s) // encode the text 
{
    string ans = "";
    for(int i = 0; i < s.size(); i++){
        ans += cano_huff[s[i]];
    }
    return ans;
}




void make_8bit(string &s) // the string length should be divisible by 8
{
    int size = s.size();
    while(size%8 != 0){
        s.pb('0');
        size++;
    }
}
void write_file(fstream &file, string &s) // compres and write binary string into binary file
{
    make_8bit(s);
    for(int i = 0; i < s.size(); i += 8){
        unsigned char x = 0;
        int p = 1;
        for(int j = 0; j < 8; j++){ // if 8 bits are like 00010100 : we insert 20
            x += p*(s[i+j]-'0');
            p *= 2; 
        }
        file.write(reinterpret_cast<char *>(&x), sizeof(char));
    }
    
}

bool is_one_letter(string s) // check if there is only one letter used in text
{
    for(int i = 0; i < s.size(); i++){
        if(s[i] != s[0]){
            return false;
        }
    }
    return true;
}
void fill_binary_huffman_tree()
{
    for(auto &x : huff_code){
        string c = make_binary(x.first);
        binary_huffman_tree += c; // first insert the charachter
        c = make_binary((x.second).size()); 
        binary_huffman_tree += c; // and then the size of huffman code of that charachter
    }
}

int32_t SALI()
{

    //////////////////// read file to string
    string s = "";
    string text = "";
    fstream file;
    file.open("text.txt",ios::in);
    if(!file.is_open()){
        cout << "can't open the file" << endl;
        return 1;
    }
    while(getline(file, s)){ // reads line by line
        text += s;
        text.pb('\n');
    }
    file.close();

    fstream output ("encode.bin", ios::out | ios::binary);
    if (!output)
    {
        cout << "can't open file" << endl;
        return 2;
    }

    if(is_one_letter(text)){
        int size = text.size();
        char letter = text[0];
        int mark = 0;
        output.write(reinterpret_cast<char *>(&mark), sizeof(int));
        output.write(reinterpret_cast<char *>(&size), sizeof(int));
        output.write(reinterpret_cast<char *>(&letter), sizeof(char));
        return 0;
    }
    ///////////////////// make huffman tree for it

    creat_huffman_tree(text);
    string code = "";
    dfs(minheap.getMin(), code);
    canonical();
    string en = encode(text);
    fill_binary_huffman_tree();

    ///////////////////  write the binary string into the binary file
    int size1 = (binary_huffman_tree.size());
    int size2 = (en.size());
    

    output.write(reinterpret_cast<char *>(&size1), sizeof(int));
    write_file(output, binary_huffman_tree);

    output.write(reinterpret_cast<char *>(&size2), sizeof(int));
    write_file(output, en);

    
    output.flush();
    output.close();

    return 0;

}


/**< WRITEN BY ALI ADELKHAH */









