#include "ExpressionEvaluation.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EXPREESSIONLEN 100

struct Node {
    char bit;
    Ptrtonode next;
} ;

int IsEmpty(Stack S)
{
    return S->next == NULL;
}

void MakeEmpty(Stack S)
{
    if (S == NULL) {
        printf("MakeEmpty is wrong,line is %d", __LINE__);
    } else {
        while (!IsEmpty(S)) {
            Pop(S);
        }
    }
}

void Push(char x, Stack S)
{
    Ptrtonode tmp = (Ptrtonode)malloc(sizeof(struct Node));
    if (tmp == NULL) {
        printf("push wrong\n");
    } else {
        tmp->bit = x;
        tmp->next = S->next;
        S->next = tmp;
    }
}

void Pop(Stack S)
{
    if (IsEmpty(S)) {
        printf("Pop 's stack is kong'\n");
    } else {
        Ptrtonode tmp = S->next;
        S->next = tmp->next;
        free(tmp);
    }
}

char Top(Stack S)
{
    if (!IsEmpty(S)) {
        return S->next->bit;
    } else {
        return 'n';
    }
}

Stack CreateStack()
{
    Stack dummy = (Stack)malloc(sizeof(struct Node));
    if (dummy == NULL) {
        printf("create dummy is wrong,line is %d\n", __LINE__);
    }
    dummy->next = NULL;
    MakeEmpty(dummy);
    return dummy;
}

char *InfixToSuffix(char *inffixexpreesion)                    
{                                                              
    int counter = 0;                                           
    char *suffix = (char *)malloc(EXPREESSIONLEN*sizeof(char));
    memset(suffix, 0, EXPREESSIONLEN*sizeof(char));            
    Stack dummy = CreateStack();                               
    char top;                                                  
    for (size_t i = 0; i < strlen(inffixexpreesion); i++) {    
        switch (inffixexpreesion[i]) {                         
        case '+':                                              
            top = Top(dummy);                                  
            while (top == '+' || top == '-' || top == '*' || top == '/' || top == '%' || top == '^') { 
                suffix[counter++] = top;
                Pop(dummy);
                top = Top(dummy);
            }
            Push('+', dummy);
            break;                                             
        case '-':                                              
            top = Top(dummy);          
            while (top == '+' || top == '-' || top == '*' || top == '/' || top == '%' || top == '^') { 
                suffix[counter++] = top;
                Pop(dummy);            
                top = Top(dummy);      
            }                          
            Push('-', dummy);          
            break;                                             
        case '*':                                              
            top = Top(dummy);           
            while (top == '*' || top == '/' || top == '%' || top == '^') { 
                suffix[counter++] = top;
                Pop(dummy);             
                top = Top(dummy);       
            }                           
            Push('*', dummy);           
            break;                                             
        case '/':                                              
            top = Top(dummy);           
            while (top == '*' || top == '/' || top == '%' || top == '^') { 
                suffix[counter++] = top;
                Pop(dummy);             
                top = Top(dummy);       
            }                           
            Push('/', dummy);           
            break;                                             
        case '%':                                              
            top = Top(dummy);                                             
            while (top == '*' || top == '/' || top == '%' || top == '^') {
                suffix[counter++] = top;                                  
                Pop(dummy);                                               
                top = Top(dummy);                                         
            }                                                             
            Push('%', dummy);                                             
            break;                                             
        case '^':                                              
            top = Top(dummy);                                             
            while (top == '^') {
                suffix[counter++] = top;                                  
                Pop(dummy);                                               
                top = Top(dummy);                                         
            }                                                             
            Push('^', dummy);                                             
            break;                                             
        case '(':
            Push('(', dummy);
            break;
        case ')':
            top = Top(dummy);                                             
            while (top != '(') {
                suffix[counter++] = top;
                Pop(dummy);
                top = Top(dummy);                                         
            }
            Pop(dummy);
            break;
        default:                                               
            suffix[counter] = inffixexpreesion[i];             
            counter++;                                         
            break;                                             
        }                                                      
    }                                                          
    while (!IsEmpty(dummy)) {
        top = Top(dummy);
        suffix[counter++] = top;
        Pop(dummy);
    }
    free(dummy);
    return suffix;                                             
}                                                              

