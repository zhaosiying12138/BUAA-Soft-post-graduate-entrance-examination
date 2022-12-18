#include <stdio.h>

struct Line {
    int lx;
    int ly;
    int rx;
    int ry;
};

struct Line Line[10000];
int n = 0;

void insert_line(int lx, int ly, int rx, int ry)
{
    Line[n].lx = lx;
    Line[n].ly = ly;
    Line[n].rx = rx;
    Line[n].ry = ry;
    n++;
}

int cnt_line_seg(struct Line *l)
{
    int tmp_rx = l->rx;
    int tmp_ry = l->ry;
    int tmp_length = -1;
    for (int i = 0; i < n; i++) {
        if ((Line[i].lx == tmp_rx) && (Line[i].ly == tmp_ry)) {
            int length = cnt_line_seg(&Line[i]);
            if (length > tmp_length) {
                tmp_length = length;
            }
        }
    }
    if (tmp_length == -1)
        return 1;

    return tmp_length + 1;
}

int main() {
#if 0
    insert_line(1, 2, 2, 3);
    insert_line(2, 3, 3, 4);
    insert_line(3, 4, 4, 1);
    insert_line(2, 3, 5, 6);
#endif // 0

#if 0
    insert_line(1, 3, 2, 4);
    insert_line(2, 4, 3, 3);
    insert_line(3, 3, 7, 2);
    insert_line(2, 4, 4, 1);
    insert_line(4, 1, 5, 6);
    insert_line(5, 6, 6, 5);
#endif // 0

#if 0
    insert_line(1, 3, 2, 4);
    insert_line(2, 4, 7, 2);
    insert_line(3, 3, 7, 2);
#endif // 0

    insert_line(1, 3, 2, 4);
    insert_line(3, 3, 7, 2);
    insert_line(2, 4, 3, 3);

    int tmp_length = -1;
    int tmp_idx = -1;

    for (int i = 0; i < n; i++) {
        int length = cnt_line_seg(&Line[i]);
        if (length > tmp_length) {
            tmp_idx = i;
            tmp_length = length;
        }
    }
    printf("%d %d %d", tmp_length, Line[tmp_idx].lx, Line[tmp_idx].ly);

    return 0;
}
