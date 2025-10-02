
/*
  biblioteca.h
  Implementación simple de una "base de datos" en memoria para una biblioteca escolar
  usando structs, vectores y persistencia en archivos .txt (formato separado por '|').
  Compilar con: g++ main.cpp -o biblioteca
*/

#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include <string>
#include <vector>
#include <optional>

using std::string;
using std::vector;
using std::optional;

struct Autor {
    int id;
    string nombre;
    string nacionalidad;
};

struct Libro {
    int id;
    string titulo;
    string isbn;
    int ano_publicacion;
    int id_autor; // FK -> Autor.id
};

struct Estudiante {
    int id;
    string nombre;
    string grado;
};

struct Prestamo {
    int id;
    int id_libro;      // FK -> Libro.id
    int id_estudiante; // FK -> Estudiante.id
    string fecha_prestamo;  // formato YYYY-MM-DD (texto simple)
    string fecha_devolucion; // vacio si no ha sido devuelto
};

class BibliotecaDB {
public:
    vector<Autor> autores;
    vector<Libro> libros;
    vector<Estudiante> estudiantes;
    vector<Prestamo> prestamos;

    // Cargar/Guardar (persistencia)
    void cargarTodos();
    void guardarTodos() const;

    // CRUD Autores
    bool agregarAutor(const Autor& a);
    optional<Autor> obtenerAutor(int id) const;
    bool actualizarAutor(const Autor& a);
    bool eliminarAutor(int id); // falla si el autor tiene libros

    // CRUD Libros
    bool agregarLibro(const Libro& l);
    optional<Libro> obtenerLibro(int id) const;
    bool actualizarLibro(const Libro& l);
    bool eliminarLibro(int id); // falla si el libro está prestado

    // CRUD Estudiantes
    bool agregarEstudiante(const Estudiante& e);
    optional<Estudiante> obtenerEstudiante(int id) const;
    bool actualizarEstudiante(const Estudiante& e);
    bool eliminarEstudiante(int id); // falla si tiene préstamos activos? (no implementado)

    // CRUD Prestamos
    bool agregarPrestamo(const Prestamo& p); // valida existencia y disponibilidad
    optional<Prestamo> obtenerPrestamo(int id) const;
    bool actualizarPrestamo(const Prestamo& p);
    bool devolverPrestamo(int id, const string& fecha_devolucion); // set fecha_devolucion

    // Consultas básicas
    vector<Prestamo> listarPrestamosPorEstudiante(int id_estudiante) const;
    vector<std::pair<Autor,int>> autoresConMasLibros() const; // Autor + conteo

private:
    // helpers de persistencia (archivos separados)
    void cargarAutores();
    void cargarLibros();
    void cargarEstudiantes();
    void cargarPrestamos();

    void guardarAutores() const;
    void guardarLibros() const;
    void guardarEstudiantes() const;
    void guardarPrestamos() const;

    // helpers
    bool libroEstaPrestado(int id_libro) const;
    bool existeAutor(int id) const;
    bool existeLibro(int id) const;
    bool existeEstudiante(int id) const;

    // parse helpers
    static vector<string> splitLine(const string& line, char delim='|');
    static string joinFields(const vector<string>& flds, char delim='|');
};

#endif // BIBLIOTECA_H
