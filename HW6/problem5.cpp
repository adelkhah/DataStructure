

#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n = 9;
	cin >> n;
	int a[n];
	int mxm = 0;
	for(int i = 0; i < n; i++){
		cin >> a[i];
		mxm = max(a[i],mxm);
	}
	int exist[mxm] = {0};
	for(int i = 0; i < n; i++){
		exist[a[i]] = 1;
	}
	int ans = 0;
	int cnt = 0;
	for(int i = 0; i < mxm; i++){
		if(exist[i] == 0){
			cnt = 0;
		}
		cnt += exist[i];
		ans = max(ans, cnt);
	}
	cout << ans << endl;

}


/**< WRITEN BY ALI ADELKHAH */

