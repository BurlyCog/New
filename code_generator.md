# Simple Code Generator in C

## Overview
This document contains:
1. Algorithm for simple code generator (TAC)
2. Algorithm for Quadruple, Triple, Indirect Triple
3. C Programs

---

# 1. Algorithm: Simple Code Generator (TAC)

## Steps
1. Read input expression
2. Split into LHS and RHS
3. Convert RHS from infix to postfix:
   - Use stack
   - Handle precedence and parentheses
4. Scan postfix:
   - If operand → push
   - If operator:
     - Pop two operands
     - Generate temp (t1, t2...)
     - Print: t = op1 op op2
     - Push temp
5. Assign final temp to LHS

---

# 2. Algorithm: Quadruple, Triple, Indirect Triple

## Quadruple
(op, arg1, arg2, result)

Steps:
1. Convert infix → postfix
2. Scan postfix
3. For operator:
   - Pop op2, op1
   - Create temp
   - Output quadruple

## Triple
(index, op, arg1, arg2)

Steps:
- Same as quadruple
- Use index instead of temp

## Indirect Triple
Steps:
- Maintain pointer table
- Store references to triples

---

# 3. Program 1: Simple TAC Generator

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

char stack[MAX];
int top = -1;

int prec(char c) {
    if (c == '*' || c == '/') return 2;
    if (c == '+' || c == '-') return 1;
    return 0;
}

void push(char c) { stack[++top] = c; }
char pop() { return stack[top--]; }

void infixToPostfix(char *exp, char *postfix) {
    int i, j = 0;
    char c;

    for (i = 0; exp[i]; i++) {
        c = exp[i];

        if (isalnum(c))
            postfix[j++] = c;
        else if (c == '(')
            push(c);
        else if (c == ')') {
            while (stack[top] != '(')
                postfix[j++] = pop();
            pop();
        } else {
            while (top != -1 && prec(stack[top]) >= prec(c))
                postfix[j++] = pop();
            push(c);
        }
    }

    while (top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';
}

void generateTAC(char *postfix, char lhs) {
    char tempStack[MAX][10];
    int ttop = -1, temp = 1;

    for (int i = 0; postfix[i]; i++) {
        char c = postfix[i];

        if (isalnum(c)) {
            sprintf(tempStack[++ttop], "%c", c);
        } else {
            char op2[10], op1[10], res[10];

            strcpy(op2, tempStack[ttop--]);
            strcpy(op1, tempStack[ttop--]);

            sprintf(res, "t%d", temp++);
            printf("%s = %s %c %s\n", res, op1, c, op2);

            strcpy(tempStack[++ttop], res);
        }
    }

    printf("%c = %s\n", lhs, tempStack[ttop]);
}

int main() {
    char input[50], rhs[50], postfix[50];
    char lhs;

    printf("Enter expression: ");
    scanf("%s", input);

    lhs = input[0];
    strcpy(rhs, strchr(input, '=') + 1);

    infixToPostfix(rhs, postfix);
    generateTAC(postfix, lhs);

    return 0;
}
```

---

# 4. Program 2: Quadruple, Triple, Indirect Triple

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 20

char postfix[50];

void generateCode() {
    char stack[MAX][10];
    int top = -1, temp = 1, index = 0;

    printf("\nQuadruple:\n");
    printf("Op Arg1 Arg2 Result\n");

    for (int i = 0; postfix[i]; i++) {
        char c = postfix[i];

        if (isalnum(c)) {
            sprintf(stack[++top], "%c", c);
        } else {
            char op2[10], op1[10], res[10];

            strcpy(op2, stack[top--]);
            strcpy(op1, stack[top--]);

            sprintf(res, "t%d", temp++);

            printf("%c %s %s %s\n", c, op1, op2, res);

            stack[++top][0] = 't';
            stack[top][1] = index + '0';
            stack[top][2] = '\0';

            index++;
        }
    }
}

int main() {
    printf("Enter postfix expression: ");
    scanf("%s", postfix);

    generateCode();
    return 0;
}
```

---

## End of File
