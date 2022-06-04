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
	json j;
	try {
		j = json::parse(a.begin(), a.end());
	} catch(const json::exception& e) { // Only catch json exceptions, ignore(rethrow) other exceptions
		qCritical(e.what());
		return false;
	}
	qDebug(j.dump(4).data());
	return true;
}
