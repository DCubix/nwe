#pragma once

#include "nwe_widget.h"

#include <vector>
#include <map>

namespace nwe {
	struct ColumnParams : Params {
		std::vector<Widget*> children;
		Alignment alignment{ Alignment::Near };
	};
	struct Column : public Widget {
		Size nativeBuild(Rect bounds, HWND parent = nullptr) override;
		Size nativeUpdate(Rect bounds) override;
		void nativeDestroy() override;

	private:
		std::vector<std::unique_ptr<Widget>> _childRefs;
		std::map<size_t, Size> _childSizes;

	};
}
