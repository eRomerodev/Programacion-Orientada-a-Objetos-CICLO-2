#include <iostream>
#include <vector>
using namespace std;

 

// Clase Base

class Notificacion {
    public:
        Notificacion(string mensaje) {
        this->mensaje = mensaje;
}

    virtual void enviar(string mensaje) {
        return mensaje;
}

          // SETTERS
             void setmensaje(string n) {mensaje=n;}

          // GETTERS
             string getmensaje(mensaje);
};

 

 ~Notificacion()

 

// CLASE HIJA UNO

class NotificacionEmail: public Notificacion {

       void enviar() override {

         cout << "Enviando email: " << mensaje << endl;

}

};

 

//  CLASE HIJA DOS

class NotificacionSMS: public Notificacion {

       void enviar() override {

         cout << "Enviando SMS: " << mensaje << endl;

}

};

 

//  CLASE HIJA TRES

class NotificacionPush: public Notificacion {

       void enviar() override {

         cout << "Enviando notificación Push: " << mensaje << endl;

}

};

 

int main() {

      vector<Notificacion*> notificaciones;

      notificaciones.push_back(new NotificacionEmail());

      notificaciones.push_back(new NotificacionSMS());

      notificaciones.push_back(new NotificacionPush());

      return 0