// oil.h

#include <stdio.h>
#include <stdlib.h>
// �Ʒ� ���� 5���� ���� ��� ����� ������ �� ���� ���� �Դϴ�.
// �Լ��� �����Ͻñ� �ٶ��ϴ�.

int Oil_sz;     /* ��ü ���� ũ�� */
int Oil_beg;    /* ���� ������ ���� ���� */
int Oil_end;    /* ���� ������ �� ���� */
int call_num;   /* observe() ȣ�� Ƚ�� */
int call_limit; /* observe() ȣ�� Ƚ�� ���� */

/* initial() : ��ü ���� ũ��, ��������, ȣ�� Ƚ�� ���� ���� */
void initial( ) {
    // �Ʒ� ���ô� ���ǻ� ���� ������ ���� ����������, �����δ� ���� ������� ���� ���� ������ ���� �Դϴ�.
    // �л��� ���� ����������� �ϴ°� �ƴ϶�, initial()���� ����˴ϴ�.
    // ���� �ڵ� �ۼ��� ���� ���� initial() �Լ��� ȣ���ؾ� �մϴ�.

    call_num    = 0;

    /* Sample Data 1 */
//    Oil_sz      = 19;
//    Oil_beg     =  2;
//    Oil_end     = 11;
//    call_limit  = 10;

    /* Sample Data 2 */
//    Oil_sz      = 1000;
//    Oil_beg     =  599;
//    Oil_end     =  599;
//    call_limit  =   30;

    /* Sample Data 3 */
    Oil_sz      = 10000;
    Oil_beg     =  1113;
    Oil_end     =  1794;
    call_limit  =    40;

    /* Sample Data 4 */
//    Oil_sz      = 100000;
//    Oil_beg     =  92981;
//    Oil_end     =  99984;
//    call_limit  =     500000;

}

/* oil_size() : ��ü ���� ũ�� ��ȯ */
int oil_size( ) {
    return Oil_sz;
}

/* observe(i, j) : Oil[i;j]�� ���� ��ȯ */
int observe( int i, int j ) {

    call_num++;

    /* ȣ�� Ƚ�� �ʰ� */
    if( call_num > call_limit ){
        printf("%d %d %d", 0, 0, call_num);
        exit(0);
    }

    /* 3. index ���� */
    if( i>j || i<0 || j<0 || i>=Oil_sz || j>=Oil_sz )
        return -1;

    if( j< Oil_beg || i> Oil_end ) return 0;    /* 1. �� ������ ��� '0' : Empty */
    if( i>=Oil_beg && j<=Oil_end ) return 1;    /* 2. �� ������ ��� '1' : Oil */

    return 2;                                   /* 4. '0'�� '1'�� ��� ���� : Mixed */
}

/* oil_report(i, j) : ��� ���*/
void oil_report( int i, int j ) {
    // ��� ����� oil_report(i, j)�� �̿��� ������ ����Ͻʽÿ�.
    // ���ǻ� console�� ����ϵ��� �Ǿ�������, �����δ� ���� ������� ���� ����� ����� �� �����Դϴ�.
    // oil_report(i,j)�� ȣ������ �ʰ�, �л��� ���� ���� ������� �� ��� ���� ó�� �˴ϴ�.
	 if( Oil_beg==i && Oil_end==j ) printf("����");

    printf( "%d %d", i, j );
    exit(0);
}
