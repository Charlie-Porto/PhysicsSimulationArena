#ifndef rigid_body_component_cpp
#define rigid_body_component_cpp

#include <string>
#include <unordered_map>

namespace pce {

struct RigidBody {
  std::string type_name;
  double mass;
  std::unordered_map<std::string, double> parameters;
};

}

#endif /* rigid_body_component_cpp */
