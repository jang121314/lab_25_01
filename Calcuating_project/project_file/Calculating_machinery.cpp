#include "Calculating_machinery.hpp"
#include "Draw_link.hpp"

namespace ns_cm
{
	Calculating_machinery::Calculating_machinery()
	{
		md = new ns_md::Main_draw(600, 800, u8"Calculating");
		flag = Flag::None;
		dotEvent = false;
		dotPoint = 0;
		Init();
	}

	int Calculating_machinery::Init()
	{
		ns_dl::Draw_link* dl;
		dl = new ns_dl::Draw_link(*md);
		
		using Color = ns_md::types::Color;

		dl->setting(ns_dl::Draw_link::Setting_flag::gl);
		//dl->rect_round(0, 0, -0.3, -0.3);
		//dl->text(0, 0, "hello world", -0.973, Color(255, 0, 0));

		{

			auto& md = *this->md;
			md.append_draw_function([this](std::string& format, std::string& string, float& pos_x, float& pos_y, float& size, Color& color) {
				format = "String";
				double& sum = (flag == Flag::None ? a : b);
				
				string = std::to_string(sum);
				std::string string_point = std::to_string(dotPoint);
				while (string_point.back() == '0') string_point.pop_back();
				int min_size = string_point.length();
				int dot_len = 6;
				while (string.back() == '0')
				{
					if(dot_len-- + 2 < min_size) break;
					string.pop_back();
				}
				//if (string.back() == '1' && 0.0000009 < dotPoint) string.pop_back();
				if (string.back() == '.' && !dotEvent) string.pop_back();

				pos_x = 300;
				pos_y = 100;
				size = 80;
				color = Color(255, 255, 255);

				return 0; 
			});

			md.append_draw_function([this](std::string& format, std::string& string, float& pos_x, float& pos_y, float& size, Color& color) {
				format = "String";
				string = flag == Flag::None ? "" : flag == Flag::Addition ? "+" : flag == Flag::Subtraction ? "-" : flag == Flag::Multiplication ? "*" : flag == Flag::Division ? "/" : "error";
				pos_x = 550;
				pos_y = 100;
				size = 40;
				color = Color(255, 255, 255);
				return 0;
				});
			md.append_draw_function([this](std::string& format, std::string& string, float& pos_x, float& pos_y, float& size, Color& color) {
				if (flag != Flag::None)
				{
					format = "String";
					string = std::to_string(a);
					while (string.back() == '0')
					{
						string.pop_back();
					}
					if (string.back() == '.' && !dotEvent) string.pop_back();
					pos_x = 450;
					pos_y = 40;
					size = 40;
					color = Color(255, 255, 255);
				}
				else
				{
					format = "NULL";
				}
				return 0;
				});
		}

		{
			Color block(14, 14, 14), border(255, 255, 255), text(255, 255, 255);
			auto grid_add = [=](float x, float y, std::string name, std::function<int()> function) {
				float w = 2.0F / 4, h = 2.0F / 6;
				x *= w, y *= h; x += w / 2, y += h / 2;
				return dl->button(x - 1, 1 - y, w - 1 - 0.05, h - 1 - 0.05, name, function, block, border, text);
				};

			

			auto dot_point_function = [this]() {
				double& augend = (flag == Flag::None ? a : b);
				std::string string = std::to_string(augend);
				string = string.substr(string.rfind('.')+1);
				while (string.length() > 0 && string.back() == '0') string.pop_back();
				int off = string.length();
				dotPoint = 0.1;
				while (off--)
				{
					dotPoint /= 10;
				}
				};

			auto dot_check = [this]() {
				double& augend = (flag == Flag::None ? a : b);
				dotEvent = !int_check(augend);

				};


			{
				auto append = [this](int addend) {
					double& augend = (flag == Flag::None ? a : b);

					if (dotEvent)
					{
						/*std::string string = std::to_string(augend);
						string = string.substr(string.rfind('.') + 1);
						int index = string.size()-1;
						while (string[index] == '0') if (index-- == 0) break;
						index += 2;
						float offset = 1;
						while (index--) offset /= 10;
						augend += offset * addend;*/
						augend += dotPoint * addend;
						dotPoint /= 10;
					}
					else
					{
						augend *= 10;
						augend += addend;
					}
					return 0;
					};

				for (int i = 0; i < 9; i++)
				{
					int d = i + 1;
					int y = i / 3;
					grid_add(i % 3, y + 1, std::to_string(d), [this, d, append]()
						{
							return append(d);
						}
					);
				}
				grid_add(1, 0, "0", [this, append]()
					{
						if (0.0000009 > dotPoint) dotPoint = 0.1;
						return append(0);
					}
				);
			}

			{
				std::string names = "+-*/";
				for (int i = 0; i < 4; i++)
				{
					grid_add(3, i+1, names.substr(i, 1), [this, i]()
						{
							dotEvent = false;
							dotPoint = 0.1;
							switch (i)
							{
							case 0:
								flag = Flag::Addition;
								break;
							case 1:
								flag = Flag::Subtraction;
								break;
							case 2:
								flag = Flag::Multiplication;
								break;
							case 3:
								flag = Flag::Division;
								break;
							}
							return 0;
						}
					);
				}

				{
					grid_add(0, 0, "+-", [this]()
						{
							double& sum = (flag == Flag::None ? a : b);
							sum = -sum;
							return 0;
						}
					);
					grid_add(2, 0, ".", [this, dot_check]()
						{
							dotEvent = !dotEvent;
							if (!dotEvent) dot_check();
							else dotPoint = 0.1;
							return 0;
						}
					);
					grid_add(3, 0, "=", [this, dot_check, dot_point_function]()
						{
							switch (flag)
							{
							case Flag::None:
								break;
							case Flag::Addition:
								a = a + b;
								break;
							case Flag::Subtraction:
								a = a - b;
								break;
							case Flag::Multiplication:
								a = a * b;
								break;
							case Flag::Division:
								if (b != 0) a = a / b;
								else a = 0;
								break;
							}
							b = 0;
							flag = Flag::None;
							dot_check();
							dot_point_function();
							return 0;
						}
					);

					grid_add(0, 4, "C", [this]()
						{
							a = 0, b = 0, dotEvent = false, flag = Flag::None, dotPoint = 0.1;
							return 0;
						}
					);
					grid_add(1, 4, "CE", [this]()
						{
							double& augend = (flag == Flag::None ? a : b);
							augend = 0, dotEvent = false, dotPoint = 0.1;
							return 0;
						}
					);
					grid_add(2, 4, "<-", [this]()
						{
							double& augend = (flag == Flag::None ? a : b);
							if (int_check(augend))
							{
								if (dotEvent) dotEvent = false;
								else augend = (int)augend / 10;
							}
							else
							{
								/*float addend = 0;
								std::string string = std::to_string(augend);
								string = string.substr(string.rfind('.')+1);
								int index = string.size() - 1;
								while (string[index] == '0')
								{
									if (index-- == 0) break;
								}
								addend = string[index] - '0';
								float offset = 1;
								index++;
								while (index--) offset /= 10;
								addend *= offset;
								augend -= addend;*/
								std::string string = std::to_string(augend);
								string = string.substr(string.rfind('.') + 1);
								while (string.back() == '0') string.pop_back();
								double addend = string.back() - '0';
								dotPoint *= 10;
								augend -= addend * dotPoint;
								
							}
							return 0;
						}
					);
				}

			}
			
			
		}

		


		delete dl;
		return 0;
	}

	int Calculating_machinery::run()
	{
		while (!md->activated())
		{
			md->run();
		}
		return 0;
	}

	Calculating_machinery::~Calculating_machinery()
	{

		delete md;
	}

}