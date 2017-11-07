#include "node.hpp"

Node::Node(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent) {
  this->name = name;
  this->id = id;

  xpos = 0.0; ypos = 0.0; zpos = 0.0;
  xrot = 0.0; yrot = 0.0; zrot = 0.0;

  xrot_limits[0] = xrot_limits[1] = 0.0;
  yrot_limits[0] = yrot_limits[1] = 0.0;
  zrot_limits[0] = zrot_limits[1] = 0.0;

  translatable = false;

  local_matrix = glm::mat4(1.0f);
  model_matrix = glm::mat4(1.0f);
  normal_matrix = glm::mat4(1.0f);

  this->shaderProgram = shaderProgram;

  this->parent = parent;
  // populateBuffers();
  children.resize(0);
}

void Node::populateBuffers() {
  vertex_buffer_size = data->num_vertices * sizeof(glm::vec4);
  color_buffer_size = data->num_vertices * sizeof(glm::vec4);
  tex_coord_buffer_size = data->num_vertices * sizeof(glm::vec2);
  normal_buffer_size = data->num_vertices * sizeof(glm::vec4);

  v_position = glGetAttribLocation(shaderProgram, "vPosition");
  v_color = glGetAttribLocation(shaderProgram, "vColor");
  v_texture = glGetAttribLocation(shaderProgram, "vTexture");
  v_normal = glGetAttribLocation(shaderProgram, "vNormal");
  u_model_matrix = glGetUniformLocation(shaderProgram, "uModelMatrix");
  u_normal_matrix = glGetUniformLocation(shaderProgram, "uNormalMatrix");
  u_texture_sampler = glGetUniformLocation(shaderProgram, "textureSampler");

  model_matrix = glm::mat4(1.0f);
  normal_matrix = glm::mat4(1.0f);

  glGenVertexArrays(1, &this->vao);
  glGenBuffers(1, &this->vbo);

  glBindVertexArray(vao);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glEnableVertexAttribArray(v_position);
  glVertexAttribPointer(v_position, 4, GL_FLOAT, GL_FALSE, 0,
                        BUFFER_OFFSET(0));
  glEnableVertexAttribArray(v_color);
  glVertexAttribPointer(v_color, 4, GL_FLOAT, GL_FALSE, 0,
                        BUFFER_OFFSET(vertex_buffer_size));
  glEnableVertexAttribArray(v_texture);
  glVertexAttribPointer(v_texture, 2, GL_FLOAT, GL_FALSE, 0,
                        BUFFER_OFFSET(vertex_buffer_size + color_buffer_size));
  glEnableVertexAttribArray(v_normal);
  glVertexAttribPointer(v_normal, 4, GL_FLOAT, GL_FALSE, 0,
                        BUFFER_OFFSET(vertex_buffer_size + color_buffer_size +
                          tex_coord_buffer_size));

  glBufferData(GL_ARRAY_BUFFER,
              vertex_buffer_size +
                color_buffer_size +
                tex_coord_buffer_size +
                normal_buffer_size,
              NULL,
              GL_STATIC_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER,
                  0,
                  vertex_buffer_size,
                  data->vertices);
  glBufferSubData(GL_ARRAY_BUFFER,
                  vertex_buffer_size,
                  color_buffer_size,
                  data->colors);
  glBufferSubData(GL_ARRAY_BUFFER,
                  vertex_buffer_size + color_buffer_size,
                  tex_coord_buffer_size,
                  data->tex_coords);
  glBufferSubData(GL_ARRAY_BUFFER,
                  vertex_buffer_size + color_buffer_size + tex_coord_buffer_size,
                  normal_buffer_size,
                  data->normals);
}

void Node::addChild(Node *node) {
  children.push_back(node);
  node->updateModelMatrix(model_matrix * glm::inverse(local_matrix));
}

void Node::updateModelMatrix(const glm::mat4 &transformation) {
  model_matrix = transformation * model_matrix;
  normal_matrix = glm::inverse(glm::transpose(model_matrix));
  pivot_point = transformation * pivot_point;

  for (Node *child : children) {
    child->updateModelMatrix(transformation);
  }
}

void Node::render() {
  glBindVertexArray(vao);

  // bind texture
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(u_texture_sampler, 0);

  glUniformMatrix4fv(u_model_matrix, 1, GL_FALSE, glm::value_ptr(model_matrix));
  glUniformMatrix4fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glDrawArrays(GL_TRIANGLES, 0, data->num_vertices);

  // TODO: call child->render();
}

void Node::rotate(GLuint axis, GLfloat angle) {
  glm::mat4 rot_matrix(1.0f);
  switch (axis) {
    case 0:
      // X axis
      if (xrot + angle >= xrot_limits[0] && xrot + angle <= xrot_limits[1]) {
        xrot += angle;
        rot_matrix = glm::rotate(rot_matrix, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
      }
      break;
    case 1:
      // Y axis
      if (yrot + angle >= yrot_limits[0] && yrot + angle <= yrot_limits[1]) {
        yrot += angle;
        rot_matrix = glm::rotate(rot_matrix, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
      }
      break;
    case 2:
      // Z axis
      if (zrot + angle >= zrot_limits[0] && zrot + angle <= zrot_limits[1]) {
        zrot += angle;
        rot_matrix = glm::rotate(rot_matrix, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
      }
      break;
  }
  // rot_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(pivot_point)) * rot_matrix * glm::translate(glm::mat4(1.0f), glm::vec3(-pivot_point));
  rot_matrix = model_matrix * glm::inverse(local_matrix) * rot_matrix * local_matrix * glm::inverse(model_matrix);

  updateModelMatrix(rot_matrix);
}

void Node::translate(GLuint axis, GLfloat d) {
  if (!translatable)
    return;

  glm::mat4 trans_matrix(1.0f);

  switch (axis) {
    case 0:
      // X axis
      xpos += d;
      trans_matrix = glm::translate(trans_matrix, glm::vec3(d, 0.0, 0.0));
      break;
    case 1:
      // Y axis
      // ypos += d;
      // trans_matrix = glm::translate(trans_matrix, glm::vec3(0.0, d, 0.0));
      break;
    case 2:
      // Z axis
      zpos += d;
      trans_matrix = glm::translate(trans_matrix, glm::vec3(0.0, 0.0, d));
      break;
  }

  trans_matrix = model_matrix * glm::inverse(local_matrix) * trans_matrix * local_matrix * glm::inverse(model_matrix);
  updateModelMatrix(trans_matrix);
}