#include "view.hpp"

View::View(GLfloat h_width, GLfloat h_height, GLfloat h_depth) {
  half_width = h_width;
  half_height = h_height;
  half_depth = h_depth;

  c_xpos = 0.0; c_ypos = 0.0; c_zpos = 700.0;
  c_up_x = 0.0; c_up_y = 1.0; c_up_z = 0.0;
  c_xrot = 0.0; c_yrot = 0.0; c_zrot = 0.0;

  enable_perspective = true;

  light_positions[0] = glm::vec4(0.0, (FLOOR_LEVEL + WALL_HEIGHT) / 2, 4000.0, 1.0);
  light_positions[1] = glm::vec4(-4000.0, (FLOOR_LEVEL + WALL_HEIGHT) / 2, -4000.0, 1.0);

  spotlight_position[0] = glm::vec4(0.0, (FLOOR_LEVEL + WALL_HEIGHT) - 1000.0f, 1000.0f, 1.0);
  spotlight_position[1] = glm::vec4(0.0, 0.0, -0.0, 1.0);

  lights_state[0] = 1;
  lights_state[1] = 1;
  lights_state[2] = 0;

  initShadersGL();

  updateCamera();
  buzz = new Buzz(shaderProgram);
  hamm = new Hamm(shaderProgram);

  floor = new Floor("floor", 0, shaderProgram, NULL);
  walls = new Walls(shaderProgram);
  ceiling = new Ceiling("ceiling", 0, shaderProgram, NULL);
  bulb = new Bulb("bulb", 0, shaderProgram, NULL);
  bulb->translate(glm::vec3(spotlight_position[0]));

  curr_selected_model = 1;

  // record mode
  mode = 0;
  num_keyframes = 0;
  curr_keyframe = 0;
  curr_frame = 0;
  // loadKeyframes();

  last_c_rot = glm::vec3(c_xrot, c_yrot, c_zrot);
  last_c_pos = glm::vec3(c_xpos, c_ypos, c_zpos);
}

void View::updateView(GLfloat h_width, GLfloat h_height) {
  half_width = h_width;
  half_height = h_height;
  updateCamera();
}

void View::togglePerspective() {
  enable_perspective = !enable_perspective;
  updateCamera();
}

void View::initShadersGL() {
  std::string vertex_shader_file("shaders/vshader.glsl");
  std::string fragment_shader_file("shaders/fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(toys::loadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(toys::loadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = toys::createProgramGL(shaderList);
  glUseProgram(shaderProgram);

  u_view_matrix = glGetUniformLocation(shaderProgram, "uViewMatrix");
  u_camera_position = glGetUniformLocation(shaderProgram, "uCameraPosition");
  u_light_positions = glGetUniformLocation(shaderProgram, "uLightPositions");
  u_spotlight_position = glGetUniformLocation(shaderProgram, "uSpotLightPosition");
  u_lights_state = glGetUniformLocation(shaderProgram, "uLightsState");
}

void View::renderGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (mode == 1 && curr_keyframe + 1 < num_keyframes) {

    curr_frame++;
    curr_frame %= 120;

    interpolateCamera();

    if (curr_frame == 0) {
      curr_keyframe++;
    }
  }

  glUniform4fv(u_camera_position, 1, glm::value_ptr(glm::vec4(c_xpos, c_ypos, c_zpos, 1.0)));
  glUniform4fv(u_light_positions, 2, glm::value_ptr(light_positions[0]));
  glUniform4fv(u_spotlight_position, 2, glm::value_ptr(spotlight_position[0]));
  glUniform1uiv(u_lights_state, 3, &lights_state[0]);
  glUniformMatrix4fv(u_view_matrix, 1, GL_FALSE, glm::value_ptr(view_matrix));

  buzz->render(mode, curr_keyframe, curr_frame);
  hamm->render(mode, curr_keyframe, curr_frame);

  floor->render();
  walls->render();
  ceiling->render();
  bulb->render();
}

void View::interpolateCamera() {
  if (mode != 1)
    return;

  lights_state[0] = light_keyframes[curr_keyframe + 1].x;
  lights_state[1] = light_keyframes[curr_keyframe + 1].y;
  lights_state[2] = light_keyframes[curr_keyframe + 1].z;

  glm::vec3 c_pos_vec = (1.0f / 120) * c_pos_keyframes[curr_keyframe + 1];
  c_xpos += c_pos_vec.x;
  c_ypos += c_pos_vec.y;
  c_zpos += c_pos_vec.z;

  glm::quat q1(glm::vec3(0, 0, 0));
  glm::quat q2(c_rot_keyframes[curr_keyframe + 1]);

  glm::quat q_rot = glm::slerp(q1, q2, 1.0f / 120);
  glm::vec3 d_angles = glm::eulerAngles(q_rot);

  c_xrot += glm::degrees(d_angles.x);
  c_yrot += glm::degrees(d_angles.y);
  c_zrot += glm::degrees(d_angles.z);

  updateCamera();

  // c_rotation_matrix = glm::mat4_cast(q_rot) * c_rotation_matrix;

  // glm::vec4 c_pos = glm::vec4(c_xpos, c_ypos, c_zpos, 1.0) * c_rotation_matrix;
  // glm::vec4 c_up = glm::vec4(c_up_x, c_up_y, c_up_z, 1.0) * c_rotation_matrix;

  // // Creating the lookAt matrix
  // glm::mat4 lookat_matrix = glm::lookAt(glm::vec3(c_pos), glm::vec3(0.0), glm::vec3(c_up));
  // view_matrix = projection_matrix * lookat_matrix;
}

