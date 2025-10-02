#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <iomanip>
#include <limits>
#include <vector>
#include <string>
using namespace std;

// Emiliano Romero 

// ------------------- Estructuras -------------------
struct Autor { int id; string nombre; string nacionalidad; };
struct Libro { int id; string titulo; string isbn; int ano; int id_autor; };
struct Estudiante { int id; string nombre; string grado; };
struct Prestamo { int id; int id_libro; int id_estudiante; string fecha_prestamo; string fecha_devolucion; };

// ------------------- Clase DB -------------------
class BibliotecaDB {
public:
    vector<Autor> autores;
    vector<Libro> libros;
    vector<Estudiante> estudiantes;
    vector<Prestamo> prestamos;

    // utilidades
    vector<string> split(const string &line, char delim) {
        vector<string> v; string item; stringstream ss(line);
        while(getline(ss,item,delim)) v.push_back(item);
        return v;
    }


    // ------------------- Persistencia -------------------
    void cargarAutores(){ autores.clear(); ifstream f("autores.txt"); string line;
        while(getline(f,line)){auto v=split(line,'|'); if(v.size()<3) continue;
            autores.push_back({stoi(v[0]),v[1],v[2]});}}
    void guardarAutores()const{ ofstream f("autores.txt"); for(auto&a:autores) f<<a.id<<"|"<<a.nombre<<"|"<<a.nacionalidad<<"\n"; }

    void cargarLibros(){ libros.clear(); ifstream f("libros.txt"); string line;
        while(getline(f,line)){auto v=split(line,'|'); if(v.size()<5) continue;
            libros.push_back({stoi(v[0]),v[1],v[2],stoi(v[3]),stoi(v[4])});}}
    void guardarLibros()const{ ofstream f("libros.txt"); for(auto&l:libros) f<<l.id<<"|"<<l.titulo<<"|"<<l.isbn<<"|"<<l.ano<<"|"<<l.id_autor<<"\n"; }

    void cargarEstudiantes(){ estudiantes.clear(); ifstream f("estudiantes.txt"); string line;
        while(getline(f,line)){auto v=split(line,'|'); if(v.size()<3) continue;
            estudiantes.push_back({stoi(v[0]),v[1],v[2]});}}
    void guardarEstudiantes()const{ ofstream f("estudiantes.txt"); for(auto&e:estudiantes) f<<e.id<<"|"<<e.nombre<<"|"<<e.grado<<"\n"; }

    void cargarPrestamos(){ prestamos.clear(); ifstream f("prestamos.txt"); string line;
        while(getline(f,line)){auto v=split(line,'|'); if(v.size()<5) continue;
            prestamos.push_back({stoi(v[0]),stoi(v[1]),stoi(v[2]),v[3],v[4]});}}
    void guardarPrestamos()const{ ofstream f("prestamos.txt"); for(auto&p:prestamos) f<<p.id<<"|"<<p.id_libro<<"|"<<p.id_estudiante<<"|"<<p.fecha_prestamo<<"|"<<p.fecha_devolucion<<"\n"; }

    void cargarTodos(){ cargarAutores(); cargarLibros(); cargarEstudiantes(); cargarPrestamos(); }
    void guardarTodos()const{ guardarAutores(); guardarLibros(); guardarEstudiantes(); guardarPrestamos(); }

    // ------------------- Validaciones -------------------
    bool existeAutor(int id)const{ for(auto&a:autores) if(a.id==id) return true; return false; }
    bool existeLibro(int id)const{ for(auto&l:libros) if(l.id==id) return true; return false; }
    bool existeEstudiante(int id)const{ for(auto&e:estudiantes) if(e.id==id) return true; return false; }
    bool libroPrestado(int id_libro)const{ for(auto&p:prestamos) if(p.id_libro==id_libro && p.fecha_devolucion.empty()) return true; return false; }

    // ------------------- CRUD -------------------
    bool agregarAutor(Autor a){ if(existeAutor(a.id)) return false; autores.push_back(a); return true; }
    bool actualizarAutor(int id,string nom,string nac){ for(auto &a:autores) if(a.id==id){ if(!nom.empty())a.nombre=nom; if(!nac.empty())a.nacionalidad=nac; return true;} return false; }
    bool eliminarAutor(int id){ if(!existeAutor(id)) return false; for(auto&l:libros) if(l.id_autor==id) return false;
        autores.erase(remove_if(autores.begin(),autores.end(),[&](Autor&a){return a.id==id;}),autores.end()); return true; }

    bool agregarLibro(Libro l){ if(existeLibro(l.id)||!existeAutor(l.id_autor)) return false; libros.push_back(l); return true; }
    bool eliminarLibro(int id){ if(!existeLibro(id)) return false; if(libroPrestado(id)) return false;
        libros.erase(remove_if(libros.begin(),libros.end(),[&](Libro&l){return l.id==id;}),libros.end()); return true; }

    bool agregarEstudiante(Estudiante e){ if(existeEstudiante(e.id)) return false; estudiantes.push_back(e); return true; }

    bool agregarPrestamo(Prestamo p){ if(!existeLibro(p.id_libro)||!existeEstudiante(p.id_estudiante)) return false;
        if(libroPrestado(p.id_libro)) return false; prestamos.push_back(p); return true; }
    bool devolverPrestamo(int id,string fecha){ for(auto&x:prestamos) if(x.id==id && x.fecha_devolucion.empty()){ x.fecha_devolucion=fecha; return true;} return false; }

