#pragma once

extern Ancora::Application* Ancora::CreateApplication();

int main(int argc, char** argv)
{
	Ancora::Log::Init();
	AE_CORE_WARN("Initialized Ancora!");
	AE_INFO("Hello!");

	Ancora::Application* app = Ancora::CreateApplication();
	app->Run();
	delete app;
	return 0;
}