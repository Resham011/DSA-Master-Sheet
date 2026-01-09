// 1. Handles Negative Edge Weights ✅
// 2. Detects Negative Cycles ✅

// WHY THIS WORKS for -ve cycle
// - Normal shortest path has at most V-1 edges
// - After V-1 iterations, all shortest paths should be found
// - If we can still improve → someone is in a negative cycle


// ✅ Use Bellman-Ford When:
// Graph has negative edge weights
// Need to detect negative cycles
// Graph is small (V × E is acceptable)
// Simplicity is preferred over speed

// ❌ Don't Use Bellman-Ford When:
// All edges are positive (use Dijkstra instead)
// Graph is very large (too slow)
// Need multiple source shortest paths (use Floyd-Warshall)

// ┌─────────────────────────────────────────────────────────────┐
// │                    BELLMAN-FORD ALGORITHM                   │
// └─────────────────────────────────────────────────────────────┘

// STEP 1: INITIALIZATION
// ┌──────────────────────────────────────┐
// │ dist[source] = 0                     │
// │ dist[all others] = ∞                 │
// └──────────────────────────────────────┘
//                   ↓

// STEP 2: RELAX ALL EDGES (V-1 TIMES) (WHY V - 1?) beacuse tum v - 1 ke bad relax karoge to koi bhi relaxation nhi ayega age hua to -ve cycle
// ┌──────────────────────────────────────┐
// │ FOR i = 1 to V-1:                    │
// │   FOR each edge (u, v, weight):      │
// │     IF dist[u] + weight < dist[v]:   │
// │       dist[v] = dist[u] + weight     │
// └──────────────────────────────────────┘
//                   ↓

// STEP 3: CHECK FOR NEGATIVE CYCLES [agr (v - 1) relaxation ke bad bhi relaxation hua to bas -ve cycle present hai ]
// ┌──────────────────────────────────────┐
// │ FOR each edge (u, v, weight):        │
// │   IF dist[u] + weight < dist[v]:     │
// │     RETURN "Negative cycle exists!"  │
// └──────────────────────────────────────┘
//                   ↓

// STEP 4: RETURN RESULT
// ┌──────────────────────────────────────┐
// │ RETURN dist[] array                  │
// │ (shortest distances from source)     │
// └──────────────────────────────────────┘

// Time Complexity: O(V × E)
// SPACE COMPLEXITY: O(V)

class Solution {
     public:
     vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
          vector<int> dist(V, 1e8);
          dist[src] = 0;
          
          for(int i = 1; i <= V - 1; i++){
               for(auto& edge : edges){
                    int u = edge[0];
                    int v = edge[1];
                    int edgeWt = edge[2];
                    if(dist[u] != 1e8 && (dist[u] + edgeWt < dist[v])){
                         dist[v] = dist[u] + edgeWt;
                    }
               }
          }
          bool negCycle = false;
          for(auto& edge : edges){
               int u = edge[0];
               int v = edge[1];
               int edgeWt = edge[2];
               if(dist[u] != 1e8 && (dist[u] + edgeWt < dist[v])){
                    return {-1};
               }
          }
          return dist;
     }
};