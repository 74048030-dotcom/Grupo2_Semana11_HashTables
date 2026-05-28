// =============================================================
// GRUPO 2 - SEMANA 11 - Hash Tables (Direccionamiento Abierto)
// Universidad Continental - Estructura de Datos - Seccion Viernes
//
// Programa: Registro de materias universitarias
// Clave: codigo de materia (ej. "INF101")
// Valor: nombre de materia  (ej. "Algoritmica I")
//
// Implementa los tres metodos de sondeo:
//   1 = Lineal,  2 = Cuadratico,  3 = Doble Hashing
// Con Lazy Deletion (eliminacion con marcadores).
// =============================================================

#include <iostream>
#include <string>
using namespace std;

const int TAM = 11;  // numero primo: facilita la distribucion

// Estados posibles de cada cubeta
enum Estado { VACIO, OCUPADO, ELIMINADO };

struct Entrada {
    string clave;
    string valor;
    Estado estado;
};

struct TablaHash {
    int tamanio;
    int numElementos;
    Entrada* tabla;

    // Constructor: inicializa todas las cubetas como VACIO
    void inicializar(int t) {
        tamanio = t;
        numElementos = 0;
        tabla = new Entrada[tamanio];
        for (int i = 0; i < tamanio; i++) {
            tabla[i].estado = VACIO;
        }
    }

    // Funcion hash primaria - djb2 modificada
    int h1(string clave) {
        unsigned long h = 5381;
        for (int i = 0; i < (int)clave.length(); i++) {
            h = ((h << 5) + h) + clave[i];  // h * 33 + c
        }
        return h % tamanio;
    }

    // Funcion hash secundaria - usada en doble hashing
    // Nunca debe retornar 0
    int h2(string clave) {
        unsigned long h = 0;
        for (int i = 0; i < (int)clave.length(); i++) {
            h = h * 31 + clave[i];
        }
        return 1 + (h % (tamanio - 1));
    }

    // Calcula el indice segun el metodo de sondeo
    // metodo: 1 = lineal, 2 = cuadratico, 3 = doble hashing
    int sondear(string clave, int i, int metodo) {
        int base = h1(clave);
        if (metodo == 1) {
            return (base + i) % tamanio;
        } else if (metodo == 2) {
            return (base + i * i) % tamanio;
        } else {
            return (base + i * h2(clave)) % tamanio;
        }
    }

    // Inserta un par (clave, valor) usando el metodo de sondeo elegido
    // Devuelve el numero de pasos consumidos
    int insertar(string clave, string valor, int metodo) {
        if (numElementos >= tamanio) {
            cout << "  >> Tabla llena. No se puede insertar." << endl;
            return -1;
        }
        for (int i = 0; i < tamanio; i++) {
            int pos = sondear(clave, i, metodo);
            if (tabla[pos].estado != OCUPADO) {
                tabla[pos].clave = clave;
                tabla[pos].valor = valor;
                tabla[pos].estado = OCUPADO;
                numElementos++;
                return i + 1;  // pasos realizados
            }
            // si la cubeta tiene la misma clave, actualizamos
            if (tabla[pos].clave == clave) {
                tabla[pos].valor = valor;
                return i + 1;
            }
        }
        return -1;
    }

    // Busca la clave - devuelve el valor o "" si no existe
    // Tambien retorna por referencia el numero de pasos
    string buscar(string clave, int metodo, int& pasos) {
        for (int i = 0; i < tamanio; i++) {
            int pos = sondear(clave, i, metodo);
            pasos = i + 1;
            if (tabla[pos].estado == VACIO) {
                return "";  // no existe
            }
            if (tabla[pos].estado == OCUPADO && tabla[pos].clave == clave) {
                return tabla[pos].valor;
            }
            // si estado == ELIMINADO seguimos buscando
        }
        return "";
    }

    // Elimina con Lazy Deletion (marca la cubeta como ELIMINADO)
    bool eliminar(string clave, int metodo) {
        for (int i = 0; i < tamanio; i++) {
            int pos = sondear(clave, i, metodo);
            if (tabla[pos].estado == VACIO) return false;
            if (tabla[pos].estado == OCUPADO && tabla[pos].clave == clave) {
                tabla[pos].estado = ELIMINADO;
                numElementos--;
                return true;
            }
        }
        return false;
    }

