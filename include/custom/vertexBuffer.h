#pragma once

class VertexBuffer
{
private:
  unsigned int ID;

public:
  VertexBuffer();
  VertexBuffer(unsigned int size, void *data, unsigned int usage);
  ~VertexBuffer();

  VertexBuffer(const VertexBuffer&) = delete;
  VertexBuffer& operator=(const VertexBuffer&) = delete;

  VertexBuffer(VertexBuffer&& other) noexcept;
  VertexBuffer& operator=(VertexBuffer&& other) noexcept;

  void bind() const;
  void unbind() const;
  void setData(unsigned int size, void *data, unsigned int usage);
};
