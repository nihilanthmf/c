#include <stdio.h>

double atof(char s[]);

int main() {
    double a = atof("-345.135");
    printf("%g", a);

    return 0;
}

int converttoi(char c) {
    return c - '0';
}

double atof(char s[]) {
    int sign = 1, power = 0;
    double number = 0;

    if (s[0] == '-') {
        sign = -1;
    }
    for (int i = sign == -1 ? 1 : 0; s[i] != '\0'; ++i) {
        if (s[i] == '.') {
            ++i;
            power = 1;
        }

        if (power != 0) { // if number after .
            power *= 10;
        }
        number = number * 10 + converttoi(s[i]);
    }
    return sign * number / power;
}