#include <iostream>
#include <string>
#include <limits>

using namespace std;

class Estudiante {
public:
    int numeroDeMaterias;
    int matricula; 
    string nombre;
    string apellido;
    float* calificaciones; 

    Estudiante() {
        numeroDeMaterias = 0;
        matricula = 0;
        calificaciones = nullptr; 
    }

    ~Estudiante() {
        if (calificaciones != nullptr) {
            delete[] calificaciones;
        }
    }

    Estudiante(Estudiante& otroEstudiante) {
        numeroDeMaterias = otroEstudiante.numeroDeMaterias;
        matricula = otroEstudiante.matricula;
        nombre = otroEstudiante.nombre;
        apellido = otroEstudiante.apellido;

        if (otroEstudiante.calificaciones != nullptr && numeroDeMaterias > 0) {
            calificaciones = new float[numeroDeMaterias];
            for (int i = 0; i < numeroDeMaterias; ++i) {
                calificaciones[i] = otroEstudiante.calificaciones[i];
            }
        } else {
            calificaciones = nullptr;
        }
    }

    Estudiante& operator=(Estudiante& otroEstudiante) {
        if (this == &otroEstudiante) {
            return *this;
        }

        numeroDeMaterias = otroEstudiante.numeroDeMaterias;
        matricula = otroEstudiante.matricula;
        nombre = otroEstudiante.nombre;
        apellido = otroEstudiante.apellido;

        if (calificaciones != nullptr) {
            delete[] calificaciones;
            calificaciones = nullptr; 
        }

        if (otroEstudiante.calificaciones != nullptr && numeroDeMaterias > 0) {
            calificaciones = new float[numeroDeMaterias];
            for (int i = 0; i < numeroDeMaterias; ++i) {
                calificaciones[i] = otroEstudiante.calificaciones[i];
            }
        } else {
            calificaciones = nullptr;
        }
        return *this;
    }

    float getPromedio() { 
        if (numeroDeMaterias == 0) return 0.0f;
        float sumaTotal = 0.0f;
        for (int i = 0; i < numeroDeMaterias; ++i) {
            sumaTotal += calificaciones[i];
        }
        return sumaTotal / numeroDeMaterias;
    }
};

struct Nodo_Arbol {
    Estudiante datosEstudiante; 
    Nodo_Arbol* hijoIzquierdo;  
    Nodo_Arbol* hijoDerecho;   

    Nodo_Arbol(Estudiante estudianteRecibido) { 
        datosEstudiante = estudianteRecibido; 
        hijoIzquierdo = nullptr;
        hijoDerecho = nullptr;
    }
};

Nodo_Arbol* crearNodo(Estudiante estudianteACrear) {
    return new Nodo_Arbol(estudianteACrear); 
}

Nodo_Arbol* insertar(Nodo_Arbol* nodoActual, Estudiante estudianteAInsertar) {
    if (nodoActual == nullptr) {
        return crearNodo(estudianteAInsertar);
    }
    if (estudianteAInsertar.matricula < nodoActual->datosEstudiante.matricula) {
        nodoActual->hijoIzquierdo = insertar(nodoActual->hijoIzquierdo, estudianteAInsertar);
    } else if (estudianteAInsertar.matricula > nodoActual->datosEstudiante.matricula) {
        nodoActual->hijoDerecho = insertar(nodoActual->hijoDerecho, estudianteAInsertar);
    }
    return nodoActual;
}

void mostrarInorden(Nodo_Arbol* nodoActual) {
    if (nodoActual == nullptr) return;
    mostrarInorden(nodoActual->hijoIzquierdo);
    cout << "  - Matricula: " << nodoActual->datosEstudiante.matricula 
         << ", Nombre: " << nodoActual->datosEstudiante.nombre << " " << nodoActual->datosEstudiante.apellido
         << ", Promedio: " << nodoActual->datosEstudiante.getPromedio() << endl; 
    mostrarInorden(nodoActual->hijoDerecho);
}

void mostrarPromedioMayorA(Nodo_Arbol* nodoActual, float promedioLimite) {
    if (nodoActual == nullptr) return;
    mostrarPromedioMayorA(nodoActual->hijoIzquierdo, promedioLimite);
    if (nodoActual->datosEstudiante.getPromedio() > promedioLimite) { 
        cout << "  - Matricula: " << nodoActual->datosEstudiante.matricula
             << ", Nombre: " << nodoActual->datosEstudiante.nombre << " " << nodoActual->datosEstudiante.apellido
             << ", Promedio: " << nodoActual->datosEstudiante.getPromedio() << endl;
    }
    mostrarPromedioMayorA(nodoActual->hijoDerecho, promedioLimite);
}

