#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype> 
using namespace std;

class Manejo_de_archivos {
public:
    string texto; 
    void leerArchivo(); 
    void crearArchivo(string contenido);
};

void Manejo_de_archivos::leerArchivo() {
    cout << "Ingrese el nombre del archivo a leer: ";
    string filename;
    cin >> filename; 
    ifstream archivo(filename); 
    if (archivo.is_open()) {
        string linea;
        texto = "";
        while (getline(archivo, linea)) {
            texto += linea + "\n";
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo para lectura." << endl;
    }
}

void Manejo_de_archivos::crearArchivo(string contenido) {
    ofstream archivo("exp_postfija.txt");
    if (archivo.is_open()) {
        archivo << contenido << endl;
        archivo.close();
        cout << "Archivo creado exitosamente: exp_postfija.txt" << endl;
    } else {
        cout << "No se pudo crear el archivo." << endl;
    }
}

class ConversorAritemetico {
    char* pila;
    int tope;   
    string* expresiones; 
    int numero_expresiones;
    Manejo_de_archivos archivo_de_entrada;

public:
    ConversorAritemetico();  
    ~ConversorAritemetico(); 
    int prioridad(char operador);
    void infijoAPostfijo();
};

ConversorAritemetico::ConversorAritemetico() {
    archivo_de_entrada.leerArchivo(); 
    string linea = "";
    pila = new char[1000]; 
    tope = -1; 
    expresiones = new string[100];  
    int contadorExpresiones = 0;

    for (int i = 0; i < archivo_de_entrada.texto.size(); i++) {
        char c = archivo_de_entrada.texto[i];
        if (c == ';' || c == '\n') {
            if (!linea.empty()) {
                expresiones[contadorExpresiones++] = linea;
                linea = "";
            }
        } else {
            linea += c;
        }
    }
    if (!linea.empty()) { 
        expresiones[contadorExpresiones++] = linea;
    }
    numero_expresiones = contadorExpresiones; 
}
    
ConversorAritemetico::~ConversorAritemetico() {
    delete[] pila;
    delete[] expresiones;
}

int ConversorAritemetico::prioridad(char operador) {
    switch (operador) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        case '(': return 0;
        default: return 0;
    }
}

void ConversorAritemetico::infijoAPostfijo() {
    string resultadoCompleto = ""; 
    for (int i = 0; i < numero_expresiones; i++) {
        string expresion = expresiones[i]; 
        string postfijo = ""; 
        tope = -1; 

        for (char token : expresion) {
            if (isalnum(token)) { 
                postfijo += token;
            } else if (token == '(') { 
                pila[++tope] = token;
            } else if (token == ')') { 
                while (tope != -1 && pila[tope] != '(') {
                    postfijo += pila[tope--];
                }
                tope--; 
            } else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^' || token == '(') {
                while (tope != -1 && prioridad(pila[tope]) >= prioridad(token)) {
                    postfijo += pila[tope--];
                }
                pila[++tope] = token;
            } else {
            }
        }

        while (tope != -1) {
            postfijo += pila[tope--];
        }

        cout << "Expresión en notación postfija: " << postfijo << endl;
        resultadoCompleto += postfijo + "\n"; 
    }

    archivo_de_entrada.crearArchivo(resultadoCompleto);
}

int main() {
    ConversorAritemetico conversor; 
    conversor.infijoAPostfijo();
    return 0;
}
