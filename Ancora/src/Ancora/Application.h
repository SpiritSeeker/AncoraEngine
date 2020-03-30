#pragma once

#include "Core.h"

#include "Window.h"
#include "Ancora/LayerStack.h"
#include "Events/Event.h"
#include "Ancora/Events/ApplicationEvent.h"
#include "Ancora/ImGui/ImGuiLayer.h"

#include "Ancora/Renderer/Shader.h"
#include "Ancora/Renderer/Buffer.h"
#include "Ancora/Renderer/VertexArray.h"

#include "Ancora/Renderer/OrthographicCamera.h"

namespace  Ancora {
	class ANCORA_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlackShader;
		std::shared_ptr<VertexArray> m_TriangleVA;

		OrthographicCamera m_Camera;
	private:
		static Application* s_Instance;
	};

	Application* CreateApplication();

}
