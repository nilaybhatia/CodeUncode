#pragma GCC optimize "trapv"
#include<bits/stdc++.h>
using namespace std;
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
            
            // int total_buffered_size = accumulate(a.begin()+l, a.begin()+r+1, 0LL);
            int total_buffered_size = 0;
            for(int j = l; j <= r; j++){
                total_buffered_size += a[j];
            }
            // cout << l << " " << r << " " << total_buffered_size << "\n";
            
            int lower, higher;
            if(type == 1) {
                lower = r+1;
                higher = ((i == q-1)? n+1 : queries[i+1].first);
            }
            else {
                lower = r+1, higher = n+1;
                for(int j = 0; j < q; j++){
                    if(queries[j].first > r){
                        lower = queries[j-1].second;
                        higher = queries[j].first;
                        break;
                    }
                    r = max(r, queries[j].second);
                }
                // cout << lower << " " << higher << "\n";
            }
            for(int j = lower; j < higher and total_buffered_size > 0; j++){
                total_buffered_size -= (k - a[j]);
            }
            if(total_buffered_size > 0){
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