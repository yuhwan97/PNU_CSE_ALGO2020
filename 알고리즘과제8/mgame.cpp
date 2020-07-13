#include <bits/stdc++.h>
using namespace std;

ifstream ifs("1.inp");
ofstream ofs("mgame.out");

int** min_ans;
int** max_ans;

void read_data();
void processing();
int arithmetic(int,char,int);
void init();
void foo(int,int);
void print_output();

vector<int> number;
vector<char> oper;

void check_data() {
    for(int i=0; i<number.size(); ++i) {
        for(int j=0; j<number.size(); ++j)
            cout << min_ans[i][j] << " ";
        cout << endl;
    }
    cout << "\n" << endl;

    for(int i=0; i<number.size(); ++i) {
        for(int j=0; j<number.size(); ++j)
            cout << max_ans[i][j] << " ";
        cout << endl;
    }
    cout << "\n" << endl;
}

int main() {
    read_data();
    init();
    processing();
    print_output();
}

void read_data() {

    string str;
    ifs >> str;
    for(auto s: str) {
        if(isdigit(s)) {
            char num[1] = {s};
            number.push_back(atoi(num));
        }
        else
            oper.push_back(s);
    }
    min_ans = (int**) calloc(number.size(), sizeof(int));
    max_ans = (int**) calloc(number.size(), sizeof(int));
    for(int i=0; i<number.size(); ++i) {
        min_ans[i] = (int*) calloc(number.size(), sizeof(int));
        max_ans[i] = (int*) calloc(number.size(), sizeof(int));
    }


    ifs.close();
}

void init() {
    for(int i=0; i<number.size()-1; ++i) {
        min_ans[i][i+1] = arithmetic(number[i],oper[i],number[i+1]);
        max_ans[i][i+1] = arithmetic(number[i],oper[i],number[i+1]);
    }
    check_data();
}

void processing() {
    for(int j=2; j<number.size(); ++j) {
        for(int i=0; i<number.size()-1 && i+j < number.size(); ++i) {
           foo(i,i+j);
        }
        check_data();
    }
}


void foo(int i,int j) {
//    cout << i << " " << j << endl;
    int ans1 = arithmetic(min_ans[i][j-1], oper[j-1], number[j]);
    int ans2 = arithmetic(number[i], oper[i], min_ans[i+1][j]);
    int ans3 = arithmetic(max_ans[i][j-1], oper[j-1], number[j]);
    int ans4 = arithmetic(number[i],oper[i],max_ans[i+1][j]);
    min_ans[i][j] = min(min(ans1,ans2),min(ans3,ans4));
    max_ans[i][j] = max(max(ans1,ans2),max(ans3,ans4));


}


int arithmetic(int a, char OP, int b) {

    switch(OP) {
    case '+':
        return a+b;
    case '-':
        return a-b;
    case '*':
        return a*b;
    default:
        exit(-1);
    }

}

void print_output() {
    cout << max_ans[0][number.size()-1] <<endl;
    ofs << max_ans[0][number.size()-1] << endl;

    ofs.close();
}
