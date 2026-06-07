#include "vertexBuffer.h"
#include <utils.h>

#include <glad/glad.h>

VertexBuffer::VertexBuffer() : ID(0) {
  glCall(glGenBuffers(1, &ID));
  glCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

VertexBuffer::VertexBuffer(unsigned int size, void *data, unsigned int usage)
    : VertexBuffer() {
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}

VertexBuffer::~VertexBuffer() {
  glCall(glDeleteBuffers(1, &ID));
}

// Move Constructor
VertexBuffer::VertexBuffer(VertexBuffer &&other) noexcept : ID(other.ID) {
  other.ID = 0;
}

// Move Assignment Operator
VertexBuffer &VertexBuffer::operator=(VertexBuffer &&other) noexcept {
  if (this != &other) {
    // Clean up the old buffer using your error-checking macro
    if (ID != 0) {
      glCall(glDeleteBuffers(1, &ID));
    }

    // Steal the new resource
    ID = other.ID;

    // Nullify the temporary object's ID
    other.ID = 0;
  }
  return *this;
}

// -------------------------------------

void VertexBuffer::bind() const { glCall(glBindBuffer(GL_ARRAY_BUFFER, ID)); }

void VertexBuffer::unbind() const { glCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); }

void VertexBuffer::setData(unsigned int size, void *data, unsigned int usage) {
  glCall(glDeleteBuffers(1, &ID));
  glCall(glGenBuffers(1, &ID)); // Added this: you need a new ID after deleting!
  glCall(glBindBuffer(GL_ARRAY_BUFFER, ID));
  glCall(glBufferData(GL_ARRAY_BUFFER, size, data, usage));
}