void mostrarPromedioMenorA(Nodo_Arbol* nodoActual, float promedioLimite) {
    if (nodoActual == nullptr) return;
    mostrarPromedioMenorA(nodoActual->hijoIzquierdo, promedioLimite);
    if (nodoActual->datosEstudiante.getPromedio() < promedioLimite) { 
        cout << "  - Matricula: " << nodoActual->datosEstudiante.matricula
             << ", Nombre: " << nodoActual->datosEstudiante.nombre << " " << nodoActual->datosEstudiante.apellido
             << ", Promedio: " << nodoActual->datosEstudiante.getPromedio() << endl;
    }
    mostrarPromedioMenorA(nodoActual->hijoDerecho, promedioLimite);
}

Nodo_Arbol* encontrarMinimo(Nodo_Arbol* nodoActual) {
    while (nodoActual && nodoActual->hijoIzquierdo != nullptr) {
        nodoActual = nodoActual->hijoIzquierdo;
    }
    return nodoActual;
}

Nodo_Arbol* eliminarEstudiante(Nodo_Arbol* nodoActual, int matriculaAEliminar) {
    if (nodoActual == nullptr) return nodoActual;

    if (matriculaAEliminar < nodoActual->datosEstudiante.matricula) {
        nodoActual->hijoIzquierdo = eliminarEstudiante(nodoActual->hijoIzquierdo, matriculaAEliminar);
    } else if (matriculaAEliminar > nodoActual->datosEstudiante.matricula) {
        nodoActual->hijoDerecho = eliminarEstudiante(nodoActual->hijoDerecho, matriculaAEliminar);
    } else {
        if (nodoActual->hijoIzquierdo == nullptr) {
            Nodo_Arbol* nodoReemplazo = nodoActual->hijoDerecho;
            delete nodoActual; 
            return nodoReemplazo;
        } else if (nodoActual->hijoDerecho == nullptr) {
            Nodo_Arbol* nodoReemplazo = nodoActual->hijoIzquierdo;
            delete nodoActual;
            return nodoReemplazo;
        }
        Nodo_Arbol* nodoSucesor = encontrarMinimo(nodoActual->hijoDerecho);
        nodoActual->datosEstudiante = nodoSucesor->datosEstudiante; 
        nodoActual->hijoDerecho = eliminarEstudiante(nodoActual->hijoDerecho, nodoSucesor->datosEstudiante.matricula);
    }
    return nodoActual;
}

Estudiante* buscarEstudiante(Nodo_Arbol* nodoActual, int matriculaBuscada) {
    if (nodoActual == nullptr) {
        return nullptr;
    }
    if (matriculaBuscada == nodoActual->datosEstudiante.matricula) {
        return &(nodoActual->datosEstudiante);
    }
    if (matriculaBuscada < nodoActual->datosEstudiante.matricula) {
        return buscarEstudiante(nodoActual->hijoIzquierdo, matriculaBuscada);
    } else {
        return buscarEstudiante(nodoActual->hijoDerecho, matriculaBuscada);
    }
}

void actualizarCalificaciones(Nodo_Arbol* raizDelArbol) {
    int matriculaParaActualizar;
    cout << "Ingrese la matricula del estudiante a actualizar: ";
    cin >> matriculaParaActualizar;

    Estudiante* estudianteEncontrado = buscarEstudiante(raizDelArbol, matriculaParaActualizar);

    if (estudianteEncontrado == nullptr) {
        cout << "Estudiante con matricula " << matriculaParaActualizar << " no encontrado." << endl;
    } else {
        cout << "Estudiante encontrado: " << estudianteEncontrado->nombre << " " << estudianteEncontrado->apellido << endl;
        if (estudianteEncontrado->calificaciones != nullptr) {
            delete[] estudianteEncontrado->calificaciones;
        }
        cout << "Cuantas materias cursa AHORA?: ";
        cin >> estudianteEncontrado->numeroDeMaterias;
        if (estudianteEncontrado->numeroDeMaterias > 0) {
            estudianteEncontrado->calificaciones = new float[estudianteEncontrado->numeroDeMaterias];
            cout << "Ingrese las " << estudianteEncontrado->numeroDeMaterias << " nuevas calificaciones:" << endl;
            for (int i = 0; i < estudianteEncontrado->numeroDeMaterias; ++i) {
                cout << "Calificacion " << i + 1 << ": ";
                cin >> estudianteEncontrado->calificaciones[i];
            }
        } else {
            estudianteEncontrado->calificaciones = nullptr;
        }
        cout << "¡Calificaciones actualizadas correctamente!" << endl;
    }
}

