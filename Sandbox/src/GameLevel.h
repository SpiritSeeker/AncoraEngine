#pragma once

#include <Ancora.h>
#include "Controller/Controller.h"

// (#) Include all the implementations of GameObjects here.
// ($) #include "Player.h"

class GameLevel
{
public:
  void Init();

  void OnUpdate(Ancora::Timestep ts);
  void OnRender();

  bool IsGameOver() const { return m_GameOver; }
  void Reset();

  void SetController(const Ancora::Ref<Controller>& controller) { m_Controller = controller; }

  void UpdateCamera(const Ancora::Ref<Ancora::PerspectiveCamera>& camera) { m_SceneData.Camera = camera; }

  // ($) Player& GetPlayer() { return m_Player; }
private:
  // ($) All private methods here
  // (#) Write different collision tests for player colliding with different objects.
  // ($) bool CollisionTest();
private:
  // ($) All private members here
  // (#) Game objects
  // ($) Player m_Player;
  // ($) RoadMap m_RoadMap;
  // ($) std::vector<Bikers> m_Bikers;
  // ($) std::vector<Vehicles> m_Vehicles;
  // ($) std::vector<Pedestrians> m_Pedestrians;
  Ancora::Ref<Controller> m_Controller;
	Ancora::Ref<Ancora::Model3D> m_RedBox;
	Ancora::Ref<Ancora::Model3D> m_BlueBox;
	float m_Red = -20.0f;
	float m_Blue = -20.0f;
	float m_Speed = 10.0f;

  // CubeMap for the environment
  Ancora::Ref<Ancora::CubeMap> m_CubeMap;

  // Scene data for rendering
  Ancora::Renderer3DSceneData m_SceneData;

  bool m_GameOver = false;
};
