#pragma GCC optimize "trapv"
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>

int32_t main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T; cin >> T;

    while(T--){
        int n, k, type; cin >> n >> k >> type;

        vector<int> a(n+1);
        for(int i = 1; i <= n; i++){
            cin >> a[i];
            assert( 1 <= a[i] and a[i] <= k);
        }


        int q; cin >> q;
        vector<pii> queries;

        for(int i = 1; i <= q; i++){
            int l, r; cin >> l >> r;
            queries.push_back({l, r});
        }

        sort(queries.begin(), queries.end());
        bool smooth = true;
        for(int i = 0; i < q; i++){
            pii qry = queries[i];
            int l = qry.first, r = qry.second;
            
            int sum = accumulate(a.begin()+l, a.begin()+r+1, 0LL);
            
            int lower;
            if(type == 1) lower = r+1;
            else {
                pii tmp = {r, -1};
                auto it = upper_bound(queries.begin(), queries.end(), tmp);
                assert(it != queries.begin());
                lower = prev(it)->second+1;

            }

            for(int j = lower; sum > 0; j++){
                if(i == q-1){
                    if(j > n) break;
                }
                else{
                    if(j >= queries[i+1].first) break;
                }
                sum -= (k - a[j]);
            }
            if(sum > 0){
                smooth = false;
                break;
            }

        }
        
        if(smooth) cout << "YES";
        else cout << "NO";
        cout << "\n";

    }

    return 0;
}