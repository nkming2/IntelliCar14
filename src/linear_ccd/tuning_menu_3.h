/*
 * program_tuning_3.h
 *
 * Author: Louis Mo, Ming Tsang, Spartey Chen
 * Copyright (c) 2014 HKUST SmartCar Team
 */

#ifndef LINEAR_CCD_TUNING_MENU_3_H_
#define LINEAR_CCD_TUNING_MENU_3_H_

#include <cstdint>

#include <libutil/tunable_int_manager.h>
#include <libutil/tunable_int_manager.tcc>

namespace linear_ccd
{

class Car;

}

namespace linear_ccd
{

class TuningMenu3
{
public:
	explicit TuningMenu3(Car *const car);

	void Run();

	uint32_t GetCcdThreshold() const
	{
		return m_ccd_threshold->GetValue();
	}

	float GetEdge() const
	{
		return m_edge->GetValue();
	}

	float GetTurnKp() const
	{
		return libutil::TunableInt::AsFloat(m_turn_kp->GetValue());
	}

	float GetTurnKd() const
	{
		return libutil::TunableInt::AsFloat(m_turn_kd->GetValue());
	}

	float GetTurnTurnKp() const
	{
		return libutil::TunableInt::AsFloat(m_turn_turn_kp->GetValue());
	}

	float GetTurnTurnKd() const
	{
		return libutil::TunableInt::AsFloat(m_turn_turn_kd->GetValue());
	}

	int GetSpeedSp() const
	{
		return m_speed_sp->GetValue();
	}

	float GetSpeedKp() const
	{
		return libutil::TunableInt::AsFloat(m_speed_kp->GetValue());
	}

	float GetSpeedKi() const
	{
		return libutil::TunableInt::AsFloat(m_speed_ki->GetValue());
	}

	float GetSpeedKd() const
	{
		return libutil::TunableInt::AsFloat(m_speed_kd->GetValue());
	}

	int GetSpeedTurnSp() const
	{
		return m_speed_turn_sp->GetValue();
	}

private:
	enum Page
	{
		TURN,
		SPEED,

		SIZE,
	};

	static constexpr int TUNABLE_INT_COUNT = 11;

	void Select(const int id);
	void SwitchPage(const int id);

	int GetMultiplier() const;

	void AdjustValueTurn(const bool is_positive);
	void AdjustValueSpeed(const bool is_positive);

	void Redraw(const bool is_clear_screen);

	Car *m_car;

	Page m_page;
	int m_select;

	const libutil::TunableInt *m_ccd_threshold;
	const libutil::TunableInt *m_edge;
	const libutil::TunableInt *m_turn_kp;
	const libutil::TunableInt *m_turn_kd;
	const libutil::TunableInt *m_turn_turn_kp;
	const libutil::TunableInt *m_turn_turn_kd;

	const libutil::TunableInt *m_speed_sp;
	const libutil::TunableInt *m_speed_kp;
	const libutil::TunableInt *m_speed_ki;
	const libutil::TunableInt *m_speed_kd;
	const libutil::TunableInt *m_speed_turn_sp;
};

}

#endif /* LINEAR_CCD_TUNING_MENU_3_H_ */