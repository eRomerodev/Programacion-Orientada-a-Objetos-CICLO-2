
/*
  main.cpp
  Programa interactivo con menú para gestionar la "base de datos" de la biblioteca.
  Usa biblioteca.h que contiene definiciones de structs y la clase BibliotecaDB.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <iomanip>
#include "biblioteca.h"

using namespace std;

// ------------------- Implementación de BibliotecaDB -------------------

vector<string> BibliotecaDB::splitLine(const string& line, char delim) {
    vector<string> out;
    std::stringstream ss(line);
    string item;
    while (std::getline(ss, item, delim)) {
        out.push_back(item);
    }
    return out;
}

string BibliotecaDB::joinFields(const vector<string>& flds, char delim) {
    string s;
    for (size_t i=0;i<flds.size();++i) {
        if (i) s.push_back(delim);
        s += flds[i];
    }
    return s;
}

void BibliotecaDB::cargarAutores() {
    autores.clear();
    ifstream f("autores.txt");
    string line;
    while (getline(f, line)) {
        if(line.empty()) continue;
        auto flds = splitLine(line);
        if (flds.size() < 3) continue;
        Autor a;
        a.id = stoi(flds[0]);
        a.nombre = flds[1];
        a.nacionalidad = flds[2];
        autores.push_back(a);
    }
    f.close();
}

void BibliotecaDB::cargarLibros() {
    libros.clear();
    ifstream f("libros.txt");
    string line;
    while (getline(f, line)) {
        if(line.empty()) continue;
        auto flds = splitLine(line);
        if (flds.size() < 5) continue;
        Libro l;
        l.id = stoi(flds[0]);
        l.titulo = flds[1];
        l.isbn = flds[2];
        l.ano_publicacion = stoi(flds[3]);
        l.id_autor = stoi(flds[4]);
        libros.push_back(l);
    }
    f.close();
}

void BibliotecaDB::cargarEstudiantes() {
    estudiantes.clear();
    ifstream f("estudiantes.txt");
    string line;
    while (getline(f, line)) {
        if(line.empty()) continue;
        auto flds = splitLine(line);
        if (flds.size() < 3) continue;
        Estudiante e;
        e.id = stoi(flds[0]);
        e.nombre = flds[1];
        e.grado = flds[2];
        estudiantes.push_back(e);
    }
    f.close();
}

void BibliotecaDB::cargarPrestamos() {
    prestamos.clear();
    ifstream f("prestamos.txt");
    string line;
    while (getline(f, line)) {
        if(line.empty()) continue;
        auto flds = splitLine(line);
        if (flds.size() < 5) continue;
        Prestamo p;
        p.id = stoi(flds[0]);
        p.id_libro = stoi(flds[1]);
        p.id_estudiante = stoi(flds[2]);
        p.fecha_prestamo = flds[3];
        p.fecha_devolucion = flds[4];
        prestamos.push_back(p);
    }
    f.close();
}

void BibliotecaDB::guardarAutores() const {
    ofstream f("autores.txt");
    for (auto &a : autores) {
        f << a.id << '|' << a.nombre << '|' << a.nacionalidad << '\n';
    }
    f.close();
}

void BibliotecaDB::guardarLibros() const {
    ofstream f("libros.txt");
    for (auto &l : libros) {
        f << l.id << '|' << l.titulo << '|' << l.isbn << '|' << l.ano_publicacion << '|' << l.id_autor << '\n';
    }
    f.close();
}

void BibliotecaDB::guardarEstudiantes() const {
    ofstream f("estudiantes.txt");
    for (auto &e : estudiantes) {
        f << e.id << '|' << e.nombre << '|' << e.grado << '\n';
    }
    f.close();
}

void BibliotecaDB::guardarPrestamos() const {
    ofstream f("prestamos.txt");
    for (auto &p : prestamos) {
        f << p.id << '|' << p.id_libro << '|' << p.id_estudiante << '|' << p.fecha_prestamo << '|' << p.fecha_devolucion << '\n';
    }
    f.close();
}

void BibliotecaDB::cargarTodos() {
    cargarAutores();
    cargarLibros();
    cargarEstudiantes();
    cargarPrestamos();
}

void BibliotecaDB::guardarTodos() const {
    guardarAutores();
    guardarLibros();
    guardarEstudiantes();
    guardarPrestamos();
}

// helpers
bool BibliotecaDB::existeAutor(int id) const {
    return std::any_of(autores.begin(), autores.end(), [id](const Autor& a){ return a.id==id; });
}
bool BibliotecaDB::existeLibro(int id) const {
    return std::any_of(libros.begin(), libros.end(), [id](const Libro& l){ return l.id==id; });
}
bool BibliotecaDB::existeEstudiante(int id) const {
    return std::any_of(estudiantes.begin(), estudiantes.end(), [id](const Estudiante& e){ return e.id==id; });
}

optional<Autor> BibliotecaDB::obtenerAutor(int id) const {
    for (const auto &a : autores) if (a.id==id) return a;
    return std::nullopt;
}
optional<Libro> BibliotecaDB::obtenerLibro(int id) const {
    for (const auto &l : libros) if (l.id==id) return l;
    return std::nullopt;
}
optional<Estudiante> BibliotecaDB::obtenerEstudiante(int id) const {
    for (const auto &e : estudiantes) if (e.id==id) return e;
    return std::nullopt;
}
optional<Prestamo> BibliotecaDB::obtenerPrestamo(int id) const {
    for (const auto &p : prestamos) if (p.id==id) return p;
    return std::nullopt;
}

bool BibliotecaDB::libroEstaPrestado(int id_libro) const {
    for (const auto &p : prestamos) {
        if (p.id_libro==id_libro && p.fecha_devolucion.empty()) return true;
    }
    return false;
}

// CRUD: Autores
bool BibliotecaDB::agregarAutor(const Autor& a) {
    if (existeAutor(a.id)) return false; // id duplicado
    autores.push_back(a);
    return true;
}

bool BibliotecaDB::actualizarAutor(const Autor& a) {
    for (auto &x : autores) {
        if (x.id==a.id) {
            x.nombre = a.nombre;
            x.nacionalidad = a.nacionalidad;
            return true;
        }
    }
    return false;
}

bool BibliotecaDB::eliminarAutor(int id) {
    // evitar borrar autor que tenga libros
    for (const auto &l : libros) {
        if (l.id_autor == id) return false;
    }
    auto it = std::remove_if(autores.begin(), autores.end(), [id](const Autor& a){ return a.id==id; });
    if (it!=autores.end()) {
        autores.erase(it, autores.end());
        return true;
    }
    return false;
}

// CRUD: Libros
bool BibliotecaDB::agregarLibro(const Libro& l) {
    if (existeLibro(l.id)) return false;
    if (!existeAutor(l.id_autor)) return false; // FK invalida
    libros.push_back(l);
    return true;
}

bool BibliotecaDB::actualizarLibro(const Libro& l) {
    for (auto &x : libros) {
        if (x.id==l.id) {
            // si se cambia el autor, verificar fk
            if (!existeAutor(l.id_autor)) return false;
            x.titulo = l.titulo;
            x.isbn = l.isbn;
            x.ano_publicacion = l.ano_publicacion;
            x.id_autor = l.id_autor;
            return true;
        }
    }
    return false;
}

bool BibliotecaDB::eliminarLibro(int id) {
    if (libroEstaPrestado(id)) return false; // no eliminar libro prestado
    auto it = std::remove_if(libros.begin(), libros.end(), [id](const Libro& l){ return l.id==id; });
    if (it!=libros.end()) {
        libros.erase(it, libros.end());
        return true;
    }
    return false;
}

// CRUD: Estudiantes
bool BibliotecaDB::agregarEstudiante(const Estudiante& e) {
    if (existeEstudiante(e.id)) return false;
    estudiantes.push_back(e);
    return true;
}

bool BibliotecaDB::actualizarEstudiante(const Estudiante& e) {
    for (auto &x : estudiantes) {
        if (x.id==e.id) {
            x.nombre = e.nombre;
            x.grado = e.grado;
            return true;
        }
    }
    return false;
}

bool BibliotecaDB::eliminarEstudiante(int id) {
    // no prohibimos si tiene préstamos, pero se podría validar
    auto it = std::remove_if(estudiantes.begin(), estudiantes.end(), [id](const Estudiante& e){ return e.id==id; });
    if (it!=estudiantes.end()) {
        estudiantes.erase(it, estudiantes.end());
        return true;
    }
    return false;
}

// CRUD: Prestamos
bool BibliotecaDB::agregarPrestamo(const Prestamo& p) {
    if (std::any_of(prestamos.begin(), prestamos.end(), [&](const Prestamo& x){ return x.id==p.id; })) return false; // id dup
    if (!existeLibro(p.id_libro)) return false;
    if (!existeEstudiante(p.id_estudiante)) return false;
    if (libroEstaPrestado(p.id_libro)) return false; // no disponible
    prestamos.push_back(p);
    return true;
}

bool BibliotecaDB::actualizarPrestamo(const Prestamo& p) {
    for (auto &x : prestamos) {
        if (x.id==p.id) {
            // validar fk
            if (!existeLibro(p.id_libro) || !existeEstudiante(p.id_estudiante)) return false;
            x.id_libro = p.id_libro;
            x.id_estudiante = p.id_estudiante;
            x.fecha_prestamo = p.fecha_prestamo;
            x.fecha_devolucion = p.fecha_devolucion;
            return true;
        }
    }
    return false;
}

bool BibliotecaDB::devolverPrestamo(int id, const string& fecha_devolucion) {
    for (auto &x : prestamos) {
        if (x.id==id) {
            if (!x.fecha_devolucion.empty()) return false; // ya devuelto
            x.fecha_devolucion = fecha_devolucion;
            return true;
        }
    }
    return false;
}

// Consultas
vector<Prestamo> BibliotecaDB::listarPrestamosPorEstudiante(int id_estudiante) const {
    vector<Prestamo> out;
    for (const auto &p : prestamos) {
        if (p.id_estudiante==id_estudiante) out.push_back(p);
    }
    return out;
}

vector<pair<Autor,int>> BibliotecaDB::autoresConMasLibros() const {
    std::map<int,int> cnt;
    for (const auto &l : libros) cnt[l.id_autor]++;
    vector<pair<Autor,int>> res;
    for (const auto &a : autores) {
        int c = 0;
        auto it = cnt.find(a.id);
        if (it!=cnt.end()) c = it->second;
        res.push_back({a,c});
    }
    // ordenar descendente por conteo
    std::sort(res.begin(), res.end(), [](const pair<Autor,int>& A, const pair<Autor,int>& B){
        return A.second > B.second;
    });
    return res;
}

// Guardar/Cargar generales
void BibliotecaDB::cargarTodos() { cargarAutores(); cargarLibros(); cargarEstudiantes(); cargarPrestamos(); }
void BibliotecaDB::guardarTodos() const { guardarAutores(); guardarLibros(); guardarEstudiantes(); guardarPrestamos(); }

// ------------------- Interfaz de consola -------------------

void pausa() {
    cout << "Presiona Enter para continuar...";
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\\n');
    cin.get();
}

int leerEntero(const string& prompt) {
    cout << prompt;
    int x;
    while (!(cin >> x)) {
        cout << "Entrada inválida. Intenta de nuevo: ";
        cin.clear();
        cin.ignore(10000, '\\n');
    }
    cin.ignore(10000, '\\n');
    return x;
}

string leerLinea(const string& prompt) {
    cout << prompt;
    string s;
    std::getline(cin, s);
    return s;
}

void menuAutores(BibliotecaDB& db) {
    while (true) {
        cout << "\n--- Gestión de Autores ---\n";
        cout << "1. Agregar autor\n2. Listar autores\n3. Actualizar autor\n4. Eliminar autor\n0. Volver\n";
        int op = leerEntero("Opción: ");
        if (op==0) break;
        if (op==1) {
            Autor a;
            a.id = leerEntero("ID autor: ");
            a.nombre = leerLinea("Nombre: ");
            a.nacionalidad = leerLinea("Nacionalidad: ");
            if (!db.agregarAutor(a)) cout << "Error: ID duplicado.\n"; else { db.guardarAutores(); cout << "Autor añadido.\n"; }
        } else if (op==2) {
            cout << left << setw(6) << "ID" << setw(30) << "Nombre" << setw(20) << "Nacionalidad" << "\n";
            for (const auto &a : db.autores) {
                cout << left << setw(6) << a.id << setw(30) << a.nombre << setw(20) << a.nacionalidad << "\n";
            }
            pausa();
        } else if (op==3) {
            int id = leerEntero("ID autor a actualizar: ");
            auto opt = db.obtenerAutor(id);
            if (!opt) { cout << "No existe autor.\n"; continue; }
            Autor a = *opt;
            a.nombre = leerLinea("Nuevo nombre (enter para mantener): ");
            if (a.nombre.empty()) a.nombre = opt->nombre;
            a.nacionalidad = leerLinea("Nueva nacionalidad (enter para mantener): ");
            if (a.nacionalidad.empty()) a.nacionalidad = opt->nacionalidad;
            if (!db.actualizarAutor(a)) cout << "Error al actualizar.\n"; else { db.guardarAutores(); cout << "Actualizado.\n"; }
        } else if (op==4) {
            int id = leerEntero("ID autor a eliminar: ");
            if (!db.eliminarAutor(id)) cout << "Error: Autor no existe o tiene libros asociados.\n"; else { db.guardarAutores(); cout << "Eliminado.\n"; }
        }
    }
}

void menuLibros(BibliotecaDB& db) {
    while (true) {
        cout << "\n--- Gestión de Libros ---\n";
        cout << "1. Agregar libro\n2. Listar libros\n3. Actualizar libro\n4. Eliminar libro\n0. Volver\n";
        int op = leerEntero("Opción: ");
        if (op==0) break;
        if (op==1) {
            Libro l;
            l.id = leerEntero("ID libro: ");
            l.titulo = leerLinea("Título: ");
            l.isbn = leerLinea("ISBN: ");
            l.ano_publicacion = leerEntero("Año publicación: ");
            l.id_autor = leerEntero("ID autor (FK): ");
            if (!db.agregarLibro(l)) cout << "Error: ID duplicado o autor no existe.\n"; else { db.guardarLibros(); cout << "Libro añadido.\n"; }
        } else if (op==2) {
            cout << left << setw(6) << "ID" << setw(40) << "Título" << setw(15) << "ISBN" << setw(6) << "Año" << setw(6) << "AutorID" << "\n";
            for (const auto &l : db.libros) {
                cout << left << setw(6) << l.id << setw(40) << l.titulo << setw(15) << l.isbn << setw(6) << l.ano_publicacion << setw(6) << l.id_autor << "\n";
            }
            pausa();
        } else if (op==3) {
            int id = leerEntero("ID libro a actualizar: ");
            auto opt = db.obtenerLibro(id);
            if (!opt) { cout << "No existe libro.\n"; continue; }
            Libro l = *opt;
            string s = leerLinea("Nuevo título (enter para mantener): ");
            if (!s.empty()) l.titulo = s;
            s = leerLinea("Nuevo ISBN (enter para mantener): ");
            if (!s.empty()) l.isbn = s;
            string tmp;
            tmp = leerLinea("Nuevo año (enter para mantener): ");
            if (!tmp.empty()) l.ano_publicacion = stoi(tmp);
            tmp = leerLinea("Nuevo ID autor (enter para mantener): ");
            if (!tmp.empty()) l.id_autor = stoi(tmp);
            if (!db.actualizarLibro(l)) cout << "Error al actualizar (¿autor inválido?).\n"; else { db.guardarLibros(); cout << "Actualizado.\n"; }
        } else if (op==4) {
            int id = leerEntero("ID libro a eliminar: ");
            if (!db.eliminarLibro(id)) cout << "Error: libro no existe o está prestado.\n"; else { db.guardarLibros(); cout << "Eliminado.\n"; }
        }
    }
}

void menuEstudiantes(BibliotecaDB& db) {
    while (true) {
        cout << "\n--- Gestión de Estudiantes ---\n";
        cout << "1. Agregar estudiante\n2. Listar estudiantes\n3. Actualizar estudiante\n4. Eliminar estudiante\n0. Volver\n";
        int op = leerEntero("Opción: ");
        if (op==0) break;
        if (op==1) {
            Estudiante e;
            e.id = leerEntero("ID estudiante: ");
            e.nombre = leerLinea("Nombre: ");
            e.grado = leerLinea("Grado: ");
            if (!db.agregarEstudiante(e)) cout << "Error: ID duplicado.\n"; else { db.guardarEstudiantes(); cout << "Estudiante añadido.\n"; }
        } else if (op==2) {
            cout << left << setw(6) << "ID" << setw(30) << "Nombre" << setw(20) << "Grado" << "\n";
            for (const auto &e : db.estudiantes) {
                cout << left << setw(6) << e.id << setw(30) << e.nombre << setw(20) << e.grado << "\n";
            }
            pausa();
        } else if (op==3) {
            int id = leerEntero("ID estudiante a actualizar: ");
            auto opt = db.obtenerEstudiante(id);
            if (!opt) { cout << "No existe estudiante.\n"; continue; }
            Estudiante e = *opt;
            string s = leerLinea("Nuevo nombre (enter para mantener): ");
            if (!s.empty()) e.nombre = s;
            s = leerLinea("Nuevo grado (enter para mantener): ");
            if (!s.empty()) e.grado = s;
            if (!db.actualizarEstudiante(e)) cout << "Error al actualizar.\n"; else { db.guardarEstudiantes(); cout << "Actualizado.\n"; }
        } else if (op==4) {
            int id = leerEntero("ID estudiante a eliminar: ");
            if (!db.eliminarEstudiante(id)) cout << "Error: estudiante no existe.\n"; else { db.guardarEstudiantes(); cout << "Eliminado.\n"; }
        }
    }
}

void menuPrestamos(BibliotecaDB& db) {
    while (true) {
        cout << "\n--- Gestión de Préstamos ---\n";
        cout << "1. Crear préstamo\n2. Listar préstamos\n3. Registrar devolución\n4. Buscar préstamos por estudiante\n0. Volver\n";
        int op = leerEntero("Opción: ");
        if (op==0) break;
        if (op==1) {
            Prestamo p;
            p.id = leerEntero("ID préstamo: ");
            p.id_libro = leerEntero("ID libro (FK): ");
            p.id_estudiante = leerEntero("ID estudiante (FK): ");
            p.fecha_prestamo = leerLinea("Fecha préstamo (YYYY-MM-DD): ");
            p.fecha_devolucion = "";
            if (!db.agregarPrestamo(p)) cout << "Error: id duplicado, libro no existe, estudiante no existe o libro no disponible.\n"; else { db.guardarPrestamos(); cout << "Préstamo creado.\n"; }
        } else if (op==2) {
            cout << left << setw(6) << "ID" << setw(8) << "Libro" << setw(10) << "EstudID" << setw(14) << "FechaPrest" << setw(14) << "FechaDev" << "\n";
            for (const auto &p : db.prestamos) {
                cout << left << setw(6) << p.id << setw(8) << p.id_libro << setw(10) << p.id_estudiante << setw(14) << p.fecha_prestamo << setw(14) << (p.fecha_devolucion.empty() ? "-" : p.fecha_devolucion) << "\n";
            }
            pausa();
        } else if (op==3) {
            int id = leerEntero("ID préstamo a devolver: ");
            string fecha = leerLinea("Fecha devolución (YYYY-MM-DD): ");
            if (!db.devolverPrestamo(id, fecha)) cout << "Error: préstamo no existe o ya devuelto.\n"; else { db.guardarPrestamos(); cout << "Devolución registrada.\n"; }
        } else if (op==4) {
            int id = leerEntero("ID estudiante: ");
            auto lista = db.listarPrestamosPorEstudiante(id);
            if (lista.empty()) { cout << "No hay préstamos para ese estudiante.\n"; continue; }
            cout << left << setw(6) << "ID" << setw(8) << "Libro" << setw(14) << "FechaPrest" << setw(14) << "FechaDev" << "\n";
            for (const auto &p : lista) {
                cout << left << setw(6) << p.id << setw(8) << p.id_libro << setw(14) << p.fecha_prestamo << setw(14) << (p.fecha_devolucion.empty() ? "-" : p.fecha_devolucion) << "\n";
            }
            pausa();
        }
    }
}

void menuConsultas(BibliotecaDB& db) {
    while (true) {
        cout << "\n--- Consultas ---\n";
        cout << "1. Listar libros prestados por un estudiante\n2. Autores con más libros\n0. Volver\n";
        int op = leerEntero("Opción: ");
        if (op==0) break;
        if (op==1) {
            int id = leerEntero("ID estudiante: ");
            auto prestamos = db.listarPrestamosPorEstudiante(id);
            if (prestamos.empty()) { cout << "No hay préstamos.\n"; continue; }
            cout << "Libros prestados:\n";
            for (auto &p : prestamos) {
                auto optL = db.obtenerLibro(p.id_libro);
                if (optL) cout << " - " << optL->titulo << " (ID " << optL->id << ") - Fecha préstamo: " << p.fecha_prestamo << " - Dev: " << (p.fecha_devolucion.empty() ? "NO" : p.fecha_devolucion) << "\n";
            }
            pausa();
        } else if (op==2) {
            auto v = db.autoresConMasLibros();
            cout << left << setw(6) << "ID" << setw(30) << "Autor" << setw(8) << "Libros" << "\n";
            for (const auto &p : v) {
                cout << left << setw(6) << p.first.id << setw(30) << p.first.nombre << setw(8) << p.second << "\n";
            }
            pausa();
        }
    }
}

int main() {
    BibliotecaDB db;
    db.cargarTodos();

    while (true) {
        cout << "\n=== Sistema Biblioteca (C++) ===\n";
        cout << "1. Gestionar Autores\n2. Gestionar Libros\n3. Gestionar Estudiantes\n4. Gestionar Préstamos\n5. Consultas\n6. Guardar todo\n0. Salir\n";
        int op = leerEntero("Opción: ");
        if (op==0) {
            db.guardarTodos();
            cout << "Guardado y salida. Bye.\n";
            break;
        }
        switch(op) {
            case 1: menuAutores(db); break;
            case 2: menuLibros(db); break;
            case 3: menuEstudiantes(db); break;
            case 4: menuPrestamos(db); break;
            case 5: menuConsultas(db); break;
            case 6: db.guardarTodos(); cout << "Guardado realizado.\n"; break;
            default: cout << "Opción inválida.\n"; break;
        }
    }
    return 0;
}
