#include <stdio.h>
#include <stdlib.h>

int n;
struct Node {
    int no;
    int depth;
    struct Node *child[3];
};

struct Node* node_map[10000];

struct Node* root = NULL;

struct Queue {
    struct Node *data;
    struct Queue *next;
};

struct Queue *qHead = NULL;
struct Queue *qTail = NULL;

void queue_push(struct Node *n)
{
    struct Queue *qNode = (struct Queue *)malloc(sizeof(struct Queue));
    memset(qNode, 0, sizeof(*qNode));
    qNode->data = n;
 //   qNode->next = NULL;
    if (qTail == NULL) {
        qHead = qNode;
        qTail = qNode;
    } else {
        qTail->next = qNode;
        qTail = qNode;
    }
}

struct Node* queue_pop()
{
    if (qHead == NULL)
        return NULL;

    struct Node *res = qHead->data;
    qHead = qHead->next;
    if (qHead == NULL)
        qTail = NULL;
    return res;
}

char is_queue_empty()
{
    return qHead == NULL;
}

int cnt_childrens(struct Node *node)
{
    int cnt = 0;
    for (int i = 0; i < 3; i++) {
        if (node->child[i] != NULL) {
            cnt++;
        }
    }
    return cnt;
}

void insert_node(int p, int c1, int c2, int c3)
{
    struct Node *p_node, *c1_node, *c2_node, *c3_node;
    int p_depth;
    if (root == NULL) {
        p_node = (struct Node *)malloc(sizeof(struct Node));
        p_node->no = p;
        p_node->depth = 0;
        p_node->child[0] = NULL;
        p_node->child[1] = NULL;
        p_node->child[2] = NULL;
        p_depth = 0;
        node_map[p] = p_node;
        root = p_node;
    } else {
        p_node = node_map[p];
        p_depth = p_node->depth;
    }
    if (c1 != -1) {
        c1_node = (struct Node *)malloc(sizeof(struct Node));
        c1_node->child[0] = NULL;
        c1_node->child[1] = NULL;
        c1_node->child[2] = NULL;
        c1_node->no = c1;
        c1_node->depth = p_depth + 1;
        node_map[c1] = c1_node;
        p_node->child[0] = c1_node;
    }
    if (c2 != -1) {
        c2_node = (struct Node *)malloc(sizeof(struct Node));
        c2_node->child[0] = NULL;
        c2_node->child[1] = NULL;
        c2_node->child[2] = NULL;
        c2_node->no = c2;
        c2_node->depth = p_depth + 1;
        node_map[c2] = c2_node;
        p_node->child[1] = c2_node;
    }
    if (c3 != -1) {
        c3_node = (struct Node *)malloc(sizeof(struct Node));
        c3_node->child[0] = NULL;
        c3_node->child[1] = NULL;
        c3_node->child[2] = NULL;
        c3_node->no = c3;
        c3_node->depth = p_depth + 1;
        node_map[c3] = c3_node;
        p_node->child[2] = c3_node;
    }
}

void BFS(struct Node *n)
{
    queue_push(n);
    int best_cnt_childrens = -1;
    int best_depth = -1;
    int best_no = -1;
    int best_times;
    int curr_times = 0;
    while(!is_queue_empty()) {
        struct Node *tmp_node = queue_pop();
        // Visit_Node(tmp_node);
        #if 1
        curr_times++;
        int tmp_cnt_childerns = cnt_childrens(tmp_node);
        int tmp_depth = tmp_node->depth;
        if (tmp_cnt_childerns > best_cnt_childrens) {
            best_cnt_childrens = tmp_cnt_childerns;
            best_depth = tmp_depth;
            best_no = tmp_node->no;
            best_times= curr_times;
        } else if (tmp_cnt_childerns == best_cnt_childrens) {
            if (tmp_depth > best_depth) {
                best_depth = tmp_depth;
                best_no = tmp_node->no;
                best_times= curr_times;
            }
        }
        #else
        printf("%d\n", tmp_node->no);
        #endif

        for (int i = 0; i < 3; i++) {
            if (tmp_node->child[i] != NULL) {
                queue_push(tmp_node->child[i]);
            }
        }
    }
    printf("%d %d\n", best_no, best_times);
}

int main() {
#if 0
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int p, c1, c2, c3;
        scanf("%d%d%d%d", &p, &c1, &c2, &c3);
        insert_node(p, c1, c2, c3);
    }
#else

#endif

    n = 4;
    insert_node(10, 9, -1, 7);
    insert_node(9, 6, 5, -1);
    insert_node(7, -1, 3, 11);
    insert_node(11, -1, 14, -1);

    BFS(root);

    return 0;
}
