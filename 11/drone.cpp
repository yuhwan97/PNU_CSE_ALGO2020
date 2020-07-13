#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int> tit;

ifstream ifs("drone.inp");
ofstream ofs("drone.out");
vector<tuple<int,int,int>> coord;
vector<int> weight;
int total_weight=0;
int least_energy=0;
int n=0;
int** track=NULL;
stack<int> energy_stack;

void read_data();
void data_check();
void processing();
int manhattan_dist(tit start, tit dest);
int get_energy(tit start, tit dest, int current_weight);
void back_tracking(vector<int> coord_index, int start_index, int current_weight);
void close();
bool mycomp(tit a, tit b) {
    if(manhattan_dist(coord[1], a) < manhattan_dist(coord[1], b))
        return true;
    else
        return false;
}

int main() {
    read_data();
    data_check();
    processing();
    close();
}

void data_check() {
    for(int i=1; i<n+1; ++i) {
        printf("%d %d %d\n", weight[i], get<0>(coord[i]), get<1>(coord[i]));
    }
}

void read_data() {

    ifs >> n;
    coord.reserve(n+1);
    weight.reserve(n+1);
    for(int i=0; i<n; ++i) {
        int index,w,x,y;
        ifs >> index >> w >> x >> y;
        total_weight += w;
        weight[index] = w;
        coord[index] = make_tuple(x,y,w);
    }
    sort(coord.begin()+2, coord.begin()+n+1, mycomp);
    cout << "!" << endl;
    track = new int*[n];

    for(int i=0; i<n; ++i) {
        track[i] = new int[n];
        for(int j=0; j<n; ++j)
            track[i][j] = 0;
    }

}

int manhattan_dist(tit start, tit dest) {
//    cout << abs(get<0>(start)-get<0>(dest)) + abs(get<1>(start)-get<1>(dest)) << endl;
    return abs(get<0>(start)-get<0>(dest)) + abs(get<1>(start)-get<1>(dest));
}

int get_energy(tit start, tit dest, int current_weight) {
//    cout << current_weight <<endl;
    int energy = (current_weight+1)*manhattan_dist(start, dest);
//    cout << energy << endl;
    return energy;
}

void processing() {
    cout << total_weight << endl;
    if(n!=0) {
        vector<int> coord_index;
        for(int i=0; i<n; ++i) {
            coord_index.push_back(i+1);
        }
        energy_stack.push(0);
        back_tracking(coord_index, 1, total_weight);
    }
    else {
//        b_b();
    }

}

void back_tracking(vector<int> coord_index, int start_index, int current_weight) {
    if(least_energy!=0 && least_energy < energy_stack.top())
        return;
    if(coord_index.size() == 1) {
        energy_stack.push(energy_stack.top() + get_energy(coord[start_index], coord[1], 0));
        if(least_energy == 0 || least_energy > energy_stack.top())
            least_energy = energy_stack.top();
//        cout << energy_stack.top() << endl;
        energy_stack.pop();
        return;
    }

    for(int i=1; i<coord_index.size(); ++i) {
        auto tmp = coord_index;
        auto iter = tmp.begin();
        int dest_index = coord_index[i];
        advance(iter, i);
        int energy = get_energy(coord[start_index], coord[dest_index], current_weight);
        tmp.erase(iter);
 //       cout << energy << endl;
        energy_stack.push(energy_stack.top() + energy);
        back_tracking(tmp, dest_index, current_weight-get<2>(coord[dest_index]));
        energy_stack.pop();
    }
}

void close() {
    for(int i=0; i<n; ++i) {
        delete track[i];
    }
    delete track;
 //   cout << least_energy << endl;
    ofs << least_energy << endl;
    ofs.close();
}
