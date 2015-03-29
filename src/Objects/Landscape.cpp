#include "Landscape.hpp"
#include "Parser.hpp"
#include "LoadShaders.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>

Landscape::Landscape(void) {
}

Landscape::Landscape(std::string const &filename) :
	_filename(filename) {
}

void			Landscape::init(void) {
	Parser									p(_filename);

	std::cout << "Parsing: DONE" << std::endl;
	_waterDiff = 0;
	clearMap();
	lexer(p);
	std::cout << "Lexing: DONE" << std::endl;
	smoothMap();
	useMap();
	initBuffers();
}

void	Landscape::initBuffers(void) {
	static GLfloat	g_vertex_buffer_data[WIDTH_MAP * HEIGHT_MAP * 3 + 1];
	static GLfloat	g_color_buffer_data[WIDTH_MAP * HEIGHT_MAP * 3 + 1];
	size_t			i;

	/*Vertex Buffer*/
	for (i = 0; i < WIDTH_MAP * HEIGHT_MAP * 3; i += 3) {
		g_vertex_buffer_data[i] = (i / WIDTH_MAP) * 0.1f;
		g_index_buffer_data[i] = i;
	}
	for (i = 2; i < WIDTH_MAP * HEIGHT_MAP * 3; i += 3) {
		g_vertex_buffer_data[i] = (i % WIDTH_MAP) * 0.1f;
	}
	for (i = 1; i < WIDTH_MAP * HEIGHT_MAP * 3; i += 3) {
		g_vertex_buffer_data[i] = _map[(i / 3) / WIDTH_MAP][(i / 3) % WIDTH_MAP] * Z_MULT;
	}
	/*Color Buffer*/
	for (i = 0; i < WIDTH_MAP * HEIGHT_MAP * 3; ++i) {
		g_color_buffer_data[i] = i * 0.0001f;
	}
	/*Index Buffer*/
	for (i = 0; i < WIDTH_MAP * HEIGHT_MAP * 3; ++i) {
		g_index_buffer_data[i * 3] = i;
		g_index_buffer_data[i * 3 + 1] = i + WIDTH_MAP;
		g_index_buffer_data[i * 3 + 2] = i + 1;
	}

	glGenVertexArrays(1, &_vertexArrayID);
	glBindVertexArray(_vertexArrayID);

	_progID = LoadShaders("./src/shaders/SimpleTriangle.vert", "./src/shaders/SimpleTriangle.frag");

	glGenBuffers(1, &_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &_colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(g_index_buffer_data), g_index_buffer_data, GL_STATIC_DRAW);
}

bool	Landscape::loop(int const key) {
	switch (key) {
		case 22: raiseWater(0.01f);
				break ;
		case 20: raiseWater(-0.01f);
				break ;
		default: return (false);
	}
	return (true);
}

void	Landscape::lexer(const Parser &p) {
	const std::vector<sReadToken>		reads(p.getRead());
	float									x;
	float									y;
	float									z;
	size_t									i(0);
	size_t									len;

	len = reads.size();
	while (i < len - 4) {
		if (reads[i].type != SCOPE
			|| reads[i + 1].type != NUMBER || reads[i + 2].type != NUMBER || reads[i + 3].type != NUMBER
			|| reads[i + 4].type != SCOPE) {
			return ;
		}
		x = strtof(reads[i + 1].word.c_str(), NULL);
		y = strtof(reads[i + 2].word.c_str(), NULL);
		z = strtof(reads[i + 3].word.c_str(), NULL);
		x = fmod((x / WIDTH_DIVIDE), WIDTH_MAP);
		y = fmod((y / HEIGHT_DIVIDE), HEIGHT_MAP);
		z = fmod((z / Z_DIVIDE), Z_MAX);

		std::cout << "Assign value: " << z << " at point (" << x << ", " << y << ")" << std::endl;
		_immovablePoints.push_back((t_point){static_cast<unsigned int>(x), static_cast<unsigned int>(y), z});
		_map[static_cast<unsigned int>(x)][static_cast<unsigned int>(y)] = z;
		i += 5;
	}

}

void	Landscape::smoothMap(void) {
	t_point		closestPoint;

	for (std::vector<t_point>::iterator it = _immovablePoints.begin(); it != _immovablePoints.end(); ++it) {
		findClosestPoint((*it), closestPoint);
		std::cout << "Closest point from:\t" << it->x << ", " << it->y << ", " << it->z << std::endl
		<< "found at:\t\t" << closestPoint.x << ", " << closestPoint.y << ", " << closestPoint.z << std::endl;
		smoothPoint(*it, closestPoint);
		std::cout << "Fill map: DONE" << std::endl;
	}
}

