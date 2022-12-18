#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(int n)
{
    int bak_n = n;
    int tmp = 0;
    int init_flag = 1;
    int zero_cnt = 0;
    while (n) {
        int yushu = n % 10;
        tmp = 10 * tmp + yushu;
        n /= 10;
        if (init_flag) {
            if (yushu == 0) {
                zero_cnt++;
            } else {
                init_flag = 0;
            }
        }
    }
    n = bak_n;
    if (tmp % n == 0) {
        printf("%d*%d=%d\n", n, tmp / n, tmp);
    } else {
        printf("%d ", n);
        for (int i = 0; i < zero_cnt; i++) {
            printf("0");
        }
        printf("%d\n", tmp);
    }
}


int main() {
    reverse(1089);
    reverse(9801);
    reverse(1234);
    reverse(23200);

    return 0;
}
