#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<stack>
#include<string>
#include<algorithm>
#include<cmath>
#include<unordered_map>
#include<map>
#include<queue>
#include<tuple>
#include<iomanip>
#include<bitset>
#include<stdio.h>
#include<set>
#include<array>
using namespace std;
#define rep(i,n) for(int i=0;i<(int)(n);i++)
using graph = vector<vector<int>>;
const long long MOD = 1000000007;
const long long INF = 1e18;
using ll = long long;
using P = pair<int,int>;
using matrix = vector<vector<ll>>;

void chmin(int &x,int y){ x = min(x,y); }

int digit(ll x){
  int count = 1;
  while(x/10>0){
    count ++;
    x /= 10;
  }
  return count;
}

bool prime(ll x){
  if(x==1) return false;
  for(ll i=2;i*i<=x;i++){
    if(x%i==0) return false;
  }
  return true;
}

void decom(ll x,map<ll,int> &hatano){
  for(ll i=2;i*i<=x;i++){
    if(x%i==0&&prime(i)){
      while(x%i==0){
      x /= i;
      hatano[i] ++;
    }
    }
  }
  if(x!=1) hatano[x] ++;
}

ll speedpow(ll x,ll y){
  ll res = 1;
  ll test = x;
  for(int i=0;i<31;i++){
    if(y&(1<<i)) res *= test;
    res = res%MOD;
    test = (test*test)%MOD;
  }
  return res;
}

ll combination(ll x,ll y){
  ll test = 1;
  ll test1 = 1;
  for(ll i=0;i<y;i++){
    test = (test*(x-i))%MOD;
    test1 = (test1*(i+1LL))%MOD;
  }
  return (test * speedpow(test1,MOD-2))%MOD ;
}

int euclid(int x,int y){
  if(y==0) return x;
  return euclid(y,x%y);
}

//行列累乗


matrix mul(matrix &a, matrix &b) {
  int p = a.size();
    matrix res(p, vector<long long>(p, 0));
    for(int i = 0; i < p; i++)
        for(int j = 0; j < p; j++)
            for(int k = 0; k < p; k++)
                (res[i][j] += a[i][k] * b[k][j]) %= MOD;
    return res;
}


matrix pow(matrix m, long long k) {
  int p = m.size();
    matrix res(p, vector<long long>(p, 0));
    for(int i = 0; i < p; i++)
        res[i][i] = 1; // 単位行列にする

    while(k > 0) {
        if(k & 1) res = mul(res, m);
        m = mul(m, m);
        k >>= 1;
    }
    return res;
}

// フェニック木
ll n;
ll MAX = 1e6;
ll bit1[1000020];
ll bit2[1000020];

ll sum(ll *b,ll x){
  ll res = 0;
  while(x>0){
    res += b[x];
    x -= x&(-x);
  }
  return res;
}

vector<ll> ans;

void add(ll *b,ll i,ll x){
  //bit[i] += x;
  if(i==0) return;
  while(i<=n){
    b[i] += x;
    i += i&(-i);
    //cout << i << endl;

  }
}

int main(){
  cin >> n;
  int a[n];
/*
  for(int i=1;i<=20010;i++){
    add(bit1,i,0LL);
  }*/

  for(int i=0;i<n;i++){
    ll s;cin >> s;
    a[i] = s+1;
    //add(bit1,a[i],s);
  }

  ll ans = 0;

  for(ll j=0;j<n;j++){
    ans += (j-sum(bit1,a[j]));
    add(bit1,a[j],1);
  }

  cout << ans << endl;

  }
