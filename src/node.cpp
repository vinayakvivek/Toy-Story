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
  initial_matrix = glm::mat4(1.0f);
  model_matrix = glm::mat4(1.0f);
  normal_matrix = glm::mat4(1.0f);

  last_rot = glm::vec3(0.0f);
  last_pos = glm::vec3(0.0f);
  is_static = false;

  this->shaderProgram = shaderProgram;

  this->parent = parent;
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

void Node::updateModelMatrix(const glm::mat4 &transformation, bool update_child) {
  model_matrix = transformation * model_matrix;
  normal_matrix = glm::inverse(glm::transpose(model_matrix));

  if (update_child) {
    for (Node *child : children) {
      child->updateModelMatrix(transformation);
    }
  }
}

void Node::render(int mode, int curr_keyframe, int curr_frame) {

  if (mode == 1) {
    glm::quat q1(glm::vec3(0, 0, 0));
    glm::quat q2(rot_keyframes[curr_keyframe + 1]);

    glm::quat q_rot = glm::slerp(q1, q2, 1.0f / 120);
    glm::mat4 rot_matrix = glm::mat4_cast(q_rot);

    rot_matrix = model_matrix * glm::inverse(local_matrix) * rot_matrix * local_matrix * glm::inverse(model_matrix);
    updateModelMatrix(rot_matrix);

    // xrot += glm::degrees(rot_keyframes[curr_keyframe + 1].x) / 120;
    // yrot += glm::degrees(rot_keyframes[curr_keyframe + 1].y) / 120;
    // zrot += glm::degrees(rot_keyframes[curr_keyframe + 1].z) / 120;

    if (translatable) {
      glm::vec3 trans_vec = (1.0f / 120) * pos_keyframes[curr_keyframe + 1];
      glm::mat4 trans_matrix = glm::translate(glm::mat4(1.0f), trans_vec);
      trans_matrix = model_matrix * glm::inverse(local_matrix) * trans_matrix * local_matrix * glm::inverse(model_matrix);
      xpos += trans_vec.x;
      ypos += trans_vec.y;
      zpos += trans_vec.z;
      updateModelMatrix(trans_matrix);
    }
  }

  glBindVertexArray(vao);

  // bind texture
  glActiveTexture(GL_TEXTURE0 + 0);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(u_texture_sampler, 0);

  glUniformMatrix4fv(u_model_matrix, 1, GL_FALSE, glm::value_ptr(model_matrix));
  glUniformMatrix4fv(u_normal_matrix, 1, GL_FALSE, glm::value_ptr(normal_matrix));
  glDrawArrays(GL_TRIANGLES, 0, data->num_vertices);

  for (Node *child : children) {
    child->render(mode, curr_keyframe, curr_frame);
  }
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

void Node::saveKeyframe(std::fstream &key_file) {
  key_file << glm::radians(xrot - last_rot.x) << " "
           << glm::radians(yrot - last_rot.y) << " "
           << glm::radians(zrot - last_rot.z) << " ";
  last_rot = glm::vec3(xrot, yrot, zrot);

  if (translatable) {
    key_file << (xpos - last_pos.x) << " "
             << (ypos - last_pos.y) << " "
             << (zpos - last_pos.z) << " ";
    last_pos = glm::vec3(xpos, ypos, zpos);
  }

  for (Node *child : children) {
    child->saveKeyframe(key_file);
  }
}

void Node::loadKeyframe(std::fstream &key_file) {
  GLfloat x = 0, y = 0, z = 0;
  key_file >> x >> y >> z;
  rot_keyframes.push_back(glm::vec3(x, y, z));

  if (translatable) {
    key_file >> x >> y >> z;
    pos_keyframes.push_back(glm::vec3(x, y, z));
  }

  for (Node *child : children) {
    child->loadKeyframe(key_file);
  }
}

void Node::reset() {
  for (Node *child : children) {
    child->reset();
  }

  model_matrix = initial_matrix * local_matrix;
  xpos = ypos = zpos = 0;
  xrot = yrot = zrot = 0;
  rot_keyframes.clear();
  pos_keyframes.clear();
  last_pos = glm::vec3(0.0f);
  last_rot = glm::vec3(0.0f);

  for (Node *child : children) {
    child->updateModelMatrix(initial_matrix);
  }
}