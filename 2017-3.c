#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cnt = 0;

struct Member {
    char name[100];
    struct Member *child[2];
    struct Member *parent;
    int depth;
};

struct Member m[100000];

int spill_str(const char *str, char *dst1, char *dst2, char *dst3)
{
    const char *cursor = str;
    while(*cursor != ' ') {
        *dst1++ = *cursor++;
    }
    *dst1 = 0;
    cursor++;
    while((*cursor != ' ') && (*cursor)) {
        *dst2++ = *cursor++;
    }
    *dst2 = 0;
    if (*cursor == 0) {
        *dst3 = 0;
        return 2;
    } else {
        cursor++;
        while(*cursor) {
            *dst3++ = *cursor++;
        }
        *dst3 = 0;
        return 3;
    }
}

struct Member* find_member(const char *str)
{
    for (int i = 0; i < cnt; i++) {
        if (strcmp(m[i].name, str) == 0) {
            return &m[i];
        }
    }
    return NULL;
}

void insert_member(const char *p, const char *c1, const char *c2)
{
    struct Member *p_node;
    if (cnt == 0) {
        p_node = &m[cnt];
        strcpy(p_node->name, p);
        p_node->depth = 0;
        cnt = 1;
    } else {
        p_node = find_member(p);
    }
    struct Member *c1_node, *c2_node;
    c1_node = &m[cnt];
    strcpy(c1_node->name, c1);
    c1_node->parent = p_node;
    c1_node->depth = p_node->depth + 1;
    cnt++;
    c2_node = &m[cnt];
    strcpy(c2_node->name, c2);
    c2_node->parent = p_node;
    c2_node->depth = p_node->depth + 1;
    cnt++;
}

void query_member(const char *str1, const char *str2)
{
    struct Member *m1 = find_member(str1);
    struct Member *m2 = find_member(str2);
    int m1_depth = m1->depth;
    int m2_depth = m2->depth;
    int depth_diff = 0;
    if (m1_depth > m2_depth) {
        depth_diff = m1_depth - m2_depth;
        for (int i = 0; i < depth_diff; i++) {
            m1 = m1->parent;
        }
    } else if (m1_depth < m2_depth) {
        depth_diff = m2_depth - m1_depth;
        for (int i = 0; i < depth_diff; i++) {
            m2 = m2->parent;
        }
    }
    while (strcmp(m1->name, m2->name) != 0) {
        m1 = m1->parent;
        m2 = m2->parent;
    }
    printf("%s %d\n", m1->name, depth_diff);
}

int main() {
    char tmp_str[300];
    char tmp_str1[100];
    char tmp_str2[100];
    char tmp_str3[100];
 //   scanf("%s%s%s", tmp_str1, tmp_str2, tmp_str3);
 //   printf("%s,%s,%s\n", tmp_str1, tmp_str2, tmp_str3);
//    gets(tmp_str);
#if 0
    spill_str("Ye Shu Ba", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Shu Ge Mei1", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Ba Self Mei2", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Ge Son1 Son2", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Son2 Mei1", tmp_str1, tmp_str2, tmp_str3);
    query_member(tmp_str1, tmp_str2);
#endif // 0

#if 0
    spill_str("Ye Shu Ba", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Shu Ge Mei1", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Ba Self Mei2", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Ge Son1 Son2", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Son2 Self", tmp_str1, tmp_str2, tmp_str3);
    query_member(tmp_str1, tmp_str2);
#endif // 0

#if 0
    spill_str("Ye Shu Ba", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Shu Ge Mei1", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Ba Self Mei2", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Ge Son1 Son2", tmp_str1, tmp_str2, tmp_str3);
    insert_member(tmp_str1, tmp_str2, tmp_str3);
    spill_str("Son2 Son2", tmp_str1, tmp_str2, tmp_str3);
    query_member(tmp_str1, tmp_str2);
#endif // 0

    while(1) {
        gets(tmp_str);
        int spill_strs_cnt = spill_str(tmp_str, tmp_str1, tmp_str2, tmp_str3);
        if (spill_strs_cnt == 3) {
            insert_member(tmp_str1, tmp_str2, tmp_str3);
        } else {
            query_member(tmp_str1, tmp_str2);
            break;
        }
    }
}
