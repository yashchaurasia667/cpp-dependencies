#pragma once

#include <vertexBuffer.h>
#include <vertexBufferLayout.h>

class VertexArray
{
private:
  unsigned int ID;

public:
  VertexArray();
  ~VertexArray();

  VertexArray(const VertexArray&) = delete;
  VertexArray& operator=(const VertexArray&) = delete;

  VertexArray(VertexArray&& other) noexcept;
  VertexArray& operator=(VertexArray&& other) noexcept;

  void bind() const;
  void unbind() const;
  
  void addBuffer(VertexBuffer &vb, VertexBufferLayout &layout);
};
