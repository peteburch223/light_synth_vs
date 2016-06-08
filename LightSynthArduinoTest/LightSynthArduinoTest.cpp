// LightSynthArduinoTest.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include <conio.h>
#include "gtest/gtest.h"
#include "..\LightSynthArduino\TimerCalculator.h"
#include "..\LightSynthArduino\Debounce.h"
#include "..\LightSynthArduino\SequenceState.h"
#include "..\LightSynthArduino\States.h"

#ifndef LOW
	#define LOW 0
#endif 

#ifndef HIGH
	#define HIGH 1
#endif 

TEST(testTimerCalculator, MyFirstTest)
{
	TimerCalculator timerCalculator;
	timerCalculator.calculate(65537);
	unsigned long result = timerCalculator.t1_comparator;
	EXPECT_EQ(result, 32768);
}


TEST(testDebounce, DebounceCompleted)
{
	Debounce debouncer(0);
	unsigned char reading = 1;

	for (int i = 0; i < 11; i++)
	{
		debouncer.debounced_state(reading);
	}

	EXPECT_EQ(debouncer.current_state, reading);
}

TEST(testDebounce, DebounceNotCompleted)
{
	Debounce debouncer(0);
	unsigned char reading;

	for (int i = 0; i < 11; i++)
	{
		if (i < 5)
			reading = 1;
		else
			reading = 0;

		debouncer.debounced_state(reading);
	}
	EXPECT_EQ(debouncer.current_state, 0);
}

TEST(testDebounce, BouncingSwitch)
{
	Debounce debouncer(0);
	unsigned char reading;

	for (int i = 0; i < 11; i++)
	{
		if (i < 2)
			reading = 1;
		else if (i >= 2 && i < 5)
			reading = 0;
		else if (i >= 5 && i < 8)
			reading = 1;
		else
			reading = 0;

		debouncer.debounced_state(reading);
	}
	EXPECT_EQ(debouncer.current_state, 0);
}

TEST(TestState, testAwaitCommand)
{
	SequenceState sequence;
	EXPECT_EQ(sequence.state, AWAIT_COMMAND);
	EXPECT_EQ(sequence.buttonState, HIGH);
}

TEST(TestState, testStartWait)
{
	SequenceState sequence;
	sequence.buttonState = LOW;
	sequence.advance();
	EXPECT_EQ(sequence.state, WAIT);
	EXPECT_EQ(sequence.buttonState, LOW);
	EXPECT_EQ(sequence.isStartTimer(), true);
	EXPECT_EQ(sequence.isStartTimer(), false);

}

TEST(TestState, testDisplayColour)
{
	SequenceState sequence;
	sequence.buttonState = LOW;
	sequence.advance();
	sequence.isStartTimer();
	sequence.advance();
	EXPECT_EQ(sequence.state, WAIT);
	for (int i = 0; i < 11; i++)
		sequence.advance();
	sequence.timerComplete = true;
	sequence.advance();
	EXPECT_EQ(sequence.isStartTimer(), true);
	EXPECT_EQ(sequence.isStartTimer(), false);
	EXPECT_EQ(sequence.state, DISPLAY_COLOUR);
	EXPECT_EQ(sequence.colour, RED);


}

TEST(TestState, testWholeSequence)
{
	SequenceState sequence;

	for (int i = 0; i < 11; i++)
		sequence.advance();

	EXPECT_EQ(sequence.state, AWAIT_COMMAND);

	sequence.buttonState = LOW;
	for (int i = 0; i < 11; i++)
		sequence.advance();

	EXPECT_EQ(sequence.state, WAIT);

	sequence.isStartTimer();
	for (int i = 0; i < 11; i++)
		sequence.advance();
	EXPECT_EQ(sequence.state, WAIT);

	sequence.timerComplete = true;
	sequence.advance();

	EXPECT_EQ(sequence.state, DISPLAY_COLOUR);
	EXPECT_EQ(sequence.colour, RED);

	sequence.isStartTimer();
	for (int i = 0; i < 11; i++)
		sequence.advance();
	sequence.timerComplete = true;
	sequence.advance();

	EXPECT_EQ(sequence.state, WAIT);
	sequence.isStartTimer();
	for (int i = 0; i < 11; i++)
		sequence.advance();
	EXPECT_EQ(sequence.state, WAIT);

	sequence.timerComplete = true;
	sequence.advance();

	EXPECT_EQ(sequence.state, DISPLAY_COLOUR);
	EXPECT_EQ(sequence.colour, GREEN);

	sequence.isStartTimer();
	for (int i = 0; i < 11; i++)
		sequence.advance();
	sequence.timerComplete = true;
	sequence.advance();

	EXPECT_EQ(sequence.state, WAIT);
	sequence.isStartTimer();
	for (int i = 0; i < 11; i++)
		sequence.advance();
	EXPECT_EQ(sequence.state, WAIT);

	sequence.timerComplete = true;
	sequence.advance();

	EXPECT_EQ(sequence.state, DISPLAY_COLOUR);
	EXPECT_EQ(sequence.colour, BLUE);

	sequence.isStartTimer();
	for (int i = 0; i < 11; i++)
		sequence.advance();
	sequence.timerComplete = true;
	sequence.advance();

	EXPECT_EQ(sequence.state, AWAIT_COMMAND);
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

