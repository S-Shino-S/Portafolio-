#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <mutex>

std::mutex mtx;
using namespace std;
using namespace std::this_thread;     
using namespace std::chrono;          

//-----------------------------------------------------//
// CLASE CLIENTE
//-----------------------------------------------------//
class Cliente{
    string Cliente;
    float Hora_de_llegada;
    float Hora_de_salida;
public:
    void setDatos(string Cliente, float Hora_de_llegada, float Hora_de_salida);
    void getDatos();
    float getHora_de_salida();
    string getNombre();
    float getHora_de_llegada();
};

void Cliente::setDatos(string Cliente, float Hora_de_llegada, float Hora_de_salida){
    this->Cliente = Cliente;
    this->Hora_de_llegada = Hora_de_llegada;
    this->Hora_de_salida = Hora_de_salida;
}

void Cliente::getDatos(){
    cout << Cliente << endl;
    cout << "La hora de llegada fue: " << Hora_de_llegada << endl;
    cout << "La hora de salida fue " << Hora_de_salida << endl;
}

string Cliente::getNombre(){ return Cliente; }
float Cliente::getHora_de_llegada(){ return Hora_de_llegada; }
float Cliente::getHora_de_salida(){ return Hora_de_salida; }

//-----------------------------------------------------//
// CLASE CRONOMETRO
//-----------------------------------------------------//
class Cronometro{
    time_point<high_resolution_clock> inicio;
    vector<float> tiempos_de_llegada;
    float tiempo_actual;
public:
    void cronometrar_tiempos(int numero_de_clientes);
    void mostrar_tiempos();
    vector<float> Gettiempos_de_llegada();
};

vector<float> Cronometro::Gettiempos_de_llegada(){ return tiempos_de_llegada; }

void Cronometro::cronometrar_tiempos(int numero_de_clientes){
    inicio = high_resolution_clock::now();
    for (int i = 0; i < numero_de_clientes; i++) {
        this_thread::sleep_for(milliseconds(rand() % 2000));
        auto ahora = high_resolution_clock::now();
        float tiempo_actual = duration_cast<milliseconds>(ahora - inicio).count()/1000.0;
        tiempos_de_llegada.push_back(tiempo_actual);
    }
}

void Cronometro::mostrar_tiempos(){
    for (int i = 0; i < tiempos_de_llegada.size(); i++) {
        cout << "Tiempo de llegada del cliente " << i + 1 << ": " << tiempos_de_llegada[i] << " segundos" << endl;
    }
}

//-----------------------------------------------------//
// CLASE COLA
//-----------------------------------------------------//
class cola{
    int capacidad;
    Cliente* arreglo_de_clientes;
    int frente;
    int fin;
    int contador;
public:
    cola();
    cola(int num_clientes);
    ~cola(){ delete[] arreglo_de_clientes; }
    int getCapacidad();
    int getfrente();
    Cliente* getarreglo_de_clientes();
    void agregar(Cliente Nuevo_cliente);
    void eliminar();
    bool estaVacia();
    Cliente Frente();
    int tamaño();
    void imprimir();
};

cola::cola(int num_clientes){
    frente = -1;
    fin = -1;
    contador = 0;
    capacidad = num_clientes;
    arreglo_de_clientes = new Cliente[capacidad];
}

int cola::getCapacidad(){ return capacidad; }
int cola::getfrente(){ return frente; }
Cliente* cola::getarreglo_de_clientes(){ return arreglo_de_clientes; }

void cola::agregar(Cliente Nuevo_cliente){
    if (contador == capacidad) {
        cout << "Cola llena" << endl;
        return;
    }
    fin = (fin + 1) % capacidad;
    arreglo_de_clientes[fin] = Nuevo_cliente;
    if (frente == -1) frente = fin;
    contador++;
}

void cola::eliminar(){
    if (estaVacia()) {
        cout << "Cola vacía" << endl;
        return;
    }
    if (contador == 1) {
        frente = -1; fin = -1; contador = 0;
        return;
    }
    frente = (frente + 1) % capacidad;
    contador--;
}

Cliente cola::Frente(){
    if(estaVacia()){
        cout << "Cola vacia" << endl;
        Cliente vacio;
        vacio.setDatos("Sin cliente",0,0);
        return vacio;
    }else{
        return arreglo_de_clientes[frente];
    }
}