void recorrerParaPromedioMenor(Nodo_Arbol* nodoActual, float promedioLimite, int matriculaExcluida) {
    if (nodoActual == nullptr) {
        return;
    }
    recorrerParaPromedioMenor(nodoActual->hijoIzquierdo, promedioLimite, matriculaExcluida);
    if (nodoActual->datosEstudiante.getPromedio() < promedioLimite && nodoActual->datosEstudiante.matricula != matriculaExcluida) {
        cout << "  - Matricula: " << nodoActual->datosEstudiante.matricula
             << ", Nombre: " << nodoActual->datosEstudiante.nombre << " " << nodoActual->datosEstudiante.apellido
             << ", Promedio: " << nodoActual->datosEstudiante.getPromedio() << endl;
    }
    recorrerParaPromedioMenor(nodoActual->hijoDerecho, promedioLimite, matriculaExcluida);
}

void mostrarPromedioMenorAEstudiante(Nodo_Arbol* raizDelArbol) {
    int matriculaDeReferencia;
    cout << "Ingrese la matricula del estudiante de referencia: ";
    cin >> matriculaDeReferencia;

    Estudiante* estudianteReferencia = buscarEstudiante(raizDelArbol, matriculaDeReferencia);

    if (estudianteReferencia == nullptr) {
        cout << "Estudiante con matricula " << matriculaDeReferencia << " no encontrado." << endl;
    } else {
        float promedioReferencia = estudianteReferencia->getPromedio();
        cout << "\n--- Estudiantes con promedio MENOR a " << estudianteReferencia->nombre 
             << " (Promedio: " << promedioReferencia << ") ---" << endl;
        recorrerParaPromedioMenor(raizDelArbol, promedioReferencia, matriculaDeReferencia);
        cout << "---------------------------------------------------------" << endl;
    }
}

// === ¡NUEVA FUNCIÓN 3: MOSTRAR NODOS POR NIVEL! (Sin cambios) ===
void mostrarNivel(Nodo_Arbol* nodoActual, int nivelDeseado, int nivelActual) {
    if (nodoActual == nullptr) {
        return; 
    }
    if (nivelDeseado == nivelActual) {
        cout << "  - Matricula: " << nodoActual->datosEstudiante.matricula
             << ", Nombre: " << nodoActual->datosEstudiante.nombre << " " << nodoActual->datosEstudiante.apellido << endl;
    } else if (nivelDeseado > nivelActual) {
        mostrarNivel(nodoActual->hijoIzquierdo, nivelDeseado, nivelActual + 1);
        mostrarNivel(nodoActual->hijoDerecho, nivelDeseado, nivelActual + 1);
    }
}

void imprimirNodosDelNivel(Nodo_Arbol* raizDelArbol) {
    int nivelAImprimir;
    cout << "Ingrese el nivel del arbol que desea mostrar (1 = raiz): ";
    cin >> nivelAImprimir;

    if (nivelAImprimir < 1) {
        cout << "Nivel invalido. Debe ser 1 o mayor." << endl;
        return;
    }

    cout << "\n--- Estudiantes en el Nivel " << nivelAImprimir << " ---" << endl;
    mostrarNivel(raizDelArbol, nivelAImprimir, 1);
    cout << "---------------------------------" << endl;
}

void imprimirArbolGraficoRecursivo(Nodo_Arbol* nodoActual, int nivel) {
    if (nodoActual == nullptr) {
        return;
    }


    imprimirArbolGraficoRecursivo(nodoActual->hijoDerecho, nivel + 1);
    for (int i = 0; i < nivel; i++) {
        cout << "    "; 
    }
    cout << "|--(" << nodoActual->datosEstudiante.matricula << ")" << endl;
    imprimirArbolGraficoRecursivo(nodoActual->hijoIzquierdo, nivel + 1);
}

void mostrarArbolGrafico(Nodo_Arbol* raizDelArbol) {
    cout << "\n--- Representacion Grafica del Arbol (Girado 90 grados) ---" << endl;
    cout << "(La raiz es el nodo mas a la izquierda)\n" << endl;
    
    if (raizDelArbol == nullptr) {
        cout << "     [ ARBOL VACIO ]" << endl;
    } else {
        imprimirArbolGraficoRecursivo(raizDelArbol, 0);
    }
    
    cout << "\n----------------------------------------------------------" << endl;
}

void liberarArbol(Nodo_Arbol* nodoABorrar) {
    if (nodoABorrar == nullptr) {
        return;
    }
    liberarArbol(nodoABorrar->hijoIzquierdo);
    liberarArbol(nodoABorrar->hijoDerecho);
    delete nodoABorrar; 
}


