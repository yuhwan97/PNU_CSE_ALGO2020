//8 incorrect
#include <bits/stdc++.h>
using namespace std;

ifstream ifs("7.inp");
ofstream ofs("lock.out");
typedef tuple<int,int> dit;

int n=0, m=0;
int DFS_num=1;
char** table;
int** DFS_num_table;
bool ST_search=false;
vector<dit> cut_vertices;
vector<dit> answer;
stack<dit> ST_path;
dit S;
dit T;

void read_data();
void check_data();
void processing();
int DFS(int x, int y);
void find_answer();

void print_nums() {
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; ++j) {
            if(DFS_num_table[i][j]==99999999)
            cout << '_' << " ";
            else
            cout << DFS_num_table[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    read_data();
    check_data();
    processing();
}


void read_data() {
    ifs >> m >> n;
    table = new char*[n];
    DFS_num_table = new int*[n];

    for(int i=0; i<n; ++i) {
        table[i] = new char[m];
        DFS_num_table[i] = new int[m] {0,};
    }

    char c;
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; ++j) {
            ifs >> c;
            table[i][j] = c;

            if(c == '#')
                DFS_num_table[i][j] = 99999999;

            if(c == 'S') {
                S = make_tuple(i,j);
            }
            if(c == 'T') {
                T = make_tuple(i,j);
            }
        }
    }
    ifs.close();
}

void check_data() {

    for(int i=0; i<n; i++) {
        for(int j=0; j<m; ++j) {
            cout << table[i][j] << " ";
        }
        cout << endl;
    }

}

void processing() {
    int start_x, start_y;
    tie(start_y, start_x) = S;
    DFS(start_y, start_x);
    if(cut_vertices.size()==0)
        ofs << 0 << endl;
    else
        find_answer();

    ofs.close();
}

bool is_equal(dit a, dit b) {

    if(get<0>(a)==get<0>(b) && get<1>(a)==get<1>(b))
        return true;
    else
        return false;
}

int DFS(int y, int x) { // find cut-vertex

    //만약 방문 한 vertex이면 그 vertex의 DFS_number를 return;
    if(DFS_num_table[y][x] != 0)
        return DFS_num_table[y][x];

    //방문하지 않은 vertex라면 DFS_num을 부여해준다.
    DFS_num_table[y][x] = DFS_num;
    DFS_num++;
//    cout << "x: " << x << " " << "y: " << y << " " << DFS_num_table[y][x] << endl;
//    print_nums();
    int ret_val[4];
    // 상하좌우 네 방향으로 DFS진행
    if(m > x+1)
        ret_val[3] = DFS(y, x+1);
    else
        ret_val[3] = 99999999;
    if(0 <= y-1)
        ret_val[2] = DFS(y-1, x);
    else
        ret_val[2] = 99999999;
    if(0 <= x-1)
        ret_val[1] = DFS(y, x-1); // 만약 DFS를 시도한 vertex가 이미 방문한 vertex라면 그 vertex의 BFS_num을 반환하기 때문에
    else                              // 현재 vertex에서 갈 수 있는 최소 BFS_num을 구하는 과정이 된다.
        ret_val[1] = 99999999;
    if(n > y+1)
        ret_val[0] = DFS(y+1, x);
    else
        ret_val[0] = 99999999;




//    cout << abs(row-n) << " " << abs(y+1) << " " << DFS_num_table[row][y] << endl;
    for(int i=0; i<4; ++i) {        // 만약 4가지 경우중에 자신의 DFS_num과 같은 경우가 있다면 cut_vertex이다.
//        printf("ret_val[%d] = %d\n", i, ret_val[i]);
        if(ret_val[i] == DFS_num_table[y][x] && DFS_num_table[y][x] != 1 && !is_equal(T, make_tuple(y,x))) {
            cut_vertices.push_back(make_tuple(y,x));
            break;
        }
    }

    return min(min(ret_val[0],ret_val[1]), min(ret_val[2],ret_val[3])); //갈 수 있는 vertexdml BFS_num 중 최소 BFS_num을 반환한다.
}




