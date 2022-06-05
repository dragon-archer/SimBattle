#pragma once

#ifndef _SIMBATTLE_UNIT_H_
#define _SIMBATTLE_UNIT_H_

#include "pch.h"

struct UnitData {
		uint16_t health;
		uint16_t attack;
		uint16_t defense;
		uint16_t minDamage;
		uint16_t maxDamage;
		uint16_t speed;
		uint16_t shots;
};

class Unit : public QWidget {
		Q_OBJECT
	public:
		using MapType = std::unordered_map<QString, UnitData>;

		Unit(QWidget* parent = nullptr);
		~Unit();

		static bool initDataMap();

	private:
		UnitData m_data;
		QString	 m_name;

		static MapType dataMap;
};

#endif // _SIMBATTLE_UNIT_H_
