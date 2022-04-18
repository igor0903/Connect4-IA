#include <iostream>

using namespace std;

int jogadas = 0;
int verific = 0;

typedef struct node{
  char tabu[6][7];
  int util;
  struct node *filhos[7];
  struct node *ant;
} *Node;

Node des(){
  Node aux = (Node)malloc(sizeof(struct node));
  for(int i=0; i<6; i++){
    for(int j=0; j<7; j++)
      aux->tabu[i][j] = '-';
  }

  return aux;
}

int pontuacao(int x, int o){
  if(x == 4){
    return 512;
  }
  if(o == 4){
    return -512;
  }
  if(x > 0 && o > 0){
    return 0;
  }
  if(x == 1){
    return 1;
  }
  if(x == 2){
    return 10;
  }
  if(x == 3){
    return 50;
  }
  if(o == 1){
    return -1;
  }
  if(o == 2){
    return -10;
  }
  if(o == 3){
    return -50;
  }
  return 0;
}

void printt(Node n){
  system("clear||cls");
  for(int i=0; i<6; i++){
    for(int j=0; j<7; j++)
      printf("%c ", n->tabu[i][j]);   
    printf("\n");
  }
}

int verutil(Node n){
  int util = 0;
  int nO;
  int nX;
  nO = 0;
  nX = 0;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 7; j++){
      for(int k = 0; k < 4; k++){
        if(n->tabu[i+k][j] == 'O')
          nO++;
        else if(n->tabu[i+k][j] == 'X')
          nX++;
      }
      if(pontuacao(nX,nO) == 512 || pontuacao(nX,nO) == -512){
        return pontuacao(nX,nO);
      }
      util += pontuacao(nX,nO);
      nO = 0;
      nX = 0;
    }
  }
  return util;
}

int horutil(Node n){
  int util = 0;
  int nO;
  int nX;
  nO = 0;
  nX = 0;
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 4; j++){
      for(int k = 0; k < 4; k++){
        if(n->tabu[i][j+k] == 'O')
          nO++;
        else if(n->tabu[i][j+k] == 'X')
          nX++;
      }
      if(pontuacao(nX,nO) == 512 || pontuacao(nX,nO) == -512){
        return pontuacao(nX,nO);
      }
      util += pontuacao(nX,nO);
      nO = 0;
      nX = 0;
    }
  }
  return util;
}

int diagMainUtil(Node n){
  int util = 0;
  int nO = 0;
  int nX = 0;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 4; j++){
      for(int a = 0 ; a < 4; a++){
        if(n->tabu[i+a][j+a] == 'O'){
          nO++;
        }
        else if(n->tabu[i+a][j+a] == 'X'){
          nX++;
        }
      }
      if(pontuacao(nX,nO) == 512 || pontuacao(nX,nO) == -512){
        return pontuacao(nX,nO);
        }
        util += pontuacao(nX,nO);
        nO = 0;
        nX = 0;
    }
  }
  return util;
}

int antiDiagUtil(Node n){
  int util = 0;
  int nO = 0;
  int nX = 0;
  for(int i = 0; i < 3; i++){
    for(int j = 3; j < 7; j++){
      for(int k = 0; k < 4; k++){
        if(n->tabu[i+k][j-k] == 'O'){
          nO++;
        }
        else if(n->tabu[i+k][j-k] == 'X'){
          nX++;
        }
      }
      if(pontuacao(nX,nO) == 512 || pontuacao(nX,nO) == -512){
          return pontuacao(nX,nO);
        }
        util += pontuacao(nX,nO);
        nO = 0;
        nX = 0;
    }
  }
  return util;
}

int horver(int linha, int col, Node n){ //VERIFICA SE HA 4 IGUAIS NA HORIZONTAL
  int coltemp = col;
  int lintemp = linha;
  int serie = 1;
  int flag = 1;
  while(coltemp < 6 && flag == 1){
    coltemp++;
    if(n->tabu[lintemp][coltemp] == n->tabu[linha][col])
      serie++;
    else
      flag = 0;
  }
  flag = 1;
  coltemp = col;
  lintemp = linha;
  while(coltemp > 0 && flag == 1){
    coltemp--;
    if(n->tabu[lintemp][coltemp] == n->tabu[linha][col])
      serie++;
    else
      flag = 0;
  }
  if(serie >= 4)
    return 1;
  else
    return 0;
}

