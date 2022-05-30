#include "pch.h"
#include "utility.h"

void setupPainter(QPainter& painter, QPaintDevice* object) {
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

// Note: Result is cached, so colCount, rowCount, and radius should not change
void drawGrid(QPainter& painter, QPointF startPoint, int rowCount, int colCount, double radius) {
	static QPixmap bgPixmap;
	static bool isInited = false;
	IF_LIKELY(isInited) {
		painter.drawPixmap(startPoint, bgPixmap);
		return;
	}
	QPainter p;
	QImage bgImage(sqrt(3) * radius * (colCount + 0.5), radius * (1.5 * rowCount + 0.5), QImage::Format_ARGB32_Premultiplied);
	setupPainter(p, &bgImage);

	double r = radius;
	double sqrt3r = r * sqrt(3);
	for(int i = 0; i < colCount; ++i) {
		for(int j = 0; j < rowCount; ++j) {
			if(j & 1) {
				// bottom -> top
				p.drawLine( i * sqrt3r, 0.5 * r + 1.5 * r * j,
							i * sqrt3r, 1.5 * r + 1.5 * r * j);
				// bottom left -> top right
				p.drawLine( i * sqrt3r + 0.5 * sqrt3r, 1.5 * r * j,
							i * sqrt3r + 1.0 * sqrt3r, 0.5 * r + 1.5 * r * j);
				// bottom right -> top left
				p.drawLine( i * sqrt3r + 0.5 * sqrt3r, 1.5 * r * j,
							i * sqrt3r, 0.5 * r + 1.5 * r * j);
			} else {
				// bottom -> top
				p.drawLine( i * sqrt3r + 0.5 * sqrt3r, 0.5 * r + 1.5 * r * j,
							i * sqrt3r + 0.5 * sqrt3r, 1.5 * r + 1.5 * r * j);
				// bottom left -> top right
				p.drawLine( i * sqrt3r + 1.0 * sqrt3r, 1.5 * r * j,
							i * sqrt3r + 1.5 * sqrt3r, 0.5 * r + 1.5 * r * j);
				// bottom right -> top left
				p.drawLine( i * sqrt3r + 1.0 * sqrt3r, 1.5 * r * j,
							i * sqrt3r + 0.5 * sqrt3r, 0.5 * r + 1.5 * r * j);
			}
			// Special: right boarder
			// j is even & i not zero
			if((j & 1) && !i) {
				p.drawLine( 0, 1.5 * r + 1.5 * r * j,
							0.5 * sqrt3r, 2.0 * r + 1.5 * r * j);
			}
		}
		// j == rowCount - 1
		double basex = 0;
		if(rowCount & 1) basex = -0.5 * sqrt3r;
		// bottom left -> top right
		p.drawLine( basex + i * sqrt3r + 1.0 * sqrt3r, 1.5 * r * rowCount,
					basex + i * sqrt3r + 1.5 * sqrt3r, 0.5 * r + 1.5 * r * rowCount);
		// bottom right -> top left
		IF_LIKELY(i) {
			p.drawLine( basex + i * sqrt3r + 1.0 * sqrt3r, 1.5 * r * rowCount,
						basex + i * sqrt3r + 0.5 * sqrt3r, 0.5 * r + 1.5 * r * rowCount);
		}
	}
	for(int j = 0; j < rowCount; ++j) {
		if(j & 1) {
			// bottom -> top
			p.drawLine( colCount * sqrt3r, 0.5 * r + 1.5 * r * j,
						colCount * sqrt3r, 1.5 * r + 1.5 * r * j);
			// bottom right -> top left
			IF_LIKELY(j) {
				p.drawLine( colCount * sqrt3r + 0.5 * sqrt3r, 1.5 * r * j,
							colCount * sqrt3r, 0.5 * r + 1.5 * r * j);
			}
		} else {
			// bottom -> top
			p.drawLine( colCount * sqrt3r + 0.5 * sqrt3r, 0.5 * r + 1.5 * r * j,
						colCount * sqrt3r + 0.5 * sqrt3r, 1.5 * r + 1.5 * r * j);
		}
	}
	double basex = 0;
	if(rowCount & 1) basex = 0.5 * sqrt3r;
	p.drawLine( basex + colCount * sqrt3r, 1.5 * r * rowCount,
				basex + colCount * sqrt3r - 0.5 * sqrt3r, 0.5 * r + 1.5 * r * rowCount);

	p.end();
	bgPixmap = QPixmap::fromImage(bgImage);
	isInited = true;
	painter.drawPixmap(startPoint, bgPixmap);
}

// Note: reesult is cached, so radius should not change
void drawHexagon(QPainter& painter, QPointF startPoint, double r) {
	static QPixmap hexagonPixmap;
	static bool isInited = false;
	IF_LIKELY(isInited) {
		painter.drawPixmap(startPoint, hexagonPixmap);
		return;
	}
	double r1 = r * sqrt(3) / 2, r2 = r * 0.5;
	QPolygonF hexagon { QPointF{r1, 0}, QPointF{2 * r1, r2},
						QPointF{2 * r1, 3 * r2}, QPointF{r1, 2 * r},
						QPointF{0, 3 * r2}, QPointF{0, r2}};
	QImage hexagonImage(2 * r1, 2 * r, QImage::Format_ARGB32_Premultiplied);
	QPainter p;
	setupPainter(p, &hexagonImage);
	p.drawPolygon(hexagon);
	p.end();
	hexagonPixmap = QPixmap::fromImage(hexagonImage);
	isInited = true;
}

HexPosition posToHex(double x, double y, double r) {
	double sqrt3 = sqrt(3);
	double sqrt3r = r * sqrt3;
	double r0;
	int i = floor(x / sqrt3r);
	int j = floor(y / (1.5 * r));
	bool odd = j & 1;
	r0 = y - 1.5 * j * r;
	IF_LIKELY(r0 >= 0.5 * r) { // easy mode
		if(!odd) {
			i = floor((x - 0.5 * sqrt3r) / sqrt3r);
		}
	} else {
		double r1 = x - i * sqrt3r;
		if(!odd) {
			i = floor((x - 0.5 * sqrt3r) / sqrt3r);
			r1 = x - 0.5 * sqrt3r - i * sqrt3r;
		}
		if(r1 <= 0.5 * sqrt3r) {
			if(r0 * sqrt3 <= (0.5 * sqrt3r - r1)) {
				if(odd) i -= 1;
				j -= 1;
			}
		} else {
			if(r0 * sqrt3 <= (r1 - 0.5 * sqrt3r)) {
				j -= 1;
				if(!odd) i += 1;
			}
		}
	}
	return HexPosition{i, j};
}
