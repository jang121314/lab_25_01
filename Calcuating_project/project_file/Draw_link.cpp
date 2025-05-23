
#include "Draw_link.hpp"

namespace ns_dl
{
	int Draw_link::rect(float x, float y, float w, float h, Color _color)
	{
		Md& md = this->md;
		auto pos_setting_function = this->pos_setting_function;
		auto size_setting_function = this->size_setting_function;

		return md.append_draw_function([=, &md]
		(std::string& format, std::vector<float>& arg, ns_md::types::Color& color)
			{
				Point point_xy(x, y);
				point_xy = pos_setting_function(point_xy);
				Point point_wh(w, h);
				point_wh = size_setting_function(point_wh);
				format = "Rect";
				arg.push_back(point_xy.x);
				arg.push_back(point_xy.y);
				arg.push_back(point_wh.x);
				arg.push_back(point_wh.y);
				color = _color;
				return 0;
			}
		);
	}

	int Draw_link::rect_round(float x, float y, float w, float h, Color _color)
	{
		
		Md& md = this->md;
		auto pos_setting_function = this->pos_setting_function;
		auto size_setting_function = this->size_setting_function;

		float roundness = 0.2;
		float segments = 16;

		return md.append_draw_function([=, &md]
		(std::string& format, std::vector<float>& arg, ns_md::types::Color& color)
			{
				Point point_xy(x, y);
				point_xy = pos_setting_function(point_xy);
				Point point_wh(w, h);
				point_wh = size_setting_function(point_wh);
				format = "RectRound";
				arg.push_back(point_xy.x);
				arg.push_back(point_xy.y);
				arg.push_back(point_wh.x);
				arg.push_back(point_wh.y);
				arg.push_back(roundness);
				arg.push_back(segments);
				color = _color;
				return 0;
			}
		);
	}

	int Draw_link::rect_round_line(float x, float y, float w, float h, Color _color)
	{

		Md& md = this->md;
		auto pos_setting_function = this->pos_setting_function;
		auto size_setting_function = this->size_setting_function;

		float roundness = 0.2;
		float segments = 64;

		return md.append_draw_function([=, &md]
		(std::string& format, std::vector<float>& arg, ns_md::types::Color& color)
			{
				Point point_xy(x, y);
				point_xy = pos_setting_function(point_xy);
				Point point_wh(w, h);
				point_wh = size_setting_function(point_wh);
				format = "RectRoundLine";
				arg.push_back(point_xy.x);
				arg.push_back(point_xy.y);
				arg.push_back(point_wh.x);
				arg.push_back(point_wh.y);
				arg.push_back(roundness);
				arg.push_back(segments);
				color = _color;
				return 0;
			}
		);
	}

	int Draw_link::circle(float x, float y, float _r, Color _color)
	{
		Md& md = this->md;
		auto pos_setting_function = this->pos_setting_function;
		auto size_setting_function = this->size_setting_function;

		return md.append_draw_function([=, &md]
		(std::string& format, std::vector<float>& arg, ns_md::types::Color& color)
			{
				Point point_xy(x, y);
				point_xy = pos_setting_function(point_xy);
				Point point_wh(_r, _r);
				point_wh = size_setting_function(point_wh);
				float r = point_wh.x < point_wh.y ? point_wh.x : point_wh.y;
				format = "Circle";
				arg.push_back(point_xy.x);
				arg.push_back(point_xy.y);
				arg.push_back(_r);
				color = _color;
				return 0;
			}
		);
	}

	int Draw_link::text(float x, float y, std::string text, float _size, Color _color)
	{
		Md& md = this->md;
		auto pos_setting_function = this->pos_setting_function;
		auto size_setting_function = this->size_setting_function;
		return md.append_draw_function([=, &md]
		(std::string& format, std::string& string, float& pos_x, float& pos_y, float& size, Color& color)
			{
				Point point_xy(x, y);
				point_xy = pos_setting_function(point_xy);
				Point point_wh(_size, _size);
				point_wh = size_setting_function(point_wh);
				size = point_wh.x;
				format = "String";
				pos_x = point_xy.x;
				pos_y = point_xy.y;
				string = text;
				color = _color;
				return 0;
			}
		);
	}

	int Draw_link::button(float x, float y, float w, float h, std::string string, std::function<int()> function, Color block_color, Color border_color, Color string_color)
	{
		Md& md = this->md;
		auto pos_setting_function = this->pos_setting_function;
		auto size_setting_function = this->size_setting_function;

		{
			Point point = Point(x, y);
			point = pos_setting_function(point);
			x = point.x, y = point.y;
			point = Point(w, h);
			point = size_setting_function(point);
			w = point.x, h = point.y;
		}

		return md.append_object_function([=, &md](std::string& format, std::string& put_string, float& pos_x, float& pos_y, float& width, float& height, Color& put_block_color, Color& put_border_color, Color& put_string_color, std::function<int()>& call_function)
			{
				format = "Button";
				put_string = string;
				pos_x = x;
				pos_y = y;
				width = w;
				height = h;
				put_block_color = block_color;
				put_border_color = border_color;
				put_string_color = string_color;
				call_function = function;
				return 0;
			});
	}


	void Draw_link::setting(Setting_flag flag)
	{
		Md& md = this->md;

		auto call_nds_size = [&md](Point p) {
			return md.scale_to_screen(p);
			};
		auto call_pixel_size = [&md](Point p) {
			return p;
			};

		switch (flag)
		{
		case Setting_flag::pixel:
			pos_setting_function = [&md](Point p) {
				return md.get_point(p);
				};
			size_setting_function = call_pixel_size;
			break;
		case Setting_flag::nds:
			pos_setting_function = [&md](Point p) {
				return md.get_point_in_ndc(p);
				};
			size_setting_function = call_nds_size;
			break;
		case Setting_flag::gl:
			pos_setting_function = [&md](Point p) {
				return md.scale_to_screen(p);
				};
			size_setting_function = call_nds_size;
			break;
		case Setting_flag::raylib:
			pos_setting_function = [&md](Point p) {
				return p;
				};
			size_setting_function = call_pixel_size;
			break;
		}
	}

}

