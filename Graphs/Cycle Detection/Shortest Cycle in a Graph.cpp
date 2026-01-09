// SINCE BFS IS BEST FOR FINDING SHORTEST PATH THAT'S WHY BFS CAME TO MY MIND
// Since we don’t know which node belongs to the shortest cycle,
// every node must be considered as a potential “anchor” of a shortest cycle.
class Solution {
public:
     int result;
     int n;
     void bfs(int node, unordered_map<int, vector<int>>& adj){
          vector<bool> vis(n, false);
          vector<int> parent(n, -1);
          vector<int> dist(n, 0);
          queue<int> q;

          q.push(node);
          vis[node] = true;
          int level = 0;
          while(!q.empty()){
               int size = q.size();

               while(size--){
                    int node = q.front();
                    q.pop();

                    for(auto& nbr : adj[node]){
                         if(vis[nbr] == true && parent[node] != nbr){ //cycle found
                         result = min(result, dist[nbr] + dist[node] + 1);
                         }else if(vis[nbr] == false){
                         parent[nbr] = node;
                         vis[nbr] = true;
                         q.push(nbr);
                         dist[nbr] = level + 1;
                         }
                    }
               }
               level++;
          }
          return;
     }
     int findShortestCycle(int N, vector<vector<int>>& edges){
          result = INT_MAX;
          n = N;

          unordered_map<int, vector<int>> adj;
          for(auto& edge : edges){
               adj[edge[0]].push_back(edge[1]);
               adj[edge[1]].push_back(edge[0]);
          }
          for(int i = 0; i < n; i++){
               bfs(i, adj);
          }
          return result == INT_MAX ? -1 : result;
    }
};


// USING DFS

// agr meh ak hi global vis array lelu or jase normal dfs ka use karte hai ham cycle detect karne meh usi ka same yaha use karu to vo galt hai kyuki isme bohot sare cycles ham explore hi nhi kar payenge because once a node is visited that that's it we cannot explore it more okay.

// fir mne visited ko as a backtracting ki tarah use kiya to explore each possibilty and than got tle because t.c hi high 

// that by applying pruning concept to disable unnecessary calling of dfs 
// dis[src] + 1 < dis[it] this only works for shortest path 

// BUT IF WE NEED TO FIND LONGEST THAN WE HAVE TO USE PREVIOUS BACKTRATING CONCEPT EXPLORE EACH POSSIBILITY 

// dist[node] - dist[nbr] + 1 ab dekho isko correct rakhne ke liye kuch karna hoga kyuki dist[nbr]= INT_MAX  ho sakta hai let say we have cycle starting from 0 and dist[0] is initialized to INT_MAX iske liye mne prev_dist liya 

 
class Solution {
public:
     int result;
     int n;

     void dfs(int node, int prev_dist, vector<bool>& vis, int parent, vector<int>& dist, unordered_map<int, vector<int>>& adj){
          vis[node] = true;
          dist[node] = prev_dist + 1;

          for(auto& nbr : adj[node]){
               if(parent == nbr) continue;
               if(vis[nbr] == true){   // cycle
                    result = min(result, dist[node] - dist[nbr] + 1);
               }else if((vis[nbr] == false) && (dist[node] + 1 < dist[nbr])){
                    dfs(nbr, dist[node], vis, node, dist, adj);
               }
          }
          vis[node] = false; // backtarck we need to explore each case 
     }
     int findShortestCycle(int N, vector<vector<int>>& edges){
          result = INT_MAX;
          n = N;

          unordered_map<int, vector<int>> adj;
          for(auto& edge : edges){
               adj[edge[0]].push_back(edge[1]);
               adj[edge[1]].push_back(edge[0]);
          }

          vector<bool> vis(n, false);
          vector<int> dist(n, INT_MAX);

          for(int i = 0; i < n; i++){
               if(dist[i] == INT_MAX){
                    dfs(i, -1, vis, -1, dist, adj);
               }
          }
          return result == INT_MAX ? -1 : result;
     }
};

