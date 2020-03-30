#include <Ancora.h>

#include "imgui.h"

class ExampleLayer : public Ancora::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		if (Ancora::Input::IsKeyPressed(AE_KEY_TAB))
			AE_INFO("Tab key is pressed!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Ancora::Event& event) override
	{
		if (event.GetEventType() == Ancora::EventType::KeyPressed)
		{
			Ancora::KeyPressedEvent& e = (Ancora::KeyPressedEvent&)event;
			AE_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};


class Sandbox : public Ancora::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}

};

Ancora::Application* Ancora::CreateApplication()
{
	return new Sandbox();
}
