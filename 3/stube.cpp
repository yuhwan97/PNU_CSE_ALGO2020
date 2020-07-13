#include <bits/stdc++.h>
using namespace std;
typedef tuple<double,double,double> tdt;

ifstream ifs("stube.inp");
ofstream ofs("stube.out");
tuple<double,double,double> A,B,C,D,P,Q;
double p=1,q=1;
double bp,bq;
void read_data();
void print_output();
void processing();
void search_p(double,double);
void search_q(double,double);
double dist(tdt&,tdt&,tdt&,double);
void change_pq(tdt&,tdt&,tdt&,double);
bool is_min();

void print_data() {
	cout << get<0>(A) << " " << get<1>(A) << " " << get<2>(A) << endl;
	cout << get<0>(B) << " " << get<1>(B) << " " << get<2>(B) << endl;
	cout << get<0>(C) << " " << get<1>(C) << " " << get<2>(C) << endl;
	cout << get<0>(D) << " " << get<1>(D) << " " << get<2>(D) << endl;
}

int main() {
	read_data();
//	print_data();
    processing();
	print_output();
}


void read_data() {
	int x,y,z;
	ifs >> x >> y >> z;
	A = make_tuple(x,y,z);
	ifs >> x >> y >> z;
	B = make_tuple(x,y,z);
	ifs >> x >> y >> z;
	C = make_tuple(x,y,z);
	ifs >> x >> y >> z;
	D = make_tuple(x,y,z);
	ifs.close();
	P=A;
	Q=C;
}

void processing() {
    do {
        search_p(0.0,1.0);
        search_q(0.0,1.0);
    }while(!is_min());
}

void search_p(double start_t, double end_t) {
    double half = (end_t + start_t)/2.0;
    double dist_start = dist(A,B,Q,start_t);
    double dist_end = dist(A,B,Q,end_t);
    if(dist_start == dist_end) {
        change_pq(A,B,P,half);
        p = half;
    }
    else if(dist_start > dist_end)
        search_p(half,end_t);
    else
        search_p(start_t,half);
}

void search_q(double start_t, double end_t) {
    double half = (end_t + start_t)/2.0;
    double dist_start = dist(C,D,P,start_t);
    double dist_end = dist(C,D,P,end_t);
    if(dist_start == dist_end) {
        change_pq(C,D,Q,half);
        q = half;
    }
    else if(dist_start > dist_end)
        search_q(half,end_t);
    else
        search_q(start_t,half);
}

void change_pq(tdt& a, tdt& b, tdt& p, double t) {
    get<0>(p) = get<0>(a) + (get<0>(b) - get<0>(a)) * t;
    get<1>(p) = get<1>(a) + (get<1>(b) - get<1>(a)) * t;
    get<2>(p) = get<2>(a) + (get<2>(b) - get<2>(a)) * t;

}

double dist(tdt& a, tdt& b, tdt& p, double t) {
	double x,y,z;
	x = get<0>(p) - (get<0>(a) + (get<0>(b) - get<0>(a)) * t);
	y = get<1>(p) - (get<1>(a) + (get<1>(b) - get<1>(a)) * t);
	z = get<2>(p) - (get<2>(a) + (get<2>(b) - get<2>(a)) * t);
	//printf("%f %f %f\n", x,y,z);
	double d =  (sqrt(x*x + y*y + z*z));
	//printf("t = %f\tdist = %f\n", t, d);
	return d;
}

bool is_min() {
    if(0.00001 > abs(bp-p) && 0.00001 > abs(bq-q))
        return true;
    else{
        bp=p;
        bq=q;
        return false;
    }

}

void print_output() {
    double x,y,z;
    x = get<0>(P) - get<0>(Q);
    y = get<1>(P) - get<1>(Q);
    z = get<2>(P) - get<2>(Q);
    if(int(x)==0 && int(y)==0 && int(z)==0) {
        ofs << 0 << endl;
        ofs.close();
        return;
    }
    double dist = sqrt(x*x + y*y + z*z);
    if(0==dist-int(dist))
        ofs << int(dist) << endl;
    else
        ofs << int(dist)+1 << endl;

    ofs.close();
}
