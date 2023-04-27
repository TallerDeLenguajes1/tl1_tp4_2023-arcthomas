#include <stdio.h>
#include <stdlib.h>

struct Tarea
{
    int TareaID;       // Numerado en ciclo iterativo
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} typedef Tarea;

struct Nodo
{
    Tarea T;
    struct Nodo *siguiente;
} typedef Nodo;

void crearNodo(Nodo **start, int id);
void mostrarPendientesYListar(Nodo **tPendientes, Nodo **tRealizadas);
void mostrarLista(Nodo *lista);
void buscarTarea(Nodo *tPendientes, Nodo *tRealizadas);

int main()
{
    printf("Bienvenido a la interfaz de gestión de tareas, a continuación seleccione una funcion.\n");
    int sel = 0, sel2 = 0, slLista = 0; // Selectores
    int idC = 1;                        // Contador de IDs
    Nodo *TareasPendientes = NULL;
    Nodo *TareasRealizadas = NULL;
    while (sel != 5)
    {
        printf("\n-- Menu --\n");
        printf("\n1- Agregar tareas\n2- Listar pendientes\n3- Mostrar una lista\n4- Buscar una tarea por ID\n5- Salir\nProgram: ");
        fflush(stdin);
        scanf("%d", &sel);
        switch (sel)
        {
        case 1:
            while (sel2 != 2)
            {
                printf("Agregar una tarea a la lista?\n1- Si\n2- No\nProgram: ");
                fflush(stdin);
                scanf("%d", &sel2);
                if (sel2 == 1)
                {
                    crearNodo(&TareasPendientes, idC);
                    idC++;
                }
            }
            break;
        case 2:
            mostrarPendientesYListar(&TareasPendientes, &TareasRealizadas);
            break;
        case 3:
            printf("\nSeleccione una lista:\n1- Tareas pendientes\n2- Tareas realizadas\nProgram: ");
            fflush(stdin);
            scanf("%d", &slLista);
            if (slLista == 1)
            {
                mostrarLista(TareasPendientes);
            }
            else
            {
                mostrarLista(TareasRealizadas);
            }
            break;
        case 4:
            buscarTarea(TareasPendientes, TareasRealizadas);
            break;
        default:
            break;
        }
    }
}

void crearNodo(Nodo **start, int id)
{
    Nodo *NNodo = (Nodo *)malloc(sizeof(Nodo));
    NNodo->T.TareaID = id;
    NNodo->T.Descripcion = (char *)malloc(50 * sizeof(char));
    printf("Ingrese una descripcion: ");
    fflush(stdin);
    gets(NNodo->T.Descripcion);
    NNodo->T.Duracion = rand() % (100 - 10 + 1) + 10;
    NNodo->siguiente = NULL;
    if (*start == NULL)
    {
        *start = NNodo;
    }
    else
    {
        Nodo *aux = *start;
        while (aux->siguiente != NULL)
        {
            aux = aux->siguiente;
        }
        aux->siguiente = NNodo;
    }
}

void mostrarPendientesYListar(Nodo **tPendientes, Nodo **tRealizadas)
{
    Nodo *aux = *tPendientes;
    Nodo *anterior = NULL;
    Nodo *nodoAMover = NULL;
    int slAux;
    printf("\n-- Lista de tareas pendientes --\n\n");
    while (aux != NULL)
    {
        nodoAMover = NULL;
        printf("ID de la Tarea: %d\n", aux->T.TareaID);
        printf("Descripcion: ");
        puts(aux->T.Descripcion);
        printf("Duracion: %d\n", aux->T.Duracion);
        printf("Se realizo?\n1- Si\n2- No\nProgram: ");
        fflush(stdin);
        scanf("%d", &slAux);
        if (slAux == 1)
        {
            nodoAMover = aux;
            if (anterior == NULL)
            {
                *tPendientes = aux->siguiente;
            }
            else
            {
                anterior->siguiente = aux->siguiente;
            }
        }
        anterior = aux;
        aux = aux->siguiente;
        if (nodoAMover != NULL)
        {
            nodoAMover->siguiente = NULL;
            if (*tRealizadas == NULL)
            {
                *tRealizadas = nodoAMover;
            }
            else
            {
                Nodo *ultRealizado = *tRealizadas;
                while (ultRealizado->siguiente != NULL)
                {
                    ultRealizado = ultRealizado->siguiente;
                }
                ultRealizado->siguiente = nodoAMover;
            }
            printf("\n-- Tarea movida a Tarea Realizadas --\n");
        }
    }
}

void mostrarLista(Nodo *lista)
{
    Nodo *aux = lista;
    while (aux != NULL)
    {
        printf("ID de la Tarea: %d\n", aux->T.TareaID);
        printf("Descripcion: ");
        puts(aux->T.Descripcion);
        printf("Duracion: %d\n", aux->T.Duracion);
        aux = aux->siguiente;
    }
}

void buscarTarea(Nodo *tPendientes, Nodo *tRealizadas)
{
    int idS;
    int find = 0;
    printf("\nIngrese un ID a buscar: ");
    fflush(stdin);
    scanf("%d", &idS);
    Nodo *aux = tPendientes;
    while (aux != NULL)
    {
        if (aux->T.TareaID == idS)
        {
            find = 1;
            printf("ID de la Tarea: %d\n", aux->T.TareaID);
            printf("Descripcion: ");
            puts(aux->T.Descripcion);
            printf("Duracion: %d\n", aux->T.Duracion);
            printf("Estado: Pendiente\n");
        }
        aux = aux->siguiente;
    }
    Nodo *auxR = tRealizadas;
    while (auxR != NULL)
    {
        if (auxR->T.TareaID == idS)
        {
            find = 1;
            printf("ID de la Tarea: %d\n", auxR->T.TareaID);
            printf("Descripcion: ");
            puts(auxR->T.Descripcion);
            printf("Duracion: %d\n", auxR->T.Duracion);
            printf("Estado: Realizada\n");
        }
        auxR = auxR->siguiente;
    }
    if (find == 0)
    {
        printf("\nNo se encontro ninguna tarea\n");
    }
}