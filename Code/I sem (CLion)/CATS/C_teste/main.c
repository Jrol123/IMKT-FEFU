#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "Rus");
    int c, a[32][32], i, o, b[10000], C[10000], count = 0;
    a[0][0] = 128;
    for (i = 1; i < 32; i++){
        a[i][0] = a[i-1][0]+1;
    }
    for (o = 1; o < 32; o++){
        a[0][o] = a[0][o-1]+1;
    }
    for (i = 1; i < 32; i++){
        for (o = 1; o < 32; o++){
            if (a[i][o-1] < 159){
                if (i != 0 && o != 0){
                    a[i][o] = a[i][o-1]+1;
                }
            } else {
                a[i][o] = 128;
            }
        }
    }
    FILE *f1, *f2;
    i = 0;
    //1 - шифрует, 2 - дешифрует
    f1 = fopen("input.txt","r");
    c = fgetc(f1);
    if (c == 49){
        c = fgetc(f1);
        c = fgetc(f1);
        while (c != EOF && c != '\n'){
            b[i] = c-128;
            i++;
            c = fgetc(f1);
            count++;
        }
        i = 0;
        c = fgetc(f1);
        while (c != EOF && c != '\n'){
            C[i] = c-128;
            i++;
            c = fgetc(f1);
        }
        f2 = fopen("output.txt","w");
        for (i = 0; i < count; i++){
            fprintf(f2,"%c",a[b[i]][C[i]]);
        }
    }
    if (c == 50){
        c = fgetc(f1);
        c = fgetc(f1);
        while (c != EOF && c != '\n'){
            b[i] = c;
            i++;
            c = fgetc(f1);
            count++;
        }
        i = 0;
        c = fgetc(f1);
        while (c != EOF && c != '\n'){
            C[i] = c-128;
            i++;
            c = fgetc(f1);
        }
        f2 = fopen("output.txt","w");
        for (i = 0; i < count; i++){
            o = 0;
            while (a[o][C[i]] != b[i]){
                o++;
            }
            fprintf(f2,"%c",a[o][0]);
        }
    }
    fclose(f1);
    fclose(f2);
    return 0;
}
