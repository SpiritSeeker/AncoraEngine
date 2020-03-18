#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace  Ancora {
	class ANCORA_API Application
	{
	public:
		Application();
		virtual ~Application();
		
		void Run();
	};

	Application* CreateApplication();

}