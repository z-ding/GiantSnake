#include "debugger.h"
#include "global.h"
void displaygrid() {
	for (auto& e : grid) {
		for (auto& f : e) {
			if (f->getter().text != 'e') {
				//std::cout << f->getter().x << "," << f->getter().y << "," << f->getter().text << std::endl;
				drawCircle(f->getter().x, f->getter().y, default_radius, f->getter().text, 100);
			}
		}
	}
}