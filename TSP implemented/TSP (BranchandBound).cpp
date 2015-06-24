#include<cstdio>
#include<iostream>
#include<climits>
#include<ctime>
#include<vector>
#include<queue>
#define CITY 15
#define INF 10000

using namespace std;

vector<int> costs[CITY];
int n;
int lowestBound=INF;

struct Node{
    int lowerBound;
    int reducedMatrix[CITY][CITY];
    vector<int> citiesVisited;
    int visited[CITY];
    Node(){
        for(int i=0; i<n; i++) visited[i]=0;
    }
    bool operator<(const Node &p)const{
        return lowerBound > p.lowerBound;
    }
};

void input(){
    FILE* fp;
    fp=fopen("E:\\Learn Sth\\L-4,T-2\\Algorithm Sessional\\offline\\tsp5.txt","r");
    int val;
    fscanf(fp,"%d",&n);
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            fscanf(fp,"%d",&val);
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

Node findLowerBound(Node parent){

    Node child=parent;
    int minm=INF;
    for(int r=0; r<n; r++){
        minm=INF;
        for(int c=0; c<n; c++){
            minm=min(minm,child.reducedMatrix[r][c]);
        }
        for(int c=0; c<n; c++){

            if(child.reducedMatrix[r][c]==INF)
                    continue;
            else
                    child.reducedMatrix[r][c] -= minm;
        }
        child.lowerBound += minm;
    }

    for(int r=0; r<n; r++){
        minm=INF;
        for(int c=0; c<n; c++){
            minm=min(minm,child.reducedMatrix[c][r]);
        }
        for(int c=0; c<n; c++){

            if(child.reducedMatrix[c][r]==INF)
                    continue;
            else
                    child.reducedMatrix[c][r] -= minm;
        }
        child.lowerBound += minm;
    }

    return child;
}
Node bnbTSP(int st){


    Node city0;
    city0.lowerBound=0;
    //int temp[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            city0.reducedMatrix[i][j]=costs[i][j];
        }
    }
    city0.visited[st]=1;
    city0.citiesVisited.push_back(st);
    city0=findLowerBound(city0);

    priority_queue<Node> pq;
    Node parent,child;
//    if(city0.lowerBound<=lowestBound) {
//        lowestBound=city0.lowerBound;
//        pq.push(city0);
//    }
    pq.push(city0);
    while(!pq.empty())
    {
        parent=pq.top(); pq.pop();
        if(parent.citiesVisited.size()==n) return parent;

        int flag=0;
        for(int i=0; i<n; i++)
        {
            if(parent.visited[i]==0)
            {
                flag=1;
                child=parent;
                child.citiesVisited.push_back(i);
                child.visited[i]=1;
                int r=parent.citiesVisited[parent.citiesVisited.size()-1];
                child.lowerBound+=parent.reducedMatrix[r][i];
                for(int c=0; c<n; c++){
                    child.reducedMatrix[r][c]=INF;
                }
                for(int r=0; r<n; r++){
                    child.reducedMatrix[r][i]=INF;
                }
                //child.reducedMatrix[i][1]=INF;
                child=findLowerBound(child);
//                if(child.lowerBound<=lowestBound){
//                    lowestBound=child.lowerBound;
//                    pq.push(child);
//                }
                pq.push(child);

            }
        }
        if(flag==0) return parent;
    }
}
int main(){

    input();

    clock_t tbegin=clock();
    //
    Node ans=bnbTSP(0);
    int minWeight=0;
    cout<<endl;
    for(int i=0; i<ans.citiesVisited.size(); i++){
        int u=ans.citiesVisited[i%n];
        int v=ans.citiesVisited[(i+1)%n];
        printf("%d<->%d %d\n",u,v,costs[u][v]);
        minWeight += costs[u][v];
    }
    clock_t tend=clock();
    double elapsed_time=(tend-tbegin)/CLOCKS_PER_SEC;

    //cout<<"minCost- "<<minCost<<endl;
    cout<<"minWeight- "<<minWeight<<endl;
    cout<<"Elapsed time- "<<elapsed_time<<endl;

    return 0;
}
