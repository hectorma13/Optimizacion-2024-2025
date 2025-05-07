/*
 * GRAFO.CPP - Plantilla para la implementación de la clase GRAFOS
 *
 * Autores: Antonio Sedeno Noda, Sergio Alonso
 * Alumno: Héctor Martín Álvarez
 * Curso: 2024-2025
 */

 #include "grafo.h"

 void GRAFO::destroy() {
   LS.clear();
   if (dirigido == 1) {
     LP.clear();
   }
 }
 
 void GRAFO::build(char nombrefichero[85], int &errorapertura) {
   ElementoLista dummy;
   ifstream textfile;
   textfile.open(nombrefichero);
   if (!textfile) {
     errorapertura = 1;
     return;
   }
 
   if (textfile.is_open()) {
     unsigned i, j, k;
     textfile >> (unsigned &)n >> (unsigned &)m >> (unsigned &)dirigido;
     LS.resize(n);
 
     if (dirigido == 1) {
       for (k = 0; k < m; k++) {
         textfile >> (unsigned &)i >> (unsigned &)j >> (int &)dummy.c;
         dummy.j = j - 1;
         LS[i - 1].push_back(dummy);
       }
       ListaPredecesores();
     } else {
       for (k = 0; k < m; k++) {
         textfile >> (unsigned &)i >> (unsigned &)j >> (int &)dummy.c;
         dummy.j = j - 1;
         LS[i - 1].push_back(dummy);
         if (i - 1 != j - 1) {
           dummy.j = i - 1;
           LS[j - 1].push_back(dummy);
         }
       }
     }
     errorapertura = 0;
     textfile.close();
   }
 }
 
 GRAFO::~GRAFO() {
   destroy();
 }
 
 GRAFO::GRAFO(char nombrefichero[85], int &errorapertura) {
   build(nombrefichero, errorapertura);
 }
 
 void GRAFO::actualizar(char nombrefichero[85], int &errorapertura) {
   destroy();
   build(nombrefichero, errorapertura);
 }
 
 unsigned GRAFO::Es_dirigido() {
   return dirigido;
 }
 
 void GRAFO::Info_Grafo() {
   cout << "Número de nodos (n): " << n << endl;
   cout << "Número de arcos (m): " << m << endl;
   cout << "El grafo es " << (dirigido != 0 ? "dirigido" : "no dirigido") << endl;
 }
 
 void Mostrar_Lista(vector<LA_nodo> L) {
   cout << "\nA continuación podrás ver, para cada nodo del grafo, los nodos que lo suceden, preceden o adyacen junto con su costo\n";
   cout << "La salida es de la forma NODO (i) -> {j, c}, donde:\n";
   cout << "- i: es el nodo para el que se muestra la información\n";
   cout << "- j: es el nodo sucesor/predecesor/adyacente a i\n";
   cout << "- c: es el costo asociado al arco/arista que une a i y j\n";
 
   for (int i{0}; i < L.size(); i++) {
     unsigned arco_nulo = 0;
     cout << "NODO (" << i + 1 << ") -> ";
     for (int j{0}; j < L[i].size(); j++) {
       cout << "{" << L[i][j].j + 1 << ", " << L[i][j].c << "} ";
       arco_nulo = 1;
     }
     if (arco_nulo == 0) {
       cout << "{∅}";
     }
     cout << "\n";
   }
   cout << "\n";
 }
 
 void GRAFO::Mostrar_Listas(int l) {
   if (l == 0) {
     Mostrar_Lista(LS);
   } else if (l == 1) {
     Mostrar_Lista(LS);
   } else if (l == -1) {
     Mostrar_Lista(LP);
   } else {
     cout << "Valor incorrecto, no hay lista para mostrar\n";
   }
 }
 
 void GRAFO::ListaPredecesores() {
   ElementoLista dummy;
   LP.resize(n);
   for (unsigned i{0}; i < n; i++) {
     if (!LS[i].empty()) {
       for (unsigned j{0}; j < LS[i].size(); j++) {
         dummy.c = LS[i][j].c;
         dummy.j = i;
         LP[LS[i][j].j].push_back(dummy);
       }
     }
   }
 }
 
 void GRAFO::dfs_cc(unsigned i, vector<bool> &visitado) {
   visitado[i] = true;
   cout << i + 1;
   for (unsigned j{0}; j < LS[i].size(); j++) {
     if (!visitado[LS[i][j].j]) {
       cout << ", ";
       dfs_cc(LS[i][j].j, visitado);
     }
   }
 }
 
 void GRAFO::ComponentesConexas() {
   cout << "Las componentes conexas del grafo son:\n";
   unsigned i{0}, componentesconexas{0};
   vector<bool> visitado;
   visitado.resize(n, false);
   while (i < n) {
     if (!visitado[i]) {
       cout << "Componente Conexa " << ++componentesconexas << ": {";
       dfs_cc(i, visitado);
       cout << "}";
     }
     i++;
     cout << "\n";
   }
 }
 
 void GRAFO::dfs_cfc(unsigned i, vector<bool> &visitado) {
   visitado[i] = true;
   cout << i + 1;
   for (unsigned j{0}; j < LP[i].size(); j++) {
     if (!visitado[LP[i][j].j]) {
       cout << ", ";
       dfs_cfc(LP[i][j].j, visitado);
     }
   }
 }
 
 void GRAFO::dfs_postnum(unsigned i, vector<bool> &visitado,
                         vector<unsigned> &postnum, unsigned &postnum_ind) {
   visitado[i] = true;
   for (unsigned j{0}; j < LS[i].size(); j++) {
     if (!visitado[LS[i][j].j]) {
       dfs_postnum(LS[i][j].j, visitado, postnum, postnum_ind);
     }
   }
   postnum[postnum_ind--] = i;
 }
 
 void GRAFO::ComponentesFuertementeConexas() {
   cout << "Las Componente Fuertemente Conexa del grafo son:\n";
   unsigned i{0}, postnum_ind{n - 1}, componentesfuertementeconexas{0};
   vector<bool> visitado;
   vector<unsigned> postnum;
   visitado.resize(n, false);
   postnum.resize(n, UERROR);
 
   while (i < n) {
     if (!visitado[i]) {
       dfs_postnum(i, visitado, postnum, postnum_ind);
     }
     i++;
   }
 
   visitado.clear();
   visitado.resize(n, false);
   i = 0;
   while (i < n) {
     if (!visitado[postnum[i]]) {
       componentesfuertementeconexas++;
       cout << "Componente Fuertemente Conexa: " << componentesfuertementeconexas << ": {";
       dfs_cfc(postnum[i], visitado);
       cout << "}\n";
     }
     i++;
   }
 }
 
 void GRAFO::Vecino_Cercano(const vunsigned& Nk, unsigned& ik, unsigned& jk, const vector<unsigned>& Raiz) {
   int min_coste = maxint;
   ik = UERROR;
   jk = UERROR;
 
   for (unsigned i = 0; i < Nk.size(); i++) {
     unsigned nodo_i = Nk[i];
     for (unsigned j = 0; j < LS[nodo_i].size(); j++) {
       unsigned nodo_j = LS[nodo_i][j].j;
       int coste = LS[nodo_i][j].c;
       if (Raiz[nodo_i] != Raiz[nodo_j] && coste < min_coste) {
         min_coste = coste;
         ik = nodo_i;
         jk = nodo_j;
       }
     }
   }
 }
 
 void GRAFO::Union(unsigned ik, unsigned jk, vector<vunsigned>& N, vector<unsigned>& Raiz, int& AristasAdd, int& peso_total) {
   cout << endl;
   if (ik != UERROR) {
     int coste = 0;
     for (unsigned k = 0; k < LS[ik].size(); k++) {
       if (LS[ik][k].j == jk) {
         coste = LS[ik][k].c;
         break;
       }
     }
 
     AristasAdd++;
     peso_total += coste;
     cout << "    Arista (" << ik+1 << "," << jk+1 << ") con peso " << coste << " añadida al árbol";
 
     unsigned NewRaiz = Raiz[ik];
     unsigned OldRaiz = Raiz[jk];
 
     if (NewRaiz > OldRaiz) {
       swap(NewRaiz, OldRaiz);
     }
 
     for (unsigned i = 0; i < N[OldRaiz].size(); i++) {
       unsigned nodo = N[OldRaiz][i];
       Raiz[nodo] = NewRaiz;
       N[NewRaiz].push_back(nodo);
     }
 
     N[OldRaiz].clear();
   }
 }
 
 void GRAFO::Sollin() {
   vector<vunsigned> N;
   vector<unsigned> Raiz;
   Raiz.resize(n);
   N.resize(n);
 
   cout << "\nAlgoritmo de Sollin para encontrar árbol generador de mínimo coste\n";
   cout << "--------------------------------------------------------------------\n";
 
   for (unsigned i = 0; i < n; i++) {
     Raiz[i] = i;
     N[i].push_back(i);
   }
 
   cout << "Componentes conexas iniciales:" << endl;
   for (unsigned i = 0; i < n; i++) {
     if (!N[i].empty()) {
       cout << "Componente " << i+1 << ": {";
       for (unsigned j = 0; j < N[i].size(); j++) {
         cout << N[i][j]+1;
         if (j < N[i].size()-1) cout << ", ";
       }
       cout << "}" << endl;
     }
   }
 
   cout << "\n--------------------------------------------------------------------";
 
   int AristasAdd = 0;
   int peso_total = 0;
   bool componentes_modificadas;
   unsigned iteraciones{0};
 
   while (AristasAdd < n-1) {
     cout << "\n\nITERACIÓN NÚMERO " << ++iteraciones << " /////////////////////////////////////////////////" << endl;
     componentes_modificadas = false;
 
     for (unsigned k = 0; k < n; k++) {
       if (!N[k].empty()) {
         unsigned ik, jk;
         Vecino_Cercano(N[k], ik, jk, Raiz);
         if (ik != UERROR) {
           Union(ik, jk, N, Raiz, AristasAdd, peso_total);
           componentes_modificadas = true;
         }
       }
     }
 
     if (!componentes_modificadas) {
       cout << "\nEl grafo no es conexo. No se puede construir un árbol generador completo." << endl;
       break;
     }
 
     cout << "\n    Componentes conexas después de la iteración número " << iteraciones << ":" << endl;
     int numero_cc{0};
     for (unsigned i = 0; i < n; i++) {
       if (!N[i].empty()) {
         cout << "        Componente " << i+1 << ": {";
         for (unsigned j = 0; j < N[i].size(); j++) {
           cout << N[i][j]+1;
           if (j < N[i].size()-1) cout << ", ";
         }
         cout << "}" << endl;
         numero_cc++;
       }
     }
     cout << "\nMODIFICACIÓN: Hay " << numero_cc << " componentes conexas después de la " << iteraciones << " iteración" << endl;
 
     if (AristasAdd == n-1) {
       cout << "\n--------------------------------------------------------------------\n";
       cout << "\nEl peso total del árbol generador de mínimo coste es: " << peso_total << endl;
       break;
     }
   }
 }
 
 void MostrarCamino(unsigned s, unsigned i, LA_nodo pred) {
   if (i != s) {
     MostrarCamino(s, pred[i].j, pred);
     cout << " -> " << i+1;
   } else {
     cout << i+1;
   }
 }
 
 void GRAFO::ImprimirMatrices(unsigned dim, unsigned k, const vector<LA_nodo>& P) {
   if (k < dim) {
     cout << "\nMatrices D y Pred después de la iteración k = " << k << endl;
   } else {
     cout << "\nMatrices D y Pred finales:" << endl;
   }
 
   cout << "\nMatriz de distancias D:\n\n   ";
   for (unsigned j = 0; j < dim; j++) {
     cout << setw(8) << j+1;
   }
   cout << "\n\n";
   for (unsigned i = 0; i < dim; i++) {
     cout << setw(3) << i+1;
     for (unsigned j = 0; j < dim; j++) {
       if (P[i][j].c == maxint) {
         cout << "       ∞";
       } else if (P[i][j].c < 0) {
         cout << "      " << P[i][j].c;
       } else {
         cout << "       " << P[i][j].c;
       }
     }
     cout << "\n";
   }
 
   cout << "\nMatriz de predecesores Pred:\n   ";
   for (unsigned j = 0; j < dim; j++) {
     cout << setw(8) << j+1;
   }
   cout << "\n";
   for (unsigned i = 0; i < dim; i++) {
     cout << setw(3) << i+1;
     for (unsigned j = 0; j < dim; j++) {
       if (P[i][j].j == UERROR) {
         cout << setw(8) << "0";
       } else {
         cout << setw(8) << P[i][j].j + 1;
       }
     }
     cout << "\n";
   }
 }
 
 void GRAFO::Floyd_Warshall() {
   cout << "\nAlgoritmo de Floyd-Warshall para caminos mínimos entre todos los pares de nodos\n";
   cout << "----------------------------------------------------------------------------\n";
 
   vector<LA_nodo> P;
   bool circuitocostenegativo = false;
   P.resize(n);
   for (unsigned i = 0; i < n; i++) {
     P[i].resize(n);
   }
 
   for (unsigned i = 0; i < n; i++) {
     for (unsigned j = 0; j < n; j++) {
       if (i != j) {
         P[i][j].j = UERROR;
         P[i][j].c = maxint;
       } else {
         P[i][j].j = i;
         P[i][j].c = 0;
       }
     }
   }
 
   for (unsigned i = 0; i < n; i++) {
     for (unsigned j = 0; j < LS[i].size(); j++) {
       unsigned sucesor = LS[i][j].j;
       int coste = LS[i][j].c;
       P[i][sucesor].j = i;
       P[i][sucesor].c = coste;
     }
   }
 
   cout << "\nMatrices iniciales antes de comenzar el algoritmo:" << endl;
   ImprimirMatrices(n, 0, P);
 
   for (unsigned k = 0; k < n; k++) {
     ImprimirMatrices(n, k, P);
     for (unsigned i = 0; i < n; i++) {
       if (i != k) {
         for (unsigned j = 0; j < n; j++) {
           if (j != k) {
             if (P[i][k].c != maxint && P[k][j].c != maxint &&
                 P[i][j].c > P[i][k].c + P[k][j].c) {
               P[i][j].c = P[i][k].c + P[k][j].c;
               P[i][j].j = P[k][j].j;
             }
           }
         }
       }
     }
   }
 
   ImprimirMatrices(n, n, P);
 
   int donde_hay_coste_negativo;
   for (unsigned i = 0; i < n; i++) {
     if (P[i][i].c < 0) {
       circuitocostenegativo = true;
       donde_hay_coste_negativo = i;
       break;
     }
   }
 
   if (!circuitocostenegativo) {
     cout << "\nCaminos mínimos entre cada par de nodos:\n\n";
     for (unsigned i = 0; i < n; i++) {
       for (unsigned j = 0; j < n; j++) {
         if (i != j) {
           if (P[i][j].c == maxint) {
             cout << "No existe camino de " << i+1 << " a " << j+1 << endl;
           } else {
             cout << "Camino mínimo de " << i+1 << " a " << j+1 << ": ";
             MostrarCamino(i, j, P[i]);
             cout << " (coste: " << P[i][j].c << ")" << endl;
           }
         }
       }
     }
   } else {
     cout << "\n¡Hay circuitos de coste negativo en el grafo!" << endl;
     cout << "Primer camino de coste negativo: ";
     MostrarCamino(donde_hay_coste_negativo, P[donde_hay_coste_negativo][donde_hay_coste_negativo].j, P[donde_hay_coste_negativo]);
     cout << " -> " << donde_hay_coste_negativo + 1 << endl;
     cout << "\nCoste: " << P[donde_hay_coste_negativo][donde_hay_coste_negativo].c << endl;
     cout << "Es el elemento (" << donde_hay_coste_negativo << ", " << donde_hay_coste_negativo << ") de la diagonal de la matriz d\n";
     cout << "\nNo aceptamos la solución, pues hay circuitos de coste negativos.\n";
   }
 }