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

        // create required prefix arrays
        vector<int> pref_a(n+1);
        for(int i = 1; i <= n; i++){
            pref_a[i] = pref_a[i-1] + a[i];
        }
        
        vector<int> pref_remaining(n+1);
        for(int i = 1; i <= n; i++){
            pref_remaining[i] = pref_remaining[i-1] + k-a[i];
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

            int total_buffered_size = pref_a[r] - pref_a[l-1];

            int lower, higher;
            if(type == 1) {
                lower = r+1;
                higher = ((i == q-1)? n+1 : queries[i+1].first);
            }
            else {
                pii tmp = {r, -1};
                auto it = upper_bound(queries.begin(), queries.end(), tmp);
                assert(it != queries.begin());
                lower = prev(it)->second+1;
                higher = ((it == queries.end())? n+1 : it->first);
                // cout << lower << " " << higher << "\n";
            }

            int index = lower_bound(pref_remaining.begin()+lower, pref_remaining.end(), total_buffered_size + pref_remaining[r]) - pref_remaining.begin();

            if(index >= higher){
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