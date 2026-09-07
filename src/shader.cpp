#include "shader.h"
#include <utils.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

string getShaderSource(const char *path) {
  ifstream shader_file(path);
  if (!shader_file) {
    cout << "ERROR::SHADER::" << path << "::NOT SUCCESSFULLY READ" << endl;
    return "";
  }

  cout << "Successfully read shader: " << path
       << endl; // Add this for debugging
  stringstream buffer;
  buffer << shader_file.rdbuf();
  string source = buffer.str();
  cout << "Shader source length: " << source.length() << endl; // Add this too
  return source;
}

void checkCompileError(unsigned int id, const char *type) {
  int success;
  char info[1024];
  if (strcmp(type, "PROGRAM") != 0) {
    glCall(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    if (!success) {
      glCall(glGetShaderInfoLog(id, 1024, NULL, info));

      cout << "ERROR::" << type << "::SHADER_COMPILATION_ERROR " << info
           << endl;
    }
  } else {
    glCall(glGetProgramiv(id, GL_LINK_STATUS, &success));
    if (!success) {
      glCall(glGetProgramInfoLog(id, 1024, NULL, info));

      cout << "ERROR::" << type << "::PROGRAM_LINKING_ERROR " << info << endl;
    }
  }
}

unsigned int createShader(GLenum type, string source, const char *shader_type) {
  unsigned int id = glCreateShader(type);
  // string source = getShaderSource(path);
  const char *c_source = source.c_str();

  glCall(glShaderSource(id, 1, &c_source, NULL));
  glCall(glCompileShader(id));
  checkCompileError(id, shader_type);

  return id;
}

void bind(unsigned int ID) { glCall(glUseProgram(ID)); }
void unbind() { glCall(glUseProgram(0)); }

void setInt(const char *name, int data, unsigned int ID) {
  unsigned int loc = glGetUniformLocation(ID, name);
  glCall(glUniform1i(loc, data));
}

void setFloat(const char *name, float data, unsigned int ID) {
  unsigned int loc = glGetUniformLocation(ID, name);
  glCall(glUniform1f(loc, data));
}

void setBool(const char *name, bool data, unsigned int ID) {
  unsigned int loc = glGetUniformLocation(ID, name);
  glCall(glUniform1i(loc, data));
}

void setVec3(const char *name, glm::vec3 data, unsigned int ID) {
  unsigned int loc = glGetUniformLocation(ID, name);
  glCall(glUniform3fv(loc, 1, glm::value_ptr(data)));
}

void setVec2(const char *name, glm::vec2 data, unsigned int ID) {
  unsigned int loc = glGetUniformLocation(ID, name);
  glCall(glUniform2fv(loc, 1, glm::value_ptr(data)));
}

void setMat4(const char *name, glm::mat4 data, unsigned int ID) {
  unsigned int loc = glGetUniformLocation(ID, name);
  glCall(glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(data)));
}

ComputeShader::ComputeShader(const char *path) {
  unsigned int compute_shader = 0;
  ID = glCreateProgram();

  if (path != nullptr) {
    string source = getShaderSource(path);
    compute_shader = createShader(GL_COMPUTE_SHADER, source, "COMPUTE SHADER");
    glCall(glAttachShader(ID, compute_shader));
  }

  glCall(glLinkProgram(ID));
  checkCompileError(ID, "PROGRAM");
  glCall(glValidateProgram(ID));

  if (compute_shader != 0)
    glDeleteShader(compute_shader);
}

ComputeShader::~ComputeShader() {
  if (ID != 0) {
    glCall(glDeleteProgram(ID));
  }
}

ComputeShader::ComputeShader(ComputeShader &&other) noexcept : ID(other.ID) {
  other.ID = 0; // Steal the ID, and set the temporary's ID to 0
}

ComputeShader &ComputeShader::operator=(ComputeShader &&other) noexcept {
  if (this != &other) {
    glDeleteProgram(ID); // Delete the old program if it exists
    ID = other.ID;       // Steal the ID from the temporary object
    other.ID = 0; // Set temporary's ID to 0 so its destructor does nothing
  }
  return *this;
}



void ComputeShader::bind() { ::bind(ID); }

void ComputeShader::unbind() { ::unbind(); }

unsigned int ComputeShader::getId() { return ID; }

