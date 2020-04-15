#include "aepch.h"
#include "Renderer3D.h"

#include "Ancora/Renderer/VertexArray.h"
#include "Ancora/Renderer/Shader.h"
#include "Ancora/Renderer/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Ancora {

  struct Renderer3DStorage
  {
    const uint32_t MaxTriangles = 50000;
    const uint32_t MaxVertices = MaxTriangles * 3;
    const uint32_t MaxIndices = MaxTriangles * 3;

    Ref<VertexArray> QuadVertexArray;
    Ref<VertexBuffer> QuadVertexBuffer;
    Ref<IndexBuffer> QuadIndexBuffer;
    Ref<Shader> QuadShader;
    Ref<Shader> CubeMapShader;
    Ref<Shader> LightingShader;
    Ref<Texture2D> WhiteTexture;
    Ref<Texture2D> ColorTexture;
  };

  static Renderer3DStorage s_Data;

  void Renderer3D::Init()
  {
    s_Data.QuadVertexArray = VertexArray::Create();

    s_Data.QuadVertexBuffer = VertexBuffer::Create(s_Data.MaxVertices * sizeof(VertexData3D));
    BufferLayout layout = {
      { ShaderDataType::Float3, "a_Position" },
      { ShaderDataType::Float2, "a_TexCoord" },
      { ShaderDataType::Float3, "a_Normal" }
    };
    s_Data.QuadVertexBuffer->SetLayout(layout);
    s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);

    s_Data.QuadIndexBuffer = IndexBuffer::Create(s_Data.MaxIndices);
    s_Data.QuadVertexArray->SetIndexBuffer(s_Data.QuadIndexBuffer);

    s_Data.WhiteTexture = Texture2D::Create(1, 1);
    uint32_t whiteTextureData = 0xffffffff;
    s_Data.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

    s_Data.ColorTexture = Texture2D::Create(1, 1);

    s_Data.QuadShader = Shader::Create("Sandbox/assets/shaders/FlatColor.glsl");
    s_Data.CubeMapShader = Shader::Create("Sandbox/assets/shaders/CubeMap.glsl");
    s_Data.LightingShader = Shader::Create("Sandbox/assets/shaders/Lighting.glsl");
  }

  void Renderer3D::Shutdown()
  {
  }

  void Renderer3D::BeginScene(const Renderer3DSceneData& sceneData)
  {
    s_Data.QuadShader->Bind();
    s_Data.QuadShader->SetMat4("u_ViewProjection", sceneData.Camera->GetViewProjectionMatrix());
    s_Data.CubeMapShader->Bind();
    s_Data.CubeMapShader->SetMat4("u_ViewProjection", sceneData.Camera->GetViewProjectionMatrix());
    s_Data.LightingShader->Bind();
    s_Data.LightingShader->SetMat4("u_ViewProjection", sceneData.Camera->GetViewProjectionMatrix());
    s_Data.LightingShader->SetFloat3("u_CameraPosition", sceneData.Camera->GetPosition());
    s_Data.LightingShader->SetFloat3("u_DirLight.direction", sceneData.DirLight->GetDirection());
    s_Data.LightingShader->SetFloat3("u_DirLight.ambient", sceneData.DirLight->GetAmbient());
    s_Data.LightingShader->SetFloat3("u_DirLight.diffuse", sceneData.DirLight->GetDiffuse());
    s_Data.LightingShader->SetFloat3("u_DirLight.specular", sceneData.DirLight->GetSpecular());
  }

  void Renderer3D::EndScene()
  {
  }

  void Renderer3D::SkyBox(Ref<CubeMap> cubeMap, const glm::vec3& position, const glm::vec3& size)
  {
    s_Data.CubeMapShader->Bind();
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), size);
    s_Data.CubeMapShader->SetMat4("u_Transform", transform);

    cubeMap->Bind(0);
    s_Data.CubeMapShader->SetInt("u_Skybox", 0);

    float vertexData[] = {
      // -x
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
      -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,

      // +x
       0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
       0.5f,  0.5f, -0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
       0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
       0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,

      // -y
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
       0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
       0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
      -0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

      // +y
       0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,

      // -z
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
       0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
       0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
      -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,

      // +z
       0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
       0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
    };

    s_Data.QuadVertexBuffer->SetData(vertexData, sizeof(vertexData));

    uint32_t indices[36];
    uint32_t offset = 0;
    for (uint32_t i = 0; i < 36; i += 6)
    {
      indices[i + 0] = offset + 0;
      indices[i + 1] = offset + 1;
      indices[i + 2] = offset + 2;

      indices[i + 3] = offset + 2;
      indices[i + 4] = offset + 3;
      indices[i + 5] = offset + 0;

      offset += 4;
    }
    s_Data.QuadIndexBuffer->SetData(indices, 36);

    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, 36);
  }

  void Renderer3D::DrawCube(const glm::vec3& position, const glm::vec3& size, const glm::vec4& color)
  {
    // s_Data.QuadShader->Bind();
    // s_Data.QuadShader->SetFloat4("u_Color", color);
    s_Data.LightingShader->Bind();
    s_Data.WhiteTexture->Bind(0);

    uint32_t colorTextureData = 0;
    for (int i = 0; i < 4; i++)
    {
      colorTextureData *= 256;
      colorTextureData += (int)(color[3-i] * 255);
    }
    s_Data.ColorTexture->SetData(&colorTextureData, sizeof(uint32_t));
    s_Data.ColorTexture->Bind(1);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), size);
    // s_Data.QuadShader->SetMat4("u_Transform", transform);
    s_Data.LightingShader->SetMat4("u_Transform", transform);

    s_Data.LightingShader->SetInt("u_Material.diffuse", 1);
    s_Data.LightingShader->SetInt("u_Material.specular", 0);
    s_Data.LightingShader->SetFloat("u_Material.shininess", 32.0f);

    float vertexData[] = {
      // -x
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
      -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
      -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, -1.0f,  0.0f,  0.0f,

      // +x
       0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  1.0f,  0.0f,  0.0f,
       0.5f,  0.5f, -0.5f, 1.0f, 0.0f,  1.0f,  0.0f,  0.0f,
       0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  1.0f,  0.0f,  0.0f,
       0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  1.0f,  0.0f,  0.0f,

      // -y
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f, -1.0f,  0.0f,
       0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f, -1.0f,  0.0f,
       0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  0.0f, -1.0f,  0.0f,
      -0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  0.0f, -1.0f,  0.0f,

      // +y
       0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  1.0f,  0.0f,
      -0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  1.0f,  0.0f,
       0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  1.0f,  0.0f,

      // -z
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,  0.0f,  0.0f, -1.0f,
       0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  0.0f,  0.0f, -1.0f,
       0.5f,  0.5f, -0.5f, 1.0f, 1.0f,  0.0f,  0.0f, -1.0f,
      -0.5f,  0.5f, -0.5f, 0.0f, 1.0f,  0.0f,  0.0f, -1.0f,

      // +z
       0.5f,  0.5f,  0.5f, 0.0f, 0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f,  0.5f,  0.5f, 1.0f, 0.0f,  0.0f,  0.0f,  1.0f,
      -0.5f, -0.5f,  0.5f, 1.0f, 1.0f,  0.0f,  0.0f,  1.0f,
       0.5f, -0.5f,  0.5f, 0.0f, 1.0f,  0.0f,  0.0f,  1.0f,
    };

    s_Data.QuadVertexBuffer->SetData(vertexData, sizeof(vertexData));

    uint32_t indices[36];
    uint32_t offset = 0;
    for (uint32_t i = 0; i < 36; i += 6)
    {
      indices[i + 0] = offset + 0;
      indices[i + 1] = offset + 1;
      indices[i + 2] = offset + 2;

      indices[i + 3] = offset + 2;
      indices[i + 4] = offset + 3;
      indices[i + 5] = offset + 0;

      offset += 4;
    }
    s_Data.QuadIndexBuffer->SetData(indices, 36);

    RenderCommand::DrawIndexed(s_Data.QuadVertexArray, 36);
  }

  void Renderer3D::DrawModel(Ref<Model3D> model, const glm::mat4& transform)
  {
    s_Data.LightingShader->Bind();
    s_Data.LightingShader->SetMat4("u_Transform", transform);

    s_Data.LightingShader->SetInt("u_Material.diffuse", 1);
    s_Data.LightingShader->SetInt("u_Material.specular", 0);
    s_Data.LightingShader->SetFloat("u_Material.shininess", 32.0f);

    for (auto& mesh : model->GetMesh())
    {
      s_Data.WhiteTexture->Bind(0);
      for (uint32_t i = 0; i < mesh.DiffuseTextures.size(); i++)
        mesh.DiffuseTextures[i]->Bind(1);
      for (uint32_t i = 0; i < mesh.SpecularTextures.size(); i++)
        mesh.SpecularTextures[i]->Bind(0);

      if (mesh.Vertices.size() > s_Data.MaxVertices)
      {
        uint32_t count = mesh.Vertices.size();
        uint32_t numIter = 0;
        while (count > s_Data.MaxVertices)
        {
          std::vector<VertexData3D> data(mesh.Vertices.begin() + numIter * s_Data.MaxVertices, mesh.Vertices.begin() + (numIter + 1) * s_Data.MaxVertices);
          std::vector<uint32_t> index(mesh.Indices.begin() + numIter * s_Data.MaxIndices, mesh.Indices.begin() + (numIter + 1) * s_Data.MaxIndices);
          numIter++;
          count -= s_Data.MaxVertices;
          s_Data.QuadVertexBuffer->SetData(&data[0], s_Data.MaxVertices * sizeof(VertexData3D));
          s_Data.QuadIndexBuffer->SetData(&index[0], s_Data.MaxIndices);
          RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.MaxIndices);
        }

        std::vector<VertexData3D> data(mesh.Vertices.begin() + numIter * s_Data.MaxVertices, mesh.Vertices.end());
        std::vector<uint32_t> index(mesh.Indices.begin() + numIter * s_Data.MaxIndices, mesh.Indices.end());
        s_Data.QuadVertexBuffer->SetData(&data[0], count * sizeof(VertexData3D));
        s_Data.QuadIndexBuffer->SetData(&index[0], count);
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, count);
      }

      else
      {
        s_Data.QuadVertexBuffer->SetData(&mesh.Vertices[0], mesh.Vertices.size() * sizeof(VertexData3D));
        s_Data.QuadIndexBuffer->SetData(&mesh.Indices[0], mesh.Indices.size());
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, mesh.Indices.size());
      }
    }
  }

  void Renderer3D::DrawModel(Ref<Model3D> model, const glm::mat4& transform, const glm::vec4& color)
  {
    s_Data.LightingShader->Bind();
    s_Data.LightingShader->SetMat4("u_Transform", transform);

    s_Data.LightingShader->SetInt("u_Material.diffuse", 1);
    s_Data.LightingShader->SetInt("u_Material.specular", 0);
    s_Data.LightingShader->SetFloat("u_Material.shininess", 32.0f);

    for (auto& mesh : model->GetMesh())
    {
      s_Data.WhiteTexture->Bind(0);

      uint32_t colorTextureData = 0;
      for (int i = 0; i < 4; i++)
      {
        colorTextureData *= 256;
        colorTextureData += (int)(color[3-i] * 255);
      }
      s_Data.ColorTexture->SetData(&colorTextureData, sizeof(uint32_t));
      s_Data.ColorTexture->Bind(1);

      for (uint32_t i = 0; i < mesh.SpecularTextures.size(); i++)
        mesh.SpecularTextures[i]->Bind(0);

      if (mesh.Vertices.size() > s_Data.MaxVertices)
      {
        uint32_t count = mesh.Vertices.size();
        uint32_t numIter = 0;
        while (count > s_Data.MaxVertices)
        {
          std::vector<VertexData3D> data(mesh.Vertices.begin() + numIter * s_Data.MaxVertices, mesh.Vertices.begin() + (numIter + 1) * s_Data.MaxVertices);
          std::vector<uint32_t> index(mesh.Indices.begin() + numIter * s_Data.MaxIndices, mesh.Indices.begin() + (numIter + 1) * s_Data.MaxIndices);
          numIter++;
          count -= s_Data.MaxVertices;
          s_Data.QuadVertexBuffer->SetData(&data[0], s_Data.MaxVertices * sizeof(VertexData3D));
          s_Data.QuadIndexBuffer->SetData(&index[0], s_Data.MaxIndices);
          RenderCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.MaxIndices);
        }

        std::vector<VertexData3D> data(mesh.Vertices.begin() + numIter * s_Data.MaxVertices, mesh.Vertices.end());
        std::vector<uint32_t> index(mesh.Indices.begin() + numIter * s_Data.MaxIndices, mesh.Indices.end());
        s_Data.QuadVertexBuffer->SetData(&data[0], count * sizeof(VertexData3D));
        s_Data.QuadIndexBuffer->SetData(&index[0], count);
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, count);
      }

      else
      {
        s_Data.QuadVertexBuffer->SetData(&mesh.Vertices[0], mesh.Vertices.size() * sizeof(VertexData3D));
        s_Data.QuadIndexBuffer->SetData(&mesh.Indices[0], mesh.Indices.size());
        RenderCommand::DrawIndexed(s_Data.QuadVertexArray, mesh.Indices.size());
      }
    }
  }

}
