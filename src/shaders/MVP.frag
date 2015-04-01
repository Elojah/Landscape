#version 330 core
in float zHeight;
out vec3 color;
void main() {
	if (zHeight < 5) {
		color = vec3(0.1, 0.1, 0.7);
	} else if (zHeight < 5.5) {
		color = vec3(0.8, 0.8, 0.9);
	} else if (zHeight < 15) {
		color = vec3(0.5, 0.3, 0.1);
	} else if (zHeight < 20) {
		color = vec3(0.2, 0.7, 0.2);
	} else {
		color = vec3(1.0, 1.0, 1.0);
	}
}
