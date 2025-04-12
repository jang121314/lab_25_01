#include "Class.hpp"

/*
* 메인 클래스, 프로그램의 캡슐화 담당
*/
class Class
{
	/*
	* 연산 기능 전용 클래스
	*/
	class Sumer
	{
	public:
		template<typename T>
		static T max(T a, T b)
		{
			return a > b ? a : b;
		}
	};

	/*
	* 텍스트 연산 기능 전용 클래스
	*/
	class Parser
	{

	public:

		int subString(std::vector<std::string>& output, std::string input, char low, char high)
		{
			output.push_back({});
			for (char get : input)
			{
				if (get == low)
				{
					output.push_back({});
					output.back().push_back(get);
				}
				else if (get == high)
				{
					output.back().push_back(get);
					output.push_back({});
				}
				else output.back().push_back(get);
			}

			return 0;
		}

		int twoString(std::string& low, std::string& high, std::string input, char point)
		{
			int flag = 0;
			for (char get : input)
			{
				if (get == point)
				{
					flag = 1;
				}
				else  switch (flag)
				{
				case 0:
					low.push_back(get);
					break;
				case 1:
					high.push_back(get);
					break;
				}
			}
			return 0;
		}

		int twoString(std::vector<std::string>& lowOutput, std::vector<std::string>& highOutPut, std::vector<std::string> input, char point)
		{

			for (std::string getString : input)
			{
				lowOutput.push_back({});
				highOutPut.push_back({});
				twoString(lowOutput.back(), highOutPut.back(), getString, point);
			}
			return 0;
		}

		int squish(std::string& string)
		{
			std::string output;
			for (char get : string)
			{
				if (get == ' ' || get == '\t' || get == '\n');
				else output.push_back(get);
			}
			string = output;
			return 0;
		}

		int squish(std::vector<std::string>& vector)
		{
			for (std::string& string : vector)
			{
				squish(string);
			}
			return 0;
		}

		int trim(std::string& string)
		{
			size_t index = 0;
			for (char get : string)
			{
				if (get == ' ' || get == '\t' || get == '\n') index++;
				else break;
			}
			if (string.size() <= index)
			{
				string = "";
				return -1;
			}
			std::string output = string.substr(index);
			for (char& get = output.back(); get == ' ' || get == '\t' || get == '\n'; output.pop_back());
			for (char& get = output.back(); get == ' ' || get == '\t' || get == '\n'; output.pop_back());
			string = output;
			return 0;
		}

		int tapToSpace(std::string& string)
		{
			std::string output;
			for (char get : string)
			{
				if (get == '\t')
				{
					output.append("     ");
				}
				else
				{
					output.push_back(get);
				}
			}
			string = output;
			return 0;
		}

		int split(std::vector<std::string>& output, std::string string, char point)
		{
			long long low = -1;
			long long index = 0;
			for (char get : string)
			{
				if (get == point)
				{
					output.push_back( string.substr (low+1, index-low-1) );
					low = index;
				}
				index++;
			}
			if (index > low + 1)
			{
				output.push_back( string.substr(low + 1) );
			}
			return 0;
		}

		int to﻿Squish(std::string& string, char point)
		{
			std::string output;
			for (char get : string)
			{
				if(get != point) output.push_back(get);
			}
			string = output;
			return 0;
		}

	};

	/*
	* 속성 값을 가지는 클래스, 동적 할당을 더 쉽게 하도록 하는 특수 클래스임
	*/
	template<typename T>
	class Property
	{
		T* val = nullptr;
		bool exist = false;

		int delVal()
		{
			if (val != nullptr)
			{
				delete val;
				val = nullptr;
			}
			exist = false;
			return 0;
		}

		int setVal(T get)
		{
			delVal();
			val = new T(get);
			exist = true;
			return 0;
		}

		int empty()
		{
			if (!val) return 1;
			return 0;
		}

	public:
		Property() : val(nullptr), exist(false) {}
		Property(T& get) : val(nullptr), exist(true)
		{
			setVal(get);
		}
		Property(Property& S)
		{
			if (S.exist)
			{
				setVal(*S.val);
				exist = S.exist;
			}
			else
			{
				delVal();
				exist = false;
			}
		}

		~Property()
		{
			delVal();
		}

		Property& operator=(T get)
		{
			setVal(get);
			return *this;
		}

		Property& operator|=(T get)
		{
			if (!exist) setVal(get);
			return *this;
		}

		Property& operator--(int)
		{
			delVal();
			return *this;
		}

		Property& operator--()
		{
			delVal();
			return *this;
		}

		T& operator*()
		{
			if (empty() == 1)
			{
				setVal({});
			}

			return *val;
		}

		T* operator->()
		{
			if (empty() == 1)
			{
				setVal({});
			}
			return val;
		}

		bool isExist()
		{
			return exist;
		}

	};

	/*
	* style들의 값들을 가지는 가상 클래스, 다만 정의가 없는 가상 함수가 있지는 않기에 기능이 없을뿐 가상 클래스로 취급을 받지는 않음
	*/
	class VirtualStyle
	{

#define named __name__

	protected:
	public:

