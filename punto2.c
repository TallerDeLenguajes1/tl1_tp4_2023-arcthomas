#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea
{
    int tareaID;
    char *desc;
    int duracion;
} Tarea;

int pedirNumTareas();
void mostrarTareas(Tarea *tareas[], int cantTareas);
void moverTareas(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas);
void buscarTareasId(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas);
void buscarTareasPalabra(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas);

int main()
{
    int numTareas, select = 0, sAux;
    numTareas = pedirNumTareas();
    srand(time(NULL));
    Tarea **tareas = (Tarea **)malloc(numTareas * sizeof(Tarea *));
    Tarea **tareasRealizadas = (Tarea **)malloc(numTareas * sizeof(Tarea *));

    for (int i = 0; i < numTareas; i++)
    {
        tareasRealizadas[i] = NULL;
    }

    for (int i = 0; i < numTareas; i++)
    {
        tareas[i] = (Tarea *)malloc(sizeof(Tarea));
        printf("Ingrese los datos de la tarea %d\n", i + 1);
        tareas[i]->tareaID = i + 1;
        tareas[i]->desc = (char *)malloc(50 * sizeof(char));
        printf("Ingrese la desc: ");
        fflush(stdin);
        gets(tareas[i]->desc);
        tareas[i]->duracion = rand() % (100 - 10 + 1) + 10;
    }

    moverTareas(tareas, tareasRealizadas, numTareas);
    printf("\n-- Bienvenido a la interfaz de tareas --\n");
    while (select != 4)
    {
        printf("\nMenu\n");
        printf("1- Buscar una tarea por ID\n2- Buscar una tarea por palabra clave\n3- Mostrar una lista por pantalla\n4- Salir\n");
        printf("Seleccione una opcion: ");
        fflush(stdin);
        scanf("%d", &select);
        switch (select)
        {
        case 1:
            buscarTareasId(tareas, tareasRealizadas, numTareas);
            break;
        case 2:
            buscarTareasPalabra(tareas, tareasRealizadas, numTareas);
            break;
        case 3:
            printf("\nListas\n1- Tareas pendientes\n2- Tareas realizadas\n");
            printf("Seleccione una lista: ");
            scanf("%d", &sAux);
            if (sAux == 1)
            {
                mostrarTareas(tareas, numTareas);
            }
            else if (sAux == 2)
            {
                mostrarTareas(tareasRealizadas, numTareas);
            }
            break;
        default:
            break;
        }
    }
    for (int i = 0; i < numTareas; i++)
    {
        if (tareas[i] != NULL)
        {
            free(tareas[i]->desc);
            free(tareas[i]);
        }
        if (tareasRealizadas[i] != NULL)
        {
            free(tareasRealizadas[i]->desc);
            free(tareasRealizadas[i]);
        }
    }
    free(tareasRealizadas);
    free(tareas);
    return 0;
}
int pedirNumTareas()
{
    int num;
    printf("Ingrese el numero de tareas: ");
    scanf("%d", &num);
    return num;
}

void mostrarTareas(Tarea *tareas[], int cantTareas)
{
    printf("Datos de las tareas\n");
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i] != NULL)
        {
            printf("ID de la tarea: %d\n", tareas[i]->tareaID);
            printf("Descripcion: ");
            puts(tareas[i]->desc);
            printf("Duracion: %d\n", tareas[i]->duracion);
        }
    }
}

void moverTareas(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas)
{
    printf("Datos de las tareas\n");
    for (int i = 0; i < cantTareas; i++)
    {
        int realizada;

        printf("ID de la tarea: %d\n", tareas[i]->tareaID);
        printf("Descripcion: ");
        puts(tareas[i]->desc);
        printf("Duracion: %d\n", tareas[i]->duracion);
        printf("Se realizo? 1- Si, 0- No: ");
        scanf("%d", &realizada);
        if (realizada)
        {
            tareasRealizadas[i] = tareas[i];
            tareas[i] = NULL;
        }
    }
}

