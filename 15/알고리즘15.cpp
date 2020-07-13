
#include <bits/stdc++.h>
using namespace std;

ifstream ifs("1.inp");
ofstream ofs("lock.out");
typedef tuple<int,int> dit;

int n=0, m=0;
int DFS_num=1;
char** table;
int** DFS_num_table;
bool ST_search=false;
vector<dit> cut_vertices;
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
  //  check_data();
    processing();
}


void read_data() {
    ifs >> n >> m;
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
    find_answer();
    ofs.close();
}


int DFS(int y, int x) {

    //���� �湮 �� vertex�̸� �� vertex�� DFS_number�� return;
    if(DFS_num_table[y][x] != 0)
        return DFS_num_table[y][x];


    //S to T Path�� ã�� �� ���� ST_path�� ���� vertex�� push;
    if(!ST_search)
        ST_path.push(make_tuple(y,x));
    if(get<0>(T)==y && get<1>(T)==x)
        ST_search = true;

    //�湮���� ���� vertex��� DFS_num�� �ο����ش�.
    DFS_num_table[y][x] = DFS_num;
    DFS_num++;
//    cout << "x: " << x << " " << "y: " << y << " " << DFS_num_table[y][x] << endl;
    print_nums();
    int ret_val[4];
    // �����¿� �� �������� DFS����
    if(m > x+1)
        ret_val[3] = DFS(y, x+1);
    else
        ret_val[3] = 99999999;
        if(0 <= y-1)
        ret_val[2] = DFS(y-1, x);
    else
        ret_val[2] = 99999999;
    if(0 <= x-1)
        ret_val[1] = DFS(y, x-1); // ���� DFS�� �õ��� vertex�� �̹� �湮�� vertex��� �� vertex�� BFS_num�� ��ȯ�ϱ� ������
    else                              // ���� vertex���� �� �� �ִ� �ּ� BFS_num�� ���ϴ� ������ �ȴ�.
        ret_val[1] = 99999999;
    if(n > y+1)
        ret_val[0] = DFS(y+1, x);
    else
        ret_val[0] = 99999999;




//    cout << abs(row-n) << " " << abs(y+1) << " " << DFS_num_table[row][y] << endl;
    for(int i=0; i<4; ++i) {        // ���� 4���� ����߿� �ڽ��� DFS_num�� ���� ��찡 �ִٸ� cut_vertex�̴�.
//        printf("ret_val[%d] = %d\n", i, ret_val[i]);
        if(ret_val[i] == DFS_num_table[y][x] && DFS_num_table[y][x] != 1) {
            cut_vertices.push_back(make_tuple(y,x));
            break;
        }
    }
    if(!ST_search) {    //���� �� vertex�� S to T Path�� ���Ե��� ������ pop;
        ST_path.pop();
    }

    return min(min(ret_val[0],ret_val[1]), min(ret_val[2],ret_val[3])); //�� �� �ִ� vertexdml BFS_num �� �ּ� BFS_num�� ��ȯ�Ѵ�.
}

bool is_equal(dit a, dit b) {
    if(get<0>(a)==get<0>(b) && get<1>(a)==get<1>(b))
        return true;
    else
        return false;
}

bool mycomp(dit a, dit b) {

    if(get<0>(a) == get<0>(b))
        return get<1>(a) < get<1>(b);
    else
        return get<0>(a) > get<0>(b);
}

void find_answer() {
    if(ST_path.size() <= 0) {
        ofs << 0 << endl;
        return;
    }
    if(cut_vertices.size() == 0) {
        ofs << 0 << endl;
        return;
    }
    vector<dit> tmp;

    while(!ST_path.empty()) {
        for(int i=0; i<cut_vertices.size(); ++i) {
            if(is_equal(cut_vertices[i], ST_path.top()))
                tmp.push_back(ST_path.top());
        }
        ST_path.pop();
    }
    sort(tmp.begin(), tmp.end(), mycomp);
    ofs << tmp.size() << endl;
    for(auto s: tmp) {
        cout << get<1>(s)+1 << " " << abs(get<0>(s)-n) << endl;
        ofs << get<1>(s)+1 << " " << abs(get<0>(s)-n) << endl;
    }
}
