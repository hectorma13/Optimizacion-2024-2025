/*
 * GRAFO.h - Definición de la clase GRAFO
 *
 * Autores: Antonio Sedeno Noda, Sergio Alonso
 * Alumno: Héctor Martín Álvarez
 * Curso: 2024-2025
*/

#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <iostream>
#include <fstream>
#include <queue>
#include <deque>

using namespace std;

//Solo para ubuntu, una forma de borrar la pantalla
#define gotoxy(x,y)  printf("\33[%d;%dH",y,x)
#define clrscr()     gotoxy(1,1); printf("\33[2J")

const unsigned UERROR = 65000;    //Para ciertos algoritmos es necesario codificar este valor de error
const int maxint = 1000000;       //Para ciertos algoritmos es necesario codificar este valor de maximo

/**
 * @brief Definición de un elemento de la lista de adyacencia
 */
typedef struct {
	// Nodo
  unsigned j;
  // Atributo para expresar los costes, pesos, las longitudes, las inversiones, etc...
  int c;
} ElementoLista;

/**
 * @brief Definición del tipo de una lista de adyacencia de un nodo
 *  
 * Sería de la forma { {j, c}, {j, c}, ..., {j, c} }
 */
typedef vector<ElementoLista> LA_nodo;

// PRÁCTICA 4: SOLLIN
typedef vector<unsigned> vunsigned;

class GRAFO {
	
  //0 si el grafo es no dirigido y 1 si es dirigido
  unsigned dirigido;
	// numero de NODOS
  unsigned n;
  // numero de ARCOS
	unsigned m;
  // Lista de adyacencia de los sucesores: es una matriz donde cada fila posiblemente es posiblemente de distinto tamano
  vector<LA_nodo> LS;
  // Lista de adyacencia de los predecesores: es una matriz dode cada fila posiblemente es posiblemente de distinto tamano
	vector<LA_nodo> LP;

  // FASE 1 DE LA PRACTICA
  
  // Destructor del LS, y, en su caso, LP
	void destroy();
  //Crea LS, A y, en su caso, LP, desde la lectura del fichero
	void build (char nombrefichero[85], int &errorapertura);


  // PRÁCTICA 3 ////////////////////////////////////////////////////

  // Recorrido en profundidad recursivo con solo marca de visitado para el calculo de las componentes conexas
	void dfs_cc(unsigned i, vector<bool> &visitado);
  //Recorrido en profundidad recursivo para calcular postnum
	void dfs_postnum(unsigned i, vector<bool> &visitado, vector<unsigned> &postnum, unsigned &postnum_ind);
	// Recorrido en profundidad recursivo con solo marca de visitado para el calculo de las componentes fuertemente conexas
  void dfs_cfc(unsigned i, vector<bool> &visitado);


  // PRÁCTICA 4 ////////////////////////////////////////////////////
  
    // Encuentra la arista de menor coste que conecta una componente con otra distinta
    void Vecino_Cercano(const vunsigned& Nk, unsigned& ik, unsigned& jk, const vector<unsigned>& Raiz);
    // Une dos componentes conexas distintas
    void Union(unsigned ik, unsigned jk, vector<vunsigned>& N, vector<unsigned>& Raiz, int& AristasAdd, int& peso_total);


public:

  // PRÁCTICA 3 ////////////////////////////////////////////////////


	// Constructor de la clase GRAFO
  GRAFO(char nombrefichero[], int &errorapertura);
  
  void actualizar (char nombrefichero[], int &errorapertura);

	/**
   * @brief Devuelve 0 si el grafo es no dirigido, y 1 si es dirigido
   */
  unsigned Es_dirigido();

	/**
   * @brief Muestra la información básica de un grafo: número de nodos, 
   * su orden, número de arcos o aristas y su tipo
   */
  void Info_Grafo();

  /**
   * @brief Muestra la lista de adyacencia
   * 
   * @param l Indica el tipo de lista que queremos mostrar, donde 0 es la
   * lista de adyacentes de un Grafo G no digirido, 1 es la lista de sucesores
   * de un Grafo G dirigido y -1 es la lista de predecesores de un Grafo G dirigido
   * 
   */
	void Mostrar_Listas(int l);

  /**
   * @brief Recorre la lista de sucesores LS para construir la de predecesores, LP
   */
	void ListaPredecesores();

  //Destructor del grafo
	~GRAFO();

  //Construye el vector de componentes conexas de un grafo no dirigido para
  // cada nodo
  void ComponentesConexas();

  //Construye el vector de componentes conexas de un grafo no dirigido para
  void ComponentesFuertementeConexas();

  
  
  // PRÁCTICA 4 ////////////////////////////////////////////////////
  void Sollin();

};

#endif