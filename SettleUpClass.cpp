#include <bits/stdc++.h> 
using namespace std;
class SettleUp
{
    public:
    int n;
    vector<vector<int>> Graph;
    vector<vector<int>> residualgraph;
    unordered_map<string,int> names;
    SettleUp(int n,vector<vector<int>> &Graph)
    {
        this->n=n;
        this->Graph=Graph;    
    }
    void TransactionsDetails()
    {       
        string from,to;
        int amt,i=0;
        int choice;
           
        while(1)
        {
            cout<<"ENTER 1 TO ADD MORE TRANSACTIONS.\n";
            cout<<"ENTER 2 IF NO MORE TRANSACTIONS.\n";
            cin>>choice;
            if(choice==2)
            break;
            cin>>from;
            cin>>to;
            cin>>amt;
            if(names.find(from)==names.end())
            {
                names[from]=i;
                i++;
            }
            if(names.find(to)==names.end())
            {
                names[to]=i;
                i++;
            }
            Graph[names[from]][names[to]]+=amt;
        }
        
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            cout<<Graph[i][j]<<" ";
            cout<<"\n";
        }
    }
    
    int bfs(int source, int sink, vector<int>& parent) 
    {
        fill(parent.begin(), parent.end(), -1);
        int V = residualgraph.size(); //rows in graph.
        parent[source] = -2;
        queue<pair<int, int>> q;
        q.push({source, INT_MAX});

        while (!q.empty()) 
        {
            int u = q.front().first;
            int capacity = q.front().second;
            q.pop();
            for (int av=0; av < V; av++) 
            {
                if (u != av && parent[av] == -1 && residualgraph[u][av] != 0) 
                {
                    parent[av] = u;
                    int min_cap = min(capacity, residualgraph[u][av]);
                    if (av == sink)
                        return min_cap;
                    q.push({av, min_cap});
                }
            }
        }
        return 0;
    }
    void ford_fulkerson(int source, int sink) 
    {
        vector<int> parent(Graph.size(), -1);//save the path from source to sink.   
        int min_cap = 0, max_flow = 0;
        while (min_cap = bfs(source, sink, parent)) 
        {
            max_flow += min_cap;
            int u = sink;
            while (u != source) 
            {
                int v = parent[u];
                residualgraph[v][u] -= min_cap;
                u = v;
            }
        }
        residualgraph[source][sink]=max_flow;
    }
    void simplifyTransactions() //SettleUp 
    {
        residualgraph=Graph; 
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i==j)
                continue;
                else
                {
                    ford_fulkerson(i, j);
                }
            }        
        }
        cout<<"\n";
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            cout<<residualgraph[i][j]<<" ";
            cout<<"\n";
        }
    }

    void display()
    {
        cout<<"TRANSACTIONS BEFORE : \n";
        for(int i=0;i<n;i++)
        {
            cout<<"     Transactions for "<<i<<"\n";
            cout<<"             payTo   Amount\n";
            for(int j=0;j<n;j++)
            {
                if(Graph[i][j]==0)
                continue;

                cout<<"             "<<j<<"        "<<Graph[i][j]<<"\n";
            }
        }
      
        cout<<"\n\nTRANSACTIONS AFTER : \n";
        for(int i=0;i<n;i++)
        {
            for(int k=0;k<n;k++)
            {
                if(residualgraph[i][k]>0)
                {
                    cout<<"     Transactions for "<<i<<"\n";
                    cout<<"             payTo   Amount\n";
                    for(int j=0;j<n;j++)
                    {
                        if(residualgraph[i][j]==0)
                            continue;
                        cout<<"             "<<j<<"        "<<residualgraph[i][j]<<"\n";
                    }
                    break;
                }
            }
        }
    }
};
int main()
{
        int n;
        cout<<"Number of members : ";
        cin>>n;
        vector<vector<int>> Graph(n,vector<int> (n, 0));
        SettleUp obj1(n,Graph);
        obj1.TransactionsDetails();
        obj1.simplifyTransactions();
        obj1.display();
    return 0;   
}