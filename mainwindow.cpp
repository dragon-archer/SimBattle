#include "pch.h"
#include "mainwindow.h"
#include "utility.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent) {
	this->setFixedSize(Global::windowWidth, Global::windowHeight);
	grabMouse();
	grabKeyboard();
	setMouseTracking(true);
	colCount = Global::colCount;
	rowCount = Global::rowCount;
	radius = Global::blockRadius;
	startPoint = {50, 50};
	drawShadow = false;
	id = UINT_MAX;
}

MainWindow::~MainWindow() {
}

void MainWindow::paintEvent(QPaintEvent* event) {
	QPainter painter;
	setupPainter(painter, this);
	drawGrid(painter, startPoint, colCount, rowCount, radius);
	if(drawShadow) {
		drawHexagon(painter, idToPoint(id, startPoint, radius), radius);
	}
	painter.end();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
	static uint32_t lastid = UINT32_MAX;
	double x = event->position().x(), y = this->height() - event->position().y(); // Change the coordinate
	x -= startPoint.x();
	y -= startPoint.y();
	id = posToHexId(x, y, radius);
	IF_LIKELY(id == lastid) return;
	lastid = id;
	if(validId(id)) {
		drawShadow = true;
		update();
	} else {
		drawShadow = false;
		update();
	}
}

bool MainWindow::validId(uint32_t id) const {
	short x = id >> 16, y = id & 0xFFFF;
	if((x >= colCount) || (y >= rowCount)) return false;
	else return true;
}
