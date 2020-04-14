#pragma once

#include <glm/glm.hpp>

namespace Ancora {

  class DirectionalLight
  {
  public:
    DirectionalLight(const glm::vec3& direction, const glm::vec3& ambient = glm::vec3(0.2f), const glm::vec3& diffuse = glm::vec3(0.5f), const glm::vec3& specular = glm::vec3(1.0f))
      : m_Direction(direction), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular) {}
    ~DirectionalLight() = default;

    void SetDirection(const glm::vec3& direction) { m_Direction = direction; }
    const glm::vec3& GetDirection() { return m_Direction; }

    void SetAmbient(const glm::vec3& ambient) { m_Ambient = ambient; }
    const glm::vec3& GetAmbient() { return m_Ambient; }

    void SetDiffuse(const glm::vec3& diffuse) { m_Diffuse = diffuse; }
    const glm::vec3& GetDiffuse() { return m_Diffuse; }

    void SetSpecular(const glm::vec3& specular) { m_Specular = specular; }
    const glm::vec3& GetSpecular() { return m_Specular; }
  private:
    glm::vec3 m_Direction, m_Ambient, m_Diffuse, m_Specular;
  };

  class PointLight
  {
  public:
    PointLight(const glm::vec3& position, const glm::vec3& ambient = glm::vec3(0.2f), const glm::vec3& diffuse = glm::vec3(0.5f), const glm::vec3& specular = glm::vec3(1.0f))
      : m_Position(position), m_Ambient(ambient), m_Diffuse(diffuse), m_Specular(specular), m_Constants(glm::vec3(1.0f, 0.1f, 0.03f)) {}
    ~PointLight() = default;

    void SetPosition(const glm::vec3& position) { m_Position = position; }
    const glm::vec3& GetPosition() { return m_Position; }

    void SetAmbient(const glm::vec3& ambient) { m_Ambient = ambient; }
    const glm::vec3& GetAmbient() { return m_Ambient; }

    void SetDiffuse(const glm::vec3& diffuse) { m_Diffuse = diffuse; }
    const glm::vec3& GetDiffuse() { return m_Diffuse; }

    void SetSpecular(const glm::vec3& specular) { m_Specular = specular; }
    const glm::vec3& GetSpecular() { return m_Specular; }

    void SetConstants(const glm::vec3& constants) { m_Constants = constants; }
    const glm::vec3& GetConstants() { return m_Constants; }
  private:
    glm::vec3 m_Position, m_Ambient, m_Diffuse, m_Specular, m_Constants;
  };

  class Light
  {
  public:
    static Ref<DirectionalLight> CreateDirectionalLight(const glm::vec3& direction, const glm::vec3& ambient = glm::vec3(0.2f), const glm::vec3& diffuse = glm::vec3(0.5f), const glm::vec3& specular = glm::vec3(1.0f))
    {
      return CreateRef<DirectionalLight>(direction, ambient, diffuse, specular);
    }

    static Ref<PointLight> CreatePointLight(const glm::vec3& position, const glm::vec3& ambient = glm::vec3(0.2f), const glm::vec3& diffuse = glm::vec3(0.5f), const glm::vec3& specular = glm::vec3(1.0f))
    {
      return CreateRef<PointLight>(position, ambient, diffuse, specular);
    }
  };

}
