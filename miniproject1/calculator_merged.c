#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
/* あ～死ぬ　/v\ */

// for lex
#define MAXLEN 256

// Token types
typedef enum {
    UNKNOWN, END, ENDFILE,
    INT, ID,
    ADDSUB, MULDIV,
    ASSIGN, ADDSUB_ASSIGN,
    AND, XOR, OR,
    INCDEC,
    LPAREN, RPAREN
} TokenSet;

TokenSet getToken(void);
TokenSet curToken = UNKNOWN;
char lexeme[MAXLEN];

// Test if a token matches the current token
int match(TokenSet token);
// Get the next token
void advance(void);
// Get the lexeme of the current token
char *getLexeme(void);


// for parser
#define TBLSIZE 64
// Set PRINTERR to 1 to print error message while calling error()
// Make sure you set PRINTERR to 0 before you submit your code
#define PRINTERR 1

// Call this macro to print error message and exit the program
// This will also print where you called it in your program
#define error(errorNum) { \
    if (PRINTERR) \
        fprintf(stderr, "error() called at %s:%d: ", __FILE__, __LINE__); \
    err(errorNum); \
}

// Error types
typedef enum {
    UNDEFINED, MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NOTLVAL, DIVZERO, SYNTAXERR
} ErrorType;

// Structure of the symbol table
typedef struct {
    int val;
    char name[MAXLEN];
} Symbol;

// Structure of a tree node
typedef struct _Node {
    TokenSet data;
    int val;
    char lexeme[MAXLEN];
    struct _Node *left;
    struct _Node *right;
} BTNode;

int sbcount = 0;
Symbol table[TBLSIZE];

// Initialize the symbol table with builtin variables
void initTable(void);
// Get the value of a variable
int getval(char *str);
// Set the value of a variable
int setval(char *str, int val);
// Make a new node according to token type and lexeme
BTNode *makeNode(TokenSet tok, const char *lexe);
// Free the syntax tree
void freeTree(BTNode *root);
BTNode *factor(void);
BTNode *unary_expr(void);
BTNode *muldiv_expr(void);
BTNode *muldiv_expr_tail(BTNode *left);
BTNode *addsub_expr(void);
BTNode *addsub_expr_tail(BTNode *left);
BTNode *and_expr(void);
BTNode *and_expr_tail(BTNode *left);
BTNode *xor_expr(void);
BTNode *xor_expr_tail(BTNode *left);
BTNode *or_expr(void);
BTNode *or_expr_tail(BTNode *left);
BTNode *assign_expr(void);
// BTNode *term(void);
// BTNode *term_tail(BTNode *left);
// BTNode *expr(void);
// BTNode *expr_tail(BTNode *left);
void statement(void);
// Print error message and exit the program
void err(ErrorType errorNum);


// for codeGen
int codeGen(BTNode *root, int dir);
// Evaluate the syntax tree
int evaluateTree(BTNode *root);
// Print the syntax tree in prefix
void printPrefix(BTNode *root);


/*============================================================================================
lex implementation
============================================================================================*/

int pos;
char lex[MAXLEN];               // track on input
TokenSet getToken(void)
{
    int i = 0;
    char c = '\0', tmp = '\0';

    while ((c = fgetc(stdin)) == ' ' || c == '\t');

    if (isdigit(c)) {
        lexeme[0] = c;
        lex[pos++] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i < MAXLEN) {
            lexeme[i] = c;
            lex[pos++] = c;
            ++i;
            c = fgetc(stdin);
        }
        if(isalpha(c) || c == '_')              // num leading var - invalid
            error(SYNTAXERR);
        ungetc(c, stdin);
        lexeme[i] = '\0';
        lex[pos] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lex[pos++] = c;
        if((tmp = fgetc(stdin)) == c){
            lexeme[1] = c;
            lexeme[2] = '\0';
            lex[pos++] = c;
            lex[pos] = '\0';
            return INCDEC;
        } else if(tmp == '='){
            lexeme[1] = tmp;
            lexeme[2] = '\0';
            lex[pos++] = tmp;
            lex[pos] = '\0';
            return ADDSUB_ASSIGN;
        } else {
            ungetc(tmp, stdin);
            lexeme[1] = '\0';
            lex[pos] = '\0';
        }
        return ADDSUB;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        lex[pos++] = c;
        lex[pos] = '\0';
        return MULDIV;
    } else if (c == '&') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        lex[pos++] = c;
        lex[pos] = '\0';
        return AND;
    } else if (c == '^') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        lex[pos++] = c;
        lex[pos] = '\0';
        return XOR;
    } else if (c == '|') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        lex[pos++] = c;
        lex[pos] = '\0';
        return OR;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        lex[pos++] = c;
        lex[pos] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        lex[pos++] = c;
        lex[pos] = '\0';
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        lex[pos++] = c;
        lex[pos] = '\0';
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        lex[pos++] = c;
        lex[pos] = '\0';
        return RPAREN;
    } else if (isalpha(c) || c == '_') {            // valid var name '_' alph num
        int len = 0;
        lexeme[len++] = c;
        lex[pos++] = c;
        while(isalnum(tmp = fgetc(stdin)) || tmp == '_'){
            lexeme[len++] = tmp;
            lex[pos++] = tmp;
        }
        ungetc(tmp, stdin);
        lexeme[len] = '\0';
        lex[pos] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void) {
    curToken = getToken();
}

