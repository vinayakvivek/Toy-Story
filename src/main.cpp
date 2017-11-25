#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "view.hpp"

GLfloat half_width = 400, half_height = 400, half_depth = 10000;
View *v;
int mode = 0;

void initView() {
  v = new View(half_width, half_height, half_depth);
}

int main(int argc, char** argv) {
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(toys::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  // We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  // This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // We don't want the old OpenGL
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // ! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(half_width * 2, half_height * 2, "Toy story", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  // ! Make the window's context current
  glfwMakeContextCurrent(window);

  // Initialize GLEW
  // Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err) {
    // Problem: glewInit failed, something is seriously wrong.
    std::cerr << "GLEW Init Failed : %s" << std::endl;
  }

  // Print and see what context got enabled
  std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
  std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
  std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
  std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

  // Keyboard Callback
  glfwSetKeyCallback(window, toys::key_callback);
  // Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, toys::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  // Initialize GL state
  toys::initGL();
  initView();

  double lastTime = glfwGetTime();
  int nbFrames = 0;

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0) {

    // Measure speed
    double currentTime = glfwGetTime();
    nbFrames++;
    if (currentTime - lastTime >= 1.0){
      // printf and reset timer
      if (mode == 1)
        std::cout << "fps: " << nbFrames << "\n";
      nbFrames = 0;
      lastTime += 1.0;
    }

    // Render here
    v->renderGL();

    // Swap front and back buffers
    glfwSwapBuffers(window);

    // Poll for and process events
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
