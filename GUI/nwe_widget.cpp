#include "nwe_widget.h"
#include <iostream>

nwe::Rect nwe::Widget::bounds() {
	return win32::getBounds(handle);
}
