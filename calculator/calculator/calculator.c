#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#define MAX_SIZE 10000

struct Stack {
    int elements[MAX_SIZE];
    int top;
};

void initialize(struct Stack* stack) {
    stack->top = -1;
}

int is_empty(struct Stack* stack) {
    return stack->top == -1;
}

int is_full(struct Stack* stack) {
    return stack->top == 9999;
}

void push(struct Stack* stack, int value) {
    if (is_full(stack)) {
        return;
    }
    else {
        stack->elements[++(stack->top)] = value;
    }
}

int pop(struct Stack* stack) {
    if (is_empty(stack)) {
        return -1;
    }
    else {
        return stack->elements[(stack->top)--];
    }
}

int is_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool is_degree(char c) {
    if (c == '^') {
        return 1;
    }
    else {
        return 0;
    }
}

int priority(char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (c == '*' || c == '/') {
        return 2;
    }
    if (c == '^') {
        return 3;
    }
    return 0;
}
int iscorrectinput(char* infix_expression) {
    int count_brackets = 0, count_digit = 0, count_operator = 0, flag = 0;
    for (size_t i = 0; i < strlen(infix_expression); i++) {
        if (infix_expression[i] == '$') {
            flag = 1;
        }
    }
    for (size_t i = 0; i < strlen(infix_expression); i++) {
        if (infix_expression[i] == '(') {
            count_brackets++;
        }
        if (infix_expression[i] == ')') {
            count_brackets--;
            if (count_brackets < 0 || (i > 0 && infix_expression[i - 1] == '(')) {
                return -1;
            }
        }
        if ('0' <= infix_expression[i] && infix_expression[i] <= '9') {
            while ('0' <= infix_expression[i] && infix_expression[i] <= '9') { i++; }
            count_digit++;
            i--;
        }
        if (is_operator(infix_expression[i])) {
            count_operator++;
        }
    }
    if (count_brackets != 0 || (count_operator >= count_digit && flag == 0) || (count_operator != count_digit && flag == 1) || infix_expression == NULL) {
        return -1;
    }
    size_t len = strlen(infix_expression);
    for (size_t i = 0; i < len - 2; i++) {
        if (!isdigit(infix_expression[i]) && !is_operator(infix_expression[i]) && infix_expression[i] != '(' && infix_expression[i] != ')' && infix_expression[i] != '$') {
            return -1;
        }
    }
    return 0;
}

char* infix_to_postfix(char* infix_expression, char* postfix, int prev_res) {
    postfix[0] = '\0';
    struct Stack stack;
    initialize(&stack);
    int num = 0;
    for (int i = 0; infix_expression[i]; i++) {
        if (isdigit(infix_expression[i])) {
            num = num * 10 + (infix_expression[i] - '0');
        }
        else if (infix_expression[i] == '(') {
            push(&stack, '(');
        }
        else if (infix_expression[i] == ')') {
            if (num > 0) {
                char temp[MAX_SIZE];
                sprintf(temp, "%d ", num);
                strcat(postfix, temp);
                num = 0;
            }
            while (!is_empty(&stack) && stack.elements[stack.top] != '(') {
                char temp[MAX_SIZE];
                sprintf(temp, "%c ", stack.elements[stack.top--]);
                strcat(postfix, temp);
            }
            if (!is_empty(&stack) && stack.elements[stack.top] == '(') {
                pop(&stack);
            }
        }
        else if (is_operator(infix_expression[i])) {
            if (num > 0) {
                char temp[MAX_SIZE];
                sprintf(temp, "%d ", num);
                strcat(postfix, temp);
                num = 0;
            }
            while (((!is_empty(&stack) && (priority(stack.elements[stack.top]) >= priority(infix_expression[i])) && (!is_degree(infix_expression[i]))) ||
                ((!is_empty(&stack)) && (priority(stack.elements[stack.top])) > priority(infix_expression[i])))) {
                char temp[MAX_SIZE];
                sprintf(temp, "%c ", stack.elements[stack.top--]);
                strcat(postfix, temp);
            }
            push(&stack, infix_expression[i]);
        }
        else if (infix_expression[i] == '$') {
            char temp[MAX_SIZE];
            sprintf(temp, "%d ", prev_res);
            strcat(postfix, temp);
        }
    }
    if (num == 0) {
        for (size_t i = 0; i < strlen(infix_expression) - 1; i++) {
            if (infix_expression[i] == '/' && infix_expression[i + 1] == '0') {
                strcpy(postfix, "division by zero");
                return postfix;
            }
        }
    }
    else if (num > 0) {
        char temp[MAX_SIZE];
        sprintf(temp, "%d ", num);
        strcat(postfix, temp);
        num = 0;
    }
    while (!is_empty(&stack)) {
        char temp[MAX_SIZE];
        sprintf(temp, "%c ", stack.elements[stack.top--]);
        strcat(postfix, temp);
    }
    return postfix;
}

