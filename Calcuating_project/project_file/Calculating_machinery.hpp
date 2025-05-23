#pragma once

#include "Main_draw.hpp"

namespace ns_cm
{
	class Calculating_machinery
	{
		ns_md::Main_draw* md;
		double a = 0;
		double b = 0;
		
		enum class Flag
		{
			None = 0,
			Addition = 1,
			Subtraction = 2,
			Multiplication = 4,
			Division = 8,
		};

		bool dotEvent;
		double dotPoint;
		Flag flag;

		bool int_check(double x) 
		{
			return x - (int)x < 0.000001;
		};

	public:

		Calculating_machinery();

		int Init();

		int run();

		~Calculating_machinery();

	};

}