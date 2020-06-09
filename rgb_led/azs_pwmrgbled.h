/// \file azs_pwmrgbled.h
/// \brief This header contains functionality that extends the Azure Sphere PWM library for controlling an RGB led

#pragma once
#include <applibs/pwm.h>

#define DEFAULT_LED_PWM_FREQUENCY 50
#define DEFAULT_LED_R_CHANNEL 0 // Default red channel on the PWM controller
#define DEFAULT_LED_G_CHANNEL 1 // Default green channel on the PWM controller
#define DEFAULT_LED_B_CHANNEL 2 // Default blue channel on the PWM controller
#define NS_PER_SEC 1e9 // a second has 1e9 nanoseconds (notation is evaluated a double)

/// <summary>
///     Reflects a RGB color by R, G and B value between 0..255
/// </summary>
typedef struct RGBLED_Color {
	int redValue;
	int greenValue;
	int blueValue;
} RGBLED_Color;

/// <summary>
///     PWM settings that are needed to feed PWM_Apply()
/// </summary>
typedef struct RGBLED_PWMSettings {	
	int redPWMChhannel;	
	int greenPWMChhannel;		
	int FrequencyInHertz;
} RGBLED_PWMSettings;

/// <summary>
///     Sets the given RGB color onto an RGB LED connected to PWM channels  0(R), 1(G) and  2(B) on the referenced PWM Controller.
///		RGB value gt 255 or lt 0 will be set to 255/0 before applying them onto the channels.
/// </summary>
/// <param name="pPWMControllerFileDescriptor">A pointer to a file descriptor that represents an opened PWM controller</param>
/// <param name="pRGBLEDColor">A pointer to a struct that holds the color information</param>
/// <returns>
///		1 (true) for success, 0 (false) if one ore more color channels could not be set to the given value(s)
/// </returns>
int LEDSetRGBColor(int *pPWMControllerFileDescriptor, RGBLED_Color *pRGBLEDColor);

/// <summary>
///     Sets the given value (0..255) onto a given PWM channel on the referenced PWM Controller.
///		RGB value gt 255 or lt 0 will be set to 255/0 before applying them onto the channels.
/// </summary>
/// <param name="pPWMControllerFileDescriptor">A pointer to a file descriptor that represents an opened PWM controller</param>
/// <param name="PWMChannel">The PWM channel to set. Usually 0=R, 1=G, 2=B</param>
/// <param name="Channel"Value>Value between 0 and 255 to set onto the channel</param>
/// <returns>
///		1 (true) for success, 0 (false) if one ore more color channels could not be set to the given value(s)
/// </returns>
int LEDSetRGBChannelValue(int* pPWMControllerFileDescriptor, PWM_ChannelId PWMChannel, int ChannelValue);

/// <summary>
///     Checks a given value against a minimum and maximum value
/// </summary>
/// <param name="Value">The value to check</param>
/// <param name="MinValue">The minimum</param>
/// <param name="MaxValue">The Maxmimum</param>
/// <returns>
///		The minimum value, if the value is below minimum. The maximum value, if the value is above the maximum.
/// </returns>
int MinMaxValue(int Value, int MinValue, int MaxValue);
