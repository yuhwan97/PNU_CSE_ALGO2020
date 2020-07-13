#include <bits/stdc++.h>
using namespace std;


int main() {

    int* a = new int[10] {0,};
    int* b = new int[10];
    b = a;
    b[2] = 3;
    for(int i=0; i<10; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;


}