		struct VtrualProperty
		{
			virtual std::string getNamed() = 0;

			virtual int isName(std::string string)
			{
				return string == getNamed() ? 1 : 0;
			}

			virtual int setDatafunction(std::string data) = 0;

			virtual int setChild(std::string name, std::string data)
			{
				return 0;
			}

			int setData(std::string string)
			{
				Parser parser;
				std::string name, data;
				parser.twoString(name, data, string, ':');
				parser.squish(name);
				parser.squish(data);
				return setData(name, data);
			}

			int setData(std::string name, std::string data)
			{
				if (setChild(name, data))
				{

				}
				else if (isName(name) == 1)
				{
					setDatafunction(data);
					return 1;
				}
				return -1;
			}
		};

		struct InChildVtrualProperty : public VtrualProperty
		{
			virtual int setDataChild(std::string name, std::string data) = 0;

			int setChild(std::string name, std::string data) override
			{
				Parser parser;
				std::string low, high;
				parser.twoString(low, high, name, '-');
				parser.squish(low);
				parser.squish(high);
				if (low == getNamed())
				{
					return setDataChild(high, data);
				}
				else return 0;
			}

		};


	private:

		struct IntegerProperty : public VtrualProperty
			{
				virtual std::string getNamed() override
				{
					return "IntegerProperty";
				}

				typedef long long int Type;
				Property<Type> IntegerData;

				virtual int setFunction(Type get)
				{
					IntegerData = get;
					return 0;
				}

				virtual int setDatafunction(std::string data) override
				{
					std::vector<int> vector;
					for (char get : data)
					{
						if ('0' <= get && get <= '9')
						{
							vector.push_back(int(get - '0'));
						}
					}
					long long int put = 0;
					size_t carry = 1;
					size_t vsize = 10 < vector.size() ? 10 : vector.size();
					for (int index = vsize - 1; index >= 0; index--)
					{
						char get = vector.at(index);
						put += get * carry;
						carry *= 10;
					}
					setFunction(put % (65536));
					return 0;
				}

				virtual Type& operator*()
				{
					return *IntegerData;
				}

				virtual Type* operator->()
				{
					return IntegerData.operator->();
				}
			};

		struct lengthPropety : public IntegerProperty
		{

			bool _auto_ = false;

			virtual int setDatafunction(std::string data) override
			{
				if (data == "auto")
				{
					_auto_ = true;
				}
				else
				{
					return IntegerProperty::setDatafunction(data);
				}
				return 0;
			}
		};

	public:

		struct Color : public VtrualProperty
		{
			static constexpr const char* named = "color";

			std::string getNamed() override
			{
				return named;
			}

			unsigned char r, g, b, a;

			Color(unsigned char r = 0, unsigned char g = 0, unsigned char b = 0, unsigned char a = 255) : r(r), g(g), b(b), a(a)
			{

			}

			SDL_Color toSDL()
			{
				return SDL_Color{ .r = r, .g = g, .b = b, .a = a };
			}

			int setDatafunction(std::string data) override
			{
				if (data.empty())
				{
					return -1;
				}
				else if (data.at(0) == '#')
				{
					if (6 < data.size())
					{
						
						std::vector<int> val;
						for (int i = 0; i < 3; i++)
						{
							std::stringstream sstream;
							sstream << std::hex << data.substr(i*2+1, 2);
							val.push_back(0);
							sstream >> std::hex >> val.back();
						}
						r = val.at(0);
						g = val.at(1);
						b = val.at(2);
					}
					if (8 < data.size())
					{
						std::stringstream sstream;
						sstream << std::hex << data.substr(6);
						int val = 0;
						sstream >> val;
						a = val;
					}
					return 0;
				}
				if (data == "white")
				{
					r = 255;
					g = 255;
					b = 255;
					return 0;
				}
				if (data == "gray")
				{
					r = 128;
					g = 128;
					b = 128;
					return 0;
				}
				if (data == "black")
				{
					r = g = b = 0;
					return 0;
				}
				if (data == "red")
				{
					r = 255;
					return 0;
				}
				if (data == "yellow")
				{
					r = 255;
					g = 255;
					return 0;
				}
				if (data == "green")
				{
					g = 255;
					return 0;
				}
				if (data == "aqua ")
				{
					g = 255;
					b = 255;
					return 0;
				}
				if (data == "blue")
				{
					b = 255;
					return 0;
				}
				if (data == "magenta")
				{
					r = 255;
					b = 255;
					return 0;
				}
				return -2;
			}

		};

		struct Font : public InChildVtrualProperty
		{
			static constexpr const char* named = "font";
			std::string getNamed() override
			{
				return named;
			}

			struct Size : public IntegerProperty
			{
				std::string getNamed() override
				{
					return "size";
				}

			};

			Size size = {};

			int setDataChild(std::string name, std::string data) override
			{
				size.setData(name, data);
				return 1;
			}

			int setDatafunction(std::string data) override
			{
				return 0;
			}

			int apply(Font s)
			{
				size.IntegerData |= *s.size.IntegerData;
				return 0;
			}
		};

		struct Text : public InChildVtrualProperty
		{

			static constexpr const char* named = "text";
			std::string getNamed() override
			{
				return named;
			}

