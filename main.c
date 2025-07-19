#include <stdio.h>

int binary(int x, int v[], int n);

int main() {
    int arraylen = 100;
    int v[arraylen];

    for (int i = 0; i < arraylen; i++) {
        v[i] = i*2;
    }

    for (int i = 0; i < arraylen; i++) {
        printf("%d\n", v[i]);
    }
    printf("\n");

    int res = binary(20, v, arraylen);

    printf("%d", res);

    return 0;
}

int binary(int x, int v[], int n) {
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low < high) {
        mid = (high + low) / 2;

        if (x < v[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    if (v[high] == x) {
        printf("a");
        return high;
    }
    if (v[high - 1] == x) {
        printf("b");
        return high - 1;
    }
    return -1;
}