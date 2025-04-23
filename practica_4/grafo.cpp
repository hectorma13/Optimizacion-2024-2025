/*
 * GRAFO.CPP - Plantilla para la implementación de la clase GRAFOS
 *
 * Autores: Antonio Sedeno Noda, Sergio Alonso
 * Alumno: Héctor Martín Álvarez
 * Curso: 2024-2025
*/

#include "grafo.h"

// FASE 1 /////////////////////////////////////////////////////////////////////


/**
 * @brief Método con el que libero la memoria de las listas de adyacencia, LS
 * y LP, si el grafo es dirigido. Se ejecutará en el destructor de la clase
 * GRAFO. Lo programamos aparte (no directamente en el destructor) para poder
 * reutilizarlo en el método actualizar().
 */
void GRAFO::destroy() {
  /*
	// Itero para cada nodo del Grafo (desde 0 hasta n - 1)
	for (unsigned i = 0; i < n; i++) {
		// Se limpian todos los arcos para el nodo i
		LS[i].clear();
		// Si el Grafo es dirigido, se hace lo mismo con los predecesores
		if (dirigido == 1) {
			LP[i].clear();
		}
	}
	// Se elimina el vector de sucesores o adyacentes
	LS.clear();
	// Si el grafo es dirigido, se hace lo mismo con el vector de predecesores
	if (dirigido == 1) {
    LP.clear();
  }
  */

  LS.clear();

  if (dirigido == 1) {
    LP.clear();
  }
}

/*
  Es el método para cargar desde fichero los datos del grafo, y según sea un
  grafo dirigido o no dirigido, construir la lista de sucesores y la lista de 
  predecesores, LS y LP, respectivamente en el primer caso, o sólo la lista de 
  adyacencia en LS. Si ocurriera algún error en la apertura del fichero de texto, 
  devolvería un 1 en errorapertura.
*/
void GRAFO::build(char nombrefichero[85], int &errorapertura) {
  // Creo un ElementoLista con su nodo sucesor y coste {j, c}
  ElementoLista dummy;

  // Creo un objeto "fichero de entrada"
	ifstream textfile;

  // Abro dicho archivo
	textfile.open(nombrefichero);

  // Compruebo si ha abierto el archivo
  if (!textfile) {

    // Si no se ha abierto, devolvemos error
    errorapertura = 1;
		return;
  }

  // Verifico si ha abierto correctamente y comienzo el proceso de construcción
	if (textfile.is_open()){

    /*
      Creamos las variables para llenar la lista de adyacencia de los sucesores
      - i = Nodo predecesor del arco
      - j = Nodo sucesor del arco
      - k = coste del arco
    */
		unsigned i, j, k;

		// Leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
    // Esta es la primera línea de texto de textfile (ej. 6 4 1)
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;

		// Los nodos internamente se numeran desde 0 a n-1
		// Creamos las n listas de sucesores (una para cada nodo)
		LS.resize(n);
    
    // Si el grafo es dirigido:
		if (dirigido == 1) {

			// Leo los m arcos

			/*
				Crearé una lista de sucesores
				Cada elemento será un nodo (0,...,n - 1)
			*/
			for (k = 0; k < m; k++) {
        
				textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
				// Doy los valores a dummy.j y dummy.c
				// Añado a nuestro objeto ElementoLista el nodo sucesor a i
				dummy.j = j - 1;
	
				//Situamos en la posición del nodo i a dummy mediante push_back
				// Añadimos el nodo sucesor a i y su coste a nuestra lista
				LS[i - 1].push_back(dummy);
			}

			// Creamos la lista de predecesores con ListaPredecesores()
			ListaPredecesores();
		} 

    // Si no es dirigido
    else {
			for (k = 0; k < m; k++) {
				textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
				
				dummy.j = j - 1;
				LS[i - 1].push_back(dummy);

				// Si leemos del fichero de texto la arista (i, j), debemos situar j
				// como adyacente de i, pero también a i como adyacente de j, excepto
				// en el caso de que se trate de un bucle
				if (i - 1 != j - 1) {
					dummy.j = i - 1;
					LS[j - 1].push_back(dummy); 
				}

				// Aquí no habría lista de predecesores (LP), sólo de adyacencia (LS)
			}
		}

		// Todo se ha realizado con éxito, por tanto:
		errorapertura = 0;

    // Cierro el archivo de texto
    textfile.close();
  }
}

/*
  @brief Es el destructor de la clase GRAFO, y se dedica a liberar la memoria 
	de las listas de adyacencia. 
	
	NOTA DE LOS AUTORES: No olvides ejecutarlo antes de la finalización del programa.
*/
GRAFO::~GRAFO() {
	// Utilizo el método destroy() para liberar la memoria de LS y, en su caso, LP
	destroy();
}

