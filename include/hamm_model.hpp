#ifndef HAMM_MODEL_HPP_
#define HAMM_MODEL_HPP_

class HammHead : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (float)(PI/2 + PI/3), glm::vec3(0.0f, 0.0f, 1.0f));

    local_matrix = glm::rotate(glm::mat4(1.0f), -(float)PI/2, glm::vec3(0.0f, 1.0f, 0.0f)) * rotate * scale;
    updateModelMatrix(local_matrix, false);

    glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 100.0f, 300.0f));
    initial_matrix = translate;
    updateModelMatrix(initial_matrix);
  }

 public:
  HammHead(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/hamm/head.bmp", 256, 256);
    data = sphere(150, 30, 30);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -50.0; xrot_limits[1] = 70.0;
    yrot_limits[0] = -70.0; yrot_limits[1] = 70.0;
    zrot_limits[0] = -70.0; zrot_limits[1] = 70.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class HammTorso : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.3f));

    local_matrix = scale;
    updateModelMatrix(local_matrix, false);

    glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(450.0f, -210.0f, -100.0f));
    initial_matrix = translate * glm::scale(glm::mat4(1.0f), 0.7f * glm::vec3(1.0f, 1.0f, 1.0f));
    updateModelMatrix(initial_matrix);
  }

 public:
  HammTorso(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/hamm/pink.bmp", 256, 256);
    data = sphere(250, 30, 30);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    // xrot_limits[0] = -1000.0; xrot_limits[1] = 1000.0;
    yrot_limits[0] = -100.0; yrot_limits[1] = 100.0;
    // zrot_limits[0] = -1000.0; zrot_limits[1] = 1000.0;

    translatable = true;

    populateBuffers();
    setInitialTransformation();
  }

  void rotate(GLuint axis, GLfloat angle) {
    if (axis == 1) {
      Node::rotate(axis, angle);
      yrot_limits[0] -= 1.0;
      yrot_limits[1] += 1.0;
    }
  }
};

class HammNose : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    local_matrix = scale;
    updateModelMatrix(local_matrix, false);

    glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 100.0f, 0.0f));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (float)PI/2, glm::vec3(1.0f, 0.0f, 0.0f));
    initial_matrix = rotate * translate;
    updateModelMatrix(initial_matrix);
  }

 public:
  HammNose(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/hamm/pink.bmp", 256, 256);
    data = cylinder(100, 50, 100);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    // xrot_limits[0] = -50.0; xrot_limits[1] = 30.0;
    // yrot_limits[0] = -70.0; yrot_limits[1] = 70.0;
    // zrot_limits[0] = -50.0; zrot_limits[1] = 50.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class HammLeg : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

    local_matrix = scale;
    updateModelMatrix(local_matrix, false);
  }

 public:
  HammLeg(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/hamm/pink.bmp", 256, 256);
    data = cylinder(40, 30, 150);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -50.0; xrot_limits[1] = 50.0;
    yrot_limits[0] = -70.0; yrot_limits[1] = 70.0;
    zrot_limits[0] = -50.0; zrot_limits[1] = 50.0;

    populateBuffers();
    setInitialTransformation();

    glm::mat4 t = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, -260.0f, 0.0f));
    glm::mat4 rz;
    glm::mat4 rx;
    glm::mat4 r;

    switch (id) {
      case 3:
        // front left
        rz = glm::rotate(glm::mat4(1.0f), (float)PI, glm::vec3(0.0f, 0.0f, 1.0f));
        rx = glm::rotate(glm::mat4(1.0f), -(float)PI/4, glm::vec3(1.0f, 0.0f, 0.0f));
        r = glm::rotate(glm::mat4(1.0f), (float)PI/8, glm::vec3(0.0f, 1.0f, 1.0f));
        initial_matrix = r * rx * t * rz;
        updateModelMatrix(initial_matrix);
        break;
      case 4:
        // front right
        rz = glm::rotate(glm::mat4(1.0f), -(float)PI, glm::vec3(0.0f, 0.0f, 1.0f));
        rx = glm::rotate(glm::mat4(1.0f), -(float)PI/4, glm::vec3(1.0f, 0.0f, 0.0f));
        r = glm::rotate(glm::mat4(1.0f), -(float)PI/8, glm::vec3(0.0f, 1.0f, 1.0f));
        initial_matrix = r * rx * t * rz;
        updateModelMatrix(initial_matrix);
        break;
      case 5:
        // back left
        rz = glm::rotate(glm::mat4(1.0f), (float)PI, glm::vec3(0.0f, 0.0f, 1.0f));
        rx = glm::rotate(glm::mat4(1.0f), (float)PI/4, glm::vec3(1.0f, 0.0f, 0.0f));
        r = glm::rotate(glm::mat4(1.0f), (float)PI/8, glm::vec3(0.0f, 1.0f, -1.0f));
        initial_matrix = r * rx * t * rz;
        updateModelMatrix(initial_matrix);
        break;
      case 6:
        // back right
        rz = glm::rotate(glm::mat4(1.0f), -(float)PI, glm::vec3(0.0f, 0.0f, 1.0f));
        rx = glm::rotate(glm::mat4(1.0f), (float)PI/4, glm::vec3(1.0f, 0.0f, 0.0f));
        r = glm::rotate(glm::mat4(1.0f), -(float)PI/8, glm::vec3(0.0f, 1.0f, -1.0f));
        initial_matrix = r * rx * t * rz;
        updateModelMatrix(initial_matrix);
        break;
    }
  }
};

