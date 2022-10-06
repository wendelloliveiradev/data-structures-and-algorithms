#include <iostream>
#include <list>
#include <unordered_map>
#include <algorithm>

#define mp unordered_map<int, list<int>>

using namespace std;

//Functions Definition
void splitCities(mp &cities);
void dfsSearch(mp &cities, unordered_map<int, bool> &visiteds, int &sum_cities_ids, int init);

int main() {
    mp cities;
    int M, N, u, v;

    cin >> N >> M;

    for (int i = 0; i < M; ++i) {
        cin >> u >> v;
        cities[u].push_back(v);
        cities[v].push_back(u);
    }

    splitCities(cities);

    return 0;
}

//Here we try to generate the second-largest subdivision for the cities
//the second-largest subdivision is equal to the DFS-tree generated
//from the DFS algorithm being executed over the second-biggest city ID
void splitCities(mp &cities) {
    unordered_map<int, bool> visiteds;
    int remain_cities_size = 0, sum_cities_ids = 0;
    auto max_city = max_element(cities.begin(), cities.end());
    auto second_max_city = max_element(cities.begin(), cities.end(),
                                       [&max_city](auto &a, auto &b) {
                                           if (a == *max_city) return true;
                                           if (b == *max_city) return false;
                                           return a < b;
                                       });

    visiteds[max_city->first] = true;

    sum_cities_ids += second_max_city->first;
    visiteds[second_max_city->first] = true;

    dfsSearch(cities, visiteds, sum_cities_ids, second_max_city->first);

    for (auto &itr : cities)
        remain_cities_size += itr.first;

    remain_cities_size -= sum_cities_ids;

    cout << remain_cities_size << endl;
}

//Standard DFS algorithm, start over the second-biggest city ID.
void dfsSearch(mp &cities, unordered_map<int, bool> &visiteds, int &sum_cities_ids, int init) {
    for (auto &itr : cities[init]) {
        if (visiteds.find(itr) == visiteds.end()) {
            visiteds[itr] = true;

            sum_cities_ids += itr;

            dfsSearch(cities, visiteds, sum_cities_ids, itr);
        }
    }
}