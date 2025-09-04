#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Paciente {
protected:
    int id;
    string nombre;
    int edad;
    string diagnostico;

public:
    Paciente(int _id, string _nombre, int _edad, string _diagnostico)
        : id(_id), nombre(_nombre), edad(_edad), diagnostico(_diagnostico) {}

    virtual ~Paciente() {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getDiagnostico() const { return diagnostico; }

    virtual void mostrarInfo() const {
        cout << "\n--- Paciente " << nombre << " ---\n";
        cout << "Edad: " << edad << "\n";
        cout << "Diagnostico: " << diagnostico << "\n";
    }
};


class PacienteInternado : public Paciente {
    int habitacion;
    int dias;
    int costoPorDia;
public:
    PacienteInternado(int _id, string _nombre, int _edad, string _diagnostico,
                      int _habitacion, int _dias, int _costoPorDia)
        : Paciente(_id, _nombre, _edad, _diagnostico),
          habitacion(_habitacion), dias(_dias), costoPorDia(_costoPorDia) {}

    int calcularCosto() const {
        return dias * costoPorDia;
    }

    void mostrarInfo() const override {
        Paciente::mostrarInfo();
        cout << "Tipo: Internado\n";
        cout << "Habitacion: " << habitacion << "\n";
        cout << "Dias internado: " << dias << "\n";
        cout << "Costo total: $" << calcularCosto() << "\n";
    }
};


class PacienteAmbulatorio : public Paciente {
    string fechaTurno;
    string medico;
public:
    PacienteAmbulatorio(int _id, string _nombre, int _edad, string _diagnostico,
                        string _fechaTurno, string _medico)
        : Paciente(_id, _nombre, _edad, _diagnostico),
          fechaTurno(_fechaTurno), medico(_medico) {}

    void mostrarInfo() const override {
        Paciente::mostrarInfo();
        cout << "Tipo: Ambulatorio\n";
        cout << "Fecha del turno: " << fechaTurno << "\n";
        cout << "Medico asignado: " << medico << "\n";
    }
};


Paciente* buscarPaciente(vector<Paciente*>& pacientes, int id) {
    for (auto* p : pacientes) {
        if (p->getId() == id) return p;
    }
    return nullptr;
}


void menuPaciente(Paciente* paciente) {
    int op;
    do {
        cout << "\n1. Ver informacion\n2. Salir\n--> ";
        cin >> op;
        switch(op) {
            case 1:
                paciente->mostrarInfo();
                break;
            case 2:
                cout << "Cerrando sesion...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while(op != 2);
}


void menuPrincipal(vector<Paciente*>& pacientes) {
    int opcion, idCounter = 1;
    do {
        cout << "\n--- Hospital ---\n";
        cout << "1. Registrar paciente internado\n2. Registrar paciente ambulatorio\n3. Iniciar sesion paciente\n4. Salir\n--> ";
        cin >> opcion;

        switch(opcion) {
            case 1: {
                string nombre, diagnostico;
                int edad, habitacion, dias, costo;
                cout << "Nombre: "; cin >> nombre;
                cout << "Edad: "; cin >> edad;
                cout << "Diagnostico: "; cin >> diagnostico;
                cout << "Habitacion: "; cin >> habitacion;
                cout << "Dias de internacion: "; cin >> dias;
                cout << "Costo por dia: "; cin >> costo;
                pacientes.push_back(new PacienteInternado(idCounter++, nombre, edad, diagnostico, habitacion, dias, costo));
                cout << "Paciente internado registrado!\n";
                break;
            }
            case 2: {
                string nombre, diagnostico, fecha, medico;
                int edad;
                cout << "Nombre: "; cin >> nombre;
                cout << "Edad: "; cin >> edad;
                cout << "Diagnostico: "; cin >> diagnostico;
                cout << "Fecha del turno: "; cin >> fecha;
                cout << "Medico asignado: "; cin >> medico;
                pacientes.push_back(new PacienteAmbulatorio(idCounter++, nombre, edad, diagnostico, fecha, medico));
                cout << "Paciente ambulatorio registrado!\n";
                break;
            }
            case 3: {
                int id;
                cout << "Ingrese ID de paciente: ";
                cin >> id;
                Paciente* p = buscarPaciente(pacientes, id);
                if (p) {
                    menuPaciente(p);
                } else {
                    cout << "Paciente no encontrado.\n";
                }
                break;
            }
            case 4:
                cout << "Saliendo...\n";
                break;
            default:
                cout << "Opcion invalida.\n";
        }
    } while(opcion != 4);
}

int main() {
    vector<Paciente*> pacientes;
    menuPrincipal(pacientes);

    for (auto* p : pacientes) delete p;
    return 0;
}

