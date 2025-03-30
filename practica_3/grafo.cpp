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