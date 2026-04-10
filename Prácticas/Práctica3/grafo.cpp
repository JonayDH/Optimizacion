/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Optimización 2025-2026
  *
  * @file grafo.cpp
  * @author Jonay Déniz Hernández  alu0101791623@ull.edu.es
  * @date March 28 2026
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
		for (k=0;k<m;k++) {

			textfile >> (unsigned &) i  >> (unsigned &) j >> (int &) dummy.c;
			//damos los valores a dummy.j y dummy.c
			//situamos en la posici�n del nodo i a dummy mediante push_back
			//pendiente de hacer un segundo push_back si es no dirigido. O no.
			//pendiente la construcci�n de LP, si es dirigido
			//pendiente del valor a devolver en errorapertura
      dummy.j = j-1;
      LS[i-1].push_back(dummy);

      if (!dirigido && (i != j)) {

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

GRAFO::~GRAFO() {

	destroy();
}

GRAFO::GRAFO(char nombrefichero[85], int &errorapertura) {

	build (nombrefichero, errorapertura);
}

void GRAFO::actualizar (char nombrefichero[85], int &errorapertura) {

  //Limpiamos la memoria dinamica asumida en la carga previa, como el destructor
  destroy();
  //Leemos del fichero y actualizamos G con nuevas LS y, en su caso, LP
  build(nombrefichero, errorapertura);
}

unsigned GRAFO::Es_dirigido() {

  return dirigido;
}

void GRAFO::Info_Grafo() {

  if (Es_dirigido()) {

    cout << "Grafo dirigido | nodos " << n << " | arcos " << m;
  } else {

    cout << "Grafo no dirigido | nodos " << n << " | aristas " << m;
  }
}

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

void GRAFO::Mostrar_Listas (int l) {

  if (l == 1) {

    Mostrar_Lista(LS);
  } else if (l == -1) {

    Mostrar_Lista(LP);
  } else {

    Mostrar_Lista(LS);
  }
}

void GRAFO::ListaPredecesores() { //Recorre la lista de sucesores LS para construir la de predecesores, LP

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

void GRAFO::dfs_cc(unsigned i, vector<bool> &visitado) { //Este recorrido esta� hecho adhoc para mostrar el ritmo de nodos visitados, para su uso en la construccion de Componentes Conexas
  
  visitado[i] = true;
  cout << i+1;

  for (unsigned j{}; j < LS[i].size(); j++) {

    if (!visitado[LS[i][j].j]) {

      cout << ", ";
      dfs_cc(LS[i][j].j);
    }
  }
}

void GRAFO::ComponentesConexas() {

  unsigned i{}, componentesconexas{};
  vector<bool> visitado{};
  visitado.resize(n,false);

  for (unsigned i{}; i < n; i++) {

    if (!visitado[i]) {

      componentesconexas++;
      cout << "componente Conexa" << componentesconexas << "{:";

      dfs_cc(i,visitado);
    }
    
    i++;
  }
}

void GRAFO::dfs_cfc(unsigned i, vector<bool> &visitado) { //Este recorrido esta� hecho adhoc para mostrar el ritmo de nodos visitados, para su uso en la construccion de Componentes fuertemente Conexas

  visitado[i] = true;
  cout << i + 1 << " ";

  for (unsigned j{}; j < LP[i].size();j++) {

    if (!visitado[LP[i][j].j]) {

      dfs_cfc(LS[i][j].j,visitado);
    }
  }
}

void GRAFO::dfs_postnum(unsigned i, vector<bool> &visitado, vector<unsigned> &postnum, unsigned &postnum_ind) { //Este recorrido esta� hecho adhoc para calcular el orden postnumeraci�n de los nodos

  visitado[i] = true;
  
  for (unsigned j{}; j < LS[i].size(); j++) {

    if (!visitado[LS[i][j].j]) {

      dfs_postnum(LS[i][j].j, visitado, postnum, postnum_ind);
    }
  }

  postnum[postnum_ind--] = i;
}

void GRAFO::ComponentesFuertementeConexas() {

  unsigned i{}, postnum_ind{}, componentesfuertementeconexas{};
  vector<bool> visitado;
  vector<unsigned> postnum;

  visitado.resize(n,false);
  postnum.resize(n,UERROR);
  postnum_ind = n-1;

  for (unsigned i{}; i < n; i++) {

    if (!visitado[i]) {

      dfs_postnum(i,visitado,postnum,postnum_ind);
    }
  }

  visitado.resize(n,false);

  i = 0;

  for (unsigned i{}; i < n; i++) {

    if (!visitado[postnum[i]]) {

      componentesfuertementeconexas++;
      cout << "componente Fuertemente Conexa" << componentesfuertementeconexas << ":{";
      dfc_cfc(postnum[i],visitado);
    }
  }
}

