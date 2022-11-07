#include "nwe_widget.h"

void nwe::Widget::update(Params* params) {
	this->params.reset(params);
	nativeUpdate(m_parentBounds);
}

nwe::Widget* nwe::Widget::construct(Params* params) {
	this->params = std::unique_ptr<Params>(params);
	return this;
}
