#include <stdio.h>
#include <stdlib.h>

typedef struct No {
  int valor;
  struct No *esquerda;
  struct No *direita;
} No;

No *criar_no(int valor) {
  No *novo_no = (No *)malloc(sizeof(No));
  novo_no->esquerda = NULL;
  novo_no->direita = NULL;
  novo_no->valor = valor;
  return novo_no;
}

No *inserir(int valor, No *raiz) {
  if (raiz == NULL) {
    raiz = criar_no(valor);
    return raiz;
  } else {
    if (valor > raiz->valor) {
      raiz->direita = inserir(valor, raiz->direita);
    } else {
      raiz->esquerda = inserir(valor, raiz->esquerda);
    }
  }
  return raiz;
}

No *buscar(int valor, No *raiz) {
  if (valor == raiz->valor || raiz == NULL) {
    return raiz;
  }
  if (valor > raiz->valor) {
    return buscar(valor, raiz->direita);
  }
  return buscar(valor, raiz->esquerda);
}

No *destruir(int valor, No *raiz) {
  if (raiz == NULL) {
    return raiz;
  }
  if (valor > raiz->valor) {
    raiz->direita = destruir(valor, raiz->direita);
  } else if (valor < raiz->valor) {
    raiz->esquerda = destruir(valor, raiz->esquerda);
  } else {
    if (raiz->esquerda == NULL) {
      No *aux = raiz->direita;
      free(raiz);
      return aux;
    } else if (raiz->direita == NULL) {
      No *aux = raiz->esquerda;
      free(raiz);
      return aux;
    }
    No *filho = raiz->direita;
    No *pai = raiz;
    while (filho->esquerda != NULL) {
      pai = filho;
      filho = filho->esquerda;
    }
    raiz->valor = filho->valor;
    if (pai != raiz) {
      pai->esquerda = filho->direita;
    } else {
      pai->direita = filho->direita;
    }
    free(filho);
  }
  return raiz;
}

void mostrarEmOrdem(No *raiz) {
  if (raiz != NULL) {
    mostrarEmOrdem(raiz->esquerda);
    printf("%d ", raiz->valor);
    mostrarEmOrdem(raiz->direita);
  }
}

int main(void) {

  No *raiz = inserir(8, NULL);

  inserir(3, raiz);
  inserir(10, raiz);
  inserir(6, raiz);
  inserir(1, raiz);
  inserir(14, raiz);
  inserir(4, raiz);
  inserir(7, raiz);
  inserir(13, raiz);

  mostrarEmOrdem(raiz);

  printf("\n");
  printf("%d", buscar(6, raiz)->valor);

  destruir(6, raiz);

  printf("\n");
  mostrarEmOrdem(raiz);
  return 0;
}