#include <stdio.h>

#define MAX_SIZE 100001

char prime[MAX_SIZE];
int a, b;
int res[MAX_SIZE];

void init_prime()
{
    for (int i = 0; i < MAX_SIZE; i++) {
        prime[i] = 1;
    }
    prime[0] = 0;
    prime[1] = 0;
}

void cal_prime(int b)
{
    for (int i = 2; i < b; i++) {
        if (prime[i] == 0)
            continue;
        for (int j = 2 * i; j <= b; j += i)
            prime[j] = 0;
    }
}

int output_prime(int a, int b)
{
    int cnt = 0;
    for (int i = a; i <= b; i++) {
        if (prime[i] == 1) {
            res[cnt] = i;
            cnt++;
//            printf("%d ", i);
        }
    }
//    printf("\n");
    return cnt;
}

void find_shulie(int cnt)
{
    int begin_idx, curr_idx;
    begin_idx = 0;
    curr_idx = begin_idx + 1;

    while(curr_idx < cnt) {
        int cha = res[curr_idx] - res[begin_idx];
        curr_idx++;
        while(curr_idx < cnt) {
            if ((res[curr_idx] - res[curr_idx-1]) == cha)
                curr_idx++;
            else
                break;
        }
        if (curr_idx - begin_idx > 2) {
            for (int i = begin_idx; i < curr_idx; i++) {
                printf("%d ", res[i]);
            }
            printf("\n");
            begin_idx = curr_idx - 1;
        } else {
            begin_idx++;
            curr_idx = begin_idx + 1;
        }
    }
}

int main()
{
    int cnt;
    a = 100;
    b = 200;
    init_prime();
    cal_prime(b);
    cnt = output_prime(a, b);
    find_shulie(cnt);

    printf("\n\n");

    a = 200;
    b = 500;
    init_prime();
    cal_prime(b);
    cnt = output_prime(a, b);
    find_shulie(cnt);

    return 0;
}
