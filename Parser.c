#include "Parser.h"

Node* parse_regex(lexer* l);
Node* parse_Expr(lexer* l);
Node* parse_ExprOptional(lexer* l, Node* left);
Node* parse_ExprC(lexer* l);
Node* parse_ExprCOptional(lexer* l, Node* left);
Node* parse_ExprK(lexer* l);
Node* parse_ExprKPrime(lexer* l, Node* left);
Node* parse_Group(lexer* l);

Node* parse(char* regex){
    lexer* l = makeLexer(regex);
    return parse_regex(l);
}

Node* parse_regex(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL){
        Node* final = parse_Expr(l);

        nextToken(l, &t);
        if(t.type == END){
            return final;
        }
    }
    
    printf("parse_regex ERROR PARSING\n");
}

Node* parse_Expr(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL){
        Node* left = parse_ExprC(l);
        return parse_ExprOptional(l, left);
    }

    printf("parse_Expr ERROR PARSING\n");

}

Node* parse_ExprOptional(lexer* l, Node* left){
    token t;
    nextToken(l, &t);

    if(t.type == UNION){
        eatToken(l, &t);
        Node* right = parse_Expr(l);
        return unionNode(left, right);
    }

    if(t.type == RPAREN || t.type == END){
        return left;
    }

    printf("parse_ExprOptional ERROR PARSING\n");
}

Node* parse_ExprC(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL){
        Node* left = parse_ExprK(l);
        return parse_ExprCOptional(l, left);
        
    }

    printf("parse_ExprC ERROR PARSING\n %d", t.type);
}

Node* parse_ExprCOptional(lexer* l, Node* left){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL){
        Node* right = parse_ExprC(l);
        return concatNode(left, right);
    }

    if(t.type == UNION || t.type == RPAREN || t.type == END){
        return left;
    }

    printf("parse_ExprCOptional ERROR PARSING\n");
}

Node* parse_ExprK(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL){
        Node* left = parse_Group(l);
        return parse_ExprKPrime(l, left);
    }

    printf("parse_ExprK ERROR PARSING\n");
}

Node* parse_ExprKPrime(lexer* l, Node* left){
    token t;
    nextToken(l, &t);

    if(t.type == KLEENE){
        eatToken(l, &t);
        parse_ExprKPrime(l, left); //could cause problems
        return kleeneNode(left);
    }

    if(t.type == UNION || t.type == LPAREN || t.type == RPAREN || t.type == SYMBOL || t.type == END){
        return left;
    }

    printf("parse_ExprKPrime ERROR PARSING\n");
}

Node* parse_Group(lexer* l){
    token t;

    nextToken(l, &t);

    if(t.type == LPAREN){

        eatToken(l, &t);
        Node* nest = parse_Expr(l);
        
        nextToken(l, &t);
        if(t.type == RPAREN){
            eatToken(l, &t);
            return nest;
        }
    }
    else if(t.type == SYMBOL){
        eatToken(l, &t);
        return leafNode(t.symbol);
    } 


    printf("parse_Group ERROR PARSING\n");
}