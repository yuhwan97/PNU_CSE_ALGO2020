#include <bits/stdc++.h>
using namespace std;

ifstream ifs("angle.inp");
ofstream ofs("angle.out");
typedef tuple<int,int,int> tit;

int n=0;

vector<tit> first_quadrant;
vector<tit> second_quadrant;
vector<tit> third_quadrant;
vector<tit> fourth_quadrant;

void read_data();
void check_data();
void processing();
int calc_geo(tit a, tit b);
void print_output();

int main() {
    read_data();
    check_data();
    processing();
    print_output();
}


void read_data() {
    ifs >> n;
    int x,y;
    for(int i=0; i<n; ++i){
        ifs >> x >> y;
        if(x>=0 && y >=0)
            first_quadrant.push_back(make_tuple(x,y,i+1));
        if(x<0 && y>=0)
            second_quadrant.push_back(make_tuple(x,y,i+1));
        if(x<=0 && y<0)
            third_quadrant.push_back(make_tuple(x,y,i+1));
        if(x>0 && y<0)
            fourth_quadrant.push_back(make_tuple(x,y,i+1));
    }
    ifs.close();
}

void check_data() {
    int x,y,i;
    for(auto s: first_quadrant) {
        tie(x,y,i)=s;
        printf("(%d,%d) %d\n", x,y,i);
    }
    for(auto s: second_quadrant) {
        tie(x,y,i)=s;
        printf("(%d,%d) %d\n", x,y,i);
    }
    for(auto s: third_quadrant) {
        tie(x,y,i)=s;
        printf("(%d,%d) %d\n", x,y,i);
    }
    for(auto s: fourth_quadrant) {
        tie(x,y,i)=s;
        printf("(%d,%d) %d\n", x,y,i);
    }
}

int calc_geo(tit a, tit b) {
    int ax, ay;
    int bx, by;
    int result;
    tie(ax,ay,result)=a;
    tie(bx,by,result)=b;

    result = ax*by - ay*bx;

    if(result > 0)
        return 1;
    else if(result < 0)
        return -1;
    else
        return 0;
}

bool mycomp(tit a, tit b) {
    if(calc_geo(a,b) == 0) {
        int ax, ay;
        int bx, by;
        int sum_a, sum_b;
        tie(ax,ay,sum_a)=a;
        tie(bx,by,sum_b)=b;

        sum_a = abs(ax) + abs(ay);
        sum_b = abs(bx) + abs(by);
        return sum_a < sum_b;
    }

    else
        return calc_geo(a,b) > 0;

}

void processing() {

    sort(first_quadrant.begin(), first_quadrant.end(), mycomp);
    sort(second_quadrant.begin(), second_quadrant.end(), mycomp);
    sort(third_quadrant.begin(), third_quadrant.end(), mycomp);
    sort(fourth_quadrant.begin(), fourth_quadrant.end(), mycomp);
}

void print_output() {

    for(auto s: first_quadrant) {
        ofs << get<2>(s) << endl;
    }
    for(auto s: second_quadrant) {
        ofs << get<2>(s) << endl;
    }
    for(auto s: third_quadrant) {
        ofs << get<2>(s) << endl;
    }
    for(auto s: fourth_quadrant) {
        ofs << get<2>(s) << endl;
    }
}
