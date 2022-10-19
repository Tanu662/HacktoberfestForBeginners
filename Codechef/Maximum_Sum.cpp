// #pragma GCC target("fpmath=sse,sse2") // off
// #pragma GCC target("fpmath=387") // on
#include <bits/stdc++.h>
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
const int mod = 1e9 + 7;
#define int long long
#define FOR(i,a,b) for(int i=a;i<(int)b;i++)
#define FORr(i,a,b) for(int i =a;i>=(int)b;i--)
#define rep(i,n) FOR(i,0,n)
#define rep1(i,n) FOR(i,1,n)
#define print(arr)  for(auto a: arr) cout << a<< " "; cout << endl;
#define in(a) int a; cin >> a;
#define inp(arr,n) vector<int>arr(n); for(auto &a: arr) cin >> a;
#define pb emplace_back
#define all(a) a.begin(), a.end()
#define mp make_pair
#define f first
#define vi vector<int>
#define s second
#define mxheap priority_queue<int>
#define mnheap priority_queue<int, vector<int>, greater<int>>
#define mxheap2 priority_queue<pair<int,int>>
#define mnheap2 priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>
#define ordered_set tree<ll, null_type, less<ll>, rb_tree_tag, tree_order_statistics_node_update>
#define case cout << "Case "<< tt << ": ";
inline int uceil(int a,int b) {return (a % b ? a / b + 1 : a / b);}
#define pll pair<int, int>
#define set_bit(x, idx) x = x|(1LL<<idx)
int dx[8] = {0,1,0,-1,1,-1,1,-1};
int dy[8] = {-1,0,1,0,1,1,-1,-1};
#define toggle_bit(x, idx) x = x^(1LL<<idx)
#define check_bit(x, idx) min(x&(1LL<<idx),1LL)
#define endl "\n"
#define yes cout << "Yes\n";
#define no cout << "No\n";
#define db long double
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
#define rng(x,y) uniform_int_distribution<int>(x,y)(rng)


#ifdef DEBUG
#include "tpc.hpp"
#define pause(x) thamm(x)
#define ios
#define dbg(...) {cerr << __LINE__ << " : " ;cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__);}
#define ok tikkk
#elif ASHIQ
#define pause(x) 
#define ios
#define dbg(...) 
#define ok
#else
#define pause(x) 
#define ios {ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);}
#define dbg(...) 
#define ok
#endif

int n;
vector<vector<pll>>arr;
vector<int>nxt;
int power(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) {
            res = res * a;
            res %= mod;
        }
        a = a * a;
        a %= mod;
        b >>= 1;
    }
    return res;
}
vector<pll>lcm(vector<pll>&a, vector<pll>&b){
    vector<pll>fin;
    int idx = 0;
    for(auto x: a){
        while(idx < b.size() and x.f > a[idx].f){
            fin.pb(b[idx]);
            idx++;
        }
        if(idx < b.size() and x.f == b[idx].f){
            x.s = max(x.s, b[idx].s);
            idx++;
        }
        fin.pb(x);
    }
    while(idx < b.size()) fin.pb(b[idx++]);
    return fin;
}
vector<pll>gcd(vector<pll>&a, vector<pll>&b){
    vector<pll>fin;
    int idx = 0;
    for(auto x: a){
        while(idx < b.size() and x.f > b[idx].f){
            idx++;
        }
        if(idx < b.size() and x.f == b[idx].f){
            x.s = min(x.s, b[idx].s);
            fin.pb(x);
            idx++;
        }
    }
    return fin;
}
int getval(vector<pll>&a){
    int ans = 1;
    for(auto x: a){
        ans *= power(x.f, x.s);
        ans %= mod;
    }
    return ans;
}


void buildnxt(){
    int nw = 0;
    int lst = 0;
    while(nw < n){
        vector<int>mls;
        while(nw < n and arr[lst] == arr[nw]){
            mls.pb(nw);
            nw = nxt[nw];
        }
        for(auto a: mls) nxt[a] = nw;
        lst = nw;
    }
}

int getlcm(int lm){  
    vector<pll>lc = arr[0];
    buildnxt();
    rep1(i, lm){
        if(arr[i] == arr[i-1]){
            i = nxt[i];
            i--;
        }
        //dbg(i);
        arr[i-1] = gcd(arr[i], lc);
        lc = lcm(arr[i],lc);
        //dbg(i, lc);
    }
    return getval(lc);
}
const int N = 1e6+10;

vector<int> tmp(N);

void seive() {
    for (int i = 2; i < N; i++)
        tmp[i] = i;
    for (int i = 2; i * i < N; i++) 
        if (tmp[i] == i)
            for (int j = 2 * i; j < N; j += i)
                if (tmp[j] == j)
                    tmp[j] = i;
}

vector<pll> prime_fact(int x) {
    vector<pll> res;
    while (x > 1) {
        int nw = tmp[x];
        int cnt = 0;
        while(x%nw == 0){
            x /= nw;
            cnt++;
        }
        res.pb(mp(nw,cnt));
    }
    return res;
}

void solvetc(int tt){
    cin >> n; arr.resize(n);
    rep(i, n){
        in(x) arr[i] = prime_fact(x);
    }

    for(int j = 0; j < 20; j++){
        for(int i = 1; i < n; i++){
            vector<pll>a= gcd(arr[i], arr[i-1]);
            vector<pll>b= lcm(arr[i], arr[i-1]);
            arr[i-1] = a;
            arr[i] = b;
        }
    }
    int ans = 0;
    for(auto a: arr) ans += getval(a);
    cout << ans << endl;
}

int32_t main()
{
    seive();
    ios ;
    #ifdef DEBUG
    //freopen("in", "r", stdin);
    #endif 
    int nn = 1;
    cin >> nn;
    rep(i, nn) solvetc(i+1);
}
