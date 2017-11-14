#ifndef BUZZ_HPP_
#define BUZZ_HPP_

#include "node.hpp"
#include "texture_util.hpp"

class BuzzHead : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), 0.25f * glm::vec3(1.0f, 1.3, 1.0f));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (float)PI/2, glm::vec3(0.0f, 1.0f, 0.0f));
    rotate = glm::rotate(rotate, (float)PI, glm::vec3(1.0f, 0.0f, 0.0f));

    local_matrix *= rotate * scale;
    updateModelMatrix(local_matrix);

    glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 200 * 1.3 * 0.25 + 20.0f, 0.0f));
    initial_matrix = translate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzHead(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/face3.bmp", 256, 570);
    data = sphere(200, 30, 30);
    pivot_point = glm::vec4(0.0, 200.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    // xrot_limits[0] = -50.0; xrot_limits[1] = 30.0;
    // yrot_limits[0] = -70.0; yrot_limits[1] = 70.0;
    // zrot_limits[0] = -50.0; zrot_limits[1] = 50.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class BuzzNeck : public Node {
  void setInitialTransformation() {
    glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 130.0f, 0.0f));
    initial_matrix = translate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzNeck(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/face3.bmp", 256, 570);
    data = cylinder(30, 30, 40);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -50.0; xrot_limits[1] = 30.0;
    yrot_limits[0] = -70.0; yrot_limits[1] = 70.0;
    zrot_limits[0] = -50.0; zrot_limits[1] = 50.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class BuzzTorso : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.4f, 1.0f, 0.7f));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (float)PI, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 translate = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 70.0f, 0.0f));

    local_matrix *= scale * rotate;
    updateModelMatrix(local_matrix);

    initial_matrix = translate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzTorso(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/suit3.bmp", 1024, 330);
    data = cylinder(60, 100, 150);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -70.0; xrot_limits[1] = 80.0;
    yrot_limits[0] = -50.0; yrot_limits[1] = 50.0;
    zrot_limits[0] = -50.0; zrot_limits[1] = 50.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class BuzzHip : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.4f, 1.0f, 0.7f));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (float)PI, glm::vec3(0.0f, 1.0f, 0.0f));

    local_matrix *= scale * rotate;
    updateModelMatrix(local_matrix);

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -100.0f, 0.0f));
    initial_matrix = translate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzHip(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/hip.bmp", 768, 256);
    data = cylinder(60, 60, 70);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    // xrot_limits[0] = -70.0; xrot_limits[1] = 80.0;
    yrot_limits[0] = -90.0; yrot_limits[1] = 90.0;
    // zrot_limits[0] = -50.0; zrot_limits[1] = 50.0;

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

class BuzzLeftUpperArm : public Node {
  void setInitialTransformation() {
    local_matrix = glm::rotate(glm::mat4(1.0f), -(float)PI/2, glm::vec3(0.0f, 1.0f, 0.0f));
    updateModelMatrix(local_matrix);

    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (float)PI, glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(120.0f, 130.0f, 0.0f));

    initial_matrix = translate * rotate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzLeftUpperArm(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/left_hand.bmp", 1024, 1024);
    data = cylinder(30, 20, 150);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -0.0; xrot_limits[1] = 180.0;
    yrot_limits[0] = -0.0; yrot_limits[1] = 150.0;
    zrot_limits[0] = -180.0; zrot_limits[1] = 40.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class BuzzRightUpperArm : public Node {
  void setInitialTransformation() {
    local_matrix = glm::rotate(glm::mat4(1.0f), (float)PI/2, glm::vec3(0.0f, 1.0f, 0.0f));
    updateModelMatrix(local_matrix);

    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (float)PI, glm::vec3(1.0f, 0.0f, 0.0f));
    // rotate = glm::rotate(rotate, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-120.0f, 130.0f, 0.0f));


    initial_matrix = translate * rotate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzRightUpperArm(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/right_hand.bmp", 1024, 1024);
    data = cylinder(30, 20, 150);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -0.0; xrot_limits[1] = 180.0;
    yrot_limits[0] = -150.0; yrot_limits[1] = 0.0;
    zrot_limits[0] = -40.0; zrot_limits[1] = 180.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class BuzzLowerArm : public Node {
  void setInitialTransformation() {
    local_matrix = glm::rotate(glm::mat4(1.0f), (float)PI, glm::vec3(0.0f, 1.0f, 0.0f));
    updateModelMatrix(local_matrix);

    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 150.0f, 0.0f));
    initial_matrix = translate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzLowerArm(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/right_lower_hand.bmp", 1024, 1024);
    data = cylinder(20, 15, 130);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -150.0; xrot_limits[1] = 5.0;

    int parent_id = parent->getId();
    if (parent_id == 3) {
      // parent is left_upper_arm
      yrot_limits[0] = -0.0; yrot_limits[1] = 150.0;
    } else if (parent_id == 6) {
      // parent is right_upper_arm
      yrot_limits[0] = -150.0; yrot_limits[1] = 0.0;
    }

    zrot_limits[0] = -0.0; zrot_limits[1] = 0.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class BuzzHand : public Node {
  void setInitialTransformation() {
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 130.0f, 0.0f));
    initial_matrix = translate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzHand(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/palm.bmp", 256, 256);
    data = cuboid(10, 20, 40);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -90.0; xrot_limits[1] = 80.0;
    yrot_limits[0] = -0.0; yrot_limits[1] = 0.0;
    zrot_limits[0] = -0.0; zrot_limits[1] = 0.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class BuzzLeftThigh : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(40.0f, 0.0f, 0.0f));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (float)PI, glm::vec3(0.0f, 1.0f, 0.0f));
    rotate = glm::rotate(rotate, (float)PI, glm::vec3(1.0f, 0.0f, 0.0f));

    initial_matrix = translate * scale * rotate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzLeftThigh(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/thigh.bmp", 1024, 1024);
    data = cylinder(40, 30, 150);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -50.0; xrot_limits[1] = 80.0;
    yrot_limits[0] = -30.0; yrot_limits[1] = 30.0;
    zrot_limits[0] = -0.0; zrot_limits[1] = 80.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class BuzzRightThigh : public Node {
  void setInitialTransformation() {
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-40.0f, 0.0f, 0.0f));
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), (float)PI, glm::vec3(0.0f, 1.0f, 0.0f));
    rotate = glm::rotate(rotate, (float)PI, glm::vec3(1.0f, 0.0f, 0.0f));

    initial_matrix = translate * scale * rotate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzRightThigh(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/thigh.bmp", 1024, 1024);
    data = cylinder(40, 30, 150);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -50.0; xrot_limits[1] = 80.0;
    yrot_limits[0] = -30.0; yrot_limits[1] = 30.0;
    zrot_limits[0] = -80.0; zrot_limits[1] = 0.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class BuzzLeg : public Node {
  void setInitialTransformation() {
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 150.0f, 0.0f));
    initial_matrix = translate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzLeg(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/leg.bmp", 1024, 1024);
    data = cylinder(30, 40, 150);
    pivot_point = glm::vec4(0.0, 0.0, 0.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -80.0; xrot_limits[1] = 0.0;
    yrot_limits[0] = -0.0; yrot_limits[1] = 0.0;
    zrot_limits[0] = -0.0; zrot_limits[1] = 0.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class BuzzFoot : public Node {
  void setInitialTransformation() {
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 150.0f, 15.0f));
    initial_matrix = translate;
    updateModelMatrix(initial_matrix);
  }

 public:
  BuzzFoot(
    std::string name,
    int id,
    const GLuint &shaderProgram,
    Node *parent): Node(name, id, shaderProgram, parent) {

    tex = LoadTexture("../images/buzz/palm.bmp", 256, 256);
    data = cuboid(32, 40, 15);
    pivot_point = glm::vec4(0.0, 0.0, -20.0, 1.0);
    // std::cout << "num_vertices: " << data->num_vertices << "\n";

    xrot_limits[0] = -10.0; xrot_limits[1] = 40.0;
    yrot_limits[0] = -0.0; yrot_limits[1] = 0.0;
    zrot_limits[0] = -5.0; zrot_limits[1] = 5.0;

    populateBuffers();
    setInitialTransformation();
  }
};

class Buzz {
  Node *head;
  Node *torso;

  Node *neck;
  Node *hip;

  Node *left_upper_arm;
  Node *left_lower_arm;
  Node *left_hand;

  Node *right_upper_arm;
  Node *right_lower_arm;
  Node *right_hand;

  Node *left_thigh;
  Node *left_leg;
  Node *left_foot;

  Node *right_thigh;
  Node *right_leg;
  Node *right_foot;

  int curr_selected_node;
 public:
  explicit Buzz(GLuint shaderProgram) {
    hip = new BuzzHip("buzz_hip", 0, shaderProgram, NULL);
    torso = new BuzzTorso("buzz_torso", 1, shaderProgram, hip);

    neck = new BuzzNeck("buzz_neck", 2, shaderProgram, torso);
    head = new BuzzHead("buzz_head", 9, shaderProgram, neck);

    left_upper_arm = new BuzzLeftUpperArm("buzz_left_upper_arm", 3, shaderProgram, torso);
    left_lower_arm = new BuzzLowerArm("buzz_left_lower_arm", 4, shaderProgram, left_upper_arm);
    left_hand = new BuzzHand("buzz_left_hand", 5, shaderProgram, left_lower_arm);

    right_upper_arm = new BuzzRightUpperArm("buzz_right_upper_arm", 6, shaderProgram, torso);
    right_lower_arm = new BuzzLowerArm("buzz_right_lower_arm", 7, shaderProgram, right_upper_arm);
    right_hand = new BuzzHand("buzz_right_hand", 8, shaderProgram, right_lower_arm);

    left_thigh = new BuzzLeftThigh("buzz_left_thigh", 10, shaderProgram, hip);
    left_leg = new BuzzLeg("buzz_left_leg", 11, shaderProgram, left_thigh);
    left_foot = new BuzzFoot("buzz_left_foot", 14, shaderProgram, left_leg);

    right_thigh = new BuzzRightThigh("buzz_right_thigh", 12, shaderProgram, hip);
    right_leg = new BuzzLeg("buzz_right_leg", 13, shaderProgram, right_thigh);
    right_foot = new BuzzFoot("buzz_right_foot", 15, shaderProgram, right_leg);

    hip->addChild(torso);
    hip->addChild(left_thigh);
    hip->addChild(right_thigh);
    neck->addChild(head);

    torso->addChild(neck);
    torso->addChild(left_upper_arm);
    torso->addChild(right_upper_arm);

    left_upper_arm->addChild(left_lower_arm);
    left_lower_arm->addChild(left_hand);

    right_upper_arm->addChild(right_lower_arm);
    right_lower_arm->addChild(right_hand);

    left_thigh->addChild(left_leg);
    left_leg->addChild(left_foot);

    right_thigh->addChild(right_leg);
    right_leg->addChild(right_foot);

    curr_selected_node = 0;

    setInitialPose();
  }

  void render(int mode = 0, int curr_keyframe = 0, int curr_frame = 0) {
    hip->render(mode, curr_keyframe, curr_frame);
  }

  void setInitialPose() {
    left_upper_arm->rotate(1, 90.0f);
    left_upper_arm->rotate(0, 60.0f);
    left_lower_arm->rotate(0, -120.0f);

    right_upper_arm->rotate(1, -90.0f);
    right_upper_arm->rotate(0, 60.0f);
    right_lower_arm->rotate(0, -120.0f);

    left_thigh->rotate(0, 5.0f);
    left_thigh->rotate(2, 5.0f);
    left_leg->rotate(0, -5.0f);
    left_foot->rotate(2, -5.0f);

    right_thigh->rotate(0, 5.0f);
    right_thigh->rotate(2, -5.0f);
    right_leg->rotate(0, -5.0f);
    right_foot->rotate(2, 5.0f);
  }

  void rotate(GLuint axis, GLfloat angle) {
    switch (curr_selected_node) {
      case 0:
        hip->rotate(axis, angle);
        break;
      case 1:
        torso->rotate(axis, angle);
        break;
      case 2:
        neck->rotate(axis, angle);
        break;
      case 3:
        left_upper_arm->rotate(axis, angle);
        break;
      case 4:
        left_lower_arm->rotate(axis, angle);
        break;
      case 5:
        left_hand->rotate(axis, angle);
        break;
      case 6:
        right_upper_arm->rotate(axis, angle);
        break;
      case 7:
        right_lower_arm->rotate(axis, angle);
        break;
      case 8:
        right_hand->rotate(axis, angle);
        break;

      case 10:
        left_thigh->rotate(axis, angle);
        break;
      case 11:
        left_leg->rotate(axis, angle);
        break;

      case 12:
        right_thigh->rotate(axis, angle);
        break;
      case 13:
        right_leg->rotate(axis, angle);
        break;

      case 14:
        left_foot->rotate(axis, angle);
        break;
      case 15:
        right_foot->rotate(axis, angle);
        break;
    }
  }

  void translate(GLuint axis, GLfloat d) {
    hip->translate(axis, d);
  }

  void selectNode(int nodeId) {
    curr_selected_node = nodeId;
  }

  void saveKeyframe(std::fstream &key_file) {
    hip->saveKeyframe(key_file);
  }

  void loadKeyframe(std::fstream &key_file) {
    hip->loadKeyframe(key_file);
  }

  void reset() {
    hip->reset();
    setInitialPose();
  }
};

#endif  // BUZZ_HPP_
