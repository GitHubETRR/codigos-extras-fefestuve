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
        printf("%02X", *puntero);
    }
}
