#pragma once

#include "nwe_widget.h"

namespace nwe {
	struct ContainerParams : Params {
		Widget* child;
		Insets padding{};
		Size size{ 0, 0 };
	};

	struct Container : public Widget {
		Size nativeBuild(Rect bounds, HWND parent = nullptr) override;
		Size nativeUpdate(Rect bounds) override;
		void nativeDestroy() override;

		std::unique_ptr<Widget> _childRef;
	};
}
