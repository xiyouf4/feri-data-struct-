#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

typedef enum choice {
    INIT = 1,
    ADD,
    SUBTRACT,
    RIDE,
    DIVIDE,
    COEFF,
    EXIT,
} choice_t;

choice_t InputMenu();
choice_t AddMenu();

#endif
