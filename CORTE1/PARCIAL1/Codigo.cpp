#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_ESTUDIANTES = 30;
const int NUM_NOTAS = 3;

// =============================================
//  CLASE Estudiante
// =============================================
class Estudiante {
private:
    int codigo;
    string nombre;
    int edad;
    bool activo; // indica si el slot está ocupado

public:
    // --- Constructor (slot vacio) ---
    Estudiante() {
        codigo = 0;
        nombre = "";
        edad = 0;
        activo = false;
    }

    // --- Constructor con parametros ---
    Estudiante(int cod, string nom, int eda) {
        codigo = cod;
        nombre = nom;
        edad = eda;
        activo = true;
    }

    // Getters
    int getCodigo() const { return codigo; }
    string getNombre() const { return nombre; }
    int getEdad() const { return edad; }
    bool estaActivo() const { return activo; }

    // Setters
    void setCodigo(int cod) { codigo = cod; }
    void setNombre(string nom) { nombre = nom; }
    void setEdad(int eda) { edad = eda; }
    void setActivo(bool a) { activo = a; }

    // Mostrar información básica
    void mostrarInfo() const {
        cout << "  Codigo : " << codigo << endl;
        cout << "  Nombre : " << nombre << endl;
        cout << "  Edad   : " << edad << " años" << endl;
    }
};

// =============================================
//  CLASE GestorCurso
// =============================================
class GestorCurso {
private:
    Estudiante estudiantes[MAX_ESTUDIANTES]; // arreglo de tamaño fijo
    float notas[MAX_ESTUDIANTES][NUM_NOTAS]; // matriz de notas
    int totalRegistrados;

    // Busca el índice interno por código (-1 si no existe)
    int buscarIndice(int codigo) const {
        for (int i = 0; i < MAX_ESTUDIANTES; i++) {
            if (estudiantes[i].estaActivo() && estudiantes[i].getCodigo() == codigo) {
                return i;
            }
        }
        return -1;
    }

    // Busca el primer slot disponible (-1 si está lleno)
    int primerSlotLibre() const {
        for (int i = 0; i < MAX_ESTUDIANTES; i++) {
            if (!estudiantes[i].estaActivo()) {
                return i;
            }
        }
        return -1;
    }

public:
    GestorCurso() {
        totalRegistrados = 0;
        // Inicializar todas las notas en -1 (sin asignar)
        for (int i = 0; i < MAX_ESTUDIANTES; i++) {
            for (int j = 0; j < NUM_NOTAS; j++) {
                notas[i][j] = -1.0f;
            }
        }
    }

    // 1. Registrar estudiante
    void registrarEstudiante() {
        if (totalRegistrados >= MAX_ESTUDIANTES) {
            cout << "\n  [!] El curso esta lleno. No se pueden registrar mas estudiantes.\n";
            return;
        }

        int slot = primerSlotLibre();
        int cod;
        string nom;
        int eda;

        cout << "\n--- Registrar Estudiante ---\n";

        // Validar código
        cout << "  Codigo (numero positivo): ";
        cin >> cod;
        while (cin.fail() || cod <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Codigo invalido. Ingrese un numero positivo: ";
            cin >> cod;
        }
        cin.ignore();

        if (buscarIndice(cod) != -1) {
            cout << "  [!] Ya existe un estudiante con ese codigo.\n";
            return;
        }

        cout << "  Nombre: ";
        getline(cin, nom);
        while (nom.empty()) {
            cout << "  El nombre no puede estar vacio: ";
            getline(cin, nom);
        }

        cout << "  Edad (entre 14 y 99): ";
        cin >> eda;
        while (cin.fail() || eda < 14 || eda > 99) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Edad invalida. Ingrese entre 14 y 99: ";
            cin >> eda;
        }

        // Usar constructor con parámetros
        estudiantes[slot] = Estudiante(cod, nom, eda);
        totalRegistrados++;