int match(TokenSet token) {
    if (curToken == UNKNOWN)
        advance();
    return token == curToken;
}

char *getLexeme(void) {
    return lexeme;
}


/*============================================================================================
parser implementation
============================================================================================*/
char stack[MAXLEN][MAXLEN], queue = 0;
int reg[10];
int regidx = 0, varcounter = 0;
void initTable(void) {
    strcpy(table[0].name, "x");
    table[0].val = 0;
    strcpy(table[1].name, "y");
    table[1].val = 0;
    strcpy(table[2].name, "z");
    table[2].val = 0;
    sbcount = 3;
}

// check new var at right side of assign - invalid
int checkVar(char *str) {
    for (int i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0)
            return 1;
    }
    return 0;
}

//*** unget token for assign_expr if not assign counter
void ungetTok() {
    pos--;
    while (isalnum(lex[pos-1]) || lex[pos-1] == '_'){
        ungetc(lex[pos--], stdin);
    }
    ungetc(lex[pos], stdin);
    lex[pos] = '\0';
}

// get address of var
int getaddr(char *str) {
    for (int i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0)
            return i;
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return sbcount - 1;                 // new var addr
}

int getval(char *str) {
    int i = 0;

    for (i = 0; i < sbcount; i++)
        if (strcmp(str, table[i].name) == 0)
            return table[i].val;

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = 0;
    sbcount++;
    return 0;
}

int setval(char *str, int val) {
    int i = 0;

    for (i = 0; i < sbcount; i++) {
        if (strcmp(str, table[i].name) == 0) {
            table[i].val = val;
            return val;
        }
    }

    if (sbcount >= TBLSIZE)
        error(RUNOUT);

    strcpy(table[sbcount].name, str);
    table[sbcount].val = val;
    sbcount++;
    return val;
}

