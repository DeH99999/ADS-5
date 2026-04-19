// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int Capacity>
class TStack {
 private:
  T buffer[Capacity];
  int topIndex;

 public:
  TStack() : topIndex(-1) {}

  void add(const T& item) {
    if (topIndex < Capacity - 1)
      buffer[++topIndex] = item;
  }

  void remove() {
    if (topIndex >= 0)
      --topIndex;
  }

  T peek() const {
    return buffer[topIndex];
  }

  bool isVacant() const {
    return topIndex == -1;
  }
};

#endif  // INCLUDE_TSTACK_H_
