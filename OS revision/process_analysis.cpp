#include<bits/stdc++.h>
#include<sys/semaphore.h>

using namespace std;
double check_stab(double* prev, double* curr) {
    if (*curr == 0 || (*prev != *curr)) {
        return -1;
    }
    return *curr;
}
int sequential_compute(int stage_num, vector<double> stage_cost, int batch_size) {
    int init_time = 0;
    vector<double> progress(stage_cost.size(), 0.0);
    for (int i = 0; i < batch_size; i++) {
        progress[0] += stage_cost[0];
        for (int j = 1; j < stage_cost.size(); j++) {
            progress[j] = max(progress[j - 1], progress[j]) + stage_cost[j];
        }
    }
    return progress[progress.size() - 1];
}

double find_stab_cost(int stage_num, vector<double> stage_cost) {
    double prev = 0.0;
    double curr = 0.0;
    double cost = 0.0;
    vector<double> progress(stage_cost.size(), 0.0);
    while (check_stab(&prev, &curr) < 0) {
        for (int i = 1; i < stage_cost.size(); i++) {
            progress[i] = max(progress[i - 1], progress[i]) + stage_cost[i];
        }
        prev = curr;
        curr = progress[progress.size() - 1] - progress[0] + stage_cost[0];
        if (curr - prev > 1000) {
            return -1;
        }
    }
    return curr;
}

int main() {
    int stage[2] = {3, 3};
    vector<double> costs[2] = {{5, 4, 3}, {4,3,5}};
    int batch[2] = {3, 3};
    cout << sequential_compute(stage[0], costs[0], batch[0]) << endl;
    cout << sequential_compute(stage[1], costs[1], batch[1]) << endl;

}