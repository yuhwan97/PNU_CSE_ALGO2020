//1 2 3 5 10 incorrect answer

#include <bits/stdc++.h>
using namespace std;
ifstream ifs("2.inp");
ofstream ofs("marathon.out");

typedef tuple<int,int> dit;
typedef struct nd{
    int index;
    vector<dit> neighbor;
    bool* visit_list;
    int length=0;
} Node;

vector<Node> vertices;
stack<Node> N_stack;
int n=0;
int shortest_len=0;
int start_index = 0;
//int cnt = 0;
void read_data();
void check_data();
void processing();
void BFS(Node);
bool mycomp(const Node& a, const Node& b) {
    return a.index < b.index;
}

int main() {
    read_data();
 //   check_data();
    processing();
}


void read_data() {
    ifs >> n;
    for(int i=0; i<n; ++i) {
        Node node;
        node.visit_list = new bool[n] {false,};
        ifs >> node.index;
        while(1) {
            int vertex, length;
            ifs >> vertex;
            if(vertex == 0)
                break;
            ifs >> length;
            node.neighbor.push_back(make_tuple(vertex, length));
        }
        vertices.push_back(node);
    }
    sort(vertices.begin(), vertices.end(), mycomp);
    ifs.close();

}

void check_data() {
    for(auto s: vertices) {
        printf("index: %d\n", s.index);
        for(auto t: s.neighbor) {
            printf("(%d,%d) ", get<0>(t), get<1>(t));
        }
        cout << endl;
    }
    cout << endl;
}

void processing() {

    for(auto s: vertices) {
        start_index = s.index;
        printf("start BFS(%d)\n", start_index);
        BFS(s);
    }

    cout << shortest_len << endl;
    ofs << 0 << endl;
    ofs.close();
}

void visit_check(const Node& node) {
    cout << "index: " << node.index << endl;
    for(int i=0; i<n; ++i) {
        cout << i+1 << " ";
    }
    cout << endl;

    for(int i=0; i<n; ++i) {
        if(node.visit_list[i])
            cout << "O" << " ";
        else
            cout << "X" << " ";
    }
    cout << endl;
}


void BFS(Node node) {
    //cout << "BFS start" << endl;
    //cnt++;
//    cout << "cnt: " << cnt << endl;
    cout << node.index << " " << node.length << endl;
    visit_check(node);
    N_stack.push(node);
    if(node.length>shortest_len && shortest_len!=0) {
       // cnt--;
        N_stack.top().visit_list[N_stack.top().index-1] = false;
        N_stack.pop();
        return;
    }
    //cout << "first branch" << endl;
    if(node.index == start_index && N_stack.size()>3) {
        if(shortest_len>node.length || shortest_len==0) {
            printf("old: %d     new: %d\n", shortest_len, node.length);
            shortest_len = node.length;
        }
        N_stack.top().visit_list[N_stack.top().index-1] = false;
        N_stack.pop();
      //  cnt--;
        return;
    }

    //cout << "second branch" << endl;

    for(int i=0; i<vertices[N_stack.top().index-1].neighbor.size(); ++i) {
    //    cout << "for loop start" << endl;
        int index, length;
        tie(index,length) = vertices[N_stack.top().index-1].neighbor[i];
        if(node.visit_list[index-1] == false && !(index == start_index && N_stack.size()<=3)) {
    //        cout << "for loop if" << endl;
            node.visit_list[index-1] = true;
            node.length += length;
            node.index = index;
            BFS(node);
            node.length -= length;
        }
    //    cout << "for loop end" << endl;
    }
    N_stack.top().visit_list[N_stack.top().index-1] = false;
    //cout << "BFS end" << endl;
    N_stack.pop();
    //cnt--;
}
