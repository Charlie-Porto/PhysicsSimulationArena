#ifndef RenderSystem_cpp
#define RenderSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
system to render on-screen objects
-----------------------------------------------------------------*/

#include <ezprint.cpp>
#include <triangle_raster_functions.cpp>

#include "subsystems/squareDrawingFunctions.cpp"
#include "../System.cpp"

extern ControlPanel control;

namespace pce{
class RenderSystem : public ISystem {
public:

void RenderPlatform() {
  Entity vertex_a = 0;
  Entity vertex_b = 1;
  Entity vertex_c = 2;
  Entity vertex_d = 3;

  auto const& position_a = control.GetComponent<pce::Radar>(vertex_a);
  auto const& position_b = control.GetComponent<pce::Radar>(vertex_b);
  auto const& position_c = control.GetComponent<pce::Radar>(vertex_c);
  auto const& position_d = control.GetComponent<pce::Radar>(vertex_d);

  const std::vector<glm::dvec2> quad_vertices = {
    position_a.hitpoint_corresponding_pixel,
    position_b.hitpoint_corresponding_pixel,
    position_c.hitpoint_corresponding_pixel,
    position_d.hitpoint_corresponding_pixel
  };

  pce::draw::drawQuadrilateral(quad_vertices, platform_color_);
  pce::draw::drawFilledQuadrilateral(quad_vertices, platform_color_);
  
}


void UpdateEntities() {
  for (auto const& entity : entities) {

  }
}

private:
  std::vector<int> platform_color_ = {255, 255, 255, 255};
};
}
#endif /* RenderSystem_cpp */
