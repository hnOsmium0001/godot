/*************************************************************************/
/*  dialogs.h                                                            */
/*************************************************************************/
/*                       This file is part of:                           */
/*                           GODOT ENGINE                                */
/*                      https://godotengine.org                          */
/*************************************************************************/
/* Copyright (c) 2007-2020 Juan Linietsky, Ariel Manzur.                 */
/* Copyright (c) 2014-2020 Godot Engine contributors (cf. AUTHORS.md).   */
/*                                                                       */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*                                                                       */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*                                                                       */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.*/
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*************************************************************************/

#ifndef TITLE_BAR_H
#define TITLE_BAR_H

#include "scene/gui/box_container.h"
#include "scene/gui/label.h"
#include "scene/gui/texture_button.h"
#include "scene/main/window.h"

class TitleBar : public Control {
	GDCLASS(TitleBar, Control);

public:
	enum TitleAlign {
		ALIGN_LEFT,
		ALIGN_CENTER,
		ALIGN_RIGHT,
	};

	enum TitleButton {
		BUTTON_CLOSE = 0b001,
		BUTTON_MAXIMIZE = 0b010,
		BUTTON_MINIMIZE = 0b100,
	};

private:
	Window *window = nullptr;
	TextureButton *close_btn;
	TextureButton *maximize_btn;
	TextureButton *minimize_btn;
	// Dragging position relative to top left of the window, including native decorations
	Point2i initial_drag_pos = { -1, -1 };
	TitleAlign title_align = ALIGN_CENTER;
	bool has_default_behaviors = false;

	void _update_button_rects();

	void _close_pressed();
	void _maximize_pressed();
	void _minimize_pressed();

protected:
	static void _bind_methods();
	virtual void _gui_input(Ref<InputEvent> p_event);
	void _notification(int p_what);

public:
	String get_title() const;
	void set_title(const String &p_title);

	TitleAlign get_title_align() const;
	void set_title_align(TitleAlign p_align);

	void bind_window(Window *p_window);
	void bind_default_behaviors(int p_flags = BUTTON_CLOSE | BUTTON_MAXIMIZE | BUTTON_MINIMIZE);

	TextureButton *get_close_button() { return close_btn; }
	TextureButton *get_maximize_button() { return maximize_btn; }
	TextureButton *get_minimize_button() { return minimize_btn; }

	void close_window();
	void maximize_window();
	void restore_window();
	void minimize_window();

	virtual Size2 get_minimum_size() const override;

	TitleBar();
	~TitleBar();
};

VARIANT_ENUM_CAST(TitleBar::TitleAlign);
VARIANT_ENUM_CAST(TitleBar::TitleButton);

#endif