void buscarTareasId(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas)
{
    int idB, aux, pr, mis;
    printf("Modulo para buscar tareas por Id, ingrese un id: ");
    fflush(stdin);
    scanf("%d", &idB);
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i] != NULL) // Si hay una tarea en pendientes...
        {
            if (idB == tareas[i]->tareaID)
            {
                printf("\n! Tarea encontrada !\n");
                aux = i; // Encuentra una coincidencia en el ID y guardo donde se ubica la tarea, termino el bucle
                pr = 0;  // Esto es para saber si en tareas pendientes o realizadas
                mis = 0; // Bool para control de faltantes
                break;
            }
            else
            {
                mis = 1; // Faltante en pendiente si es 1
            }
        }
        else if (tareasRealizadas[i] != NULL)
        {
            if (idB == tareasRealizadas[i]->tareaID)
            {
                printf("\n! Tarea encontrada !\n");
                aux = i;
                pr = 1;
                mis = 0;
                break;
            }
            else
            {
                mis = 2; // Faltante en realizadas si es 2
            }
        }
    }
    if (mis == 0) // Si no falta una tarea:
    {
        printf("Detalles de la tarea encontrada:\n");
        if (pr == 0)
        {
            printf("ID de la tarea: %d\n", tareas[aux]->tareaID);
            printf("Descripcion: ");
            puts(tareas[aux]->desc);
            printf("Duracion: %d\n", tareas[aux]->duracion);
            printf("Estado: Pendiente\n");
        }
        else
        {
            printf("ID de la tarea: %d\n", tareasRealizadas[aux]->tareaID);
            printf("Descripcion: ");
            puts(tareasRealizadas[aux]->desc);
            printf("Duracion: %d\n", tareasRealizadas[aux]->duracion);
            printf("Estado: Realizada\n");
        }
    }
    else
    {
        switch (mis)
        {
        case 1:
            printf("No se encontro ninguna coincidencia en tareas pendientes.\n");
            break;
        case 2:
            printf("No se encontro ninguna coincidencia en tareas realizadas.\n");
            break;
        default:
            break;
        }
    }
}

void buscarTareasPalabra(Tarea *tareas[], Tarea *tareasRealizadas[], int cantTareas)
{
    char palabra[20];
    char *result;
    int find, aux, pr;
    printf("Ingrese palabra clave: ");
    fflush(stdin);
    gets(palabra);
    for (int i = 0; i < cantTareas; i++)
    {
        if (tareas[i] != NULL) // Si hay una tarea en pendientes...
        {
            result = strstr(tareas[i]->desc, palabra); // Busco la palabra clave en la desc de las Tareas
            if (result != NULL)                        // Si no es NULL la palabra...
            {
                find = strcmp(result, palabra); // Compara y guarda en find
                if (find == 0)
                {
                    printf("\n! Tarea encontrada !\n");
                    aux = i; // Encuentra una coincidencia en 0 y guardo donde se ubica la tarea, termino el bucle
                    pr = 0;  // Esto es para saber si en tareas pendientes o realizadas
                    break;
                }
                else
                {
                    printf("No se encontro ninguna coincidencia en tareas pendientes.\n");
                }
            }
        }
        else if (tareasRealizadas[i] != NULL) // Si no encuentra en pendientes hace lo mismo en Tareas realizadas
        {
            result = strstr(tareasRealizadas[i]->desc, palabra);
            if (result != NULL)
            {
                find = strcmp(result, palabra);
                if (find == 0)
                {
                    printf("\n! Tarea encontrada !\n");
                    aux = i;
                    pr = 1;
                    break;
                }
                else
                {
                    printf("No se encontro ninguna coincidencia en tareas realizadas.\n");
                }
            }
        }
    }
    printf("Detalles de la tarea encontrada:\n");
    if (pr == 0)
    {
        printf("ID de la tarea: %d\n", tareas[aux]->tareaID);
        printf("Descripcion: ");
        puts(tareas[aux]->desc);
        printf("Duracion: %d\n", tareas[aux]->duracion);
        printf("Estado: Pendiente\n");
    }
    else
    {
        printf("ID de la tarea: %d\n", tareasRealizadas[aux]->tareaID);
        printf("Descripcion: ");
        puts(tareasRealizadas[aux]->desc);
        printf("Duracion: %d\n", tareasRealizadas[aux]->duracion);
        printf("Estado: Realizada\n");
    }
}