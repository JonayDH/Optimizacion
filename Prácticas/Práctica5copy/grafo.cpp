/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Optimización 2025-2026
  *
  * @file grafo.cpp
  * @author Jonay Déniz Hernández  alu0101791623@ull.edu.es
  * @date May 7 2026
  * @brief Implementación de la clase grafo
  * @bug There are no known bugs
  * @see https://campusvirtual.ull.es/2526/ingenieriaytecnologia/course/section.php?id=3490
  *
  * This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
  * as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of 
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. 
  */

#include "grafo.h"

/// @brief Método que aplica el algoritmo TWOQ
void GRAFO::TWOQ() {

  deque<unsigned> colarapida{}, colalenta{};
  vector<int> distancia(n, maxint);
  vector<unsigned> predecesor(n, UERROR);
  vector<bool> encola(n, false);

  unsigned nodo_inicio{};
  int coste_minimo = CosteMinimo();

  cout << "Camino mínimo de un nodo al resto: Algoritmo TWOQ" << endl;

  // Pedimos un nodo de inicio
  while ((nodo_inicio < 1) || (nodo_inicio > n)) {

    cout << "Introduce un nodo de inicio [1, " << n << "]: ";
    cin >> nodo_inicio;
  }

  nodo_inicio--; // Ajustamos a como guardamos nosotros los nodos
  cout << endl;

  distancia[nodo_inicio] = 0;
  predecesor[nodo_inicio] = nodo_inicio;
  colalenta.push_back(nodo_inicio);
  encola[nodo_inicio] = true;

  // Mientras que alguna de las colas tenga elementos y no hayas ciclos negativos iteramos
  while ((!colarapida.empty() || !colalenta.empty()) && !HayCicloNegativo(distancia, coste_minimo)) {

    unsigned nodo_actual{};

    // Sacamos el primer nodo de la cola
    if (colarapida.empty() == false) {

      nodo_actual = colarapida.front();
      colarapida.pop_front();
      encola[nodo_actual] = false;
    } else {

      nodo_actual = colalenta.front();
      colalenta.pop_front();
      encola[nodo_actual] = false;
    }

    // Miramos los sucesores de ese nodo
    for (size_t i{}; i < LS[nodo_actual].size(); i++) {
      
      int distancia_nueva = distancia[nodo_actual] + LS[nodo_actual][i].c;
      unsigned sucesor = LS[nodo_actual][i].j;

      // Si la distancia del sucesor es mayor que la distancia del nodo + lo que cuesta ir del nodo al sucesor
      if (distancia_nueva < distancia[sucesor]) {

        // Si nunca ha estado en la cola
        if (predecesor[sucesor] == UERROR) {

          colalenta.push_back(sucesor);
          encola[sucesor] = true;
        } else if (encola[sucesor] == false) { // Si si ha estado pero ahora no esta en cola

          colarapida.push_back(sucesor);
          encola[sucesor] = true;
        }

        distancia[sucesor] = distancia_nueva;
        predecesor[sucesor] = nodo_actual;
      }
    }
  }

  if (HayCicloNegativo(distancia, coste_minimo)) {

    cout << "Hay un ciclo de coste negativo en el grafo." << endl;
  } else {

    cout << "Soluciones: " << endl << endl;

    for (unsigned nodo_final{}; nodo_final < n; nodo_final++) {

      if (predecesor[nodo_final] == UERROR) {

        cout << "No hay camino desde " << nodo_inicio + 1 << " al nodo " << nodo_final + 1;
        cout << endl;
      } else if (nodo_final != nodo_inicio) {

        cout << "El camino desde " << nodo_inicio + 1 << " al nodo " << nodo_final + 1 << " es : "; 
        MostrarCamino(nodo_inicio, nodo_final, predecesor);
        cout << " de longitud " << distancia[nodo_final];
        cout << endl;
      }
    }
  }
}