bool cola::estaVacia(){ return contador == 0; }
int cola::tamaño(){ return contador; }

void cola::imprimir(){
    if (estaVacia()) {
        cout << "Cola vacía" << endl;
        return;
    }
    cout << "Contenido de la cola: "<<endl;
    for (int i = 0; i < contador; i++) {
        int indice = (frente + i) % capacidad;
        cout << "Cliente en posición " << i + 1 << ":" << endl;
        arreglo_de_clientes[indice].getDatos();
        cout << "---------------------" << endl;
    }
    cout << endl;
}

//-----------------------------------------------------//
// CLASE GENERADOR
//-----------------------------------------------------//
class Generador{
    int numero_de_cliente;
    int numero_de_transacciones;
    float tiempo_de_llegada;
    float tiempo_de_servicio;
public:
    int numero_de_clientes();
    int generador_de_transacciones();
};

int Generador::numero_de_clientes(){ return rand() % 20 + 1; }
int Generador::generador_de_transacciones(){ return rand() % 10 + 1; }

//-----------------------------------------------------//
// CLASE CALCULADORA CLIENTES
//-----------------------------------------------------//
class CalculadoraClientes{
    vector<Cliente>& clientes;
public:
    CalculadoraClientes(vector<Cliente>& clientes) : clientes(clientes) {}
    float calcularPromedioServicio();
    float calcularPromedioEspera();
    int calcularNumeroClientesAtendidos();
};

float CalculadoraClientes::calcularPromedioServicio() {
    if (clientes.empty()) return 0.0;
    float suma = 0.0;
    for (auto &c : clientes) suma += c.getHora_de_salida() - c.getHora_de_llegada();
    return suma / clientes.size();
}

float CalculadoraClientes::calcularPromedioEspera() { return calcularPromedioServicio(); }
int CalculadoraClientes::calcularNumeroClientesAtendidos() { return clientes.size(); }

//-----------------------------------------------------//
// CLASE CAJA DE ATENCION
//-----------------------------------------------------//
class Caja_de_atencion{
    cola& ColaCaja;
    int id;
    bool estado;
    int numero_de_clientes_atendidos;
    vector<Cliente> clientes_atendidos; 
public:
    Caja_de_atencion(cola& provisional, int idcaja);
    void atender_cliente();
    cola& getCola();
    vector<Cliente>& getClientesAtendidos();
    void atender_todos_clientes() {
        while (!ColaCaja.estaVacia()) {
            atender_cliente();
            this_thread::sleep_for(seconds(3));
        }
    }
};

Caja_de_atencion::Caja_de_atencion(cola& provisional, int idCaja)
    : ColaCaja(provisional), id(idCaja), estado(true), numero_de_clientes_atendidos(0) {}

void Caja_de_atencion::atender_cliente(){
    if (!ColaCaja.estaVacia()) {
        Cliente &cliente_actual = ColaCaja.getarreglo_de_clientes()[ColaCaja.getfrente()];

        // Inicio de tiempo real
        auto inicio_servicio = high_resolution_clock::now();

        // Bloqueo de impresión y colores según caja
        {
            std::lock_guard<std::mutex> lock(mtx);
            string color;
            switch(id) {
                case 1: color = "\033[31m"; break;
                case 2: color = "\033[32m"; break;
                case 3: color = "\033[34m"; break;
                default: color = "\033[0m"; break;
            }
            cout << color << "Atendiendo a " << cliente_actual.getNombre() 
                 << " en Caja " << id << "...\033[0m" << endl;
        }

        int simulacion = rand() % 5 + 1;
        this_thread::sleep_for(seconds(simulacion));

        auto fin_servicio = high_resolution_clock::now();
        float tiempo_real = duration_cast<milliseconds>(fin_servicio - inicio_servicio).count()/1000.0;
        float hora_salida = cliente_actual.getHora_de_llegada() + tiempo_real;

        cliente_actual.setDatos(cliente_actual.getNombre(),
                                cliente_actual.getHora_de_llegada(),
                                hora_salida);

        clientes_atendidos.push_back(cliente_actual);
        numero_de_clientes_atendidos++;
        ColaCaja.eliminar();

        // Impresión final con color
        {
            std::lock_guard<std::mutex> lock(mtx);
            string color;
            switch(id) {
                case 1: color = "\033[31m"; break;
                case 2: color = "\033[32m"; break;
                case 3: color = "\033[34m"; break;
                default: color = "\033[0m"; break;
            }
            cout << color << "Cliente " << cliente_actual.getNombre() 
                 << " atendido en Caja " << id
                 << " | Tiempo real de servicio: " << tiempo_real << " segs"
                 << " | Hora de salida: " << hora_salida << "\033[0m" << endl;
        }
    }
}

