#include "Main_draw.hpp"

#include <raylib.h>



namespace ns_md
{

	namespace util
	{
		Color toColor(types::Color input_color)
		{
			return Color({ input_color.r, input_color.g, input_color.b, input_color.a });
		}

		inline float fabs(float x)
		{
			return 0 > x ? -x : x;
		}

	}

	namespace call_draw_function
	{
		int call_draw_rectangle(std::string& format, std::vector<float>& arg, types::Color& color_)
		{
			int error = 0;
			if (4 <= arg.size())
			{
				arg[0] -= arg[2] / 2;
				arg[1] -= arg[3] / 2;
				Color color = util::toColor(color_);
				DrawRectangle(arg[0], arg[1], arg[2], arg[3], color);
			}
			else error = -2;
			return error;
		}

		int call_draw_rectangle_line(std::string& format, std::vector<float>& arg, types::Color& color_)
		{
			int error = 0;
			if (4 <= arg.size())
			{
				arg[0] -= arg[2] / 2;
				arg[1] -= arg[3] / 2;
				Color color = util::toColor(color_);
				DrawRectangleLines(arg[0], arg[1], arg[2], arg[3], color);
			}
			else error = -2;
			return error;
		}

		int call_draw_rectangle_round(std::string& format, std::vector<float>& arg, types::Color& color_)
		{
			int error = 0;
			if (6 <= arg.size())
			{
				arg[0] -= arg[2] / 2;
				arg[1] -= arg[3] / 2;
				Color color = util::toColor(color_);
				Rectangle rect({ arg[0], arg[1], arg[2], arg[3] });
				DrawRectangleRounded(rect, arg[4], arg[5], color);
				/*std::cout << __FILE__ << "::" << __LINE__ << "hello" << "\n";
				std::cout << format << ", x: " << arg[0] << ", y: " << arg[1] << ", size: " << arg[2] << ", " << arg[3] << ", color: " << color.r << "\n";*/
			}
			else error = -2;
			return error;
		}

		int call_draw_rectangle_round_line(std::string& format, std::vector<float>& arg, types::Color& color_)
		{
			int error = 0;
			if (6 <= arg.size())
			{
				arg[0] -= arg[2] / 2;
				arg[1] -= arg[3] / 2;
				Color color = util::toColor(color_);
				Rectangle rect({ arg[0], arg[1], arg[2], arg[3] });
				DrawRectangleRoundedLines(rect, arg[4], arg[5], color);
			}
			else error = -2;
			return error;
		}

		int call_draw_circle(std::string& format, std::vector<float>& arg, types::Color& color_)
		{
			int error = 0;
			if (3 <= arg.size())
			{
				Color color = util::toColor(color_);
				DrawCircle(arg[0], arg[1], arg[2], color);
			}
			else error = -2;
			return error;
		}

		int call_draw_string(std::string& string, float pos_x, float pos_y, float font_size, types::Color& color_)
		{
			int error = 0;
			{
				Color color = util::toColor(color_);
				float w = MeasureText(string.c_str(), font_size);
				float h = font_size;
				pos_x -= w / 2;
				pos_y -= h / 2;

				DrawText(string.c_str(), pos_x, pos_y, font_size, color);
				/*std::cout << __FILE__ << "::" << __LINE__ << "hello" << "\n";
				std::cout << string << ", x: " << pos_x << ", y: " << pos_y << ", size: " << font_size << ", color: " << color.r << "\n";*/
			}
			return error;
		}

	}

	void Main_draw::Property::set_draw_function_pair(types::draw_function_pair_map& map)
	{
		std::string rect = "Rect", line = "Line", circle = "Circle", round = "Round";
		map[rect] = call_draw_function::call_draw_rectangle;
		map[rect + line] = call_draw_function::call_draw_rectangle_line;
		map[rect + round] = call_draw_function::call_draw_rectangle_round;
		map[rect + round + line] = call_draw_function::call_draw_rectangle_round_line;
		map[circle] = call_draw_function::call_draw_circle;
	}

	bool Main_draw::Property::get_quit() const
	{
		return quit || WindowShouldClose();
	}

	Main_draw::Main_draw(int width, int height, std::string title)
	{
		InitWindow(width, height, title.c_str());
		SetTargetFPS(60);
		property = Property();
		property.set_window_property(width, height);
		set_backgound_color();
	}

	int Main_draw::draw_function_call(types::draw_function function)
	{
		std::string format;
		std::vector<float> arg;
		types::Color color;

		int error = function(format, arg, color);
		if (error != 0) return error;

		auto call_function = property.get_draw_function_pair().find(format);

		if (property.get_draw_function_pair().end() != call_function) (call_function->second)(format, arg, color);
		else error = -2;

		return error;
	}

	int Main_draw::draw_string_function_call(types::draw_string_function function)
	{
		std::string format;
		std::string string;
		float pos_x, pos_y, size;
		types::Color color;

		int error = function(format, string, pos_x, pos_y, size, color);
		if(format == "String") call_draw_function::call_draw_string(string, pos_x, pos_y, size, color);

		return error;
	}

