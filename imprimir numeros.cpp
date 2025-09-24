#include <iostream>
using namespace std;
void imprimir(int numero) {
    cout << "Numero entero: " << numero << endl;
}

void imprimir(double numero) {
    cout << "Numero decimal: " << numero << endl;
}

void imprimir(const string& texto) {
    cout << "Texto: " << texto << endl;
}

int main() {
    imprimir(19);
    imprimir(19.5);
    imprimir("Hola Mundo");
    double d =2.9;
    int i = static_cast<int>(d);

    imprimir(d);
    imprimir(i);

    return 0;
}