int main() {
    Nodo_Arbol* raizDelArbol = nullptr; 
    int opcionMenu;

    do {
        cout << "\n===== MENU ARBOL DE ESTUDIANTES =====" << endl;
        cout << "1. Insertar estudiante" << endl;
        cout << "2. Mostrar todos (ordenados por matricula)" << endl;
        cout << "3. Mostrar con promedio mayor a 70" << endl;
        cout << "4. Mostrar con promedio menor a 70" << endl;
        cout << "5. Eliminar estudiante por matricula" << endl;
        cout << "6. Actualizar calificaciones de un estudiante" << endl; 
        cout << "7. Mostrar prom. menor a un estudiante especifico" << endl; 
        cout << "8. Mostrar estudiantes por nivel del arbol" << endl; 
        cout << "9. Mostrar arbol graficamente (ASCII)" << endl;
        cout << "10. Salir" << endl; 
        cout << "Elige una opcion: ";
        cin >> opcionMenu;

        if (cin.fail()) {
            cout << "Entrada invalida. Por favor, ingrese un numero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (opcionMenu) {
            case 1: {
                Estudiante nuevoEstudiante; 
                cout << "Ingrese Matricula: ";
                cin >> nuevoEstudiante.matricula;
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

                cout << "Ingrese Nombre(s): ";
                getline(cin, nuevoEstudiante.nombre);

                cout << "Ingrese Apellido(s): ";
                getline(cin, nuevoEstudiante.apellido);

                cout << "Cuantas materias cursa?: ";
                cin >> nuevoEstudiante.numeroDeMaterias;
                
                if (nuevoEstudiante.numeroDeMaterias > 0) {
                    nuevoEstudiante.calificaciones = new float[nuevoEstudiante.numeroDeMaterias];
                    cout << "Ingrese las " << nuevoEstudiante.numeroDeMaterias << " calificaciones:" << endl;
                    for (int i = 0; i < nuevoEstudiante.numeroDeMaterias; ++i) {
                        cout << "Calificacion " << i + 1 << ": ";
                        cin >> nuevoEstudiante.calificaciones[i];
                    }
                } else {
                    nuevoEstudiante.calificaciones = nullptr;
                }
                raizDelArbol = insertar(raizDelArbol, nuevoEstudiante); 
                cout << "¡Estudiante insertado correctamente!" << endl;
                break;
            }
            case 2: {
                if (!raizDelArbol) cout << "El arbol esta vacio." << endl;
                else {
                    cout << "\n--- Lista de Estudiantes (en orden) ---" << endl;
                    mostrarInorden(raizDelArbol);
                    cout << "------------------------------------" << endl;
                }
                break;
            }
            case 3: {
                if (!raizDelArbol) cout << "El arbol esta vacio." << endl;
                else {
                    cout << "\n--- Estudiantes con Promedio > 70 ---" << endl;
                    mostrarPromedioMayorA(raizDelArbol, 70.0f);
                    cout << "-----------------------------------" << endl;
                }
                break;
            }
            case 4: {
                if (!raizDelArbol) cout << "El arbol esta vacio." << endl;
                else {
                    cout << "\n--- Estudiantes con Promedio < 70 ---" << endl;
                    mostrarPromedioMenorA(raizDelArbol, 70.0f);
                    cout << "-----------------------------------" << endl;
                }
                break;
            }
            case 5: {
                if (!raizDelArbol) cout << "El arbol esta vacio." << endl;
                else {
                    int matriculaParaEliminar;
                    cout << "Ingrese la matricula del estudiante a eliminar: ";
                    cin >> matriculaParaEliminar;
                    raizDelArbol = eliminarEstudiante(raizDelArbol, matriculaParaEliminar);
                    cout << "Operacion finalizada." << endl;
                }
                break;
            }
            case 6: {
                if (!raizDelArbol) cout << "El arbol esta vacio." << endl;
                else {
                    actualizarCalificaciones(raizDelArbol);
                }
                break;
            }
            case 7: {
                if (!raizDelArbol) cout << "El arbol esta vacio." << endl;
                else {
                    mostrarPromedioMenorAEstudiante(raizDelArbol);
                }
                break;
            }
            case 8: {
                if (!raizDelArbol) cout << "El arbol esta vacio." << endl;
                else {
                    imprimirNodosDelNivel(raizDelArbol);
                }
                break;
            }
            case 9: {
                if (!raizDelArbol) {
                     cout << "El arbol esta vacio. No se puede mostrar." << endl;
                     mostrarArbolGrafico(raizDelArbol);
                }
                else {
                    mostrarArbolGrafico(raizDelArbol);
                }
                break;
            }
            case 10: { 
                cout << "Saliendo del programa... ¡Adios!" << endl;
                break;
            }
            default: {
                cout << "Opcion no valida. Por favor, intenta de nuevo." << endl;
                break;
            }
        }
    } while (opcionMenu != 10); 

    cout << "Limpiando la memoria. .." << endl;
    liberarArbol(raizDelArbol);
    return 0;   
}