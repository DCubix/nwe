#include <iostream>

#include "nwe_core.h"
#include "nwe_widget.h"
#include "nwe_label.h"
#include "nwe_button.h"
#include "nwe_container.h"
#include "nwe_column.h"

int main(int argc, char** argv) {
	return nwe::runApplication(
		WID(nwe::Container)(new nwe::ContainerParams{
			.child = WID(nwe::Column)(new nwe::ColumnParams{
				.children = {
					WID(nwe::Label)(new nwe::LabelParams{
						.text = TEXT("Hello World!")
					}),
					WID(nwe::Label)(new nwe::LabelParams{
						.text = TEXT("Another line...")
					}),
					WID(nwe::Button)(new nwe::ButtonParams{
						.text = TEXT("Click on this Button!"),
						.onPressed = []() {
							MessageBox(NULL, TEXT("Hello World! This is a Button click event!"), TEXT("Hello Message"), MB_OK);
						}
					})
				},
				.alignment = nwe::Alignment::Stretch
			})
		})
	);
}
