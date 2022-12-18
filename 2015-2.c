#include <stdio.h>
#include <stdlib.h>

struct window_node {
    int id;
    int rd_x;
    int rd_y;
    int lu_x;
    int lu_y;
    struct window_node *prev;
    struct window_node *next;
};

struct window_node Tail;
struct window_node *Head = &Tail;

void insert_window(int id, int rd_x, int rd_y, int lu_x, int lu_y)
{
    struct window_node *n = (struct window_node *)malloc(sizeof(struct window_node));
    memset(n, 0, sizeof(struct window_node));
    n->id = id;
    n->rd_x = rd_x;
    n->rd_y = rd_y;
    n->lu_x = lu_x;
    n->lu_y = lu_y;

    n->prev = NULL;
    n->next = Head;
    Head->prev = n;
    Head = n;
}

struct window_node * search_window(int x, int y)
{
    struct window_node *tmp_node = &Tail;
    while (tmp_node->prev != NULL) {
        tmp_node = tmp_node->prev;
        if ((x <= tmp_node->rd_x && x >= tmp_node->lu_x) &&
        (y >= tmp_node->rd_y && y <= tmp_node->lu_y)) {
            return tmp_node;
        }
    }
}

void click(int x, int y)
{
    struct window_node *n = search_window(x, y);
    if (n->prev != NULL) {
        n->prev->next = n->next;
    }
    n->next->prev = n->prev;
    n->prev = Tail.prev;
    n->next = &Tail;
    Tail.prev = n;
    if (n->prev != NULL) {
        n->prev->next = n;
    }
}

void print_window()
{
    struct window_node *tmp_node = &Tail;
    while (tmp_node->prev != NULL) {
        tmp_node = tmp_node->prev;
        printf("%d ", tmp_node->id);
    }
    printf("\n");
}

int main() {
#if 1
    insert_window(1, 5, 1, 1, 5);
    insert_window(2, 7, 1, 3, 5);
    click(1, 2);
    click(4, 3);
    click(6, 4);
#endif // 0

#if 0
    insert_window(3, 5, 1, 1, 4);
    insert_window(4, 7, 3, 3, 6);
    insert_window(2, 8, 2, 4, 5);
    click(5, 3);    click(8, 4);
    click(4, 4);
#endif // 0

    print_window();

    return 0;
}

