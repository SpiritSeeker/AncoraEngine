#include "GameLevel.h"

// Initial setup
void GameLevel::Init(const Ancora::Ref<Ancora::PerspectiveCamera>& camera)
{
  // Load environment
  // (^) Make environment
  std::array<std::string, 6> textureFaces = {
    "Sandbox/assets/cubemaps/tears_of_steel/px.png",
    "Sandbox/assets/cubemaps/tears_of_steel/nx.png",
    "Sandbox/assets/cubemaps/tears_of_steel/py.png",
    "Sandbox/assets/cubemaps/tears_of_steel/ny.png",
    "Sandbox/assets/cubemaps/tears_of_steel/pz.png",
    "Sandbox/assets/cubemaps/tears_of_steel/nz.png"
  };

  m_CubeMap = Ancora::CubeMap::Create(textureFaces);

  // (#) Call LoadAssets for every object.
  // ($) m_Player.LoadAssets();

  // Load camera
  m_SceneData.Camera = camera;
}

void GameLevel::OnUpdate(Ancora::Timestep ts)
{
  // (#) Call OnUpdate for every object.
  // ($) m_Player.OnUpdate(ts);

  // (#) If the player collides with anything.
  // (#) All Collisions tests to be called here.
  // ($) if (CollisionTest())
  // {
  // }

  // (#) Check if player crossed finish line here.

}

void GameLevel::OnRender()
{
  Ancora::Renderer3D::BeginScene(m_SceneData);

  // Render the player
  // ($) m_Player.OnRender();

  // (#) Render other bikers

  // (#) Render other vehicles (if any)

  // (#) Render pedestrians (if any)

  // Render the road
  // ($) m_RoadMap.OnRender();

  // (*) Render the environment
  Ancora::Renderer3D::SkyBox(m_CubeMap, glm::vec3(0.0f), glm::vec3(100.0f));

  Ancora::Renderer3D::EndScene();
}

void GameLevel::Reset()
{
  m_GameOver = false;

  // Reset the player
  // ($) m_Player.Reset();

  // (#) Reset all other objects.
}