/// @brief Método que aplica el algoritmo Bellman-Ford-Moore
void GRAFO::BFM() {

  deque<unsigned> cola{};
  vector<int> distancia(n, maxint);
  vector<unsigned> predecesor(n, UERROR);
  vector<bool> encola(n, false);

  unsigned nodo_inicio{};
  int coste_minimo = CosteMinimo();

  cout << "Camino mínimo de un nodo al resto: Algoritmo BFM" << endl;

  // Pedimos un nodo de inicio
  while ((nodo_inicio < 1) || (nodo_inicio > n)) {

    cout << "Introduce un nodo de inicio [1, " << n << "]: ";
    cin >> nodo_inicio;
  }

  nodo_inicio--; // Ajustamos a como guardamos nosotros los nodos
  cout << endl;

  distancia[nodo_inicio] = 0;
  predecesor[nodo_inicio] = nodo_inicio;
  cola.push_back(nodo_inicio);
  encola[nodo_inicio] = true;

  // Mientras que la cola no este vacía y no haya ciclos negativos iteramos
  while ((!cola.empty()) && !HayCicloNegativo(distancia, coste_minimo)) {

    unsigned nodo_actual{};

    // Sacamos el primer nodo de la cola
    nodo_actual = cola.front();
    cola.pop_front();
    encola[nodo_actual] = false;

    // Miramos los sucesores de ese nodo
    for (size_t i{}; i < LS[nodo_actual].size(); i++) {
      
      int distancia_nueva = distancia[nodo_actual] + LS[nodo_actual][i].c;
      unsigned sucesor = LS[nodo_actual][i].j;

      // Si la distancia del sucesor es mayor que la distancia del nodo + lo que cuesta ir del nodo al sucesor
      if (distancia_nueva < distancia[sucesor]) {

        if (encola[sucesor] == false) {

          cola.push_back(sucesor);
          encola[sucesor] = true;
        }

        distancia[sucesor] = distancia_nueva;
        predecesor[sucesor] = nodo_actual;
      }
    }
  }

  if (HayCicloNegativo(distancia, coste_minimo)) {

    cout << "Hay un ciclo de coste negativo en el grafo." << endl;
  } else {

    cout << "Soluciones: " << endl << endl;

    for (unsigned nodo_final{}; nodo_final < n; nodo_final++) {

      if (predecesor[nodo_final] == UERROR) {

        cout << "No hay camino desde " << nodo_inicio + 1 << " al nodo " << nodo_final + 1;
        cout << endl;
      } else if (nodo_final != nodo_inicio) {

        cout << "El camino desde " << nodo_inicio + 1 << " al nodo " << nodo_final + 1 << " es : "; 
        MostrarCamino(nodo_inicio, nodo_final, predecesor);
        cout << " de longitud " << distancia[nodo_final];
        cout << endl;
      }
    }
  }
}

/// @brief Método que calcula el arco con el coste mínimo
int GRAFO::CosteMinimo() {

  int coste_minimo{};

  for (unsigned nodo_actual{}; nodo_actual < n; nodo_actual++) {

    for (size_t sucesor{}; sucesor < LS[nodo_actual].size(); sucesor++) {

      if (LS[nodo_actual][sucesor].c < coste_minimo) {

        coste_minimo = LS[nodo_actual][sucesor].c;
      }
    }
  }
  
  return coste_minimo;
}

/// @brief Método que dice si hay ciclos de coste negativo o no
bool GRAFO::HayCicloNegativo(vector<int>& distancia, int coste_minimo) {

  bool ciclo_negativo{false};

  for (size_t i {}; (i < distancia.size()) && (!ciclo_negativo); i++) {

    if (distancia[i] < ((static_cast<int>(n)-1) * coste_minimo)) {

      ciclo_negativo = true;
    }
  }

  return ciclo_negativo;
}

/// @brief Método que sirve para mostrar un camino
void MostrarCamino(unsigned nodo_inicio, unsigned nodo_final, vector<unsigned>& predecesor) {

  if (nodo_final != nodo_inicio) {

    MostrarCamino(nodo_inicio, predecesor[nodo_final], predecesor);
    cout << " -> " << nodo_final + 1;
  } else {

    cout << nodo_final + 1;
  }
}

