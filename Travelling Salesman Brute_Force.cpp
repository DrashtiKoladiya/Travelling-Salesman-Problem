#include <bits/stdc++.h>

using namespace std;

void TSP(vector<vector<double>> graph, int s)
{
    int V = graph.size();
    vector<int> final_path;
    vector<int> vertex;
    for (int i = 0; i < V; i++)
        if (i != s)
            vertex.push_back(i);
    double min_path = INT_MAX;

    do
    {
        double current_pathweight = 0;
        int k = s;
        for (int i = 0; i < vertex.size(); i++)
        {
            current_pathweight += graph[k][vertex[i]];
            k = vertex[i];
        }
        current_pathweight += graph[k][s];
        min_path = min(min_path, current_pathweight);

        if (min_path == current_pathweight)
        {
            final_path.clear();
            final_path = vertex;
        }
    } while (next_permutation(vertex.begin(), vertex.end()));

    cout << min_path << endl;
    cout << s << " ";
    for (int i = 0; i < vertex.size(); i++)
        cout << vertex[i] << " ";
    cout << s << " ";
    cout << endl;
}

int main()
{
    cout << "Enter number of vertices:";
    int n;
    cin >> n;
    vector<vector<double>> adj(n, vector<double>(n, 0));
    vector<vector<double>> cord(n, vector<double>(2, 0));

    for (int i = 0; i < n; i++)
    {
        cout << "Enter x coordinate of " << i << "th city: ";
        cin >> cord[i][0];
        cout << "Enter y coordinate of " << i << "th city: ";
        cin >> cord[i][1];
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            adj[i][j] = sqrt((cord[i][0] - cord[j][0]) * (cord[i][0] - cord[j][0]) + (cord[i][1] - cord[j][1]) * (cord[i][1] - cord[j][1]));
        }
    }

    cout << "Enter index of starting city:";
    int s;
    cin >> s;
    TSP(adj, s);
    return 0;
}