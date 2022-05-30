#pragma once

#ifndef _SIMBATTLE_UTILITY_H_
#define _SIMBATTLE_UTILITY_H_ 1

#include "pch.h"

// Paint functions
void setupPainter(QPainter& painter, QPaintDevice* object);
void drawGrid(QPainter& painter, QPointF startPoint, int colCount, int rowCount, double radius);
void drawHexagon(QPainter& painter, QPointF startPoint, double radius, bool erase = false);

// Transfom functions
uint32_t posToHexId(double x, double y, double radius);
QPointF idToPoint(uint32_t id, QPointF startPoint, double radius);

#endif // _SIMBATTLE_UTILITY_H_
