//El código funciona, pero cada vez que debería poner 00 pone un solo 0.
#include <stdio.h>

typedef union numero{
    float flotante;
    unsigned char caracter;
}numero_t;

int main(void){
    numero_t num;
    printf("\nIngresa el valor del numero: ");
    scanf("%f", &num.flotante);

    unsigned char *puntero = &num.caracter;

    for(int i = 3; i>=0; i--, puntero--){
        printf("%X", *puntero);
    }
}