/**
 * @brief Constructor de la clase GRAFO, que recibe el nombre del fichero de que
 * contiene los datos del grafo y un entero (por referencia) que indica si ha
 * habido un error en la apertura del fichero.
 */
GRAFO::GRAFO(char nombrefichero[85], int &errorapertura) {
	// Utilizamos el método build() para cargar los datos del grafo
	build(nombrefichero, errorapertura);
}

/**
 * @brief Método que utilizo para actualizar el grafo, liberando la memoria
 * y cargando los datos del fichero de texto que se le pasa como argumento a
 * nuestro objeto GRAFO.
 */
void GRAFO::actualizar(char nombrefichero[85], int &errorapertura) {
    //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
    destroy();
    //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
    build(nombrefichero, errorapertura);
}

/*
  Devuelve 0 si el grafo es no dirigido, y 1 en otro caso. 
  Esta función servirá para distinguir que tipo de grafo se
  ha cargado y, desde el programa principal, mostrar el menú
  de opciones para grafos dirigidos o no dirigidos.
*/
unsigned GRAFO::Es_dirigido() {
  return dirigido;
}

/*
  Muestra la información básica de un grafo: número de nodos, su orden, 
  número de arcos o aristas y su tipo.
*/
void GRAFO::Info_Grafo() {
  cout << "Número de nodos (n): " << n << endl;
  cout << "Número de arcos (m): " << m << endl;
  cout << "El grafo es " << (dirigido != 0 ? "dirigido" : "no dirigido") << endl;
}

// Mostramos la lista que pasamos como argumento
void Mostrar_Lista(vector<LA_nodo> L) {
  cout << "\nA continuación podrás ver, para cada nodo del grafo, "
  << "los nodos que lo suceden, preceden o adyacen junto con su costo\n";
  cout << "La salida es de la forma NODO (i) -> {j, c}, donde:\n\n";
  cout << "- i: es el nodo para el que se muestra la información\n" << 
  "- j: es el nodo sucesor/predecesor/adyacente a i\n" <<
  "- c: es el costo asociado al arco/arista que une a i y j\n\n";

	// Iteramos para cada nodo (para mostrar su adyacente/sucesor/predecesor)
	for (int i{0}; i < L.size(); i++) {

		unsigned arco_nulo = 0;

		cout << "NODO (" << i + 1 << ") -> ";

		for (int j{0}; j < L[i].size(); j++) {

			cout << "{" << L[i][j].j + 1 << ", " << L[i][j].c << "} ";

			// Simboliza que hay al menos un arco relacionado con i
			arco_nulo = 1; 
		}

		// Si no hay arcos, muestro el conjunto vacío de arcos {∅}

		(arco_nulo == 0) ? cout << "{∅ }" : cout << "";

		cout << "\n";	
	}
	cout << "\n";
}

/*
	Según el parámetro l, mostrará la lista de sucesores y predecesores, o sólo 
	la lista de adyacentes, según el tipo de grafo que sea. Por ejemplo, si el 
	grafo es no dirigido, el valor de l=0 mostrará la lista de adyacencia del 
	grafo; si el grafo es dirigido, el valor l=+1 mostrará la lista de sucesores 
	y l=-1 la lista de predecesores.
*/
void GRAFO::Mostrar_Listas(int l) {
	// Para lo que sería mostrar la lista determinada (en función del arg. l)
	// utilizaré otra función llamada Mostrar_Listas(), a la que le pasaré
	// cómo argumento la lista a mostrar (dos posibles, LS y LP)
	
	if (l == 0) { 			// Mostrar la lista de adyacentes de un G no digirido
		Mostrar_Lista(LS);
	} else if (l == 1) { 	// Mostrar la lista de sucesores de un G digirido
		Mostrar_Lista(LS);
	} else if (l == -1) { 	// Mostrar la lista de predecesores de un G digirido
		Mostrar_Lista(LP);
	} else { 				// En caso de que el argumento l != {-1,0,1}
		cout << "Valor incorrecto, no hay lista para mostrar\n";
	}
}

//Recorre la lista de sucesores LS para construir la de predecesores, LP
void GRAFO::ListaPredecesores() { 
	
	ElementoLista dummy;
	// Hacemos que nuestra lista LP tenga tamaño n
	// Sabiendo que n = nº de nodos
	LP.resize(n);

	for (unsigned i{0}; i < n; i++) {
		if (LS[i].empty() == false) {
			for (unsigned j{0}; j < LS[i].size(); j++) {
			dummy.c = LS[i][j].c;
			dummy.j = i;
			LP[LS[i][j].j].push_back(dummy);
			}
		}
	}
}

// FASE 2 /////////////////////////////////////////////////////////////////////
/**
 * @brief Recorrido en profundidad del GRAFO para buscar
 * componentes conexas
 * 
 * @param i nodo que se le pasa para explorar sus sucesores recursivamente
 * @param visitado lista de nodos visitados para no hacer revisitas
 */
