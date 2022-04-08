#include "pch.h"
#include "utility.h"

void setupPainter(QPainter& painter, QWidget* object) {
	painter.begin(object);
	painter.setWindow(0, object->height(), object->width(), -1 * object->height());
	painter.setRenderHint(QPainter::Antialiasing);
	QPen pen;
	pen.setColor(Qt::red);
	pen.setStyle(Qt::SolidLine);
	pen.setWidth(1);
	painter.setPen(pen);
	QBrush brush;
	brush.setColor(Qt::blue);
	brush.setStyle(Qt::SolidPattern);
	painter.setBrush(brush);
}

void drawGrid(QPainter& painter, QPointF startPoint, int rowCount, int colCount, double radius) {
	double r = radius;
	double sqrt3r = r * sqrt(3);
	double basex = startPoint.x(), basey = startPoint.y();
	for(int i = 0; i < rowCount; ++i) {
		for(int j = 0; j < colCount; ++j) {
			if(j & 1) {
				// bottom -> top
				painter.drawLine(i * sqrt3r + 0.5 * sqrt3r + basex, 0.5 * r + 1.5 * r * j + basey,
								 i * sqrt3r + 0.5 * sqrt3r + basex, 1.5 * r + 1.5 * r * j + basey);
				// bottom left -> top right
				painter.drawLine(i * sqrt3r + 1.0 * sqrt3r + basex, 1.5 * r * j + basey,
								 i * sqrt3r + 1.5 * sqrt3r + basex, 0.5 * r + 1.5 * r * j + basey);
				// bottom right -> top left
				painter.drawLine(i * sqrt3r + 1.0 * sqrt3r + basex, 1.5 * r * j + basey,
								 i * sqrt3r + 0.5 * sqrt3r + basex, 0.5 * r + 1.5 * r * j + basey);
			} else {
				// bottom -> top
				painter.drawLine(i * sqrt3r + basex, 0.5 * r + 1.5 * r * j + basey,
								 i * sqrt3r + basex, 1.5 * r + 1.5 * r * j + basey);
				// bottom left -> top right
				painter.drawLine(i * sqrt3r + 0.5 * sqrt3r + basex, 1.5 * r * j + basey,
								 i * sqrt3r + 1.0 * sqrt3r + basex, 0.5 * r + 1.5 * r * j + basey);
				// bottom right -> top left
				painter.drawLine(i * sqrt3r + 0.5 * sqrt3r + basex, 1.5 * r * j + basey,
								 i * sqrt3r + basex, 0.5 * r + 1.5 * r * j + basey);
			}
			// Special: right boarder
			// j is even & i not zero
			if(!(j & 1) && !i) {
				painter.drawLine(basex, 1.5 * r + 1.5 * r * j + basey,
								 0.5 * sqrt3r + basex, 2.0 * r + 1.5 * r * j + basey);
			}
		}
		// j == colCount - 1
		if(colCount & 1) basex -= 0.5 * sqrt3r;
		// bottom left -> top right
		painter.drawLine(i * sqrt3r + 0.5 * sqrt3r + basex, 1.5 * r * colCount + basey,
						 i * sqrt3r + 1.0 * sqrt3r + basex, 0.5 * r + 1.5 * r * colCount + basey);
		// bottom right -> top left
		if(i) {
			painter.drawLine(i * sqrt3r + 0.5 * sqrt3r + basex, 1.5 * r * colCount + basey,
							 i * sqrt3r + basex, 0.5 * r + 1.5 * r * colCount + basey);
		}
		if(colCount & 1) basex += 0.5 * sqrt3r;
	}
	for(int j = 0; j < colCount; ++j) {
		if(j & 1) {
			// bottom -> top
			painter.drawLine(rowCount * sqrt3r + 0.5 * sqrt3r + basex, 0.5 * r + 1.5 * r * j + basey,
							 rowCount * sqrt3r + 0.5 * sqrt3r + basex, 1.5 * r + 1.5 * r * j + basey);
		} else {
			// bottom -> top
			painter.drawLine(rowCount * sqrt3r + basex, 0.5 * r + 1.5 * r * j + basey,
							 rowCount * sqrt3r + basex, 1.5 * r + 1.5 * r * j + basey);
			// bottom right -> top left
			if(j) {
				painter.drawLine(rowCount * sqrt3r + 0.5 * sqrt3r + basex, 1.5 * r * j + basey,
								 rowCount * sqrt3r + basex, 0.5 * r + 1.5 * r * j + basey);
			}
		}
	}
	if(colCount & 1) basex -= 0.5 * sqrt3r;
	painter.drawLine(rowCount * sqrt3r + 0.5 * sqrt3r + basex, 1.5 * r * colCount + basey,
					 rowCount * sqrt3r + basex, 0.5 * r + 1.5 * r * colCount + basey);
	if(colCount & 1) basex += 0.5 * sqrt3r;
}

void drawHexagon(QPainter& painter, QPointF startPoint, double radius, bool erase) {
	auto oldMode = painter.compositionMode();
	if(erase) {
		painter.setCompositionMode(QPainter::CompositionMode_Clear);
	}
	double r = radius, r1 = radius * sqrt(3) / 2, r2 = radius * 0.5;
	QPolygonF hexagon {startPoint + QPointF{r1, r2}, startPoint + QPointF{0, r},
					   startPoint + QPointF{-r1, r2}, startPoint + QPointF{-r1, -r2},
					   startPoint + QPointF{0, -r}, startPoint + QPointF{r1, -r2}};
	painter.drawPolygon(hexagon);
	if(erase) {
		painter.setCompositionMode(oldMode);
	}
}

uint32_t posToHexId(double x, double y, double radius) {
	double r = radius;
	double sqrt3r = radius * sqrt(3);
	bool odd = false;
	int i = x / sqrt3r;
	int j = y / (1.5 * r);
	double r0 = y - j * 1.5 * r;
	double sqrt3 = sqrt(3);
	if(r0 >= 0.5 * r) { // easy mode
		odd = j & 1;
		if(odd) {
			i = (x - 0.5 * sqrt3r) / sqrt3r;
		}
	} else {
		double r1 = x - i * sqrt3r;
		odd = j & 1;
		if(odd) {
			i = (x - 0.5 * sqrt3r) / sqrt3r;
			r1 = x - 0.5 * sqrt3r - i * sqrt3r;
		}
		if(r1 <= 0.5 * sqrt3r) {
			if(r0 * sqrt3 <= (0.5 * sqrt3r - r1)) {
				if(!odd) i -= 1;
				j -= 1;
			}
		} else {
			if(r0 * sqrt3 <= (r1 - 0.5 * sqrt3r)) {
				j -= 1;
				if(odd) i += 1;
			}
		}
	}
	return ((i & 0xFFFF) << 16) | (j & 0xFFFF);
}

QPointF idToPoint(uint32_t id, QPointF startPoint, double radius) {
	int x = id >> 16, y = id & 0xFFFF;
	double a, b;
	double r = radius;
	double sqrt3r = radius * sqrt(3);
	a = x * sqrt3r + 0.5 * sqrt3r;
	b = y * 1.5 * r + r;
	if(y & 1) {
		a += 0.5 * sqrt3r;
	}
	return startPoint + QPointF {a, b};
}
