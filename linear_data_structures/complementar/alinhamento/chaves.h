// Copyright [2022] <COLOQUE SEU NOME AQUI...>
#include <string>
#include "./array_stack.h"
using namespace std;

bool verificaChaves(std::string trecho_programa) {
  int tamanho = trecho_programa.length();
  structures::ArrayStack < char > pilha(500);

  for (int i = 0; i < tamanho; i++) {
    // condições de parada dor 'for' podem ser adicionadas...
    switch (trecho_programa[i]) {
    case '{':
      pilha.push('{');
      break;
    case '[':
      pilha.push('[');
      break;
    case '(':
      pilha.push('(');
      break;
    case '}':
      if (pilha.empty() || pilha.pop() != '{') {
        return false;
      }
      break;
    case ']':
      if (pilha.empty() || pilha.pop() != '[') {
        return false;
      }
      break;
    case ')':
      if (pilha.empty() || pilha.pop() != '(') {
        return false;
      }
      break;
    }
  }
  if (pilha.empty()) {
    return true;
  }
  return false;
}
