#include <bits/stdc++.h>
using namespace std;

ifstream ifs("1.inp");
ofstream ofs("allin.out");
stack<int> stock;
int n=0;

void read_data();
void processing();
void print_output();

int main() {
    read_data();
    processing();
    print_output();
}

void read_data() {
    ifs >> n;
    for(int i=0; i<n; ++i) {
        int input;
        ifs >> input;
        stock.push(input);
    }
}

void processing() {




}
