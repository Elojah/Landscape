#define GLM_FORCE_RADIANS
#include "Camera.hpp"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(void) {
	_projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	_view = glm::lookAt(
		glm::vec3(30.0f, 30.0f, 50.0f),
		glm::vec3(25.0f, 25.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	_vp = _projection * _view;
}

Camera::~Camera(void) {
}

const glm::mat4	Camera::getViewProj(void) const {
	return (_vp);
}

void				Camera::rotate(const eDirection &dir) {
	if (dir == RIGHT) {
		_view = glm::rotate(
			_view,
			-0.1f,
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
	} else if (dir == LEFT) {
		_view = glm::rotate(
			_view,
			0.1f,
			glm::vec3(0.0f, 1.0f, 0.0f)
		);
	}
	_vp = _projection * _view;
}

void				Camera::translate(const eDirection &dir) {
	if (dir == UP) {
		_view = glm::translate(
			_view,
			-1.01f * glm::vec3(0.0f, 1.0f, 0.0f));
	} else if (dir == DOWN) {
		_view = glm::translate(
			_view,
			1.01f * glm::vec3(0.0f, 1.0f, 0.0f));
	}
	_vp = _projection * _view;
}
