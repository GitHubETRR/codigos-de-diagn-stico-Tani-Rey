#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

struct Libro {
    int ID;
    string Titulo;
    string Autor;
    string Editorial;
    string Idioma;
    string Edicion;
    int Year;
    float Precio;
    bool Leido;
};

vector<Libro> biblioteca;

void Cargar_desde_archivo();
void Guardar_en_archivo();
void Agregar_libro();
void Eliminar_libro(int id);
void Buscar(int id, const string& nombre);
void Marcar_leido(int id, bool estado);
void Mostrar_libros();

int main() {
    Cargar_desde_archivo();  

    int opcion;
    do {
        cout << "\n--- Biblioteca ---\n";
        cout << "1. Agregar libro\n";
        cout << "2. Mostrar libros\n";
        cout << "3. Eliminar libro\n";
        cout << "4. Buscar libro\n";
        cout << "5. Marcar como leido/no leido\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1: Agregar_libro(); break;
            case 2: Mostrar_libros(); break;
            case 3: {
                int id;
                cout << "Ingrese ID a eliminar: ";
                cin >> id;
                Eliminar_libro(id);
                break;
            }
            case 4: {
                int id;
                string nombre;
                cout << "Ingrese ID (0 si no lo sabe): ";
                cin >> id;
                cout << "Ingrese parte del titulo (o 'ninguno'): ";
                cin >> nombre;
                Buscar(id, nombre);
                break;
            }
            case 5: {
                int id;
                cout << "Ingrese ID: ";
                cin >> id;
                cout << "1 = Leido, 0 = No leido: ";
                bool estado;
                cin >> estado;
                Marcar_leido(id, estado);
                break;
            }
        }
    } while (opcion != 0);

    Guardar_en_archivo();  
    return 0;
}

void Mostrar_libros() {
    if (biblioteca.empty()) {
        cout << "No hay libros en la biblioteca.\n";
        return;
    }
    for (const auto& libro : biblioteca) {
        cout << "\nLibro\n";
        cout << "ID: " << libro.ID << "\n";
        cout << "Titulo: " << libro.Titulo << "\n";
        cout << "Autor: " << libro.Autor  << "\n";
        cout << "Editorial: " << libro.Editorial << "\n";
        cout << "Idioma: " << libro.Idioma << "\n";
        cout << "Edicion: " << libro.Edicion << "\n";
        cout << "Año: " << libro.Year << "\n";
        cout << "Precio: $" << libro.Precio << "\n";
        cout << "Leido: " << (libro.Leido ? "Si" : "No") << "\n";
    }
}

void Agregar_libro() {
    Libro libro;
    cout << "Ingrese ID: "; cin >> libro.ID; cin.ignore();
    cout << "Ingrese Titulo: "; getline(cin, libro.Titulo);
    cout << "Ingrese Autor: "; getline(cin, libro.Autor);
    cout << "Ingrese Editorial: "; getline(cin, libro.Editorial);
    cout << "Ingrese Idioma: "; getline(cin, libro.Idioma);
    cout << "Ingrese Edicion: "; getline(cin, libro.Edicion);
    cout << "Ingrese Año: "; cin >> libro.Year;
    cout << "Ingrese Precio: "; cin >> libro.Precio;
    cout << "¿Leido? (1=Si, 0=No): "; cin >> libro.Leido;

    biblioteca.push_back(libro);
    Guardar_en_archivo();  // actualiza archivo cada vez
    cout << "Libro agregado!\n";
}

void Eliminar_libro(int id) {
    for (auto it = biblioteca.begin(); it != biblioteca.end(); ++it) {
        if (it->ID == id) {
            biblioteca.erase(it);
            Guardar_en_archivo();
            cout << "Libro eliminado.\n";
            return;
        }
    }
    cout << "No se encontro un libro con ese ID.\n";
}

void Buscar(int id, const string& nombre) {
    bool encontrado = false;
    for (const auto& libro : biblioteca) {
        if ((id != 0 && libro.ID == id) || (nombre != "ninguno" && libro.Titulo.find(nombre) != string::npos)) {
            cout << "\nLibro encontrado:\n";
            cout << "ID: " << libro.ID << " - " << libro.Titulo << "\n";
            encontrado = true;
        }
    }
    if (!encontrado) cout << "No se encontro el libro.\n";
}

void Marcar_leido(int id, bool estado) {
    for (auto& libro : biblioteca) {
        if (libro.ID == id) {
            libro.Leido = estado;
            Guardar_en_archivo();
            cout << "Estado actualizado.\n";
            return;
        }
    }
    cout << "No se encontro un libro con ese ID.\n";
}

void Guardar_en_archivo() {
    ofstream archivo("biblioteca.txt");
    for (const auto& libro : biblioteca) {
        archivo << libro.ID << "|"
                << libro.Titulo << "|"
                << libro.Autor << "|"
                << libro.Editorial << "|"
                << libro.Idioma << "|"
                << libro.Edicion << "|"
                << libro.Year << "|"
                << libro.Precio << "|"
                << libro.Leido << "\n";
    }
    archivo.close();
}

