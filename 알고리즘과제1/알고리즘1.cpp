#include <iostream>
#include <fstream>
using namespace std;

ifstream ifs("2.inp");
ofstream ofs("cards.out");
int processing(int);
int sum(int);
void print_output(int,int);


int main() {

    int n;
    ifs >> n;
    int card_sum = sum(n);
    int answer = processing(n);
    print_output(card_sum, answer);

    ifs.close();
    ofs.close();
}
void print_output(int sum, int answer) {
        ofs << answer << endl;
        ofs << sum-answer << endl;
}

int sum(int n) {
    int card_sum=0;
    for(int i=n; i>2; --i) {
        int input;
        ifs >> input;
        card_sum += i;
        card_sum -= input;
    }
    card_sum += 3;
    return card_sum;
}

int processing(int n) {

    for(int i=1; i<=n; ++i) {
        ifstream ifs2("2.inp");
        int garbage;
        ifs2 >> garbage;
        int flag=0;

        for(int j=0; j<n-2; ++j) {
            int input;
            ifs2 >> input;
            if(input==i) {
                flag=1;
                break;
            }
        }
        ifs2.close();
        if(flag==0) {
            return i;
            break;
        }
    }
    exit(0);
}
