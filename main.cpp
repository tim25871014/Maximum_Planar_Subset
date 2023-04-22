#include<iostream>
#include<fstream>
#include<algorithm>
#include<utility>
#include<vector>
using namespace std;

#define maxn 90000
int chord[2*maxn + 10];
vector<pair<int,int>> mps;
vector<int> dp[2*maxn + 10];

void reconstruct(int i, int j) {
    if(i >= j) return;
    int k = chord[j];
    if(i < k && k < j && dp[i][k-1] + 1 + dp[k+1][j-1] > dp[i][j-1]) {
        mps.push_back(make_pair(k, j));
        reconstruct(i, k-1);     
        reconstruct(k+1, j-1);
    }
    else if(k == i) {
        mps.push_back(make_pair(k, j));
        reconstruct(i+1, j-1);
    }
    else reconstruct(i, j-1);
}

signed main(int argc, char* argv[]) {
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);

    // input
    int two_n, n, s, t;
    fin >> two_n;
    n = two_n >> 1;

    for(int i=0;i<n;i++) {
        fin >> s >> t;
        chord[s] = t, chord[t] = s;
    }
    fin >> ws;
    
    for(int i=0;i<2*n;i++) dp[i].resize(2*n);
    for(int i=0;i<2*n;i++) for(int j=0;j<2*n;j++) dp[i][j] = 0;
 
    // process
    for(int j=0; j<2*n; j++) {
        int k = chord[j];
        for(int i=0; i<j; i++) {
            if(i < k && k < j && dp[i][k-1] + 1 + dp[k+1][j-1] > dp[i][j-1]) {
                dp[i][j] = dp[i][k-1] + 1 + dp[k+1][j-1];
            }
            else if(k == i) dp[i][j] = dp[i+1][j-1] + 1;
            else dp[i][j] = dp[i][j-1];
        }
    }
    
    // output
    int res = dp[0][2*n-1];
    fout << res << endl;
    
    reconstruct(0, 2*n-1);
    sort(mps.begin(), mps.end());
    for(auto i: mps) fout << i.first << ' ' << i.second << '\n';
    
    fin.close();
    fout.close();
}



