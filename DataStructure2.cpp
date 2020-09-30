//data strcture exercise 2

#include<bits/stdc++.h>
using namespace std;

template<class A> ostream& operator <<(ostream& out, const vector<A> &v)
{out << "[";for(int i = 0; i < v.size(); i++) {if(i) out << ", ";out << v[i];}return out << "]";}

int to_number(string s)
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

vector<string> clean(vector<string> v)
{

	vector<string> ans;
	for(int i = 0; i < v.size(); i++){
		if(v[i] != ""){
			ans.push_back(v[i]);
		}
	}
	return ans;
}
vector<string> seperating(string s)
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

vector<string> infix_to_postfix(vector<string> a)
{
	int n = a.size();
	vector<string> postfix(n);

	if(!check_valid(a)){
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
	a = "(A-B/C)*(A/K-L)";
	//*-A/BC-/AKL
	vector<string> ans = infix_to_prefix(seperating(a));
	for(int i = 0; i < ans.size(); i++){
		cout << ans[i];
	}
	cout << endl;
	//ab^c*d*efg/+h--
	return 0;
}