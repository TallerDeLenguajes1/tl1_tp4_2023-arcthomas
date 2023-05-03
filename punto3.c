#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
void moverNodo(Nodo **lista, int id, Nodo **listaDestino);
void mostrarPendientesYListar(Nodo **tPendientes, Nodo **tRealizadas, Nodo **tEnProceso);
void mostrarLista(Nodo *lista);
void buscarYGestionar(Nodo **tPendientes, Nodo **tEnProceso, Nodo **tRealizadas);
void mostrarDatosLista(Nodo *lista);
void eliminar(Nodo **lista, int id);

int main()
{
    srand(time(NULL));
    printf("Bienvenido a la interfaz de gestión de tareas, a continuación seleccione una funcion.\n");
    int sel = 0, sel2 = 0, slLista = 0, sel3 = 0; // Selectores
    int idC = 1;                                  // Contador de IDs
    Nodo *TareasPendientes = NULL;
    Nodo *TareasRealizadas = NULL;
    Nodo *TareasEnProceso = NULL;
    while (sel != 6)
    {
        printf("\n-- Menu --\n");
        printf("\n1- Agregar tareas\n2- Listar pendientes\n3- Mostrar una lista\n4- Buscar una tarea por ID\n5- Mostrar datos de una lista\n6- Salir\nProgram: ");
        fflush(stdin);
        scanf("%d", &sel);
        switch (sel)
        {
        case 1:
            sel2 = 0;
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
            mostrarPendientesYListar(&TareasPendientes, &TareasRealizadas, &TareasEnProceso);
            break;
        case 3:
            printf("\nSeleccione una lista:\n1- Tareas pendientes\n2- Tareas realizadas\n3- Tareas en proceso\nProgram: ");
            fflush(stdin);
            scanf("%d", &slLista);
            switch (slLista)
            {
            case 1:
                mostrarLista(TareasPendientes);
                break;
            case 2:
                mostrarLista(TareasRealizadas);
                break;
            case 3:
                mostrarLista(TareasEnProceso);
            default:
                break;
            }
            break;
        case 4:
            buscarYGestionar(&TareasPendientes, &TareasEnProceso, &TareasRealizadas);
            break;
        case 5:
            sel3 = 0;
            printf("Seleccione la lista que quiera mostrar sus datos:\n1- Tareas pendientes\n2- Tareas en proceso\n3- Tareas realizadas\nProgram: ");
            fflush(stdin);
            scanf("%d", &sel3);
            switch (sel3)
            {
            case 1:
                mostrarDatosLista(TareasPendientes);
                break;
            case 2:
                mostrarDatosLista(TareasEnProceso);
                break;
            case 3:
                mostrarDatosLista(TareasRealizadas);
                break;
            default:
                break;
            }
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

void moverNodo(Nodo **lista, int id, Nodo **listaDestino)
{
    Nodo *aux = *lista;
    Nodo *anterior = NULL;
    int finish = 0;
    while (aux != NULL && finish != 1)
    {
        if (aux->T.TareaID == id && finish != 1)
        {
            if (anterior == NULL)
            {
                *lista = aux->siguiente;
            }
            else
            {
                anterior->siguiente = aux->siguiente;
            }
            aux->siguiente = NULL;
            if (*listaDestino == NULL)
            {
                *listaDestino = aux;
            }
            else
            {
                Nodo *ultRealizado = *listaDestino;
                while (ultRealizado->siguiente != NULL)
                {
                    ultRealizado = ultRealizado->siguiente;
                }
                ultRealizado->siguiente = aux;
            }
            printf("\n-- Tarea movida a la lista de destino --\n");
            finish = 1;
        }
        if (aux->siguiente != NULL)
        {
            anterior = aux;
            aux = aux->siguiente;
        }
    }
}

void mostrarPendientesYListar(Nodo **tPendientes, Nodo **tRealizadas, Nodo **tEnProceso)
{
    Nodo *aux = *tPendientes;
    Nodo *anterior = NULL;
    int id;
    int slAux;
    if (aux != NULL)
    {
        printf("\n-- Lista de tareas pendientes --\n\n");
        while (aux != NULL)
        {
            slAux = 0;
            printf("ID de la Tarea: %d\n", aux->T.TareaID);
            printf("Descripcion: ");
            puts(aux->T.Descripcion);
            printf("Duracion: %d\n", aux->T.Duracion);
            printf("Acciones para la tarea\n1- Mover a la lista en proceso\n2- Mover a tareas realizadas\n3- Eliminar la tarea\n4- No hacer nada\nProgram: ");
            fflush(stdin);
            scanf("%d", &slAux);
            switch (slAux)
            {
            case 1:
                moverNodo(tPendientes, aux->T.TareaID, tEnProceso);
                if (anterior == NULL)
                {
                    aux = *tPendientes;
                }
                else
                {
                    aux = anterior->siguiente;
                }
                break;
            case 2:
                moverNodo(tPendientes, aux->T.TareaID, tRealizadas);
                if (anterior == NULL)
                {
                    aux = *tPendientes;
                }
                else
                {
                    aux = anterior->siguiente;
                }
                break;
            case 3:
                eliminar(tPendientes, aux->T.TareaID);
                aux = NULL;
                break;
            case 4:
                if (aux != NULL)
                {
                    anterior = aux;
                    aux = aux->siguiente;
                }
                break;
            default:
                break;
            }
        }
        if (aux != NULL)
        {
            anterior = aux;
            aux = aux->siguiente;
        }
    }
    else
    {
        printf("\nNo hay pendientes que listar.\n");
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

void buscarYGestionar(Nodo **tPendientes, Nodo **tEnProceso, Nodo **tRealizadas)
{
    int idS;
    int slAux2, sl2, sl3;
    int find = 0, tmoved = 0;
    printf("\nIngrese un ID a buscar: ");
    fflush(stdin);
    scanf("%d", &idS);
    Nodo *aux = *tPendientes;
    while (aux != NULL)
    {
        if (aux->T.TareaID == idS)
        {
            slAux2 = 0;
            find = 1;
            printf("ID de la Tarea: %d\n", aux->T.TareaID);
            printf("Descripcion: ");
            puts(aux->T.Descripcion);
            printf("Duracion: %d\n", aux->T.Duracion);
            printf("Estado: Pendiente\n");
            printf("Seleccione una accion para esta tarea\n1- Mover a otra lista\n2- Eliminar\n3- No hacer nada\nProgram: ");
            fflush(stdin);
            scanf("%d", &slAux2);
            switch (slAux2)
            {
            case 1:
                sl3 = 0;
                printf("Seleccione una lista\n1- Tareas en proceso\n2- Tareas realizadas\n3- Cancelar\nProgram: ");
                fflush(stdin);
                scanf("%d", &sl3);
                switch (sl3)
                {
                case 1:
                    moverNodo(tPendientes, idS, tEnProceso);
                    aux = NULL;
                    tmoved = 1;
                    break;
                case 2:
                    moverNodo(tPendientes, idS, tRealizadas);
                    aux = NULL;
                    tmoved = 1;
                    break;
                default:
                    break;
                }
                break;
            case 2:
                sl2 = 0;
                printf("Esta seguro de eliminar la tarea %d?\n1- Si\2- No\nProgram: ", aux->T.TareaID);
                fflush(stdin);
                scanf("%d", &sl2);
                if (sl2 == 1)
                {
                    eliminar(tPendientes, idS);
                }
                break;
            default:
                break;
            }
        }
        if (aux != NULL)
        {
            aux = aux->siguiente;
        }
    }
    Nodo *auxR = *tRealizadas;
    while (auxR != NULL && tmoved != 1)
    {
        if (auxR->T.TareaID == idS)
        {
            slAux2 = 0;
            find = 1;
            printf("ID de la Tarea: %d\n", auxR->T.TareaID);
            printf("Descripcion: ");
            puts(auxR->T.Descripcion);
            printf("Duracion: %d\n", auxR->T.Duracion);
            printf("Estado: Realizada\n");
            printf("Seleccione una accion para esta tarea\n1- Mover a otra lista\n2- Eliminar\n3- No hacer nada\nProgram: ");
            fflush(stdin);
            scanf("%d", &slAux2);
            switch (slAux2)
            {
            case 1:
                sl3 = 0;
                printf("Seleccione una lista\n1- Tareas pendientes\n2- Tareas en proceso\n3- Cancelar\nProgram: ");
                fflush(stdin);
                scanf("%d", &sl3);
                switch (sl3)
                {
                case 1:
                    moverNodo(tRealizadas, idS, tPendientes);
                    aux = NULL;
                    tmoved = 1;
                    break;
                case 2:
                    moverNodo(tRealizadas, idS, tEnProceso);
                    aux = NULL;
                    tmoved = 1;
                    break;
                default:
                    break;
                }
                break;
            case 2:
                sl2 = 0;
                printf("Esta seguro de eliminar la tarea %d?\n1- Si\2- No\nProgram: ", aux->T.TareaID);
                fflush(stdin);
                scanf("%d", &sl2);
                if (sl2 == 1)
                {
                    eliminar(tRealizadas, idS);
                }
                break;
            default:
                break;
            }
        }
        if (auxR != NULL)
        {
            auxR = auxR->siguiente;
        }
    }
    Nodo *auxEP = *tEnProceso;
    while (auxEP != NULL && tmoved != 1)
    {
        if (auxEP->T.TareaID == idS)
        {
            slAux2 = 0;
            find = 1;
            printf("ID de la Tarea: %d\n", auxEP->T.TareaID);
            printf("Descripcion: ");
            puts(auxEP->T.Descripcion);
            printf("Duracion: %d\n", auxEP->T.Duracion);
            printf("Estado: En proceso\n");
            printf("Seleccione una accion para esta tarea\n1- Mover a otra lista\n2- Eliminar\n3- No hacer nada\nProgram: ");
            fflush(stdin);
            scanf("%d", &slAux2);
        }
        switch (slAux2)
        {
        case 1:
            sl3 = 0;
            printf("Seleccione una lista\n1- Tareas pendientes\n2- Tareas realizadas\n3- Cancelar\nProgram: ");
            fflush(stdin);
            scanf("%d", &sl3);
            switch (sl3)
            {
            case 1:
                moverNodo(tEnProceso, idS, tPendientes);
                aux = NULL;
                tmoved = 1;
                break;
            case 2:
                moverNodo(tEnProceso, idS, tRealizadas);
                aux = NULL;
                tmoved = 1;
                break;
            default:
                break;
            }
            break;
        case 2:
            sl2 = 0;
            printf("Esta seguro de eliminar la tarea %d?\n1- Si\2- No\nProgram: ", aux->T.TareaID);
            fflush(stdin);
            scanf("%d", &sl2);
            if (sl2 == 1)
            {
                eliminar(tEnProceso, idS);
            }
            break;
        default:
            break;
        }
        if (auxEP != NULL)
        {
            auxEP = auxEP->siguiente;
        }
    }
    if (find == 0)
    {
        printf("\nNo se encontro ninguna tarea\n");
    }
    idS = 0;
}

void eliminar(Nodo **lista, int id)
{
    Nodo *aux = *lista;
    Nodo *anterior = NULL;
    while (aux != NULL)
    {
        if (aux->T.TareaID == id)
        {
            if (anterior == NULL)
            {
                *lista = aux->siguiente;
                free(aux);
            }
            else
            {
                anterior->siguiente = aux->siguiente;
                free(aux);
            }
        }
        anterior = aux;
        aux = aux->siguiente;
    }
    printf("La tarea se elimino correctamente");
}

void mostrarDatosLista(Nodo *lista)
{
    int cant = 0, duracionTotal = 0;
    Nodo *aux = lista;
    while (aux != NULL)
    {
        cant++;
        duracionTotal += aux->T.Duracion;
        aux = aux->siguiente;
    }
    printf("\n-- Datos de la lista seleccionada --\n\n");
    printf("Cantidad de tareas: %d\n Duracion total de las tareas de esta lista: %d", cant, duracionTotal);
}