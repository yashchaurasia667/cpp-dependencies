#pragma once

class IndexBuffer {
private:
  unsigned int ID;

public:
  IndexBuffer();
  IndexBuffer(unsigned int size, unsigned int *data, unsigned int usage);
  ~IndexBuffer();

  // 1. Delete copy semantics to prevent shallow copies
  IndexBuffer(const IndexBuffer &) = delete;
  IndexBuffer &operator=(const IndexBuffer &) = delete;

  // 2. Declare move semantics
  IndexBuffer(IndexBuffer &&other) noexcept;
  IndexBuffer &operator=(IndexBuffer &&other) noexcept;

  void bind() const;
  void unbind() const;
  void setData(unsigned int size, unsigned int *data, unsigned int usage);
};
