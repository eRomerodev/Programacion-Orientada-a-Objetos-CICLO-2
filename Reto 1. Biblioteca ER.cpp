// Reto 1. Biblioteca
    // PSEUDO CÓDIGO

# include <iostream>
# include <string>

// Crear la clase Libro ( L I S T O ! )

class Libro {
    public:
        std::string titulo;
        std::string autor;
        int anopublicacion;
        bool estadisponible;

    // Constructor
    Libro() : anopublicacion(0), estadisponible(true) {}

    void mostrarDetallesCompletos() {
        std::cout << "Titulo: " << titulo << std::endl;
        std::cout << "Autor: " << autor << std::endl;
        std::cout << "Año de publicación: " << anopublicacion << std::endl;
        if (estadisponible) {
            std::cout << "Disponiblidad: Sí hay!" << std::endl;
    }   else {
            std::cout << "Disponibilidad: No hay :(" << titulo << std::endl;
    }
        }
};