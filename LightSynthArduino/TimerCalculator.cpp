#include "stdafx.h"
#include "TimerCalculator.h"

// ALL DURATION VALUES ARE IN CLOCK CYCLES

// #define CLOCK_PERIOD 125 // ns
#define MAX_T2_COMPARATOR 255

TimerCalculator::TimerCalculator() :
	t2_prescaler_array{ 1, 8, 32, 64, 128, 256, 1024 }
{
}

void TimerCalculator::calculate(unsigned long duration)
{
	_duration = duration;
	t2_prescaler_pointer = 0;
	t2_comparator = 1;
	t1_comparator = 1;
	// clock_period = CLOCK_PERIOD;
	unsigned long max_t1_comparator = 65535;
	unsigned long max_duration = calc_period(max_t1_comparator);

	while (duration > max_duration)
	{
		if (t2_comparator < (t2_prescaler_array[t2_prescaler_pointer + 1] / t2_prescaler_array[t2_prescaler_pointer]))
		{
			t2_comparator += 1;

		}
		else {
			t2_comparator = 1;
			t2_prescaler_pointer += 1;
		}
		max_duration = calc_period(max_t1_comparator);
		if (t2_comparator == MAX_T2_COMPARATOR) break;
	}
	t1_comparator = (int)(duration / calc_t2_period());
}

unsigned long TimerCalculator::calc_period(unsigned long t1_comparator_value)
{
	unsigned long t2_period = calc_t2_period() * t2_comparator;
	return t1_comparator_value * t2_period;
}

unsigned long TimerCalculator::calc_t2_period(void)
{
	unsigned long prescaler = t2_prescaler_array[t2_prescaler_pointer];
	return prescaler * t2_comparator;
}
