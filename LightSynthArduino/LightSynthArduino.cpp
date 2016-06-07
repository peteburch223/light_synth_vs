// light_synth_arduino.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TimerCalculator.h"
#include <iostream>


int main()
{
	TimerCalculator timerCalculator;
	timerCalculator.calculate(123);
	unsigned long result = timerCalculator.t1_comparator;
	std::cerr << result << std::endl;

    return 0;
}

