#include <stdio.h>
#include <stdlib.h>

int n;

struct Node {
    int data;
    int idx;
};

struct Node node_array[1000000];

void swap_node(struct Node *n1, struct Node *n2)
{
    int tmp_data = n1->data;
    int tmp_idx = n1->idx;

    n1->data = n2->data;
    n1->idx = n2->idx;

    n2->data = tmp_data;
    n2->idx = tmp_idx;
}

void bubble_sort()
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (node_array[j].data > node_array[j + 1].data) {
                swap_node(&node_array[j], &node_array[j + 1]);
            }
        }
    }
}

int main() {

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        node_array[i].idx = i + 1;
        scanf("%d", &node_array[i].data);
    }

    bubble_sort();

    if (n % 2 == 1) {
        int idx = n / 2;
        printf("%d %d\n", node_array[idx].data, node_array[idx].idx);
    } else {
        int idx = n / 2;
        printf("%d %d\n", node_array[idx-1].data, node_array[idx-1].idx);
        printf("%d %d\n", node_array[idx].data, node_array[idx].idx);
    }

    return 0;
}
