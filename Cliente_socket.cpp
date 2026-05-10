#include "Cliente_socket.h"
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <fstream>
#include <vector>
#include <arpa/inet.h>

using namespace std;

// 1. Funcion para crear el socket
int crear_socket(){
    //para crear el socket TCP/IP
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //Comprobar si hay error al crearlo
    if (sockfd == -1){
        cerr << "Error al crear el socket" << endl;
        //Devolvemos una -1 para avisar del fallo
        return -1;
    }
    cout << "Socket creado correctamente." << endl;
    return sockfd;
}

bool configurar_direccion(struct sockaddr_in &serv_addr, const string &ip, int puerto){
    // Limpiar estructura de memoria
    memset(&serv_addr, 0, sizeof(serv_addr));
    // Usamos una IPv4
    serv_addr.sin_family = AF_INET;
    //configuramos el puerto (htons lo traduce al idioma de la red)
    serv_addr.sin_port = htons(puerto);
    //Traducimos la IP de texto al formato binario del sistema
    if (inet_pton(AF_INET, ip.c_str(), &serv_addr.sin_addr) <= 0) {
        cerr << "Direccion invalida " << endl;
        return false; // Abortar por si falla
    }
    return true; // devolvermos true porque se configuró bien
}

// Función para conectar con el servidor
bool conectar_servidor(int sockfd, struct sockaddr_in &serv_addr){
    //Usamos la función connet de Linux, pasándole nuestro socket y la IP/puerto
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
        cerr << "Error al conectar con el servidor." << endl;
        return false; // Falló la conexión
    }
    cout << "Conexión establecida con el servidor" << endl;
    return true;
}

// Función para recibir los datos del servidor
bool recibir_datos(int sockfd, vector<float> &datos){
    float buffer; // Variable temporal para guardar el dato que llega

    //bucle que lee de la red mientras el servidor siga enviando información
    while (recv(sockfd, &buffer, sizeof(buffer), 0) > 0) {
        datos.push_back(buffer); // añadimos el dato al final del valor
    }
    // si el vector esta vacio al salir del bucle, es por que hubo un problema
    if (datos.empty()){
        cerr << "No se recibieron datos del servidor." << endl;
        return false;
    }
    cout << "Se han recibido " << datos.size() << " datos de temperatura correctamente." << endl;
    return true;
}

// Función para guardar los datos en un archivo de texto
bool guardar_datos(const vector<float> &datos, const string &nombre_archivo){
    // creamos el archivo
    ofstream archivo(nombre_archivo);
    //comprobar si el sistema operativo lo ha creado
    if(!archivo.is_open()){
        cerr << "Error al crear el archivo local para guardar los datos." << endl;
        return false;
    }
    archivo << "--- REGISTRO DE TEMPERATURAS ---" << endl;
    //Recorremos el vector y escribimos cada temperatura en una línea nueva
    for (float f : datos) {
        archivo << f << endl;
    }
    archivo.close();
    cout << "Datos guardados correctamente en el archivo: " << nombre_archivo << endl;
    return true;
}

// Función para imprimir resultado en pantalla
void imprimir_resultado(const vector<float> &datos) {
    cout << "\nNumeros de punto flotante recibidos: " << endl;
    // Recorremos el vector e imprimimos en pantalla
    for (float f : datos){
        cout << f << endl;
    }
}
