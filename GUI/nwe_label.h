#pragma once

#include "nwe_widget.h"

namespace nwe {
	struct LabelParams : public Params {
		String text{ TEXT("Label") };
		Alignment alignment{ Alignment::Center };
	};
	struct Label : public Widget {
		Size nativeBuild(Rect bounds, HWND parent = nullptr) override;
		Size nativeUpdate(Rect bounds) override;
	};
}