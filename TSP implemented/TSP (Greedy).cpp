#include<cstdio>
#include<iostream>
#include<climits>
#include<ctime>
#include<vector>
#include<queue>
#define CITY 20

using namespace std;

struct Edge{
    int src, dest;
    int cst;
    bool operator<(const Edge &p) const{
        return cst>p.cst;
    }
};
vector<int> edges[CITY+1];
vector<int> costs[CITY+1];
vector<int> tree[CITY+1];

int visited[CITY+1];
int parent[CITY+1];
int dist[CITY+1];
int cities[CITY+1];
int minCost,cnt,n;
int minWeight;

void preorderTraversal(int u){
    for(int i=0; i<tree[u].size(); i++){
        cities[cnt++]=tree[u][i];
        preorderTraversal(tree[u][i]);
    }
}
void mst_prims(int n){

    priority_queue<Edge> pq;
    Edge ed,u,v;
    int ne=0;
    for(int i=0; i<n; i++) visited[i]=0;
    for(int i=0; i<n; i++) dist[i]=INT_MAX;
    minCost=0;
    dist[0]=0;
    ed.src=-1; ed.dest=0; ed.cst=0;
    pq.push(ed);

    while(!pq.empty()){
        u=pq.top(); pq.pop();

        if(visited[u.src] && visited[u.dest]) continue;
        visited[u.dest]=1;
        parent[u.dest]=u.src;
        //printf("u.src = %d u.dest = %d u.cst = %d\n",u.src,u.dest,u.cst);
        ne++;
        if(ne==n) break;

        for(int j=0; j<edges[u.dest].size(); j++){

            v.dest=edges[u.dest][j];
            v.cst=costs[u.dest][j];
            if(visited[v.dest]==0)
            {
                  if(dist[v.dest] > v.cst)
                  {
                      v.src=u.dest;
                      dist[v.dest]=v.cst;
                      pq.push(v);
                  }
            }
        }
    }
    for(int i=0; i<n; i++) minCost+=dist[i];
    return;
}

void input(){
    FILE* fp;
    fp=fopen("E:\\Learn Sth\\L-4,T-2\\Algorithm Sessional\\offline\\tsp8.txt","r");
    int val;
    fscanf(fp,"%d",&n);
    //printf("%d",n);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            fscanf(fp,"%d",&val);
            edges[i].push_back(j);
            costs[i].push_back(val);
        }
    }
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            printf("%3d ",costs[i][j]);
        }
        cout<<endl;
    }
}
int main(){

    input();
    clock_t tbegin=clock();
    //
    mst_prims(n);
    for(int i=1; i<n; i++){
        tree[parent[i]].push_back(i);
    }
    cnt=0;
    cities[cnt++]=0;
    preorderTraversal(0);
    printf("\nCnt - %d\n",cnt);
    minWeight=0;
    for(int i=0;i<cnt; i++){
        int u=cities[i%cnt];
        int v=cities[(i+1)%cnt];
        printf("%d<->%d %d\n",u,v,costs[u][v]);
        minWeight+=costs[u][v];
    }

    clock_t tend=clock();
    double elapsed_time=(tend-tbegin)/CLOCKS_PER_SEC;

    //cout<<"minCost- "<<minCost<<endl;
    cout<<"minWeight- "<<minWeight<<endl;
    cout<<"Elapsed time- "<<elapsed_time<<endl;

    return 0;
}
