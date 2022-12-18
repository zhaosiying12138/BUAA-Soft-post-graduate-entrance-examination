#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cnt = 0;
struct symbol {
    char name[1000];
};

struct symbol symbol_table[1000];

char is_start_chr(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return 1;
    if (ch >= 'A' && ch <= 'Z')
        return 1;
    if (ch == '_')
        return 1;
    return 0;
}

char is_continued_chr(char ch)
{
    if (ch >= 'a' && ch <= 'z')
        return 1;
    if (ch >= 'A' && ch <= 'Z')
        return 1;
    if (ch == '_')
        return 1;
    if (ch >= '0' && ch <= '9')
        return 1;
    return 0;
}

void my_strcpy(char *dest, const char *src_start, const char *src_end)
{
    for (const char *tmp = src_start; tmp < src_end; tmp++) {
        *dest = *tmp;
        dest++;
    }
    *dest = 0;
}

void analysis(const char *str)
{
    const char *cursor = str;
    int state = 0;
    const char *start_chr, *end_chr;
    while(*cursor) {
        if (state == 0) {
            if (is_start_chr(*cursor)) {
                state = 1;
                start_chr = cursor;
            } else {
            }
        } else {
            if (is_continued_chr(*cursor)) {
            } else {
                end_chr = cursor;
                my_strcpy(symbol_table[cnt].name, start_chr, end_chr);
                cnt++;
                state = 0;
            }
        }
        cursor++;
    }
//    for (int i = 0; i < cnt; i++) {
//        printf("%s,", symbol_table[i].name);
//    }
}

void query(const char *str)
{
    const char *cursor = str;
    int state = 0;
    const char *start_chr, *end_chr;
    char tmp_symbol[1000];
    while(*cursor) {
        if (state == 0) {
            if (is_start_chr(*cursor)) {
                state = 1;
                start_chr = cursor;
            } else {
            }
        } else {
            if (is_continued_chr(*cursor)) {
            } else {
                end_chr = cursor;
                my_strcpy(tmp_symbol, start_chr, end_chr);
                state = 0;

                int result = 0;
                for (int i = 1; i < cnt; i++) {
                    if (strcmp(tmp_symbol, symbol_table[i].name) == 0) {
                        result = 1;
                        break;
                    }
                }
                if (result == 0) {
                    printf("%s ", tmp_symbol);
                }
            }
        }
        cursor++;
    }

}

int main() {
//    char *str1 = "double x12, y=1, num_stu=89,a[30],*p;";
//    char *str2 = "Sum=num+x12*y";
//    char *str1 = "int int123    =456;";
//    char *str2 = "in = ab_ * (int123+++)";
    char tmp_str[1000];
    gets(tmp_str);
    analysis(tmp_str);
    gets(tmp_str);
    query(tmp_str);
}
