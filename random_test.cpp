#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>

mt19937_64 prng(chrono::high_resolution_clock::now().time_since_epoch().count());
// returns x such that a <= x <= b
long long random(long long a, long long b)
{
  return uniform_int_distribution<long long>(a, b)(prng);
}

int32_t main(){

    for(int i = 1; i <= 100; i++) cout << random(i, 100) << "\n";
    cout << LLONG_MAX+1;    
    return 0;
}