#include "nwe_container.h"

nwe::Size nwe::Container::nativeBuild(Rect pBounds, HWND parent) {
	win32::WidgetParams params{};
	params.className = TEXT("STATIC");
	params.parent = parent;
	params.style = WS_VISIBLE | WS_CHILD;
	handle = win32::createControl(params, 0, this);
	
	ContainerParams& cntParams = ConvertParams(ContainerParams);
	_childRef = std::unique_ptr<Widget>(cntParams.child);
	_childRef->nativeBuild(pBounds, handle);

	return nativeUpdate(pBounds);
}

void nwe::Container::nativeDestroy() {
	_childRef->nativeDestroy();
	_childRef.reset(nullptr);
	nwe::Widget::nativeDestroy();
}

nwe::Size nwe::Container::nativeUpdate(nwe::Rect pBounds) {
	Widget::nativeUpdate(pBounds);

	ContainerParams& cntParams = ConvertParams(ContainerParams);
	Rect oBounds{
		.x = 0,
		.y = 0,
		.width = cntParams.size.width == 0 ? pBounds.width : cntParams.size.width,
		.height = cntParams.size.height == 0 ? pBounds.height : cntParams.size.height
	};

	Rect newBounds{
		.x = int(cntParams.padding.left),
		.y = int(cntParams.padding.top),
		.width = oBounds.width - (cntParams.padding.left + cntParams.padding.right),
		.height = oBounds.height - (cntParams.padding.top + cntParams.padding.bottom)
	};
	_childRef->nativeUpdate(newBounds);

	return newBounds.size();
}
