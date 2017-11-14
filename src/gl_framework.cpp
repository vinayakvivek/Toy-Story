#include "gl_framework.hpp"
#include "view.hpp"

extern View *v;
extern GLfloat half_width, half_height, half_depth;

namespace toys {

  // !Initialize GL State
  void initGL(void) {
    // Set frame buffer clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Set depth buffer furthest depth
    glClearDepth(1.0);
    // Set depth test to less-than
    glDepthFunc(GL_LESS);
    // Enable depth testing
    glEnable(GL_DEPTH_TEST);
    // Enable Gourard shading
    glShadeModel(GL_SMOOTH);

    glEnable(GL_PROGRAM_POINT_SIZE);
  }

  // !GLFW Error Callback
  void error_callback(int error, const char* description) {
    std::cerr << description << std::endl;
  }

  // !GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // !Resize the view port to fit the window size - draw to entire window
    glViewport(0, 0, width, height);

    #ifdef __APPLE__
      half_width = width / 4;
      half_height = height / 4;
    #elif __linux__
      half_width = width / 2;
      half_height = height / 2;
    #endif

    v->updateView(half_width, half_height);
  }

  // !GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    // !Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, GL_TRUE);
      return;
    } else if (key == GLFW_KEY_P && action == GLFW_PRESS) {
      v->togglePerspective();
      return;
    } else if (key == GLFW_KEY_M && action == GLFW_PRESS) {
      v->toggleMode();
      return;
    } else if (key == GLFW_KEY_R && action == GLFW_PRESS) {
      v->reset();
      return;
    } else if (key == GLFW_KEY_O && action == GLFW_PRESS) {
      v->saveKeyframe();
      return;
    } else if (key == GLFW_KEY_B && action == GLFW_PRESS) {
      v->selectModel(0);  // select buzz
      return;
    } else if (key == GLFW_KEY_H && action == GLFW_PRESS) {
      v->selectModel(1);  // select Hamm
      return;
    } else if (key == GLFW_KEY_J && action == GLFW_PRESS) {
      v->toggleLight(0);
      return;
    } else if (key == GLFW_KEY_K && action == GLFW_PRESS) {
      v->toggleLight(1);
      return;
    } else if (key == GLFW_KEY_L && action == GLFW_PRESS) {
      v->toggleLight(2);
      return;
    }

    switch (key) {
      // rotation
      case GLFW_KEY_UP:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
          v->translateCamera(1, 20);
        else
          v->rotateCamera(1, 1);
        break;

      case GLFW_KEY_DOWN:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
          v->translateCamera(1, -20);
        else
          v->rotateCamera(1, -1);
        break;

      case GLFW_KEY_LEFT:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
          v->translateCamera(0, 20);
        else
          v->rotateCamera(0, 1);
        break;

      case GLFW_KEY_RIGHT:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
          v->translateCamera(0, -20);
        else
          v->rotateCamera(0, -1);
        break;

      case GLFW_KEY_PAGE_UP:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
          v->translateCamera(2, 20);
        else
          v->rotateCamera(2, 1);
        break;

      case GLFW_KEY_PAGE_DOWN:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
          v->translateCamera(0, -20);
        else
          v->rotateCamera(2, -1);
        break;

      case GLFW_KEY_Z:
        v->zoom(20);
        break;

      case GLFW_KEY_X:
        v->zoom(-20);
        break;

      // model rotation
      case GLFW_KEY_W:
        v->rotateNode(1, 1);
        break;

      case GLFW_KEY_S:
        v->rotateNode(1, -1);
        break;

      case GLFW_KEY_A:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          v->translateNode(0, 10);
        } else {
          v->rotateNode(0, 1);
        }
        break;

      case GLFW_KEY_D:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          v->translateNode(0, -10);
        } else {
          v->rotateNode(0, -1);
        }
        break;

      case GLFW_KEY_Q:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          v->translateNode(2, 10);
        } else {
          v->rotateNode(2, 1);
        }
        break;

      case GLFW_KEY_E:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          v->translateNode(2, -10);
        } else {
          v->rotateNode(2, -1);
        }
        break;

      // select model
      case GLFW_KEY_B:
        // buzz
        v->selectModel(0);
        break;

      // select node
      case GLFW_KEY_0:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          v->selectNode(10);
        } else {
          v->selectNode(0);
        }
        break;
      case GLFW_KEY_1:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          v->selectNode(11);
        } else {
          v->selectNode(1);
        }
        break;
      case GLFW_KEY_2:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          v->selectNode(12);
        } else {
          v->selectNode(2);
        }
        break;
      case GLFW_KEY_3:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          v->selectNode(13);
        } else {
          v->selectNode(3);
        }
        break;
      case GLFW_KEY_4:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          v->selectNode(14);
        } else {
          v->selectNode(4);
        }
        break;
      case GLFW_KEY_5:
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
          v->selectNode(15);
        } else {
          v->selectNode(5);
        }
        break;
      case GLFW_KEY_6:
        v->selectNode(6);
        break;
      case GLFW_KEY_7:
        v->selectNode(7);
        break;
      case GLFW_KEY_8:
        v->selectNode(8);
        break;
    }
  }
};  // namespace toys
