#include "aepch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Ancora {

  RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
