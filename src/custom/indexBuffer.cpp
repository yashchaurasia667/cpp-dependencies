#include "indexBuffer.h"
#include <utils.h>

#include <glad/glad.h>

IndexBuffer::IndexBuffer() : ID(0) {
  glCall(glGenBuffers(1, &ID));
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}

IndexBuffer::IndexBuffer(unsigned int size, unsigned int *data,
                         unsigned int usage)
    : IndexBuffer() {
  glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
}

IndexBuffer::~IndexBuffer() { glCall(glDeleteBuffers(1, &ID)); }

// --- Move Semantics Implementation ---

// Move Constructor
IndexBuffer::IndexBuffer(IndexBuffer &&other) noexcept : ID(other.ID) {
  other.ID = 0;
}

// Move Assignment Operator
IndexBuffer &IndexBuffer::operator=(IndexBuffer &&other) noexcept {
  if (this != &other) {
    // Clean up the old buffer
    if (ID != 0) {
      glCall(glDeleteBuffers(1, &ID));
    }

    // Steal the new resource
    ID = other.ID;

    // Disarm the temporary object
    other.ID = 0;
  }
  return *this;
}

// -------------------------------------

void IndexBuffer::bind() const {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
}

void IndexBuffer::unbind() const {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::setData(unsigned int size, unsigned int *data,
                          unsigned int usage) {
  glCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID));
  glCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage));
}
