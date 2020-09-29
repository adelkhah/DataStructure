//data strcture exercise 2

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
		if(is_operator(a[i-1]) || is_operator(a[i])){
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

string* infix_to_postfix(string infix[], int n)
{
	string postfix[n];


	for(int i = 0; i < n; i++){
		if(a[i] == "("){

		}
		else if(a[i] == ")"){

		}
		else if(a[i] == "+"){

		}
		else if(a[i] == "-"){

		}
		else if(a[i] == "*"){

		}
		else if(a[i] == "/"){

		}
		else if(a[i] == "^"){

		}
		else{ // a[i] is a number or variable
			postfix.push(a[i]);
		}
	}
}


int postfix_ecalation(string postfix[], int n)
{

}

string* infix_to_prefix(string infix[], int n)
{

}