#pragma GCC optimize "trapv"
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
int SEED;
// seeds 1, 2, 3 respectively for 1, 2, 3
// For feature 1:
// for small, MAX_N = 10^3, MAX_K = 10^5
// for large MAX_N = 10^6, MAX_K = 10^9
// For feature 2:
// MAX_N = 10^6, MAX_K = 10^9
mt19937_64 prng(SEED); // chrono::high_resolution_clock::now().time_since_epoch().count()
// returns x such that a <= x <= b
long long random(long long a, long long b)
{
  return uniform_int_distribution<long long>(a, b)(prng);
}

// int rnd(int a, int b){
//     return a + rand() % (b - a + 1);
// }

int32_t main(int32_t argc, char* argv[]){
    int type = stoi(argv[1]);
    SEED = stoi(argv[2]);
    prng.seed(SEED);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int T = 10; // cin >> T;
    cout << T << "\n";

    while(T--){
        // cout << T << ":\n";
        const int MIN_N = 1, MAX_N = stoi(argv[3]);
        const int n = MAX_N;
        assert(MIN_N <= n and n <= MAX_N);

        const int MIN_K = 1, MAX_K = stoi(argv[4]);
        const int k = MAX_K;
        assert(MIN_K <= k and k <= MAX_K);
        // cout << T << ":\n";

        cout << n << " " << k << " " << type << "\n";
        int MIN_Ai = 1, MAX_Ai = k;
        if(type == 1){
            for(int i = 1; i <= n; i++){
                int ai = random(MIN_Ai, MAX_Ai);
                assert(MIN_Ai <= ai and ai <= k);
                cout << ai << " ";
            }
        }
        else{
            for(int i = 1; i < n; i++){
                int ai = random(MAX_Ai-10, MAX_Ai);
                assert(MAX_Ai-10 <= ai and ai <= MAX_Ai);
                cout << ai << " ";
            }
            cout << 1 << " ";
        }
        cout << endl;
        vector<pii> queries;
        
        if(type == 1){
            int prev = -1;

            while(prev+2 <= n){
                
                int l = prev+2;
                int width = (int)(sqrtl(MAX_N));
                int r = l + width-1;
                if(r > n) break;
                assert(l > prev);
                assert(l <= n);
                assert(r >= l);
                assert(r <= n);
                queries.push_back({l, r});
                prev = r;
            }
        }
        else{
            int prev = 0;
            while(prev+1 <= n){
                int l = prev+1;
                int width = 2;
                int r = l + width-1;
                if(r > n/2) break;
                assert(l > prev);
                assert(l <= n);
                assert(r >= l);
                assert(r <= n);
                queries.push_back({l, r});
                prev = l;
            }
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
