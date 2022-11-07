#pragma once

#include "nwe_widget.h"

namespace nwe {
	struct ButtonParams : Params {
		String text{ TEXT("Button") };
		std::function<void()> onPressed;
	};
	struct Button : public Widget {
		Size nativeBuild(Rect bounds, HWND parent = nullptr) override;
		Size nativeUpdate(Rect bounds) override;

		uint64_t _commandID{ 0 };
	};
}
