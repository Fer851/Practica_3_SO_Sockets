#ifndef Cliente_socket_h
#define Cliente_socket_h

#include <iostream>
#include <string>
#include <vector>
#include <arpa/inet.h>

// Declaracion de Funciones
int crear_socket();
// Pasamos el struct de linux por referencia (&) para que la funcion lo rellene
bool configurar_direccion(struct sockaddr_in &serv_addr, const std::string &ip, int puerto);
bool conectar_servidor(int sockfd, struct sockaddr_in &serv_addr);
bool recibir_datos(int sockfd, std::vector<float> &datos);
bool guardar_datos(const std::vector<float> &datos, const std::string &nombre_archivo);
void imprimir_resultado(const std::vector<float> &datos);

#endif