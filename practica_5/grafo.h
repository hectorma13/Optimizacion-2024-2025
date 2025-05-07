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
 #include <iomanip>
 
 using namespace std;
 
 #define gotoxy(x,y) printf("\33[%d;%dH",y,x)
 #define clrscr()    gotoxy(1,1); printf("\33[2J")
 
 const unsigned UERROR = 65000;
 const int maxint = 1000000;
 
 typedef struct {
   unsigned j;
   int c;
 } ElementoLista;
 
 typedef vector<ElementoLista> LA_nodo;
 
 typedef vector<unsigned> vunsigned;
 
 class GRAFO {
  public:
   unsigned dirigido;
   unsigned n;
   unsigned m;
   vector<LA_nodo> LS;
   vector<LA_nodo> LP;
   vector<LA_nodo> P;
 
   GRAFO(char nombrefichero[], int &errorapertura);
   void actualizar(char nombrefichero[], int &errorapertura);
   unsigned Es_dirigido();
   void Info_Grafo();
   void Mostrar_Listas(int l);
   void ListaPredecesores();
   ~GRAFO();
   void ComponentesConexas();
   void ComponentesFuertementeConexas();
   void Sollin();
   void Floyd_Warshall();
 
  private:
   void destroy();
   void build(char nombrefichero[85], int &errorapertura);
   void dfs_cc(unsigned i, vector<bool> &visitado);
   void dfs_postnum(unsigned i, vector<bool> &visitado, vector<unsigned> &postnum, unsigned &postnum_ind);
   void dfs_cfc(unsigned i, vector<bool> &visitado);
   void Vecino_Cercano(const vunsigned& Nk, unsigned& ik, unsigned& jk, const vector<unsigned>& Raiz);
   void Union(unsigned ik, unsigned jk, vector<vunsigned>& N, vector<unsigned>& Raiz, int& AristasAdd, int& peso_total);
   void ImprimirMatrices(unsigned dim, unsigned k, const vector<LA_nodo>& P);
 };
 
 #endif  // _GRAPH_H