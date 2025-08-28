#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Clase base
class Vehiculo {
protected:
    string marca;
    string modelo;
    int anio;
    double precioBase;

public:
    Vehiculo(string _marca, string _modelo, int _anio, double _precioBase)
        : marca(_marca), modelo(_modelo), anio(_anio), precioBase(_precioBase) {}

    virtual ~Vehiculo() {} // Destructor virtual (buenas prácticas con polimorfismo)

    virtual double calcularPrecioFinal() const = 0; // Método abstracto

    virtual void mostrarInfo() const {
        cout << "Marca: " << marca
             << " | Modelo: " << modelo
             << " | Año: " << anio
             << " | Precio final: $" << calcularPrecioFinal()
             << endl;
    }
};

// Clase derivada Auto
class Auto : public Vehiculo {
private:
    int numeroPuertas;

public:
    Auto(string _marca, string _modelo, int _anio, double _precioBase, int _numeroPuertas)
        : Vehiculo(_marca, _modelo, _anio, _precioBase), numeroPuertas(_numeroPuertas) {}

    double calcularPrecioFinal() const override {
        return precioBase * 1.15; // Impuesto del 15%
    }

    void mostrarInfo() const override {
        cout << "[Auto] ";
        Vehiculo::mostrarInfo();
        cout << "   Numero de puertas: " << numeroPuertas << endl;
    }
};

// Clase derivada Moto
class Moto : public Vehiculo {
private:
    int cilindrada;

public:
    Moto(string _marca, string _modelo, int _anio, double _precioBase, int _cilindrada)
        : Vehiculo(_marca, _modelo, _anio, _precioBase), cilindrada(_cilindrada) {}

    double calcularPrecioFinal() const override {
        return precioBase * 1.10; // Impuesto del 10%
    }

    void mostrarInfo() const override {
        cout << "[Moto] ";
        Vehiculo::mostrarInfo();
        cout << "   Cilindrada: " << cilindrada << "cc" << endl;
    }
};

// Clase derivada Camion (extra)
class Camion : public Vehiculo {
private:
    double capacidadToneladas;

public:
    Camion(string _marca, string _modelo, int _anio, double _precioBase, double _capacidadToneladas)
        : Vehiculo(_marca, _modelo, _anio, _precioBase), capacidadToneladas(_capacidadToneladas) {}

    double calcularPrecioFinal() const override {
        return precioBase * 1.20; // Impuesto del 20%
    }

    void mostrarInfo() const override {
        cout << "[Camion] ";
        Vehiculo::mostrarInfo();
        cout << "   Capacidad: " << capacidadToneladas << " toneladas" << endl;
    }
};

// Función principal
int main() {
    vector<Vehiculo*> concesionaria;

    // Crear objetos dinámicamente
    concesionaria.push_back(new Auto("Toyota", "Corolla", 2022, 18000, 4));
    concesionaria.push_back(new Moto("Yamaha", "MT-07", 2021, 7000, 689));
    concesionaria.push_back(new Camion("Volvo", "FH16", 2020, 90000, 25));

    // Mostrar la información de todos los vehículos
    for (auto vehiculo : concesionaria) {
        vehiculo->mostrarInfo();
        cout << "-----------------------------------" << endl;
    }

    // Liberar memoria
    for (auto vehiculo : concesionaria) {
        delete vehiculo;
    }
    concesionaria.clear();

    return 0;
}
