#pragma once

#include <Windows.h>
#include <windowsx.h>

#include <cstdint>
#include <string>
#include <sstream>

#include <CommCtrl.h>
#pragma comment(lib, "Comctl32.lib")

namespace nwe {
	using String = std::basic_string<TCHAR>;
	using StringStream = std::basic_stringstream<TCHAR>;

	struct Size { uint32_t width, height; };
	struct Point { int x, y; };
	struct Rect {
		int x{ 0 }, y{ 0 };
		uint32_t width{ 0 }, height{ 0 };

		Size size() const { return { width, height }; }
	};

	struct Widget;

	namespace win32 {
		struct WindowParams {
			String title{ TEXT("Window") }, className{ TEXT("Window") };
			Size size{ 640, 480 };
			HWND parent{ nullptr };
		};

		struct WidgetParams {
			String className{ TEXT("STATIC") };
			HWND parent{ nullptr };
			LONG_PTR style{ 0 };
		};

		HWND createWindow(WindowParams params, void* userData = nullptr);
		HWND createControl(WidgetParams params, uint64_t uniqueID = 0, void* userData = nullptr);
		Rect getBounds(HWND handle);
		Size measureText(HWND handle, const String& text);
		
		void setFont(HWND handle, const String& fontFamily, int size = 10);

		String messageToString(UINT msg);
	}

	int runApplication(Widget* root);

}
