#include <bits/stdc++.h>
using namespace std;
ifstream ifs("tube.inp");
ofstream ofs("tube.out");
int stack_cnt=0;
int total_leng;
int n;
vector<int> leng;
stack<int> welding;


void read_data();
void processing();
void do_welding();


int main() {
    read_data();
    processing();

}

void read_data() {
    ifs >> total_leng;
    ifs >> n;
    for(int i=0; i<n; ++i) {
        int len;
        ifs >> len;
        leng.push_back(len);
    }
    ifs.close();

}

void processing() {
    for(int i=n-1; i>=0; --i) {
        welding.push(leng[i]);
        do_welding();
        welding.pop();
    }
    ofs << "0" << endl;
    ofs.close();
}

void do_welding() {
    if(welding.top() == total_leng) {
        int cnt=0;
        while(!welding.empty()) {
            cnt++;
            welding.pop();
        }
        ofs << cnt << endl;
        ofs.close();
        exit(0);
    }

    if(welding.top() > total_leng)
        return;

    for(int i=n-1; i>=0; --i) {
        welding.push(welding.top() + leng[i]);
        do_welding();
        welding.pop();
    }

}
