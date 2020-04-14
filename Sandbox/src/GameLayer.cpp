#include "GameLayer.h"

GameLayer::GameLayer()
  : Layer("GameLayer")
{
  auto& window = Ancora::Application::Get().GetWindow();
  CreateCamera(window.GetWidth(), window.GetHeight());

  Ancora::Random::Init();
}

void GameLayer::OnAttach()
{
  m_Level.Init(m_Camera);
}

void GameLayer::OnDetach()
{
}

// Main Game Loop, including MainMenu and Restart UI (will be implemented soon)
void GameLayer::OnUpdate(Ancora::Timestep ts)
{
  // ts is time since last iteration of Sandbox::OnUpdate, which in this case is equal to that of GameLayer::OnUpdate
  m_Time += ts;
  m_FPS = 1 / ts;

  if (m_Level.IsGameOver())
    m_State = GameState::GameOver;

  // (^) See how this looks and maybe change it to be at the center of the road and follow the player along the road
  const auto& playerPos = m_Level.GetPlayer().GetPosition();
  m_Camera->SetView({ playerPos.x, playerPos.y, playerPos.z + 2.0f });

  switch (m_State)
  {
    case GameState::Play:
    {
      m_Level.OnUpdate(ts);
      break;
    }
  }

  // Rendering
  Ancora::RenderCommand::SetClearColor({ 0.8f, 0.5f, 0.3f, 1.0f });
  Ancora::RenderCommand::Clear();

  m_Level.OnRender();
}

void GameLayer::OnImGuiRender()
{
  // (*) Implement UI
}

void GameLayer::OnEvent(Ancora::Event& e)
{
	Ancora::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Ancora::WindowResizeEvent>(AE_BIND_EVENT_FN(GameLayer::OnWindowResize));
	dispatcher.Dispatch<Ancora::MouseButtonPressedEvent>(AE_BIND_EVENT_FN(GameLayer::OnMouseButtonPressed));
}

bool GameLayer::OnMouseButtonPressed(Ancora::MouseButtonPressedEvent& e)
{
	if (m_State == GameState::GameOver)
		m_Level.Reset();

	m_State = GameState::Play;
	return false;
}

bool GameLayer::OnWindowResize(Ancora::WindowResizeEvent& e)
{
	CreateCamera(e.GetWidth(), e.GetHeight());
	return false;
}

void GameLayer::CreateCamera(uint32_t width, uint32_t height)
{
  float aspectRatio = (float)width / (float)height;
  float fov = 45.0f;
  float nearPlane = 1.0f;
  float farPlane = 1000.0f;

  m_Camera = Ancora::CreateRef<Ancora::PerspectiveCamera>(fov, aspectRatio, nearPlane, farPlane);
}
