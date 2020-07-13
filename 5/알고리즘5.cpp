#include "oil.h"

int b=-1,s=-1;
void processing(int,int);
void search_left(int,int);
void search_right(int,int);

int main() {
    initial();
    int n=oil_size();
    processing(0,n-1);
    oil_report(b,s);
}

void processing(int Start, int End) {

    int half = (Start+End)/2;
    int left = observe(Start,half);
    int right = observe(half+1,End);
    printf("%d %d %d %d %d\n", Start, End, left, right, half);
    if(left==2 && right==2) {
        search_right(half+1,End);
        search_left(Start,half);
    }
    else if(left==2) {
        processing(Start,half);
    }
    else if(right==2) {
        processing(half+1, End);
    }

    if(left==1) {
        if(b==-1 || b>Start)
            b=Start;
        if(s==-1 || s<half)
            s=half;
    }

    if(right==1) {
        if(b==-1 || b>(half+1))
            b=half+1;
        if(s==-1 || s<End)
            s=End;
    }

    if(left==-1 || right==-1) {
        printf("Index Error\n");
        exit(-1);
    }

}

void search_left(int Start, int End) {
    printf("left\n");
    while(true) {
        int half = (Start+End)/2;
        int oil = observe(half-1,half+1);
        printf("half: %d\toil: %d\n", half,oil);
        if(oil==0) {
            Start = half;
        }
        else if(oil==1) {
            End = half;
        }
        else if(oil==2) {
            if(observe(half,half)==1)
                b=half;
            else
                b=half+1;
            break;
        }
    }

}
// 0 0 0 0 0 0 0 0 0 1 1 1    1 1 1 1 1 1 1 0 0 0 0 0 0
void search_right(int Start, int End) {
    bool flag=false;
    printf("right\n");

    while(true) {
        int half = (Start+End)/2;
        int oil = observe(half-1,half+1);
        printf("half: %d\toil: %d\n", half,oil);
        if(oil==0) {
            End = half;
        }
        else if(oil==1) {
            Start = half;
        }
        else if(oil==2) {
            if(observe(half,half)==1)
                s=half;
            else
                s=half-1;
            break;
        }
    }

}


//딱 한지점에만 있을 대 안댐
