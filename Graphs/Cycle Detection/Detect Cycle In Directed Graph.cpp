//  ALWAYS REMEMBER THIS GRAPH       1 -----> 2 <------- 3

class Solution {
     public:
     bool dfs(int node, vector<bool>& inRecurssion, vector<bool>& visited, vector<vector<int>>& adj){
          visited[node] = true;
          inRecurssion[node] = true;
          
          for(auto nbr : adj[node]){
               if(visited[nbr] == true && inRecurssion[nbr] == true) return true;
               if(dfs(nbr, inRecurssion, visited, adj)) return true;
          }
          inRecurssion[node] = false;
          return false;
     }
     bool bfs(vector<vector<int>> adj){
          int V = adj.size();
          int count = 0;
          vector<int> indegree(V, 0);
          queue<int> q;
          
          for(int node = 0; node < V; node++){
               for(auto& nbr : adj[node]){
                    indegree[nbr]++;
               }
          }
          for(int node = 0; node < V; node++){
               if(indegree[node] == 0) q.push(node);
          }
          
          while(!q.empty()){
               int n = q.size();
               while(n--){
                    int node = q.front();
                    count++;
                    q.pop();
                    
                    for(auto& nbr : adj[node]){
                         indegree[nbr]--;
                         if(indegree[nbr] == 0) q.push(nbr);
                    } 
               }
          }
          return count != V;
     }
     bool isCyclic(int V, vector<vector<int>> adj) {
          vector<bool> inRecurssion(V, false);
          vector<bool> visited(V, false);
          
          // for(int i = 0; i < V; i++){
          //     if(visited[i] == true) continue;
          //     if(dfs(i, inRecurssion, visited, adj)) return true;
          // }
          // return false;
          
          return bfs(adj);
     }
};