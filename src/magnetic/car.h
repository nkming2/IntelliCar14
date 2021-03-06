/*
 * car.h
 * Magnetic car
 *
 * Author:
 * Copyright (c) 2014 HKUST SmartCar Team
 */

#ifndef MAGNETIC_CAR_H_
#define MAGNETIC_CAR_H_

#include <libsc/k60/futaba_s3010.h>
#include <libsc/com/lcd.h>
#include <libsc/com/lcd_console.h>
#include <libsc/k60/led.h>
#include <libsc/k60/motor.h>
#include <libsc/k60/uart_device.h>
#include <libsc/com/encoder.h>

namespace magnetic
{

class Car
{
public:
	Car();

	/**
	 * Start the wheel motor
	 *
	 * @param is_forward Is going forward or not
	 * @param power Power scale in [0, 1000]
	 */
	void StartMotor(const bool is_forward, const uint16_t powerl, const uint16_t powerr)
	{
		SetMotorDirection(is_forward);
		SetMotorPowerLeft(powerl);
		SetMotorPowerRight(powerr);
	}

	void StopMotor()
	{
		SetMotorPowerLeft(0);
		SetMotorPowerRight(0);
	}

	void SetMotorDirection(const bool is_forward);
	void SetMotorLeftDirection(const bool is_forward);
	void SetMotorRightDirection(const bool is_forward);
	void SetMotorPowerLeft(const uint16_t power)
	{
		m_motor[1].SetPower(power / 10);
	}

	void SetMotorPowerRight(const uint16_t power)
	{
		m_motor[0].SetPower(power / 10);
	}

	void UpdateEncoder()
	{
		m_encoder[0].Update();
		m_encoder[1].Update();
	}

	/**
	 * Set the turning percentage, negative input means turning left
	 *
	 * @param percentage Specifying how aggressively should the car turn,
	 * in [-100, 100], where passing 0 basically means going straight
	 */
	void SetTurning(const int16_t percentage);

	/**
	 * Switch on/off the LEDs
	 *
	 * @param obj
	 * @param id The id of the LED, [0, 3]
	 * @param flag
	 */
	void SwitchLed(const uint8_t id, const bool flag)
	{
		m_leds[id].SetEnable(flag);
	}

	void UpdateEncoder(const uint8_t id)
	{
		m_encoder[id].Update();
	}

	void UartSendStr(const char *str)
	{
		m_uart.SendStr(str);
	}

	void UartSendStrLiteral(const char *str)
	{
		m_uart.SendStrLiteral(str);
	}

	void UartSendStr(std::string &&str)
	{
		m_uart.SendStr(std::move(str));
	}

	void UartSendBuffer(const Byte *buf, const size_t len)
	{
		m_uart.SendBuffer(buf, len);
	}

	bool UartPeekChar(char *out_ch)
	{
		return m_uart.PeekChar(out_ch);
	}

	bool IsMotorForward() const;
	bool IsMotorStop() const
	{
		return !m_motor[0].GetPower();
	}

	uint16_t GetMotorPower() const
	{
		return m_motor[0].GetPower();
	}

	int16_t GetEncoderCount(const uint8_t id)
	{
		return m_encoder[id].GetCount();
	}

	int16_t GetTurning() const;


	void LcdDrawGrayscalePixelBuffer(const uint8_t x, const uint8_t y,
			const uint8_t w, const uint8_t h, const uint8_t *pixel)
	{
		m_lcd.DrawGrayscalePixelBuffer(x, y, w, h, pixel);
	}

	void LcdPrintString(const char *str, const uint16_t color)
	{
		m_lcd_console.PrintString(str, color);
	}

	void LcdClear(const uint16_t)
	{
		m_lcd_console.Clear(false);
		// Skip clearing the screen as it's too slow
		//m_lcd.Clear(color);
	}

	void LcdSetRow(const uint8_t row)
	{
		m_lcd_console.SetCursorRow(row);
	}

private:
	libsc::Encoder m_encoder[2];
	libsc::k60::FutabaS3010 m_servo;
	libsc::Lcd m_lcd;
	libsc::LcdConsole m_lcd_console;
	libsc::k60::Led m_leds[4];
	libsc::k60::Motor m_motor[2];
	libsc::k60::UartDevice m_uart;

};

}

#endif /* MAGNETIC_CAR_H_ */
