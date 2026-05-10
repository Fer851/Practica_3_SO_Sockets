#Práctica 3 de Sistemas Operativos - CLIENTE-SERVIDO

## 1. Descripción 
Este repositorio contiene la **Práctica 3**, desarrollada en **C++ y Python** y automatizada mediante Bash.
El objetivo del proyecto es aplicar y demostrar conceptos fundamentales de comunicación en redes con la estructura **Cliente-Servidor mediante Sockets TCP/IP**. 
El proyecto simula un entorno industrial donde un sensor remoto envía datos de temperatura a una estación de monitorización local (cliente c++), la cual procesa la información y lo guarda en un archivo de texto. El proyecto está diseño para que sea facíl de ejecutar a través de un script de automatización.  

## 2. Estructura del repositorio 
''' text 
|--- src/
|	|--- main.cpp		 	# Código fuente principal del cliente C++ 
|
|	|--- Cliente_socket.ccp	 	# Implementación de la lógica de red (Sockets) 
|  
|	|---Cliente_socket.h		# Fichero de cabecera de ñas funciones de red
|--- scripts/
|	|--- ServidorCamara.py		# Servidor simulado en Python (camara térmica)
|
|       |--- ejecutar.sh		# Script de compilación y ejecución automatizada
|-- README.md				

## 3. Requisistos del sistema
* Sistema Operativo: **Linux** (probado en entorno Ubunto/WSL).
* Compilador: **g++** soporte para C++ estándar.
* Intérprete: python3 (para lanzar el servidor simulado).
* Herramientas de compilación: Utilidades básicas de construción (buil-essential).
- Instalación de herramientas básicas:
	* sudo apt update
	* sudo apt install -y buil-essential python3

## 4. Compilación
Para compilar el código de C++ y generar el ejecutable, ejecuta el siguiente comando desde la raíz del repositorio:
bash
- Dar permiso de ejecución (solo la primera vez): 	
 * chmod +x ejecutar.sh
- Si se desea compilar manualmente sin el script bash, ejecuta:
 * g++ main.cpp Cliente_socket.cpp -o cliente
 
## 5. Ejecución
Para que el sistena de Sockets funcione, la arquitetura requiere que el servidor esté encendido y escuchando antes de que el cliente intente conectarse. Se necesitan dos terminales divididas. 

- Terminal 1 (Lanzar el servidor Python):
	* Python3 ServidorCamara.py
- Terminal 2 (Lanzar el cliente C++):
	* ./ejecutar.sh

## 6. Funcionamiento interno (C++ y Bash) 
* Protocolo: TCP/IP (IPv4)
* Dirección: 127.0.0.1 (Localhost)
* Puerto: 12345
* Flujo de datos: El servidor empaqueta 768 números (floats) simulando temperaturas. El cliente de C++ utiliza ña función recv() en bucle while, almacenando los datos en un vector<float> en memoria antes de volcarlos al disco local usando ofstream.

## 7.Salida esperada
Las terminales mostrarán lo siguiente:
- En la terminal del servidor: 
Servidor escuchando en 127.0.0.1:12345
Conexión aceptada desde ('127.0.0.1', 56544)
Array de datos enviado al cliente

- En la terminal del Cliente:
compilando...
Compilacion completada. Ejecutando cliente...
=== INICIANDO CLIENTE DE TEMPERATURA ====
Socket creado correctamente.
conexión establecida con el servidor 
Se han recibido 768 datos de temperatura correctamente.
Datos guardados correctamente en el archivo: registro_temperatura.txt 

Numeros de punto flotanta recibidos: 
0
1
2
...
(listado hasta 225 repitiendose en bucle) 
Conexión cerrada. Programa finalizado correctamente.

## 8.Depuración
Si se necesita depurar el codigo C++, puedes compilarlo añadiendo en flag -g y utilizar gdb:

**g++ -g main.cpp Cliente_socket.cpp -o cliente**
**gdb ./cliente**
 

## 9. Problemas comunes
* El script no se ejcuta: Asegúrarse que haberle dado permisos con chmod +x lanzador_segundoplano.sh
* Error al conectar con el servidor: Asegurarse de que el script ServidorCamara.py se está ejecutando en otra terminal antes de lanzar el cliente. 

## 10. Autoría
· Alumno: Fernando Morán 
