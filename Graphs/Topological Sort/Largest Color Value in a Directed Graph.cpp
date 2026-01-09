// USING DFS
// Overall Time Complexity: O(V + E × 26) = O(V + E) 
class Solution {
public:
     int maxi;
     bool dfs(int node, vector<bool>& inStack, vector<bool>& vis, unordered_map<int, vector<int>> adj, string& colors, vector<vector<int>>& dp){
          inStack[node] = true;
          vis[node] = true;

          dp[node][colors[node] - 'a'] = 1; // AGR NODE KA KOI BHI NBR NHI HUA TO JO USKA COLOR HAI VO TO UPDATE KARNA HI HAI DP TABLE MEH
          for(auto& nbr : adj[node]){
               if(vis[nbr] && inStack[nbr]) return true; // cycle is there 
               if(vis[nbr] == false){
                    if(dfs(nbr, inStack, vis, adj, colors, dp)) return true;
               }  

               // NOW FILL THE DP TABLE ROW OF CURR NODE USING THE NBR NODE ROW 
               for(int i = 0; i < 26; i++){
                    int currNodeColorVal = colors[node] - 'a';

                    dp[node][i] = max(dp[node][i], dp[nbr][i] + (i == currNodeColorVal));
                    maxi = max(maxi, dp[node][i]);
               } 
          }
          inStack[node] = false;
          return false;
     }
     int largestPathValue(string colors, vector<vector<int>>& edges) {
          maxi = 1;
          int n = colors.size();
          unordered_map<int, vector<int>> adj;
          vector<bool> inStack(n, false);
          vector<bool> vis(n, false);
          vector<vector<int>> dp(n, vector<int>(26, 0));

          for(auto& edge : edges){
               int u = edge[0];
               int v = edge[1];
               adj[u].push_back(v);
          }

          for(int i = 0; i < n; i++){
               if(vis[i] == false){
                    if(dfs(i, inStack, vis, adj, colors, dp)) return -1;
               }
          }
          return maxi;
     }
};


// USING BFS 

class Solution {
public:
     int largestPathValue(string colors, vector<vector<int>>& edges) {
          unordered_map<int, vector<int>> adj;
          int N = colors.size();
          
          vector<int> indegree(N, 0);
          
          for(auto &vec : edges) {
               int u = vec[0];
               int v = vec[1];
               
               adj[u].push_back(v);
               indegree[v]++;
               
          }
          
          queue<int> que;
          vector<vector<int>> t(N, vector<int>(26, 0));
          
          for(int i = 0; i<N; i++) {
               if(indegree[i] == 0) {
                    que.push(i);
                    t[i][colors[i]-'a'] = 1;
               }
          }
          
          int answer = 0;
          
          int countNodes = 0;
          
          while(!que.empty()) {
               
               int u = que.front();
               que.pop();
               
               countNodes++;
               
               answer = max(answer, t[u][colors[u]-'a']);
               
               for(int &v : adj[u]) {
                    
                    for(int i = 0; i<26; i++) {
                         
                         t[v][i] = max(t[v][i], t[u][i] + (colors[v]-'a' == i));
                         
                    }
                    
                    indegree[v]--;
                    if(indegree[v] == 0) {
                         que.push(v);
                    }
               }
               
          }
          
          if(countNodes < N)
               return -1;
          
          return answer;
     }
};