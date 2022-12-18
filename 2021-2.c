#include <stdio.h>

int n, m = 0;

struct Node {
    int id;
    struct Node *parent;
    struct Node *child[3];
};

struct myQueue {
    struct Node *data;
    struct myQueue *next;
};
struct myQueue* qHead = NULL;
struct myQueue* qTail = NULL;

void queue_push(struct Node *data)
{
    struct myQueue *q = (struct myQueue *)malloc(sizeof(struct myQueue));
    q->data = data;
    q->next = NULL;
    if (qTail != NULL) {
        qTail->next = q;
    }
    qTail = q;
    if (qHead == NULL) {
        qHead = q;
    }
}

struct Node * queue_pop()
{
    struct Node *res;
    if (qHead == NULL)
        return NULL;
    struct myQueue *q = qHead;
    res = qHead->data;
    qHead = qHead->next;
    free(q);
    if (qHead == NULL)
        qTail = NULL;
    return res;
}

char queue_is_empty()
{
    if (qHead == NULL)
        return 1;
    else
        return 0;
}

struct Cmd {
    int id;
    int priority;
};
int cmd_idx = 0;

struct Node* node_map[10000];
struct Node* root;
struct Cmd cmd_array[10000];
int bfs_trace[10000];
int bfs_idx = 0;

void insert_node(int p, int c1, int c2, int c3, char is_root)
{
    struct Node* p_node, *c1_node, *c2_node, *c3_node;
    if (is_root) {
        p_node = (struct Node *)malloc(sizeof(struct Node));
        if (p < 100)
            m++;
        p_node->id = p;
        p_node->parent = NULL;
        p_node->child[0] = NULL;
        p_node->child[1] = NULL;
        p_node->child[2] = NULL;
        root = p_node;
        node_map[p] = p_node;
    } else {
        p_node = node_map[p];
    }
    if (c1 != -1) {
        c1_node = (struct Node *)malloc(sizeof(struct Node));
        if (c1 < 100)
            m++;
        c1_node->id = c1;
        c1_node->parent = p_node;
        c1_node->child[0] = NULL;
        c1_node->child[1] = NULL;
        c1_node->child[2] = NULL;
        p_node->child[0] = c1_node;
        node_map[c1] = c1_node;
    }
    if (c2 != -1) {
        c2_node = (struct Node *)malloc(sizeof(struct Node));
        if (c2 < 100)
            m++;
        c2_node->id = c2;
        c2_node->parent = p_node;
        c2_node->child[0] = NULL;
        c2_node->child[1] = NULL;
        c2_node->child[2] = NULL;
        p_node->child[1] = c2_node;
        node_map[c2] = c2_node;
    }
    if (c3 != -1) {
        c3_node = (struct Node *)malloc(sizeof(struct Node));
        if (c3 < 100)
            m++;
        c3_node->id = c3;
        c3_node->parent = p_node;
        c3_node->child[0] = NULL;
        c3_node->child[1] = NULL;
        c3_node->child[2] = NULL;
        p_node->child[2] = c3_node;
        node_map[c3] = c3_node;
    }
}

void insert_cmd(int id, int priority)
{
    cmd_array[cmd_idx].id = id;
    cmd_array[cmd_idx].priority = priority;
    cmd_idx++;
}

static void swap_cmd(struct Cmd* cmd1, struct Cmd* cmd2)
{
    int tmp_id = cmd1->id;
    int tmp_priority = cmd1->priority;

    cmd1->id = cmd2->id;
    cmd1->priority = cmd2->priority;
    cmd2->id = tmp_id;
    cmd2->priority = tmp_priority;
}

void sort_cmd()
{
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            if (cmd_array[j].priority > cmd_array[j+1].priority) {
                swap_cmd(&cmd_array[j], &cmd_array[j+1]);
            }
        }
    }
}

void BFS(struct Node* root)
{
    queue_push(root);
    while(!queue_is_empty()) {
        struct Node* n = queue_pop();
        //Visit(n)
        if (n->id < 100) {
            bfs_trace[bfs_idx] = n->id;
            bfs_idx++;
        } else {
            struct Node* c[3];
            for (int i = 0; i < 3; i++) {
                if (n->child[i] != NULL) {
                    queue_push(n->child[i]);
                }
            }
        }
    }
}

int main() {
    n = 12;
    insert_node(100, 101, 102, 103, 1);
    insert_node(103, 14, 108, 13, 0);
    insert_node(101, 5, 104, 6, 0);
    insert_node(104, 7, 8, -1, 0);
    insert_node(102, 105, 106, 107, 0);
    insert_node(106, 1, 110, 2, 0);
    insert_node(108, 16, 15, -1, 0);
    insert_node(107, 18, 111, 17, 0);
    insert_node(110, 3, 4, -1, 0);
    insert_node(105, 9, 109, 10, 0);
    insert_node(111, 20, 19, -1, 0);
    insert_node(109, 11, 12, -1, 0);


    insert_cmd(17, 865);
    insert_cmd(5, 668);
    insert_cmd(20, 3000);
    insert_cmd(13, 1020);
    insert_cmd(11, 980);
    insert_cmd(8, 2202);
    insert_cmd(15, 1897);
    insert_cmd(6, 1001);
    insert_cmd(14, 922);
    insert_cmd(7, 2178);
    insert_cmd(19, 2189);
    insert_cmd(1, 1267);
    insert_cmd(12, 3281);
    insert_cmd(2, 980);
    insert_cmd(18, 1020);
    insert_cmd(10, 980);
    insert_cmd(3, 1876);
    insert_cmd(9, 1197);
    insert_cmd(16, 980);
    insert_cmd(4, 576);

    sort_cmd();

    BFS(root);

//    printf("m = %d, bfs_idx = %d\n", m, bfs_idx);

    for (int i = 0; i < m; i++) {
        printf("%d %d \n", cmd_array[m - i -1].id, bfs_trace[i]);
    }

    return 0;
}
