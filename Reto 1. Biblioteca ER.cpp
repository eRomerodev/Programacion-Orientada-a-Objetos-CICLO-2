// Reto 1. Biblioteca
    // PSEUDO CÓDIGO

# include <iostream>
# include <string>
# include <vector>

// Crear la clase Libro ( L I S T O ! )

class Libro {
    public:
        const std::string titulo;
        const std::string autor;
        const int anopublicacion;
        bool estadisponible;

    // Constructor
     Libro(const std::string& titulo, const std::string& autor, int anopublicacion)
        : titulo(titulo), autor(autor), anopublicacion(anopublicacion), estadisponible(true) {}

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

// Crear la clase Biblioteca

class Biblioteca {

    public:
        std::vector<Libro> libros;
        Biblioteca(std::vector<Libro>& iniciales) : libros(iniciales) {}
};


// M A I N
int main() {
    std::vector<Libro> misLibros = {
        Libro("Cien años de soledad", "Gabriel García Márquez", 1967),
        Libro("El Principito", "Antoine de Saint-Exupéry", 1943),
        Libro("Don Quijote de la Mancha", "Miguel de Cervantes", 1605),
        Libro("1984", "George Orwell", 1949),
        Libro("Rayuela", "Julio Cortázar", 1963),
        Libro("Orgullo y prejuicio", "Jane Austen", 1813),
        Libro("Crimen y castigo", "Fiódor Dostoyevski", 1866),
        Libro("La Odisea", "Homero", -800),
        Libro("Fahrenheit 451", "Ray Bradbury", 1953),
        Libro("El Hobbit", "J.R.R. Tolkien", 1937)
    };

    Biblioteca miBiblioteca(misLibros);

    // Mostrar detalles de cada libro
    for (const auto& libro : miBiblioteca.libros) {
        libro.mostrarDetallesCompletos();
        std::cout << std::endl;
    }

    return 0;
}