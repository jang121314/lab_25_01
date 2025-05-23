#pragma once

#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <list>
#include <map>


namespace ns_md
{

	namespace types
	{
		struct Color
		{
			unsigned char r, g, b, a;
			Color(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255)
			{
				this->r = r;
				this->g = g;
				this->b = b;
				this->a = a;
			}
		};

		struct Point
		{
			float x, y;
			Point(float x = 0, float y = 0) : x(x), y(y) {}
		};

		using draw_function = std::function<int(std::string& format, std::vector<float>& arg, Color& color)>;
		using draw_function_pair_map = std::map<std::string, ns_md::types::draw_function>;

		using draw_string_function = std::function<int(std::string&, std::string&, float& pos_x, float& pos_y, float& size, Color& color)>;

		using click_event_function = std::function<int(int mouse_x, int mouse_y)>;
		
		namespace ns_obj
		{
			using button_call_function = std::function<int(std::string& format, std::string& string, float& pos_x, float& pos_y, float& width, float& height, Color& block_color, Color& border_color, Color& string_color, std::function<int()>&)>;
		}

	}

	class Main_draw
	{

		class Property
		{
			bool quit;
			std::list<types::draw_function> draw_function_list;
			std::list<types::draw_string_function> draw_string_function_list;
			std::list<types::click_event_function> click_event_function_list;


			types::draw_function_pair_map draw_function_pair;
			void set_draw_function_pair(types::draw_function_pair_map& map);

			int window_w;
			int window_h;
			types::Color backgound_color;

		public:

			Property()
			{
				quit = false;
				draw_function_pair = types::draw_function_pair_map();
				set_draw_function_pair(draw_function_pair);
			}

			bool get_quit() const;

			std::list<types::draw_function>& get_draw_function_list()
			{
				return draw_function_list;
			}

			std::list<types::draw_string_function>& get_draw_string_function_list()
			{
				return draw_string_function_list;
			}

			types::draw_function_pair_map& get_draw_function_pair()
			{
				return draw_function_pair;
			}

			std::list<types::click_event_function>& get_click_event_function_list()
			{
				return click_event_function_list;
			}

			void set_window_property(int w, int h)
			{
				window_w = w;
				window_h = h;
			}

			int get_window_w() const
			{
				return window_w;
			}

			int get_window_h() const
			{
				return window_h;
			}

			void setBackgoundColor(types::Color color)
			{
				backgound_color = color;
			}

			types::Color getBackgoundColor()
			{
				return backgound_color;
			}

		} property;

		int draw_function_call(types::draw_function function);
		int draw_string_function_call(types::draw_string_function function);
		int draw_button_function_call(types::ns_obj::button_call_function function);
		int draw_click_function_call(types::click_event_function function);

		int draw();

		types::Point scale_to_pixel(types::Point p) const;
		types::Point mirror_y(types::Point p) const;
		public:

		Main_draw(int width = 800, int height = 800, std::string title = "Main_draw");

		bool activated() const;

		int append_draw_function(types::draw_function function);
		int append_draw_function(types::draw_string_function function);
		int append_event_function(types::click_event_function function);
		int append_object_function(types::ns_obj::button_call_function function);

		int run();

		~Main_draw();

		types::Point get_point(types::Point p) const;
		types::Point get_point_p(types::Point p) const;
		types::Point get_point_2f(float x, float y) const;
		types::Point get_point_in_ndc(types::Point p) const;
		types::Point get_point_in_ndc_2f(float x, float y) const;
		types::Point scale_to_screen(types::Point p) const;
		
		void set_backgound_color(types::Color color = types::Color(0, 0, 0))
		{
			property.setBackgoundColor(color);
		}

		Main_draw& operator=(const Main_draw&) = delete;

	};



}