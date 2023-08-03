#include "boilerplate.h"

#include "glad/glad.h"

#include "GLFW/glfw3.h"

#include <vector>

int w, h;

GLFWwindow* window;
GLuint texture;
GLuint vao;
GLuint program;

struct v3 {
  float e[3];
};
std::vector<v3> buffer;

GLuint CreateProgram() {
  const char* vsrc = R"(
#version 460 core

layout (location = 0) out vec2 texcoord;

void main() {
  float x = -1.0 + float(((gl_VertexID & 1) << 2));
  float y = -1.0 + float(((gl_VertexID & 2) << 1));

  texcoord.x = (x + 1.0) * 0.5;
  texcoord.y = (y + 1.0) * 0.5;

  gl_Position = vec4(x, y, 0.0, 1.0);
}
)";

  const char* fsrc = R"(
#version 460 core

uniform sampler2D tex;
uniform int nbPass;

layout (location = 0) in vec2 texcoord;
layout (location = 0) out vec4 color;

void main() {
  color = vec4(texture(tex, texcoord).rgb / nbPass, 1);
}
)";

  // Create program and render
  GLuint vs = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vs, 1, &vsrc, nullptr);
  glCompileShader(vs);
  int success;
  glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(vs, 512, NULL, infoLog);

    printf("Error compiling vs: %s\n", infoLog);

    return 42;
  }

  GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fs, 1, &fsrc, nullptr);
  glCompileShader(fs);
  glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
  if (!success) {
    char infoLog[512];
    glGetShaderInfoLog(fs, 512, NULL, infoLog);

    printf("Error compiling fs: %s\n", infoLog);

    return 42;
  }

  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  return program;
}

bool setup(int width, int height) {
  w = width;
  h = height;

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(w, h, "Raytracer", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSwapInterval(0);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    fprintf(stderr, "OpenGL error\n");
    return false;
  }

  glCreateTextures(GL_TEXTURE_2D, 1, &texture);
  glTextureStorage2D(texture, 1, GL_RGB32F, w, h);

  glCreateVertexArrays(1, &vao);

  glBindTextureUnit(0, texture);

  program = CreateProgram();

  buffer.resize(w * h);

  return true;
}

void set_pixel(color c, int i, int j) {
  v3 v = {(float)c.x, (float)c.y, (float)c.z};
  buffer[j * w + i] = v;
}

int display_result() {
  glTextureSubImage2D(texture, 0, 0, 0, w, h, GL_RGB, GL_FLOAT, buffer.data());

  if (glGetError() != GL_NO_ERROR) {
    fprintf(stderr, "OpenGL error\n");
    return 42;
  }

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glViewport(0, 0, w, h);

    glUseProgram(program);
    glUniform1i(glGetUniformLocation(program, "nbPass"), 1);

    if (glGetError() != GL_NO_ERROR) {
      fprintf(stderr, "OpenGL error\n");
      return 42;
    }

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
  }

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
