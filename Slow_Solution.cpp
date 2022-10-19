 #include<bits/stdc++.h>
using namespace std;
int main(){
	int t;
	cin>>t;
	while(t--){
		int  t,maxT,maxN,sumN,n,sum=0;
		cin>>maxT>>maxN>>sumN;
		t = sumN/(maxN);
		if(t<maxT){
			if(sumN%maxN != 0){
				while(t--){
					sum+=pow(maxN,2);
				}
				sum+= pow(sumN%maxN,2);
			}
			else{
				while(t--){
					sum+=pow(maxN,2);
				}
			}
		}
		else{
			while(maxT--){
				sum+=pow(maxN,2);
			}
		}
		cout<<sum<<"\n";
	}
}
