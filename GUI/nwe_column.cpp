#include "nwe_column.h"

nwe::Size nwe::Column::nativeBuild(Rect pBounds, HWND parent) {
	win32::WidgetParams params{};
	params.className = TEXT("STATIC");
	params.parent = parent;
	params.style = WS_VISIBLE | WS_CHILD;
	handle = win32::createControl(params, 0, this);

	ColumnParams& colParams = ConvertParams(ColumnParams);
	for (auto&& child : colParams.children) {
		_childRefs.push_back(std::unique_ptr<Widget>(child));
		auto&& wid = _childRefs.back();
		Size wSize = wid->nativeBuild({ pBounds.x, pBounds.y, 0, 0 }, handle);
		_childSizes[reinterpret_cast<size_t>(wid->handle)] = wSize; // i don't care!
	}

	return nativeUpdate(pBounds);
}

nwe::Size nwe::Column::nativeUpdate(Rect pBounds) {
	SetWindowPos(handle, 0, pBounds.x, pBounds.y, pBounds.width, pBounds.height, 0);

	ColumnParams& colParams = ConvertParams(ColumnParams);

	int y = 0;

	// save and position them the widgets
	for (auto&& wid : _childRefs) {
		size_t widID = reinterpret_cast<size_t>(wid->handle);
		Size wSize = _childSizes[widID];

		int x = 0;
		uint32_t width = 0; // 0 means auto-size
		switch (colParams.alignment) {
			default: break;
			case Alignment::Center: x = pBounds.width / 2 - wSize.width / 2; break;
			case Alignment::Far: x = pBounds.width - wSize.width; break;
			case Alignment::Stretch: width = pBounds.width; break;
		}

		wSize = wid->nativeUpdate({
			.x = x,
			.y = y,
			.width = width,
			.height = wSize.height
		});
		y += wSize.height;
	}

	return { pBounds.width, uint32_t(y) };
}

void nwe::Column::nativeDestroy() {
	for (auto&& child : _childRefs) {
		child->nativeDestroy();
		child.reset(nullptr);
	}
	nwe::Widget::nativeDestroy();
}
