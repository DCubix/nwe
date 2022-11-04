#pragma once

#include "nwe_widget.h"

namespace nwe {
	struct ContainerParams : Params {
		Widget* child;
		Insets padding{};
		Size size{ 0, 0 };
	};
	struct Container : public Widget {
		void nativeBuild(Rect bounds, HWND parent = nullptr) override;
		void nativeDestroy() override;

		Rect bounds() override;

		std::unique_ptr<Widget> _childRef;
	};
}
