#ifndef observation_camera_cpp
#define observation_camera_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
camera struct that resembles view from stadium seat, or sum' like that. 
-----------------------------------------------------------------*/

#include <glm/vec3.hpp>
#include <glm/ext/quaternion_double.hpp> 
#include <ezprint.cpp>

namespace pce {
struct ObservationCamera {
  glm::dvec3 position;  
  glm::dvec3 view_direction;
  glm::dvec3 focus_point;
  double position_scalar;
  double zoom_index;
  double xz_angle;
  double y_angle;
  double xz_circle_radius;
  glm::dquat rotation_versor;
  glm::dvec3 transformation_vector;
};
}



#endif /* observation_camera_cpp */
