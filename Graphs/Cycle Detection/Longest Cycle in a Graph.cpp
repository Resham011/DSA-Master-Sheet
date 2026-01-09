class Solution {
public:
     int n;
     int result;
     void dfs(int node, vector<int>& edges, vector<bool>& vis, vector<bool>& inRec, vector<int>& dist){
          vis[node] = true;
          inRec[node] = true;

          int nbr = edges[node];

          if(nbr == -1){ // No edge from this node simply just return by marking inRec as false
               inRec[node] = false;
               return;
          }else{
               if(vis[nbr] == true && inRec[nbr] == true){
                    // cycle
                    result = max(result, dist[node] - dist[nbr] + 1);
               }else if(vis[nbr] == false){
                    dist[nbr] = dist[node] + 1;
                    dfs(nbr, edges, vis, inRec, dist);
               }
          }
          inRec[node] = false;
     }

     void bfs(vector<int>& edges){
          queue<int> q;
          vector<int> indegree(n, 0);

          for(int i = 0; i < n; i++){
               if(edges[i] == -1) continue;
               indegree[edges[i]]++;
          }

          for(int i = 0; i < n; i++){
               if(indegree[i] == 0){
                    q.push(i);
               } 
          }

          while(!q.empty()){
               int front = q.front();
               q.pop();

               int nbr = edges[front];
               if(nbr == -1) continue;

               indegree[nbr]--;
               if(indegree[nbr] == 0){
                    q.push(nbr);
               }
          }

          // ab jitni bhi nodes hamare bachi hai jinki indegree > 0 hai vo cycle meh ati hai 
          // ab simple har node jiski indegree > 0 hai use dfs maro or cycle length calculate karo 
          vector<bool> vis(n, false);

          for(int node = 0; node < n; node++){
               if(indegree[node] > 0 && vis[node] == false){
                    int currCycleLen = 0;
                    int currNode = edges[node];

                    while(currNode != -1 && vis[currNode] == false){
                         currCycleLen++;
                         vis[currNode] = true;
                         currNode = edges[currNode];
                    }
                    result = max(result, currCycleLen);
               }
          } 
     }

     int longestCycle(vector<int>& edges) {
          n = edges.size();
          result = -1;
          // vector<bool> vis(n, false);
          // vector<bool> inRec(n, false);
          // vector<int> dist(n, 1);

          // for(int i = 0; i < n; i++){
          //     if(vis[i] == false){
          //         dfs(i, edges, vis, inRec, dist);
          //     }
          // }
          bfs(edges);
          return result;
     }
};