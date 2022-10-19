#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	string s;
	int t,n,c;
	cin>>t;
	while(t--){
	    c=0;
	    cin>>n>>s;
	    for(int i=0;i<n&&c<4;i++){
	        if(s[i]=='a'||s[i]=='e'||s[i]=='i'||s[i]=='o'||s[i]=='u'){
	            c=0;
	            continue;
	        }
	        c++;
	    }
	    if(c<4)
	        cout<<"Yes"<<endl;
	    else
	        cout<<"No"<<endl;
	}
	return 0;
}
