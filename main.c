#include <stdio.h>
#define MAXLEN 1000

void inputline(char s[]);
int formats(char input[], char output[]);

int main(){
    // char input[MAXLEN];
    // char output[MAXLEN];

    // inputline(input);
    // formats(input, output); // fuck
    // // hwody bro
    // printf("%s", output); //

    printf("%d", -1L < 1UL);

    return 0; // 111
}

void inputline(char s[]){
    int c = getchar();
    int i;
    for (i = 0; c != EOF; ++i){
        s[i] = c;
        c = getchar();
    }
    s[i] = EOF;
}

int formats(char input[], char output[]){
    int iscomment = 0;

    if (input[0] == '\n') {
        return 0;
    }

    for (int i = 0; input[i + 1] != EOF; ++i) {
        if (input[i] == '/' && input[i+1] == '/') {
            iscomment = 1;
        }
        if (input[i] == '\n'){
            iscomment = 0;
        }

        if (iscomment) {
            output[i] = ' ';
        } else {
            output[i] = input[i];
        }
    }
    return 0;
}