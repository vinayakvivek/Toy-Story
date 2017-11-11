#ifndef _NODE_HPP_
#define _NODE_HPP_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

#include "model_utils.hpp"

#define BUFFER_OFFSET(offset) (reinterpret_cast<void *>(offset))
#define PI 3.14159265
#define deg_to_rad(a) (a * PI / 180.0)

class Node {
 protected:
  std::string name;
  int id;

  GLuint vao, vbo, tex;
  GLuint shaderProgram;

  VertexData *data;

  std::size_t vertex_buffer_size;
  std::size_t color_buffer_size;
  std::size_t tex_coord_buffer_size;
  std::size_t normal_buffer_size;

  GLuint v_position;
  GLuint v_color;
  GLuint v_texture;
  GLuint v_normal;
  GLuint u_model_matrix;
  GLuint u_normal_matrix;

  GLuint u_texture_sampler;

  // transformations
  glm::mat4 local_matrix;  // for initial local transformations
  glm::mat4 model_matrix;
  glm::mat4 normal_matrix;

  GLfloat xpos, ypos, zpos;
  bool translatable;

  GLfloat xrot, yrot, zrot;
  GLfloat xrot_limits[2], yrot_limits[2], zrot_limits[2];

  // for keyframe
  std::vector<glm::vec3> rot_keyframes;
  std::vector<glm::vec3> pos_keyframes;
  glm::vec3 last_rot;
  glm::vec3 last_pos;
  bool is_static;

  glm::vec4 pivot_point;

  std::vector<Node*> children;
  Node *parent;

  void populateBuffers();
  virtual void setInitialTransformation() = 0;

 public:
  Node(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent);
  void addChild(Node *node);
  virtual void rotate(GLuint axis, GLfloat angle);
  virtual void translate(GLuint axis, GLfloat d);
  void updateModelMatrix(const glm::mat4 &transformation, bool update_child = true);
  void render(int mode = 0, int curr_keyframe = 0, int curr_frame = 0);
  void saveKeyframe(std::fstream &key_file);
  void clearKeyframes();
  void loadKeyframe(std::fstream &key_file);

  int getId() {return id;}
  virtual ~Node();
};

#endif  // _NODE_HPP_