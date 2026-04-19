// Copyright 2025 NNTU-CS
#include <string>
#include <map>
#include "tstack.h"

std::string infx2pstfx(const std::string& infix) {
  std::map<char, int> weight = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2}
  };
  TStack<char, 100> operators;
  std::string postfix;
  size_t i = 0;

  while (i < infix.size()) {
    char symbol = infix[i];

    if (symbol >= '0' && symbol <= '9') {
      while (i < infix.size() && infix[i] >= '0' && infix[i] <= '9')
        postfix += infix[i++];
      postfix += ' ';
      continue;
    }
    if (symbol == '(') {
      operators.add(symbol);
    } else if (symbol == ')') {
      while (!operators.isVacant() && operators.peek() != '(') {
        postfix += operators.peek();
        postfix += ' ';
        operators.remove();
      }
      if (!operators.isVacant())
        operators.remove();
    } else if (weight.find(symbol) != weight.end()) {
      while (!operators.isVacant() && operators.peek() != '(' &&
             weight[operators.peek()] >= weight[symbol]) {
        postfix += operators.peek();
        postfix += ' ';
        operators.remove();
      }
      operators.add(symbol);
    }
    ++i;
  }

  while (!operators.isVacant()) {
    postfix += operators.peek();
    postfix += ' ';
    operators.remove();
  }

  if (!postfix.empty() && postfix.back() == ' ')
    postfix.pop_back();
  return postfix;
}

int eval(const std::string& postfixStr) {
  TStack<int, 100> numbers;
  size_t i = 0;

  while (i < postfixStr.size()) {
    if (postfixStr[i] == ' ') {
      ++i;
      continue;
    }
    if (postfixStr[i] >= '0' && postfixStr[i] <= '9') {
      int x = 0;
      while (i < postfixStr.size() && postfixStr[i] >= '0' && postfixStr[i] <= '9') {
        x = x * 10 + (postfixStr[i] - '0');
        ++i;
      }
      numbers.add(x);
      continue;
    } else {
      int rOp = numbers.peek();
      numbers.remove();
      int lOp = numbers.peek();
      numbers.remove();
      switch (postfixStr[i]) {
        case '+': numbers.add(lOp + rOp); break;
        case '-': numbers.add(lOp - rOp); break;
        case '*': numbers.add(lOp * rOp); break;
        case '/': numbers.add(lOp / rOp); break;
      }
      ++i;
    }
  }
  return numbers.peek();
}
