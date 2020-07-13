#include <bits/stdc++.h>
using namespace std;

ifstream ifs("3.inp");
ofstream ofs("allin.out");
vector<int> stock;
int b=0,s=0,n=0;

void read_data() {
    ifs >> n;
    s=n-1;
    for(int i=0; i<n; ++i) {
        int p;
        ifs >> p;
        stock.push_back(p);
    }
    ifs.close();
}

void processing() {
    for(int j=0; j<1000; j++){
        for(int i=s-1; i>b; --i) {
            if(stock[i] >= stock[s]) {
                s=i;
                break;
            }
        }
        for(int i=b+1; i<s; ++i) {
            if(stock[i] <= stock[b]) {
                b=i;
                break;
            }
        }
    }
}

void print_output() {
    ofs << b+1 << " " << s+1 << endl;
    ofs.close();
}

int main() {
    read_data();
    processing();
    print_output();
}

/*








*/
