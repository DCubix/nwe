#include "nwe_edit.h"

#include <iostream>

DefWndProc(edit) {
    if (msg == WM_KEYDOWN || msg == WM_CHAR || msg == WM_KEYUP) {
        nwe::Edit* edit = reinterpret_cast<nwe::Edit*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        if (edit) {
            nwe::EditParams& params = *static_cast<nwe::EditParams*>(edit->params.get());

            nwe::String str{};
            str.resize(1024);
            Edit_GetText(hWnd, str.data(), 1024);

            if (edit->value != str) {
                edit->value = str;
                if (params.onChange) params.onChange(str);
            }
        }
    }
    return DefSubclassProc(hWnd, msg, wParam, lParam);
}

nwe::Size nwe::Edit::nativeBuild(Rect pBounds, HWND parent) {
    win32::WidgetParams params{};
    params.className = TEXT("EDIT");
    params.style = WS_BORDER | WS_CHILD | WS_VISIBLE;
    params.parent = parent;
    _commandID = g_WidgetID++;
    handle = win32::createControl(params, _commandID, this);
    SetWindowSubclass(handle, editWndProc, 0, 0);
    return nativeUpdate(pBounds);
}

nwe::Size nwe::Edit::nativeUpdate(Rect pBounds) {
    Widget::nativeUpdate(pBounds);

    EditParams& params = ConvertParams(EditParams);

    Size textSize = win32::measureText(handle, TEXT("E]|"));
    Rect cBounds = pBounds;
    if (pBounds.width == 0) {
        cBounds.width = params.width;
    }
    if (pBounds.height == 0) {
        cBounds.height = textSize.height;
        cBounds.height += 6;
    }

    SetWindowPos(handle, 0, cBounds.x, cBounds.y, cBounds.width, cBounds.height, 0);

    auto style = GetWindowLongPtr(handle, GWL_STYLE);
    style &= ~(ES_LEFT | ES_CENTER | ES_RIGHT);

    switch (params.alignment) {
        default:
        case Alignment::Near: style |= ES_LEFT; break;
        case Alignment::Center: style |= ES_CENTER; break;
        case Alignment::Far: style |= ES_RIGHT; break;
    }
    SetWindowLongPtr(handle, GWL_STYLE, style);
    InvalidateRect(handle, NULL, TRUE);

    return cBounds.size();
}
