#include <iostream>  // Incluir librería 
#include <limits>   // Añadido para manejo de entradas
using namespace std;  // Para no escribir escribir std:: cada vez

#define TAMANO_TABLERO 5  // Definir el tamaño del tablero (5x5)

// Clase Nave: Representa un barco de cada jugador
class Nave {
public:
    int fila, columna;  // Coordenadas del barco en el tablero
    bool hundida;  // El barco está hundido (true or false)

    // Constructor del barco: posición inicial (1,1) y no está hundida
    Nave() : fila(1), columna(1), hundida(false) {}
};

// Clase Tablero: Representa el tablero 
class Tablero {
private:
    char tablero[TAMANO_TABLERO][TAMANO_TABLERO];  // Un arreglo representa el tablero de 5x5

public:
    // Constructor: Inicia el tablero con '~' en todas las posiciones
    Tablero() {
        for (int i = 0; i < TAMANO_TABLERO; i++) {  // Recorre las filas
            for (int j = 0; j < TAMANO_TABLERO; j++) {  // Recorre las columnas
                tablero[i][j] = '~';  // Llena de '' (agua) a cada celda
            }
        }
    }

    // Método para mostrar el tablero
    void mostrar() {
        cout << "Estado actual del tablero:" << endl;
        for (int i = 0; i < TAMANO_TABLERO; i++) {  // Recorre las filas
            for (int j = 0; j < TAMANO_TABLERO; j++) {  // Recorre las columnas
                cout << tablero[i][j] << " ";  // Muestra el contenido de la celda
            }
            cout << endl;  // Salto de línea al final de cada fila
        }
    }

    // Método para poner un barco en el tablero, según indique el usuario 
    void colocarNave(int fila, int columna) {
        tablero[fila][columna] = 'B';  // Poner 'B' (barco) en la celda que indique el usuario
    }

    // Método para atacar una posición del tablero
    char atacar(int fila, int columna) {
        if (tablero[fila][columna] == 'B') {  // Si en esa celda hay un barco...
            tablero[fila][columna] = 'X';  // Cambia el barco por 'X' (X = hundir el barco)
            return 'X';  // Retorna 'X', para mostrar al usuario que hundio un barco
        } else if (tablero[fila][columna] == '~') {  // Si la posición es agua
            tablero[fila][columna] = 'O';  // Cambia el agua por 'O' (0 = agua)
            return 'O';  // Devuelve 'O', para mostrar al usuario que es agua/ahí no hay barco
        }
        return 'R';  // Devuelve 'R' si ya se había ingresado esa posición
    }
    
    void mostrarOculto() {
        cout << "Estado actual del tablero:" << endl;
        for (int i = 0; i < TAMANO_TABLERO; i++) {  // Recorre las filas
            for (int j = 0; j < TAMANO_TABLERO; j++) {  // Recorre las columnas
                if (tablero[i][j] == 'B') {
                    cout << "~ ";  // Oculta las posiciones de los barcos del oponente
                } else {
                    cout << tablero[i][j] << " ";  // Muestra el contenido real de las celdas atacadas
                }
            }
            cout << endl;  // Salto de línea al final de cada fila
        }
    }

    // Método para verificar si todas los barcos están hundidas
    bool todasHundidas() {
        for (int i = 0; i < TAMANO_TABLERO; i++) {  // Recorre las filas
            for (int j = 0; j < TAMANO_TABLERO; j++) {  // Recorre las columnas
                if (tablero[i][j] == 'B') return false;  // Si hay un barco, no todos están hundidas
            }
        }
        return true;  // Si no queda ningún barco, todas los barcos están hundidas
    }

    // Método para verificar si uun barco está hundido
    bool verificarHundimiento(Nave& nave) { // "&" afecta al objeto original, con la función origal para que se mantenga el valor asignado guardado
        return tablero[nave.fila][nave.columna] == 'X';  // Si la posición del barco está marcada con 'X', está hundido
    }
};

// Clase Jugador: Un jugador del juego
class Jugador {
public:
    string nombre;  // Nombre del jugador
    Tablero tablero;  // El tablero de este jugador
    Nave naves[3];  // Tres barcos porcada jugador

    // Constructor: Inicializa el nombre del jugador, depués de los : es el parámetro que recibe
    Jugador(string nombre) : nombre(nombre) {
    }

    // Método para colocar los barcos del jugador en el tablero
    void colocarNaves() {
    for (int i = 0; i < 3; i++) {  // Ciclo for para poner los tres barcos
        int fila, columna;
        bool coordenadaOcupada;
        
        do {
            coordenadaOcupada = false;
            
            while (true) {
                cout << nombre << ", pon tu barco #" << i + 1 << " (fila y columna entre 1 y " << TAMANO_TABLERO << "): ";
                
                // Verificar si la entrada es válida
                if (!(cin >> fila >> columna)) {
                    // Limpiar el estado de error de cin
                    cin.clear();
                    // Descartar la entrada incorrecta
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    
                    cout << "Error: Solo se permiten números enteros." << endl;
                    cout << "Por favor, ingresa coordenadas válidas." << endl;
                    continue;
                }

                // Verificar si las coordenadas están dentro del rango
                if (!coordenadasValidas(fila, columna)) {
                    cout << "Fuera de rango. Ingresa coordenadas entre 1 y " << TAMANO_TABLERO << "." << endl;
                    continue;
                }

                break;
            }

            // Verificar si ya existe un barco en esas coordenadas
            for (int j = 0; j < i; j++) {
                if (naves[j].fila + 1 == fila && naves[j].columna + 1 == columna) {
                    cout << "Ya tienes un barco en estas coordenadas. Elige otras coordenadas." << endl;
                    coordenadaOcupada = true;
                    break;
                }
            }

        } while (coordenadaOcupada);

        tablero.colocarNave(fila - 1, columna - 1); // Pone el barco en el tablero
        naves[i].fila = fila - 1; // Fila del barco
        naves[i].columna = columna - 1; // Columna del barco
    }
}

