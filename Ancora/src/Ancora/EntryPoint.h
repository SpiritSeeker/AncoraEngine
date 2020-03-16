#pragma once

extern Ancora::Application* Ancora::CreateApplication();

int main(int argc, char** argv)
{
	Ancora::Application* app = Ancora::CreateApplication();
	app->Run();
	delete app;
	return 0;
}