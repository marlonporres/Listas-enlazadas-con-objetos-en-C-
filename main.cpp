#include <iostream>
#include <string>

using namespace std;

// Molde para guardar la informacion de cada estudiante
class Alumno {
public:
    string nombres;
    string apellidos;
    string carnet;
    string email;
    string telefono;

    // Arreglo para almacenar exactamente las 5 notas solicitadas
    float notas[5];
};

// Estructura del nodo que guarda al alumno y enlaza la lista
class Nodo {
public:
    Alumno estudiante;
    Nodo* siguiente; // Apuntador al siguiente elemento en la memoria

    Nodo(Alumno alu) {
        estudiante = alu;
        siguiente = nullptr;
    }
};

// Clase que administra la lista enlazada
class ListaAlumnos {
private:
    Nodo* inicio; // Puntero que marca donde arranca nuestra lista

public:
    ListaAlumnos() {
        inicio = nullptr;
    }

    // Destructor para cumplir con la liberacion de memoria al terminar el programa
    ~ListaAlumnos() {
        Nodo* actual = inicio;

        // Recorremos la lista completa para borrar cada nodo
        while (actual != nullptr) {
            Nodo* temporal = actual;
            actual = actual->siguiente;
            delete temporal; // Devolvemos la memoria prestada por new
        }
    }

    // Funcion para insertar un nuevo nodo al inicio de la lista
    void agregarAlumno(Alumno nuevoAlumno) {
        Nodo* nuevo = new Nodo(nuevoAlumno);
        nuevo->siguiente = inicio;
        inicio = nuevo;
    }

    // Funcion que recorre e imprime toda la informacion recopilada
    void mostrarAlumnos() {
        if (inicio == nullptr) {
            cout << "\nNo hay alumnos en la lista.\n";
            return;
        }

        Nodo* actual = inicio;
        cout << "\n=========== LISTA DE ALUMNOS REGISTRADOS ===========\n";

        // Iteramos mientras no lleguemos al final de la lista
        while (actual != nullptr) {
            cout << "\nCarnet:   " << actual->estudiante.carnet << "\n";
            cout << "Nombre:   " << actual->estudiante.nombres << " " << actual->estudiante.apellidos << "\n";
            cout << "Email:    " << actual->estudiante.email << "\n";
            cout << "Telefono: " << actual->estudiante.telefono << "\n";

            cout << "Notas:    ";
            float suma = 0;

            // Imprimimos las 5 notas y las vamos sumando para el promedio
            for (int i = 0; i < 5; i++) {
                cout << "[" << actual->estudiante.notas[i] << "] ";
                suma += actual->estudiante.notas[i];
            }

            // Calculamos e imprimimos el promedio de este alumno
            float promedio = suma / 5.0;
            cout << "\nPromedio: " << promedio << "\n";
            cout << "----------------------------------------------------\n";

            actual = actual->siguiente; // Avanzamos al siguiente alumno
        }
    }
};

int main() {
    ListaAlumnos miLista;
    char respuesta;

    cout << "=== SISTEMA DE REGISTRO DE ALUMNOS ===\n";

    // Ciclo principal para ingresar varios alumnos dinamicamente
    do {
        Alumno temp;

        cout << "\n--- Ingrese los datos del alumno ---\n";
        cout << "Nombres: ";
        cin >> ws; // Limpiamos el buffer para que no se salte la lectura de textos
        getline(cin, temp.nombres);

        cout << "Apellidos: ";
        getline(cin, temp.apellidos);

        cout << "Carnet: ";
        getline(cin, temp.carnet);

        cout << "Email: ";
        getline(cin, temp.email);

        cout << "Telefono: ";
        getline(cin, temp.telefono);

        cout << "\n--- Ingrese las 5 notas ---\n";
        for (int i = 0; i < 5; i++) {
            // Evaluamos que la nota este estrictamente en el rango correcto
            do {
                cout << "Nota " << (i + 1) << " (0 a 10): ";
                cin >> temp.notas[i];


                if (cin.fail()) { // Si cin falla porque le metieron texto en lugar de numero
                    cin.clear(); // 1. Le quitamos el estado de error a cin
                    cin.ignore(10000, '\n'); // 2. Tiramos a la basura lo que sea que escribio el usuario
                    temp.notas[i] = -1; // 3. Le asignamos un -1 para obligar a que el ciclo se repita
                    cout << "[!] Error: Debes ingresar un numero, no texto.\n";
                }
                // -----------------------------------
                else if (temp.notas[i] < 0 || temp.notas[i] > 10) {
                    cout << "[!] Error: La nota debe estar entre 0 y 10.\n";
                }

            } while (temp.notas[i] < 0 || temp.notas[i] > 10);
        }

        // Mandamos el objeto validado a la lista enlazada
        miLista.agregarAlumno(temp);

        // Validamos si el usuario quiere detener el ingreso de datos
        cout << "\nDesea agregar otro alumno? (S/N): ";
        cin >> respuesta;

    } while (respuesta == 'S' || respuesta == 's');

    // Desplegamos todos los datos al finalizar el ingreso
    miLista.mostrarAlumnos();

    return 0;
}