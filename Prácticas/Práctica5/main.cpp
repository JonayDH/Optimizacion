/**
  * Universidad de La Laguna
  * Escuela Superior de Ingeniería y Tecnología
  * Grado en Ingeniería Informática
  * Optimización 2025-2026
  *
  * @file main.cpp
  * @author Jonay Déniz Hernández  alu0101791623@ull.edu.es
  * @date May 7 2026
  * @brief Programa principal
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

#include <string.h>
#include "grafo.h"

void pressanykey() {

  char c;
  //system("pause"); s�lo en windows
  cout << endl;
  cout << "pulsa [c] para continuar: ";
  cin >> c;
}

void menu (unsigned dirigido, char &opcion) {
//Expresion del menu de opciones segun sea un grafo dirigido o no dirigido

  cout << "Optimización en Grafos, 2025-2026 Jonay Déniz Hernández" << endl;
  cout << "c. [c]argar grafo desde fichero" << endl;
  if (dirigido == 0) { //Grafo no dirigido

    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
    cout << "a. Mostrar la lista de [a]dyacencia del grafo" << endl;
    cout << "o. Mostrar c[o]mponentes conexas del grafo" << endl;
    cout << "r. Algoritmo de P[r]im para determinar el árbol generado de mínimo peso" << endl;
	  //Aqu� se a�aden m�s opciones al men� del grafo no dirigido
  } else {

    cout << "i. Mostrar [i]nformacion basica del grafo" << endl;
    cout << "s. Mostrar la lista de [s]ucesores del grafo" << endl;
    cout << "p. Mostrar la lista de [p]redecesores del grafo" << endl;
    cout << "o. Mostrar c[o]mponentes fuertemente conexas del grafo" << endl;
    cout << "t. Algoritmo [T]WOQ para los caminos mínimos desde un nodo s"<< endl;
	  //Aqu� se a�aden m�s opciones al men� del grafo dirigido
  }

  cout << "q. Finalizar el programa" << endl;
  cout << "Introduce la letra de la accion a ejecutar  > ";
  cin >> opcion;
};


// El principal es simplemente un gestor de menu, diferenciando acciones para dirigido y para no dirigido, y un men� inicial si no hay un grafo cargado
int main(int argc, char *argv[]) {

  int error_apertura;
  char nombrefichero[85], opcion;
  clrscr();
  //Si tenemos el nombre del primer fichero por argumento, es una excepcion, y lo intentamos cargar, si no, lo pedimos desde teclado
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

    cout<< "Grafo cargado desde el fichero " << nombrefichero << endl;
    pressanykey();
    clrscr();

    do {

      menu(G.Es_dirigido(), opcion);
      switch (opcion) {

        case 't':

          clrscr();

          if (G.Es_dirigido() == false) {

            cout << "No puede ejecutar esta opción con este tipo de grafo" << endl;
          } else {

            G.TWOQ();
          }

          pressanykey();
          clrscr();
          break;

        case 'r':

          clrscr();

          if(G.Es_dirigido()) {

            cout << "No puedes ejecutar esta opción con este tipo de grafo" << endl;
          } else {

            G.Prim();
          }

          pressanykey();
          clrscr();
          break;

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

          if (G.Es_dirigido()) {

            cout << "Nodos de la lista de sucesores " << endl;
            G.Mostrar_Listas(1);

          } else {

            cout << "No existe tal lista en el grafo actual" << endl;
          }

          pressanykey();
          clrscr();
          break;

        case 'p':

          clrscr();

          if (G.Es_dirigido()) {

            cout << "Nodos de la lista de predecesores " << endl;
            G.Mostrar_Listas(-1);

          } else {

            cout << "No existe tal lista en el grafo actual" << endl;
          }

          pressanykey();
          clrscr();
          break;
        
        case 'a':

          clrscr();

          if (G.Es_dirigido()) {

            cout << "No existe tal lista en el grafo actual " << endl;

          } else {

            cout << "Nodos de la lista de adyacentes" << endl;
            G.Mostrar_Listas(0);
          }

          pressanykey();
          clrscr();
          break;

        case 'o':

          clrscr();

          if (G.Es_dirigido()) {

            cout << "Nodos de las componentes fuertemente conexas:" << endl;
            G.ComponentesFuertementeConexas();

          } else {

            cout << "Nodos de las componentes conexas:" << endl;
            G.ComponentesConexas();
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

