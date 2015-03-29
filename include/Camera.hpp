#ifndef CAMERA_H
# define CAMERA_H
# define GL_GLEXT_PROTOTYPES

# include <GL/gl.h>
# include <glm/glm.hpp>

enum eDirection {
	CONSTANT = 0,
	RIGHT = 1,
	LEFT = 2,
	UP = 3,
	DOWN = 4
};

class Camera
{
public:
	Camera(void);
	~Camera(void);
	const glm::mat4	getViewProj(void) const;
	void				rotate(const eDirection &dir);
	void				translate(const eDirection &dir);
protected:
private:
	glm::mat4		_view;
	glm::mat4		_projection;
	glm::mat4		_vp;
};

#endif
