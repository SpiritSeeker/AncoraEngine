#include "GameLevel.h"
#include <glm/gtc/matrix_transform.hpp>

// Initial setup
void GameLevel::Init()
{
  // Load environment
  // (^) Make environment
  // std::array<std::string, 6> textureFaces = {
  //   "Sandbox/assets/cubemaps/tears_of_steel/px.png",
  //   "Sandbox/assets/cubemaps/tears_of_steel/nx.png",
  //   "Sandbox/assets/cubemaps/tears_of_steel/py.png",
  //   "Sandbox/assets/cubemaps/tears_of_steel/ny.png",
  //   "Sandbox/assets/cubemaps/tears_of_steel/pz.png",
  //   "Sandbox/assets/cubemaps/tears_of_steel/nz.png"
  // };

  // m_CubeMap = Ancora::CubeMap::Create(textureFaces);

  // (#) Call LoadAssets for every object.
  // ($) m_Player.LoadAssets();
	#ifdef AE_PLATFORM_LINUX
		m_RedBox = Ancora::ModelLoader::LoadModel("Sandbox/assets/models/box_red_arrow.fbx");
		m_BlueBox = Ancora::ModelLoader::LoadModel("Sandbox/assets/models/box_blue_arrow.fbx");
	#elif AE_PLATFORM_WINDOWS
		m_RedBox = Ancora::ModelLoader::LoadModel("assets/models/box_red_arrow.fbx");
		m_BlueBox = Ancora::ModelLoader::LoadModel("assets/models/box_blue_arrow.fbx");
	#else
		AE_ERROR("Only Linux and Windows supported!");
	#endif

  // Load lights
  m_SceneData.DirLight = Ancora::Light::CreateDirectionalLight(glm::vec3(0.0f, -1.0f, -2.0f));
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
	auto data = m_Controller->GetData();
	AE_TRACE("{0}", data.Data);

  // (#) Check if player crossed finish line here.
	m_Red += ts * m_Speed;
	m_Blue += ts * m_Speed;
	if (m_Red > 10)
	{
		m_Red = -20.0f;
		m_Blue = -20.0f;
	}
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

  // Render the environment
  // Ancora::Renderer3D::SkyBox(m_CubeMap, glm::vec3(0.0f), glm::vec3(100.0f));
  Ancora::Renderer3D::DrawModel(m_RedBox, glm::translate(glm::mat4(1.0f), glm::vec3({ -1.0f, 0.0f, m_Red })) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3({ 0.0f, -1.0f, 0.0f })) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3({ 0.0f, 0.0f, -1.0f })) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));
  Ancora::Renderer3D::DrawModel(m_BlueBox, glm::translate(glm::mat4(1.0f), glm::vec3({ 1.0f, 0.0f, m_Blue })) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3({ 0.0f, -1.0f, 0.0f })) * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3({ 0.0f, 0.0f, -1.0f })) * glm::scale(glm::mat4(1.0f), glm::vec3(0.5f)));

  Ancora::Renderer3D::EndScene();
}

void GameLevel::Reset()
{
  m_GameOver = false;

  // Reset the player
  // ($) m_Player.Reset();

  // (#) Reset all other objects.
}
