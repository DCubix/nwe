#include <iostream>

#include "nwe_core.h"
#include "nwe_widget.h"
#include "nwe_label.h"
#include "nwe_button.h"
#include "nwe_container.h"
#include "nwe_column.h"
#include "nwe_row.h"
#include "nwe_edit.h"

class MyApp : public nwe::Widget {
public:
	nwe::Label* valueLabel;

	Widget* build() override {
		return nwe::create<nwe::Container>(new nwe::ContainerParams{
			.child = nwe::create<nwe::Column>(new nwe::ColumnParams{
				.children = {
					nwe::create<nwe::Label>(new nwe::LabelParams{
						.text = TEXT("Hello World!")
					}),
					nwe::create<nwe::Label>(new nwe::LabelParams{
						.text = TEXT("Value: "),
					}, Ref(nwe::Label, valueLabel)),
					nwe::create<nwe::Container>(new nwe::ContainerParams{
						.child = nwe::create<nwe::Row>(new nwe::RowParams{
							.children = {
								nwe::create<nwe::Button>(new nwe::ButtonParams{
									.text = TEXT("Click Me!"),
									.onPressed = []() {
										MessageBox(NULL, TEXT("Hello World! This is a Button click event!"), TEXT("Hello Message"), MB_OK);
									}
								}),
								nwe::create<nwe::Button>(new nwe::ButtonParams{
									.text = TEXT("Button 2"),
									.onPressed = []() {
										MessageBox(NULL, TEXT("Hello World! This is another Button"), TEXT("Hello Message"), MB_OK);
									}
								}),
								nwe::create<nwe::Edit>(new nwe::EditParams{
									.onChange = [&](nwe::String str) {
										valueLabel->update(new nwe::LabelParams{
											.text = TEXT("Value: ") + str,
										});
									}
								})
							},
							.alignment = nwe::Alignment::Center
						}),
						.padding = { 0, 0, 0, 0 },
						.size = { 0, 40 }
					}),
				},
				.alignment = nwe::Alignment::Stretch
			})
		});
	}
};

int main(int argc, char** argv) {
	return nwe::runApplication(new MyApp());
}
