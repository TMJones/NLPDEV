#include <stdio.h>
#include <string.h>

int IF_input(char *str){
        int length;
        printf(">");
        fgets(str,256,stdin);
        length = strlen(str);
        if(str[length - 1] =='\n'){
                str[length - 1] = '\0';
        }
        return 0;
}
