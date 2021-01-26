// IN THE NAME OF GOD

#include <bits/stdc++.h>
#define pb push_back
#define SALI main

using namespace std;
typedef pair<int,char> pic;

map<char,int> huff_code; // huffman length code for charachter
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
        v.pb(pic(x.second , x.first));
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




string get_byte(string &s,int n, int id) // output substring from s of length n starting from id
{
    string ans; ans.clear();
    for(int i = id; i < id+n; i++){
        ans.pb(s[i]);
    }
    return ans;
}

int string_to_integer(string &s) // workd like : string(10001) -> int(17)
{
    int ans = 0;
    for(int i = 0; i < s.size(); i++){
        ans += (s[i]-'0') * (1<<i);
    }
    return ans;
}

void make_node(string code, char charac, Node *root) // makes a node which its path from root is "code" 
{
    Node *cur = root;
    for(int i = 0; i < code.size(); i++){
        if(code[i] == '0'){ // go left
            if(cur->left_child == nullptr){
                cur->left_child = new Node();
            }
            cur = cur->left_child;
        }
        else{ // go right
            if(cur->right_child == nullptr){
                cur->right_child = new Node();
            }
            cur = cur->right_child;
        }
    }
    cur->c = charac;
}
void creat_canonical_huffman_tree_from_binary(string &s, Node *root)
{
    int index = 0;
    while(index < s.size()){
        string chr = get_byte(s, 8, index);
        char charachter = (char)string_to_integer(chr);
        // read the charachter
        string dis = get_byte(s,8, index + 8);
        int len = string_to_integer(dis);
        // read frequancy of it
        huff_code[charachter] = len;
        index += 16;
    }

    canonical(); // creat canonical codes
    for(auto &x : cano_huff){ // make a node for each of it
        make_node(x.second, x.first, root);
    }

}



string decode(string &s, Node *root) // decode the string s
{
    string ans = "";
    Node *node = root;
	for(int i = 0; i < s.size(); i++){
        if(s[i] == '0'){
            node = node->left_child;
        }
        if(s[i] == '1'){
            node = node->right_child;
        }
        if(node->left_child == nullptr && node->right_child == nullptr){
            ans.pb(node->c);
            node = root;
        }
	}
	return ans;
}


void make_8bit(string &s) // just append 0 to string so its lenght is divisible by 8
{
    int size = s.size();
    while(size%8 != 0){
        s.pb('0');
        size++;
    }
}

string dicompres(unsigned int x) // int(20) -> string(00010100)
{
    string ans = "";
    while(x){
        ans.pb((x%2) + '0');
        x /= 2;
    }
    make_8bit(ans);
    return ans;
}

string read_file(fstream &file, int n) // raeds n byte from file
{
    unsigned char buf;
    string ans = "";
    for(int i = 0; i < n; i++){
        file.read(reinterpret_cast<char *> (&buf), 1);
        ans += dicompres(buf); 
    }
    return ans;
}

int32_t SALI()
{
    Node *root = new Node();
    int size_huffman;
    string binary_huffman_tree = "";
    int size_text;
    string binary_text = "";
    char *buf;

    fstream input("encode.bin", ios::in | ios::binary);
    if (!input)
    {
        cout << "can't open file" << endl;
        return 1;
    }

    input.read(reinterpret_cast<char *>(&size_huffman), sizeof(int));
    if(size_huffman == 0){ // there is only one letter used in the text
        int cnt;
        char letter;
        input.read(reinterpret_cast<char *>(&cnt), sizeof(int)); // how many times it used
        input.read(reinterpret_cast<char *>(&letter), sizeof(char)); // what letter it was
        string dec = "";
        for(int i = 0; i < cnt; i++){
            dec.pb(letter);
        }
        fstream output;
        output.open("decode.txt", ios::out | ios::in);
        if(!output.is_open()){
            cout << "can't open file" << endl;
            return 2;
        }
        output << dec;
        output.flush();
        output.close();
        return 0;
    }

    int round_up = (size_huffman+7)/8;
    binary_huffman_tree = read_file(input, round_up);
    for(int i = 0; i < (8*round_up) - size_huffman; i++){
        binary_huffman_tree.pop_back();
    }


    input.read(reinterpret_cast<char *>(&size_text), sizeof(int));
    round_up = (size_text+7)/8;
    binary_text = read_file(input, round_up);
    for(int i = 0; i < (8*round_up) - size_text; i++){
        binary_text.pop_back();
    }
    
    creat_canonical_huffman_tree_from_binary(binary_huffman_tree, root);

    string de = decode(binary_text, root);
    
    fstream output;
    output.open("decode.txt", ios::out | ios::in);
    if(!output.is_open()){
        cout << "can't open file" << endl;
        return 2;
    }
    
    output << de;
    output.flush();
    output.close();
    return 0;
}


/**< WRITEN BY ALI ADELKHAH */









