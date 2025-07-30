#include "../include/cRegex.h"
#include <stdio.h>

void terminalTesting();

int main(){

    terminalTesting();
    return 0;

}

void terminalTesting(){

    while(1){

        char type;
        printf("0 (Exit)\n1 (Full Match)\n2 (First Match)\nEnter:");
        type = getchar();
        getchar();

        if(type != '1' && type != '2'){
            return;
        }

        printf("\n");

        char reg[100];
        printf("Enter regex  (max len 100): ");
        fgets(reg, sizeof(reg), stdin);

        char str[100];
        printf("Enter string (max len 100): ");
        fgets(str, sizeof(str), stdin);

        if(type == '1' && quickFullMatch(reg, str)){
            printf("Match\n\n");
        }
        else if(type == '2' && 0 /*to do*/){
            
        }else{
            printf("No Match\n");
        }
    }

}


