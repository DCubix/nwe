#include "nwe_row.h"

nwe::Size nwe::Row::nativeBuild(Rect pBounds, HWND parent) {
	win32::WidgetParams params{};
	params.className = TEXT("STATIC");
	params.parent = parent;
	params.style = WS_VISIBLE | WS_CHILD;
	handle = win32::createControl(params, 0, this);

	RowParams& rowParams = ConvertParams(RowParams);
	for (auto&& child : rowParams.children) {
		_childRefs.push_back(std::unique_ptr<Widget>(child));
		auto&& wid = _childRefs.back();
		Size wSize = wid->nativeBuild({ pBounds.x, pBounds.y, 0, 0 }, handle);
		_childSizes[reinterpret_cast<size_t>(wid->handle)] = wSize; // i don't care!
	}

	return nativeUpdate(pBounds);
}

nwe::Size nwe::Row::nativeUpdate(Rect pBounds) {
	SetWindowPos(handle, 0, pBounds.x, pBounds.y, pBounds.width, pBounds.height, 0);

	RowParams& rowParams = ConvertParams(RowParams);

	int x = 0;

	for (auto&& wid : _childRefs) {
		size_t widID = reinterpret_cast<size_t>(wid->handle);
		Size wSize = _childSizes[widID];

		int y = 0;
		uint32_t height = 0; // 0 means auto-size
		switch (rowParams.alignment) {
			default: break;
			case Alignment::Center: y = pBounds.height / 2 - wSize.height / 2; break;
			case Alignment::Far: y = pBounds.height - wSize.height; break;
			case Alignment::Stretch: height = pBounds.height; break;
		}

		wSize = wid->nativeUpdate({
			.x = x,
			.y = y,
			.width = wSize.width,
			.height = height
			});
		x += wSize.width;
	}

	return { uint32_t(x), pBounds.height };
}

void nwe::Row::nativeDestroy() {
	for (auto&& child : _childRefs) {
		child->nativeDestroy();
		child.reset(nullptr);
	}
	nwe::Widget::nativeDestroy();
}

