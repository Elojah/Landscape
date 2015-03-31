#ifndef LANDSCAPE_H
# define LANDSCAPE_H
# define WIDTH_DIVIDE 400
# define HEIGHT_DIVIDE 400
# define Z_DIVIDE 7000
# define Z_MAX 7000
# define WIDTH_MAP 50
# define HEIGHT_MAP 50
# define Z_MULT 10

# include "IObject.hpp"
# include <string>
# include <vector>
class Parser;

class Landscape : public IObject
{
public:
								Landscape(std::string const&);
								~Landscape(void);
	void						init(void);
	void						draw(void) const;
	void						raiseWater(float const);
	bool						loop(int const);
protected:
private:
								Landscape(void);
	typedef struct				s_point {
		unsigned int			x;
		unsigned int			y;
		float					z;
	}							t_point;

	void						lexer(const Parser &p);
	void						initBuffers(void);

	void						smoothMap(void);
	void						smoothPoint(t_point const&, t_point const&);

	void						clearMap(void);
	void						useMap(void);
	void						printMap(void) const;
	void						findClosestPoint(t_point const&, t_point&) const;
	void						drawPoint(unsigned int const x, unsigned int const y) const;

	std::string					_filename;

	float						_map[WIDTH_MAP + 1][HEIGHT_MAP + 1];
	std::vector<t_point>		_immovablePoints;
	float						_waterDiff;
};

#endif
