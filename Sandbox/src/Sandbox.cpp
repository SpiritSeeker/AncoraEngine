#include <Ancora.h>

class ExampleLayer : public Ancora::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		// AE_INFO("ExampleLayer::Update");

		if (Ancora::Input::IsKeyPressed(AE_KEY_TAB))
			AE_INFO("Tab key is pressed!");
	}

	void OnEvent(Ancora::Event& event) override
	{
		// AE_TRACE("{0}", event);
	}
};


class Sandbox : public Ancora::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Ancora::ImGuiLayer());
	}

	~Sandbox()
	{

	}
	
};

Ancora::Application* Ancora::CreateApplication()
{
	return new Sandbox();
}