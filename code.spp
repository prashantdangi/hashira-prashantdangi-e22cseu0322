#include <nlohmann/json.hpp>
#include <bits/stdc++.h>
using namespace std;

using json = nlohmann::json;

// Function to compute Lagrange interpolation at x=0
double lagrangeInterpolationAtZero(vector<pair<double,double>> points) {
    int n = points.size();
    double result = 0.0;

    for (int i = 0; i < n; i++) {
        double term = points[i].second; // y_i
        for (int j = 0; j < n; j++) {
            if (i != j) {
                term *= (0 - points[j].first) / (points[i].first - points[j].first);
            }
        }
        result += term;
    }

    return result;
}

int main() {
    // Open JSON file
    ifstream fin("testcase1.json");
    if (!fin) {
        cerr << "Could not open testcase1.json" << endl;
        return 1;
    }
    json j;
    fin >> j;
    fin.close();

    int n = j["keys"]["n"];
    int k = j["keys"]["k"];
    vector<pair<double,double>> points;
    for (auto& el : j.items()) {
        if (el.key() == "keys") continue;
        int x = stoi(el.key());
        int base = stoi(el.value()["base"].get<string>());
        string value = el.value()["value"].get<string>();
        long long y = stoll(value, nullptr, base);
        points.emplace_back(x, y);
    }
    // Sort by x
    sort(points.begin(), points.end());
    // Use only the first k points
    if ((int)points.size() > k)
        points.resize(k);

    double c = lagrangeInterpolationAtZero(points);

    cout << "The constant term c = " << c << endl;

    return 0;
}