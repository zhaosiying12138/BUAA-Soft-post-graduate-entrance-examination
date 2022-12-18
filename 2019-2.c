#include <stdio.h>

#if 0
int main()
{
    int a, b;
    while(scanf("%d%d", &a, &b) != EOF)
        printf("%d\n", a+b);
    return 0;
}
#endif // 0

int n, m;

struct Node {
    int id;
    struct Node *parent;
    struct Node *child[3];
};

struct Cmd {
    int id;
    int priority;
};
int cmd_idx = 0;

struct Node* node_map[10000];
struct Node* root;
struct Cmd cmd_array[10000];
char is_visited[10000];
int way_trace[10000];

void insert_node(int p, int c1, int c2, int c3, char is_root)
{
    struct Node* p_node, *c1_node, *c2_node, *c3_node;
    if (is_root) {
        p_node = (struct Node *)malloc(sizeof(struct Node));
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

char findway(struct Node* start_node, int end_id, int level, int fromroot)
{
    int start_id = start_node->id;
    way_trace[level] = start_id;
    is_visited[start_id] = 1;

    if (start_id == end_id) {
        int i;
        if (fromroot == 0)
            i = 0;
        else
            i = 1;
        for (; i <= level; i++) {
            printf("%d ", way_trace[i]);
        }
        printf("\n");
        return 1;
    }

    struct Node* adj_node[4];
    adj_node[0] = start_node->child[0];
    adj_node[1] = start_node->child[1];
    adj_node[2] = start_node->child[2];
    adj_node[3] = start_node->parent;

    for (int i = 0; i < 4; i++) {
        if (adj_node[i] == NULL)
            continue;
        int adj_id = adj_node[i]->id;
        if (is_visited[adj_id] == 0) {
            char success = findway(adj_node[i], end_id, level + 1, fromroot);
            if (success)
                return 1;
        }
    }
    return 0;
}

static void clear_is_visited()
{
    for (int i = 0; i < 10000; i++)
        is_visited[i] = 0;
}

int main() {
#if 0
    insert_node(100, 101, 102, 103, 1);
    insert_node(101, 1, 104, 2, 0);
    insert_node(102, 3, 105, 4, 0);
    insert_node(103, 5, 6, -1, 0);
    insert_node(104, 7, 8, -1, 0);
    insert_node(105, 9, 10, -1, 0);

    m = 5;
    insert_cmd(7, 7);
    insert_cmd(9, 3);
    insert_cmd(6, 2);
    insert_cmd(8, 1);
    insert_cmd(4, 5);
#endif // 0
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int p, c1, c2, c3;
        scanf("%d%d%d%d", &p, &c1, &c2, &c3);
        insert_node(p, c1, c2, c3, i == 0);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int id, priority;
        scanf("%d%d", &id, &priority);
        insert_cmd(id, priority);
    }

    sort_cmd();
    int start_id = root->id;
    for (int i = 0; i < m; i++) {
        int end_id = cmd_array[i].id;
        clear_is_visited();
        findway(node_map[start_id], end_id, 0, i);
        start_id = end_id;
    }
    clear_is_visited();
    findway(node_map[start_id], root->id, 0, 1);

    return 0;
}