			struct Size : public IntegerProperty
			{
				std::string getNamed() override
				{
					return "size";
				}

			};

			struct Align : VtrualProperty
			{
				std::string getNamed() override
				{
					return "align";
				}

				enum class Type
				{
					LEFT,
					CENTER,
					RIGHT,
				};

				Property<Type> type;

				int setDatafunction(std::string data) override
				{
					if (data == "left")
					{
						type = Type::LEFT;
						return 0;
					}
					if (data == "center")
					{
						type = Type::CENTER;
						return 0;
					}
					if (data == "right")
					{
						type = Type::RIGHT;
						return 0;
					}
					return -1;
				}
			};

			Size size = {};
			Align align = {};

			int setDataChild(std::string name, std::string data) override
			{
				size.setData(name, data);
				align.setData(name, data);
				return 1;
			}

			int setDatafunction(std::string data) override
			{
				return 0;
			}

			int apply(Text s)
			{
				size.IntegerData |= *s.size.IntegerData;
				return 0;
			}
		};

		struct Background : public InChildVtrualProperty
		{
			static constexpr const char* named = "background";
			std::string getNamed() override
			{
				return named;
			}

			Property<Color> color;

			int setDataChild(std::string name, std::string data) override
			{
				(*color).setData(name, data);
				return 1;
			}

			int setDatafunction(std::string data) override
			{
				return 0;
			}

			int apply(Background s)
			{
				color |= *s.color;
				return 0;
			}
		};

		struct Border : public InChildVtrualProperty
		{
			static constexpr const char* named = "border";
			std::string getNamed() override
			{
				return named;
			}

			struct Width : IntegerProperty
			{
				std::string getNamed() override
				{
					return "width";
				}
			};

			struct Style : VtrualProperty
			{
				std::string getNamed() override
				{
					return "style";
				}

				enum class Type
				{
					NONE,
					SOLID,
					DOUBLE,
				};

				Property<Type> type;

				int setDatafunction(std::string data) override
				{
					if (data == "none")
					{
						type = Type::NONE;
						return 0;
					}
					if (data == "solid")
					{
						type = Type::SOLID;
						return 0;
					}
					if (data == "double")
					{
						type = Type::DOUBLE;
						return 0;
					}
					return -1;
				}
			};

			Width width;
			Style style;
			Property<Color> color;

			int setDataChild(std::string name, std::string data) override
			{
				( width).setData(name, data);
				( style).setData(name, data);
				(*color).setData(name, data);
				return 1;
			}

			int setDatafunction(std::string data) override
			{
				return 0;
			}

			int apply(Border s)
			{
				width.IntegerData |= *s.width.IntegerData;
				style.type |= *style.type;
				color |= *s.color;
				return 0;
			}
		};

		struct Margin : public IntegerProperty
		{
			static constexpr const char* named = "margin";
			std::string getNamed() override
			{
				return named;
			}
		};

		struct Padding : public IntegerProperty
		{
			static constexpr const char* named = "padding";
			std::string getNamed() override
			{
				return named;
			}

		};

		struct Width : public lengthPropety
		{
			static constexpr const char* named = "width";
			std::string getNamed() override
			{
				return named;
			}

		};

		struct Height : public lengthPropety
		{
			static constexpr const char* named = "height";
			std::string getNamed() override
			{
				return named;
			}

		};

#undef named

	};

	/*
	* style를 담당하는 클래스, 너무 무겁고 버그도 존재함
	* apply에서 버그가 발견 되었으나 시간이 없어서 해결하지 않았음
	*/
	class Style : public VirtualStyle
	{

	public:

		Property<Color> color = {};
		Font font = {};
		Text text = {};
		Background background = {};
		Border border = {};
		Margin margin = {};
		Padding padding = {};
		Width width = {};
		Height height = {};

		Style()
		{

		}

		Style(std::string string)
		{
			std::vector<std::string> vector;
			Parser parser;
			parser.split(vector, string, ';');
			for (std::string string : vector)
			{
				parser.squish(string);
				setting(string);
			}
		}

		int setting(std::string string)
		{
			(*color).setData(string);
			(font).setData(string);
			(text).setData(string);
			(background).setData(string);
			(border).setData(string);
			(margin).setData(string);
			(padding).setData(string);
			(width).setData(string);
			(height).setData(string);
			return 0;
		}

		int apply(Style b)
		{
			auto& a = *this;
			a.color |= *b.color;
			a.font.apply(b.font);
			a.text.apply(b.text);
			a.background.apply(b.background);
			a.border.apply(b.border);
			a.margin.IntegerData |= *b.margin.IntegerData;
			a.padding.IntegerData |= *b.padding.IntegerData;
			a.width.IntegerData |= *b.width.IntegerData;
			a.height.IntegerData |= *b.height.IntegerData;
			return 0;
		}

	};

	/*
	* 태그 처리 담당 클래스
	*/
	class Tag
	{
	protected:

		struct Att
		{
			std::string name;
			std::string data;

			std::string toString()
			{
				return name + '=' + '"' + data + '"';
			}

		};

	public:

		std::string tag;
		std::vector<Att> att;

