#include <iostream>
using namespace std;

class Alumno {
    public:
        string nombre;
        int nota;

    Alumno(string nombre, int nota): nombre(nombre), nota(nota) {}

    void setnombre(string nombre) {nombre = nombre;} 
    void setnota(int nota) {nota = nota;}

    string getnombre() {return nombre;}
    int getnota() {return nota;}
};

int main() {

    Alumno a1("Emiliano", 100);

    cout << "Alumno: " << a1.getnombre() << ", " << "Nota: " << a1.getnota() << endl;

    return 0;
}