#include "vertexArray.h"

#include <utils.h>
#include <vector>
#include <vertexBuffer.h>
#include <vertexBufferLayout.h>

#include <iostream>

VertexArray::VertexArray() : ID(0) {
  glCall(glGenVertexArrays(1, &ID));
  glCall(glBindVertexArray(ID));
}

VertexArray::~VertexArray() { glCall(glDeleteVertexArrays(1, &ID)); }

// --- Move Semantics Implementation ---
// Move Constructor
VertexArray::VertexArray(VertexArray &&other) noexcept : ID(other.ID) {
  other.ID = 0;
}

// Move Assignment Operator
VertexArray &VertexArray::operator=(VertexArray &&other) noexcept {
  if (this != &other) {
    // Clean up the old VAO
    if (ID != 0) {
      glCall(glDeleteVertexArrays(1, &ID));
    }

    // Steal the new resource
    ID = other.ID;

    // Disarm the temporary object
    other.ID = 0;
  }
  return *this;
}

// -------------------------------------

void VertexArray::bind() const {
  // std::cout << "VERTEX_ARRAY::ID -> " << ID << std::endl;
  glCall(glBindVertexArray(ID));
}

void VertexArray::unbind() const { glCall(glBindVertexArray(0)); }

void VertexArray::addBuffer(VertexBuffer &vb, VertexBufferLayout &layout) {
  // Update this to use a reference
  const std::vector<struct Attribute> &elements = layout.getElements();
  unsigned int offset = 0;
  unsigned int stride = layout.getStride();

  for (unsigned int i = 0; i < elements.size(); i++)
  {
    struct Attribute elm = elements[i];
    glCall(glEnableVertexAttribArray(i));
    glCall(glVertexAttribPointer(i, elm.count, elm.type, elm.normalized, stride,
                                 (void *)static_cast<uintptr_t>(offset)));

    offset += elm.count * elm.getSizeOfType(elm.type);
  }
}
