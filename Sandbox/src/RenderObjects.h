#pragma once
#include "GB.h"

using namespace GB;

class SceneRender : Layer
{
public:
  virtual void OnAttach() override;
  virtual void OnDetach() override;
  virtual void OnUpdate() override;
  virtual void OnEvent(Event& e) override;

  virtual void OnImguiRender() override;

};

