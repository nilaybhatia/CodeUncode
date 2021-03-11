# PROBLEM LINK:

[Practice](https://www.codechef.com/problems/CUTEAMS)
[Contest](https://www.codechef.com/UNCO2021/problems/CU4TEAMS)


*Author:* [Nilay](https://www.codechef.com/users/author_nick)

*Editorialist:* [Nilay](https://www.codechef.com/users/editorialist_nick)

# DIFFICULTY:
EASY-MEDIUM

# PREREQUISITES:
Prefix-sums, Binary Search, Greedy

# PROBLEM:
Find if it is possible to accomodate a range-sum of every interval in the gaps between intervals of the form $[l, r]$.

# EXPLANATION:
#### Subtask 1:
One can actually simulate the process by finding range sum for each interval and trying to distribute it as soon as the interval ends. Utilise the maximum available capacity for each index in order to be done with the buffered packets the soonest. This subtask allows you to be careless about overflow issues and also allows time complexity of $\mathcal{O}(n^2)$, in the case you forget to break after encountering the very next interval and iterating till the end instead.

##### Subtask 2:
Approach same as Subtask 1, but be careful about overflow and ensure linear time complexity by breaking early.

#### Subtask 3:
First do the following pre-computations:
1. Compute the prefix sum array for the array $A$, the array having the packet sizes.
2. Compute the prefix sum array for the unutilised capacities.
3. For each interval, find it's righmost connected point.

For each interval, do 3 things
1. Find the range sum of that interval using prefix-sums.
2. Find the end points of the *valid range* that can accomodate this sum. This *valid range* should begin after the rightmost connected point of this interval and end before the left point of the next disconnected interval.
3. Find the smallest index upto which we can accomodate the buffered sizes by maxing out the capacity for every index. Use binary search to speed this up like so:-

    For example if the unitilised capacities starting from the 1st index of *valid range* are $[2, 4, 3, 5]$, they would have a prefix-sum of $[2, 6, 9, 14]$. Now if we want to accomodate total buffered size of $10$, we need to find the the first element that is greater than or equal to $10$. Here it is $14$. We can send the total size of $10$ as $[2, 4, 3, 1]$. Except for the last index, all capacities are maxed-out. We could use binary search only because the prefix sum array is sorted.

    If this index does not lie in the *valid range* for any interval, then answer is "NO", else the answer is "YES".

# SOLUTIONS:

[details="Code passing 1st 2 subtasks"]
```cpp
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
        int n, k, feature; cin >> n >> k >> feature;

        vector<int> a(n+1);
        for(int i = 1; i <= n; i++){
            cin >> a[i];
        }


        int q; cin >> q;
        vector<pii> queries;

        int rightmost = 1;
        for(int i = 1; i <= q; i++){
            int l, r; cin >> l >> r;
            queries.push_back({l, r});
            rightmost = max(rightmost, r);
        }

        sort(queries.begin(), queries.end());
        bool smooth = true;
        for(int i = 0; i < q; i++){
            pii qry = queries[i];
            int l = qry.first, r = qry.second;
            
            int total_buffered_size = 0;
            for(int j = l; j <= r; j++){
                total_buffered_size += a[j];
            }
            
            int lower, higher;
            if(feature == 1) {
                lower = r+1;
                higher = ((i == q-1)? n+1 : queries[i+1].first);
            }
            else {
                assert(false);
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
```
[/details]

[details="Code passing all subtasks"]
```cpp
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
        int n, k, feature; cin >> n >> k >> feature;

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

        for(int i = 0; i < q; i++){
            int l, r; cin >> l >> r;
            queries.push_back({l, r});
        }
        // no loss of connection
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
            pii qry = queries[i];
            int l = qry.first, r = qry.second;

            int total_buffered_size = pref_a[r] - pref_a[l-1];

            int lower, higher;
            if(feature == 1) {
                lower = r+1;
                higher = ((i == q-1)? n+1 : queries[i+1].first);
            }
            else {
                lower = queries[rightmost_connected_segment[i]].second+1;
                pii tmp = {lower, -1};
                auto it = lower_bound(queries.begin(), queries.end(), tmp);
                higher = ((it == queries.end())? n+1 : it->first);
            }

            // we must send all buffered packets in [lower, higher)
            int index = lower_bound(pref_remaining.begin() + lower, pref_remaining.begin() + higher, total_buffered_size + pref_remaining[lower-1])-pref_remaining.begin();
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
```
[/details]

We hope you enjoyed the problems and if you have any questions, do ask us right away on this thread.