// THIS IS GIVING TLE
// #include<bits/stdc++.h>
// using namespace std;

// int dfs(int node, int n, unordered_map<int, vector<int>>& adj){
//      if(node == n) return 1;

//      int ans = 0;
//      for(auto& nbr : adj[node]){
//           ans += dfs(nbr, n, adj);
//      }
//      return ans;
// }

// int main() {

//      int n, m;
//      cin >> n >> m;

//      unordered_map<int, vector<int>> adj;

//      for(int i = 0; i < m; i++){
//           int u, v;
//           cin >> u >> v;

//           adj[u].push_back(v);
//      }
//      cout << dfs(1, n, adj) << endl;
//      return 0;
// }

// NO TLE BUT WRONG ANS IF I DO NOT USE MODULO 
// Time Complexity: O(N + M)


#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

long long dfs(int node, int n, unordered_map<int, vector<int>>& adj, vector<long long>& dp){
     if(node == n) return 1;

     if(dp[node] != -1) return (dp[node] % MOD);

     long long ans = 0;
     for(auto& nbr : adj[node]){
          ans = (ans + dfs(nbr, n, adj, dp)) % MOD;
     }
     return dp[node] = ans % MOD;
}

int main() {

     int n, m;
     cin >> n >> m;

     unordered_map<int, vector<int>> adj;

     for(int i = 0; i < m; i++){
          int u, v;
          cin >> u >> v;

          adj[u].push_back(v);
     }
     vector<long long> dp(n, -1);
     cout << dfs(1, n, adj, dp) << endl;
     return 0;
}

// CLASS BASED SOLUTION 

#include<bits/stdc++.h>
using namespace std;

class Graph {
private:
     int n, m;
     unordered_map<int, vector<int>> adj;
     vector<long long> dp;
     static const int MOD = 1e9 + 7;

     // DFS helper function
     long long dfs(int node) {
          // Base case: reached destination
          if (node == n) return 1;
          
          // Already computed
          if (dp[node] != -1) return dp[node];
          
          long long ans = 0;
          for (int neighbor : adj[node]) {
               ans = (ans + dfs(neighbor)) % MOD;
          }
          
          return dp[node] = ans;
     }

     public:
     // Constructor
     Graph(int nodes, int edges) {
          n = nodes;
          m = edges;
          dp.resize(n + 1, -1);
     }
     
     // Add edge to graph
     void addEdge(int u, int v) {
          adj[u].push_back(v);
     }
     
     // Solve and return number of paths from 1 to n
     long long solve() {
          return dfs(1);
     }
     
     // Print graph (for debugging)
     void printGraph() {
          cout << "Graph Structure:" << endl;
          for (auto& [node, neighbors] : adj) {
               cout << node << " -> ";
               for (int nbr : neighbors) {
                    cout << nbr << " ";
               }
               cout << endl;
          }
     }
     };

     int main() {
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     
     int n, m;
     cin >> n >> m;
     
     // Create graph object
     Graph graph(n, m);
     
     // Read edges and build graph
     for (int i = 0; i < m; i++) {
          int u, v;
          cin >> u >> v;
          graph.addEdge(u, v);
     }
     
     // Solve and print result
     cout << graph.solve() << endl;
     
     return 0;
}