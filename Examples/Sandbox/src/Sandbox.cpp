#include <Ancora.h>

class Sandbox : public Ancora::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}


	
};

Ancora::Application* Ancora::CreateApplication()
{
	return new Sandbox();
}