/*
 * Programa Principal
 *
 * Autores: Antonio Sedeno Noda, Sergio Alonso
 * Alumno: Héctor Martín Álvarez
 * Curso: 2024-2025
 * Compilación: g++ -o main main.cpp grafo.cpp
 * Ejecución: ./main Grafos/FWX.gr
 */

 #include <string.h>
 #include "grafo.h"
 
 void pressanykey() {
   char c;
   cout << endl;
   cout << "pulsa [c] para continuar: ";
   cin >> c;
 }
 
 void menu(unsigned dirigido, char &opcion) {
   cout << "Optimiza!ción en Grafos, 2024-2025 HÉCTOR MARTÍN ÁLVAREZ" << endl;
   cout << "c. [c]argar grafo desde fichero" << endl;
 
   if (dirigido == 0) {
     cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
     cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
     cout << "o. Mostrar c[o]mponentes conexas del grafo" << endl;
     cout << "s. Obtener árbol de mínimo co[s]te con el algoritmo de Sollin" << endl;
   } else {
     cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
     cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
     cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
     cout << "o. Mostrar c[o]mponentes fuertemente conexas del grafo" << endl;
     cout << "f. Calcular caminos mínimos con el Algoritmo de [F]loyd-Warshall" << endl;
   }
 
   cout << "q. Finalizar el programa" << endl;
   cout << "Introduce la letra de la accion a ejecutar  > ";
   cin >> opcion;
 }
 
 int main(int argc, char *argv[]) {
   int error_apertura;
   char nombrefichero[85], opcion;
   clrscr();
 
   if (argc > 1) {
     cout << "Cargando datos desde el fichero dado como argumento" << endl;
     strcpy(nombrefichero, argv[1]);
   } else {
     cout << "Introduce el nombre completo del fichero de datos" << endl;
     cin >> nombrefichero;
   }
 
   GRAFO G(nombrefichero, error_apertura);
 
   if (error_apertura == 1) {
     cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
     pressanykey();
     clrscr();
   } else {
     cout << "Grafo cargado desde el fichero " << nombrefichero << endl;
     pressanykey();
     clrscr();
 
     do {
       menu(G.Es_dirigido(), opcion);
       switch (opcion) {
         case 'c':
           clrscr();
           cout << "Introduce el nombre completo del fichero de datos" << endl;
           cin >> nombrefichero;
           G.actualizar(nombrefichero, error_apertura);
           if (error_apertura == 1) {
             cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
           } else {
             cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
           }
           pressanykey();
           clrscr();
           break;
 
         case 'i':
           clrscr();
           cout << "Grafo cargado desde " << nombrefichero << endl;
           G.Info_Grafo();
           pressanykey();
           clrscr();
           break;
 
         case 's':
           clrscr();
           if (G.Es_dirigido() == 1) {
             G.Mostrar_Listas(1);
           } else {
             G.Sollin();
           }
           pressanykey();
           clrscr();
           break;
 
         case 'p':
           clrscr();
           G.Mostrar_Listas(-1);
           pressanykey();
           clrscr();
           break;
 
         case 'a':
           clrscr();
           G.Mostrar_Listas(0);
           pressanykey();
           clrscr();
           break;
 
         case 'o':
           clrscr();
           if (G.Es_dirigido()) {
             G.ComponentesFuertementeConexas();
           } else {
             G.ComponentesConexas();
           }
           pressanykey();
           clrscr();
           break;
 
         case 'f':
           clrscr();
           if (G.Es_dirigido()) {
             G.Floyd_Warshall();
           } else {
             cout << "El algoritmo de Floyd-Warshall solo está disponible para grafos dirigidos." << endl;
           }
           pressanykey();
           clrscr();
           break;
       }
     } while (opcion != 'q');
   }
 
   cout << "Fin del programa" << endl;
   return 0;
 }