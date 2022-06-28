#ifndef CameraOperatorSystem_cpp
#define CameraOperatorSystem_cpp

/*----------------------------------------------------------------|
--------------------- Module Description -------------------------|
Camera Operator System: manages the camera
-----------------------------------------------------------------*/

#include <ezprint.cpp>
#include <vezprint.cpp>
#include <observation_camera.cpp>
#include <camera_functions.cpp>
#include <virtual_keyboard.cpp>


#include "cameraOperatorFunctions.cpp"
#include "../System.cpp"

extern ControlPanel control;

namespace pce{
class CameraOperatorSystem : public ISystem {
public:
  CameraOperatorSystem (){
  }
  
  void Init() {
    camera_.position = glm::dvec3(0, 0, 0);
    camera_.view_direction = normalize(glm::dvec3(0, -1, 1));
    camera_.zoom_index = 1.0;
    camera_.xz_angle = 0.0;
    camera_.y_angle = 0.0;
    camera_.xz_circle_radius = 1.0;
    camera_.rotation_versor = {1.0, 0.0, 0.0, 0.0};
    camera_.transformation_vector = {0, 0, 0};

    keyboard_ = VirtualKeyboard();
  }


  const glm::dquat ProvideCamVersor() const {
    return camera_.rotation_versor;
  }
  const glm::dvec3 ProvideCamTransformVector() const {
    return -camera_.position;
  }
  const glm::dvec3 ProvideCamPosition() const {
    return camera_.position;
  }


  
void UpdateCamera() {
  pce::cam_op::updateCameraPositionOriginFocus(camera_, keyboard_);
}
    

private:
  ObservationCamera camera_;
  VirtualKeyboard keyboard_;
  

};
}
#endif /* CameraOperatorSystem_cpp */
