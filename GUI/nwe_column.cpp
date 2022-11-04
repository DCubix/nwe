#include "nwe_column.h"

void nwe::Column::nativeBuild(Rect pBounds, HWND parent) {
	win32::WidgetParams params{};
	params.className = TEXT("STATIC");
	params.parent = parent;
	params.style = WS_VISIBLE | WS_CHILD;
	handle = win32::createControl(params, 0, this);
	SetWindowPos(handle, 0, pBounds.x, pBounds.y, pBounds.width, pBounds.height, 0);

	ColumnParams& colParams = ConvertParams(ColumnParams);

	int y = 0;

	// save and position them the widgets
	for (auto&& child : colParams.children) {
		_childRefs.push_back(std::unique_ptr<Widget>(child));

		auto&& wid = _childRefs.back();
		Rect wBounds = wid->bounds();

		int x = 0;
		switch (colParams.alignment) {
			default: break;
			case Alignment::Center: x = pBounds.width / 2 - wBounds.width / 2; break;
			case Alignment::Far: x = pBounds.width - wBounds.width; break;
		}

		wid->nativeBuild({
			.x = x,
			.y = y,
			.width = pBounds.width,
			.height = wBounds.height
			}, handle);
		y += wBounds.height;
	}
}

void nwe::Column::nativeDestroy() {
	for (auto&& child : _childRefs) {
		child->nativeDestroy();
		child.reset(nullptr);
	}
	nwe::Widget::nativeDestroy();
}
