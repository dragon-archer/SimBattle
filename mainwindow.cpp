#include "pch.h"
#include "mainwindow.h"
#include "utility.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent) {
	this->setFixedSize(Global::windowWidth, Global::windowHeight);
	grabMouse();
	grabKeyboard();
	setMouseTracking(true);
	rowCount = 30;
	colCount = 19;
	radius = 20;
	startPoint = {50, 50};
	// noUpdateGrid = false;
	id = lastid = UINT_MAX;
}

MainWindow::~MainWindow() {
}

void MainWindow::paintEvent(QPaintEvent* event) {
	QPainter painter;
	setupPainter(painter, this);
	drawGrid(painter, startPoint, rowCount, colCount, radius);
	drawHexagon(painter, idToPoint(id, startPoint, radius), radius);
	// drawHexagon(painter, idToPoint(lastid, radius), radius, true);
	painter.end();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event) {
	// static uint32_t lastid = UINT_MAX;
	double x = event->position().x(), y = this->height() - event->position().y(); // Change the coordinate
	x -= startPoint.x();
	y -= startPoint.y();
	id = posToHexId(x, y, radius);
	if(id == lastid) return;
	lastid = id;
	// noUpdateGrid = true;
	if(validId(id)) {
		update();
	}
}

bool MainWindow::validId(uint32_t id) const {
	int x = id >> 16, y = id & 0xFFFF;
	if((x >= rowCount) || (y >= colCount)) return false;
	else return true;
}
