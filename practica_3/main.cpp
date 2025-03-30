/*
 * Programa Principal
 *
 * Autores: Antonio Sedeno Noda, Sergio Alonso
 * Alumno: Héctor Martín Álvarez
 * Curso: 2024-2025
 * Compilación: g++ -o main main.cpp grafo.cpp
 * Ejecución: ./main grafos/grafoX.gr
*/

#include <string.h>
#include "grafo.h"

/**
 * Función que muestra un mensaje en pantalla y espera a que el usuario pulse
 * una tecla
 */
void pressanykey() {   
  char c;
  //system("pause"); Sólo en Windows
  cout << endl;
  cout << "pulsa [c] para continuar: ";
  cin >> c;
}

//Expresión del menu de opciones segun sea un grafo dirigido o no dirigido
void menu (unsigned dirigido, char &opcion) {
  cout << "Optimiza!cion en Grafos, 2024-2025 HÉCTOR MARTÍN ÁLVAREZ" << endl;
  cout << "c. [c]argar grafo desde fichero" << endl;
  
  //Grafo no dirigido
  if (dirigido == 0) {
    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
    cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
    cout << "o. Mostrar c[o]mponentes conexas del grafo" << endl;
	  //Aquí se añaden más opciones al menú del grafo no dirigido
  } else {
    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
    cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
    cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
    cout << "o. Mostrar c[o]mponentes fuertemente conexas del grafo" << endl;
	  //Aquí se añaden más opciones al menú del grafo dirigido
  };
  
  cout << "q. Finalizar el programa" << endl;
  cout << "Introduce la letra de la accion a ejecutar  > ";
  cin >> opcion;
};


/**
 * El principal es simplemente un gestor de menu, diferenciando acciones para
 * dirigido y para no dirigido, y un menú inicial si no hay un grafo cargado
 */
int main(int argc, char *argv[]) {

  int error_apertura;
  char nombrefichero[85], opcion;
  clrscr();

  // Si tenemos el nombre del primer fichero por argumento, es una excepcion, 
  // y lo intentamos cargar, si no, lo pedimos desde teclado
  if (argc > 1) {
	  cout << "Cargando datos desde el fichero dado como argumento" << endl;
    strcpy(nombrefichero, argv[1]);
  } else {
      cout << "Introduce el nombre completo del fichero de datos" << endl;
      cin >> nombrefichero;
  };

  // Creamos el GRAFO G
  GRAFO G(nombrefichero, error_apertura);

  // Si hay un error en la apertura del fichero de texto que contiene el grafo,
  // muestro un mensaje y termino el programa
  if (error_apertura == 1) {
    cout << "Error en la apertura del fichero desde argumento: revisa nombre y formato" << endl;
    pressanykey();
    clrscr();
    
    // En caso de que no haya error de apertura, se desplega el menú de opciones
  } else {
      cout<< "Grafo cargado desde el fichero " << nombrefichero << endl;
      pressanykey();
      clrscr();
      do {
        menu(G.Es_dirigido(), opcion);
        switch (opcion) {
          case 'c' :
            clrscr();
         	  cout << "Introduce el nombre completo del fichero de datos" << endl;
            cin >> nombrefichero;
            G.actualizar(nombrefichero, error_apertura);
            if (error_apertura == 1) {
              cout << "Error en la apertura del fichero: revisa nombre y formato : puedes volver a intentarlo" << endl;
            } else {
              cout << "Fichero cargado correctamente desde " << nombrefichero << endl;
            };
            pressanykey();
            clrscr();
            break;

          case 'i' :
            clrscr();
		        cout << "Grafo cargado desde " << nombrefichero << endl;
            G.Info_Grafo();
            pressanykey();
            clrscr();
            break;

          case 's':
            clrscr();
            // Mostrar la lista de sucesores de G
            G.Mostrar_Listas(1);
            pressanykey();
            clrscr();
            break;

          case 'p':
            clrscr();
            // Mostrar la lista de predecesores de G
            G.Mostrar_Listas(-1);
            pressanykey();
            clrscr();
            break;

          case 'a':
            clrscr();
            // Mostrar la lista de adyacentes de G
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
        }
      } while (opcion != 'q'); // Si el usuario pulsa la tecla 'q', fin de programa
    }
    // Terminamos nuestro programa
    cout << "Fin del programa" << endl;
	return(0);
};