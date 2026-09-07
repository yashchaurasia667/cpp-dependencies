#pragma once

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include <string>

std::string getShaderSource(const char *path);
void checkCompileError(unsigned int id, const char *type);
unsigned int createShader(GLenum type, std::string source,
                          const char *shader_type);

class ComputeShader {
private:
  unsigned int ID = 0;

public:
  ComputeShader() = default;
  ComputeShader(const char *path);

  ComputeShader(ComputeShader &&other) noexcept;
  ComputeShader &operator=(ComputeShader &&other) noexcept;
  ~ComputeShader();

  void bind();
  void unbind();
  unsigned int getId();

  void setInt(const char *name, int data);
  void setFloat(const char *name, float data);
  void setBool(const char *name, bool data);
  void setVec3(const char *name, glm::vec3 data);
  void setVec2(const char *name, glm::vec2 data);
  void setMat4(const char *name, glm::mat4 data);
};

class Shader {
private:
  unsigned int ID = 0;

public:
  Shader() = default;
  Shader(const char *vertex_path, const char *fragmen_path,
         const char *geometry_path = nullptr,
         const char *tessellation_control_path = nullptr,
         const char *tessellation_evaluation_path = nullptr);

  Shader(Shader &&other) noexcept;
  Shader &operator=(Shader &&other) noexcept;
  ~Shader();

  void bind();
  void unbind();
  unsigned int getId();

  void setInt(const char *name, int data);
  void setFloat(const char *name, float data);
  void setBool(const char *name, bool data);
  void setVec3(const char *name, glm::vec3 data);
  void setVec2(const char *name, glm::vec2 data);
  void setMat4(const char *name, glm::mat4 data);
};
