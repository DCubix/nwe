#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "nwe_core.h"

namespace nwe {
#define WID(WidgetType) (new WidgetType())->construct
#define ConvertParams(Type) *static_cast<Type*>(this->params.get())
#define DefWndProc(name) LRESULT CALLBACK name##WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)

	struct Params {};

	struct Widget {
		~Widget() = default;

		inline virtual void nativeDestroy() {
			if (handle) DestroyWindow(handle);
			handle = nullptr;
		}
		virtual Size nativeBuild(Rect bounds, HWND parent = nullptr) { return nativeUpdate(bounds); }
		virtual Size nativeUpdate(Rect bounds) {
			SetWindowPos(handle, 0, bounds.x, bounds.y, bounds.width, bounds.height, 0);
			return bounds.size();
		}

		virtual std::unique_ptr<Widget> build() { return nullptr; }

		Widget* construct(Params* params) { this->params = std::unique_ptr<Params>(params); return this; }

		HWND handle{ nullptr };
		std::unique_ptr<Params> params;
	};

	enum Alignment {
		Near = 0,
		Center,
		Far,
		Stretch
	};

	struct Insets {
		uint32_t left{ 12 }, right{ 12 }, top{ 12 }, bottom{ 12 };
	};

	static uint64_t g_WidgetID = 1;
}