		Tag(std::string string)
		{
			int flag = 0;
			int Stringflag = 0;

			std::string name;
			std::string data;

			for (char get : string)
			{

				if (get == '<') continue;
				if (get == '>') break;

				switch (flag)
				{
				case 0:
					if (get == ' ' || get == '\t' || get == '\n')
					{

					}
					else
					{
						tag.push_back(get);
						flag = 1;
					}
					break;
				case 1:
					if (get == ' ' || get == '\t' || get == '\n')
					{
						flag = 2;
					}
					else
					{
						tag.push_back(get);
					}
					break;
				case 2:
					if (get == ' ' || get == '\t' || get == '\n')
					{

					}
					else
					{
						flag = 3;
						name.push_back(get);
					}
					break;
				case 3:
					if (get == ' ' || get == '\t' || get == '\n')
					{
						flag = 4;
					}
					else if (get == '=')
					{
						flag = 5;
					}
					else
					{
						name.push_back(get);
					}
					break;
				case 4:
					if (get == ' ' || get == '\t' || get == '\n')
					{

					}
					else if (get == '=')
					{
						flag = 5;
					}
					else
					{
						att.push_back({ name, {} });
						name.clear();
						flag = 3;
						name.push_back(get);
					}
					break;
				case 5:
					if (get == ' ' || get == '\t' || get == '\n')
					{

					}
					else if (get == '"')
					{
						flag = 6;
					}
					break;
				case 6:
					if (get == '"')
					{
						att.push_back({ name, data });
						name.clear();
						data.clear();
						flag = 2;
					}
					else
					{
						data.push_back(get);
					}
					break;
				}
			}


		}

		virtual std::string toString()
		{
			std::string output = tag;
			for (Att get : att)
			{
				output += ' ' + get.toString();
			}
			return output;
		}

	};

	/*class TagStyle : public Tag
	{

		class ElementTag
		{
			std::string name;
			Property<Style> style;
		public:
			std::string getNamed()
			{
				return name;
			}
			Style getStyle()
			{
				return *style;
			}
			ElementTag()
			{
				name = {};
			}
			ElementTag(std::string name, std::string data) : name(name)
			{
				*style = Style(data);

			}
			ElementTag(ElementTag&& get) noexcept : name(get.name), style(get.style)
			{
				
			}
			ElementTag(ElementTag& get) : name(get.name), style(get.style)
			{

			}
			ElementTag(ElementTag* get) : name(get->name), style(get->style)
			{

			}
			ElementTag& operator=(ElementTag get)
			{
				name = get.getNamed();
				*style = *style;
				return *this;
			}

		};

		struct StyleElement
		{
			Property<ElementTag> p, h1, h2, h3, h4, h5, h6, br, div;

			StyleElement()
			{
				*p = ElementTag("p", "font-size: 25");
				p = ElementTag("p", "font-size: 20");
				h1 = ElementTag("h1", "font-size: 30");
				h2 = ElementTag("h1", "font-size: 25");
				h3 = ElementTag("h1", "font-size: 21");
				h4 = ElementTag("h1", "font-size: 18");
				h5 = ElementTag("h1", "font-size: 16");
				h6 = ElementTag("h1", "font-size: 15");
			}

		} styleElement;

	public:

		TagStyle(std::string string) : Tag(string), styleElement()
		{
			
		}

		int tagSetting(std::string tagName, Style& getStyle)
		{
			for (int i = 0; i < 7; i++)
			{
				Property<ElementTag>* pointer = &styleElement.p;
				switch (i)
				{
				case 0:
					pointer = &styleElement.p;
					break;
				case 1:
					pointer = &styleElement.h1;
					break;
				case 2:
					pointer = &styleElement.h2;
					break;
				case 3:
					pointer = &styleElement.h3;
					break;
				case 4:
					pointer = &styleElement.h4;
					break;
				case 5:
					pointer = &styleElement.h5;
					break;
				case 6:
					pointer = &styleElement.h6;
					break;
				}
				if ((**pointer).getNamed() == tagName)
				{
					getStyle = (**pointer).getStyle();
					break;
				}
			}
			return 0;
		}

	};*/

	/*
	* 요소 담당 클래스
	*/
	class Element : public Tag
	{

	public:

		std::vector<Element*> content;

		Property<Style> style = {};

		Element(std::string string) : Tag(string)
		{
			//tagSetting(tag, *style);

			for (Att get : att)
			{
				if (get.name == "style")
				{
					style = get.data;
;					break;
				}
			}
		}

		~Element()
		{
			for (Element* get : content)
			{
				delete get;
			}
		}

		virtual std::string stringContent()
		{
			return "";
		}

		virtual std::string toString() override
		{
			return '<' + Tag::toString() + '>';
		}

	};

	/*
	* 노 태그 요소 담당 클래스
	*/
	class textContent : public Element
	{
		std::string string;

	public:

		textContent(std::string string) : Element("<textContent>"), string(string)
		{
			
		}

		std::string stringContent() override
		{
			return string;
		}

	};

	/*
	* document, 문서를 정의하는 객체
	*/
	class Document
	{

		Element content;
		

	public:

		Style* style = {};

