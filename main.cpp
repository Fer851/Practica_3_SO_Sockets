#include "Cliente_socket.h"
#include <iostream>
#include <vector>
#include <unistd.h> // Para close()

using namespace std;

int main() {
    // 1. Definimos los datos de conexión
    // OJO: Cambia "127.0.0.1" por la IP de tu PC o la del servidor Python si están en máquinas distintas
    string ip_servidor = "127.0.0.1";
    int puerto = 12345;

    // Aquí guardaremos las temperaturas
    vector<float> datos_temperatura;
    struct sockaddr_in serv_addr;

    cout << "=== INICIANDO CLIENTE DE TEMPERATURA ===" << endl;

    // 2. Crear el socket
    int sockfd = crear_socket();
    if (sockfd == -1) return 1; // Si falla, salimos del programa

    // 3. Configurar la dirección
    if (!configurar_direccion(serv_addr, ip_servidor, puerto)) return 1;

    // 4. Conectar con el servidor
    if (!conectar_servidor(sockfd, serv_addr)) return 1;

    // 5. Recibir los datos
    if (recibir_datos(sockfd, datos_temperatura)) {
        // 6. Si se recibieron bien, los guardamos en un archivo de texto
        guardar_datos(datos_temperatura, "registro_temperaturas.txt");

        // 7. Y los imprimimos por pantalla
        imprimir_resultado(datos_temperatura);
    }

    // 8. Cerramos la conexión (Muy importante no olvidarlo)
    close(sockfd);
    cout << "Conexión cerrada. Programa finalizado correctamente." << endl;

    return 0;
}
