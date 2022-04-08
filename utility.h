#pragma once

#include "pch.h"

// Paint functions
void setupPainter(QPainter& painter, QWidget* object);
void drawGrid(QPainter& painter, QPointF startPoint, int rowCount, int colCount, double radius);
void drawHexagon(QPainter& painter, QPointF startPoint, double radius, bool erase = false);

// Transfom functions
uint32_t posToHexId(double x, double y, double radius);
QPointF idToPoint(uint32_t id, QPointF startPoint, double radius);
