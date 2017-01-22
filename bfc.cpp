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

int tc, in, hn, ea[is+1][is+1], ha[is+1][is+1][ds], ra[is+1][is+1];

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

int end() {
    int k, s, r = 0;

    _ra();

    r = 1;

out:
    _pr("end: r=%d\n", r);

    return r;
}

int slv() {
    int i, j, k, s = 0;

    _ra();

    for (i = 1; i <= in; i++) {
        for (j = 1; j <= in; j++) {
            if (ea[i][j] && !ra[i][j])
                goto nxt;

            if (s)
                continue;

            if (s = ha[i][j][0]) {
                _pr("end: %d,%d h hint ", i, j);

                for (k = i + 1; s > 0 && ea[k][j] && k <= in; k++)
                    s -= ra[k][j];

                _pr("s=%d\n", s);
            } else if (s = ha[i][j][1]) {
                for (k = j + 1; ea[i][k] && k <= in; k++)
                    s -= ra[i][k];
            }
        }
    }

    if (!s)
        return 1;

nxt:
    _pr("slv: %d,%d\n", i, j);

    if (i > in)
        return 0;

    for (int k = 1; k <= 9; k++) {
        ra[i][j] = k;

        if (slv())
            return 1;

        ra[i][j] = 0;
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

        for (int i = 1; i <= in; i++)
            for (int j = 1; j <= in; j++)
                ha[i][j][0] = ha[i][j][1] = ra[i][j] = 0;

        for (int h = 0, i, j, d, s; h < hn; h++) {
            scanf("%d %d %d %d", &i, &j, &d, &s);

            ha[i][j][d] = s;
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
