#include "aepch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Ancora {

  VertexArray* VertexArray::Create()
  {
    switch (Renderer::GetAPI())
    {
      case RendererAPI::API::None:     AE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
      case RendererAPI::API::OpenGL:   return new OpenGLVertexArray();
    }

    AE_CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }

}
