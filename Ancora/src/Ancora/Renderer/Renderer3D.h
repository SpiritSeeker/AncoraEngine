#pragma once

#include "PerspectiveCamera.h"

namespace Ancora {

  class Renderer3D
  {
  public:
    static void Init();
    static void Shutdown();

    static void BeginScene(const PerspectiveCamera& camera);
    static void EndScene();

    static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
  };

}
