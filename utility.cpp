#include "pch.h"
#include "utility.h"

void drawGrid(QPainter& painter, QPointF startPoint, uint rowCount, uint colCount, double radius) {
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
