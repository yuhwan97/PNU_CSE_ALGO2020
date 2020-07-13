#include <bits/stdc++.h>
using namespace std;

ifstream ifs("detroit.inp");
ofstream ofs("detroit.out");

int n=0;
int cnt=0;
int** pizza = NULL;

void read_data();
void print_pizza() {
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j)
            cout << pizza[i][j] << " ";
        cout << endl;
    }
}
void processing();
bool check(int,int,int);


int main() {
    read_data();
//    print_pizza();
    processing();
    ofs << cnt << endl;
    ofs.close();
}


void read_data() {
    ifs >> n;
    pizza = new int*[n];
    for(int i=0; i<n; ++i) {
        pizza[i] = new int[n];
        for(int j=0; j<n; ++j)
            ifs >> pizza[i][j];
    }
}

void processing() {
    for(int i=0; i<n; ++i) {
        for(int j=0; j<n; ++j) {
            if(pizza[i][j]==0) {
                for(int k=0; k<n; ++k) {
                    if(check(i,j,k+1) == 1) {
                        pizza[i][j] = k+1;
                        processing();
                        pizza[i][j] = 0;
                    }
                }
                return;
            }
        }
    }

    ++cnt;

}

bool check(int row, int col, int num) {
    for(int i=0; i<n; ++i) {
        if(pizza[i][col] == num)
            return false;
    }

    for(int i=0; i<n; ++i) {
        if(pizza[row][i] == num)
            return false;
    }
    return true;
}