BTNode *makeNode(TokenSet tok, const char *lexe) {
    BTNode *node = (BTNode*)malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

// factor := INT | ID | INCDEC ID| LPAREN assign_expr RPAREN
BTNode *factor(void) {
    BTNode *retp = NULL, *left = NULL;

    if (match(INT)) {
        retp = makeNode(INT, getLexeme());
        advance();
    } else if (match(ID)) {
        if (checkVar((getLexeme()))) {
            retp = makeNode(ID, getLexeme());
            advance();
        } else {
            error(SYNTAXERR);                   // new var in factor - invalid
        }
    } else if (match(INCDEC)) {
        retp = makeNode(INCDEC, getLexeme());
        advance();
        if (match(ID)) {
            if (checkVar((getLexeme()))) {
                retp->left = makeNode(INT, "1");
                retp->right = makeNode(ID, getLexeme());
                advance();
            } else {
                error(SYNTAXERR);               // new var in factor - invalid
            }    
        } else {
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = assign_expr();
        if (match(RPAREN)) {
            advance();
        } else {
            error(MISPAREN);
        }
    } else {
        error(NOTNUMID);
    }
    return retp;
}
BTNode *unary_expr(void) {
// unary_expr := ADDSUB unary_expr | factor
    BTNode* retp = NULL;
    if (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->left = makeNode(INT, "0");
        retp->right = unary_expr();
    } else
        retp = factor();
    return retp;
}
BTNode *muldiv_expr(void) {
// muldiv_expr := unary_expr muldiv_expr_tail
    BTNode* node = unary_expr();
    return muldiv_expr_tail(node);
}
BTNode *muldiv_expr_tail(BTNode *left) {
// muldiv_expr_tail := MULDIV unary_expr muldiv_expr_tail | Nil
    BTNode* node = NULL;
    if (match(MULDIV)) {
        node = makeNode(MULDIV, getLexeme());
        advance();
        node->left = left;
        node->right = unary_expr();
        return muldiv_expr_tail(node);
    } else 
        return left;
}
BTNode *addsub_expr(void) {
// addsub_expr := muldiv_expr addsub_expr_tail
    BTNode* node = muldiv_expr();
    return addsub_expr_tail(node);
}
BTNode *addsub_expr_tail(BTNode *left) {
// addsub_expr_tail := ADDSUB muldiv_expr addsub_expr_tail | Nil
    BTNode* node = NULL;
    if (match(ADDSUB)) {
        node = makeNode(ADDSUB, getLexeme());
        advance();
        node->left = left;
        node->right = muldiv_expr();
        return addsub_expr_tail(node);
    } else 
        return left;
}
BTNode *and_expr(void) {
// and_expr := addsub_expr and_expr_tail
    BTNode* node = addsub_expr();
    return and_expr_tail(node);
}
BTNode *and_expr_tail(BTNode *left) {
// and_expr_tail := AND addsub_expr and_expr_tail | Nil
    BTNode* node = NULL;
    if (match(AND)) {
        node = makeNode(AND, getLexeme());
        advance();
        node->left = left;
        node->right = addsub_expr();
        return and_expr_tail(node);
    } else 
        return left;
}
BTNode *xor_expr(void) {
// xor_expr := and_expr xor_expr_tail
    BTNode* node = and_expr();
    return xor_expr_tail(node);
}
BTNode *xor_expr_tail(BTNode *left) {
// xor_expr_tail := XOR and_expr xor_expr_tail | Nil
    BTNode* node = NULL;
    if (match(XOR)) {
        node = makeNode(XOR, getLexeme());
        advance();
        node->left = left;
        node->right = and_expr();
        return xor_expr_tail(node);
    } else 
        return left;   
}
BTNode *or_expr(void) {
// or_expr := xor_expr or_expr_tail
    BTNode* node = xor_expr();
    return or_expr_tail(node);
}
BTNode *or_expr_tail(BTNode *left) {
// or_expr_tail := OR xor_expr or_expr_tail | Nil
    BTNode* node = NULL;
    if (match(OR)) {
        node = makeNode(OR, getLexeme());
        advance();
        node->left = left;
        node->right = xor_expr();
        return or_expr_tail(node);
    } else 
        return left;
}
BTNode *assign_expr(void) {
//assign_expr := ID ASSIGN assign_expr | ID ADDSUB_ASSIGN assign_expr | or_expr
    BTNode *retp = NULL, *left = NULL;
    if (match(ID)) {
        left = makeNode(ID, getLexeme());
        advance();
        if (match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
        } else if (match(ADDSUB_ASSIGN)) {
            retp = makeNode(ADDSUB_ASSIGN, getLexeme());
        } else {                            // not assign after ID case -> or_expr
            ungetTok();
            advance();
            return retp = or_expr();
        }
        advance();
        retp->left = left;
        retp->right = assign_expr();
    } else {
        retp = or_expr();
    }
    return retp;
}

void statement(void) {
// statement := ENDFILE | END | assign_expr END
    BTNode *retp = NULL;

    if (match(ENDFILE)) {
        printf("MOV r0 [0]\nMOV r1 [4]\nMOV r2 [8]\n");
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        // printf(">> ");
        advance();
    } else {
        retp = assign_expr();
        if (match(END)) {
            queue = 0; 
            memset(reg, 0, sizeof(reg));
            codeGen(retp, -1);
            // printf("%d\n", evaluateTree(retp));
            // printf("Prefix traversal: ");
            // printPrefix(retp);
            // printf("\n");
            freeTree(retp);
            // printf(">> ");
            advance();
        } else {
            error(SYNTAXERR);
        }
    }
}

void err(ErrorType errorNum) {
    if (PRINTERR) {
        fprintf(stderr, "error: ");
        switch (errorNum) {
            case MISPAREN:
                fprintf(stderr, "mismatched parenthesis\n");
                break;
            case NOTNUMID:
                fprintf(stderr, "number or identifier expected\n");
                break;
            case NOTFOUND:
                fprintf(stderr, "variable not defined\n");
                break;
            case RUNOUT:
                fprintf(stderr, "out of memory\n");
                break;
            case NOTLVAL:
                fprintf(stderr, "lvalue required as an operand\n");
                break;
            case DIVZERO:
                fprintf(stderr, "divide by constant zero\n");
                break;
            case SYNTAXERR:
                fprintf(stderr, "syntax error\n");
                break;
            default:
                fprintf(stderr, "undefined error\n");
                break;
        }
    }
    printf("EXIT 1\n");
    exit(0);
}


/*============================================================================================
codeGen implementation
============================================================================================*/

int codeGen(BTNode *root, int dir) {
    int idx = 0, lx = 0, rx = 0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                if (dir == -1) {
                    strcpy(stack[queue++], root->lexeme);
                    idx = -1;
                } else {
                    for (regidx = 0; reg[regidx]; regidx++);
                    idx = regidx;  
                    reg[idx] = 1;
                    printf("MOV r%d [%d]\n", idx, 4 * getaddr(root->lexeme));
                }
                break;
            case INT:
                if (dir == -1) {
                    strcpy(stack[queue++], root->lexeme);
                    idx = -1;
                } else {
                    for (regidx = 0; reg[regidx]; regidx++);
                    idx = regidx;  
                    reg[idx] = 1;
                    printf("MOV r%d %d\n", idx, atoi(root->lexeme));
                }
                break;
            case ASSIGN:
                idx = codeGen(root->right, 1);
                printf("MOV [%d] r%d\n", 4 * getaddr(root->left->lexeme), idx);
                break;
            case ADDSUB_ASSIGN:
                idx = codeGen(root->left, -1);               // only var on left
                rx = codeGen(root->right, 1);
                if (strcmp(root->lexeme, "+=") == 0) {
                    printf("ADD r%d r%d\n", idx, rx);
                } else if (strcmp(root->lexeme, "-=") == 0) {
                    printf("SUB r%d r%d\n", idx, rx);
                }
                printf("MOV [%d] r%d\n", 4 * getaddr(root->left->lexeme), idx);
                break;
            case INCDEC:
                idx = codeGen(root->right, 1);
                for (regidx = 0; reg[regidx]; regidx++);
                lx = regidx;
                printf("MOV r%d 1\n", lx);
                if (strcmp(root->lexeme, "++") == 0) {
                    printf("ADD r%d r%d\n", idx, lx);
                } else if (strcmp(root->lexeme, "--") == 0) {
                    printf("SUB r%d r%d\n", idx, lx);
                }
                printf("MOV [%d] r%d\n", 4 * getaddr(root->right->lexeme), idx);
                break;
            case ADDSUB:
            case MULDIV:
            case AND:
            case XOR:
            case OR:
                lx = codeGen(root->left, -1);
                rx = codeGen(root->right, 1);
                if (lx == -1) {
                    if(queue == 0) error(RUNOUT);
                    --queue;
                    for (regidx = 0; reg[regidx]; regidx++);
                    lx = regidx;
                    reg[lx] = 1;
                    if (isdigit(stack[queue][0]))
                        printf("MOV r%d %d\n", lx, atoi(stack[queue]));
                    else
                        printf("MOV r%d [%d]\n", lx, 4 * getaddr(stack[queue]));
                }
                if (strcmp(root->lexeme, "+") == 0) {
                    printf("ADD r%d r%d\n", lx, rx);
                } else if (strcmp(root->lexeme, "-") == 0) {
                    printf("SUB r%d r%d\n", lx, rx);
                } else if (strcmp(root->lexeme, "*") == 0) {
                    printf("MUL r%d r%d\n", lx, rx);
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (!evaluateTree(root->right) && !varcounter)
                        error(DIVZERO);
                    printf("DIV r%d r%d\n", lx, rx);
                } else if (strcmp(root->lexeme, "&") == 0) {
                    printf("AND r%d r%d\n", lx, rx);
                }  else if (strcmp(root->lexeme, "^") == 0) {
                    printf("XOR r%d r%d\n", lx, rx);
                }  else if (strcmp(root->lexeme, "|") == 0) {
                    printf("OR r%d r%d\n", lx, rx);
                }
                // regidx--;           // after eval rx reuse. 
                reg[rx] = 0;
                idx = lx;
                break;
            default:
                idx = -1;
        }
    }
    return idx;
}

