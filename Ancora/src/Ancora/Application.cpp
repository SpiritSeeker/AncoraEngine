#include "aepch.h"
#include "Application.h"

#include <glad/glad.h>

#include "Input.h"

namespace Ancora {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		AE_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		m_VertexArray.reset(VertexArray::Create());

  	float vertices[] = {
			-0.75f, -0.75f, -1.0f, 0.8f, 0.1f, 0.2f, 1.0f,
			 0.75f, -0.75f,  0.0f, 0.0f, 0.5f, 0.9f, 1.0f,
			 0.75f,  0.75f,  1.0f, 0.3f, 0.7f, 0.1f, 1.0f,
			-0.75f,  0.75f,  0.0f, 0.7f, 0.8f, 0.3f, 1.0f
		};

		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[6] = {
			0, 1, 2,
			2, 3, 0
		};

		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_TriangleVA.reset(VertexArray::Create());

		float triangleVertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> triangleVB;
		triangleVB.reset(VertexBuffer::Create(triangleVertices, sizeof(triangleVertices)));
		triangleVB->SetLayout({
			{ ShaderDataType::Float3, "a_Position" }
		});
		m_TriangleVA->AddVertexBuffer(triangleVB);

		uint32_t triangleIndices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> triangleIB;
		triangleIB.reset(IndexBuffer::Create(triangleIndices, sizeof(triangleIndices) / sizeof(uint32_t)));
		m_TriangleVA->SetIndexBuffer(triangleIB);

		std::string vertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = vec4(a_Position, 1.0);
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

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

		std::string blackVertexSrc = R"(
			#version 450 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
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

		m_BlackShader.reset(new Shader(blackVertexSrc, blackFragmentSrc));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			m_VertexArray->Bind();
			glDrawElements(GL_TRIANGLES, m_VertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			m_BlackShader->Bind();
			m_TriangleVA->Bind();
			glDrawElements(GL_TRIANGLES, m_TriangleVA->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
