#include "nwe_label.h"

nwe::Size nwe::Label::nativeBuild(Rect pBounds, HWND parent) {
	win32::WidgetParams params{};
	params.className = TEXT("STATIC");
	params.parent = parent;
	params.style = WS_VISIBLE | WS_CHILD | SS_WORDELLIPSIS;
	handle = win32::createControl(params, 0, this);
	return nativeUpdate(pBounds);
}

nwe::Size nwe::Label::nativeUpdate(nwe::Rect pBounds) {
	Widget::nativeUpdate(pBounds);

	LabelParams& lblParams = ConvertParams(LabelParams);

	Size textSize = win32::measureText(handle, lblParams.text);
	Rect cBounds = pBounds;
	if (pBounds.width == 0) {
		cBounds.width = textSize.width;
		cBounds.width += 24;
	}
	if (pBounds.width == 0) {
		cBounds.height = textSize.height;
		cBounds.width += 10;
	}

	SendMessage(handle, WM_SETTEXT, 0, LPARAM(lblParams.text.data()));

	auto style = GetWindowLongPtr(handle, GWL_STYLE);
	style &= ~(SS_LEFT | SS_CENTER | SS_RIGHT);

	switch (lblParams.alignment) {
		default:
		case Alignment::Near: style |= SS_LEFT; break;
		case Alignment::Center: style |= SS_CENTER; break;
		case Alignment::Far: style |= SS_RIGHT; break;
	}
	SetWindowLongPtr(handle, GWL_STYLE, style);
	InvalidateRect(handle, NULL, TRUE);

	return nwe::Widget::nativeUpdate(cBounds);
}
