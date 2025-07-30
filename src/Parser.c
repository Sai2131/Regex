#include "Parser.h"

//Recursive descent parser functions according to grammar
Node* parse_regex(lexer* l);
Node* parse_Expr(lexer* l);
Node* parse_ExprOptional(lexer* l, Node* left);
Node* parse_ExprC(lexer* l);
Node* parse_ExprCOptional(lexer* l, Node* left);
Node* parse_ExprK(lexer* l);
Node* parse_ExprKPrime(lexer* l, Node* left);
Node* parse_Group(lexer* l);

Node* parse(char* regex){
    lexer* lex = makeLexer(regex);
    Node* ast = parse_regex(lex);
    destoryLexer(&lex);
    return ast;
}

Node* parse_regex(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL || t.type == DOT){
        Node* final = parse_Expr(l);

        nextToken(l, &t);
        if(t.type == END){
            return final;
        }
        fprintf(stderr, "Error parsing regex:\n\t\tNon terminating regex\n");
        return NULL;
    }
    
    fprintf(stderr, "Error parsing regex:\n\t\tNo regex given\n");
    return NULL;
}

Node* parse_Expr(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL || t.type == DOT){
        Node* left = parse_ExprC(l);
        return parse_ExprOptional(l, left);
    }

    fprintf(stderr, "Error parsing regex:\n\t\tExpected (, literal or wildcard at index %d\n", l->position);
    return NULL;

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

    fprintf(stderr, "Error parsing regex:\n\t\tExpected ), | or END at index %d\n", l->position);
    return NULL;
}

Node* parse_ExprC(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL || t.type == DOT){
        Node* left = parse_ExprK(l);
        return parse_ExprCOptional(l, left);
        
    }

    fprintf(stderr, "Error parsing regex:\n\t\tExpected (, literal or wildcard at index %d\n", l->position);
    return NULL;
}

Node* parse_ExprCOptional(lexer* l, Node* left){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL || t.type == DOT){
        Node* right = parse_ExprC(l);
        return concatNode(left, right);
    }

    if(t.type == UNION || t.type == RPAREN || t.type == END){
        return left;
    }

    fprintf(stderr, "Error parsing regex:\n\t\tExpected (, literal, wildcard, |, ) or END at index %d\n", l->position);
    return NULL;
}

Node* parse_ExprK(lexer* l){
    token t;
    nextToken(l, &t);

    if(t.type == LPAREN || t.type == SYMBOL || t.type == DOT){
        Node* left = parse_Group(l);
        return parse_ExprKPrime(l, left);
    }

    fprintf(stderr, "Error parsing regex:\n\t\tExpected (, literal or wildcard at index %d\n", l->position);
    return NULL;
}

Node* parse_ExprKPrime(lexer* l, Node* left){
    token t;
    nextToken(l, &t);

    if(t.type == KLEENE){
        eatToken(l, &t);
        parse_ExprKPrime(l, left);
        return kleeneNode(left);
    }

    if(t.type == UNION || t.type == LPAREN || t.type == RPAREN || t.type == SYMBOL || t.type == DOT || t.type == END){
        return left;
    }

    fprintf(stderr, "Error parsing regex:\n\t\tExpected *, |, (, ), literal, dot or END at index %d\n", l->position);
    return NULL;
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

        fprintf(stderr, "Error parsing regex:\n\t\tExpected ) at index %d\n", l->position);
        return NULL;
    }
    else if(t.type == SYMBOL){
        eatToken(l, &t);
        return leafNode(t.symbol);
    }
    else if(t.type == DOT){
        eatToken(l, &t);
        return leafNodeDot(t.symbol);
    } 

    fprintf(stderr, "Error parsing regex:\n\t\tExpected (, literal or wildcard at index %d\n", l->position);
    return NULL;
}