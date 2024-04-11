#include <stdio.h>

union numeros{
    float var;
    unsigned char vect[4];
    struct{
        unsigned int mantisa : 23;
        unsigned int exponente : 8;    
        unsigned int signo : 1;
    }bits;
};

void menu();
int ingresar_opcion();
union numeros ingresar_numero(union numeros);
void print_numero(union numeros);



int main(void){
    union numeros numero;
    int opcion;
    do{
        menu();
        opcion = ingresar_opcion();

        switch (opcion){

            case 1:
                numero=ingresar_numero(numero);
                break;
            
            case 2:
                print_numero(numero);
                break;
        }
    }while(opcion != 3);

    return 0;
}

void menu(){
    printf("\n----MENU----\n\n");
    printf("1.Ingresar numero\n");
    printf("2.Ver numero\n");
    printf("3.Salir del programa\n");
}

int ingresar_opcion(){
    int opcion;
    do{
        scanf("%d", &opcion);
    }while(opcion!=1 && opcion!=2 && opcion!=3);

    return opcion;
}

union numeros ingresar_numero(union numeros numero){
    printf("Ingrese un numero flotante\n");
    scanf("%f", &numero.var);

    return numero;
}


void print_numero(union numeros numero){
    printf("El numero ingresado esta guardado en la memoria como: 0x");
    for(int i = 4; i>0; i--){
        printf("%X", numero.vect[i]);
    }
    printf(" en hexadecimal\n");

    if(numero.bits.signo==0){
        printf("El signo es positivo\n"); 
    }
    else{
        printf("El signo es negativo\n");
    }

    printf("La mantisa es %X\n",numero.bits.mantisa);
    printf("El exponente es %X\n", numero.bits.exponente-127);
    printf("El numero ingresado fue %f\n", numero.var);
    
}