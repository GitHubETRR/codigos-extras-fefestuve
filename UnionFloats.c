#include <stdio.h>

union numeros{
    float var;
    unsigned char vect[4];
};

int main(void){
    union numeros numero;
    printf("Ingresa un numero \n");
    scanf("%f",&numero.var);
    printf("El numero que ingresaste esta guardado en la memoria como ");
    for (int i = 3; i >= 0; i--){
        printf("%x",numero.vect[i]);
    }
    printf(" en hexadecimal\n");
}