int vertver(int linha, int col, Node n){ //VERIFICA SE HA 4 IGUAIS NA VERTICAL
  int coltemp = col;
  int lintemp = linha;
  int serie = 1;
  int flag = 1;
  while(lintemp < 5 && flag == 1){
    lintemp++;
    if(n->tabu[lintemp][coltemp] == n->tabu[linha][col])
      serie++;
    else
      flag = 0;
  }
  flag = 1;
  coltemp = col;
    lintemp = linha;
    while(lintemp > 0 && flag == 1){
      lintemp--;
      if(n->tabu[lintemp][coltemp] == n->tabu[linha][col])
	serie++;
      else
	flag = 0;
    }
    if(serie >= 4)
      return 1;
    else
      return 0;
  }

int diag1ver(int linha, int col, Node n){ //VERIFICA SE HA 4 IGUAIS NA DIAGONAL 1
  int coltemp = col;
  int lintemp = linha;
  int serie = 1;
    int flag = 1;
    while(lintemp > 0 && coltemp < 6 && flag == 1){
      lintemp--;
      coltemp++;
      if(n->tabu[lintemp][coltemp] == n->tabu[linha][col])
	serie++;
      else
	flag = 0;
    }
    flag = 1;
    coltemp = col;
    lintemp = linha;
    while(lintemp < 5 && coltemp > 0 && flag == 1){
      lintemp++;
      coltemp--;
      if(n->tabu[lintemp][coltemp] == n->tabu[linha][col])
	serie++;
      else
	flag = 0;
    }
    if(serie >= 4)
      return 1;
    else
      return 0;
}

int diag2ver(int linha, int col, Node n){  //VERIFICA SE HA 4 IGUAIS NA DIAGONAL 2
    int coltemp = col;
    int lintemp = linha;
    int serie = 1;
    int flag = 1;
    while(lintemp > 0 && coltemp > 0 && flag == 1){
      lintemp--;
      coltemp--;
      if(n->tabu[lintemp][coltemp] == n->tabu[linha][col]){
	      serie++;
      }
      else{
	      flag = 0;
      }
    }
    flag = 1;
    coltemp = col;
    lintemp = linha;
    while(lintemp < 5 && coltemp < 6 && flag == 1){
      lintemp++;
      coltemp++;
      if(n->tabu[lintemp][coltemp] == n->tabu[linha][col])
	serie++;
      else
	flag = 0;
    }
    if(serie >= 4)
      return 1;
    else
      return 0;
}
      
void verif(int linha, int col, Node n){

  int ver1 = horver(linha, col, n);
  int ver2 = vertver(linha, col, n);
  int ver3 = diag1ver(linha,col, n);
  int ver4 = diag2ver(linha,col, n);
    printf("verHor:%d verVertical:%d verDiag1:%d verDiag2:%d\n", ver1, ver2, ver3, ver4);
    if(ver1 == 1 || ver2 == 1 || ver3 == 1 || ver4 == 1)
      verific = 1;
    else if(jogadas == 42)
      verific = -1;
}

void input(char c, int col, Node n){
  int linha = 5;
  while(n->tabu[linha][col] != '-') // procura o proximo lugar livre da coluna
    linha--;
  
  n->tabu[linha][col] = c;
  printt(n);
  verif(linha, col, n);
}



int main(int argc, char **argv){

  Node tab1 = des();
  printt(tab1);

  //int i=0;
  int jog;
  int vez = 1;
  while(jogadas < 42 && verific == 0){
    if(vez == 1){
      cout << "Jogador 1 (X)" << endl; // endl = \n
      cin >> jog;
      jogadas++;
      input('X', jog-1, tab1);
      printf("Score Colunas: %d\n", horutil(tab1));
      printf("Score Linhas: %d\n", verutil(tab1));
      printf("Score diagonal 1: %d\n", diagMainUtil(tab1));
      printf("Score diagonal 2: %d\n", antiDiagUtil(tab1));
    }
    if(vez == 2){
      cout << "Jogador 2 (O)" << endl;
      cin >> jog;
      jogadas++;
      input('O', jog-1, tab1);
      printf("Score Colunas: %d\n", horutil(tab1));
      printf("Score Linhas: %d\n", verutil(tab1));
      printf("Score diagonal 1: %d\n", diagMainUtil(tab1));
      printf("Score diagonal 2: %d\n", antiDiagUtil(tab1));
    }
    if(vez == 2)
      vez = 1;
    else
      vez = 2;
    printf("jogadas:%d\n", jogadas);
  }
  
  if(verific == -1)
    printf("Empate\n");
  else{
    if(jogadas%2 == 0)
      printf("Jogador 2 ganhou\n");
    else
      printf("Jogador 1 ganhou\n");
  }

  return 0;
}
