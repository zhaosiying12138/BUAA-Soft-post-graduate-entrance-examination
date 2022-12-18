#include <stdio.h>

struct Node {
    int addr;
    int size;
    struct Node *next;
    struct Node *prev;
};

struct Node *Head = NULL;
struct Node *Tail = NULL;
struct Node *Curr;

void insert_node(int addr, int size)
{
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->addr = addr;
    n->size = size;
    if (Head == NULL) {
        Head = n;
        n->next = n;
        n->prev = n;
        Curr = n;
    } else {
        n->next = Tail->next;
        n->prev = Tail;
        n->next->prev = n;
        n->prev->next = n;
    }
    Tail = n;
}

void alloc_block(int alloc_size)
{
    struct Node *selected_node = NULL;
    int left_size = -1;

    if (Curr == NULL)
        return;
    struct Node *tmpNode = Curr;
    do {
        if(tmpNode->size < alloc_size) {
            tmpNode = tmpNode->next;
            continue;
        }
        int tmp_left_size = tmpNode->size - alloc_size;
        if ((left_size == -1) || (tmp_left_size < left_size)) {
            left_size = tmp_left_size;
            selected_node = tmpNode;
        }
        tmpNode = tmpNode->next;
    } while(tmpNode != Curr);

    if (left_size > 0) {
        Curr = selected_node;
        Curr->size = left_size;
    } else if (left_size == 0) {
        // Maybe Buggy!
        Curr = selected_node->next;
        selected_node->prev->next = selected_node->next;
        selected_node->next->prev = selected_node->prev;
        free(selected_node);
    }
}

void print_all_nodes()
{
    if (Curr == NULL)
        return;
    struct Node *tmp = Curr;
    do {
        printf("%d %d\n", tmp->addr, tmp->size);
        tmp = tmp->next;
    } while(tmp != Curr);

}

int main() {
    insert_node(1024, 2048);
    insert_node(8192, 512);
    insert_node(16384, 1024);
    insert_node(32768, 8192);
    insert_node(65536, 8192);
    insert_node(77824, 1024);
    insert_node(80896, 3072);
    insert_node(86016, 1024);
    insert_node(91136, 5120);
    insert_node(99328, 512);
    insert_node(104448, 1024);
    insert_node(112640, 3072);

    alloc_block(1024);
    alloc_block(2560);
    alloc_block(10240);
    alloc_block(512);
    alloc_block(1024);
    alloc_block(6400);
    alloc_block(512);

    print_all_nodes();


    return 0;
}