		Document(std::string string) : content("<Document>")
		{

			std::vector<Element*> stack;
			stack.push_back(&content);

			Parser parser;
			std::vector<std::string> vector;
			parser.subString(vector, string, '<', '>');

			for (std::string get : vector)
			{
				//std::cout << "\npoint" << get;
			}

			for (std::string get : vector)
			{
				
				if (get.empty()) continue;

				std::string squishString = get;
				parser.squish(squishString);

				if (squishString.empty()) continue;

				if (squishString.at(0) == '<')
				{
					if(squishString.at(1) == '/')
					{
						stack.pop_back();
						if (stack.empty()) break;
					}
					else
					{
						Element* element = new Element(get);
						stack.back()->content.push_back(element);
						stack.push_back(element);
					}
				}
				else
				{
					if (parser.trim(get) == -1) continue;
					parser.to﻿Squish(get, '\n');
					parser.tapToSpace(get);
					Element* element = new textContent(get);
					stack.back()->content.push_back(element);
				}
			}

		}



		std::string getToString()
		{
			return getToStringFunction(&content);
		}

		Element& getElementContent()
		{
			return content;
		}

	private:

		std::string systemOutPrint(std::string string, size_t depth)
		{
			std::string output;
			for (int i = 0; i < depth; i++)
			{
				output += "    ";
			}
			if (!string.empty())
			{
				output += string;
				output += '\n';
			}
			return output;
		}

		std::string getToStringFunction(Element* element, size_t depth = 0)
		{
			std::string output;
			if ( element->tag == "textContent" )
			{
				output += systemOutPrint(element->stringContent(), depth);
			}
			else
			{
				output +=  systemOutPrint(element->toString(), depth);
				for (Element* get : element->content)
				{
					output += getToStringFunction(get, depth + 1);
				}
				output += systemOutPrint("</" + element->tag + '>', depth);
			}
			return output;
		}

	};

	/*
	* SDL들의 기능을 모은 클래스
	* 콜백함수까지 진도가 안 갔기에 부족한점이 있음
	* 버그가 있을거임
	*/
	class CSDL
	{
		SDL_Window* window = {};
		SDL_Renderer* renderer = {};
		TTF_Font* font = {};
		size_t fontSize = 18;

		//Style style = {};
		SDL_Color color = {};
		SDL_Point cursor = {};
		Document* document = {};
		
	public:

		CSDL(std::string name, int w, int h, size_t fontSize)
		{
			SDL_Init(SDL_INIT_VIDEO);
			TTF_Init();

			this->fontSize = fontSize;
			font = TTF_OpenFont(".\\lib\\NotoSansKR-VariableFont_wght.ttf", fontSize);
			if (!font) std::cout << "이런";

			window = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_TARGETTEXTURE);

			color = { 0, 0, 0, 255 };
			//style = Style("color: black; border-color: black;");
		}

		~CSDL()
		{
			if (renderer) SDL_DestroyRenderer(renderer);
			if (window) SDL_DestroyWindow(window);
			if (font) TTF_CloseFont(font);

		}

		/*
		* 이벤트 처리 루프, 근데 안 쓰이는
		*/
		int EventLoop()
		{
			SDL_Event event = {};
			while (SDL_PollEvent(&event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
					return 0;
					break;
				}
			}
			return 1;
		}

