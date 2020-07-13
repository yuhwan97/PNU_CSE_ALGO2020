#include <bits/stdc++.h>
using namespace std;
ifstream ifs("1.inp");
ofstream ofs("marathon.out");
typedef tuple<int,int> dit;
vector<vector<dit>> len_info;

int n=0;
int shortest_len=0;
//int** dp;



void read_data();
void check_data();
void print_table(int** dp) {
    for(int i=0; i<n+1; ++i) {
        for(int j=0; j<n+1; ++j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void processing();
int dynamic_programming(int);
void dp_search(int** dp, int row, int col, int len, int);

int main() {
    cout << "ER" << endl;
    read_data();
    cout << "er" << endl;
    check_data();
    processing();
}


void read_data() {
    ifs >> n;
//    dp = new int*[n+1];
    for(int i=0; i<n; ++i) {
//        dp[i] = new int[n+1] {0,};
        vector<dit> tmp;
        int garbage;
        ifs >> garbage;
        while(1) {
            int index, length;
            ifs >> index;
            if(index == 0)
                break;
            ifs >> length;
            tmp.push_back(make_tuple(index, length));

        }
        len_info.push_back(tmp);
    }
}

void check_data() {
    for(int i=0; i<len_info.size(); ++i) {
        cout << "index: " << i+1 << endl;
        for(auto s: len_info[i]) {
            printf("(%d,%d) ", get<0>(s), get<1>(s));
        }
        cout << endl;
    }

}

void processing() {

    for(int i=0; i<n; ++i) {
        int new_len = dynamic_programming(i);
        if(shortest_len==0 || new_len < shortest_len)
            shortest_len = new_len;
        cout <<shortest_len<< endl;
    }
}

int dynamic_programming(int index) {
    int** dp = new int*[n+1];
    int prev_len=0;
    for(int i=0; i<n+1; ++i) {
        dp[i] = new int[n+1] {0,};
    }
    for(int i=0; i<len_info[index].size(); ++i) {
        int vertex = get<0>(len_info[index][i]);
        dp[1][vertex] = get<1>(len_info[index][i]);
    }

    for(int i=1; i<n; ++i) {
        for(int j=1; j<n; ++j) {
            if(dp[i][j] != 0 && j!=index+1 && dp[i][j]!=dp[i-1][j]) {
             //   cout << "search" << endl;
                dp_search(dp,i,j,dp[i][j], index+1);

            }
            if(dp[i][j]==0)
                dp[i][j] = dp[i-1][j];
        }
        if(prev_len > dp[i][index+1] || prev_len==0)
            prev_len = dp[i][index+1];
        print_table(dp);
    }
    print_table(dp);
    delete[] dp;
    return prev_len;
}

void dp_search(int** dp, int row, int col, int len, int start) {
    for(int i=0; i<len_info[col-1].size(); i++) {
        int vertex = get<0>(len_info[col-1][i]);
    //    cout << "vertex: " << vertex << endl;
        int new_len = len + get<1>(len_info[col-1][i]);
  //      cout << "new len: " << new_len << endl;

        if((new_len < dp[row+1][vertex] || dp[row+1][vertex] == 0) && !(start==vertex && row<=3) )
            dp[row+1][vertex] = new_len;
    }
 //   print_table(dp);
}