    // ------------------- Consultas -------------------
    vector<Prestamo> prestamosPorEstudiante(int id){ vector<Prestamo> r; for(auto&p:prestamos) if(p.id_estudiante==id) r.push_back(p); return r; }
    vector<Libro> librosPrestados(){ vector<Libro> r; for(auto&p:prestamos) if(p.fecha_devolucion.empty()) for(auto&l:libros) if(l.id==p.id_libro) r.push_back(l); return r; }
    vector<Libro> librosPorAutor(int id){ vector<Libro> r; for(auto&l:libros) if(l.id_autor==id) r.push_back(l); return r; }
};

// ------------------- Utilidades -------------------
void pausa(){ cout<<"Presiona Enter..."; cin.ignore(numeric_limits<streamsize>::max(),'\n'); }
int leerInt(string p){ cout<<p; int x; while(!(cin>>x)){cin.clear();cin.ignore(10000,'\n');cout<<"Inválido: ";} cin.ignore(10000,'\n'); return x; }
string leerStr(string p){ cout<<p; string s; getline(cin,s); return s; }

// ------------------- Menús -------------------
void menuAutores(BibliotecaDB &db){
    int op;
    while(true){
        cout<<"\n--- Autores ---\n1.Agregar\n2.Listar\n3.Actualizar\n4.Eliminar\n0.Volver\n";
        op=leerInt("Opción: ");
        if(op==0)break;
        if(op==1){Autor a; a.id=leerInt("ID: "); a.nombre=leerStr("Nombre: "); a.nacionalidad=leerStr("Nacionalidad: "); if(db.agregarAutor(a)) {db.guardarTodos(); cout<<"Agregado\n";} else cout<<"Error\n";}
        if(op==2){for(auto&a:db.autores) cout<<a.id<<" "<<a.nombre<<" "<<a.nacionalidad<<"\n"; pausa();}
        if(op==3){int id=leerInt("ID: "); string n=leerStr("Nuevo nombre: "); string nac=leerStr("Nueva nacionalidad: "); if(db.actualizarAutor(id,n,nac)){db.guardarTodos(); cout<<"Actualizado\n";} else cout<<"No existe\n";}
        if(op==4){int id=leerInt("ID: "); if(db.eliminarAutor(id)){db.guardarTodos(); cout<<"Eliminado\n";} else cout<<"No se pudo eliminar\n";}
    }
}

// ------------------- Main -------------------
int main(){
    BibliotecaDB db; db.cargarTodos();
    int op;
    while(true){
        cout<<"\n--- MENÚ PRINCIPAL ---\n";
        cout<<"1. Agregar libro\n2. Buscar préstamos por estudiante\n3. Ver todos los libros prestados\n4. Ver libros por autor\n5. Ver todos los libros\n6. Editar información de autores\n0. Salir\n";
        op=leerInt("Opción: ");
        switch(op){
            case 0: db.guardarTodos(); return 0;
            case 1: {
    Libro l; 
    l.id = leerInt("ID: "); 
    l.titulo = leerStr("Título: "); 
    l.isbn = leerStr("ISBN: "); 
    l.ano = leerInt("Año: "); 
    l.id_autor = leerInt("ID Autor: ");

    if (!db.existeAutor(l.id_autor)) {
        cout << "Error: no existe un autor con ese ID.\n";
    } else if (db.existeLibro(l.id)) {
        cout << "Error: ya existe un libro con ese ID.\n";
    } else if (db.agregarLibro(l)) {
        db.guardarTodos(); 
        cout << "Libro agregado correctamente.\n";
    } else {
        cout << "Error desconocido al agregar libro.\n";
    }
    break;
}
            case 2: {
    int id = leerInt("ID Estudiante: "); 
    if (!db.existeEstudiante(id)) {
        cout << "Error: estudiante no existe.\n";
    } else {
        auto v = db.prestamosPorEstudiante(id); 
        if (v.empty()) cout << "Este estudiante no tiene préstamos.\n";
        for (auto &p : v) 
            cout << "Préstamo " << p.id << " | Libro " << p.id_libro 
                 << " | Fecha " << p.fecha_prestamo 
                 << " | Devuelto: " << (p.fecha_devolucion.empty() ? "NO" : p.fecha_devolucion) << "\n";
    }
    pausa(); 
    break;
}
           case 3: {
    auto v = db.librosPrestados(); 
    if (v.empty()) cout << "No hay libros prestados actualmente.\n";
    for (auto &l : v) {
        auto it = find_if(db.autores.begin(), db.autores.end(), [&](Autor &a){ return a.id == l.id_autor; });
        string nombreAutor = (it != db.autores.end()) ? it->nombre : "Autor desconocido";
        cout << l.id << " | " << l.titulo << " | Autor: " << nombreAutor << "\n";
    }
    pausa(); 
    break;
}
            case 4:{int id=leerInt("ID Autor: "); auto v=db.librosPorAutor(id); for(auto&l:v) cout<<l.id<<" "<<l.titulo<<"\n"; pausa(); break;}
            case 5: {
    if (db.libros.empty()) cout << "No hay libros registrados.\n";
    for (auto &l : db.libros) {
        auto it = find_if(db.autores.begin(), db.autores.end(), [&](Autor &a){ return a.id == l.id_autor; });
        string nombreAutor = (it != db.autores.end()) ? it->nombre : "Autor desconocido";
        cout << l.id << " | " << l.titulo << " | ISBN: " << l.isbn 
             << " | Año: " << l.ano << " | AutorID: " << l.id_autor 
             << " (" << nombreAutor << ")\n";
    }
    pausa(); 
    break;
}
            case 6: menuAutores(db); break;
            default: cout<<"Inválido\n";
        }
    }
}