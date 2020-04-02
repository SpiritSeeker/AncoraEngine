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

	Ancora::Renderer2D::BeginScene(m_CameraController.GetCamera());
  Ancora::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Ancora::Renderer2D::EndScene();

  // std::dynamic_pointer_cast<Ancora::OpenGLShader>(m_Shader)->Bind();
  // std::dynamic_pointer_cast<Ancora::OpenGLShader>(m_Shader)->UploadUniformFloat4("u_Color", m_SquareColor);
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