/// @brief Método que calcula el árbol generador de mínimo coste usando prim
void GRAFO::Prim() {

  vector<bool> encontrado(n, false);
  vector<int> coste(n, maxint);
  vector<int> predecesor(n, -1);
  vector<int> nodos{};
  
  int nodo_inicio{};
  int coste_total{};

  // Pedimos un nodo para hacer Prim
  while ((nodo_inicio < 1) || (nodo_inicio > static_cast<int>(n))) {

    cout << "Introduce un nodo de inicio [1, " << n << "]: ";
    cin >> nodo_inicio;
  }

  nodo_inicio--; // Ajustamos a como guardamos nosotros los nodos
  cout << endl;

  coste[nodo_inicio] = 0;
  predecesor[nodo_inicio] = nodo_inicio;
  encontrado[nodo_inicio] = true;
  nodos.push_back(nodo_inicio);

  while (nodos.size() < n) {

    int ultimo_nodo = nodos.back();

    // Actualizamos los costes de los sucesores del último nodo
    for (size_t i{}; i < LS[ultimo_nodo].size(); i++) {

      int coste_nuevo = LS[ultimo_nodo][i].c;
      int nodo_nuevo = LS[ultimo_nodo][i].j;

      if ((coste_nuevo < coste[nodo_nuevo]) && (!encontrado[nodo_nuevo])) {

        coste[nodo_nuevo] = coste_nuevo;
        predecesor[nodo_nuevo] = ultimo_nodo;
      }
    }

    int coste_minimo = maxint;
    int nodo_minimo{};

    // Buscamos cual es el coste mínimo
    for (size_t j{}; j < coste.size(); j++) {

      if ((coste[j] < coste_minimo) && (!encontrado[j])) {

        coste_minimo = coste[j];
        nodo_minimo = j;
      }
    }

    if (coste_minimo == maxint) {

      cout << "El grafo no es conexo" << endl;
      return;
    }

    cout << "Arista (" << predecesor[nodo_minimo] + 1 << ", " << nodo_minimo + 1 << ") con coste " << coste_minimo << " añadida" << endl;

    coste_total += coste_minimo;
    encontrado[nodo_minimo] = true;
    nodos.push_back(nodo_minimo);
  }

  cout << "El coste total del arbol generador de mínimo coste es: " << coste_total << endl;
}

/// @brief Método para destruir un grafo
void GRAFO::destroy() {

	for (unsigned i=0; i< n; i++) {

		LS[i].clear();
		if (dirigido == 1) {

      LP[i].clear();
    }
	}

	LS.clear();
	if (dirigido == 1) {
    
    LP.clear();
  }
}

/// @brief Método para construir un grafo
void GRAFO::build (char nombrefichero[85], int &errorapertura) {

  ElementoLista     dummy;
	ifstream textfile;
	textfile.open(nombrefichero);
	if (textfile.is_open()) {

    errorapertura = 0;

		unsigned i, j, k;
		// leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
		textfile >> (unsigned &) n >> (unsigned &) m >> (unsigned &) dirigido;
		// los nodos internamente se numeran desde 0 a n-1
		// creamos las n listas de sucesores
		LS.resize(n);
    
    // leemos los m arcos
		for (k=0; k<m; k++) {

      // i: Nodo de "origen"
      // j: Nodo de "destino"
      // dummy.c: coste de ir de i a j
			textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
      dummy.j = j-1; // Internamente almacenamos el nodo como nodo-1
      LS[i-1].push_back(dummy); // Y lo guardamos en la posición nodo-1 del vector

      // Aqui vamos a guardar el -1, es decir, si el archivo pone que va del nodo 1 al 3, en nuestro vector estará LS[0]=2

      if (!dirigido && (i != j)) { // Si no es dirigido entonces guardamos la arista en sentido contrario también

        dummy.j = i-1;
        LS[j-1].push_back(dummy);
      }
    }

    if (dirigido) {

      ListaPredecesores();
    }
  } else {

    errorapertura = 1;
  } 
}

/// @brief Destructor de la clase
GRAFO::~GRAFO() {

	destroy();
}

/// @brief Constructor de la clase
GRAFO::GRAFO(char nombrefichero[85], int &errorapertura) {

	build (nombrefichero, errorapertura);
}

/// @brief Método para volver a recargar un nuevo grafo
void GRAFO::actualizar (char nombrefichero[85], int &errorapertura) {

  //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
  destroy();
  //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
  build(nombrefichero, errorapertura);
}

/// @brief Getter de dirigido
unsigned GRAFO::Es_dirigido() {

  return dirigido;
}

/// @brief Método que devuelve la información básica del grafo
void GRAFO::Info_Grafo() {

  if (Es_dirigido()) {

    cout << "Grafo dirigido | nodos " << n << " | arcos " << m;
  } else {

    cout << "Grafo no dirigido | nodos " << n << " | aristas " << m;
  }
}

/// @brief Método para poder mostrar una lista
void Mostrar_Lista(vector<LA_nodo> L) {
  
  ElementoLista aux;

  for (size_t i{}; i < L.size(); i++) {

    cout << "[" << i + 1 << "] : ";

    if (L[i].size() == 0) {

      cout << "null";
    } else {

      for (size_t j{}; j < L[i].size(); j++) {

        aux = L[i][j];
        cout << aux.j + 1 << " : (" << aux.c << ") "; 
      }
    }

    cout << endl;
  }
}

