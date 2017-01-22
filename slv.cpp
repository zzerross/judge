#include <stdio.h>

// #define dbg

#define clk

#ifdef clk
#include <time.h>
#define _c0(x) clock_t _c##x = clock()
#define _c1(x) printf("_c" #x ": %.3lfms\n", (clock() - _c##x) / (double) CLOCKS_PER_SEC)
#else
#define _c0(x)
#define _c1(x)
#endif

#ifdef dbg
#define _pr printf
#else
#define _pr
#endif

#define is 20
#define ds 2
#define ss (1 << 10)

int tc, in, hn, ea[is+1][is+1], ha[is+1][is+1][ds], ra[is+1][is+1];
int ca[is+1][is+1][ds], sa[is+1][is+1][ds];

void _ha() {
#ifdef dbg
    for (int d = 0; d < ds; d++) {
        _pr(" ha: %2d\n", d);

        for (int i = 1; i <= in; i++) {
            _pr("%3d: ", i);

            for (int j = 1; j <= in; j++)
                _pr("%2d ", ha[i][j][d]);

            _pr("\n");
        }
    }
#endif
}

void _ra() {
#ifdef dbg
    _pr(" ra: \n");

    for (int i = 1; i <= in; i++) {
        _pr("%3d: ", i);

        for (int j = 1; j <= in; j++)
            _pr("%2d ", ra[i][j]);

        _pr("\n");
    }
#endif
}

int sum(int s) {
    int r = 0;

    for (int i = 1; i <= 9; i++)
        if (s & (1 << i))
            r += i;

    return r;
}

int cnt(int s) {
    int r = 0;

    for (int i = 1; i <= 9; i++)
        if (s & (1 << i))
            r++;

    return r;
}

int slv() {
    int y, x, d, k, s = 0, c = in;

    _ra();

    for (int i = 1; i <= in; i++) {
        for (int j = 1; j <= in; j++) {
            if (ea[i][j] && !ra[i][j]) {
                if (c > ca[i][j][0]) {
                    c = ca[i][j][0];
                    y = i;
                    x = j;
                    d = 0;
                } else if (c > ca[i][j][1]) {
                    c = ca[i][j][1];
                    y = i;
                    x = j;
                    d = 1;
                }
            }

            if (s)
                continue;

            if (s = ha[i][j][0]) {
                for (k = i + 1; s > 0 && ea[k][j] && k <= in; k++)
                    s -= ra[k][j];
            } else if (s = ha[i][j][1]) {
                for (k = j + 1; ea[i][k] && k <= in; k++)
                    s -= ra[i][k];
            }
        }
    }

    if (!s)
        return 1;

nxt:
    if (y > in)
        return 0;

    for (int k = 1; k <= 9; k++) {
        if (sa[y][x][d] & (1 << k)) {
            ra[y][x] = k;

            if (slv())
                return 1;

            ra[y][x] = 0;
        }
    }

    return 0;
}

int main() {
    _c0(x);

    for (scanf("%d", &tc); tc--;) {
        scanf("%d", &in);

        for (int i = 1; i <= in; i++)
            for (int j = 1; j <= in; j++)
                scanf("%d", &ea[i][j]);

        scanf("%d", &hn);

        for (int i = 1; i <= in; i++) {
            for (int j = 1; j <= in; j++) {
                ha[i][j][0] = ha[i][j][1] = ra[i][j] = 0;
                ca[i][j][0] = ca[i][j][1] = 0;
                sa[i][j][0] = sa[i][j][1] = 0;
            }
        }

        for (int h = 0, i, j, d, s; h < hn; h++) {
            scanf("%d %d %d %d", &i, &j, &d, &s);

            ha[i][j][d] = s;
        }

        for (int i = 1, c, k; i <= in; i++)  {
            for (int j = 1; j <= in; j++) {
                for (int d = 0; d < 2; d++) {
                    if (!ha[i][j][d])
                        continue;

                    if (d) {
                        for (c = 0, k = j + 1; ea[i][k] && k <= in; k++)
                            c++;
                    } else {
                        for (c = 0, k = i + 1; ea[k][j] && k <= in; k++)
                            c++;
                    }

                    for (int s = 0; s < ss; s += 2) {
                        if (ha[i][j][d] == sum(s) && cnt(s) == c) {
                            ca[i][j][d] = c;
                            sa[i][j][d] = s;

                            printf("   : %2d, c=%d s=%03x\n", ha[i][j][d], c, s);
                        }
                    }
                }
            }
        }

        _ha();

        if (slv()) {
            for (int i = 1; i <= in; i++) {
                for (int j = 1; j <= in; j++)
                    printf("%d ", ra[i][j]);

                printf("\n");
            }
        }
    }

    _c1(x);

    return 0;
}
