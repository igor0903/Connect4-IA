#include <iostream>
#include<algorithm>
#include<cstdlib>
#include<ctime>

using namespace std;

int coluna = -1;
int jogadas = 0;
int verific = 0;
int verific_interno = 0;
int numerodenos = 0;

typedef struct node{
  char tabu[6][7];
  int util;
  struct node *filhos[7];
  struct node *ant;
} *Node;

bool input(char c, int col, Node n);
void input_interno(char c, int col, Node n);
int minimize(Node n, int depth, bool c);
int maximize(Node n, int depth, bool c);

Node des(){
  Node aux = (Node)malloc(sizeof(struct node));
  for(int i=0; i<6; i++){
    for(int j=0; j<7; j++)
      aux->tabu[i][j] = '-';
  }

  return aux;
}

Node mknode(Node n, int col, char c){
  numerodenos++;
  Node aux = (Node)malloc(sizeof(struct node));
  
  for(int i=0; i<6; i++){
    for(int j=0; j<7; j++)
      aux->tabu[i][j] = n->tabu[i][j];
  }

  input_interno(c,col,aux);
  //aux->util = utility(aux);
  aux->ant = n;
  return aux;
}

bool valid_locations(Node n, int col){
  bool localtion[7];
  for(int i = 0; i < 7; i++){
    if(n->tabu[0][i] == '-'){
      localtion[i] = true;
    }
    else{
      localtion[i] = false;
    }
  }
  if(localtion[col] == true){
    return true;
  }
  else{
    return false;
  }
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

int utility(Node n){
  int soma = 0;
  if(verutil(n) == 512 || horutil(n) == 512 || diagMainUtil(n) == 512 || antiDiagUtil(n) == 512){
    return 512;
  }
  else if(verutil(n) == -512 || horutil(n) == -512 || diagMainUtil(n) == -512 || antiDiagUtil(n) == -512){
    return -512;
  }
  else{
    soma += verutil(n);
    soma += horutil(n);
    soma += diagMainUtil(n);
    soma += antiDiagUtil(n);
  return soma;
  }
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
    //printf("verHor:%d verVertical:%d verDiag1:%d verDiag2:%d\n", ver1, ver2, ver3, ver4);
    if(ver1 == 1 || ver2 == 1 || ver3 == 1 || ver4 == 1)
      verific = 1;
    else if(jogadas == 42)
      verific = -1;
}

void verif_interno(int linha, int col, Node n){

  int ver1 = horver(linha, col, n);
  int ver2 = vertver(linha, col, n);
  int ver3 = diag1ver(linha,col, n);
  int ver4 = diag2ver(linha,col, n);
    //printf("verHor:%d verVertical:%d verDiag1:%d verDiag2:%d\n", ver1, ver2, ver3, ver4);
    if(ver1 == 1 || ver2 == 1 || ver3 == 1 || ver4 == 1)
      verific_interno = 1;
    else if(jogadas == 42)
      verific_interno = -1;
}

bool input(char c, int col, Node n){
  if(valid_locations(n, col)){
    int linha = 5;
    while(n->tabu[linha][col] != '-'){ // procura o proximo lugar livre da coluna
      linha--;
    }
    n->tabu[linha][col] = c;
    printt(n);
    verif(linha, col, n);
    return true;
  }
  else{
    cout << "lugar invalido" << endl;
    return false;
  }

}

void input_interno(char c, int col, Node n){
  int linha = 5;
  while(n->tabu[linha][col] != '-'){ // procura o proximo lugar livre da coluna
    linha--;
  }
  n->tabu[linha][col] = c;
  //verif(linha, col, n);
}

void input2(char c, int col, Node n){
  int linha = 5;
  while(n->tabu[linha][col] != '-'){ // procura o proximo lugar livre da coluna
    linha--;
  }
  n->tabu[linha][col] = c;
  printt(n);
  verif(linha, col, n);
}

int minimax(Node n, int depth, bool c){
  int value;
  int new_score;
  value = -99999999;
  for(int i = 0; i < 7; i++){
    if(valid_locations(n, i)){
      n->filhos[i] = mknode(n, i, 'X');
      new_score = maximize(n->filhos[i], depth -1, false);
      if(new_score > value){
        value = new_score;
        coluna = i;
      }
    }
  }
  return coluna;
}
int maximize(Node n, int depth, bool c){
  int value;
  int new_score;
  verif_interno(6,7,n);
  if(depth == 0 || verific_interno == 1 || verific_interno == -1){
    return utility(n);
  } //MAXIMIZAR O JOGADOR X
  value = -99999999;
  for(int i = 0; i < 7; i++){
    if(valid_locations(n, i)){
      n->filhos[i] = mknode(n, i, 'X');
      new_score = minimize(n->filhos[i], depth -1, false);
      if(new_score > value){
        value = new_score;
      }
    }
  }
  return value;
}

int minimize(Node n, int depth, bool c){
  int value;
  int new_score;
  verif_interno(6,7,n);
  if(depth == 0 || verific_interno == 1 || verific_interno == -1){
    return utility(n);
  }
  else{
    value = 99999999;
    for(int i = 0; i < 7; i++){
      if(valid_locations(n, i)){
        n->filhos[i] = mknode(n, i, 'O');
        new_score = maximize(n->filhos[i], depth -1, true);
        if(new_score < value){
          value = new_score;
        }
      }
    }
    return value;
  }
}


int main(int argc, char **argv){

  Node tab1 = des();
  printt(tab1);

  //int random = 0;
  //int i=0;
  int jog;
  int vez = 1;
  while(jogadas < 42 && verific == 0){
    if(vez == 1){
      //cin >> jog;
      jog = minimax(tab1, 3, true); //profundidade 3 ja apresentar um bom nivel de resposta da IA para equilibrar tempo e qualidade da resposta
      cout << jog << endl;
      jogadas++;
      input2('X', jog, tab1);
      verif(6,7,tab1);
      printf("Score Colunas: %d\n", horutil(tab1));
      printf("Score Linhas: %d\n", verutil(tab1));
      printf("Score diagonal 1: %d\n", diagMainUtil(tab1));
      printf("Score diagonal 2: %d\n", antiDiagUtil(tab1));
      cout<<"Utilty: " << utility(tab1) << endl;
    }
    if(vez == 2){
      cout << "Sua vez, Jogador (O)" << endl;
      //srand (time(NULL));
      //random=rand() % 7 + 1; //number entre 1 e 7
      //jog = minimax(tab1);
      cin >> jog;
      jogadas++;
      while(!input('O', jog-1, tab1)){
        cin >> jog;
      }
      verif(6,7,tab1);
      printf("Score Colunas: %d\n", horutil(tab1));
      printf("Score Linhas: %d\n", verutil(tab1));
      printf("Score diagonal 1: %d\n", diagMainUtil(tab1));
      printf("Score diagonal 2: %d\n", antiDiagUtil(tab1));
      cout<<"Utilty: " << utility(tab1) << endl;
      //cout<<"minimax: " << minimax(tab1) << endl;
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
       printf("Jogador ganhou\n");
     else
       printf("AI ganhou\n");
    }
  return 0;
}
