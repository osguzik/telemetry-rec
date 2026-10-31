#pragma once

template <class T, int Capacity> class RingBuffer {
public:
  void put(T value) {
    slots[head] = value;
    head = (head + 1) % Capacity;
    if (count < Capacity) {
      count++;
    }
  }

  T last() const { return slots[(head + Capacity - 1) % Capacity]; }

  bool empty() const { return count == 0; }

private:
  T slots[Capacity] = {};
  int head = 0;
  int count = 0;
};
