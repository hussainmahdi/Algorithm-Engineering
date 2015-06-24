#include<cstdio>
#include<iostream>
#include<climits>
#include<ctime>
#include<vector>
#define CITY 15
#define INF 10000

using namespace std;

vector<int> costs[CITY];
int cities[CITY];
int nodes[CITY];
int minWeight;
int n;

void swap(int i, int j)
{
    int temp = cities[i];
    cities[i] = cities[j];
    cities[j] = temp;
}

void permute(int k, int n){

    if(k==n-1)
    {
        int sum=0;
        for(int v=0; v<n; v++){
            sum+=costs[cities[v%n]][cities[(v+1)%n]];
            //nodes[v]=cities[v];
        }
        if(minWeight>sum)
        {
            minWeight=sum;
            for(int v=0; v<n; v++){
                nodes[v]=cities[v];
            }
        }
        return;
    }
    for(int i=k; i<n; i++)
    {
        if(cities[i]!=cities[k]) swap(k,i);
        permute(k+1,n);
        if(cities[i]!=cities[k]) swap(k,i);
    }
    return;
}

void input(){
    FILE* fp;
    fp=fopen("E:\\Learn Sth\\L-4,T-2\\Algorithm Sessional\\offline\\tsp11.txt","r");
    int val;
    fscanf(fp,"%d",&n);
    //printf("%d",n);
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
int main(){

    input();
    for(int i=0; i<n; i++) cities[i]=i;

    clock_t tbegin=clock();
    minWeight=INT_MAX;
    permute(1,n);
    cout<<endl;
    for(int i=0; i<n; i++){
        int u=nodes[i%n];
        int v=nodes[(i+1)%n];
        printf("%d<->%d %d\n",u,v,costs[u][v]);
    }
    clock_t tend=clock();
    double elapsed_time=(tend-tbegin)/CLOCKS_PER_SEC;

    cout<<"minWeight- "<<minWeight<<endl;
    cout<<"Elapsed time- "<<elapsed_time<<endl;

    return 0;
}
