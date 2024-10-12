#include <stdio.h>
#include <stdlib.h>
#include "timelib.h"

#define zero 0
#define one 1
#define two 2
#define three 3
#define four 4
#define five 5
#define six 6
#define seven 7
#define eight 8
#define nine 9
#define thirtyone 31
#define fifteen 15
#define ten 10
#define eleven 11
#define twelve 12
#define startyear 1970

int main() {
    int c = zero;
    scanf("%d", &c);
    if (c == seven) {
        int n = zero;
        unsigned int x = zero;
        scanf("%d", &n);
        unsigned int *v = calloc(n, sizeof(unsigned int));
        for (int i = zero; i < n; ++i) {
            scanf("%d", &x);
            v[i] |= x;
        }
        for (int i = zero; i < n; ++i) {
            for (int j = i + one; j < n; ++j) {
                if (v[i] > v[j]) {
                    unsigned int aux = v[i];
                    v[i] = v[j];
                    v[j] = aux;
                }
            }
        }
        for (int i = zero; i < n; ++i) {
            unsigned int m = thirtyone;
            printf("%d ", v[i]&m);
            m = fifteen;
            m <<= five;
            switch ((v[i]&m) >> five) {
                case one:
                    printf("ianuarie ");
                    break;
                case two:
                    printf("februarie ");
                    break;
                case three:
                    printf("martie ");
                    break;
                case four:
                    printf("aprilie ");
                    break;
                case five:
                    printf("mai ");
                    break;
                case six:
                    printf("iunie ");
                    break;
                case seven:
                    printf("iulie ");
                    break;
                case eight:
                    printf("august ");
                    break;
                case nine:
                    printf("septembrie ");
                    break;
                case ten:
                    printf("octombrie ");
                    break;
                case eleven:
                    printf("noiembrie ");
                    break;
                case twelve:
                    printf("decembrie ");
                    break;
            }
            m = thirtyone * two + one;
            m <<= nine;
            printf("%d\n", ((v[i] & m) >> nine) + startyear);
        }
        free(v);
    } else {
        int n = zero;
        scanf("%d", &n);
        int m = n * fifteen / (thirtyone + one);
        if (n * fifteen % (thirtyone + one))
            m++;
        unsigned int *x = calloc(m, sizeof(unsigned int));
        unsigned int *cate = calloc(m, sizeof(unsigned int));
        unsigned int *c_control = calloc(m, sizeof(unsigned int));
        unsigned int *v = calloc(n, sizeof(unsigned int));
        for (int i = zero; i < m; ++i) {
            scanf("%u", &x[i]);
            unsigned int aux = one;
            int cnt = zero;
            for (int j = zero; j < (thirtyone + one); ++j) {
                if ((aux << j) & x[i])
                    cnt++;
            }
            cate[i] = cnt % two;
        }
        unsigned int control = zero;
        int k = m / (thirtyone + one);
        int cnt_control = zero;
        if (m % (thirtyone + one)) k++;
        for (int l = zero; l < k; ++l) {
            scanf("%u", &control);
            for (int i = zero; i < (thirtyone + one) && cnt_control < m; ++i) {
                c_control[cnt_control++] = control % two;
                control /= two;
            }
        }
        int cnt = zero;
        int p = thirtyone + one;
        int q = fifteen;
        int ajutor = zero;
        int i = zero;
        while (ajutor < n * fifteen) {
            if (p >= q) {
                unsigned int mask = one;
                unsigned int aux = zero;
                for (int j = zero; j < q; ++j) {
                    aux |= mask&x[i];
                    mask <<= one;
                }
                if (cate[i] == c_control[i])
                    v[cnt++] = aux;
                x[i]>>=fifteen;
                p -= q;
                ajutor += fifteen;
            } else {
                unsigned int mask = one;
                unsigned int aux = zero;
                for (int j = zero; j < p; ++j) {
                    aux |= mask&x[i];
                    mask <<= one;
                }
                i++;
                mask = one;
                for (int j = zero; j < q - p; ++j) {
                    aux |= ((mask&x[i]) << p);
                    mask <<= one;
                }
                x[i] >>= (q - p);
                if ((cate[i - one] == c_control[i - one] &&
                cate[i] == c_control[i]) || (p == zero && cate[i] == c_control[i]))
                    v[cnt++] = aux;
                p = (thirtyone + one) - (q - p);
                ajutor += fifteen;
            }
        }
        for (int i = zero; i < cnt; ++i) {
            for (int j = i + one; j < cnt; ++j) {
                if (v[i] > v[j]) {
                    unsigned int aux = v[i];
                    v[i] = v[j];
                    v[j] = aux;
                }
            }
        }
        for (int i = zero; i < cnt; ++i) {
            unsigned int m = thirtyone;
            printf("%d ", v[i]&m);
            m = fifteen;
            m <<= five;
            switch ((v[i]&m) >> five) {
                case one:
                    printf("ianuarie ");
                    break;
                case two:
                    printf("februarie ");
                    break;
                case three:
                    printf("martie ");
                    break;
                case four:
                    printf("aprilie ");
                    break;
                case five:
                    printf("mai ");
                    break;
                case six:
                    printf("iunie ");
                    break;
                case seven:
                    printf("iulie ");
                    break;
                case eight:
                    printf("august ");
                    break;
                case nine:
                    printf("septembrie ");
                    break;
                case ten:
                    printf("octombrie ");
                    break;
                case eleven:
                    printf("noiembrie ");
                    break;
                case twelve:
                    printf("decembrie ");
                    break;
            }
            m = thirtyone * two + one;
            m <<= nine;
            printf("%d\n", ((v[i]&m) >> nine) + startyear);
        }
        free(v);
        free(x);
        free(cate);
        free(c_control);
    }
    return 0;
}