int postfix_value(char* postfix_expression, bool* error, int prev_res) {
    struct Stack stack;
    initialize(&stack);
    for (int i = 0; postfix_expression[i]; i++) {
        if (isdigit(postfix_expression[i])) {
            int num = 0;
            while (isdigit(postfix_expression[i])) {
                num = num * 10 + (postfix_expression[i] - '0');
                i++;
            }
            i--;
            push(&stack, num);
        }
        else if (postfix_expression[i] == '+' || postfix_expression[i] == '-' || postfix_expression[i] == '*' || postfix_expression[i] == '/' || postfix_expression[i] == '.' || postfix_expression[i] == '^') {
            int b = pop(&stack);
            int a = pop(&stack);
            int result = 0;
            if (postfix_expression[i] == '+') {
                result = a + b;
            }
            else if (postfix_expression[i] == '-') {
                result = a - b;
            }
            else if (postfix_expression[i] == '*') {
                result = a * b;
            }
            else if (postfix_expression[i] == '^') {
                result = pow(a, b);
            }
            else if (postfix_expression[i] == '/') {
                if (b == 0) {
                    *error = true;
                    return prev_res;
                }
                result = a / b;
            }
            push(&stack, result);
        }
    }
    int result = pop(&stack);
    return result;
}
int main(int argc, char* argv[]) {
    int prev_res = 0;
    bool error = false;
    if (argc == 1) {
        char infix[MAX_SIZE];
        char postfix[MAX_SIZE];
        if (fgets(infix, sizeof(infix), stdin) == NULL) {
            return 0;
        }
        if (iscorrectinput(infix) != 0) {
            printf("syntax error");
            return 0;
        }
        infix_to_postfix(infix, postfix, prev_res);
        int result = postfix_value(postfix, &error, prev_res);
        if ((strncmp(postfix, "division by zero", 16)) == 0) {
            printf("%s", postfix);
            return 0;
        }
        else if (!error) {
            printf("%d\n", result);
        }
        else {
            printf("division by zero");
        }
        return 0;
    }
    else if ((argc == 2) && (strcmp(argv[1], "-i") == 0)) {
        printf("< Interactive mode is started:\n");
        printf("< Enter 'exit' to terminate the program.\n");
        while (1) {
            bool error = false;
            char infix[MAX_SIZE];
            char postfix[MAX_SIZE];
            printf("> ");
            if (fgets(infix, sizeof(infix), stdin) == NULL) {
                return 0;
            }
            if (strcmp(infix, "exit\n") == 0) {
                printf("< Goodbye!");
                break;
            }
            if (iscorrectinput(infix) != 0) {
                printf("< syntax error\n");
                continue;
            }
            infix_to_postfix(infix, postfix, prev_res);
            int result = postfix_value(postfix, &error, prev_res);
            if ((strncmp(postfix, "division by zero\n", 16)) == 0) {
                printf("< %s\n", postfix);
                continue;
            }
            else if (!error) {
                printf("< %d\n", result);
            }
            else {
                printf("< division by zero\n");
            }
            prev_res = result;
            continue;
        }
    }
}