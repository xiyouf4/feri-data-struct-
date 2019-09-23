#include "polynomial.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *AddThem(char *numa, char *numb)
{
    for (int i = 0; i < 11; i++) {
        numa[i] += numb[i];
    }
    return numa;
}

char *SubtractThem(char *numa, char *numb)
{                                    
    for (int i = 0; i < 11; i++) {   
        numa[i] -= numb[i];          
    }                                
    return numa;                     
}                                    

char *DoAddMenu(const char *polynomial)
{
    char *num = (char *)malloc(sizeof(char)*11);
    memset(num, 0, 11*sizeof(char));
    size_t i = 0;
    for (i = 2; polynomial[i] != '\0'; i += 4) {
        int a = polynomial[i]-48;
        num[a] = polynomial[i-2]-48;
    }
    return num;
}

choice_t SubtractMenu()                                      
{                                                       
    char *polynomial = (char *)malloc(200*sizeof(char));
    memset(polynomial, 0, 200*sizeof(char));            
    printf("请输入你的第一个多项式：\n");               
    scanf("%s", polynomial);                            
    char *numa = DoAddMenu(polynomial);                 
    memset(polynomial, 0, 200*sizeof(char));            
    printf("请输入你的第二个多项式：\n");               
    scanf("%s", polynomial);                            
    char *numb = DoAddMenu(polynomial);                 
    char *answer = SubtractThem(numa, numb);                 
    printf("答案是：\n");                               
    for (int i = 0; i < 11; i++) {                      
        if (answer[i] != 0) {                           
            printf("%dx^%d+", answer[i], i);            
        }                                               
    }                                                   
    printf("0");                                        
    return INIT;                                        
}                                                       

choice_t AddMenu()
{
    char *polynomial = (char *)malloc(200*sizeof(char));
    memset(polynomial, 0, 200*sizeof(char));            
    printf("请输入你的第一个多项式：\n");
    scanf("%s", polynomial);
    char *numa = DoAddMenu(polynomial);
    memset(polynomial, 0, 200*sizeof(char));            
    printf("请输入你的第二个多项式：\n");
    scanf("%s", polynomial);             
    char *numb = DoAddMenu(polynomial);  
    char *answer = AddThem(numa, numb);
    printf("答案是：\n");
    for (int i = 0; i < 11; i++) {
        if (answer[i] != 0) {
            printf("%dx^%d+", answer[i], i);
        }
    }
    printf("0");
    free(polynomial);
    return INIT;
}

choice_t InputMenu()
{
    printf("\n1. 加法\n");
    printf("2. 减法\n");
    printf("3. 乘法\n");
    printf("4. 除法\n");
    printf("5. 求导\n");
    printf("6. 退出\n");
    int op;
    scanf("%d", &op);
    if (op == 1) {
        return ADD;
    } else if (op == 2) {
        return SUBTRACT;
    } else if (op == 6) {
        return EXIT;
    }
    return INIT;
}

void ShowInputMenu()
{
    choice_t status = INIT;
    while (status != EXIT) {
        switch (status) {
        case INIT:
            status = InputMenu();
            break;
        case ADD:
            status = AddMenu();
            break;
        case SUBTRACT:
            status = SubtractMenu();
            break;
        case RIDE:
            break;
        case DIVIDE:
            break;
        case COEFF:
            break;
        case EXIT:
            break;
        }
    }
}

int main()
{
    ShowInputMenu();
    return 0;
}
