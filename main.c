#include "regex.h"

int main(void){
    printf("%s\n", matches("a|b*", "bbb"));

    
    return 0;
}