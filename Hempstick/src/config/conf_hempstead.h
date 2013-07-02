/*
 * conf_hempstead.h
 *
 * Created: 4/30/2013 8:06:54 AM
 *  Author: Jonah Tsai
 */ 


#ifndef CONF_HEMPSTEAD_H_
#define CONF_HEMPSTEAD_H_

#define	CONF_BOARD_ARDUINO_DUE						1

// PIN Configuration
#ifdef CONF_BOARD_SAM4S_XPLAIN_PRO
#	define CONF_NUM_PINS									13
#	define LED0_GPIO										PIO_PC23_IDX
#	define CONF_SSC_CLOCK_SOURCE_ID							ID_TC4
#	define CONF_SSC_CLOCK_TC								TC1
#	define CONF_SSC_CLOCK_CHANNEL							1
#elif defined(CONF_BOARD_ARDUINO_DUE)
#	define CONF_NUM_PINS									22
#	define CONF_TOTAL_NUM_BUTTONS							28
// #	define LED0_GPIO										PIO_PC23_IDX
#	define CONF_SSC_CLOCK_SOURCE_ID							ID_TC8
#	define CONF_SSC_CLOCK_TC								TC2
#	define CONF_SSC_CLOCK_CHANNEL							2
#endif


#define CONF_ENABLE_TM_STICK_IN_BUTTON					1

// This is how many bits of ADC sample decimation will be.
// It's basically a low pass filter with overlapping running average.
// Through trial-n-error, I find that increasing this bit to over 5 (2^5 == 32) doesn't gain you much.
// I find that with the CONF_ADC_DECIMATION_BITS == 5 and CONF_ADC_OVERSAMPLE_RESOLUTION_INCREASE_BITS == 2, inside ThrustMaster TARGET's Device Analyzer, the value variation is under about 20 out of 65535, which is about 0.0006 == 0.06% when the pots are not moved.
// That is quite an ok performance.
// Even the Hall Effect sensor MLX96316 under TM Cougar has worse variation (~0.1%) than that! However, that's not an apple to apple comparison. The Cougar + MLX90316 performance was taken with the MLX90316 limiting the measurement angles to +-25 degree and linearly interpolate the values,
//	while the values here are not limited nor linear interpolated, so the angles are 120 degrees. If we scale this nhumber up to the 25 degree linear interpolation, we would get the variation error to about 0.14%, roughly in the range of the Cougar + MLX90316 range.
// BTW, the MLX90316 internally was setup with a FIR filter to tamp down the noises.
#define CONF_ADC_DECIMATION_BITS						5

// This is the ADC oversampling to increase the resolution.
// This and the above decimation together is commonly referred to as interpolation.
// Remember, for n bit resolutions increment, you need 4^n sampling rate.
// You also have to remember, the 12bit ADC in SAM3X8E has 1 million sample rate. But, it is shared by 16 channels.
// So, each channel only has 1e6 / 16 == 625K samples/second.
// So, if you run 1K report rate (1ms per USB full-speed), and set the resolution increase to 4 bits, then you need 256K samples per channel per second. Well, you can only run 3 channels.
// If you set the bit increase to 3, you can barely run 15 channels. With the overhead of ADC startup, you most likely won't get that much out of it.
// So, I suggest you do not set it over 2 bits increment. It's an artificial interpolation anyway. Increasing too much and you don't really get much real resolution out of it.
// Also, remember, whenever you change this number, you also have to change the USB report's Physical Min/Max, Logical Min/Max, and possibly the HID report descriptor size constant, accordingly!
#define CONF_ADC_OVERSAMPLE_RESOLUTION_INCREASE_BITS	2

// ADC 
#define MAX_ADC_CHANNEL									16




#endif /* CONF_HEMPSTEAD_H_ */