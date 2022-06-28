
#ifndef SphereObjectFactory_cpp
#define SphereObjectFactory_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
factory class for making planet-like sphere entities.
-----------------------------------------------------------------*/
#include <ezprint.cpp>
#include <randomness_functions.cpp>

extern ControlPanel control; 

const double min_z = -200.0;
const double max_z = 0.0;
const double min_x = 0.0;
const double max_x = 200.0;
const double min_y = 0.0;
const double max_y = 200.0;
const double min_r = 5.0;
const double max_r = 20.0;


class SphereObjectFactory {
public:
  SphereObjectFactory() { ezp::print_item("creating SphereObjectFactory"); }


  glm::dvec3 GetRandomLocation() {
    const double z = -1.0 * get_rand_double_between_zero_and_input(min_z);
    const double x = get_rand_signed_double_between_two_doubles(min_x, max_x);
    const double y = get_rand_signed_double_between_two_doubles(min_y, max_y);
    const auto location = glm::dvec3(x, y, z);
    return location;
  }


  double GetRandomRadius() {
    const double rand_radius = get_rand_double_between_two_doubles(min_r, max_r);
    return rand_radius;
  }


  void MakeObjectAtLocation(const glm::dvec3& location) {
    const double new_object_radius = 1.0;
    Entity object = control.CreateEntity();
    control.AddComponent(object, pce::Position{
      .actual = location,
      .rotated = location
    });
    control.AddComponent(object, pce::Radar{});
    control.AddComponent(object, pce::Surface{
      .natural_color = {255, 255, 255, 255},
      .luminosity = 0.0,
    });
    objects_.push_back(object);
  }

private:
  std::vector<Entity> objects_;
};




#endif /* SphereObjectFactory_cpp */
