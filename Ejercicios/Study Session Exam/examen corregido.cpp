#include <iostream>
#include <vector>
using namespace std;

// Clase Base
class Notificacion {
protected:
    string mensaje;
public:
    Notificacion(string mensaje) {
        this->mensaje = mensaje;
    }
    virtual void enviar() {
        cout << "Notificación: " << mensaje << endl;
    }
    void setmensaje(string n) { mensaje = n; }
    string getmensaje() { return mensaje; }
    virtual ~Notificacion() {}
};

// CLASE HIJA UNO
class NotificacionEmail : public Notificacion {
public:
    NotificacionEmail(string mensaje) : Notificacion(mensaje) {}
    void enviar() override {
        cout << "Enviando email: " << mensaje << endl;
    }
};

// CLASE HIJA DOS
class NotificacionSMS : public Notificacion {
public:
    NotificacionSMS(string mensaje) : Notificacion(mensaje) {}
    void enviar() override {
        cout << "Enviando SMS: " << mensaje << endl;
    }
};

// CLASE HIJA TRES
class NotificacionPush : public Notificacion {
public:
    NotificacionPush(string mensaje) : Notificacion(mensaje) {}
    void enviar() override {
        cout << "Enviando notificación Push: " << mensaje << endl;
    }
};

int main() {
    vector<Notificacion*> notificaciones;
    notificaciones.push_back(new NotificacionEmail("Hola por Email"));
    notificaciones.push_back(new NotificacionSMS("Hola por SMS"));
    notificaciones.push_back(new NotificacionPush("Hola por Push"));

    for (auto n : notificaciones) {
        n->enviar();
        delete n; // liberar memoria
    }
    return 0;
}