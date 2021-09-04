class Solution {
    List<HashSet<Integer>> mylist;
    int[] ans,count;
    int n;
    public int[] sumOfDistancesInTree(int n, int[][] edges) {
        this.n = n;
        this.count = new int[n];
        Arrays.fill(count,1);
        this.ans = new int[n];
        mylist = new ArrayList<>();
        
        for(int i = 0;i<n;i++){
            mylist.add(new HashSet<Integer>());
        }
        
        for(int[] edge : edges){
            mylist.get(edge[0]).add(edge[1]);
            mylist.get(edge[1]).add(edge[0]);
        }
        
        dfs(0,-1);
        dfs2(0,-1);
        return ans;
    }
    
    public void dfs(int source,int parent){
        for(int child : mylist.get(source)){
            if(child != parent){
                dfs(child,source);
                count[source] += count[child];
                ans[source] += ans[child] + count[child];
            }
        }
    }
    
    public void dfs2(int node,int parent){
        for(int child : mylist.get(node)){
            if (child != parent) {
                ans[child] = ans[node] - count[child] + n - count[child];
                dfs2(child, node);
            }
        }
    }
    
    
}
