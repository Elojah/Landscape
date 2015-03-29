/*
* @Author: Latias
* @Date:   2015-02-13 10:41:52
* @Last Modified by:   Latias
* @Last Modified time: 2015-02-13 10:50:54
*/

#include <vector>
#include "X11Win.hpp"
#include "Map.hpp"
#include "Landscape.hpp"

int main(void) {
	X11Win					win(800, 600);
	Camera					cam;
	Map					m;
	Landscape				l("./test/demo1.mod1");

	win.init();
	l.init();
	m.addObject(&l);

	win.loop(m, cam);
	return (0);
}
