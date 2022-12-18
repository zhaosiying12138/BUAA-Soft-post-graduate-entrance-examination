#include <stdio.h>
#include <stdlib.h>

int tmp_factor[1000000];
int idx;

int xiangqin(int x)
{
    idx = 0;
    int res = 1;
    tmp_factor[0] = 1;
    for (int i = 2; i <= x / 2; i++) {
        int yushu = x % i;
        if (yushu == 0) {
            tmp_factor[idx] = i;
            idx++;
        }
    }
    printf("%d, 1", x);
    for (int i = 0; i < idx; i++) {
        printf("+%d", tmp_factor[i]);
        res += tmp_factor[i];
    }
    printf("=%d\n", res);

    return res;
}

int main() {
    int n1, n2;
    scanf("%d%d", &n1, &n2);

    int res1 = xiangqin(n1);
    int res2 = xiangqin(n2);

    if ((res1 == n2) && (res2 == n1))
        printf("1\n");
    else
        printf("0\n");

    return 0;
}

