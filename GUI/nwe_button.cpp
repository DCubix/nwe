#include "nwe_button.h"

DefWndProc(button) {
	if (msg == WM_LBUTTONUP) {
		nwe::Button* btn = reinterpret_cast<nwe::Button*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		if (btn) {
			nwe::ButtonParams& params = *static_cast<nwe::ButtonParams*>(btn->params.get());
			if (params.onPressed) params.onPressed();
		}
	}
	return DefSubclassProc(hWnd, msg, wParam, lParam);
}

nwe::Size nwe::Button::nativeBuild(Rect pBounds, HWND parent) {
	win32::WidgetParams params{};
	params.className = TEXT("BUTTON");
	params.parent = parent;
	params.style = WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_DEFPUSHBUTTON;

	_commandID = g_WidgetID++;
	handle = win32::createControl(params, _commandID, this);
	return nativeUpdate(pBounds);
}

nwe::Size nwe::Button::nativeUpdate(Rect pBounds) {
	ButtonParams& btnParams = ConvertParams(ButtonParams);

	Size size = win32::measureText(handle, btnParams.text);
	Rect cBounds = pBounds;
	if (pBounds.width == 0) {
		cBounds.width = size.width;
		cBounds.width += 24;
	}
	if (pBounds.height == 0) {
		cBounds.height = size.height;
		cBounds.height += 10;
	}

	SetWindowPos(handle, 0, cBounds.x, cBounds.y, cBounds.width, cBounds.height, 0);

	SendMessage(handle, WM_SETTEXT, 0, LPARAM(btnParams.text.data()));

	SetWindowSubclass(handle, buttonWndProc, 0, 0);

	return cBounds.size();
}
