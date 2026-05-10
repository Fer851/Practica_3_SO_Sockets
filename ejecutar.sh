#!/bin/bash
echo "Compilando..."
g++ main.cpp Cliente_socket.cpp -o cliente

#Comprobamos si la compilación ha ido bien
if [ $? -eq 0 ]; then
	echo "Compilacion completada. Ejecutando cliente..."
	./cliente
else
	echo "Error en la compilación."
fi 
