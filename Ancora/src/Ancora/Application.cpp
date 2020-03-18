#include "aepch.h"
#include "Application.h"

#include "Ancora/Events/ApplicationEvent.h"
#include "Ancora/Log.h"

namespace Ancora {
	Application::Application()
	{

	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		WindowResizeEvent e(1080, 720);
		AE_TRACE(e);

		while (true);
	}
}