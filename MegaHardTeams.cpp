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
            // cout << pref_remaining[i] << " ";
        }

        int q; cin >> q;
        vector<pii> queries;

        for(int i = 0; i < q; i++){
            int l, r; cin >> l >> r;
            queries.push_back({l, r});
        }
        if(q == 0){
            cout << "YES\n";
            continue;
        }
        vector<pii> queries_by_right(queries.begin(), queries.end());
        sort(queries_by_right.begin(), queries_by_right.end(), [](pii& left, pii& right){
            return  ((left.second == right.second)? left.first < right.first : left.second < right.second);
        });
        sort(queries.begin(), queries.end());
        vector<int> rightmost_connected_segment(q);
        rightmost_connected_segment[q-1] = q-1;
        for(int i = q-2; i >= 0; i--){
            if(queries[i].second >= queries[i+1].first){
                rightmost_connected_segment[i] = rightmost_connected_segment[i+1];
            }
            else{
                rightmost_connected_segment[i] = i;
            }
        }
        bool smooth = true;
        for(int i = 0; i < q; i++){
            // cout << i << endl;
            pii qry = queries[i];
            int l = qry.first, r = qry.second;

            int total_buffered_size = pref_a[r] - pref_a[l-1];

            int lower, higher;
            if(type == 1) {
                lower = r+1;
                higher = ((i == q-1)? n+1 : queries[i+1].first);
            }
            else {
                lower = queries[rightmost_connected_segment[i]].second+1;
                // higher = ((rightmost_connected_segment[i] == q-1)? n+1 : queries[rightmost_connected_segment[i] + 1].first);
                pii tmp = {lower, -1};
                auto it = lower_bound(queries.begin(), queries.end(), tmp);
                higher = ((it == queries.end())? n+1 : it->first);
            }
            assert(lower <= higher);
            // cout << lower << " " << higher << endl; 
            // we must send all buffered packets in [lower, higher)
            // assert(is_sorted(pref_remaining.begin() + lower, pref_remaining.begin() + higher));
            int index = lower_bound(pref_remaining.begin() + lower, pref_remaining.begin() + higher, total_buffered_size + pref_remaining[lower-1])-pref_remaining.begin();
            assert(lower <= index and index <= higher);
            // cout << i << ": " << index << endl;
            if(index == higher){ // can't accomodate
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