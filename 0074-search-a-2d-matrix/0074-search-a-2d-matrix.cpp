class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {

        int m = matrix.size();
        int n = matrix[0].size();
        
        // for(int i = 0; i < m; i++ ){
        //     for(int j = 0; j < n; j++ ){
        //         if(matrix[i][j] == target){
        //             return 1;
        //         }
        //     }
        // }
        // return 0;
    int start = 0;
    int end = (n*m)-1;
    int mid = start + (end-start)/2;

    while(start <= end){
        if(matrix[mid/n][mid%n] == target){
            return 1;
        }
        else if(matrix[mid/n][mid%n] > target){ 
            end = mid - 1;
        }
        else{
            start = mid + 1;
        }
mid = start + (end-start)/2;
    }

return 0;
    }
};