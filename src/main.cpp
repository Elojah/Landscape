/*
* @Author: Latias
* @Date:   2015-02-13 10:41:52
* @Last Modified by:   Latias
* @Last Modified time: 2015-02-13 10:50:54
*/

#include <vector>
#include <iostream>
#include "X11Win.hpp"
#include "Map.hpp"
#include "SimpleTriangle.hpp"
#include "Landscape.hpp"

void	exec(char *filename) {
	X11Win					win(800, 600);
	Camera					cam;
	Map					m;
	// SimpleTriangle			t;
	Landscape				l(filename);

	win.init();
	l.init();
	m.addObject(&l);
	// m.addObject(&t);

	win.loop(m, cam);
}

int main(int ac, char **av) {
	if (ac != 2) {
		std::cout << "Enter a filename:\t" << std::endl;
	} else {
		exec(av[1]);
	}
	return (0);
}
