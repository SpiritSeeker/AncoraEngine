#pragma once

#include <Ancora.h>

#include <glm/glm.hpp>

// Template class for game objects. No implementations here.
// (#) Make implementations for Player, other bikers, other vehicles, pedestrians, and the road. Preferably in a separate file.
// (#) Implement everything except the OnRender and LoadAssets.
class GameObject
{
public:
  virtual ~GameObject() = default;

  virtual void LoadAssets() = 0;

  virtual void OnUpdate(Ancora::Timestep ts) = 0;
  virtual void OnRender() = 0;

  virtual void Reset() = 0;

  // General method for retrieving the center.
  // ($) Implementations of GameObject can have more specific methods for getting bounds for collision check, etc.
  virtual const glm::vec3& GetPosition() const = 0;
};
