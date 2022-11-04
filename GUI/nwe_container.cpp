#include "nwe_container.h"

void nwe::Container::nativeBuild(Rect pBounds, HWND parent) {
	win32::WidgetParams params{};
	params.className = TEXT("STATIC");
	params.parent = parent;
	params.style = WS_VISIBLE | WS_CHILD;
	handle = win32::createControl(params, 0, this);
	SetWindowPos(handle, 0, pBounds.x, pBounds.y, pBounds.width, pBounds.height, 0);

	Rect oBounds = bounds();

	ContainerParams& cntParams = ConvertParams(ContainerParams);
	_childRef = std::unique_ptr<Widget>(cntParams.child);

	Rect newBounds{
		.x = oBounds.x + int(cntParams.padding.left),
		.y = oBounds.y + int(cntParams.padding.top),
		.width = oBounds.width - (cntParams.padding.left + cntParams.padding.right),
		.height = oBounds.height - (cntParams.padding.top + cntParams.padding.bottom)
	};
	_childRef->nativeBuild(newBounds, handle);
}

nwe::Rect nwe::Container::bounds() {
	ContainerParams& params = ConvertParams(ContainerParams);
	Rect originalBounds = nwe::Widget::bounds();
	return {
		.x = originalBounds.x,
		.y = originalBounds.y,
		.width = params.size.width == 0 ? originalBounds.width : params.size.width,
		.height = params.size.height == 0 ? originalBounds.height : params.size.height
	};
}

void nwe::Container::nativeDestroy() {
	_childRef->nativeDestroy();
	_childRef.reset(nullptr);
	nwe::Widget::nativeDestroy();
}