        cout << "  [OK] Estudiante registrado exitosamente.\n";
    }

    // 2. Mostrar todos los estudiantes
    void mostrarTodos() const {
        cout << "\n--- Lista de Estudiantes ---\n";
        if (totalRegistrados == 0) {
            cout << "  No hay estudiantes registrados.\n";
            return;
        }
        int count = 1;
        for (int i = 0; i < MAX_ESTUDIANTES; i++) {
            if (estudiantes[i].estaActivo()) {
                cout << "\n  Estudiante #" << count++ << ":\n";
                estudiantes[i].mostrarInfo();
            }
        }
    }

    // 3. Buscar estudiante por código
    void buscarEstudiante() const {
        cout << "\n--- Buscar Estudiante ---\n";
        int cod;
        cout << "  Ingrese el codigo: ";
        cin >> cod;
        while (cin.fail() || cod <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Codigo invalido: ";
            cin >> cod;
        }

        int idx = buscarIndice(cod);
        if (idx == -1) {
            cout << "  [!] No se encontro ningun estudiante con ese codigo.\n";
        } else {
            cout << "\n  Estudiante encontrado:\n";
            estudiantes[idx].mostrarInfo();
        }
    }

    // 4. Asignar / actualizar notas
    void asignarNotas() {
        cout << "\n--- Asignar Notas ---\n";
        int cod;
        cout << "  Ingrese el codigo del estudiante: ";
        cin >> cod;
        while (cin.fail() || cod <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Codigo invalido: ";
            cin >> cod;
        }

        int idx = buscarIndice(cod);
        if (idx == -1) {
            cout << "  [!] Estudiante no encontrado.\n";
            return;
        }

        cout << "  Ingresando " << NUM_NOTAS << " notas para " << estudiantes[idx].getNombre() << ":\n";
        for (int j = 0; j < NUM_NOTAS; j++) {
            float nota;
            cout << "    Nota " << (j + 1) << " (0.0 - 5.0): ";
            cin >> nota;
            while (cin.fail() || nota < 0.0f || nota > 5.0f) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "    Nota invalida. Ingrese entre 0.0 y 5.0: ";
                cin >> nota;
            }
            notas[idx][j] = nota;
        }
        cout << "  [OK] Notas asignadas correctamente.\n";
    }

    // 5. Mostrar promedio de un estudiante
    void mostrarPromedio() const {
        cout << "\n--- Promedio de Estudiante ---\n";
        int cod;
        cout << "  Ingrese el codigo: ";
        cin >> cod;
        while (cin.fail() || cod <= 0) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  Codigo invalido: ";
            cin >> cod;
        }

        int idx = buscarIndice(cod);
        if (idx == -1) {
            cout << "  [!] Estudiante no encontrado.\n";
            return;
        }

        float suma = 0.0f;
        bool tieneNotas = true;
        for (int j = 0; j < NUM_NOTAS; j++) {
            if (notas[idx][j] < 0) {
                tieneNotas = false;
                break;
            }
            suma += notas[idx][j];
        }

        if (!tieneNotas) {
            cout << "  [!] Este estudiante no tiene todas sus notas asignadas.\n";
        } else {
            float promedio = suma / NUM_NOTAS;
            cout << "  Estudiante : " << estudiantes[idx].getNombre() << endl;
            cout << "  Promedio   : " << promedio;
            if (promedio >= 3.0f) {
                cout << "  -> APROBADO" << endl;
            } else {
                cout << "  -> REPROBADO" << endl;
            }
        }
    }

    // 6. Mostrar matriz completa de notas
    void mostrarMatrizNotas() const {
        cout << "\n--- Matriz de Notas ---\n";
        if (totalRegistrados == 0) {
            cout << "  No hay estudiantes registrados.\n";
            return;
        }

        // Encabezado
        cout << "  "
             << left << setw(8)  << "Codigo"
             << left << setw(22) << "Nombre"
             << right << setw(8) << "Nota1"
             << right << setw(8) << "Nota2"
             << right << setw(8) << "Nota3" << endl;
        cout << "  " << string(54, '-') << endl;

        for (int i = 0; i < MAX_ESTUDIANTES; i++) {
            if (estudiantes[i].estaActivo()) {
                cout << "  "
                     << left << setw(8)  << estudiantes[i].getCodigo()
                     << left << setw(22) << estudiantes[i].getNombre();
                for (int j = 0; j < NUM_NOTAS; j++) {
                    if (notas[i][j] < 0) {
                        cout << right << setw(8) << "N/A";
                    } else {
                        cout << right << setw(8) << fixed << setprecision(1) << notas[i][j];
                    }
                }
                cout << endl;
            }
        }
    }
};

// =============================================
//  FUNCIÓN PRINCIPAL
// =============================================
int main() {
    GestorCurso curso;
    int opcion;

    cout << "============================================" << endl;
    cout << "  Bienvenido al Sistema de Gestion de      " << endl;
    cout << "  Estudiantes y Calificaciones             " << endl;
    cout << "  Programacion Orientada a Objetos - C++   " << endl;
    cout << "  Laura Juliana Correa - 20252020078       " << endl;
    cout << "============================================" << endl;

    while (true) {
        cout << "\n========== MENU PRINCIPAL ==========\n";
        cout << "  1. Registrar estudiante\n";
        cout << "  2. Mostrar todos los estudiantes\n";
        cout << "  3. Buscar estudiante por codigo\n";
        cout << "  4. Asignar / actualizar notas\n";
        cout << "  5. Mostrar promedio de un estudiante\n";
        cout << "  6. Mostrar matriz completa de notas\n";
        cout << "  7. Salir\n";
        cout << "====================================\n";
        cout << "  Seleccione una opcion: ";
        cin >> opcion;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "  [!] Opcion invalida. Intente de nuevo.\n";
            continue;
        }

        if (opcion == 1) {
            curso.registrarEstudiante();
        } else if (opcion == 2) {
            curso.mostrarTodos();
        } else if (opcion == 3) {
            curso.buscarEstudiante();
        } else if (opcion == 4) {
            curso.asignarNotas();
        } else if (opcion == 5) {
            curso.mostrarPromedio();
        } else if (opcion == 6) {
            curso.mostrarMatrizNotas();
        } else if (opcion == 7) {
            cout << "\n  Hasta luego. Cerrando el sistema...\n";
            break;
        } else {
            cout << "  [!] Opcion no valida. Elija entre 1 y 7.\n";
        }
    }

    return 0;
}
