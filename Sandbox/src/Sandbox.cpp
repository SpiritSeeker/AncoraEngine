#include <Ancora.h>

#include "imgui.h"

class ExampleLayer : public Ancora::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Ancora::VertexArray::Create());

  	float vertices[] = {
			-0.75f, -0.75f, -1.0f, 0.8f, 0.1f, 0.2f, 1.0f,
			 0.75f, -0.75f,  0.0f, 0.0f, 0.5f, 0.9f, 1.0f,
			 0.75f,  0.75f,  1.0f, 0.3f, 0.7f, 0.1f, 1.0f,
			-0.75f,  0.75f,  0.0f, 0.7f, 0.8f, 0.3f, 1.0f
		};

		std::shared_ptr<Ancora::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Ancora::VertexBuffer::Create(vertices, sizeof(vertices)));
		Ancora::BufferLayout layout = {
			{ Ancora::ShaderDataType::Float3, "a_Position" },
			{ Ancora::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<Ancora::IndexBuffer> indexBuffer;
		indexBuffer.reset(Ancora::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_TriangleVA.reset(Ancora::VertexArray::Create());

		float triangleVertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		std::shared_ptr<Ancora::VertexBuffer> triangleVB;
		triangleVB.reset(Ancora::VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		triangleVB->SetLayout({
			{ Ancora::ShaderDataType::Float3, "a_Position" }
		});
		m_TriangleVA->AddVertexBuffer(triangleVB);

		uint32_t triangleIndices[3] = { 0, 1, 2 };
		std::shared_ptr<Ancora::IndexBuffer> triangleIB;
		triangleIB.reset(Ancora::IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
		m_TriangleVA->SetIndexBuffer(triangleIB);

		std::string vertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string fragmentSrc = R"(
			#version 450 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = 0.5 * vec4(v_Position * 0.5 + 0.5, 1.0) + 0.5 * v_Color;
			}
		)";

		m_Shader.reset(new Ancora::Shader(vertexSrc, fragmentSrc));

		std::string blackVertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blackFragmentSrc = R"(
			#version 450 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(0.15, 0.15, 0.15, 1.0);
			}
		)";

		m_BlackShader.reset(new Ancora::Shader(blackVertexSrc, blackFragmentSrc));
	}

	void OnUpdate() override
	{
		if (Ancora::Input::IsKeyPressed(AE_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (Ancora::Input::IsKeyPressed(AE_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		if (Ancora::Input::IsKeyPressed(AE_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed;
		else if (Ancora::Input::IsKeyPressed(AE_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed;

		if (Ancora::Input::IsKeyPressed(AE_KEY_LEFT))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (Ancora::Input::IsKeyPressed(AE_KEY_RIGHT))
			m_CameraRotation -= m_CameraRotationSpeed;

		Ancora::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Ancora::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Ancora::Renderer::BeginScene(m_Camera);

		Ancora::Renderer::Submit(m_Shader, m_VertexArray);
		Ancora::Renderer::Submit(m_BlackShader, m_TriangleVA);

		Ancora::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
	}

	void OnEvent(Ancora::Event& event) override
	{
	}
private:
	std::shared_ptr<Ancora::Shader> m_Shader;
	std::shared_ptr<Ancora::VertexArray> m_VertexArray;

	std::shared_ptr<Ancora::Shader> m_BlackShader;
	std::shared_ptr<Ancora::VertexArray> m_TriangleVA;

	Ancora::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 0.05f;
	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 2.0f;
};


class Sandbox : public Ancora::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Ancora::Application* Ancora::CreateApplication()
{
	return new Sandbox();
}