void GRAFO::dfs_cc(unsigned i, vector<bool> &visitado) {

  // Hago que el nodo actual se declare como visitado
  visitado[i] = true;

  // Imprimo el nodo que se está recorriendo por pantalla
  cout << i + 1;

  // Recorro todos los sucesores (LS) del nodo i
  for (unsigned j{0}; j < LS[i].size(); j++) {
    
    // Si el nodo sucesor de i no ha sido visitado:
    if (!visitado[LS[i][j].j]) {
      cout << ", ";
      
      // Se analiza este sucesor de i recursivamente
      dfs_cc(LS[i][j].j, visitado);
    }
  }
}

/**
 * @brief Encuentra y muestra todas las componentes conexas de un grafo no
 * dirigido Uso la búsqueda en profundidad (DFS) para identificar las 
 * componentes conexas del grafo.
 */
void GRAFO::ComponentesConexas() {

  // Información del método ComponentesConexas para la interfaz
  cout << "Las componentes conexas del grafo son:\n\n";
  // Primer nodo y contador de componentes conexas
  unsigned i{0}, componentesconexas{0};

  // Vector de nodos visitados, qué tiene tantos elementos cómo nodos el grafo
  vector<bool> visitado;
  visitado.resize(n, false);

  while (i < n) {

    // Vemos si el nodo actual ha sido visitado
    if (visitado[i] == false) {
      // Si no ha sido visitado:
      // Buscamos a partir del nodo actual
      cout <<  "Componente Conexa " << ++componentesconexas << ": {";
      // Obtenemos todos los nodos a los que se puede ir desde i
      // y qué no han sido visitados
      dfs_cc(i, visitado);
      cout << "}\n";
    }
    // Convertimos el nodo siguiente en el actual para la siguiente iteración
    i++;
  }
}

/**
 * @brief Método de recorrido en profundidad con el fin de encontrar
 * componentes fuertemente conexas. Es el mismo método que dfs_cc, pero
 * en este se utiliza la lista de predecesores en lugar de la de sucesores
 */
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

/**
 * @brief Este recorrido está hecho para calcular el orden de postnumeración
 * de los nodos.
 * 
 * @param postnum es el número que recibe un nodo (i) cuando su exploración 
 * ha terminado por completo.
 * @param i nodo actual, que se le ha pasado al método para ver su postnum
 * @param visitado lista de nodos visitados para no revisitar nodos
 * @param postnum_ind índice que se decrementará con cada asignación a postnum 
 */
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

/**
 * @brief Método para
 */
void GRAFO::ComponentesFuertementeConexas() {
  cout << "Las Componente Fuertemente Conexa del grafo son:\n\n";
  
  // Nodo actual, índice de postnumeración y nº de cfc del grafo
  unsigned i{0}, postnum_ind{n - 1}, componentesfuertementeconexas{0};

  // Vector de nodos visitados
  vector<bool> visitado;
  // Vector de postnum para el GRAFO
  vector<unsigned> postnum;

  // Hago que ambos vectores tengan tamaño n (para n nodos)
  visitado.resize(n,false);
  postnum.resize(n,UERROR);

  // Itero para cada nodo del grafo (de 0 a n-1) con el fin de obtener la lista
  // de postnumeración
  while (i < n) {
    if (visitado[i] == false) {
      dfs_postnum(i, visitado, postnum, postnum_ind);
    }
    i++;
  }

  // En este punto, tengo la lista de postnumeración ya completada

  visitado.clear();
  visitado.resize(n, false);
  i = 0;
  while (i < n) {
    if (visitado[postnum[i]] == false) {
      componentesfuertementeconexas++;
      
      cout << "Componente Fuertemente Conexa: " << 
      componentesfuertementeconexas << ": {";

      dfs_cfc(postnum[i], visitado);
      cout << "}\n";
    }
    i++;
  }
}

// PRÁCTICA 4 ////////////////////////////////////////////////////

// Encuentra la arista de menor coste que conecta una componente con otra distinta
void GRAFO::Vecino_Cercano(const vunsigned& Nk, unsigned& ik, unsigned& jk, const vector<unsigned>& Raiz) {
  int min_coste = maxint; // Inicializar con un valor grande
  ik = UERROR;
  jk = UERROR;
  
  // Para cada nodo de la componente conexa
  for (unsigned i = 0; i < Nk.size(); i++) {
    unsigned nodo_i = Nk[i];
    
    // Recorrer todos los adyacentes de este nodo
    for (unsigned j = 0; j < LS[nodo_i].size(); j++) {
      unsigned nodo_j = LS[nodo_i][j].j;
      int coste = LS[nodo_i][j].c;
      
      // Si el adyacente está en una componente distinta y el coste es menor al mínimo encontrado
      if (Raiz[nodo_i] != Raiz[nodo_j] && coste < min_coste) {
        min_coste = coste;
        ik = nodo_i;
        jk = nodo_j;
      }
    }
  }
}