int Do(char *suffixexpreesion)
{
    Stack dummy = CreateStack();
    int topa, topb;
    char x;
    for (size_t i = 0; i < strlen(suffixexpreesion); i++) {
        printf("%c", suffixexpreesion[i]);
    }
    printf("\n");
    for (size_t i = 0; i < strlen(suffixexpreesion); i++)
    {
        if (suffixexpreesion[i] != '+' && suffixexpreesion[i] != '-' && suffixexpreesion[i] != '*' && suffixexpreesion[i] != '/' && suffixexpreesion[i] != '%' && suffixexpreesion[i] != '^') {
            Push(suffixexpreesion[i], dummy);
        } else {
            topa = (int)Top(dummy);
            if (topa <= 57 && topa >= 48) {
                topa = topa-48;
            }
            Pop(dummy);
            topb = (int)Top(dummy);
            if (topb <= 57 && topb >= 48) {  
                topb = topb-48;
            }                  
            Pop(dummy);
            //printf("topa = %d, topb = %d\n", topa, topb);
            if (suffixexpreesion[i] == '+') {
                topa = topa + topb;
                if (topa >= 0 && topa <= 9) {
                    x = (char)topa + 48;
                } else {
                    x = (char)topa;
                }
                Push(x, dummy);
            }
            if (suffixexpreesion[i] == '-') {
                topa = topa-topb;          
                if (topa >= 0 && topa <= 9) {
                    x = (char)topa + 48;     
                } else {                     
                    x = (char)topa;          
                }                            
                Push(x, dummy);              
            }                                
            if (suffixexpreesion[i] == '*') {
                topa = topa*topb;          
                if (topa >= 0 && topa <= 9) {
                    x = (char)topa + 48;     
                } else {                     
                    x = (char)topa;          
                }                            
                Push(x, dummy);              
            }                                
            if (suffixexpreesion[i] == '/') {
                topa = topb/topa;          
                if (topa >= 0 && topa <= 9) {
                    x = (char)topa + 48;     
                } else {                     
                    x = (char)topa;          
                }                            
                Push(x, dummy);              
            }                                
            if (suffixexpreesion[i] == '%') {
                topa = topb%topa;          
                if (topa >= 0 && topa <= 9) {
                    x = (char)topa + 48;     
                } else {                     
                    x = (char)topa;          
                }                            
                Push(x, dummy);              
            }                                
            if (suffixexpreesion[i] == '^') {
                int loop = topa;
                int di = topb;
                for (int i = 0; i < loop-1; i++) {
                    topb *= di;
                }
                topa = topb;
                if (topa >= 0 && topa <= 9) {
                    x = (char)topa + 48;     
                } else {                     
                    x = (char)topa;          
                }                            
                Push(x, dummy);              
            }                                
        }
    }
    int answer = (int)Top(dummy);
    if (answer >= 48 && answer <= 57) {
        answer -= 48;
    }
    return answer;
}

choice_t RealInput()
{
    char *expression = (char *)malloc(EXPREESSIONLEN*sizeof(char));
    printf("请输入表达式：\n");
    scanf("%s", expression);
    char *suffixexpreesion = InfixToSuffix(expression);
    int answer = Do(suffixexpreesion);
    printf("计算结果：%d\n", answer);
    return INIT;
}

choice_t ShowInput()
{
    int op;
    printf("1. 计算：\n");
    printf("2. 退出：\n");
    scanf("%d", &op);
    switch (op) {
    case 1:
        return GO;
        break;
    case 2:
        return EXIT;
        break;
    }
    return INIT;
}

void InputMenu()
{
    choice_t status = INIT;
    while (status != EXIT) {
        switch (status) {
        case INIT:
            status = ShowInput();
            break;
        case GO:
            status = RealInput();
            break;
        case EXIT:
            break;
        }
    }
}

int main()
{
    InputMenu();
    return 0;
}
