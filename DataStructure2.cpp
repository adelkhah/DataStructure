//data strcture exercise 2

#include<bits/stdc++.h>
using namespace std;


bool is_operator(string s)
{
	if(s == "*" || s == "+" || s == "/" || s == "^" || s == "-"){
		return true;
	}
	return false;
}

bool check_valid(string a[], int n)
{
	int cnt = 0;
	if(is_operator(a[0]) || is_operator(a[n-1])){
		return false;
	}
	for(int i = 1; i < n; i++){
		if(is_operator(a[i-1]) && is_operator(a[i])){
			return false;
		}
	}
	for(int i = 0; i < n; i++){
		if(a[i] == "("){
			cnt++;
		}
		if(a[i] == ")"){
			cnt--;
		}
		if(cnt < 0){
			return false;
		}
	}
	if(cnt != 0){
		return false;
	}
	return true;

}

void infix_to_postfix(string a[], int n, string postfix[])
{
	if(!check_valid(a, n)){
		return;
	}
	int id = 0; // for postfix
	stack<string> stk;

	for(int i = 0; i < n; i++){
		if(a[i] == "("){
			stk.push(a[i]);
		}
		else if(a[i] == ")"){
			while(!stk.empty() && stk.top() != "("){
				postfix[id] = stk.top();
				id++;
				stk.pop();
			}
			stk.pop(); // popping the "(";
		}
		else if(a[i] == "+"){
			while(!stk.empty() && stk.top() != "("){
				postfix[id] = stk.top();
				id++;
				stk.pop();
			}
			stk.push(a[i]);
		}
		else if(a[i] == "-"){
			while(!stk.empty() && stk.top() != "("){
				postfix[id] = stk.top();
				id++;
				stk.pop();
			}
			stk.push(a[i]);
		}
		else if(a[i] == "*"){
			while(!stk.empty() && stk.top() != "(" && stk.top() != "+" && stk.top() != "-"){
				postfix[id] = stk.top();
				id++;
				stk.pop();
			}
			stk.push(a[i]);
		}
		else if(a[i] == "/"){
			while(!stk.empty() && stk.top() != "(" && stk.top() != "+" && stk.top() != "-"){
				postfix[id] = stk.top();
				id++;
				stk.pop();
			}
			stk.push(a[i]);
		}
		else if(a[i] == "^"){
			stk.push(a[i]);
		}
		else{ // a[i] is a number or variable
			postfix[id] = a[i];
			id++;
		}
	}
	while(!stk.empty()){
		postfix[id] = stk.top();
		id++;
		stk.pop();
	}
}



int postfix_ecalation(string postfix[], int n)
{
	return 0;
}

void infix_to_prefix(string infix[], int n, string prefix)
{

}


int main()
{
	
	string a[] = {"a","^","b","*","c","*","d","-","(","(","e","+","f","/","g",")","-","h",")"};
	int n = 19;
	string ans[n];
	infix_to_postfix(a, n, ans);
	for(int i = 0; i < n; i++){
		cout << ans[i];
	}
	return 0;
}