// Une dos componentes conexas distintas
void GRAFO::Union(unsigned ik, unsigned jk, vector<vunsigned>& N, vector<unsigned>& Raiz, int& AristasAdd, int& peso_total) {
  cout << endl;
  if (ik != UERROR) {
    // Encontrar el coste de la arista entre ik y jk
    int coste = 0;
    for (unsigned k = 0; k < LS[ik].size(); k++) {
      if (LS[ik][k].j == jk) {
        coste = LS[ik][k].c;
        break;
      }
    }
    
    // Actualizar contador de aristas y peso total
    AristasAdd++;
    peso_total += coste;
    
    cout << "    Arista (" << ik+1 << "," << jk+1 << ") con peso " << coste << " añadida al árbol";
    
    // Determinar las raíces de las componentes
    unsigned NewRaiz = Raiz[ik];
    unsigned OldRaiz = Raiz[jk];
    
    // La raíz final será la de menor valor
    if (NewRaiz > OldRaiz) {
      NewRaiz = Raiz[jk];
      OldRaiz = Raiz[ik];
    }
    
    // Mover todos los nodos de la componente OldRaiz a NewRaiz
    for (unsigned i = 0; i < N[OldRaiz].size(); i++) {
      unsigned nodo = N[OldRaiz][i];
      Raiz[nodo] = NewRaiz;
      N[NewRaiz].push_back(nodo);
    }
    
    // Vaciar la componente antigua
    N[OldRaiz].clear();
  }
}

void GRAFO::Sollin() {
  // Estructuras de datos
  vector<vunsigned> N;
  vector<unsigned> Raiz;
  
  // Inicialización
  Raiz.resize(n);
  N.resize(n); // tenemos n componentes conexas inicialmente
  
  cout << "\nAlgoritmo de Sollin para encontrar árbol generador de mínimo coste\n";
  cout << "--------------------------------------------------------------------\n" << endl;
  
  // Inicializar: cada nodo está en su propia componente conexa
  for (unsigned i = 0; i < n; i++) {
    Raiz[i] = i;
    N[i].push_back(i);
  }
  
  // Mostrar componentes iniciales: Siempre habrán n CompConexas al principio
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
  cout << "\n--------------------------------------------------------------------\n";
  
  int AristasAdd = 0; // Contador de aristas añadidas
  int peso_total = 0; // Peso total del árbol generador
  bool componentes_modificadas;
  unsigned iteraciones{0};
  
  // Iterar hasta añadir n-1 aristas (árbol) o hasta que no se puedan añadir más aristas
  while (AristasAdd < n-1) {
    cout << "\nITERACIÓN NÚMERO " << ++iteraciones << " /////////////////////////////////////////////////" << endl;
    componentes_modificadas = false;
    
    // Para cada componente conexa no vacía
    for (unsigned k = 0; k < n; k++) {
      if (!N[k].empty()) {
        // Buscar la arista de menor coste que conecta esta componente con otra
        unsigned ik, jk;
        Vecino_Cercano(N[k], ik, jk, Raiz);
        
        // Si encontramos una arista válida, unimos las componentes
        if (ik != UERROR) {
          Union(ik, jk, N, Raiz, AristasAdd, peso_total);
          componentes_modificadas = true;
        }
      }
    }
    
    // Si no se modificaron componentes, el grafo no es conexo  
    if (!componentes_modificadas) {
      cout << "\nEl grafo no es conexo. No se puede construir un árbol generador completo." << endl;
      break;
    }
    
    // Mostrar componentes después de la iteración
    cout << "\n\n    Componentes conexas después de la iteración número " << iteraciones << ":" << endl;
    int numero_cc{0};

    for (unsigned i = 0; i < n; i++) {
      // Si la CompConexa no está vacía
      if (!N[i].empty()) {
        cout << "        Componente " << i+1 << ": {";
        // Iteramos para los nodos de la componente conexa i;
        for (unsigned j = 0; j < N[i].size(); j++) {
          cout << N[i][j]+1;
          
          // Para no poner una coma después del último elemento
          if (j < N[i].size()-1) cout << ", ";
        }
        cout << "}" << endl;
        numero_cc++;
      }
    }
    cout << "\nMODIFICACIÓN: Hay " << numero_cc << " componentes conexas después de la " << iteraciones << " iteración" << endl;
    
    // Si ya hemos añadido n-1 aristas, hemos terminado
    if (AristasAdd == n-1) {
      cout << "\n--------------------------------------------------------------------\n";
      cout << "\nEl peso total del árbol generador de mínimo coste es: " << peso_total << endl;
      break;
    }
  }
}