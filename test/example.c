#include "../include/cRegex.h"
#include <stdio.h>
#include <string.h>

int main(){

    char strings[10][100] = {
        "johnappleseed@email.org",
        "adam@adam.org",
        "123432432534.3443",
        "!!!;';'@email.com",
        "(111)-222-3333",
        "111-222-3333",
        "abcdefg",
        "(111)-222-900",
        "111-222-abcd",
        "helloworld@.com"
    };

    char emailRegex[73] = "[A-Za-z0-9][A-Za-z0-9]*@[A-Za-z0-9][A-Za-z0-9]*\\.[A-Za-z0-9][A-Za-z0-9]*";
    char phoneRegex[75] = "(\\([0-9][0-9][0-9]\\)|[0-9][0-9][0-9])-[0-9][0-9][0-9]-[0-9][0-9][0-9][0-9]";

    for(int i = 0; i<10;i++){
        if(quickFullMatch(emailRegex, strings[i]) == 1){
            printf("  Email: %s \n\n",strings[i]);
        }else if(quickFullMatch(phoneRegex, strings[i]) == 1){
            printf("  Phone: %s \n\n",strings[i]);
        }
        else{
            printf("Invalid: %s \n\n",strings[i]);
        }
    }
    
    return 0;
}