#include "Lexer.h"

void parse_regex(lexer* l);
void parse_Expr(lexer* l);
void parse_ExprOptional(lexer* l);
void parse_ExprC(lexer* l);
void parse_ExprCOptional(lexer* l);
void parse_ExprK(lexer* l);
void parse_ExprKPrime(lexer* l);
void parse_Group(lexer* l);

int main(){
    lexer* l = makeLexer("aa|(aa)*vfdaaa");
    parse_regex(l);
    return 0;
}

void parse_regex(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL){
        parse_Expr(l);

        nextToken(l, &t);
        if(t.type == END){
            return;
        }
    }
    
    printf("parse_regex ERROR PARSING\n");
}

void parse_Expr(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL){
        parse_ExprC(l);
        parse_ExprOptional(l);
        return;
    }

    printf("parse_Expr ERROR PARSING\n");

}

void parse_ExprOptional(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == UNION){
        eatToken(l, &t);
        parse_Expr(l);
        return;
    }

    if(t.type == RPAREN || t.type == END){
        return;
    }

    printf("parse_ExprOptional ERROR PARSING\n");
}

void parse_ExprC(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL){
        parse_ExprK(l);
        parse_ExprCOptional(l);
        return;
    }

    printf("parse_ExprC ERROR PARSING\n %d", t.type);
}

void parse_ExprCOptional(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL){
        parse_ExprC(l);
        return;
    }

    if(t.type == UNION || t.type == RPAREN || t.type == END){
        return;
    }

    printf("parse_ExprCOptional ERROR PARSING\n");
}

void parse_ExprK(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL){
        parse_Group(l);
        parse_ExprKPrime(l);
        return;
    }

    printf("parse_ExprK ERROR PARSING\n");
}

void parse_ExprKPrime(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == KLEENE){
        eatToken(l, &t);
        parse_ExprKPrime(l);
        return;
    }

    if(t.type == UNION || t.type == LPAREN || t.type == RPAREN || t.type == SYMBOL || t.type == END){
        return;
    }

    printf("parse_ExprKPrime ERROR PARSING\n");
}

void parse_Group(lexer* l){
    token t;

    nextToken(l, &t);

    if(t.type == LPAREN){

        eatToken(l, &t);
        parse_Expr(l);
        
        nextToken(l, &t);
        if(t.type == RPAREN){
            eatToken(l, &t);
            return;
        }
    }
    else if(t.type == SYMBOL){
        eatToken(l, &t);
        return;
    } 


    printf("parse_Group ERROR PARSING\n");
}