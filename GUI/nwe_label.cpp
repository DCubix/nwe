#include "nwe_label.h"

void nwe::Label::nativeBuild(Rect pBounds, HWND parent) {
	win32::WidgetParams params{};
	params.className = TEXT("STATIC");
	params.parent = parent;
	params.style = WS_VISIBLE | WS_CHILD | SS_WORDELLIPSIS;
	handle = win32::createControl(params, 0, this);
	nativeUpdate(pBounds);
}

void nwe::Label::nativeUpdate(nwe::Rect pBounds) {
	LabelParams& lblParams = ConvertParams(LabelParams);

	Rect cBounds = pBounds;
	if (lblParams.autoSize) {
		cBounds = bounds();
		cBounds.x = pBounds.x;
		cBounds.y = pBounds.y;
	}

	nwe::Widget::nativeUpdate(cBounds);

	SendMessage(handle, WM_SETTEXT, 0, LPARAM(lblParams.text.data()));

	auto style = GetWindowLongPtr(handle, GWL_STYLE);
	style &= ~(SS_LEFT | SS_CENTER | SS_RIGHT);

	switch (lblParams.alignment) {
		case Alignment::Near: style |= SS_LEFT; break;
		case Alignment::Center: style |= SS_CENTER; break;
		case Alignment::Far: style |= SS_RIGHT; break;
	}
	SetWindowLongPtr(handle, GWL_STYLE, style);
	InvalidateRect(handle, NULL, TRUE);
}

nwe::Rect nwe::Label::bounds() {
	LabelParams& lblParams = ConvertParams(LabelParams);
	HDC dc = GetDC(handle);
	SIZE sz;
	GetTextExtentPoint32(dc, lblParams.text.c_str(), lblParams.text.size(), &sz);
	ReleaseDC(handle, dc);
	return {
		.x = 0,
		.y = 0,
		.width = uint32_t(sz.cx) + 2,
		.height = uint32_t(sz.cy)
	};
}
