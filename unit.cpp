#include "pch.h"
#include "unit.h"

Unit::MapType Unit::dataMap = {};

Unit::Unit(QWidget* parent)
	: QWidget(parent) {
}

Unit::~Unit() {
}

bool Unit::initDataMap() {
	QFile f(Global::dataFileNames[Global::UNIT_FILE]);
	if(!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
		return false;
	}
	QByteArray a = f.readAll();
	if(a.isEmpty()) {
		return false;
	}
	try {
		json j, j_units;
		j		= json::parse(a.begin(), a.end());
		j_units = j.at("units");
		if(!j_units.is_array()) {
			qCritical() << ("Cannot find units data in " + Global::dataFileNames[Global::UNIT_FILE]).toLocal8Bit();
			return false;
		}
		UnitData data {};
		QString	 name;
		json	 x;
		for(auto& unit : j_units) {
			// Not assert `unit` is an object, for it will cause an exception
			x = unit.at("name");
			// Use `get_ref` instead of `get` to avoid copy
			name		   = QString::fromStdString(x.get_ref<std::string&>());
			x			   = unit.at("health");
			data.health	   = x.get<uint16_t>();
			x			   = unit.at("attack");
			data.attack	   = x.get<uint16_t>();
			x			   = unit.at("defense");
			data.defense   = x.get<uint16_t>();
			x			   = unit.at("minDamage");
			data.minDamage = x.get<uint16_t>();
			x			   = unit.at("maxDamage");
			data.maxDamage = x.get<uint16_t>();
			x			   = unit.at("speed");
			data.speed	   = x.get<uint16_t>();
			x			   = unit.at("shots");
			data.shots	   = x.get<uint16_t>();
			dataMap.insert(std::make_pair(name, data));
		}
		qDebug() << j.dump(4).data();
	} catch(const json::exception& e) { // Only catch json exceptions, ignore(rethrow) other exceptions
		qCritical("%s", e.what());
		return false;
	}
	return true;
}
