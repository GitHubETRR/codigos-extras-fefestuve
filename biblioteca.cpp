#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class libro {
public:
    string titulo;
    string autor;
    string identificacion;
    int cantidad;

    libro(string t, string a, string ID, int c){
        titulo=t;
        autor=a;
        identificacion=ID;
        cantidad=c;
    }

    virtual void mostrarInfo() {
        cout << "\nTitulo: " << titulo << endl;
        cout << "   Autor: " << autor << endl;
        cout << "   Identificacion: " << identificacion << endl;
        cout << "   Cantidad disponible: " << cantidad << endl;
    }

    virtual void prestarLibro() {
        if (cantidad > 0) {
            cantidad--;
        } else {
            cout << "No hay ejemplares disponibles para prestar." << endl;
        }
    }

    virtual void devolverLibro() {
        cantidad++;
    }
};
//esto es herencia
class libroDigital : public libro {
public:
    float MB;   // Tamaño del libro en MB
    string formato;   // Formato del libro

    //para el constructor este, tengo que usar el constructor de libro en la misma linea
    libroDigital(string t, string a, string ID, int c, float tam, string form) : libro(t, a, ID, c){
        MB=tam;
        formato=form;
    }

    // uso override como para modificar el metodo original
    void mostrarInfo() override {
        libro::mostrarInfo();  // Llamar al metodo base para mostrar lo que tienen en comun
        cout << "   Tamanio: " << MB << " MB" << endl;
        cout << "   Formato: " << formato << endl;
    }

    void prestarLibro() override {
        cout << "Compartiendo el libro digital" << endl;
    }

    void devolverLibro() override {
        cout << "Devolviendo el libro digital" << endl;
    }
};

class usuario {
public:
    string nombre;
    string IDusuario;
    vector<string> librosPrestados;

    usuario(string n, string ID){
        nombre=n;
        IDusuario=ID;
    }

    void prestarLibro(string libroID) {
        librosPrestados.push_back(libroID);
    }

    void devolverLibro(string libroID) {
        for (int i = 0; i < librosPrestados.size(); i++) {
            if (librosPrestados[i] == libroID) {
                librosPrestados.erase(librosPrestados.begin() + i);
                break;
            }
        }
    }

    void mostrarInfo() {
        cout << "\nNombre: " << nombre << endl;
        cout << "Identificacion de usuario: " << IDusuario << endl;
        cout << "Libros prestados: ";
        for (int i = 0; i < librosPrestados.size(); i++) {
            cout << librosPrestados[i] << " ";
        }
        cout << endl;
    }
};

class biblioteca {
public:
    vector<libro*> catalogo;  // uso punteros para que haya polimorfismo
    vector<usuario> usuarios;

    void importarLibro(){
        fstream archivo("Libros.txt", ios::in);
        if(!archivo.is_open()){
            cout<<"No se pudo abrir el archivo de libros"<<endl;
            return;
        }
        string tipo, nombre, autor, ID;

        while(archivo.good()){
            getline(archivo, tipo);
            getline(archivo, nombre);
            getline(archivo, autor);
            getline(archivo, ID);
            if(tipo=="fisico"){
                int cant;
                archivo>>cant;
                archivo.ignore();
                catalogo.push_back(new libro(nombre, autor, ID, cant));
            }else if(tipo=="digital"){
                int MB;
                string formato;
                archivo>>MB;
                archivo.ignore();
                getline(archivo, formato);
                catalogo.push_back(new libroDigital(nombre, autor, ID, 1, MB, formato));
            }
            archivo.ignore();
        }

    }

