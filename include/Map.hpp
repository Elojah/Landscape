#ifndef MAP_H
# define MAP_H

# include <vector>
class IObject;
class Camera;

class Map
{
public:
	Map(void);
	~Map(void);
	void	addObject(IObject *obj);
	void	draw(void) const;
	void	refresh(Camera const &cam) const;
protected:
private:
	std::vector<IObject *>	_objects;
};

#endif
