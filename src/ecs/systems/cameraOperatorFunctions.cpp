#ifndef cameraOperatorFunctions_cpp
#define cameraOperatorFunctions_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
camera operation helper functions
-----------------------------------------------------------------*/

#include <cmath>

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/geometric.hpp>

#include <ezprint.cpp>
#include <vezprint.cpp>
#include <virtual_keyboard.cpp>
#include <camera.cpp>
#include <camera_functions.cpp>
#include <vector3_functions.cpp>
#include <math_objects/Plane.cpp>
#include <math_objects/LineParamEq.cpp>
#include <math_objects/LineVectorForm.cpp>

#include "../../constants/static_variables.cpp"

namespace pce {
namespace cam_op {

const double PI = 3.14159265;

// NOTE: SIGNS (+-) ARE VERY IMPORTANT IN THIS FUNCTION
void updateCameraReverseRotationVersor(ObservationCamera& camera, double rotation_direction) {
  const glm::dquat vert_rot_versor = rotation_direction * cam_func::getCameraVerticalRotationVersor(-camera.y_angle);
  const glm::dquat horiz_rot_versor = rotation_direction * cam_func::getCameraHorizontalRotationVersor(camera.xz_angle);
  camera.rotation_versor = horiz_rot_versor * vert_rot_versor;
}


void moveCameraFocusPointLateral(ObservationCamera& camera, const double& direction) {
  camera.xz_angle += global_const::hop_angle * direction;
  const double new_focus_xpos = camera.xz_circle_radius * sin(PI * camera.xz_angle/180.0) + camera.position.x;
  const double new_focus_zpos = camera.xz_circle_radius * cos(PI * camera.xz_angle/180.0) + camera.position.y;

  camera.focus_point.x = new_focus_xpos;
  camera.focus_point.z = new_focus_zpos;
  vezp::print_dvec3(camera.focus_point);
  updateCameraReverseRotationVersor(camera, -1.0);
}


void moveCameraFocusPointVertical(ObservationCamera& camera, const double& direction) {
  camera.y_angle += global_const::hop_angle * direction;
  const double new_focus_ypos = camera.position_scalar * sin(PI * camera.y_angle/180.0);
  const double new_camera_xz_radius = camera.position_scalar * cos(PI * camera.y_angle/180.0);

  camera.focus_point.y = new_focus_ypos;
  camera.xz_circle_radius = new_camera_xz_radius;
  vezp::print_dvec3(camera.focus_point);
  moveCameraFocusPointLateral(camera, 0.0);
}


void moveCameraPositionFrontBack(ObservationCamera& camera, const double& direction) {
  pce::math_objs::LineVectorForm meridian = vfunc::getVector3ThroughVector3s(
                                                camera.focus_point,
                                                camera.position);
  const glm::dvec3 point_adjustment = (glm::normalize(meridian.direction)
                                    * direction);
  // ezp::print_item("point adjustment: ");
  // vezp::print_dvec3(point_adjustment);
  camera.position += point_adjustment;
  camera.focus_point += point_adjustment;
}


void moveCameraPositionLeftRight(ObservationCamera& camera, const double& direction) {
  auto const normal_vect = glm::normalize(glm::dvec3(camera.position.z,
                                                     camera.position.y,
                                                    -camera.position.x))
                                                    * direction;
  camera.position += normal_vect;
  camera.focus_point += normal_vect;
  vezp::print_dvec3(camera.position);
}


void updateCameraXZAngle(ObservationCamera& camera, const double& direction) {
  if (direction != 0.0) {
    camera.xz_angle += global_const::hop_angle * direction;
  }
  const double new_camera_xpos = camera.xz_circle_radius * sin(PI * camera.xz_angle/180.0);
  const double new_camera_zpos = camera.xz_circle_radius * cos(PI * camera.xz_angle/180.0);

  camera.position.x = new_camera_xpos;
  camera.position.z = new_camera_zpos;

  vezp::print_dvec3(camera.position);
  updateCameraReverseRotationVersor(camera, 1.0);
}


void updateCameraYAngle(ObservationCamera& camera, const double& direction) {
  camera.y_angle += global_const::hop_angle * direction;
  const double new_camera_ypos = camera.position_scalar * sin(PI * camera.y_angle/180.0);
  const double new_camera_xz_radius = camera.position_scalar * cos(PI * camera.y_angle/180.0);

  camera.position.y = new_camera_ypos;
  camera.xz_circle_radius = new_camera_xz_radius;
  updateCameraXZAngle(camera, 0.0);
}


void updateCameraPositionScalar(ObservationCamera& camera, double direction) {
  camera.position_scalar += direction * global_const::movement_speed;
  updateCameraYAngle(camera, 0.0);
}


JoystickReport pollVirtualKeyboard(VirtualKeyboard& keyboard) {
  return keyboard.check_buttons();
}


void updateCameraPositionOriginFocus(ObservationCamera& camera, VirtualKeyboard& keyboard) {
  JoystickReport joystick_report = pollVirtualKeyboard(keyboard);
  if (joystick_report.R_pressed == true) { 
    ezp::print_item("JOYSTICK: RIGHT");
    updateCameraXZAngle(camera, 1.0);
  }
  if (joystick_report.L_pressed == true) {
    ezp::print_item("JOYSTICK: LEFT");
    updateCameraXZAngle(camera, -1.0);
  }
  if (joystick_report.Up_pressed == true) {
    ezp::print_item("JOYSTICK: UP");
    updateCameraYAngle(camera, 1.0);
  }
  if (joystick_report.Down_pressed == true) {
    ezp::print_item("JOYSTICK: DOWN");
    updateCameraYAngle(camera, -1.0);
  }
  if (joystick_report.W_pressed == true) {
    ezp::print_item("JOYSTICK: W");
    // if (camera.pov_scalar <= global_const::camera_inward_zoom_barrier + 10.0) {
      // ezp::print_item("NOT MOVING CLOSER: hit inward zoom barrier.");
    // } else {
    updateCameraPositionScalar(camera, -1.0);
    // }
  }
  if (joystick_report.S_pressed == true) {
    ezp::print_item("JOYSTICK: S");
    updateCameraPositionScalar(camera, 1.0);
  }
  if (joystick_report.X_pressed == true) {
    ezp::print_item("JOYSTICK: X");

  }
}





}
}


#endif /* cameraOperatorFunctions_cpp */
