#version 330 core
layout(location = 0) in vec3 vertexSpace;
layout(location = 1) in vec3 vertexColor;
out float zHeight;
uniform mat4	mvp;
void main() {
	gl_Position = mvp * vec4(vertexSpace, 1);
	zHeight = vertexSpace.z;
}
