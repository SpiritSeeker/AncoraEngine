#pragma once

// (#) Include all the implementations of GameObjects here.

class GameLevel
{
public:
  void Init();

  void OnUpdate(Ancora::Timestep ts)
  void OnRender();

  bool IsGameOver() const { return m_GameOver; }
  void Reset();

  Player& GetPlayer() { return m_Player; }
private:
  // ($) All private methods here
  // (#) Write different collision tests for player colliding with different objects.
  bool CollisionTest();
private:
  // ($) All private members here
  // (#) Game objects
  Player m_Player;
  RoadMap m_RoadMap;
  std::vector<Bikers> m_Bikers;
  std::vector<Vehicles> m_Vehicles;
  std::vector<Pedestrians> m_Pedestrians;

  // CubeMap for the environment
  // (*) Implement CubeMap sampling
  Ancora::Ref<Ancora::CubeMap> m_CubeMap;

  bool m_GameOver = false;
}
