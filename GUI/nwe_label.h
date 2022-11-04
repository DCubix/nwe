#pragma once

#include "nwe_widget.h"

namespace nwe {
	struct LabelParams : Params {
		String text{ TEXT("Label") };
		Alignment alignment{ Alignment::Center };
		bool autoSize{ true };
	};
	struct Label : public Widget {
		void nativeBuild(Rect bounds, HWND parent = nullptr) override;
		void nativeUpdate(Rect bounds) override;
		Rect bounds() override;
	};
}