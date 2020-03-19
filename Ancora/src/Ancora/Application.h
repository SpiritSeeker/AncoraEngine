#pragma once

#include "Core.h"

#include "Window.h"
#include "Ancora/LayerStack.h"
#include "Events/Event.h"
#include "Ancora/Events/ApplicationEvent.h"

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
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;
	};

	Application* CreateApplication();

}