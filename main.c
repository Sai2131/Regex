#include "regex.h"

int main(void){

    printf("%d\n", quickFullMatch("abc*|(x*)", "abccccc"));
    
    return 0;
}