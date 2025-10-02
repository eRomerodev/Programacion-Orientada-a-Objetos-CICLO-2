# Programacion-Orientada-a-Objetos-CICLO-2

# 📚 Sistema de Gestión de Biblioteca (C++)

Este proyecto implementa un sistema básico de gestión de una base de datos de biblioteca en C++. Utiliza estructuras de datos en memoria (`std::vector`) para almacenar la información de autores, libros, estudiantes y préstamos, y garantiza la persistencia de los datos mediante el guardado y la carga en archivos de texto plano (`.txt`).

---

## 💻 Características Principales

* **Modularidad:** Código concentrado en una clase central (`BibliotecaDB`) que encapsula la lógica de negocio y la gestión de datos.
* **Persistencia:** Todos los datos se cargan al iniciar y se guardan al salir (o al realizar operaciones de modificación) en archivos de texto (`autores.txt`, `libros.txt`, etc.), usando el delimitador `|`.
* **CRUD Básico:** Implementación de operaciones de Creación, Lectura, Actualización y Eliminación para las entidades principales (`Autor`, `Libro`, `Estudiante`, `Préstamo`).
* **Validación de Datos:** Incluye chequeos de integridad, como ID duplicados, verificación de claves foráneas (FK), y validación de disponibilidad de libros para préstamo.
* **Consultas Especializadas:** Funcionalidad para buscar préstamos por estudiante y listar libros actualmente prestados.

---

## 🛠️ Estructura del Proyecto

El sistema está modelado a través de las siguientes estructuras y relaciones:

| Estructura | Campos Clave | Relaciones (FK) | Archivo de Persistencia |
| :--- | :--- | :--- | :--- |
| **`Autor`** | `id`, `nombre`, `nacionalidad` | N/A | `autores.txt` |
| **`Libro`** | `id`, `titulo`, `isbn`, `ano` | `id_autor` (hacia `Autor`) | `libros.txt` |
| **`Estudiante`** | `id`, `nombre`, `grado` | N/A | `estudiantes.txt` |
| **`Prestamo`** | `id`, `fecha_prestamo`, `fecha_devolucion` | `id_libro`, `id_estudiante` | `prestamos.txt` |

---

## 🚀 Cómo Compilar y Ejecutar

Este proyecto está diseñado para ser compilado con un compilador C++ moderno (como g++).

### 1. Requisitos
* Compilador C++ (g++, Clang, o similar).

### 2. Compilación
Guarda el código fuente en un único archivo (ej. `biblioteca.cpp`) y usa el siguiente comando en tu terminal:

```bash
g++ biblioteca.cpp -o biblioteca.exe
````

### 3\. Ejecución

Una vez compilado, inicia el programa:

```bash
./biblioteca.exe
```

El programa cargará automáticamente los datos existentes de los archivos `.txt` y presentará el menú interactivo principal.

-----

## 📖 Menú de Opciones

El menú principal ofrece acceso a la gestión de datos y las consultas:

| Opción | Descripción | Detalle |
| :--- | :--- | :--- |
| **1** | **Agregar libro** | Crea un nuevo registro de libro (requiere un ID de autor válido). |
| **2** | **Buscar préstamos por estudiante** | Muestra el historial completo de préstamos de un estudiante. |
| **3** | **Ver todos los libros prestados** | Lista los títulos que tienen un préstamo activo. |
| **4** | **Ver libros por autor** | Muestra todos los títulos asociados a un ID de autor específico. |
| **5** | **Ver todos los libros** | Lista el inventario completo, mostrando el nombre del autor asociado. |
| **6** | **Editar información de autores** | Accede al **Submenú de Gestión de Autores (CRUD)**. |
| **0** | **Salir** | Guarda todos los datos en los archivos de texto y finaliza el programa. |

### Submenú: Gestión de Autores

Al seleccionar la opción **6**, se accede al submenú CRUD de Autores:

1.  Agregar Autor
2.  Listar Autores
3.  Actualizar Autor (permite dejar campos vacíos para no modificarlos)
4.  Eliminar Autor (fallará si el autor tiene libros asociados)
5.  Volver al Menú Principal