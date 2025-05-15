#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

/*
  Función is_valid(Node* n) :
  Esta función se encarga de revisar que el nodo recibido sea válido según las reglas del sudoku
  
  Ningún número del 1 al 9 se repite :
  - En ninguna fila
  - En ninguna columna
  - En ningún subcuadro 3x3
  
  La función retorna 0 en caso de que no cumpla, retorna 1 en caso de que cumpla.
*/

int is_valid(Node* n){
  
  // Para cada condición, se crea un arreglo que verifica la existencia única de un número
  // Si no ha sido leído, es 0, si ya se leyó, es 1.
  // Por lo tanto, ningún número que tenga en su posición el 1, debería volver a leerse.
  
  // Verificación por filas
  for (int i = 0 ; i < 9 ; i++){
    int verificados[9] = {0};
    
    for (int j = 0 ; j < 9 ; j++){
      int val = n->sudo[i][j];
      if (val == 0) continue;
      
      if (verificados[val - 1] == 0)
        verificados[val - 1] = 1;
      else return 0;
    }
  }

  // Verificación por columnas
  for (int i = 0 ; i < 9 ; i++){
    int verificados[9] = {0};
    
    for (int j = 0 ; j < 9 ; j++){
      int val = n->sudo[j][i];
      if (val == 0) continue;
      
      if (verificados[val - 1] == 0)
        verificados[val - 1] = 1;
      else return 0;
    }
  }
  
  // Verificación por subcuadros 3x3
  for (int boxRow = 0; boxRow < 3; boxRow++) {
    for (int boxCol = 0; boxCol < 3; boxCol++) {
      int verificados[9] = {0};
        for (int i = 0; i < 3; i++) {
          for (int j = 0; j < 3; j++) {
            int row = boxRow * 3 + i;
            int col = boxCol * 3 + j;
            int val = n->sudo[row][col];
            if (val == 0) continue;
            if (verificados[val - 1] == 0) verificados[val - 1] = 1;
            else return 0;
          }
        }
    }
  }

  // El sudoku es válido.
  return 1;
}

/*
  Función get_adj_nodes(Node* n) :
  Crea una lista de nodos adyacentes al estado de un nodo, busca la primera posición vacía del
  tablero, si la encuentra, retorna una lista con todos los nodos de los posibles estados de esa posición vacía.
  En caso de no encontrar una posición vacía, se retorna la lista vacía.
*/

List* get_adj_nodes(Node* n)  {
    List* adjacentNodes = createList();
    
    // Posiciones x e y de la primera posición vacía.
    int x, y;
    int Flag = 1;

    //Buscar la primera posición vacía para retornar los posibles estados de este.
    for (int i = 0 ; i < 9 && Flag != 0 ; i++){
      for (int j = 0 ; j < 9 && Flag != 0 ; j++){
        if (n->sudo[i][j] == 0) {
          x = i; y = j;  // Guardar la primera posición vacía del sudoku
          Flag = 0;
        }
      }
    }
    
    // Si no tiene posición vacía se retorna la lista vacía.
    if (Flag) return adjacentNodes;
    
    // Se guardan todos los estados posibles.
    for (int i = 0 ; i < 9 ; i++){
      Node* possibleNode = copy(n);
      possibleNode->sudo[x][y] = i + 1;
      if (is_valid(possibleNode)) pushBack(adjacentNodes, possibleNode);
    }
    
    // Se retorna la lista.
    return adjacentNodes;
}

/*
  Función is_final(Node* n) :
  Esta función comprueba si no quedan espacios vacíos en un tablero de sudoku,
  lo que indicaría que este está completo.
*/

int is_final(Node* n){
  // recorrer toda la matriz
  for (int i = 0 ; i < 9 ; i++){
    for (int j = 0 ; j < 9 ; j++){
      if (n->sudo[i][j] == 0) return 0;
    }
  }
  // la matriz no tiene espacios vacíos
  return 1;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/