vector<Cliente>& Caja_de_atencion::getClientesAtendidos() { return clientes_atendidos; }
cola& Caja_de_atencion::getCola() { return ColaCaja; }

//-----------------------------------------------------//
// MAIN
//-----------------------------------------------------//
int main(){
    Cronometro cronometro;
    Generador generador;

    srand(time(0));
    int numero_de_clientes = generador.numero_de_clientes();

    cronometro.cronometrar_tiempos(numero_de_clientes);
    vector<float> tiempos = cronometro.Gettiempos_de_llegada();

    cout << "[SIMULADOR DE BANCO]" << endl;
    cout << "------------------------------" << endl << endl;

    cola Cola_Tardia(numero_de_clientes);
    cola Cola_regular(numero_de_clientes);
    cola Cola_Express(numero_de_clientes);

    for (int i = 0; i < numero_de_clientes; i++) {
        Cliente c;
        string nombre = "Cliente " + to_string(i + 1);
        float llegada = tiempos[i];
        c.setDatos(nombre, llegada, 0);

        int num_transacciones = generador.generador_de_transacciones();

        if (num_transacciones > 5) Cola_Tardia.agregar(c);
        else if (num_transacciones > 2) Cola_regular.agregar(c);
        else Cola_Express.agregar(c);

        cout << "El cliente " << nombre << " fue agregado a la cola " 
             << ((num_transacciones > 5) ? "Tardia" : ((num_transacciones > 2) ? "Regular" : "Express")) << endl;
    }

    cout << "\n[ATENDIENDO PERSONAS EN COLA]\n--------------------------\n";

    Caja_de_atencion Caja_Tardia(Cola_Tardia, 1);
    Caja_de_atencion Caja_Regular(Cola_regular, 2);
    Caja_de_atencion Caja_Express(Cola_Express, 3);

    thread hiloTardia(&Caja_de_atencion::atender_todos_clientes, &Caja_Tardia);
    thread hiloRegular(&Caja_de_atencion::atender_todos_clientes, &Caja_Regular);
    thread hiloExpress(&Caja_de_atencion::atender_todos_clientes, &Caja_Express);

    hiloTardia.join();
    hiloRegular.join();
    hiloExpress.join();

    CalculadoraClientes calc_Tardia(Caja_Tardia.getClientesAtendidos());
    CalculadoraClientes calc_Regular(Caja_Regular.getClientesAtendidos());
    CalculadoraClientes calc_Express(Caja_Express.getClientesAtendidos());

    cout << "\n[ESTADÍSTICAS DE ATENCIÓN]\n--------------------------\n";

    cout << "Cola Tardia:\n";
    cout << "Promedio de servicio: " << calc_Tardia.calcularPromedioServicio() << " segs\n";
    cout << "Promedio de espera: " << calc_Tardia.calcularPromedioEspera() << " segs\n";
    cout << "Clientes atendidos: " << calc_Tardia.calcularNumeroClientesAtendidos() << "\n\n";

    cout << "Cola Regular:\n";
    cout << "Promedio de servicio: " << calc_Regular.calcularPromedioServicio() << " segs\n";
    cout << "Promedio de espera: " << calc_Regular.calcularPromedioEspera() << " segs\n";
    cout << "Clientes atendidos: " << calc_Regular.calcularNumeroClientesAtendidos() << "\n\n";

    cout << "Cola Express:\n";
    cout << "Promedio de servicio: " << calc_Express.calcularPromedioServicio() << " segs\n";
    cout << "Promedio de espera: " << calc_Express.calcularPromedioEspera() << " segs\n";
    cout << "Clientes atendidos: " << calc_Express.calcularNumeroClientesAtendidos() << "\n";

    return 0;
}
