#include <stdio.h>

#define LETRAS_MAX 40
#define CANT_PERSONAS 5

typedef struct{
    char nombre[LETRAS_MAX];
    unsigned int edad;
    unsigned int salario;
}empleado;

empleado ingresarDatos(empleado persona);
void procesarDatos(empleado persona[], int cant);
void mostrarDatos(empleado persona[], int cant);
void printOpciones(void);

int main(void){

    empleado persona[CANT_PERSONAS];
    for(int i = 0; i<CANT_PERSONAS; i++){
        persona[i].edad=0;
        persona[i].salario=0;
    }
    unsigned int personasIngresadas = 0;
    printf("\n\n---MENU---");
    int opcionIngresada;

    do{
        printOpciones();
        printf("ingrese la opcion: ");
        scanf("%i", &opcionIngresada);  
        while(opcionIngresada!=1 && opcionIngresada!=2 && opcionIngresada!=3){
            printf("La opcion ingresada no se encuentra en el menu, ingrese 1, 2 o 3.\n");
            printf("ingrese la opcion: ");
            scanf("%i", &opcionIngresada);
        }

        switch(opcionIngresada){

            case 1:
            persona[personasIngresadas] = ingresarDatos(persona[personasIngresadas]);
            personasIngresadas++;
            break;

            case 2:
            mostrarDatos(persona, personasIngresadas);
            procesarDatos(persona, (personasIngresadas+1));
            break;
        }
        

    }while(opcionIngresada != 3);

    return 0;
}

void printOpciones(void){
    printf("\n\n1. Ingresar datos de un empleado\n");
    printf("2. Mostrar informacion\n");
    printf("3. Salir\n");
}

empleado ingresarDatos(empleado persona){
    printf("ingrese el nombre del empleado: ");
    scanf("\n%[^\n]%*c", &persona.nombre);
    printf("ingrese la edad del empleado: ");
    scanf("%i", &persona.edad);
    printf("ingrese el salario del empleado: ");
    scanf("%i", &persona.salario);
    return persona;
}
void procesarDatos(empleado persona[], int cant){
    int promedio=0;
    int maximo=0;
    for(int i = 0; i<cant; i++){
        if(persona[i].salario > persona[maximo].salario){
            maximo=i;
        }
        promedio+=persona[i].salario;
    }
    promedio/=cant;

    printf("%s tiene el salario maximo con: %i\n", persona[maximo].nombre, persona[maximo].salario);
    printf("El promedio es de: %i", promedio);
}
void mostrarDatos(empleado persona[], int cant){
    for(int i=0; i<cant; i++){
        printf("\n%i. Nombre: %s, Edad: %i, Salario: %i\n", i+1, persona[i].nombre, persona[i].edad, persona[i].salario);
    }
}