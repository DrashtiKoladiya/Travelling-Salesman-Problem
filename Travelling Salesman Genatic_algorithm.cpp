// C++ implementation of the above approach
#include <bits/stdc++.h>
#include <limits.h>
using namespace std;
#define VVD vector<vector<double>>
#define VVL vector<vector<int>>

vector<int> minPath;
double minCost;
int noOfCities, startCity;

// Number of cities in TSP
int V;

// Names of the cities
#define GENES ABCDE

// Starting Node Value
#define START 0

// Initial population size for the algorithm
#define POP_SIZE 100

struct individual
{
    vector<int> gnome;
    double fitness;
};

int rand_num(int start, int end)
{
    int r = end - start;
    int rnum = start + rand() % r;
    return rnum;
}

bool repeat(string s, char ch)
{
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == ch)
            return true;
    }
    return false;
}

vector<int> mutatedGene(vector<int> gnome)
{
    while (true)
    {
        int r = rand_num(1, V);
        int r1 = rand_num(1, V);
        if (r1 != r)
        {
            int temp = gnome[r];
            gnome[r] = gnome[r1];
            gnome[r1] = temp;
            break;
        }
    }
    return gnome;
}

vector<int> create_gnome()
{
    map<int, int> m;
    int cnt = 1;
    vector<int> gnome(V + 1);
    gnome[0] = 0;
    while (true)
    {
        if (cnt == V)
        {
            gnome[V] = 0;
            break;
        }
        int temp = rand_num(1, V);
        if (!m.count(temp))
        {
            gnome[cnt] = temp;
            cnt++;
            m[temp]++;
        }
    }
    return gnome;
}

double cal_fitness(vector<int> gnome, VVD map)
{
    double f = 0;
    for (int i = 0; i < gnome.size() - 1; i++)
    {
        if (map[gnome[i]][gnome[i + 1]] == 0)
            return DBL_MAX;
        f += map[gnome[i]][gnome[i + 1]];
    }
    return f;
}

int cooldown(int temp)
{
    return (90 * temp) / 100;
}

bool lessthan(struct individual t1,
              struct individual t2)
{
    return t1.fitness < t2.fitness;
}

void TSPUtil(VVD adj)
{
    vector<double> final;
    // Generation Number
    int gen = 1;
    // Number of Gene Iterations
    int gen_thres = 500;

    vector<struct individual> population;
    struct individual temp;

    // Populating the GNOME pool.
    for (int i = 0; i < POP_SIZE; i++)
    {
        temp.gnome = create_gnome();
        temp.fitness = cal_fitness(temp.gnome, adj);
        population.push_back(temp);
    }

    bool found = false;
    int temperature = 10000;

    // Iteration to perform
    // population crossing and gene mutation.
    while (/temperature > 1000 &&/ gen <= gen_thres)
    {
        sort(population.begin(), population.end(), lessthan);
        vector<struct individual> new_population;

        for (int i = 0; i < POP_SIZE; i++)
        {
            struct individual p1 = population[i];

            while (true)
            {
                vector<int> new_g = mutatedGene(p1.gnome);
                struct individual new_gnome;
                new_gnome.gnome = new_g;
                new_gnome.fitness = cal_fitness(new_gnome.gnome, adj);

                if (new_gnome.fitness <= population[i].fitness)
                {
                    new_population.push_back(new_gnome);
                    break;
                }
                else
                {

                    // Accepting the rejected children at
                    // a possible probability above threshold.
                    float prob = pow(2.7,
                                     -1 * ((float)(new_gnome.fitness - population[i].fitness) / temperature));
                    if (prob > 0.5)
                    {
                        new_population.push_back(new_gnome);
                        break;
                    }
                }
            }
        }

        temperature = cooldown(temperature);
        population = new_population;
        /*
        cout << "Generation " << gen << " \n";
        cout << "GNOME	 FITNESS VALUE\n";

        for (int i = 0; i < POP_SIZE; i++)
        {
            for (int j = 0; j < population[i].gnome.size(); j++)
            {
                cout << population[i].gnome[j] << " ";
            }
            cout << population[i].fitness << endl;
        }
        */
        double min = DBL_MAX;
        for(int i=0; i<population.size(); i++)
            if(population[i].fitness< min)
                min = population[i].fitness;
            
        if(final.size() < 1)
        final.push_back(min);
        else if (min < final[final.size()-1])
        final.push_back(min);
        else
        final.push_back(final[final.size()-1]);
        gen++;
    }
    
    for(auto it: final)
    {
        cout << it << " ";
    }
}

int main()
{

    //cout << "Please enter the number of cities: ";
    cin >> noOfCities;
    V = noOfCities;

    //cout << "Please enter the co-ordinates of each city:\n";
    VVD cordi(noOfCities, vector<double>(2, 0));

    // Input for the co-ordinates of each of the city
    for (int i = 0; i < noOfCities; i++)
    {
        //cout << "Enter the co-ordinate of the " << i << "th city: ";
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

    // Start measuring time
    
    TSPUtil(adj);
    

}