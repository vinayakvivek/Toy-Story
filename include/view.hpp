#ifndef VIEW_HPP_
#define VIEW_HPP_

#include "gl_framework.hpp"
#include "shader_util.hpp"
#include "buzz_model.hpp"
#include "hamm_model.hpp"
#include "models.hpp"

class View {
  // screen size
  GLfloat half_width;
  GLfloat half_height;
  GLfloat half_depth;

  GLuint shaderProgram;
  GLuint u_view_matrix;
  GLuint u_camera_position;
  GLuint u_light_positions;
  GLuint u_spotlight_position;
  GLuint u_lights_state;

  glm::mat4 projection_matrix;
  glm::mat4 c_rotation_matrix;
  glm::mat4 c_trans_matrix;
  glm::mat4 view_matrix;

  // Camera position and rotation Parameters
  GLfloat c_xpos, c_ypos, c_zpos;
  GLfloat c_up_x, c_up_y, c_up_z;
  GLfloat c_xrot, c_yrot, c_zrot;

  // Enable/Disable perspective view
  bool enable_perspective;

  glm::vec4 light_positions[2];
  glm::vec4 spotlight_position[2];
  GLuint lights_state[3];

  Buzz *buzz;
  Hamm *hamm;

  Floor *floor;
  Walls *walls;
  Ceiling *ceiling;
  Bulb *bulb;

  /**
   *  0 -> Buzz
   *  1 -> Hamm
   */
  int curr_selected_model;

  /**
   *  0 -> record mode
   *  1 -> play mode
   */
  int mode;
  int num_keyframes;
  int curr_keyframe;
  int curr_frame;

  std::vector<glm::vec3> c_rot_keyframes;
  std::vector<glm::vec3> c_pos_keyframes;
  std::vector<glm::vec3> light_keyframes;
  glm::vec3 last_c_rot;
  glm::vec3 last_c_pos;

  void initShadersGL();
 public:
  View(GLfloat h_width, GLfloat h_height, GLfloat h_depth);
  void rotateCamera(GLuint axis, GLfloat angle);
  void translateCamera(GLuint axis, GLfloat d);
  void zoom(GLfloat amount);
  void updateCamera();
  void interpolateCamera();
  void renderGL();

  void toggleLight(int light_id);
  void selectModel(int model_id);
  void rotateNode(GLuint axis, GLfloat angle);
  void translateNode(GLuint axis, GLfloat d);
  void selectNode(int node_id);

  void togglePerspective();
  void updateView(GLfloat h_width, GLfloat h_height);

  void toggleMode();
  void saveKeyframe();
  void saveCameraKeyframe(std::fstream &key_file);
  void loadKeyframes();
  void loadCameraKeyframes(std::fstream &key_file);
};

#endif  // VIEW_HPP_