	int Main_draw::draw_button_function_call(types::ns_obj::button_call_function function)
	{
		int error = 0;
		std::string format;
		std::string string;
		float pos_x, pos_y, width, height;
		types::Color block_color, border_color, string_color;
		std::function<int()> call_function;

		error = function(format, string, pos_x, pos_y, width, height, block_color, border_color, string_color, call_function);

		if (format == "Button")
		{
			float roundness = 0.2;
			float segments = 64;
			auto add_rect_function = [=](std::string format, types::Color put_color) {
				return append_draw_function([=](std::string& put_format, std::vector<float>& arg, ns_md::types::Color& color)
					{
						put_format = format;
						arg.push_back(pos_x);
						arg.push_back(pos_y);
						arg.push_back(width);
						arg.push_back(height);
						arg.push_back(roundness);
						arg.push_back(segments);
						color = put_color;
						return 0;
					});
				};
			error = add_rect_function("RectRound", block_color);
			error = add_rect_function("RectRoundLine", border_color);
			auto add_text_function = [=]() {
				types::Point point_wh = types::Point{ -0.925, 0 };
				point_wh = this->scale_to_screen(point_wh);
				float size = point_wh.x;
				return append_draw_function([=](std::string& format, std::string& put_string, float& put_pos_x, float& put_pos_y, float& put_size, ns_md::types::Color& color)
					{
						format = "String";
						put_string = string;
						put_pos_x = pos_x;
						put_pos_y = pos_y;
						put_size = size;
						color = string_color;
						return 0;
					});
				} ();
			error = append_event_function([=](float mouse_x, float mouse_y)
				{
					int error = 0;
					float delta_x = pos_x - mouse_x;
					float delta_y = pos_y - mouse_y;
					using util::fabs;
					bool in_w = fabs(delta_x) < width / 2;
					bool in_h = fabs(delta_y) < height / 2;
					if (in_w && in_h) error = call_function();
					return error;
				});
		}

		return error;
	}

	int Main_draw::draw_click_function_call(types::click_event_function function)
	{
		Vector2 vector2 = GetMousePosition();
		return function(vector2.x, vector2.y);
	}

	int Main_draw::draw()
	{
		int error = 0;
		BeginDrawing();
		ClearBackground( util::toColor( property.getBackgoundColor() ) );
		//DrawRectangle(244, 244, 244, 244, { 255, 0, 0, 255 });
		if(IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) for (auto it = property.get_click_event_function_list().begin(); it != property.get_click_event_function_list().end(); ++it)
		{
			error = draw_click_function_call(*it);
		}
		for (auto it = property.get_draw_function_list().begin(); it != property.get_draw_function_list().end(); ++it)
		{
			error = draw_function_call(*it);
		}
		for (auto it = property.get_draw_string_function_list().begin(); it != property.get_draw_string_function_list().end(); ++it)
		{
			error = draw_string_function_call(*it);
		}
		EndDrawing();
		return 0;
	}

	int Main_draw::append_draw_function(types::draw_function function)
	{
		property.get_draw_function_list().push_back(function);
		return 0;
	}

	int Main_draw::append_draw_function(types::draw_string_function function)
	{
		property.get_draw_string_function_list().push_back(function);
		return 0;
	}

	int Main_draw::append_event_function(types::click_event_function function)
	{
		property.get_click_event_function_list().push_back(function);
		return 0;
	}

	int Main_draw::append_object_function(types::ns_obj::button_call_function function)
	{
		draw_button_function_call(function);
		return 0;
	}

	int Main_draw::run()
	{
		int error = 0;
		if (property.get_quit())
		{
			return -1;
		}
		else
		{
			error = draw();
		}
		return 0;

	}

	bool Main_draw::activated() const
	{
		return property.get_quit();
	}

	Main_draw::~Main_draw()
	{
		CloseWindow();
	}

	types::Point Main_draw::scale_to_pixel(types::Point p) const
	{
		p.x = property.get_window_w() * (p.x + 1) / 2;
		p.y = property.get_window_h() * (p.y + 1) / 2;
		return p;
	}
	types::Point Main_draw::mirror_y(types::Point p) const
	{
		p.y = property.get_window_h() - p.y;
		return p;
	}

	types::Point Main_draw::get_point(types::Point p) const
	{
		return mirror_y(p);
	}
	types::Point Main_draw::get_point_p(types::Point p) const
	{
		return mirror_y(p);
	}
	types::Point Main_draw::get_point_2f(float x, float y) const
	{
		types::Point p(x, y);
		return mirror_y(p);
	}
	types::Point Main_draw::get_point_in_ndc(types::Point p) const
	{
		return scale_to_pixel(scale_to_pixel(p));
	}
	types::Point Main_draw::get_point_in_ndc_2f(float x, float y) const
	{
		types::Point p(x, y);
		return scale_to_pixel(scale_to_pixel(p));
	}
	types::Point Main_draw::scale_to_screen(types::Point p) const
	{
		return scale_to_pixel(p);
	}

}