bool BFS(dit cut) {
    int cut_x, cut_y;

    tie(cut_y, cut_x) = cut;
//    cout << "cut_x: " << cut_x+1 << " " << "cut_y: " << abs(cut_y-n) << endl;
    bool visit[n][m] = {{false,},};
    visit[cut_y][cut_x] = true;
    visit[get<0>(S)][get<1>(S)] = true;
    queue<dit> Q;
    Q.push(S);
//    cout << "!!" << endl;
    while(!Q.empty()) {
        int x, y;
        tie(y,x) = Q.front();
//        cout << x+1 << " " << abs(y-n) << endl;
        if(is_equal(T, Q.front())) {
            cout << "true" << endl;
            return true;
        }
        Q.pop();
        if(m > x+1 && visit[y][x+1]==false && table[y][x+1]!='#') {
            Q.push(make_tuple(y,x+1));
           // printf("push(%d,%d)\n", x+2,abs(y-n));
            visit[y][x+1] = true;
        }


        if(0 <= y-1 && visit[y-1][x]==false && table[y-1][x]!='#') {
            Q.push(make_tuple(y-1,x));
            //printf("push(%d,%d)\n", x+1,abs(y-1-n));
            visit[y-1][x] = true;
        }

        if(0 <= x-1 && visit[y][x-1]==false && table[y][x-1]!='#') {
            Q.push(make_tuple(y,x-1));
           // printf("push(%d,%d)\n", x,abs(y-n));
            visit[y][x-1] = true;
        }

        if(n > y+1 && visit[y+1][x]==false && table[y+1][x]!='#') {
            Q.push(make_tuple(y+1,x));
           // printf("push(%d,%d)\n", x+1,abs(y+1-n));
            visit[y+1][x] = true;
        }


    }
    return false;
}

bool BFS() {
//    cout << "cut_x: " << cut_x+1 << " " << "cut_y: " << abs(cut_y-n) << endl;
    bool visit[n][m] = {{false,},};
    visit[get<0>(S)][get<1>(S)] = true;
    queue<dit> Q;
    Q.push(S);
//    cout << "!!" << endl;
    while(!Q.empty()) {
        int x, y;
        tie(y,x) = Q.front();
//        cout << x+1 << " " << abs(y-n) << endl;
        if(is_equal(T, Q.front())) {
            cout << "true" << endl;
            return true;
        }
        Q.pop();
        if(m > x+1 && visit[y][x+1]==false && table[y][x+1]!='#') {
            Q.push(make_tuple(y,x+1));
           // printf("push(%d,%d)\n", x+2,abs(y-n));
            visit[y][x+1] = true;
        }


        if(0 <= y-1 && visit[y-1][x]==false && table[y-1][x]!='#') {
            Q.push(make_tuple(y-1,x));
            //printf("push(%d,%d)\n", x+1,abs(y-1-n));
            visit[y-1][x] = true;
        }

        if(0 <= x-1 && visit[y][x-1]==false && table[y][x-1]!='#') {
            Q.push(make_tuple(y,x-1));
           // printf("push(%d,%d)\n", x,abs(y-n));
            visit[y][x-1] = true;
        }

        if(n > y+1 && visit[y+1][x]==false && table[y+1][x]!='#') {
            Q.push(make_tuple(y+1,x));
           // printf("push(%d,%d)\n", x+1,abs(y+1-n));
            visit[y+1][x] = true;
        }


    }
    return false;
}

bool mycomp(dit a, dit b) {

    if(get<1>(a) == get<1>(b))
        return get<0>(a) > get<0>(b);
    else
        return get<1>(a) < get<1>(b);
}

void find_answer() {
    if(!BFS()) {
        ofs << 0 << endl;
        return;
    }
    for(int i=0; i<cut_vertices.size(); ++i) {
        bool is_answer = BFS(cut_vertices[i]);
        if(!is_answer)
            answer.push_back(cut_vertices[i]);
    }
    sort(answer.begin(), answer.end(), mycomp);
    cout << answer.size() << endl;
    ofs << answer.size() << endl;
    for(auto s: answer) {
        cout << get<1>(s)+1 << " " << abs(get<0>(s)-n) << endl;
        ofs << get<1>(s)+1 << " " << abs(get<0>(s)-n) << endl;
    }
}