		/*
		* 그리는 루프
		*/
		int DrawLoop()
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			SDL_RenderClear(renderer);
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			cursor = {};
			{
				//if(document) SimpleDrawElement(&document->getElementContent());
				if (document)
				{
					Element* element = &document->getElementContent();
					ElementSetting(element);
					DrawElement(element);
				}
			}
			SDL_RenderPresent(renderer);
			return 0;
		}

		/*
		* 스트링 그리는 기능
		*/
		int DrawString(std::string string)
		{

			SDL_Surface* surface = TTF_RenderUTF8_Blended(font, string.c_str(), color);
			if (!surface) return -1;

			SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
			SDL_FreeSurface(surface);

			if(!texture) return -1;

			SDL_Rect rect = {};
			SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
			rect.x = cursor.x;
			rect.y = cursor.y;

			SDL_RenderCopy(renderer, texture, NULL, &rect);

			//cursor.y += rect.h;
			SDL_DestroyTexture(texture);
			return 0;
		}

		/*
		* document 저장하는 기능
		*/
		int setDocument(Document& document)
		{
			this->document = &document;
			return 0;
		}

		/*
		* main 2에 쓰기 위한 임시 함수
		*/
		SDL_Window* getWindow() const
		{
			return window;
		}

	private:

		/*
		* 임시로 만든 클래스
		*/
		template<typename T>
		class saveProperty
		{
			T* p = nullptr;
			T d = {};
			bool e = false;

		public:

			saveProperty<T>& operator=(T& get)
			{
				p = &get;
				d = get;
				e = true;
				return *this;
			}

			saveProperty<T>& operator=(T&& get)
			{
				if(p != nullptr) *p = get;
				return *this;
			}

			saveProperty<T>& operator&=(T&& get)
			{
				if (p != nullptr) *p = get;
				return *this;
			}

			~saveProperty()
			{
				if (e && p) *p = d;
			}
		};

		/*
		* 재귀함수 형태의 element의 width와 height값 설정 함수
		*/
		int ElementSettingFunction(Element* element, int& w, int& h)
		{
			Sumer sumer;
			int width = 0;
			int height = 0;
			for (Element* get : element->content)
			{
				int getWidth = 0;
				int getHeight = 0;
				if (get->tag == "textContent")
				{
					bool fontSizeEvent = (element->style.isExist() && element->style->font.size.IntegerData.isExist());
					if (fontSizeEvent) TTF_SetFontSize(font, *element->style->font.size);
					TTF_SizeUTF8(font, get->stringContent().c_str(), &getWidth, &getHeight);
					if (fontSizeEvent) TTF_SetFontSize(font, fontSize);
				}
				else
				{
					ElementSettingFunction(get, getWidth, getHeight);	
				}
				if (get->style.isExist())
				{
					if (get->style->margin.IntegerData.isExist())
					{
						getWidth += *get->style->margin.IntegerData * 1;
						getHeight += *get->style->margin.IntegerData * 1;
					}
				}
				width = sumer.max(width, getWidth);
				height += getHeight;
			}

			if (element->style.isExist() && element->style->padding.IntegerData.isExist())
			{
				width += (*element->style->padding.IntegerData * 2);
				height += (*element->style->padding.IntegerData * 2);
			}

			if(element->tag != "Document")
			{
				*element->style->width |= width;
				*element->style->height |= height;
			}
			w = *element->style->width;
			h = *element->style->height;
			return 0;
		}

		/*
		* elementSettingFunction을 감싼 함수
		*/
		int ElementSetting(Element* element)
		{
			int w = 0, h = 0;
			ElementSettingFunction(element, w, h);
			return 0;
		}

		/*
		* element들을 그리는 함수, style를 반영함
		*/
		int DrawElement(Element* element)
		{
			bool marginEvent = (element->style.isExist() && element->style->margin.IntegerData.isExist());
			bool paddingEvent = (element->style.isExist() && element->style->padding.IntegerData.isExist());
			if (marginEvent) cursor.x += *element->style->margin, cursor.y += *element->style->margin / 2;
			ElementStyleDraw(element, {});
			if (paddingEvent) cursor.x += *element->style->padding, cursor.y += *element->style->padding;
			for (Element* get : element->content)
			{
				if (get->tag == "textContent")
				{
					if (element->style.isExist()) StringStyleDraw(get, *element->style);
					//else DrawString(get->stringContent());
				}
				else
				{
					saveProperty<int> saveWidth;
					saveProperty<int> saveHeight;
					int a = *get->style->width.IntegerData;
					if (get->style.isExist()) // 여전히 auto size 버그가 있음
					{
						int play = 0;
						if (element->style->padding.IntegerData.isExist()) play += *element->style->padding * 2;
						if (get->style->margin.IntegerData.isExist()) play += *get->style->margin * 2;
						if (get->style->width._auto_) saveWidth = *get->style->width = int(*element->style->width - play);
						if (get->style->height._auto_) saveHeight = *get->style->height = int(*element->style->height - play);
					}
					/*if ((get->style.isExist()) && get->style->width._auto_)
					{
						auto& w = get->style->width.IntegerData;
						w = *element->style->width;
						if(element->style->padding.IntegerData.isExist()) *w -= *element->style->padding * 2;
						if (get->style->margin.IntegerData.isExist()) *w -= *get->style->margin * 2;
						if(false){
							std::cout << element->tag << "\n";
							std::cout << *element->style->width << "\n";
						}
					}*/
					DrawElement(get);
					if ((get->style.isExist()) && get->style->width._auto_)
					{
						get->style->width.IntegerData = a;
					}
				}
			}
			if (element->style->height.IntegerData.isExist())
			{
				cursor.y += *element->style->height;
				if (paddingEvent) cursor.y -= *element->style->padding * 2;
			}
			if (paddingEvent) cursor.x -= *element->style->padding, cursor.y += *element->style->padding;
			if (marginEvent) cursor.x -= *element->style->margin, cursor.y += *element->style->margin / 2;
			return 0;
		}

		/*
		* 과거의 테스트용 element 그리는 함수, string만 반영함
		*/
		int SimpleDrawElement(Element* element)
		{
			if (element->tag == "textContent")
			{
				DrawString(element->stringContent());
			}
			else
			{
				for (Element* get : element->content)
				{
					SimpleDrawElement(get);
				}
			}
			return 0;
		}

		/*
		* element를 직접 그리는 함수
		*/
		int ElementStyleDraw(Element* element, Style base = {})
		{
			if (!element->style.isExist()) return -2;
			Style elementStyle = *element->style;
			//elementStyle.apply(base);
			Style& s = elementStyle;
			SDL_Rect rect = { .x = cursor.x, .y = cursor.y, .w = (int)*s.width, .h = (int)*s.height };
			if (s.color.isExist())
			{

			}
			if (s.background.color.isExist())
			{
				SetColor(s.background.color->toSDL());
				SDL_RenderFillRect(renderer, &rect);
			}
			if (*s.border.style.type != VirtualStyle::Border::Style::Type::NONE)
			{
				SetColor(s.border.color->toSDL());
				switch (*s.border.style.type)
				{
				case VirtualStyle::Border::Style::Type::SOLID:
					SDL_RenderDrawRect(renderer, &rect);
					break;
				case VirtualStyle::Border::Style::Type::DOUBLE:
				{
					SDL_Rect minRect = { .x = rect.x + 1, .y = rect.y + 1, .w = rect.w - 2, .h = rect.h - 2 };
					SDL_Rect maxRect = { .x = rect.x - 1, .y = rect.y - 1, .w = rect.w + 2, .h = rect.h + 2 };
					SDL_RenderDrawRect(renderer, &minRect);
					SDL_RenderDrawRect(renderer, &maxRect);
				}
					break;
				}
				return 0;
			}
			return 0;
		}

		/*
		* style를 지원하며 스트링을 그리는 함수
		* 기존의 string을 그리는 함수의 형태를 변경하고 싶지는 않았음
		*/
		int StringStyleDraw(Element* element, Style base) // 함수의 상속은 지원하지 않는건가
		{
			if (element->tag != "textContent") return 1;
			bool fontSizeEvent = base.font.size.IntegerData.isExist();
			bool fontColorEvent = base.color.isExist();
			bool textAlignEvent = base.text.align.type.isExist();
			{
				saveProperty<SDL_Color> saveColor;

				if (fontSizeEvent) TTF_SetFontSize(font, *base.font.size);
				if (fontColorEvent) saveColor = color = base.color->toSDL();
				if (textAlignEvent) SetCurserDrawResetString(element->stringContent(), SetCursorAlign(element->stringContent(), base));
				else DrawString(element->stringContent());
				if (fontSizeEvent) TTF_SetFontSize(font, fontSize);
			}
			return 0;
		}

		/*
		* 임시로 만든 색 지정 함수
		*/
		int SetColor(SDL_Color color)
		{
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			return 0;
		}

		/*
		* 텍스트가 좌 중 우에 있는지 확인하고 커서를 움직이는 함수
		*/
		SDL_Point SetCursorAlign(std::string string, Style& base)
		{
			int tw, th, ew, eh;
			ew = *base.width;
			eh = *base.height;
			TTF_SizeUTF8(font, string.c_str(), &tw, &th);
			using type = Style::Text::Align::Type;
			switch (*base.text.align.type)
			{
			case type::LEFT:
				return cursor;
				break;
			case type::CENTER:
				return SDL_Point{ .x = cursor.x + (ew - tw) / 2 - (int)*base.padding * 2, .y = cursor.y };
				break;
			case type::RIGHT:
				return SDL_Point{ .x = cursor.x + ew - tw - (int)*base.padding * 2, .y = cursor.y };
				break;
			}
			return cursor;
		}

		/*
		* drawString의 커서 값의 변경을 무효화하거나 그 값을 반영하거나 하는 함수
		* StringStyleDraw에서 떨어져 나갔음
		*/
		int SetCurserDrawResetString(std::string string, SDL_Point point)
		{
			SDL_Point saveCursor = cursor;
			cursor = point;
			DrawString(string);
			SDL_Point play = { cursor.x - point.x, cursor.y - point.y};
			cursor = saveCursor;
			/*cursor.x += play.x;
			cursor.y += play.y;*/
			return 0;
		}

	};

	/*
	* 테스트용 클래스
	*/
	class Tester
	{
		class stream
		{
			std::stringstream sstream;
		public:

			template<class T>
			stream& operator<<(T get)
			{
				sstream << get << '\n';
				return *this;
			}

			template<class T>
			stream& operator+(T get)
			{
				sstream << get;
				return *this;
			}

			template<class T>
			stream& operator-(T get)
			{
				sstream << get << '\n';
				return *this;
			}

			stream& clear()
			{
				sstream.clear();
				return *this;
			}

			stream& print()
			{
				std::cout << sstream.str();
				return *this;
			}

			std::string str()
			{
				return sstream.str();
			}

			
		} cs;

	protected:
		int testColor()
		{
			std::stringstream sstream;
			VirtualStyle::Color color;
			sstream << color.setData("color: #FF00FFFF") << "\n";
			sstream << (int)color.r << "\n";
			sstream << (int)color.g << "\n";
			sstream << (int)color.b << "\n";
			sstream << (int)color.a << "\n";
			messag += sstream.str();
			return 0;
		}
		int testProperty()
		{
			using prop = Property<int>;
			prop p;

			cs << *p;
			p = 13;
			cs << *p;
			p = 24;
			cs << *p;

			messag += cs.str();
			return 0;
		}
		int testFont()
		{
			VirtualStyle::Font font;
			font.setData("font-size: 236");
			cs << *font.size.IntegerData;
			cs.print();
			return 0;
		}
		int testPropertyColor()
		{
			Property<VirtualStyle::Color> color;
			color->setData("color: #FF00FF");
			cs << (int)color->r;
			cs << (int)color->g;
			cs << (int)color->b;
			cs << (int)color->a;
			cs.print();
			return 0;
		}
		int testBackground()
		{
			VirtualStyle::Background s;
			s.setData("background-color: #FF00FF00");
			auto& color = s.color;
			cs << (int)color->r;
			cs << (int)color->g;
			cs << (int)color->b;
			cs << (int)color->a;
			cs.print();
			return 0;
		}
		int testBorder()
		{
			VirtualStyle::Border b;
			b.setData("border-color: #FF00FF");
			b.setData("border-width: 20");
			b.setData("border-style: solid");
			auto& color = b.color;
			cs << 'r' << (int)color->r;
			cs << 'g' << (int)color->g;
			cs << 'b' << (int)color->b;
			cs << 'a' << (int)color->a;
			cs << *b.width;
			cs << (*b.style.type == VirtualStyle::Border::Style::Type::SOLID ? "solid" : "none");
			cs.print();
			return 0;
		}
		int testStyle()
		{
			Property<Style> style;
			style = std::string("color: #0000FF; width: 20; color: red;");
			Property<VirtualStyle::Color> color;
			color = *style->color;
			cs << 'r' << (int)color->r;
			cs << 'g' << (int)color->g;
			cs << 'b' << (int)color->b;
			cs << 'a' << (int)color->a;
			cs << *style->width;
			cs.print();
			return 0;
		}
		int testStyle2()
		{
			Property<Style> style;
			style = std::string("background-color: yellow; width: 20;");

			auto printColor = [ this ]( Property<VirtualStyle::Color>& color, std::string name)
				{
					cs + name + " " + 'r' + ": " - (int)color->r;
					cs + name + " " + 'g' + ": " - (int)color->g;
					cs + name + " " + 'b' + ": " - (int)color->b;
					cs + name + " " + 'a' + ": " - (int)color->a;
				};

			printColor(style->color, "color");
			printColor(style->background.color, "back");
			printColor(style->border.color, "border");

			cs << *style->width;
			cs.print();
			return 0;
		}
	public:
		int error = 0;
		std::string messag;
		Tester()
		{
			error = testStyle2();
			std::cout << messag;
		}
	};

	int documentElementSizeFunction(int& w, int& h, Document& element)
	{
		Element& content = element.getElementContent();
		content.style->width.IntegerData = w;
		content.style->height.IntegerData = h;
		//std::cout << "갱신함:\n" << "w: " << *content.style->width.IntegerData << "\nh:" << *content.style->height.IntegerData << "\n";
		return 0;
	}