/// @brief Método para mostrar listas
void GRAFO::Mostrar_Listas (int l) {

  if (l == 1) {

    Mostrar_Lista(LS);
  } else if (l == -1) {

    Mostrar_Lista(LP);
  } else {

    Mostrar_Lista(LS);
  }
}

/// @brief Método para generar la lista de predecesores
void GRAFO::ListaPredecesores() {

  ElementoLista aux;
  LP.resize(n);

  for (size_t i{}; i < LS.size(); i++) {
    for (size_t j{}; j < LS[i].size(); j++) {

      aux.c = LS[i][j].c;
      aux.j = i;
      LP[LS[i][j].j].push_back(aux);
    }
  }
}

/// @brief Método que hace un recorrido en profundidad para calcular las componentes conexas
void GRAFO::dfs_cc(unsigned i, vector<bool> &visitado) {
  
  visitado[i] = true;
  cout << i+1;

  for (unsigned j{}; j < LS[i].size(); j++) {

    if (!visitado[LS[i][j].j]) {

      cout << ", ";
      dfs_cc(LS[i][j].j, visitado);
    }
  }

  if (dirigido == 1) {

    for (unsigned j{}; j < LP[i].size(); j++) {

      if (!visitado[LP[i][j].j]) {

        cout << ", ";
        dfs_cc(LP[i][j].j, visitado);
      }
    }
  }
}

/// @brief Método que calcula las componentes conexas
void GRAFO::ComponentesConexas() {

  unsigned componentesconexas{};
  vector<bool> visitado{};
  visitado.resize(n,false);

  for (unsigned i{}; i < n; i++) {

    if (!visitado[i]) {

      componentesconexas++;
      cout << "Componente conexa " << componentesconexas << " : {";

      dfs_cc(i,visitado);
      cout << "}" << endl;
    }
  }

  if (componentesconexas > 1) {

    cout << "El grafo NO es conexo" << endl;
  } else if (componentesconexas == 1) {

    cout << "El grafo es conexo" << endl;
  }
}

/// @brief Método que hace un recorrido en profundidad para calcular las componentes fuertemente conexas
void GRAFO::dfs_cfc(unsigned i, vector<bool> &visitado) {

  visitado[i] = true;
  cout << i + 1;

  for (unsigned j{}; j < LP[i].size();j++) {

    if (!visitado[LP[i][j].j]) {

      cout << ", ";
      dfs_cfc(LP[i][j].j,visitado);
    }
  }
}

/// @brief Método que hace un recorrido en profundidad para calcular el postnum
void GRAFO::dfs_postnum(unsigned i, vector<bool> &visitado, vector<unsigned> &postnum, unsigned &postnum_ind) {

  visitado[i] = true;
  
  for (unsigned j{}; j < LS[i].size(); j++) {

    if (!visitado[LS[i][j].j]) {

      dfs_postnum(LS[i][j].j, visitado, postnum, postnum_ind);
    }
  }

  postnum[postnum_ind--] = i; // Rellenamos el postnum (que se va rellenando a medida que visitamos los vectores) al revés de como lo hacemos en clase
}

/// @brief Método que calcula las componentes fuertemente conexas
void GRAFO::ComponentesFuertementeConexas() {

  unsigned postnum_ind{}, componentesfuertementeconexas{};
  vector<bool> visitado;
  vector<unsigned> postnum;

  visitado.resize(n,false);
  postnum.resize(n,UERROR);
  postnum_ind = n-1;

  // Recorrido uno
  for (unsigned i{}; i < n; i++) {

    if (!visitado[i]) {

      dfs_postnum(i,visitado,postnum,postnum_ind);
    }
  }

  // Reiniciamos el vector de visitados
  for (unsigned i{}; i < n; i++) {

    visitado[i] = false;
  }

  // Hacemos otro recorrido en profundidad pero en el orden inverso de postnum
  // Pero como ya hemos invertido el postnum en el método dfs_postnum entonces lo recorremos normal
  for (unsigned i{}; i < n; i++) {

    if (!visitado[postnum[i]]) {

      componentesfuertementeconexas++;
      cout << "componente Fuertemente Conexa " << componentesfuertementeconexas << ": {";
      dfs_cfc(postnum[i],visitado);

      cout << "}" << endl;
    }
  }

  if (componentesfuertementeconexas > 1) {

    cout << "El grafo NO es fuertemente conexo" << endl;
  } else if (componentesfuertementeconexas == 1) {

    cout << "El grafo es fuertermente conexo" << endl;
  }
}