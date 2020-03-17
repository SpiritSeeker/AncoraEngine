#pragma once

#include "Core.h"

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