#ifndef SIMPLE_TRIANGLE_H
# define SIMPLE_TRIANGLE_H
# define GL_GLEXT_PROTOTYPES

# include "IObject.hpp"

class Camera;

class SimpleTriangle : public IObject
{
public:
	SimpleTriangle(void);
	void		init(void);
	void		draw(void) const;
protected:
private:
};

#endif
