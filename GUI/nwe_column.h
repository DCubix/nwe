#pragma once

#include "nwe_widget.h"

namespace nwe{
	struct ColumnParams : Params {
		std::vector<Widget*> children;
		Alignment alignment{ Alignment::Near };
	};
	struct Column : public Widget {
		void nativeBuild(Rect bounds, HWND parent = nullptr) override;
		void nativeDestroy() override;

		std::vector<std::unique_ptr<Widget>> _childRefs;
	};
}
