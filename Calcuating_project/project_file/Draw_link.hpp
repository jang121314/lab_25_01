#pragma once
#include "Main_draw.hpp"

namespace ns_dl
{
	

	class Draw_link
	{

		using Color = ns_md::types::Color;
		using Point = ns_md::types::Point;
		using Md = ns_md::Main_draw;

		ns_md::Main_draw& md;
		std::function<Point(Point)> pos_setting_function;
		std::function <Point(Point)> size_setting_function;

	public:

		enum class Setting_flag
		{
			pixel = 0,
			nds = 1,
			gl = 2,
			raylib = 4,
		};

		Draw_link(ns_md::Main_draw& md) : md(md)
		{
			setting(Setting_flag::pixel);
		}

		void setting(Setting_flag flag);

		int rect(float x, float y, float w, float h, Color color = Color());
		int rect_round(float x, float y, float w, float h, Color color = Color());
		int rect_round_line(float x, float y, float w, float h, Color color = Color());
		int circle(float x, float y, float r, Color color = Color());
		int text(float x, float y, std::string text, float size = -0.973F, Color _color = Color());
		int button(float x, float y, float w, float h, std::string string, std::function<int()> function, Color block_color = Color(), Color border_color = Color(), Color string_color = Color());
	};


}

