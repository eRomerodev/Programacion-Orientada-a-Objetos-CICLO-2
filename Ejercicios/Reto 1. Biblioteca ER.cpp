// Reto 1. Biblioteca

# include <iostream>
# include <string>
# include <vector>
using namespace std;
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
        std::cout << "Ano de publicación: " << anopublicacion << std::endl;
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

    // M É T O D O S    D E    L A    L I B R E R í A

    void agregar_libro(const Libro& nuevoLibro) {
        
        bool existe = false;

        for (const auto& libro : libros) {
            if (libro.titulo == nuevoLibro.titulo) {
                existe = true;
                break;
            }
        }

        if (existe) {
            std::cout << "Ese libro ya se encuentra en la biblioteca :O, no es necesario agregarlo." << std::endl;
        } else {
            libros.push_back(nuevoLibro);
            std::cout << "El libro ha sido agregado a la librería exitosamente :)" << std::endl;
        }
    }
    
            void mostrar_inventario() {
            std::cout << "....." << std::endl;
            std::cout << "Los libros en la biblioteca son: " << std::endl;
            for (auto& libro : libros) {
                libro.mostrarDetallesCompletos();
            }
        }

        Libro* buscarLibro(const std::string& tituloBuscado) {
            for (auto& libro : libros) {
                if (libro.titulo == tituloBuscado) {
                    return &libro;
                }
            }
            return nullptr;
            }
        
        void prestarLibro(const std::string& tituloPrestamo) {
            Libro* libro = buscarLibro(tituloPrestamo);
            if (libro == nullptr) {
                std::cout << "El libro '" << tituloPrestamo << "' no se encuentra en la biblioteca." << std::endl;
            } else if (!libro->estadisponible) {
                std::cout << "El libro '" << tituloPrestamo << "' ya está prestado." << std::endl;
            } else {
                libro->estadisponible = false;
                std::cout << "El libro '" << tituloPrestamo << "' ha sido prestado exitosamente." << std::endl;
        }
    }

    void devolverLibro(const std::string& tituloDevolucion) {
        Libro* libro = buscarLibro(tituloDevolucion);
            if (libro == nullptr) {
                std::cout << "El libro '" << tituloDevolucion << "' no se encuentra en la biblioteca." << std::endl;
            } else if (libro->estadisponible) {
                std::cout << "El libro '" << tituloDevolucion << "' ya está disponible en la biblioteca." << std::endl;
            } else {
                libro->estadisponible = true;
                std::cout << "El libro '" << tituloDevolucion << "' ha sido devuelto exitosamente." << std::endl;
        }
    }
};


// M A I N

int main() {

    std::vector<Libro> misLibros = {
        Libro("Cien anos de soledad", "Gabriel García Márquez", 1967),
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

    Biblioteca BiblioKeyTeca(misLibros);

    int opcion = 0;

        while (opcion != 5) {
        std::cout << "\n--- BIBLIOTECA DIGITAL ---" << std::endl;
        std::cout << "1. Anadir libro" << std::endl;
        std::cout << "2. Mostrar inventario" << std::endl;
        std::cout << "3. Prestar libro" << std::endl;
        std::cout << "4. Devolver libro" << std::endl;
        std::cout << "5. Salir" << std::endl;
        std::cout << "..........." << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        if (opcion == 1) {
            std::string titulo, autor;
            int anopublicacion;

            std::cout << "Titulo: ";
            std::getline(std::cin >> std::ws, titulo);

            std::cout << "Autor: ";
            std::getline(std::cin >> std::ws, autor);

            std::cout << "Ano de publicación: ";
            std::cin >> anopublicacion;

            Libro nuevoLibro(titulo, autor, anopublicacion);
            BiblioKeyTeca.agregar_libro(nuevoLibro);
        }

        if (opcion == 2) {
            BiblioKeyTeca.mostrar_inventario();
        }

        if (opcion == 3) {
            std::string tituloPrestamo;
            std::cout << "Ingrese el título del libro a prestar: ";
            std::getline(std::cin >> std::ws, tituloPrestamo);
            BiblioKeyTeca.prestarLibro(tituloPrestamo);
        }

        if (opcion == 4) {
            std::string tituloDevolucion;
            std::cout << "Ingrese el título del libro a devolver: ";
            std::getline(std::cin >> std::ws, tituloDevolucion);
            BiblioKeyTeca.devolverLibro(tituloDevolucion);
        }
    }

    return 0;
};