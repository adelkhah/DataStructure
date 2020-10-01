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
	}
	while(!stk.empty()){
		postfix[id] = stk.top();
		id++;
		stk.pop();
	}
	return postfix;
}



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


int main()
{

	
	string a = "a^b*c*d-((e+f/g)-h)";
	//a = "a+b*c+d";
	//a = "(A-B/C)*(A/K-L)";
	//prefix : *-A/BC-/AKL
	//postfix : ab^c*d*efg/+h--
	vector<string> prefix = infix_to_prefix(seperating(a));
	vector<string> postfix = infix_to_postfix(seperating(a));
	
	cout << "prefix : ";
	for(int i = 0; i < prefix.size(); i++){
		cout << prefix[i];
	}
	cout << endl << "postfix : ";
	for(int i = 0; i < postfix.size(); i++){
		cout << postfix[i];
	}
	cout << endl;
	return 0;
}
