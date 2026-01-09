// ║  IDEA: Try all vertices as intermediates              ║
// ║        for all pairs of vertices in edge              ║
// ║                                                       ║
// ║  FORMULA: dist[i][j] = min(dist[i][j],                ║
// ║                            dist[i][k] + dist[k][j])   ║ 
// IT HANDLES NEGATIVE EDGES 
// HELPS IN FINDING -VE CYCLE (if 0---->0 / 1------>1 shortest path value is less than 0)
// Check diagonal: if dist[i][i] < 0, cycle exists!


// T.C -> O(n^3)




class Solution {
     public:
     void FloydWarshall(vector<vector<int>>& mat) {
          int n = mat.size();
          for(int i = 0; i< n; i++) {
               for(int j = 0; j<n; j++) {
                    
                    if(mat[i][j] == -1)
                         mat[i][j] = 100000;
                    
               }
          }
          for(int u = 0; u < n; u++){
               for(int v = 0; v < mat.size(); v++){
                    for(int k = 0; k < mat.size(); k++){
                         mat[u][v] = min(mat[u][v], mat[u][k] + mat[k][v]);
                    }
               }
          }
          for(int i = 0; i<n; i++) {
               for(int j = 0; j<n; j++) {
                    
                    if(mat[i][j] >= 100000)
                         mat[i][j] = -1;
                    
               }
          }
     }
};