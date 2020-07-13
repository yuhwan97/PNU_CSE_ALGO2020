#include <bits/stdc++.h>
using namespace std;

ifstream ifs("1.inp");
ofstream ofs("ticket.out");

struct {
    int s;
    int d;
    int t;
    int w;
}ticket;
int days[366]={0,};
int cost[366]={0,};
int last=0;

void read_data();
void print_data() {
    printf("%d %d %d %d\n", ticket.s, ticket.d, ticket.t, ticket.w);
    for(int i=0; i<366; ++i) {
        printf("%d: %d\n", i, days[i]);
    }
}
void processing();
void print_output();

int main() {
    read_data();
//    print_data();
    processing();
    print_output();
}


void read_data(){
    ifs >> ticket.s >> ticket.d >> ticket.t >> ticket.w;
    int n;
    ifs >> n;
    for(int i=0; i<n; ++i) {
        int d,r;
        ifs >> d >> r;
        days[d] = r;
        last = d;
    }
    ifs.close();
}

int three_days_ago(int d) {
    if(d < 3)
        return 0;
    else
        return d-3;

}

int monday(int d) {
    while(d%7!=1) {
        d--;
    }
    return d-1;
}

void processing() {

    for(int i=0; i<=last; ++i) {
        if(days[i]==0) {
            cost[i] = cost[i-1];
        }
        else {

            int single = cost[i-1] + days[i]*ticket.s;
            int day    = cost[i-1] + ticket.d;
            int three  = cost[three_days_ago(i)] + ticket.t;
            int week   = cost[monday(i)] + ticket.w;
//            printf("i=%d, s=%d, d=%d, t=%d, w=%d monday=%d\n", i, single, day, three, week, monday(i));
            cost[i] = min(min(single,day), min(three,week));
        }
    }

}

void print_output() {
//    for(int i=0; i<366; ++i) {
//        printf("cost[%d]: %d\n", i, cost[i]);
//    }
    ofs << cost[last] << endl;
    ofs.close();
}
