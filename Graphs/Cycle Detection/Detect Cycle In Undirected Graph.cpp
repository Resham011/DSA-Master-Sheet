//  Remember this graph    1 ------ 2
class Solution {
     public:
     bool dfs(int v, vector<int>& visited, vector<int>& parent, vector<vector<int>>& adj){
          visited[v] = true;
          
          for(auto nbr : adj[v]){
               if(nbr == parent[v]) continue;
               if(visited[nbr] == true) return true;
               parent[nbr] = v;
               if(dfs(nbr, visited, parent, adj)) return true;
          }
          return false;
     }
     
     bool bfs(int v, vector<int>& visited, vector<int>& parent, vector<vector<int>>& adj){
          visited[v] = true;
          
          queue<int> q;
          q.push(v);
          
          while(!q.empty()){
               int n = q.size();
               
               while(n--){
                    int node = q.front();
                    q.pop();
                    
                    for(auto nbr : adj[node]){
                         if(parent[node] == nbr) continue;
                         if(visited[nbr] == true) return true;
                         parent[nbr] = node;
                         visited[nbr] = true;
                         q.push(nbr);
                    }
               }
          }
          return false;
     }
     bool isCycle(vector<vector<int>>& adj) {
          int V = adj.size();
          vector<int> visited(V, false);
          vector<int> parent(V);
          parent[0] = -1;
          
          for(int v = 0; v < adj.size(); v++){
               if(visited[v] == false){
                    if(bfs(v, visited, parent, adj)) return true;
               }
          }
          return false;
     }
};