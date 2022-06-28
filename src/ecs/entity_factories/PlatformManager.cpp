#ifndef PlatformManager_cpp
#define PlatformManager_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|

-----------------------------------------------------------------*/

#include <vector>
#include <glm/vec3.hpp>
#include <ezprint.cpp>
#include "../../constants/static_variables.cpp"
#include "BasicObjectFactory.cpp"

class PlatformManager {
public:
  
  void Init() {
    object_factory_ = BasicObjectFactory();
    vertices_ = {
      glm::dvec3(global_const::platform_length, global_const::platform_height, global_const::platform_width),
      glm::dvec3(global_const::platform_length, global_const::platform_height, -global_const::platform_width),
      glm::dvec3(-global_const::platform_length, global_const::platform_height, -global_const::platform_width),
      glm::dvec3(-global_const::platform_length, global_const::platform_height, global_const::platform_width)
    };
    for (auto const vertex : vertices_) {
      object_factory_.MakePointObjectAtLocation(vertex);
    }
  }

private:
  std::vector<glm::dvec3> vertices_;
  BasicObjectFactory object_factory_;


};



#endif /* PlatformManager_cpp */
