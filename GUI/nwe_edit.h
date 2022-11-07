#pragma once

#include "nwe_widget.h"

#include <functional>

namespace nwe {
	struct EditParams : Params {
		uint32_t width{ 120 };
		Alignment alignment{ Alignment::Near };

		String initialValue{ TEXT("") };
		std::function<void(String)> onChange;
	};
	struct Edit : public Widget {
		Size nativeBuild(Rect pBounds, HWND parent = nullptr) override;
		Size nativeUpdate(Rect pBounds) override;

		uint64_t _commandID{ 0 };
		String value;
	};
}
