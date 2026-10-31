#pragma once

template <class T, int Capacity> class RingBuffer {
public:
  /**
   * @brief Stores a value, overwrites the oldest one if the buffer is full.
   * @param value - The value to be stored.
   */
  void put(T value) {
    slots[head] = value;
    head = (head + 1) % Capacity;
    if (count < Capacity) {
      count++;
    }
  }

  /** @return The most recently stored value. */
  T last() const { return slots[(head + Capacity - 1) % Capacity]; }

  /**
   * @brief Checks whether anything is stored in the buffer.
   * @return true if the buffer is empty.
   */
  bool empty() const { return count == 0; }

private:
  T slots[Capacity] = {};
  int head = 0;
  int count = 0;
};