int evaluateTree(BTNode *root) {
    int retval = 0, lv = 0, rv = 0;

    if (root != NULL) {
        switch (root->data) {
            case ID:
                varcounter = 1;
                retval = getval(root->lexeme);
                break;
            case INT:
                retval = atoi(root->lexeme);
                break;
            case ASSIGN:
            case ADDSUB_ASSIGN:
            case INCDEC:
                varcounter = 1;
                // rv = evaluateTree(root->right);
                // retval = setval(root->left->lexeme, rv);
                break;
            case AND:
            case XOR:
            case OR:
            case ADDSUB:
            case MULDIV:
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0) {
                    retval = lv + rv;
                } else if (strcmp(root->lexeme, "-") == 0) {
                    retval = lv - rv;
                } else if (strcmp(root->lexeme, "*") == 0) {
                    retval = lv * rv;
                } else if (strcmp(root->lexeme, "/") == 0) {
                    if (rv == 0 && !varcounter)
                        error(DIVZERO);
                    retval = lv / rv;
                } else if (strcmp(root->lexeme, "&") == 0) {
                    retval = lv & rv;
                } else if (strcmp(root->lexeme, "^") == 0) {
                    retval = lv ^ rv;
                } else if (strcmp(root->lexeme, "|") == 0) {
                    retval = lv | rv;
                } 
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}

void printPrefix(BTNode *root) {
    if (root != NULL) {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}


/*============================================================================================
main
============================================================================================*/

int main() {
    // freopen("input.txt", "w", stdout);
    initTable();
    // printf(">> ");
    while (1) {
        pos = 0; regidx = 0;
        statement();
    }
    return 0;
}
