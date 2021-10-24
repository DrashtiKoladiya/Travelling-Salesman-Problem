// Travelling Salesman Problem _ Optimization by Greedy Approach
// Time Complexity : O( N^2 * log(n) )
// Auxillary Space : O(N)

#include <bits/stdc++.h>
using namespace std;

// Function to find the minimum
// cost path for all the paths

void Minimum_Travelling_Cost(vector<vector<double>> edges, int start)
{
    double sum = 0;
    int counter = 0;
    double j = 0, i = 0;
    double min = INT_MAX;
    map<int, double> Check_of_Visited_Route;

    // Starting from the first city
    // from which salesman starts its journey

    Check_of_Visited_Route[start - 1] = 1;
    int route[edges.size()];

    while (i < edges.size() && j < edges[i].size())
    {

        // Corner of the Matrix
        if (counter >= edges[i].size() - 1)
        {
            break;
        }

        // If this path is unvisited then
        // and if the cost is less then
        // update the cost

        if (j != i && (Check_of_Visited_Route[j] == 0))
        {
            if (edges[i][j] < min)
            {
                min = edges[i][j];
                route[counter] = j + 1;
            }
        }
        j++;

        // Check all paths from the
        // ith indexed city

        if (j == edges[i].size())
        {
            sum += min;
            min = INT_MAX;
            Check_of_Visited_Route[route[counter] - 1] = 1;

            j = 0;
            i = route[counter] - 1;
            counter++;
        }
    }

    i = route[counter - 1] - 1;

    for (j = 0; j < edges.size(); j++)
    {

        if ((i != j) && edges[i][j] < min)
        {
            min = edges[i][j];
            route[counter] = j + 1;
        }
    }

    sum += min;

    cout << endl;
    cout << ("Minimum Cost is : ") << endl;
    cout << (sum) << endl
         << endl;

    cout << "The Route that should be followed by the Salesman for the Minimum Cost from the Starting city : " << start << "th is " << endl;

    cout << start << " "; // Salesman Starting Point
    for (int i = 0; i < edges.size() - 1; i++)
    {
        cout << route[i] - 1 << " ";
    }
    cout << start << " "; // Salesman returning to the Point where he started his journey
}

int main()
{
    cout << "Enter the number of Cities :" << endl;
    int no_of_cities, temp, start;
    cin >> no_of_cities;

    // Input Matrix
    vector<vector<double>> edges(no_of_cities, vector<double>(no_of_cities, 0));
    vector<vector<double>> points(no_of_cities, vector<double>(2, 0));

    for (int i = 0; i < no_of_cities; i++)
    {
        cout << "Enter x coordinate of " << i << "th city: " << endl;
        cin >> points[i][0];
        cout << "Enter y coordinate of " << i << "th city: " << endl;
        cin >> points[i][1];
    }

    for (int i = 0; i < no_of_cities; i++)
    {
        for (int j = 0; j < no_of_cities; j++)
        {
            edges[i][j] = sqrt(pow((points[i][0] - points[j][0]), 2) + pow((points[i][1] - points[j][1]), 2));
        }
    }

    cout << "Enter the City from which Salesman starts it's journey!!!" << endl;
    cin >> start;

    // Start measuring time
    clock_t start1 = clock();

    // Function Call
    Minimum_Travelling_Cost(edges, start);

    // Stop measuring time and calculate the elapsed time
    clock_t end = clock();
    double elapsed = double(end - start1) / CLOCKS_PER_SEC;

    cout << "Total time taken by program: " << elapsed << " seconds\n";
}