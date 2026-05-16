#include <iostream>
using namespace std;

struct lista {
    int valor;
    lista* prox;
};

struct pila {
    int valor;
    pila* prox;
};


/* INICIO PRIMITIVAS — LISTAS SIMPLEMENTE ENLAZADAS */

void insertarC(lista** p, int n) { //Inserción por cabeza
    lista* ax = new lista;
    ax->valor = n;
    ax->prox = NULL;

    if (*p == NULL) {
        *p = ax;
    }
    else {
        ax->prox = *p;
        *p = ax;
    }
}

void mostrarLista(lista* p) { //Imprime la lista
    lista* ax = p;

    while (ax) {
        cout << "[" << ax->valor << "]->";
        ax = ax->prox;
    }
    cout << "NULL";
}


/* FIN PRIMITIVAS — LISTAS SIMPLEMENTE ENLAZADAS */

/* INICIO PRIMITIVAS - PILAS */

void apilar(pila** p, int x) {
    /* Agrega x como tope de pila p */
    pila* ax = new pila; 
    ax->valor = x; 
    ax->prox = *p; 
    *p = ax;
};

int vacio(pila* p) {
    /* devuelve 1 si es vacia la pila, 0 si no lo es */
    return (p == NULL);
};

int tope(pila* p) {
    /* Devuelve el valor tope de la pila si no es vacia */
    if (!(vacio(p))) return p->valor;
    return 0;
};

void desapilar(pila** p) {
    /* Si no es vacia la pila, elimina el tope */
    if (!vacio(*p)) {
        pila* ax = *p;
        *p = (*p)->prox;
        delete ax;
    };
};

void mostrarPila(pila* p) { //Imprime la lista
    pila* ax = p;

    while (ax) {
        cout << "[" << tope(ax) << "]->";
        ax = ax->prox;
    }
    cout << "NULL";
}

/* FIN PRIMITIVAS - PILAS */


// Soluciones empiezan aquí
void separarDig(lista* p) {
    lista* ax = p;

    while (ax) {
        while ((ax->valor / 10) != 0) {
            lista* t = new lista;

            t->valor = ax->valor % 10;
            t->prox = ax->prox;
            ax->prox = t;
            ax->valor = ax->valor / 10;
        }
        ax = ax->prox;
    }
}

void eliminarComunesPila(pila** p, int n) {
    pila* ax = NULL;
    pila* t = NULL; //pila de los elementos a borrar

    bool yaExiste = false;

    while (!(vacio(*p))) {
        while (!(vacio(*p)) && tope(*p) != n) {
            apilar(&ax, tope(*p));
            desapilar(p);
            //cout << "TOPE (TRAS EL PRIMER WHILE): " << tope(*p) << "\n";

        }

        if (yaExiste == false) {
            yaExiste = true;
            apilar(&ax, tope(*p));
            desapilar(p);
            //cout << "TOPE NUEVO TRAS EL IF: \n" << tope(*p) << "\n";
        }
        else if (yaExiste == true) {
            apilar(&t, tope(*p));
            desapilar(p);
            //cout << "TOPE NUEVO TRAS EL ELSEIF: \n" << tope(*p) << "\n";

        }
    }
    delete t;

    while (!(vacio(ax))) {
        apilar(p, tope(ax));
        desapilar(&ax);
    }

    mostrarPila(*p);
}


int main() {
    int n = 0, op = -1, respuesta;
    lista* p = NULL; //Inicializo la cabeza de la lista
    pila* z = NULL;

    while (op != 0) {
        cout << "\n\n\t\tMENU BASE DE LISTAS\n\n";
        cout << "\t1. Insertar por cabeza.\n";
        cout << "\t2. Mostrar lista.\n";
        cout << "\t3. (PRACTICA) Separar dígitos. [LISTO]\n";
        cout << "\t4. (PRACTICA/PILA) Insertar números en la pila.\n";
        cout << "\t5. (PRACTICA/PILA) Mostrar pila.\n";
        cout << "\t6. (PRACTICA/PILA) Eliminar comunes de una pila.\n";

        cout << "\nSeleccione una opción del menú: ";
        cin >> op;

        switch (op) {

        case 1:
            cout << "Ingrese el número a insertar: ";
            cin >> n;
            system("cls");
            insertarC(&p, n);
            break;

        case 2:
            system("cls");
            mostrarLista(p);
            break;

        case 3:
            system("cls");
            separarDig(p);
            break;

        case 4:
            cout << "Ingrese un número a insertar en la pila: ";
            cin >> n;
            apilar(&z, n);
            system("cls");
            break;

        case 5:
            system("cls");
            mostrarPila(z);
            break;

        case 6:
            cout << "Ingrese un número a borrar: ";
            cin >> n;
            eliminarComunesPila(&z, n);
            break;
        }
    }

    system("pause");
    system("cls");

    return 0;
};