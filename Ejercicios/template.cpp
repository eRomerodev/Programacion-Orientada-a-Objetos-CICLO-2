#include <iostream>
#include <string>

using namespace std;

template<typename T> 
T suma(T a, T b) {
    return a + b;
}

int main() {
    cout << "Suma de enteros: " << suma(5,7) << endl;
    cout << "Suma de doubles: " << suma(3.5,7.1) << endl;
    cout << "Suma de strings: " << suma(string("hola "),string("deivi")) << endl;
}

// ~ es para destructor, agarra una fu