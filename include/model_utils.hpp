#ifndef _MODEL_UTIL_HPP_
#define _MODEL_UTIL_HPP_

#include <GL/glew.h>

#include <vector>
#include <string>
#include <cmath>
#include <iostream>

#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define PI 3.14159265
#define deg_to_rad(a) (a * PI / 180.0)

struct VertexData {
  GLuint num_vertices;
  glm::vec4 *vertices;
  glm::vec4 *colors;
  glm::vec2 *tex_coords;
  glm::vec4 *normals;

  void deleteData() {
    delete [] vertices;
    delete [] colors;
    delete [] tex_coords;
    delete [] normals;
  }
};

VertexData* sphere(GLfloat r, GLuint n_lats = 50, GLuint n_longs = 50);
VertexData* cylinder(GLfloat br, GLfloat tr, GLfloat h,
                     GLuint tesselation = 50,
                     bool closed = true);

/**
 * a <- half_length
 * b <- half_breadth
 * c <- height
 */
VertexData* cuboid(GLfloat a, GLfloat b, GLfloat c);

#endif  // _MODEL_UTIL_HPP_
