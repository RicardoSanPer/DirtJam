#version 450
layout(binding = 0) uniform UniformBufferObject{ mat4 model; mat4 view; mat4 proj; } ubo;
layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec2 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;

layout(location = 0) out vec3 fragColor;
layout(location = 1) out vec2 fragTexCoord;

void main()
{
	fragTexCoord = (inTexCoord + (ubo.model * vec4(inPos.x, 0.0, inPos.y, 1.0)).xz)/65;
	vec4 col = texture(texSampler, fragTexCoord);
	gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPos.x, col.y * 10, inPos.y, 1.0);
	fragColor = inColor;
}