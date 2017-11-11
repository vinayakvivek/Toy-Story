#ifndef MODELS_HPP_
#define MODELS_HPP_

#include "node.hpp"
#include "texture_util.hpp"

#define FLOOR_LEVEL -415.0f
#define WALL_HEIGHT 5000.0f
#define FLOOR_LENGTH 5000.0f

class Bulb : public Node {
  void setInitialTransformation() {
  }

 public:
  Bulb(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/floor.bmp", 512, 512);
    data = cylinder(100, 100, 50);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -0.0; xrot_limits[1] = 0.0;
    yrot_limits[0] = -0.0; yrot_limits[1] = 0.0;
    zrot_limits[0] = -0.0; zrot_limits[1] = 0.0;

    is_static = true;

    populateBuffers();
    setInitialTransformation();
  }

  void translate(const glm::vec3 &trans) {
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), trans);
    updateModelMatrix(translate);
  }
};

class Floor : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, FLOOR_LEVEL, 0.0f));
    glm::mat4 initial_transformation = translate * scale;
    updateModelMatrix(initial_transformation);
  }

 public:
  Floor(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/floor.bmp", 512, 512);
    data = cuboid(FLOOR_LENGTH, FLOOR_LENGTH, 5);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -0.0; xrot_limits[1] = 0.0;
    yrot_limits[0] = -0.0; yrot_limits[1] = 0.0;
    zrot_limits[0] = -0.0; zrot_limits[1] = 0.0;

    is_static = true;

    populateBuffers();
    setInitialTransformation();
  }
};

class Ceiling : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, FLOOR_LEVEL + WALL_HEIGHT, 0.0f));
    glm::mat4 initial_transformation = translate * scale;
    updateModelMatrix(initial_transformation);
  }

 public:
  Ceiling(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/wall.bmp", 1024, 1024);
    data = cuboid(FLOOR_LENGTH, FLOOR_LENGTH, 5);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -0.0; xrot_limits[1] = 0.0;
    yrot_limits[0] = -0.0; yrot_limits[1] = 0.0;
    zrot_limits[0] = -0.0; zrot_limits[1] = 0.0;

    is_static = true;

    populateBuffers();
    setInitialTransformation();
  }
};

class Wall : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (float)PI/2, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, FLOOR_LEVEL, FLOOR_LENGTH));
    glm::mat4 initial_transformation = translate * rotate * scale;
    updateModelMatrix(initial_transformation);
  }

 public:
  Wall(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent, int wall_pos): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/wall.bmp", 1024, 1024);
    data = cuboid(5, FLOOR_LENGTH, WALL_HEIGHT);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -0.0; xrot_limits[1] = 0.0;
    yrot_limits[0] = -0.0; yrot_limits[1] = 0.0;
    zrot_limits[0] = -0.0; zrot_limits[1] = 0.0;

    is_static = true;

    populateBuffers();
    setInitialTransformation();

    glm::mat4 rotate;
    switch (wall_pos) {
      case 1:
        rotate = glm::rotate(glm::mat4(1.0f), (float)PI / 2, glm::vec3(0.0f, 1.0f, 0.0f));
        updateModelMatrix(rotate);
        break;
      case 2:
        rotate = glm::rotate(glm::mat4(1.0f), (float)PI, glm::vec3(0.0f, 1.0f, 0.0f));
        updateModelMatrix(rotate);
        break;
      case 3:
        rotate = glm::rotate(glm::mat4(1.0f), -(float)PI/2, glm::vec3(0.0f, 1.0f, 0.0f));
        updateModelMatrix(rotate);
        break;
    }
  }
};

class Walls {
  Node *wall_1;
  Node *wall_2;
  Node *wall_3;
  Node *wall_4;

 public:
  explicit Walls(GLuint shaderProgram) {
    wall_1 = new Wall("wall_1", 0, shaderProgram, NULL, 0);
    wall_2 = new Wall("wall_2", 1, shaderProgram, NULL, 1);
    wall_3 = new Wall("wall_2", 2, shaderProgram, NULL, 2);
    wall_4 = new Wall("wall_2", 3, shaderProgram, NULL, 3);
  }

  void render() {
    wall_1->render();
    wall_2->render();
    wall_3->render();
    wall_4->render();
  }
};


#endif  // MODELS_HPP_