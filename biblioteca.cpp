#include <iostream>
#include <string>
#include <vector>

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

    void mostrarInfo() {
        cout << "\nTitulo: " << titulo << endl;
        cout << "   Autor: " << autor << endl;
        cout << "   Identificacion: " << identificacion << endl;
        cout << "   Cantidad disponible: " << cantidad << endl;
    }

    bool prestarLibro() {
        if (cantidad > 0) {
            cantidad--;
            return true;
        } else {
            cout << "No hay ejemplares disponibles para prestar." << endl;
            return false;
        }
    }

    void devolverLibro() {
        cantidad++;
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
        for(int i = 0; i<librosPrestados.size(); i++){
            if(librosPrestados[i]==libroID){
                librosPrestados.erase(librosPrestados.begin()+i);
            }
        }
    }

    void mostrarInfo() {
        cout << "\nNombre: " << nombre << endl;
        cout << "Identificacion de usuario: " << IDusuario << endl;
        cout << "Libros prestados: ";
        for(int i=0; i<librosPrestados.size(); i++){
            cout<<librosPrestados[i];
        }
        cout<<endl;
    }
};

class biblioteca {
public:
    vector<libro> catalogo;
    vector<usuario> usuarios;

    void agregarLibro() {
        string nombre, autor, ID;
        int cantidad;
        cout<<"\nNombre del libro: "<<endl;
        cin>>nombre;
        cout<<"Autor: "<<endl;
        cin>>autor;
        cout<<"Identificacion del libro: "<<endl;
        cin>>ID;
        cout<<"Cantidad: "<<endl;
        cin>>cantidad;
        libro nuevoLibro(nombre, autor, ID, cantidad);
        catalogo.push_back(nuevoLibro);
    }

    void registrarUsuario() {
        string nombre, ID;
        cout<<"\nNombre: "<<endl;
        cin>>nombre;
        cout<<"ID del usuario: "<<endl;
        cin>>ID;
        usuario nuevoUsuario(nombre, ID);
        usuarios.push_back(nuevoUsuario);
        cout<<"Registrado con exito"<<endl<<endl;
    }

    void prestarLibro() {
        bool encontrado=false;
        string usuarioID, libroID;
        cout<<"Usuario ID:"<<endl;
        cin>>usuarioID;
        cout<<"Libro ID: "<<endl;
        cin>>libroID;

        for (int i=0; i<usuarios.size(); i++) {
            if (usuarios[i].IDusuario == usuarioID) {
                encontrado=true;
                usuarios[i].prestarLibro(libroID);
                break;
            }
        }
        if(encontrado){
            for (int i=0, encontrado=false; i<catalogo.size(); i++) {
                if (catalogo[i].identificacion == libroID) {
                    encontrado=true;
                    catalogo[i].prestarLibro();
                    break;
                }
            }
            if(!encontrado){
                cout<<"Libro no encontrado"<<endl;
            }
        }else{
            cout<<"Usuario no encontrado"<<endl;
        }
    }

    void devolverLibro(){
        bool encontrado=false;
        string usuarioID, libroID;
        cout<<"Usuario ID:"<<endl;
        cin>>usuarioID;
        cout<<"Libro ID: "<<endl;
        cin>>libroID;

        for (int i=0; i<usuarios.size(); i++) {
            if (usuarios[i].IDusuario == usuarioID) {
                encontrado=true;
                usuarios[i].devolverLibro(libroID);
                break;
            }
        }
        if(encontrado){
            for (int i=0, encontrado=false; i<catalogo.size(); i++) {
                if (catalogo[i].identificacion == libroID) {
                    encontrado=true;
                    catalogo[i].devolverLibro();
                    break;
                }
            }
            if(!encontrado){
            cout<<"Libro no encontrado"<<endl;
            }
        }else{
            cout<<"Usuario no encontrado"<<endl;
        }
    }

    void mostrarCatalogo() {
        //terminar
        cout<<"-----------------------"<<endl;
        for(int i=0; i<catalogo.size(); i++){
            catalogo[i].mostrarInfo();
        }
        cout<<"-----------------------"<<endl;
        
    }

    void mostrarUsuarios() {
        //terminar
        cout<<"-----------------------"<<endl;
        for(int i=0; i<usuarios.size(); i++){
            usuarios[i].mostrarInfo();
        }
        cout<<"-----------------------"<<endl<<endl;
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
        cout << "6. Registrar nuevo libro" <<endl;
        cout << "7. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;
    } while (opcion < 1 || opcion > 7);

    return opcion;
}

int main() {
    biblioteca miBiblioteca;
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
