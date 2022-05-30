#pragma once

#ifndef _SIMBATTLE_UTILITY_H_
#define _SIMBATTLE_UTILITY_H_ 1

#include "pch.h"

// Classes declartions
class HexPosition;

// Paint functions
void setupPainter(QPainter& painter, QPaintDevice* object);
void drawGrid(QPainter& painter, QPointF startPoint = Global::startPoint,
			  int rowCount = Global::rowCount, int colCount = Global::colCount, double r = Global::blockRadius);
void drawHexagon(QPainter& painter, QPointF startPoint, double r = Global::blockRadius);

// Transfom functions
HexPosition posToHex(double x, double y, double r = Global::blockRadius);

// Classes Definitions
class HexPosition {
	private:
		int16_t _x;
		int16_t _y;
	public:
		HexPosition(int32_t x = 0, int32_t y = 0)
			:_x(x), _y(y) {}

		inline int16_t& x() {
			return _x;
		}
		inline int16_t x() const {
			return _x;
		}
		inline int16_t& y() {
			return _y;
		}
		inline int16_t y() const {
			return _y;
		}

		inline uint32_t toInt() const {
			return uint32_t((int32_t(_x) << 16) | int32_t(_y));
		}
		QPointF toCorner(double r = Global::blockRadius) const {
			double sqrt3r = r * sqrt(3);
			double a = _x * sqrt3r, b = _y * 1.5 * r;
			if(!(_y & 1)) {
				a += 0.5 * sqrt3r;
			}
			return QPointF{a, b};
		}
		QPointF toCenter(double r = Global::blockRadius) const {
			double sqrt3r = r * sqrt(3);
			double a = _x * sqrt3r + 0.5 * sqrt3r, b = _y * 1.5 * r + r;
			if(!(_y & 1)) {
				a += 0.5 * sqrt3r;
			}
			return QPointF{a, b};
		}
		inline bool isValid(int rowCount = Global::rowCount, int colCount = Global::colCount) const {
			return (_x >= 0) && (_y >= 0) && (_x < colCount) && (_y < rowCount);
		}

		inline operator uint32_t() const {
			return toInt();
		}
		inline operator bool() const {
			return isValid();
		}
		inline bool operator==(const HexPosition& p) const {
			return (_x == p._x) && (_y == p._y);
		}
};

#endif // _SIMBATTLE_UTILITY_H_
