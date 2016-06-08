#pragma once
class TimerCalculator {
public:
	TimerCalculator(void);
	void calculate(unsigned long duration);
	unsigned long t2_prescaler_pointer;
	unsigned long t2_comparator;
	unsigned long t1_comparator;

protected:
	unsigned long clock_period;
	unsigned long _duration;
	unsigned long t2_prescaler_array[7];
	unsigned long calc_period(unsigned long t1_comparator_value);
	unsigned long calc_t2_period(void);
};
