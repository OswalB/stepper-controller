#pragma once

#include <stdint.h>

#define EVENT_QUEUE_SIZE 16

class EventQueue {
public:
  bool push(const Event& ev) {
    uint8_t next = (head + 1) % EVENT_QUEUE_SIZE;
    if (next == tail) return false; // cola llena
    buffer[head] = ev;
    head = next;
    return true;
  }

  bool pop(Event& ev) {
    if (head == tail) return false; // cola vacía
    ev = buffer[tail];
    tail = (tail + 1) % EVENT_QUEUE_SIZE;
    return true;
  }

  bool isEmpty() const {
    return head == tail;
  }

private:
  Event buffer[EVENT_QUEUE_SIZE];
  volatile uint8_t head = 0;
  volatile uint8_t tail = 0;
};