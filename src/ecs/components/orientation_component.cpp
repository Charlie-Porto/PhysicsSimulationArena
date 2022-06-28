#ifndef orientation_component_cpp
#define orientation_component_cpp

#include <glm/ext/quaternion_double.hpp>

namespace pce {

struct Orientation {
  glm::dquat rotation_versor;
};

}

#endif /* orientation_component_cpp */