void View::updateCamera() {
  // Creating the lookAt and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  glm::vec4 c_pos = glm::vec4(c_xpos, c_ypos, c_zpos, 1.0) * c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x, c_up_y, c_up_z, 1.0) * c_rotation_matrix;

  // Creating the lookAt matrix
  glm::mat4 lookat_matrix = glm::lookAt(glm::vec3(c_pos), glm::vec3(0.0), glm::vec3(c_up));

  // creating the projection matrix
  if (enable_perspective)
    projection_matrix = glm::frustum(-half_width / 4, half_width / 4, -half_height / 4, half_height / 4, 100.0f, -half_depth);
    // projection_matrix = glm::perspective(glm::radians(90.0f), 1.0f, 50.0f, 250.0f);
  else
    projection_matrix = glm::ortho(-half_width, half_width,
                            -half_height, half_height,
                            -half_depth, half_depth);

  view_matrix = projection_matrix * lookat_matrix;
}

void View::rotateCamera(GLuint axis, GLfloat angle) {
  switch (axis) {
    case 0:
      // X axis
      c_xrot += angle;
      break;
    case 1:
      // Y axis
      c_yrot += angle;
      break;
    case 2:
      // Z axis
      c_zrot += angle;
      break;
  }

  updateCamera();
}

void View::translateCamera(GLuint axis, GLfloat d) {
  switch (axis) {
    case 0:
      // X axis
      c_xpos += d;
      break;
    case 1:
      // Y axis
      c_ypos += d;
      break;
    case 2:
      // Z axis
      c_zpos += d;
      break;
  }

  updateCamera();
}

void View::toggleLight(int light_id) {
  if (light_id < 0 || light_id > 2)
    return;
  lights_state[light_id] = !lights_state[light_id];
}

void View::selectModel(int model_id) {
  curr_selected_model = model_id;
}

void View::rotateNode(GLuint axis, GLfloat angle) {
  switch (curr_selected_model) {
    case 0:
      // Buzz Light-year
      buzz->rotate(axis, angle);
      break;
    case 1:
      // Hamm
      hamm->rotate(axis, angle);
  }
}

void View::translateNode(GLuint axis, GLfloat d) {
  switch (curr_selected_model) {
    case 0:
      // Buzz Light-year
      buzz->translate(axis, d);
      break;
    case 1:
      // Hamm
      hamm->translate(axis, d);
  }
}

void View::selectNode(int node_id) {
  switch (curr_selected_model) {
    case 0:
      // Buzz Light-year
      buzz->selectNode(node_id);
      break;
    case 1:
      // Hamm
      hamm->selectNode(node_id);
  }
}

void View::zoom(GLfloat amount) {
  // c_zpos -= amount

  glm::vec3 d = amount * glm::normalize(glm::vec3(c_xpos, c_ypos, c_zpos));
  c_xpos -= d.x;
  c_ypos -= d.y;
  c_zpos -= d.z;

  updateCamera();
}

void View::toggleMode() {
  mode = !mode;
}

void View::saveKeyframe() {
  if (mode != 0)
    return;

  std::string file_name = "keyframes.txt";

  std::fstream key_file;
  key_file.open(file_name, std::ios::out | std::ios::app);

  if (!key_file.is_open()) {
    std::cout << "could not open keyframes.txt\n";
    return;
  }

  saveCameraKeyframe(key_file);
  buzz->saveKeyframe(key_file);
  hamm->saveKeyframe(key_file);

  key_file << "\n";

  key_file.close();
  std::cout << "keyframe saved!\n";
}

void View::loadKeyframes() {
  if (mode != 0)
    return;

  std::string file_name = "keyframes.txt";

  std::fstream key_file;
  key_file.open(file_name);

  if (!key_file.is_open()) {
    std::cout << "could not open keyframes.txt\n";
    return;
  }

  num_keyframes = 0;

  while (1) {
    loadCameraKeyframes(key_file);
    buzz->loadKeyframe(key_file);
    hamm->loadKeyframe(key_file);

    if (key_file.eof()) break;
    num_keyframes++;
  }

  curr_keyframe = 0;
  curr_frame = 0;

  std::cout << "num_keyframes: " << num_keyframes << "\n";

  key_file.close();

  std::cout << "keyframes loaded!\n";
}

void View::saveCameraKeyframe(std::fstream &key_file) {
  // save light state
  key_file << lights_state[0] << " "
           << lights_state[1] << " "
           << lights_state[2] << " ";

  // camera position
  key_file << (c_xpos - last_c_pos.x) << " "
           << (c_ypos - last_c_pos.y) << " "
           << (c_zpos - last_c_pos.z) << " ";
  last_c_pos = glm::vec3(c_xpos, c_ypos, c_zpos);

  // camera rotation
  key_file << glm::radians(c_xrot - last_c_rot.x) << " "
           << glm::radians(c_yrot - last_c_rot.y) << " "
           << glm::radians(c_zrot - last_c_rot.z) << " ";
  last_c_rot = glm::vec3(c_xrot, c_yrot, c_zrot);
}

void View::loadCameraKeyframes(std::fstream &key_file) {
  GLuint l1 = 0, l2 = 0, l3 = 0;
  key_file >> l1 >> l2 >> l3;
  light_keyframes.push_back(glm::vec3(l1, l2, l3));

  GLfloat x = 0, y = 0, z = 0;
  key_file >> x >> y >> z;
  c_pos_keyframes.push_back(glm::vec3(x, y, z));

  key_file >> x >> y >> z;
  c_rot_keyframes.push_back(glm::vec3(x, y, z));
}

void View::reset() {
  hamm->reset();
  buzz->reset();
}