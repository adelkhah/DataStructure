//data strcture exercise 2

#include<bits/stdc++.h>
using namespace std;

int to_number(string s) // convert "123" to 123
{
	int ans = 0;
	for(int i = s.size()-1; i >= 0; i--){
		int tmp = s[i] - '0';
		ans *= 10;
		ans += tmp;
	}
	return ans;
}
bool is_operator(string s)
{
	if(s == "*" || s == "+" || s == "/" || s == "^" || s == "-"){
		return true;
	}
	return false;
}
bool is_operator(char s)
{
	if(s == '*' || s == '+' || s == '/' || s == '^' || s == '-'){
		return true;
	}
	return false;
}

vector<string> clean(vector<string> v) // cleaning form empty element
{

	vector<string> ans;
	for(int i = 0; i < v.size(); i++){
		if(v[i] != ""){
			ans.push_back(v[i]);
		}
	}
	return ans;
}

vector<string> seperating(string s) // convert "12*23+5" to ["12", "*", "23", "+", "5"]
{
	int n = s.size();
	vector<string> ans;
	int id = 0;
	string tmp;
	for(int i = 0; i < s.size(); i++){
		if(is_operator(s[i]) || s[i] == '(' || s[i] == ')'){
			ans.push_back(tmp);
			id++;
			tmp = "";
			tmp += s[i];
			ans.push_back(tmp);
			tmp = "";
		}
		else{
			tmp += s[i];
		}
	}
	ans.push_back(tmp);
	ans = clean(ans);
	return ans;

}

bool check_valid(vector<string> a)
{
	int n = a.size();
	int cnt = 0;
	if(is_operator(a[0]) || is_operator(a[n-1])){ // +4*3- is invalid
		return false;
	}
	for(int i = 1; i < n; i++){ // 3++4 is invalid
		if(is_operator(a[i-1]) && is_operator(a[i])){
			return false;
		}
	}

	// this part is checking valid paranteses
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


void print(stack<string> s)
{
	vector<string> ans;
	while(s.size()){
		ans.push_back(s.top());
		s.pop();
	}
	reverse(ans.begin(), ans.end());
	for(int i = 0; i < ans.size(); i++){
		cout << ans[i] << " ";
	}
	cout << endl;
}
void printv(vector<string> v)
{
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}
	cout << endl;
}
// question 1
vector<string> infix_to_postfix(vector<string> a)
{
	int n = a.size();
	vector<string> postfix(n); // creating a vector of string with size n

	if(!check_valid(a)){
		cout << "invalid" << endl;
		return postfix;
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
			stk.push(a[i]); // pushing "+"
		}
		else if(a[i] == "-"){
			while(!stk.empty() && stk.top() != "("){
				postfix[id] = stk.top();
				id++;
				stk.pop();
			}
			stk.push(a[i]); // pushing "-"
		}
		else if(a[i] == "*"){
			while(!stk.empty() && stk.top() != "(" && stk.top() != "+" && stk.top() != "-"){
				postfix[id] = stk.top();
				id++;
				stk.pop();
			}
			stk.push(a[i]); // pushing "*"
		}
		else if(a[i] == "/"){
			while(!stk.empty() && stk.top() != "(" && stk.top() != "+" && stk.top() != "-"){
				postfix[id] = stk.top();
				id++;
				stk.pop();
			}
			stk.push(a[i]); // pushing "/"
		}
		else if(a[i] == "^"){ // there is no operator with priority more than ^ in the string
			stk.push(a[i]);
		}
		else{ // a[i] is a number or variable
			postfix[id] = a[i];
			id++;
		}
		print(stk);
		printv(postfix);
		cout << endl;
	}
	while(!stk.empty()){
		postfix[id] = stk.top();
		id++;
		stk.pop();
	}
	return postfix;
}


// question 1
int postfix_evalation(vector<string> a)
{
	stack<int> stk;
	for(int i = 0; i < a.size(); i++){
		if(a[i] == "+"){
			int a = stk.top();
			stk.pop();
			int b = stk.top();
			stk.pop();
			stk.push(b+a);
		}
		else if(a[i] == "-"){
			int a = stk.top();
			stk.pop();
			int b = stk.top();
			stk.pop();
			stk.push(b-a);
		}
		else if(a[i] == "*"){
			int a = stk.top();
			stk.pop();
			int b = stk.top();
			stk.pop();
			stk.push(b*a);
		}
		else if(a[i] == "/"){
			int a = stk.top();
			stk.pop();
			int b = stk.top();
			stk.pop();
			stk.push(b/a);
		}
		else if(a[i] == "^"){
			int a = stk.top();
			stk.pop();
			int b = stk.top();
			stk.pop();
			int tmp = pow(b,a);
			stk.push(tmp);
		}
		else{
			stk.push(to_number(a[i]));
		}

	}
	return stk.top();
}


// question 2
vector<string> infix_to_prefix(vector<string> a)
{
	
	reverse(a.begin(), a.end());

	for(int i = 0; i < a.size(); i++){
		if(a[i] == "("){
			a[i] = ")";
		}
		else if(a[i] == ")"){
			a[i] = "(";
		}
	}
	
	
	vector<string> prefix = infix_to_postfix(a);
	reverse(prefix.begin(), prefix.end());
	return prefix;
}

void solve_2stack_problem(stack<int> s1, stack<int> s2);

int main()
{

	
	string a = "6+1-4*(3^2*(8-1)/3+4-2)*5";
	
	vector<string> postfix = infix_to_postfix(seperating(a));
	cout << endl << "postfix : ";
	for(int i = 0; i < postfix.size(); i++){
		cout << postfix[i] << " ";
	}
	cout << endl;
	return 0;
}

// written by Ali Adelkhah




void solve_2stack_problem(stack<int> s1, stack<int> s2) // 1 ... n are in the s1
{

	int number_to_remove = 1; // the number we want to print and then remove
	while(!s1.empty() || !s2.empty()){
		if(number_to_remove % 2 == 1){ // then we want to remove from the begin
			while(!s1.empty()){ // move all elements from s1 to s2
				s2.push(s1.top());
				s1.pop();
			}
			for(int i = 0; i < min(number_to_remove,(int)s2.size()); i++){ // remove elements
				cout << s2.top() << endl;
				s2.pop();
			}
			number_to_remove++;
		}

		else{ // then we want to remove from the end
			while(!s2.empty()){ // move all elements from s2 to s1
				s1.push(s2.top());
				s2.pop();
			}
			for(int i = 0; i < min(number_to_remove,(int)s1.size()); i++){ // remove elements
				cout << s1.top() << endl;
				s1.pop();
			}
			number_to_remove++;
		}
	}
	
}