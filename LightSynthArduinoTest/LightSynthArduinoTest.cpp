// LightSynthArduinoTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include "gtest/gtest.h"
#include "..\LightSynthArduino\TimerCalculator.h"


TEST(testTimerCalculator, MyFirstTest)
{
	TimerCalculator timerCalculator;
	timerCalculator.calculate(65537);
	unsigned long result = timerCalculator.t1_comparator;
	EXPECT_EQ(result, 10);
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*The method is initializes the Google framework and must be called before RUN_ALL_TESTS */
	::testing::InitGoogleTest(&argc, argv);

	/*RUN_ALL_TESTS automatically detects and runs all the tests defined using the TEST macro.
	It's must be called only once in the code because multiple calls lead to conflicts and,
	therefore, are not supported.
	*/
	return RUN_ALL_TESTS();
}

