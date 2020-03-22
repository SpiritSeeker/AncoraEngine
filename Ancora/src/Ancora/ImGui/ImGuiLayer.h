#pragma once

#include "Ancora/Layer.h"

#include "Ancora/Events/KeyEvent.h"
#include "Ancora/Events/MouseEvent.h"
#include "Ancora/Events/ApplicationEvent.h"

namespace Ancora {

	class ANCORA_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}