#ifndef surface_component_cpp
#define surface_component_cpp

#include <vector>

namespace pce {

struct Surface {
  std::vector<int> natural_color;
  double luminosity;
  double reflectiveness;
  double transparency;
};

}

#endif /* surface_component_cpp */
