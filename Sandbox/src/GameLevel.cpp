#include "GameLevel.h"

// Initial setup
void GameLevel::Init()
{
  // (#) Call LoadAssets for every object.
  m_Player.LoadAssets();
}

void GameLevel::OnUpdate(Ancora::Timestep ts)
{
  // (#) Call OnUpdate for every object.
  m_Player.OnUpdate(ts);

  // (#) If the player collides with anything.
  // (#) All Collisions tests to be called here.
  if (CollisionTest())
  {
  }

  // (#) Check if player crossed finish line here.

}

void GameLevel::OnRender()
{
  // Render the player
  m_Player.OnRender();

  // (#) Render other bikers

  // (#) Render other vehicles (if any)

  // (#) Render pedestrians (if any)

  // Render the road
  m_RoadMap.OnRender();

  // (*) Render the environment
  Ancora::Renderer3D::CubeMap(m_CubeMap);
}

void Reset()
{
  m_GameOver = false;

  // Reset the player
  m_Player.Reset();

  // (#) Reset all other objects.
}
