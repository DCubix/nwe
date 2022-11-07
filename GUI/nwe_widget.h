#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "nwe_core.h"

namespace nwe {
#define Ref(T, var) [&](T* ob) { var = ob; }
#define ConvertParams(Type) *static_cast<Type*>(this->params.get())
#define DefWndProc(name) LRESULT CALLBACK name##WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)

	struct Params {
	};

	struct Widget {
		~Widget() = default;

		inline virtual void nativeDestroy() {
			if (handle) DestroyWindow(handle);
			handle = nullptr;
		}
		virtual Size nativeBuild(Rect bounds, HWND parent = nullptr) { return nativeUpdate(bounds); }
		virtual Size nativeUpdate(Rect bounds) {
			m_parentBounds = bounds;
			SetWindowPos(handle, 0, bounds.x, bounds.y, bounds.width, bounds.height, 0);
			return bounds.size();
		}

		virtual Widget* build() { return nullptr; }
		void update(Params* params);

		Widget* construct(Params* params);

		HWND handle{ nullptr };
		std::unique_ptr<Params> params;
	protected:
		Rect m_parentBounds;
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

	template <typename WidgetType>
	WidgetType* create(Params* params, const std::function<void(WidgetType*)>& ref = nullptr) {
		WidgetType* w = static_cast<WidgetType*>((new WidgetType())->construct(params));
		if (ref) ref(w);
		return w;
	}
}

