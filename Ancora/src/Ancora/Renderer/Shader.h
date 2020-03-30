#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Ancora {

  class Shader
  {
  public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
    void UploadUniformVec4(const std::string& name, const glm::vec4& vec);
  private:
    uint32_t m_RendererID;
  };

}