class Hamm {
  Node *head;
  Node *torso;
  Node *nose;

  Node *leg_fl;
  Node *leg_fr;
  Node *leg_bl;
  Node *leg_br;

  int curr_selected_node;
 public:
  explicit Hamm(GLuint shaderProgram) {
    torso = new HammTorso("hamm_torso", 0, shaderProgram, NULL);
    head = new HammHead("hamm_head", 1, shaderProgram, torso);
    nose = new HammNose("hamm_nose", 2, shaderProgram, head);

    leg_fl = new HammLeg("hamm_leg", 3, shaderProgram, torso);
    leg_fr = new HammLeg("hamm_leg", 4, shaderProgram, torso);
    leg_bl = new HammLeg("hamm_leg", 5, shaderProgram, torso);
    leg_br = new HammLeg("hamm_leg", 6, shaderProgram, torso);

    torso->addChild(head);
    torso->addChild(leg_fl);
    torso->addChild(leg_fr);
    torso->addChild(leg_bl);
    torso->addChild(leg_br);

    head->addChild(nose);

    curr_selected_node = 0;
  }

  void render(int mode = 0, int curr_keyframe = 0, int curr_frame = 0) {
    torso->render(mode, curr_keyframe, curr_frame);
  }

  void rotate(GLuint axis, GLfloat angle) {
    switch (curr_selected_node) {
      case 0:
        torso->rotate(axis, angle);
        break;
      case 1:
        head->rotate(axis, angle);
        break;

      case 3:
        leg_fl->rotate(axis, angle);
        break;
      case 4:
        leg_fr->rotate(axis, angle);
        break;
      case 5:
        leg_bl->rotate(axis, angle);
        break;
      case 6:
        leg_br->rotate(axis, angle);
        break;
    }
  }

  void translate(GLuint axis, GLfloat d) {
    torso->translate(axis, d);
  }

  void selectNode(int nodeId) {
    curr_selected_node = nodeId;
  }

  void saveKeyframe(std::fstream &key_file) {
    torso->saveKeyframe(key_file);
  }

  void loadKeyframe(std::fstream &key_file) {
    torso->loadKeyframe(key_file);
  }

  void reset() {
    torso->reset();
  }
};

#endif  // HAMM_MODEL_HPP_