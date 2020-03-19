#include "aepch.h"
#include "Application.h"

#include "Ancora/Events/ApplicationEvent.h"

namespace Ancora {
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}
}