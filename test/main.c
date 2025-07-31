#include "../include/cRegex.h"
#include <stdio.h>
#include <string.h>

static int _passed = 0;
static int _total = 0;

#define TEST(A, B) do{\
                        _total++; \
                        if(A == B){_passed++;} \
                        else{printf("Failed: %s != %s\n", #A, #B);}\
                    }while(0);



void terminalTesting();
void automaticTesting();

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Usage: ./test <manual / automatic>\n");
        return 0;
    }

    if(!strcmp(argv[1], "automatic")){
        automaticTesting();
    }
    else if(!strcmp(argv[1], "manual")){
        terminalTesting();
    }
    else{
        printf("Usage: ./test <manual / automatic>\n");
    }

    if(_passed == _total){
        return 0;
    }
    return -1;
}


void basicFullMatchTests(){

    TEST(quickFullMatch("abc", "abc"), 1);
    TEST(quickFullMatch("abc*", "abcc"), 1);
    TEST(quickFullMatch("ab*", "a"), 1);
    TEST(quickFullMatch("a*", ""), 1);
    TEST(quickFullMatch("a|b", "ab"), 0);
}

void automaticTesting(){
    basicFullMatchTests();
    printf("Passed: %d out of %d\n", _passed, _total);
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
            printf("No Match\n\n");
        }
    }

}


