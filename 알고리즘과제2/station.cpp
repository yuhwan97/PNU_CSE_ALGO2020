#include <bits/stdc++.h>
using namespace std;

ifstream ifs("2.inp");
ofstream ofs("station.out");
tuple<double,double,double> A,B,P;

void read_data();
void search_dist(double,double);
double dist(double);

void print_data() {
	cout << get<0>(A) << " " << get<1>(A) << " " << get<2>(A) << endl;
	cout << get<0>(B) << " " << get<1>(B) << " " << get<2>(B) << endl;
	cout << get<0>(P) << " " << get<1>(P) << " " << get<2>(P) << endl;
}


int main() {
	read_data();
	print_data();
	search_dist(0.0,1.0);
	ifs.close();
	ofs.close();
}


void read_data() {
	int x,y,z;
	ifs >> x >> y >> z;
	A = make_tuple(x,y,z);
	ifs >> x >> y >> z;
	B = make_tuple(x,y,z);
	ifs >> x >> y >> z;
	P = make_tuple(x,y,z);
}

double half_of_line(double start_t, double end_t) {
	double x,y,z;
	x = get<0>(P) - ((get<0>(A) + (get<0>(B) - get<0>(A)) * start_t) + (get<0>(A) + (get<0>(B) - get<0>(A)) * end_t))/2;
	y = get<1>(P) - ((get<1>(A) + (get<1>(B) - get<1>(A)) * start_t) + (get<1>(A) + (get<1>(B) - get<1>(A)) * end_t))/2;
	z = get<2>(P) - ((get<2>(A) + (get<2>(B) - get<2>(A)) * start_t) + (get<2>(A) + (get<2>(B) - get<2>(A)) * end_t))/2;
	printf("%f %f %f\n", x,y,z);
	double d =  (sqrt(x*x + y*y + z*z));
	return d;
}

void search_dist(double start_t, double end_t) {
	double half = (end_t + start_t)/2.0;

	if(dist(start_t) == dist(end_t)) {
        double sol = half_of_line(start_t,end_t);
        if(0==sol-int(sol))
            ofs << int(sol) << endl;
        else
            ofs << int(sol)+1 << endl;
	}
	else if(dist(start_t) > dist(end_t))
		search_dist(half,end_t);
	else
		search_dist(start_t,half);
}

double dist(double t) {
	double x,y,z;
	x = get<0>(P) - (get<0>(A) + (get<0>(B) - get<0>(A)) * t);
	y = get<1>(P) - (get<1>(A) + (get<1>(B) - get<1>(A)) * t);
	z = get<2>(P) - (get<2>(A) + (get<2>(B) - get<2>(A)) * t);
	printf("%f %f %f\n", x,y,z);
	double d =  (sqrt(x*x + y*y + z*z));
	printf("t = %f\tdist = %f\n", t, d);
	return d;
}
