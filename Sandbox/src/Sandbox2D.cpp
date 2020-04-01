#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
  : Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
  m_VertexArray = Ancora::VertexArray::Create();

  float vertices[] = {
    -0.75f, -0.75f,  0.0f,
     0.75f, -0.75f,  0.0f,
     0.75f,  0.75f,  0.0f,
    -0.75f,  0.75f,  0.0f
  };

  Ancora::Ref<Ancora::VertexBuffer> vertexBuffer;
  vertexBuffer = Ancora::VertexBuffer::Create(vertices, sizeof(vertices));
  Ancora::BufferLayout layout = {
    { Ancora::ShaderDataType::Float3, "a_Position" }
  };
  vertexBuffer->SetLayout(layout);
  m_VertexArray->AddVertexBuffer(vertexBuffer);

  uint32_t indices[6] = {
    0, 1, 2,
    2, 3, 0
  };

  Ancora::Ref<Ancora::IndexBuffer> indexBuffer;
  indexBuffer = Ancora::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
  m_VertexArray->SetIndexBuffer(indexBuffer);

  m_Shader = Ancora::Shader::Create("Sandbox/assets/shaders/FlatColor.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Ancora::Timestep ts)
{
  // Update
	m_FPS = 1 / ts;

	m_CameraController.OnUpdate(ts);

	// Render
  Ancora::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Ancora::RenderCommand::Clear();

	Ancora::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Ancora::OpenGLShader>(m_Shader)->Bind();
	std::dynamic_pointer_cast<Ancora::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Ancora::Renderer::Submit(m_Shader, m_VertexArray, glm::scale(glm::mat4(1.0f), glm::vec3(0.9f)));

	Ancora::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
  ImGui::Begin("Test");
	ImGui::Text("FPS: %d", m_FPS);
	ImGui::End();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Ancora::Event& e)
{
  m_CameraController.OnEvent(e);
}
