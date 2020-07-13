#include <bits/stdc++.h>
using namespace std;
ofstream ofs("bucket.out");
int n=0;
int cnt=0;

vector<int> capacity;
vector<int> start;
vector<int> goal;
vector<int> prev_water;
queue<vector<int>> bucket;

void read_data(void);
void check_data(void);
void pour_water(vector<int>,int,int);
void processing();
bool is_answer(vector<int>);
bool is_equal(vector<int>,vector<int>);
int main() {
    read_data();
    check_data();
    processing();
}

void read_data() {
    ifstream ifs("1.inp");
    ifs >> n;
    int a;
    for(int i=0; i<n; ++i) {
        ifs >> a;
        capacity.push_back(a);
    }

    for(int i=0; i<n; ++i) {
        ifs >> a;
        start.push_back(a);
    }

    for(int i=0; i<n; ++i) {
        ifs >> a;
        goal.push_back(a);
    }
    ifs.close();
}

void check_data() {
    for(auto t: capacity)
        cout << t << " ";
    cout << endl;
    for(auto t: start)
        cout << t << " ";
    cout << endl;
    for(auto t: goal)
        cout << t << " ";
    cout << endl;

}

void processing() {
    start.push_back(0);
    bucket.push(start);
    while(!bucket.empty()) {
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                if(i!=j) {
                    pour_water(bucket.front(),i,j);
                }
            }
        }
        bucket.pop();
    }
}

void pour_water(vector<int> water, int from, int to) {


    if(water[from] + water[to] <= capacity[to]) {
        water[to] = water[to] + water[from];
        water[from] = 0;
    }
    else if(water[from] + water[to] > capacity[to]) {
        water[to] = capacity[to];
        water[from] = water[from] - (capacity[to] - water[to]);
    }

    water[n]++;

    if(equal(water.begin(), water.end(), prev_water.begin(), prev_water.end()z))
        cnt++;
    else
        cnt = 0;

    if(cnt >= 3) {
        ofs << 0 << endl;
        cout << 0 << endl;
        ofs.close();
        exit(0);
    }
    prev_water = water;

    if(is_answer(water)) {
        ofs << water[n] << endl;
        cout << water[n] << endl;
        ofs.close();
        exit(0);
    }
    bucket.push(water);

}


bool is_answer(vector<int> ans) {
    bool flag = true;

    for(int i=0; i<n; ++i) {
 //       cout << ans[i] << " ";
        if(ans[i] != goal[i])
            flag = false;
    }
 //   cout << endl;

    return flag;
}


