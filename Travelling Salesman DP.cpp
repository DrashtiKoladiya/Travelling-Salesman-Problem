#include <bits/stdc++.h>
using namespace std;
#define VVD vector<vector<double>>
#define VVL vector<vector<int>>

vector<int> minPath;
double minCost;
int noOfCities, startCity;

double TSP_DP(VVD &adj, VVD &dp, int All_Visited, int curr_mask, int src, VVL &path)
{
    // If all the cities are visited once, return the path value from the last city to the starting city
    if (curr_mask == All_Visited)
    {
        return adj[src][startCity];
    }

    // if the sub mask ending with the src is already counted, return the value
    if (dp[curr_mask][src] != -1)
    {
        return dp[curr_mask][src];
    }

    double ans = DBL_MAX;
    int path_val = -1;
    // finding the best possible path with minimum cost
    for (int i = 0; i < noOfCities; i++)
    {
        if ((curr_mask & (1 << i)) == 0)
        {
            double temp = adj[src][i] + TSP_DP(adj, dp, All_Visited, curr_mask | (1 << i), i, path);
            if (ans > temp)
            {
                ans = temp;
                path_val = i;
            }
        }
    }

    path[curr_mask][src] = path_val;
    return dp[curr_mask][src] = ans;
}

void TSP_DP_Path(int All_Visited, int startCity, int curr_mask, VVL &path)
{
    int curr_city = startCity;

    // retriving the final path
    minPath.push_back(startCity);
    while (curr_mask != All_Visited)
    {
        minPath.push_back(path[curr_mask][curr_city]);
        curr_city = path[curr_mask][curr_city];
        curr_mask |= (1 << curr_city);
    }
    minPath.push_back(startCity);

    // printing the final path
    for (int i = 0; i <= noOfCities; i++)
    {
        cout << minPath[i] << " ";
    }
    cout << "\n";
}

int main()
{
    cout << "Please enter the number of cities: ";
    cin >> noOfCities;

    cout << "Please enter the co-ordinates of each city:\n";
    VVD cordi(noOfCities, vector<double>(2, 0));

    // Input for the co-ordinates of each of the city
    for (int i = 0; i < noOfCities; i++)
    {
        cout << "Enter the co-ordinate of the " << i << "th city: ";
        cin >> cordi[i][0] >> cordi[i][1];
    }

    // generating the adjacency matrix
    VVD adj(noOfCities, vector<double>(noOfCities, 0));
    for (int i = 0; i < noOfCities; i++)
    {
        for (int j = 0; j < noOfCities; j++)
        {
            adj[i][j] = sqrt((cordi[i][0] - cordi[j][0]) * (cordi[i][0] - cordi[j][0]) + (cordi[i][1] - cordi[j][1]) * (cordi[i][1] - cordi[j][1]));
        }
    }

    // Input for the starting city
    cout << "Please enter the starting city: ";
    cin >> startCity;

    // Initializing the nessesary varibles and containers
    VVD dp((1 << noOfCities), vector<double>(noOfCities, -1));
    VVL path((1 << noOfCities), vector<int>(noOfCities, -1));

    minCost = TSP_DP(adj, dp, (1 << noOfCities) - 1, (1 << startCity), startCity, path);

    // printing the minCost and minPath
    cout << minCost << "\n";
    TSP_DP_Path((1 << noOfCities) - 1, startCity, (1 << startCity), path);
}