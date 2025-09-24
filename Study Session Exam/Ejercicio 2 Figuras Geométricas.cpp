#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

// PSEUDO CÓDIGO
    // Crear la clase Figura, y añadir el método area() = 0;
    // Crear rectángulo y círculo, diciendo que son del tipo Figura
        // Rectángulo tiene atributos base y altura
        // Círculo tiene un radio
    // En main() crear 2 rectangulos y 2 circulos y guardarlos en un vector
        // Recorrer el vector con un for llamando para cada uno el método area

class Figura {
    public:
        virtual double area() =0;
};

class Rectangulo: public Figura {
    public:
        double base;
        double altura;

        Rectangulo(double base, double altura) {
            this->base = base;
            this->altura = altura;
        }

        // SETTERS
        void setbase(double x) {base=x;}
        void setaltura(double y) {altura=y;}

        // GETTERS
        double getbase() {return base;}
        double getaltura() {return altura;}

        double area() override {
            return base*altura;
        }
};

class Circulo: public Figura {
    public:
        double radio;

        Circulo(double radio) {
            this->radio = radio;
        }

        // SETTERS
        void setradio(double r) {radio=r;}

        // GETTERS
        double getradio() {return radio;}
        
        // Multiplicar mejor en lugar de elevar al cuadrado

        double area() override {
            return M_PI * (radio * radio);
        }
};

int main() {
    vector<Figura*> figuras;

    figuras.push_back(new Rectangulo(4.1,5));
    figuras.push_back(new Rectangulo(2,3));
    figuras.push_back(new Circulo(3.2));
    figuras.push_back(new Circulo(10));

    for (Figura* f: figuras) {
        cout << "El area es: " << f->area() << endl;
    }

    for (Figura* f : figuras) {
        delete f;
    }

    return 0;
}