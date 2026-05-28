// =============================================================
// GRUPO 2 - SEMANA 11 - Aplicacion de Hash Tables
// Universidad Continental - Estructura de Datos - Seccion Viernes
//
// Contador de frecuencia de palabras usando Hash Table
// con direccionamiento abierto (sondeo lineal).
//
// Lee un texto, separa por espacios/puntuacion,
// y muestra el TOP 3 de palabras mas frecuentes.
// =============================================================

#include <iostream>
#include <string>
using namespace std;

const int TAM = 101;  // primo, soporta vocabularios pequenos

enum Estado { VACIO, OCUPADO };

struct Entrada {
    string palabra;
    int frecuencia;
    Estado estado;
};

struct ContadorHash {
    Entrada tabla[TAM];

    void inicializar() {
        for (int i = 0; i < TAM; i++) {
            tabla[i].estado = VACIO;
            tabla[i].frecuencia = 0;
        }
    }

    int hashCode(string s) {
        unsigned long h = 5381;
        for (int i = 0; i < (int)s.length(); i++) {
            h = ((h << 5) + h) + s[i];
        }
        return h % TAM;
    }

    // Inserta la palabra o incrementa su contador si ya existe
    void registrar(string palabra) {
        int base = hashCode(palabra);
        for (int i = 0; i < TAM; i++) {
            int pos = (base + i) % TAM;  // sondeo lineal
            if (tabla[pos].estado == VACIO) {
                tabla[pos].palabra = palabra;
                tabla[pos].frecuencia = 1;
                tabla[pos].estado = OCUPADO;
                return;
            }
            if (tabla[pos].palabra == palabra) {
                tabla[pos].frecuencia++;
                return;
            }
        }
    }

    // Muestra el TOP N de palabras mas frecuentes
    void mostrarTop(int n) {
        cout << "\n=== TOP " << n << " palabras mas frecuentes ===" << endl;

        bool tomado[TAM] = {false};
        for (int k = 0; k < n; k++) {
            int mejor = -1;
            int mejorFreq = 0;
            for (int i = 0; i < TAM; i++) {
                if (tabla[i].estado == OCUPADO && !tomado[i]
                    && tabla[i].frecuencia > mejorFreq) {
                    mejor = i;
                    mejorFreq = tabla[i].frecuencia;
                }
            }
            if (mejor == -1) break;
            tomado[mejor] = true;
            cout << "  " << (k+1) << ". \"" << tabla[mejor].palabra
                 << "\"  -> " << tabla[mejor].frecuencia << " veces" << endl;
        }
    }
};

// =============================================================
// UTILIDADES: tokenizacion simple
// =============================================================
string aMinusculas(string s) {
    for (int i = 0; i < (int)s.length(); i++) {
        if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
    }
    return s;
}

bool esLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// =============================================================
// MAIN
// =============================================================
int main() {
    ContadorHash contador;
    contador.inicializar();

    cout << "===== CONTADOR DE PALABRAS (Hash Table) =====" << endl;
    cout << "Ingrese un texto (terminar con ENTER):" << endl;

    string texto;
    getline(cin, texto);

    // Tokenizacion: extraemos palabras
    string palabra = "";
    int totalPalabras = 0;
    for (int i = 0; i <= (int)texto.length(); i++) {
        char c = (i < (int)texto.length()) ? texto[i] : ' ';
        if (esLetra(c)) {
            palabra += c;
        } else {
            if (palabra.length() > 0) {
                contador.registrar(aMinusculas(palabra));
                totalPalabras++;
                palabra = "";
            }
        }
    }

    cout << "\n>> Total de palabras procesadas: " << totalPalabras << endl;
    contador.mostrarTop(3);

    return 0;
}
