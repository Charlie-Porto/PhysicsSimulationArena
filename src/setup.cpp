#ifndef setup_cpp
#define setup_cpp

#include "ecs/ControlPanel.cpp"
#include <ezprint.cpp>

#include "ecs/components/position_component.cpp"
#include "ecs/components/radar_component.cpp"
#include "ecs/components/orientation_component.cpp"
#include "ecs/components/surface_component.cpp"

/* systems */
// #include "ecs/systems/PlayerMovementSystem.cpp"
#include "ecs/systems/CameraOperatorSystem.cpp"
#include "ecs/systems/ObjectPositionTransformerSystem.cpp"
#include "ecs/systems/RadarSystem.cpp"
#include "ecs/systems/RenderSystem.cpp"

/* other */
#include "ecs/entity_factories/AxisGenerator.cpp"
#include "ecs/entity_factories/PlatformManager.cpp"

extern ControlPanel control;

class EcsManager {
public: 

  void DoComponentRegistration() {
    control.RegisterComponent<pce::Position>();
    control.RegisterComponent<pce::Radar>();
    control.RegisterComponent<pce::Orientation>();
    control.RegisterComponent<pce::Surface>();
  }


  void PerformSystemSetup(){
    camera_operator_system_ = control.RegisterSystem<pce::CameraOperatorSystem>();
    Signature camera_sig;
    camera_sig.set(control.GetComponentType<pce::Orientation>());
    control.SetSystemSignature<pce::CameraOperatorSystem>(camera_sig);
    camera_operator_system_->Init();

    position_transform_system_ = control.RegisterSystem<pce::ObjectPositionTransformerSystem>();
    Signature position_transform_sig;
    position_transform_sig.set(control.GetComponentType<pce::Position>());
    control.SetSystemSignature<pce::ObjectPositionTransformerSystem>(position_transform_sig);

    radar_system_ = control.RegisterSystem<pce::RadarSystem>();
    Signature radar_sig;
    radar_sig.set(control.GetComponentType<pce::Position>());
    radar_sig.set(control.GetComponentType<pce::Radar>());
    control.SetSystemSignature<pce::RadarSystem>(radar_sig);

    render_system_ = control.RegisterSystem<pce::RenderSystem>();
    Signature render_sig;
    render_sig.set(control.GetComponentType<pce::Radar>());
    control.SetSystemSignature<pce::RenderSystem>(render_sig);

    platform_manager_ = PlatformManager();
    platform_manager_.Init();

    axis_generator_ = AxisGenerator();
    axis_generator_.BuildXAxis();
    axis_generator_.BuildYAxis();
    axis_generator_.BuildZAxis();
  }


  void UpdateSystems(double time) {
    camera_operator_system_->UpdateCamera();
    auto cam_pos = camera_operator_system_->ProvideCamPosition();
    auto cam_tvec = camera_operator_system_->ProvideCamTransformVector();
    auto cam_versor = camera_operator_system_->ProvideCamVersor();

    position_transform_system_->UpdateEntities(cam_tvec, cam_versor, cam_pos);
    radar_system_->UpdateEntities();
    render_system_->RenderPlatform();
  }



private:
  // add all systems
  std::shared_ptr<pce::CameraOperatorSystem> camera_operator_system_;
  std::shared_ptr<pce::ObjectPositionTransformerSystem> position_transform_system_;
  std::shared_ptr<pce::RadarSystem> radar_system_;
  std::shared_ptr<pce::RenderSystem> render_system_;
  
  // other 
  AxisGenerator axis_generator_;
  PlatformManager platform_manager_;
  

};


#endif /* setup_cpp */