    // Muestra el contenido completo de la tabla
    void mostrar() {
        cout << "\n+-----+----------+----------------------+-----------+" << endl;
        cout << "| Pos | Clave    | Valor                | Estado    |" << endl;
        cout << "+-----+----------+----------------------+-----------+" << endl;
        for (int i = 0; i < tamanio; i++) {
            cout << "| " << (i < 10 ? " " : "") << i << "  | ";
            if (tabla[i].estado == OCUPADO) {
                cout << tabla[i].clave;
                for (int k = tabla[i].clave.length(); k < 8; k++) cout << " ";
                cout << " | " << tabla[i].valor;
                for (int k = tabla[i].valor.length(); k < 20; k++) cout << " ";
                cout << " | OCUPADO   |";
            } else if (tabla[i].estado == ELIMINADO) {
                cout << "----     |                      | ELIMINADO |";
            } else {
                cout << "         |                      | VACIO     |";
            }
            cout << endl;
        }
        cout << "+-----+----------+----------------------+-----------+" << endl;
        cout << " Elementos: " << numElementos
             << "  |  Factor de carga: "
             << (float)numElementos / tamanio << endl;
    }
};

// =============================================================
// FUNCION COMPARATIVA - sondeo lineal vs doble hashing
// Inserta los mismos datos en dos tablas y muestra los pasos
// =============================================================
void compararMetodos() {
    cout << "\n========================================" << endl;
    cout << " COMPARATIVA: Lineal vs Doble Hashing" << endl;
    cout << "========================================" << endl;

    TablaHash tLineal, tDoble;
    tLineal.inicializar(TAM);
    tDoble.inicializar(TAM);

    string claves[]  = {"INF101","INF102","INF103","MAT201","MAT202","FIS301"};
    string valores[] = {"Algoritmica I","Algoritmica II","Estr. Datos",
                        "Calculo I","Calculo II","Fisica I"};

    cout << "\n| Clave    | Lineal | Doble Hash |" << endl;
    cout << "|----------|--------|------------|" << endl;
    int totalLin = 0, totalDob = 0;
    for (int i = 0; i < 6; i++) {
        int pL = tLineal.insertar(claves[i], valores[i], 1);
        int pD = tDoble.insertar(claves[i], valores[i], 3);
        totalLin += pL; totalDob += pD;
        cout << "| " << claves[i] << "   |   " << pL
             << "    |     " << pD << "      |" << endl;
    }
    cout << "|----------|--------|------------|" << endl;
    cout << "| TOTAL    |   " << totalLin << "    |     "
         << totalDob << "     |" << endl;
    cout << "| Promedio | " << (float)totalLin/6
         << "  | " << (float)totalDob/6 << "    |" << endl;
}

// =============================================================
// MENU PRINCIPAL
// =============================================================
int main() {
    TablaHash tabla;
    tabla.inicializar(TAM);

    int metodo = 1;
    int opcion;
    string clave, valor;

    cout << "Seleccione metodo de sondeo:" << endl;
    cout << "  1 = Lineal,  2 = Cuadratico,  3 = Doble Hashing" << endl;
    cout << "Opcion: ";
    cin >> metodo;
    if (metodo < 1 || metodo > 3) metodo = 1;

    do {
        cout << "\n===== AGENDA DE MATERIAS (Open Addressing) =====" << endl;
        cout << "[1] Insertar materia" << endl;
        cout << "[2] Buscar materia" << endl;
        cout << "[3] Eliminar materia" << endl;
        cout << "[4] Mostrar tabla completa" << endl;
        cout << "[5] Ejecutar comparativa Lineal vs Doble Hashing" << endl;
        cout << "[6] Cambiar metodo de sondeo" << endl;
        cout << "[0] Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Codigo: "; cin >> clave;
            cout << "Nombre: "; cin.ignore(); getline(cin, valor);
            int pasos = tabla.insertar(clave, valor, metodo);
            if (pasos > 0)
                cout << "  >> Insertado en " << pasos << " paso(s)." << endl;
        }
        else if (opcion == 2) {
            cout << "Codigo a buscar: "; cin >> clave;
            int pasos = 0;
            string r = tabla.buscar(clave, metodo, pasos);
            if (r == "") cout << "  >> No encontrada (" << pasos << " pasos)" << endl;
            else cout << "  >> Encontrada: " << r << " (" << pasos << " pasos)" << endl;
        }
        else if (opcion == 3) {
            cout << "Codigo a eliminar: "; cin >> clave;
            if (tabla.eliminar(clave, metodo))
                cout << "  >> Eliminada (marcada como ELIMINADO)." << endl;
            else
                cout << "  >> No se encontro la clave." << endl;
        }
        else if (opcion == 4) {
            tabla.mostrar();
        }
        else if (opcion == 5) {
            compararMetodos();
        }
        else if (opcion == 6) {
            cout << "Nuevo metodo (1/2/3): "; cin >> metodo;
            if (metodo < 1 || metodo > 3) metodo = 1;
        }
    } while (opcion != 0);

    return 0;
}