public:

	/*
	* 테스트용 함수
	*/
	int main1(int argc, char** argv)
	{
		//Tester t;

		std::string string;
		if (1 < argc)
		{
			std::ifstream istream(argv[1]);
			std::stringstream sstream;
			sstream << istream.rdbuf();
			string = sstream.str();
			//std::cout << string;
			if (string.size() >= 3 &&
				(unsigned char)string[0] == 0xEF &&
				(unsigned char)string[1] == 0xBB &&
				(unsigned char)string[2] == 0xBF) {
				string.erase(0, 3);
			}
		}

		Document document(string);
		std::cout << document.getToString();
		CSDL SDL("윈도우 입니다", 600, 400, 20);
		SDL.setDocument(document);
		while ( SDL.EventLoop() )
		{
			SDL.DrawLoop();
		}
		return 0;
	}

	/*
	* 테스트용 함수, 갱신 기능 추가
	*/
	int main2(int argc, char** argv)
	{
		//Tester t;

		std::string string;
		auto getInputString = [&argc, &argv, &string]()
			{
				if (1 < argc)
				{
					std::ifstream istream(argv[1]);
					std::stringstream sstream;
					sstream << istream.rdbuf();
					string = sstream.str();
					if (string.size() >= 3 &&
						(unsigned char)string[0] == 0xEF &&
						(unsigned char)string[1] == 0xBB &&
						(unsigned char)string[2] == 0xBF) {
						string.erase(0, 3);
					}
				}
			};
		
		getInputString();
		Document* document = new Document(string);
		int window_w = 600;
		int window_h = 400;
		documentElementSizeFunction(window_w, window_h, *document);
		CSDL SDL("윈도우 입니다", window_w, window_h, 20);
		SDL.setDocument(*document);
		
		SDL_Event event;
		bool quit = true;
		while(quit) while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				quit = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_s)
				{
					getInputString();
					delete document;
					document = new Document(string);
					SDL.setDocument(*document);
					documentElementSizeFunction(window_w, window_h, *document);
				}
				break;
			case SDL_WINDOWEVENT:
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
					SDL_GetWindowSize(SDL.getWindow(), &window_w, &window_h);
					documentElementSizeFunction(window_w, window_h, *document);
					break;
				}
				break;

			}

			SDL.DrawLoop();
		}
		delete document;
		return 0;
	}

	/*
	* 클래스의 메인의 호출점
	*/
	int main(int argc, char** argv)
	{
		return main2(argc, argv);
	}


};

//#include <Windows.h>

/*
* 메인 호출점
*/
int main(int argc, char** argv)
{
	//SetConsoleOutputCP(65001); // 콘솔 한글화를 설정에서 건드는 방법을 모르겠다.
	return Class().main(argc, argv);
}
