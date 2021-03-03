#pragma GCC optimize "trapv"
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>

// seeds 1, 2, 3 respectively for 1, 2, 3
// for small, MAX_N = 10^3, MAX_K = 10^5, width = 31
// for large MAX_N = 10^6, MAX_K = 10^9, width = 1000

mt19937_64 prng(1); // chrono::high_resolution_clock::now().time_since_epoch().count()
// returns x such that a <= x <= b
long long random(long long a, long long b)
{
  return uniform_int_distribution<long long>(a, b)(prng);
}

// int rnd(int a, int b){
//     return a + rand() % (b - a + 1);
// }

int32_t main(int32_t argc, char* argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 10; // cin >> T;
    cout << T << "\n";

    while(T--){
        // cout << T << ":\n";
        const int MIN_N = 1, MAX_N = 1000;
        const int n = MAX_N;
        assert(MIN_N <= n and n <= MAX_N);

        const int MIN_K = 1, MAX_K = 100000;
        const int k = MAX_K;
        assert(MIN_K <= k and k <= MAX_K);
        // cout << T << ":\n";

        cout << n << " " << k << "\n";
        int MIN_Ai = 1, MAX_Ai = k;
        for(int i = 1; i <= n; i++){
            int ai = random(MIN_Ai, MAX_Ai);
            assert(MIN_Ai <= ai and ai <= k);
            cout << ai << " ";
        }
        cout << endl;
        vector<pii> queries;
        int prev = -1;

        while(prev+2 <= n){
            
            int l = prev+2;
            int width = 31;
            int r = l + width-1;
            if(r > n) break;
            assert(l > prev);
            assert(l <= n);
            assert(r >= l);
            assert(r <= n);
            queries.push_back({l, r});
            prev = r;
        }
        int q = queries.size();
        cout << q << "\n";
        random_shuffle(queries.begin(), queries.end());
        for(int i = 0; i < q; i++){
            cout << queries[i].first << " " << queries[i].second << "\n";
        }
        // cout << "-------------------------------\n";
    }
    return 0;
}
