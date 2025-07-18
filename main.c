#include <stdio.h>
#include <math.h>

void gethexinput(char output[]);
int htoi(char hx[]);

int main(){
    char hex[100];

    for (int i = 0; i < 100; ++i) {
        hex[i] = '0';
    }

    gethexinput(hex);

    int dec = htoi(hex);

    printf("%d\n", dec);

    return 0;
}

void gethexinput(char output[]){
    char c;
    int cnt = 0;
    char interm[100];

    for (int i = 0; i < 100; ++i) {
        interm[i] = '0';
    }

    for (int i = 0; i < 100 && ((c = getchar()) != '\n'); ++i) {
        interm[i] = c;
        ++cnt;
    }

    for (int i = cnt; i > -1; --i) {
        output[cnt - i] = interm[i - 1];
    }

    for (int i = cnt; i < 100; ++i) {
        output[i] = '0';
    }
}

int htoi(char hx[]){
    char c;
    long int dec = 0;
    for (int i = 0; i < 100; ++i) {
        c = hx[i];
        char decchar;

        if (c >= '0' && c <= '9') {
            decchar = c - '0'; 
        } else if (c >= 'A' && c <= 'Z') {
            decchar = 10 + c - 'A';
        } else if (c >= 'a' && c <= 'z') {
            decchar = 10 + c - 'a';
        } else {
            printf("something went wrong, only 0-9, a-z, A-Z are supported");
            return 0;
        }

        dec = dec + decchar * pow(16.0, i);
    }
    return dec;
}