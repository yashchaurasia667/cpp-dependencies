#pragma once

#include <vector>
#include <glad/glad.h>
#include <utils.h>

struct Attribute
{
  unsigned int count;
  unsigned int type;
  unsigned int normalized;

  static unsigned int getSizeOfType(unsigned int type)
  {
    switch (type)
    {
    case GL_FLOAT:
      return 4;
    case GL_UNSIGNED_INT:
      return 4;
    case GL_UNSIGNED_BYTE:
      return 1;
    }
    ASSERT(false);
    return 0;
  }
};

class VertexBufferLayout
{
private:
  std::vector<Attribute> layout;
  unsigned int stride;

public:
  VertexBufferLayout() : stride(0) {};

  // --- Explicit Copy & Move Semantics ---
  
  // Explicitly tell the compiler to generate standard copy behavior
  VertexBufferLayout(const VertexBufferLayout&) = default;
  VertexBufferLayout& operator=(const VertexBufferLayout&) = default;

  // Explicitly tell the compiler to generate standard move behavior
  VertexBufferLayout(VertexBufferLayout&&) noexcept = default;
  VertexBufferLayout& operator=(VertexBufferLayout&&) noexcept = default;

  // --------------------------------------

  template <typename T>
  void push(unsigned int count);

  inline const std::vector<Attribute>& getElements() const { return layout; }
  
  unsigned int getStride() const;
};