void	Landscape::smoothPoint(t_point const &originPoint, t_point const &closestPoint) {
	unsigned int	i;
	unsigned int	j;
	float			z;
	float			dist;
	float			maxDist;

	if (originPoint.z == 0.) {
		return ;
	}
	maxDist = (pow(originPoint.x > closestPoint.x ? originPoint.x - closestPoint.x : closestPoint.x - originPoint.x, 2)
			+ pow(originPoint.y > closestPoint.y ? originPoint.y - closestPoint.y : closestPoint.y - originPoint.y, 2));
	std::cout << "Dist: " << (maxDist) << std::endl;
	for (i = 0; i < WIDTH_MAP; ++i) {
		for (j = 0; j < HEIGHT_MAP; ++j) {
			dist = pow(originPoint.x > i ? originPoint.x - i : i - originPoint.x, 2)
					+ pow(originPoint.y > j ? originPoint.y - j : j - originPoint.y, 2);
			if (dist != 0. && dist < maxDist) {
				z = ((sin((M_PI / 2) + sqrt(dist / maxDist) * M_PI) + 1.0f) / 2.0f) * (originPoint.z);
				if (_map[i][j] == -1.0f) {
					_map[i][j] = z;
				} else {
					_map[i][j] += z;
				}
			}
		}
	}
}

void	Landscape::findClosestPoint(t_point const &origin, t_point &closest) const {
	unsigned int	xDist;
	unsigned int	yDist;
	unsigned int	xTmp;
	unsigned int	yTmp;
	unsigned int	dist;


	xDist = origin.x > WIDTH_MAP / 2 ? WIDTH_MAP - origin.x : origin.x;
	yDist = origin.y > HEIGHT_MAP / 2 ? HEIGHT_MAP - origin.y : origin.y;
	if (xDist > yDist) {
		closest.x = origin.x;
		closest.y = origin.y > HEIGHT_MAP / 2 ? HEIGHT_MAP : 0;
		xDist = 0;
	} else {
		closest.x = origin.x > WIDTH_MAP / 2 ? WIDTH_MAP : 0;
		closest.y = origin.y;
		yDist = 0;
	}
	closest.z = 0;

	dist = xDist * xDist + yDist * yDist;
	for (std::vector<t_point>::const_iterator it = _immovablePoints.begin(); it != _immovablePoints.end(); ++it) {
		xTmp = it->x > origin.x ? it->x - origin.x : origin.x - it->x;
		yTmp = it->y > origin.y ? it->y - origin.y : origin.y - it->y;
		if ((xTmp != 0 || yTmp != 0)
			&& xTmp * xTmp + yTmp * yTmp < dist) {
			closest.x = it->x;
			closest.y = it->y;
			closest.z = it->z;
			dist = xTmp * xTmp + yTmp * yTmp;
		}
	}
}

void		Landscape::printMap(void) const {
	unsigned int	i;
	unsigned int	j;

	for (i = 0; i < WIDTH_MAP; ++i) {
		for (j = 0; j < HEIGHT_MAP; ++j) {
			// if (_map[i][j] != 0.) {
				std::cout << _map[i][j] << "\t";
			// }
		}
		std::cout << std::endl;
	}
}

void		Landscape::clearMap(void) {
	unsigned int	i;
	unsigned int	j;

	for (i = 0; i < WIDTH_MAP; ++i) {
		for (j = 0; j < HEIGHT_MAP; ++j) {
			_map[i][j] = -1.0f;
		}
	}
}

void		Landscape::useMap(void) {
	unsigned int	i;
	unsigned int	j;

	for (i = 0; i < WIDTH_MAP; ++i) {
		for (j = 0; j < HEIGHT_MAP; ++j) {
			if (_map[i][j] == -1.0f) {
				_map[i][j] = 0.0f;
			}
		}
	}
}

void	Landscape::raiseWater(float const n) {
	_waterDiff += n;
}

void	Landscape::draw(void) const {
	glUseProgram(_progID);
	glUniformMatrix4fv(_matrixID, 1, GL_FALSE, &mvp[0][0]);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, _colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vertexBuffer);
	// glDrawElements(
	// 	GL_TRIANGLE_STRIP,
	// 	WIDTH_MAP * HEIGHT_MAP * 3,
	// 	GL_UNSIGNED_INT,
	// 	g_index_buffer_data
	// );
	glDrawArrays(GL_POLYGON, 0, WIDTH_MAP * HEIGHT_MAP);
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}