#type vertex
#version 450 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec3 v_TexCoord;

void main()
{
  v_TexCoord = vec3(u_Transform * vec4(a_Position, 1.0));
  gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
}

#type fragment
#version 450 core

layout(location = 0) out vec4 color;

in vec3 v_TexCoord;

uniform samplerCube u_Skybox;

void main()
{
  color = texture(u_Skybox, v_TexCoord);
}
