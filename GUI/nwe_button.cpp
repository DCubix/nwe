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

void nwe::Button::nativeBuild(Rect pBounds, HWND parent) {
	win32::WidgetParams params{};
	params.className = TEXT("BUTTON");
	params.parent = parent;
	params.style = WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_DEFPUSHBUTTON;

	_commandID = g_WidgetID++;
	handle = win32::createControl(params, _commandID, this);

	Rect cBounds = bounds();
	cBounds.x = pBounds.x;
	cBounds.y = pBounds.y;

	SetWindowPos(handle, 0, cBounds.x, cBounds.y, cBounds.width, cBounds.height, 0);

	ButtonParams& btnParams = ConvertParams(ButtonParams);
	SendMessage(handle, WM_SETTEXT, 0, LPARAM(btnParams.text.data()));

	SetWindowSubclass(handle, buttonWndProc, 0, 0);
}

nwe::Rect nwe::Button::bounds() {
	ButtonParams& btnParams = ConvertParams(ButtonParams);
	HDC dc = GetDC(handle);
	SIZE sz;
	GetTextExtentPoint32(dc, btnParams.text.c_str(), btnParams.text.size(), &sz);
	ReleaseDC(handle, dc);
	return {
		.x = 0,
		.y = 0,
		.width = uint32_t(sz.cx) + 48,
		.height = uint32_t(sz.cy) + 16
	};
}
