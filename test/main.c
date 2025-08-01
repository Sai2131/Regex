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

void edgeCases(){

    TEST(quickFullMatch(".*", ""), 1);
    TEST(quickFullMatch("[ABC-Z]*", ""), 1);

    TEST(quickFullMatch("HELLO", ""), 0);
    TEST(quickFullMatch(".", ""), 0);
}

void basicFullMatchTests(){
    
    TEST(quickFullMatch("abc", "abc"), 1);
    TEST(quickFullMatch("abc*", "abcc"), 1);
    TEST(quickFullMatch("ab*", "a"), 1);
    TEST(quickFullMatch("a*", ""), 1);
    TEST(quickFullMatch("a|b", "ab"), 0);
    TEST(quickFullMatch("xyz|b", "xyz"), 1);
    TEST(quickFullMatch("xy*z|by*", "xyyz"), 1);
}

void basicFirstMatchTests(){
    TEST(quickFirstMatch("abc", "helloabchello"), 1);
    TEST(quickFirstMatch("@email.email", "hello@email.email"), 1);
    TEST(quickFirstMatch("6\\.534", "89759346.5345f4fg"), 1);

    TEST(quickFirstMatch("abc", "hello"), 0);
    TEST(quickFirstMatch("abc", "helloachello"), 0);
    TEST(quickFirstMatch("@email.email", "hello@email.com"), 0);
    TEST(quickFirstMatch("6\\.534", "8975934645f4fg"), 0);
}

void advancedFullMatchTests(){

    TEST(quickFullMatch("(abc)*", "abcabcabc"), 1);
    TEST(quickFullMatch("(a|b|c*)*|z", "aaaabbbccca"), 1);
    TEST(quickFullMatch("((xyz)*abc)", "abc"), 1);
    TEST(quickFullMatch("...-...-.*", "123-456-"), 1);
    TEST(quickFullMatch("..*@..*\\.com", "pleasework@email.com"), 1);
    TEST(quickFullMatch("\\([0-9][0-9][0-9]\\)-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]", "(111)-222-2222"), 1);
    TEST(quickFullMatch("([A-Za-z0-9][A-Za-z0-9]*)@[A-Za-z0-9][A-Za-z0-9]*\\.[A-Za-z0-9][A-Za-z0-9]*", "Hello123@hello.hello"), 1);

    TEST(quickFullMatch("(abc)*", "abcabcab"), 0);
    TEST(quickFullMatch("(a|b|c*)*|z", "zaaaabbbccca"), 0);
    TEST(quickFullMatch("((xyz)*abc)", "xyzabcc"), 0);
    TEST(quickFullMatch("...-...-.*", "123456-"), 0);
    TEST(quickFullMatch("..*@..*\\.com", "pleasedontwork@.com"), 0);
    TEST(quickFullMatch("\\([0-9][0-9][0-9]\\)-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]", "111-222-2222"), 0);
    TEST(quickFullMatch("([A-Za-z0-9][A-Za-z0-9]*)@[A-Za-z0-9][A-Za-z0-9]*\\.[A-Za-z0-9][A-Za-z0-9]*", "HELLO!@&&&.#"), 0);
}

void automaticTesting(){
    edgeCases();
    basicFullMatchTests();
    advancedFullMatchTests();

    basicFirstMatchTests();
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


