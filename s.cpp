#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include<stack>
#include<string>
#include<algorithm>
#include<cmath>
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


int main(){
  /*ll N;ll K;cin >> N >> K;matrix A;
  A.assign(N,vector<ll>(N));

  rep(i,N) rep(j,N) cin >> A[i][j];

  A = pow(A,K);

  ll res = 0;

  rep(i,N)rep(j,N) res = (res + A[i][j])%MOD;

  cout << res << endl;*/
/*
  ll k;
  ll n,m;cin >> n >> m >> k;
  ll a[n];
  rep(i,n) cin >> a[i];

  matrix A;
  A.assign(n,vector<ll>(n,0));

  rep(i,m){
    int x,y;cin >> x >> y;
    A[x-1][y-1] = 1;
    A[y-1][x-1] = 1;
  }
  rep(i,n){
    ll count = 0;
    for(int j=0;j<n;j++) if(A[i][j]>0) count ++;
    //cout << count << endl;
    A[i][i] = 2LL*m-count;
  }

  A=pow(A,k);
  ll hatano = speedpow(2LL*(m),k*(MOD-2LL));
  //hatano = speedpow(hatano,MOD-2);

  rep(i,n){
    ll ans = 0;
    rep(j,n){
      ll test = (A[i][j] * a[j])%MOD;
      ans += test;
      ans %= MOD;
    }
    cout << (ans*hatano)% MOD << endl;
  }
//  cout << A[0][0] << endl;


cout << speedpow(2,MOD-2)*3%MOD<< endl;*/

  string s;cin >> s;
  int d;cin >> d;

  int p = s.size();

  vector<vector<vector<ll>>> dp(p+1,vector<vector<ll>>(d,vector<ll>(2,0)));
  dp[0][0][1] = 1;

  rep(i,p){
    //cout << s[i] - '0';
  //  cout << endl;
    rep(j,d){
      rep(m,2){
        rep(l,10){
          if(m==1){
            if(l<s[i]-'0'){
              dp[i+1][(j+l)%d][0] += dp[i][j][1];
              dp[i+1][(j+l)%d][0] %= MOD;
            //  cout << l << " " << j << endl;
            }
            else if(l==s[i]-'0'){
              dp[i+1][(j+l)%d][1] += dp[i][j][1];
              dp[i+1][(j+l)%d][1] %= MOD;
            }
          }

          else{
            dp[i+1][(j+l)%d][0] += dp[i][j][0];
            dp[i+1][(j+l)%d][0] %= MOD;

          }

        }
      }
    }
  }



  cout << (dp[p][0][0] + dp[p][0][1] -1 + MOD)%MOD<< endl;


}