    // Método para validar que las coordenadas estén dentro del rango del tablero
    static bool coordenadasValidas(int fila, int columna) {
        return fila >= 1 && fila <= TAMANO_TABLERO && columna >= 1 && columna <= TAMANO_TABLERO;  // Verifica que las coordenadas estén dentro de los límites
    } //solo regresa true or false, pero no interactua con el usuario
};

// Clase Referi: Verifica las reglas del juego y estado de los jugadores
class Referee {
public:
    // Método para verificar si un barco está hundido
    bool verificarHundimiento(Jugador& jugador, Nave& nave) {
        return jugador.tablero.verificarHundimiento(nave);  // Verifica si el barco está hundido en el tablero
    }

    // Método para verificar si un jugador ha ganado (si todos sus barcos están hundidas)
    bool verificarGanador(Jugador& jugador) {
        return jugador.tablero.todasHundidas();  // Si todos los barcos del jugador están hundidos, el jugador ha ganado
    }
};

// Clase Juego: Control de flujo de juego
class Juego {
private:
    Jugador jugador1, jugador2;  // Jugadores
    Referee referee;  // El árbitro

public:
    // Constructor: Inicializa los dos jugadores con sus nombres
    Juego(string nombre1, string nombre2)
        : jugador1(nombre1), jugador2(nombre2) {}

    // Método para iniciar el juego
    void iniciar() {
        cout << "Bienvenidos a Batalla Naval!" << endl;

        // Poner los barcos de ambos jugadores
        jugador1.colocarNaves();
        jugador2.colocarNaves();

        bool juegoTerminado = false;
        while (!juegoTerminado) {  // Mientras el juego no haya terminado
            // Turno del jugador 1
            cout<<endl;
            cout << jugador1.nombre << ", ataca a tu enemigo!" << endl;
            if (realizarAtaque(jugador1, jugador2, juegoTerminado)) continue;  // Realiza el ataque del jugador 1

            if (juegoTerminado) break;  // Si el juego terminó, sale del bucle

            // Turno jugador 2
            cout<<endl;
            cout << jugador2.nombre << ", ataca a tu enemigo!" << endl;
            realizarAtaque(jugador2, jugador1, juegoTerminado);  // Realiza el ataque del jugador 2
        }
    }

    // Método para realizar el ataque de un jugador
    bool realizarAtaque(Jugador& atacante, Jugador& defensor, bool& juegoTerminado) { 
        int fila, columna;  // Coordenadas de ataque
        char resultado;  // Resultado del ataque (X,0,R)

        while (true) {
            cout << "Introduce las coordenadas de ataque (fila columna): ";
            
            // Verificar si la entrada es válida
            if (!(cin >> fila >> columna)) {
                // Limpiar el estado de error de cin
                cin.clear();
                // Descartar la entrada incorrecta
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << "Error: Solo se permiten números enteros." << endl;
                cout << "Por favor, ingresa coordenadas válidas." << endl;
                continue;
            }

            // Verificar si las coordenadas están dentro del rango
            if (!Jugador::coordenadasValidas(fila, columna)) {
                cout << "Fuera del rango. Ingresa otras coordenadas." << endl;
                continue;
            }

            resultado = defensor.tablero.atacar(fila-1, columna-1);

            if (resultado == 'R') {
                cout << "Ya atacaste esta posición. Ingresa otras coordenadas." << endl;
                continue;
            }

            break;
        }

        // Muestra el resultado del ataque
        cout << "Resultado del ataque: " << (resultado == 'X' ? "Impacto!" : "Agua!") << endl; 
        defensor.tablero.mostrarOculto();  // Muestra el tablero después del ataque

        // Verifica si algun barco fue hundido
        for (int i = 0; i < 3; i++) {
            if (!defensor.naves[i].hundida && referee.verificarHundimiento(defensor, defensor.naves[i])) { 
                cout << "Has hundido un barco!" << endl;
                defensor.naves[i].hundida = true;  // Marca el barco como hundido
            }
        }

        // Verifica si todas los barcos del defensor están hundidas
        if (referee.verificarGanador(defensor)) {
            cout << atacante.nombre << " !Has ganado!" << endl;
            juegoTerminado = true;  // Finaliza el juego
        }

        return false;  // Retorna false para indicar que el turno terminó
    }
};

int main() {
    string nombre1, nombre2;
    cout<<"BATALLA NAVAL"<<endl;
    cout<<"El juego consta de un tablero de 5x5 en el que iniciaras seleccionando las coordenadas en las que estarán tus barcos"<<endl;
    cout<<"La X = hundir un barco, 0 = agua"<<endl;
    cout<<"!DIVIÉRTETE"<<endl; //Inicio e instrucciones
    cout << "Ingrese el nombre del jugador 1: ";
    cin >> nombre1;  // Pide el nombre del primer jugador
    cout << "Ingrese el nombre del jugador 2: ";
    cin >> nombre2;  // Pide el nombre del segundo jugador

    Juego juego(nombre1, nombre2);  // Crea el objeto de juego con los nombres de los jugadores
    juego.iniciar();  // Inicia el juego

    return 0;  // Termina el programa
}