void ComputeShader::setInt(const char *name, int data) {
  ::setInt(name, data, ID);
}
void ComputeShader::setFloat(const char *name, float data) {
  ::setFloat(name, data, ID);
}
void ComputeShader::setBool(const char *name, bool data) {
  ::setBool(name, data, ID);
}
void ComputeShader::setVec3(const char *name, glm::vec3 data) {
  ::setVec3(name, data, ID);
}
void ComputeShader::setVec2(const char *name, glm::vec2 data) {
  ::setVec2(name, data, ID);
}
void ComputeShader::setMat4(const char *name, glm::mat4 data) {
  ::setMat4(name, data, ID);
}

Shader::Shader(const char *vertex_path, const char *fragment_path,
               const char *geometry_path, const char *tessellation_control_path,
               const char *tessellation_evaluation_path) {
  unsigned int vertex_shader = 0;
  unsigned int fragment_shader = 0;
  unsigned int geometry_shader = 0;
  unsigned int tessellation_control_shader = 0;
  unsigned int tessellation_evaluation_shader = 0;

  ID = glCreateProgram();

  if (vertex_path != nullptr) {
    string source = getShaderSource(vertex_path);
    vertex_shader = createShader(GL_VERTEX_SHADER, source, "VERTEX_SHADER");
    glCall(glAttachShader(ID, vertex_shader));
  }

  if (fragment_path != nullptr) {
    string source = getShaderSource(fragment_path);
    fragment_shader =
        createShader(GL_FRAGMENT_SHADER, source, "FRAGMENT_SHADER");
    glCall(glAttachShader(ID, fragment_shader));
  }

  if (geometry_path != nullptr) {
    string source = getShaderSource(geometry_path);
    geometry_shader =
        createShader(GL_GEOMETRY_SHADER, source, "GEOMETRY_SHADER");
    glCall(glAttachShader(ID, geometry_shader));
  }

  if (tessellation_control_path != nullptr) {
    string source = getShaderSource(tessellation_control_path);
    tessellation_control_shader =
        createShader(GL_TESS_CONTROL_SHADER, source, "TESS_CONTROL_SHADER");
    glCall(glAttachShader(ID, tessellation_control_shader));
  }

  if (tessellation_evaluation_path != nullptr) {
    string source = getShaderSource(tessellation_evaluation_path);
    tessellation_evaluation_shader = createShader(
        GL_TESS_EVALUATION_SHADER, source, "TESS_EVALUATION_SHADER");
    glCall(glAttachShader(ID, tessellation_evaluation_shader));
  }

  glCall(glLinkProgram(ID));
  checkCompileError(ID, "PROGRAM");
  glCall(glValidateProgram(ID));

  if (vertex_shader != 0)
    glCall(glDeleteShader(vertex_shader));
  if (fragment_shader != 0)
    glCall(glDeleteShader(fragment_shader));
  if (geometry_shader != 0)
    glCall(glDeleteShader(geometry_shader));
  if (tessellation_control_shader != 0)
    glCall(glDeleteShader(tessellation_control_shader));
  if (tessellation_evaluation_shader != 0)
    glCall(glDeleteShader(tessellation_evaluation_shader));
}

Shader::Shader(Shader &&other) noexcept : ID(other.ID) {
  other.ID = 0; // Steal the ID, and set the temporary's ID to 0
}

Shader &Shader::operator=(Shader &&other) noexcept {
  if (this != &other) {
    glDeleteProgram(ID); // Delete the old program if it exists
    ID = other.ID;       // Steal the ID from the temporary object
    other.ID = 0; // Set temporary's ID to 0 so its destructor does nothing
  }
  return *this;
}

Shader::~Shader() {
  if (ID != 0) {
    glCall(glDeleteProgram(ID));
  }
}

void Shader::bind() { ::bind(ID); }
void Shader::unbind() { ::unbind(); }
unsigned int Shader::getId() { return ID; }

void Shader::setInt(const char *name, int data) { ::setInt(name, data, ID); }
void Shader::setFloat(const char *name, float data) {
  ::setFloat(name, data, ID);
}
void Shader::setBool(const char *name, bool data) { ::setBool(name, data, ID); }
void Shader::setVec3(const char *name, glm::vec3 data) {
  ::setVec3(name, data, ID);
}
void Shader::setVec2(const char *name, glm::vec2 data) {
  ::setVec2(name, data, ID);
}
void Shader::setMat4(const char *name, glm::mat4 data) {
  ::setMat4(name, data, ID);
}
