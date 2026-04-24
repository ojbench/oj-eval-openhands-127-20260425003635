
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 1005;
long long dp[MAXN][MAXN];
int a[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    // Initialize dp table
    memset(dp, 0, sizeof(dp));
    
    // Fill DP table for increasing interval lengths
    for (int len = 1; len <= n; len++) {
        for (int l = 0; l + len - 1 < n; l++) {
            int r = l + len - 1;
            
            for (int k = l; k <= r; k++) {
                long long current_value = 0;
                
                // Calculate value when burning card k last in interval [l, r]
                // The neighbors are the closest cards outside the interval
                if (l == 0 && r == n - 1) {
                    // This is the whole array, no outside neighbors
                    current_value = a[k];
                } else if (l == 0) {
                    // No left neighbor outside interval
                    current_value = (long long)a[k] * a[r + 1];
                } else if (r == n - 1) {
                    // No right neighbor outside interval  
                    current_value = (long long)a[l - 1] * a[k];
                } else {
                    // Has both left and right neighbors outside interval
                    current_value = (long long)a[l - 1] * a[k] * a[r + 1];
                }
                
                // Add values from left and right subintervals
                long long left_value = (k > l) ? dp[l][k - 1] : 0;
                long long right_value = (k < r) ? dp[k + 1][r] : 0;
                
                dp[l][r] = max(dp[l][r], left_value + current_value + right_value);
            }
        }
    }
    
    cout << dp[0][n - 1] << endl;
    
    return 0;
}