    void agregarLibro() {
        string nombre, autor, ID;
        int cantidad, opcion;
        cout << "\nTipo de libro:\n1. Fisico\n2. Digital" << endl;
        cin >> opcion;
        cin.ignore();
        
        cout << "Nombre del libro: " << endl;
        getline(cin, nombre);
        cout << "Autor: " << endl;
        getline(cin, autor);
        cout << "Identificacion del libro: " << endl;
        cin >> ID;

        if (opcion == 1) {
            cout << "Cantidad: " << endl;
            cin >> cantidad;
            catalogo.push_back(new libro(nombre, autor, ID, cantidad));
        } 
        
        if (opcion == 2) {
            float MB;
            string formato;
            cout << "Tamanio en MB: " << endl;
            cin >> MB;
            cout << "Formato: " << endl;
            cin >> formato;
            catalogo.push_back(new libroDigital(nombre, autor, ID, 1, MB, formato));
        }
    }

    void registrarUsuario() {
        string nombre, ID;
        cin.ignore();
        cout << "\nNombre: " << endl;
        getline(cin, nombre);
        cout << "ID del usuario: " << endl;
        cin >> ID;
        usuarios.push_back(usuario(nombre, ID));
        cout << "Registrado con exito" << endl << endl;
    }

    void prestarLibro() {
        string usuarioID, libroID;
        cout << "Usuario ID: " << endl;
        cin >> usuarioID;
        cout << "Libro ID: " << endl;
        cin >> libroID;

        for (int i = 0; i < usuarios.size(); i++) {
            if (usuarios[i].IDusuario == usuarioID) {
                usuarios[i].prestarLibro(libroID);
                for (int j = 0; j < catalogo.size(); j++) {
                    if (catalogo[j]->identificacion == libroID) {
                        catalogo[j]->prestarLibro();
                        return;
                    }
                }
            }
        }
        cout << "Usuario o libro no encontrado." << endl;
    }

    void devolverLibro() {
        string usuarioID, libroID;
        cout << "Usuario ID: " << endl;
        cin >> usuarioID;
        cout << "Libro ID: " << endl;
        cin >> libroID;

        for (int i = 0; i < usuarios.size(); i++) {
            if (usuarios[i].IDusuario == usuarioID) {
                usuarios[i].devolverLibro(libroID);
                for (int j = 0; j < catalogo.size(); j++) {
                    if (catalogo[j]->identificacion == libroID) {
                        catalogo[j]->devolverLibro();
                        return;
                    }
                }
            }
        }
        cout << "Usuario o libro no encontrado." << endl;
    }

    void mostrarCatalogo() {
        cout << "-----------------------" << endl;
        for (int i = 0; i < catalogo.size(); i++) {
            catalogo[i]->mostrarInfo();
        }
        cout << "-----------------------" << endl;
    }

    void mostrarUsuarios() {
        cout << "-----------------------" << endl;
        for (int i = 0; i < usuarios.size(); i++) {
            usuarios[i].mostrarInfo();
        }
        cout << "-----------------------" << endl << endl;
    }

    ~biblioteca(){
        for(int i=0; i<catalogo.size();i++){
            delete catalogo[i];
        }
    }
};

int menu() {
    int opcion;
    do {
        cout << "\nMenu:" << endl;
        cout << "1. Mostrar catalogo" << endl;
        cout << "2. Mostrar usuarios" << endl;
        cout << "3. Prestar libro" << endl;
        cout << "4. Devolver libro" << endl;
        cout << "5. Registrar usuario" << endl;
        cout << "6. Registrar nuevo libro" << endl;
        cout << "7. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;
    } while (opcion < 1 || opcion > 7);

    return opcion;
}

int main() {
    biblioteca miBiblioteca;

    miBiblioteca.importarLibro();

    int opcion;
    do {
        opcion = menu();
        switch (opcion) {
            case 1:
                miBiblioteca.mostrarCatalogo();
                break;
            case 2:
                miBiblioteca.mostrarUsuarios();
                break;
            case 3:
                miBiblioteca.prestarLibro();
                break;
            case 4:
                miBiblioteca.devolverLibro();
                break;
            case 5:
                miBiblioteca.registrarUsuario();
                break;
            case 6:
                miBiblioteca.agregarLibro();
                break;
            case 7:
                cout << "Saliendo..." << endl;
                break;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
    } while (opcion != 7);

    return 0;
}
