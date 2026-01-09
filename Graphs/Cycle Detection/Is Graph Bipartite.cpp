// USING DFS
class Solution {
public:
     bool dfs(int node, vector<int>& color, unordered_map<int, vector<int>> adj){
          int nodeColor = color[node];

          for(auto& nbr : adj[node]){
               if(color[nbr] == color[node]) return false;
               if(color[nbr] == -1){
                    color[nbr] = nodeColor == 0 ? 1 : 0;
                    if(!dfs(nbr, color, adj)) return false;
               }
          }
          return true;
     }
     bool isBipartite(vector<vector<int>>& graph) {
          int n = graph.size();
          unordered_map<int, vector<int>> adj;
          for(int u = 0; u < n; u++){
               for(auto& v : graph[u]){
                    adj[u].push_back(v);
               }
          }
          vector<int> color(n, -1);
          for(int i = 0; i < graph.size(); i++){
               if(color[i] == -1){
                    color[i] = 1;
                    if(!dfs(i, color, adj)) return false;
               }
          }
          return true;
     }
};

// USING BFS
class Solution {
public:
     bool bfs(int currNode, int currColor, vector<int>& color, vector<vector<int>>& graph){
          queue<int> q;

          color[currNode] = currColor;
          q.push(currNode);

          while(!q.empty()){
               int node = q.front();
               q.pop();

               for(auto& nbr : graph[node]){
                    if(color[nbr] != -1 && color[nbr] == color[node]) return false;
                    if(color[nbr] == -1){
                         int nbrColor = (color[node] == 1) ? 0 : 1;
                         color[nbr] = nbrColor;
                         q.push(nbr);
                    }
               }
          }
          return true;
     }
     bool isBipartite(vector<vector<int>>& graph) {
          int n = graph.size();
          vector<int> color(n, -1);

          for(int node = 0; node < n; node++){
               if(color[node] == -1){
                    if(bfs(node, 1, color, graph) == false) return false;
               }            
          }
          return true;
     }
};