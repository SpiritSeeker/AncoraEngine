#include "aepch.h"
#include "Renderer2D.h"

#include "Ancora/Renderer/VertexArray.h"
#include "Ancora/Renderer/Shader.h"
#include "Ancora/Renderer/RenderCommand.h"

namespace Ancora {

  struct Renderer2DStorage
  {
    Ref<VertexArray> QuadVertexArray;
    Ref<Shader> FlatColorShader;
  };

  static Renderer2DStorage* s_Data;

  void Renderer2D::Init()
  {
    s_Data = new Renderer2DStorage();

    s_Data->QuadVertexArray = VertexArray::Create();

    float vertices[] = {
      -0.75f, -0.75f,  0.0f,
       0.75f, -0.75f,  0.0f,
       0.75f,  0.75f,  0.0f,
      -0.75f,  0.75f,  0.0f
    };

    Ref<VertexBuffer> vertexBuffer;
    vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
    BufferLayout layout = {
      { ShaderDataType::Float3, "a_Position" }
    };
    vertexBuffer->SetLayout(layout);
    s_Data->QuadVertexArray->AddVertexBuffer(vertexBuffer);

    uint32_t indices[6] = {
      0, 1, 2,
      2, 3, 0
    };

    Ref<IndexBuffer> indexBuffer;
    indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
    s_Data->QuadVertexArray->SetIndexBuffer(indexBuffer);

    s_Data->FlatColorShader = Shader::Create("Sandbox/assets/shaders/FlatColor.glsl");
  }

  void Renderer2D::Shutdown()
  {
    delete s_Data;
  }

  void Renderer2D::BeginScene(const OrthographicCamera& camera)
  {
    s_Data->FlatColorShader->Bind();
    s_Data->FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    s_Data->FlatColorShader->SetMat4("u_Transform", glm::mat4(1.0f));
  }

  void Renderer2D::EndScene()
  {

  }

  void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
  {
    DrawQuad({ position.x, position.y, 0.0f }, size, color);
  }

  void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
  {
    s_Data->FlatColorShader->Bind();
    s_Data->FlatColorShader->SetFloat4("u_Color", color);

    s_Data->QuadVertexArray->Bind();
    RenderCommand::DrawIndexed(s_Data->QuadVertexArray);
  }

}
