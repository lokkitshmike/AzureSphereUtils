/// \file azs_pwmrgbled.c
/// \brief This file contains functionality that extends the Azure Sphere PWM library for controlling an RGB led
#include "azs_pwmrgbled.h"

int  MinMaxValue(int Value, int MinValue, int MaxValue) {

	if (Value < MinValue) {
		Value = MinValue;
	}

	if (Value > MaxValue) {
		Value = MaxValue;
	}

	return Value;
}

int LEDSetRGBColor(int* pPWMControllerFileDescriptor, RGBLED_Color* pRGBLEDColor) {

	int PWM_Period = NS_PER_SEC / DEFAULT_LED_PWM_FREQUENCY;

	int redDuty = (PWM_Period / 255) * MinMaxValue(pRGBLEDColor->redValue, 0, 255);
	int greenDuty = (PWM_Period / 255) * MinMaxValue(pRGBLEDColor->greenValue, 0, 255);
	int blueDuty = (PWM_Period / 255) * MinMaxValue(pRGBLEDColor->blueValue, 0, 255);

	PwmState RledPwmState = { .period_nsec = PWM_Period,
						   .polarity = PWM_Polarity_Normal,
						   .dutyCycle_nsec = redDuty,
						   .enabled = true };
	PwmState GledPwmState = { .period_nsec = PWM_Period,
						   .polarity = PWM_Polarity_Normal,
						   .dutyCycle_nsec = greenDuty,
						   .enabled = true };
	PwmState BledPwmState = { .period_nsec = PWM_Period,
						   .polarity = PWM_Polarity_Normal,
						   .dutyCycle_nsec = blueDuty,
						   .enabled = true };

	if (PWM_Apply(*pPWMControllerFileDescriptor, (PWM_ChannelId)DEFAULT_LED_R_CHANNEL, &RledPwmState) ||
		PWM_Apply(*pPWMControllerFileDescriptor, (PWM_ChannelId)DEFAULT_LED_G_CHANNEL, &GledPwmState) ||
		PWM_Apply(*pPWMControllerFileDescriptor, (PWM_ChannelId)DEFAULT_LED_B_CHANNEL, &BledPwmState) == -1) {
		return 0;
	}

	return 1;
}

int LEDSetRGBChannelValue(int* pPWMControllerFileDescriptor, PWM_ChannelId PWMChannel, int ChannelValue) {

	int PWM_Period = NS_PER_SEC / DEFAULT_LED_PWM_FREQUENCY;

	int colorDuty = (PWM_Period / 255) * MinMaxValue(ChannelValue, 0, 255);
	PwmState ledPwmState = { .period_nsec = PWM_Period,
						   .polarity = PWM_Polarity_Normal,
						   .dutyCycle_nsec = colorDuty,
						   .enabled = true };

	if (PWM_Apply(*pPWMControllerFileDescriptor, PWMChannel, &ledPwmState) == -1) {
		return 0;
	}

	return 1;
}


