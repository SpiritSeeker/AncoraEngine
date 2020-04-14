#pragma once

#include "PerspectiveCamera.h"
#include "Light.h"
#include "Texture.h"
#include "Model3D.h"

namespace Ancora {

  struct Renderer3DSceneData
  {
    Ref<PerspectiveCamera> Camera;
    Ref<DirectionalLight> DirLight;
  };

  class Renderer3D
  {
  public:
    static void Init();
    static void Shutdown();

    static void BeginScene(const Renderer3DSceneData& sceneData);
    static void EndScene();

    static void SkyBox(Ref<CubeMap> cubeMap, const glm::vec3& position, const glm::vec3& size);
    static void DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color);
  };

}
