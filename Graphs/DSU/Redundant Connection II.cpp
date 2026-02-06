// O(n ^2) solution Brute force
// 1. At first i though only checking the components will be enough that was wrong 
// 2. than though that only checking indegree and one root check it was also wrong 
// 3. at last we came to know that we have to check all the three conditions components, Indegree, Root track

// O(n) Solution Using DSU

// There is only 3 case 
// 1. 2 indegree
// 2. a cycle
// 3. cycle + 2 indegree

class Solution {
public:
     int find(int node, vector<int>& parent){
          if(parent[node] == node) return node;
          return parent[node] = find(parent[node], parent);
     }

     void unite(int u, int v, vector<int>& rank, vector<int>& parent){
          int u_parent = find(u, parent);
          int v_parent = find(v, parent);

          if(u_parent == v_parent) return;

          if(rank[u_parent] > rank[v_parent]){
               parent[v_parent] = u_parent;
          } else if(rank[u_parent] < rank[v_parent]){
               parent[u_parent] = v_parent;
          } else {
               parent[v_parent] = u_parent;
               rank[u_parent]++;
          }
     }

     set<vector<int>> edgesCausing2Indegree(vector<vector<int>>& edges){
          int n = edges.size();
          set<vector<int>> result; // { {u, v}, {u, v} }
          vector<vector<int>> parent(n + 1); 
          vector<int> indegree(n + 1, 0);

          for(auto& edge : edges){
               int u = edge[0];
               int v = edge[1];

               indegree[v]++;
               parent[v].push_back(u);
               if(indegree[v] == 2){
                    result.insert({parent[v][0], v});    
                    result.insert({parent[v][1], v});            
                    return result;
               }
          }
          return result;
     }
     
     vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
          int n = edges.size();
          
          // sabse phle yeh track karo ki konsi 2 edges 2 indgree create kar rhi hai 
          set<vector<int>> suspect = edgesCausing2Indegree(edges);

          vector<int> parent(n + 1);
          vector<int> rank(n + 1, 0);

          // initializig the parent vector
          for(int i = 1; i <= n; i++){
               parent[i] = i;
          }
          
          vector<vector<int>> suspectedEdges;
          // with the help of DSU connect all the graph and skip the suspected edges 
          // if indegree 2 nhi hai to automatically vo edge mil jayegi jo cycle create kar rhi hai [make sure to traverse in edges from 0----> n - 1]
          for(int i = 0; i < n; i++){
               if(suspect.find(edges[i]) != suspect.end()){
                    suspectedEdges.push_back({edges[i]});
                    continue; // suspected edge
               }             

               int u = edges[i][0];
               int v = edges[i][1];

               int parent_u = find(u, parent);
               int parent_v = find(v, parent);

               if(parent_u == parent_v) return {u, v};

               unite(u, v, rank, parent);
          }
          
          // ab last meh in do edges ko one by one add karke dekhenge and the edge that is safe will get added in graph and other will be return as ans 
          for(auto edge : suspectedEdges){

               int u = edge[0];
               int v = edge[1];
               int parent_u = find(u, parent);
               int parent_v = find(v, parent);

               if(parent_u == parent_v) return edge;
               else unite(u, v, rank, parent);
          }
          return {};
     }
};