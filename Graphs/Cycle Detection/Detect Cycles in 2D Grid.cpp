class Solution {
public:
     int m;
     int n;
     int directions[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

     bool isValid(int i, int j, int prev_i, int prev_j, char ch, vector<vector<char>>& grid){
          if(i == prev_i && j == prev_j) return false;
          if(i >= 0 && i < m && j >= 0 && j < n && grid[i][j] == ch) return true;
          return false;
     }

     bool dfs(int i, int j, int prev_i, int prev_j, vector<vector<bool>>& vis, vector<vector<char>>& grid){
          vis[i][j] = true;

          for(auto& dir : directions){
               int new_i = i + dir[0];
               int new_j = j + dir[1];

               if(isValid(new_i, new_j, prev_i, prev_j, grid[i][j], grid) == false) continue;

               if(vis[new_i][new_j]) return true; 

               if(dfs(new_i, new_j, i, j, vis, grid)) return true;
          }
          return false;
     }
     bool containsCycle(vector<vector<char>>& grid) {
          m = grid.size();
          n = grid[0].size();

          vector<vector<bool>> vis(m, vector<bool>(n, false));

          for(int i = 0; i < m; i++){
               for(int j = 0; j < n; j++){
                    if(vis[i][j] == false){
                         if(dfs(i, j, -100, -100, vis, grid)){
                         return true;
                         } 
                    }
               }
          }
          return false;
     }
};
