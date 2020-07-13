#include <bits/stdc++.h>
using namespace std;
typedef tuple<int,int,int,int,int,int> hit;

ifstream ifs("diet.inp");
ofstream ofs("diet.out");
int n=0;
int flag=0;
tuple<int,int,int,int> goal;
vector<hit> food;
vector<hit> selected_food;

void read_data();
void check_data();
void processing();
void choose(int r);
bool is_good(vector<hit> new_food);
void food_comp(vector<hit> new_food);
void print_output();


int main() {

    read_data();
    check_data();
    processing();
    print_output();
}

void read_data() {
    ifs >> n;
    int p,f,s,v,cost;
    ifs >> p >> f >> s >> v;
    goal = make_tuple(p,f,s,v);

    for(int i=0; i<n; ++i) {
        ifs >> p >> f >> s >> v >> cost;
        food.push_back(make_tuple(cost,p,f,s,v,i+1));
    }
}

void check_data() {
    sort(food.begin(), food.end());
    int index,p,f,s,v,cost;
    tie(p,f,s,v) = goal;
    printf("%d %d %d %d\n", p,f,s,v);
    for(int i=0; i<n; ++i) {
        tie(cost,p,f,s,v,index) = food[i];
        printf("%d %d %d %d %d %d\n", cost,p,f,s,v,index);
    }
}

void processing() {

    for(int i=1; i<n; ++i) {
        sort(food.begin(), food.end());
        choose(i);
    }

}

bool desc(int a, int b) {
    return a>b;
}

void choose(int r) {
    cout << r << endl;
    vector<int> choose_index;
    for(int i=0; i<r; ++i) {
        choose_index.push_back(0);
    }
    for(int i=0; i<food.size()-r; ++i) {
        choose_index.push_back(1);
    }

    sort(choose_index.begin(), choose_index.end());
    flag = 0;
    do {
        vector<hit> tmp_food;

        for(int i=0; i<choose_index.size(); ++i) {
//            cout << choose_index[i] << " ";
            if(choose_index[i] == 0)
                tmp_food.push_back(food[i]);
        }
//        cout << endl;
        if(is_good(tmp_food)) {
 //           cout << "is good! " << endl;
            flag++;
            food_comp(tmp_food);
        }
//        if(flag > 30)
//            break;
    }while(next_permutation(choose_index.begin(),choose_index.end()));
}



bool is_good(vector<hit> new_food) {
    int p=0,f=0,s=0,v=0,cost=0;
    for(auto t: new_food) {
        cost += get<0>(t);
        p += get<1>(t);
        f += get<2>(t);
        s += get<3>(t);
        v += get<4>(t);
    }
//    cout << "total : " << p << " " << f << " " << s << " "<< v <<endl;
    int gp,gf,gs,gv;
    tie(gp,gf,gs,gv) = goal;

    if(p>=gp && f>=gf && s>=gs && v>=gv)
        return true;
    else
        return false;
}

void food_comp(vector<hit> new_food) {
    int sel_total=0, sel_cost=0, sel_index=0;
    int new_total=0, new_cost=0, new_index=0;
//    cout << "sel_index: ";
    for(auto t: selected_food) {
        sel_cost += get<0>(t);
        sel_total += get<1>(t);
        sel_total += get<2>(t);
        sel_total += get<3>(t);
        sel_total += get<4>(t);
//        cout << get<5>(t) << " ";
    }
//    cout << endl;
//    cout << "sel_cost: " << sel_cost << endl;
//    cout << "sel_total: " << sel_total << endl;

//    cout << "new_index: ";
    for(auto t: new_food) {
        new_cost += get<0>(t);
        new_total += get<1>(t);
        new_total += get<2>(t);
        new_total += get<3>(t);
        new_total += get<4>(t);
//        cout << get<5>(t) << " ";
    }
//    cout <<  endl;
//    cout << "new_cost: " << new_cost << endl;
//    cout << "new_total: " << new_total << endl;

    if(sel_cost > new_cost || sel_cost==0) {
 //       cout <<"E" << endl;
        selected_food = new_food;
    }
    else if(sel_cost == new_cost) {
        if(sel_total < new_total) {
            selected_food = new_food;
        }
    }
}

bool mycomp(hit a, hit b) {
    if(get<5>(a) < get<5>(b))
        return true;
    else
        return false;
}

void print_output() {
    sort(selected_food.begin(), selected_food.end(), mycomp);
    for(int i=0; i<selected_food.size(); ++i) {
        ofs << get<5>(selected_food[i]) << " ";
        cout << get<5>(selected_food[i]) << " ";
    }
    ofs << endl;
    cout << endl;
    ofs.close();
}
